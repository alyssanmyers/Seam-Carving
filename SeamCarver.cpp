/*******************************************************/
// Alyssa Myers
// 3460:435 Algorithms
// Project 3 — Seam Carving
// April 10, 2017
//
// Dynamic programming algorithm for image manipulation.
/*******************************************************/

#include <cmath>

using namespace std;

enum class SeamDirection
{
    VERTICAL,
    HORIZONTAL
};

class SeamCarver
{
    PixelGrid original_grid;
    PixelGrid copy_grid;
    PixelGrid energy_grid;
    PixelGrid cost_grid;

    // computes energy of a single pixel in the grid
    int computePixelEnergy(PixelGrid&, int, int);
    
    // computes the energy of the pixel grid
    PixelGrid computeEnergyGrid(PixelGrid&);
    
    // determines the cumulative grid and smallest cost seam
    void findVerticalSeam();
    
    // deletes the vertical seam
    void deleteVerticalSeam();

public:
    
    SeamCarver(PixelGrid image)
    {
        original_grid = image;
        copy_grid = original_grid;
    }
    
    // returns the duplicate of the grid
    PixelGrid getGrid();
    
    // runs the seam carving algorithm
    PixelGrid executeAlgorithm(unsigned int, SeamDirection);
};

PixelGrid SeamCarver::getGrid()
{
    return copy_grid;
}

PixelGrid SeamCarver::executeAlgorithm(unsigned int times, SeamDirection dir)
{
    for (int i = 0; i < times; i++)
    {
        // calculate energy pixel grid
        energy_grid = computeEnergyGrid(copy_grid);
        
        // if vertical seam
        if (dir == SeamDirection::VERTICAL)
        {
            // identify and delete the seam
            findVerticalSeam();
            deleteVerticalSeam();

        }
        // if horizontal seam
        else if (dir == SeamDirection::HORIZONTAL)
        {
            copy_grid.rotateGrid();
            energy_grid.rotateGrid();
            cost_grid.rotateGrid();

            // identify and delete the seam
            findVerticalSeam();
            deleteVerticalSeam();

            copy_grid.rotateGrid();
            energy_grid.rotateGrid();
            cost_grid.rotateGrid();
        }
    }
    
    return copy_grid;
}

int SeamCarver::computePixelEnergy(PixelGrid& grid, int x, int y)
{
    // retrieve the current pixel's value
    int current = grid.getValue(x, y);
    
    int top, bottom, right, left;
    
    if (x==0) left = grid.getValue(x,y);
    else left = grid.getValue(x-1,y);
    
    if (y==0) top = grid.getValue(x,y);
    else top = grid.getValue(x,y-1);
    
    if(x==grid.getWidth()-1) right = grid.getValue(x,y);
    else right = grid.getValue(x+1,y);
    
    if(y==grid.getHeight()-1) bottom = grid.getValue(x,y);
    else bottom = grid.getValue(x,y+1);
    
    int result = abs(current-top) + abs(current-bottom) + abs(current-right) + abs(current-left);
    
    return result;
}


PixelGrid SeamCarver::computeEnergyGrid(PixelGrid& grid)
{
    // make sure the new grid has the same number of columns and rows
    PixelGrid temp_grid = PixelGrid(grid.getWidth(), grid.getHeight());
    
    // scan through and update energy values
    for (int x = 0; x < grid.getWidth(); x++)
    {
        for (int y = 0; y < grid.getHeight(); y++)
        {
            // retrieve the pixel's energy
            int energy = computePixelEnergy(grid, x, y);
            
            // set energy value for current pixel (Δx + Δy)
            temp_grid.setValue(x, y, energy);
        }
    }
    
    return temp_grid;
}

void SeamCarver::findVerticalSeam()
{
    // generate cost grid
    int width = energy_grid.getWidth();
    int height = energy_grid.getHeight();
    cost_grid = PixelGrid(width, height);
    
    // building the cumulative cost grid
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (y == 0)
            {
                // first row matches the first column
                cost_grid.setValue(x, y, energy_grid.getValue(x, y));
            }
            else
            {
                int min_previous;
                
                if (x == 0)
                {
                    min_previous = min(cost_grid.getValue(x+1, y-1), cost_grid.getValue(x, y-1));
                }
                else if (x == (width - 1))
                {
                    min_previous = min(cost_grid.getValue(x-1, y-1), cost_grid.getValue(x, y-1));
                }
                else
                {
                    min_previous = min( min(cost_grid.getValue(x-1, y-1), cost_grid.getValue(x+1, y-1)), cost_grid.getValue(x, y-1) );
                }
                
                cost_grid.setValue(x, y, energy_grid.getValue(x, y) + min_previous);
            }
        }
    }
    
    // identify the smallest cost seam and assign them -1
    int smallest = 0;
    
    // locating the lowest cost at the bottom row
    for (int x = 0; x < width; x++)
    {
        if (cost_grid.getValue(x, height - 1) < cost_grid.getValue(smallest, height - 1))
        {
            smallest = x;
        }
    }
    
    // assigning that smallest bottom index a value of -1
    copy_grid.setValue(smallest, height - 1, -1);
    
    // trace back through the rest of the grid to find that seam
    for (int i = 1; i < height; i++)
    {
        int current_height = height - 1 - i;
        int right = smallest + 1;
        int center = smallest;
        int left = smallest - 1;
        
        if (right < 0 || right >= width)
        {
            right = center;
        }
        if (left < 0 || left >= width)
        {
            left = center;
        }
        
        int smallest_value = min( min(cost_grid.getValue(right, current_height), cost_grid.getValue(left, current_height)), cost_grid.getValue(center, current_height) );
        
        if (cost_grid.getValue(left, current_height) == smallest_value)
        {
            smallest = left;
        }
        else if (cost_grid.getValue(center, current_height) == smallest_value)
        {
            smallest = center;
        }
        else if (cost_grid.getValue(right, current_height) == smallest_value)
        {
            smallest = right;
        }

        copy_grid.setValue(smallest, current_height, -1);
    }
}

void SeamCarver::deleteVerticalSeam()
{
    unsigned int width = energy_grid.getWidth();
    int height = energy_grid.getHeight();
    
    int old_width = width;
    width--;
    
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < old_width; x++)
        {
            int current_value = copy_grid.getValue(x, y);
            
            // pixel to delete
            if (current_value == -1)
            {
                // iterate through seam to move each pixel over
                for (int current = x; current < old_width - 1; current++)
                {
                    int next = current + 1;
                    int next_value = copy_grid.getValue(next, y);
                    copy_grid.setValue(current, y, next_value);
                }
            }
        }
    }
    
    copy_grid.setWidth(width);
}








