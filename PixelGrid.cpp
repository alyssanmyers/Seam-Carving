/*******************************************************/
// Alyssa Myers
// 3460:435 Algorithms
// Project 3 — Seam Carving
// April 10, 2017
//
// Dynamic programming algorithm for image manipulation.
/*******************************************************/

#include <vector>

using namespace std;

class PixelGrid
{
    unsigned int width, height;
    vector<vector<int>> grid;
    
public:
    
    // constructs a new grid
    PixelGrid();
    PixelGrid(unsigned int, unsigned int);
    
    // gets the width
    unsigned int getWidth();
    
    // sets the width
    void setWidth(unsigned int&);
    
    // gets the height
    unsigned int getHeight();
    
    // sets the height
    void setHeight(unsigned int&);
    
    // retrieves value at given coordinate
    int getValue(unsigned int, unsigned int);
    
    // sets value at given coordinate
    void setValue(const unsigned int&, const unsigned int&, const int&);
    
    // deletes a specific pixel
    void deletePixel(unsigned int&, unsigned int&);
    
    // deletes the grid
    void deleteGrid();
    
    // rotates the grid
    void rotateGrid();
    
    // prints the given grid out
    void printGrid();

};

PixelGrid::PixelGrid()
{
    width = 0;
    height = 0;
    
    grid[0][0];
}

unsigned int PixelGrid::getWidth()
{
    return width;
}

void PixelGrid::setWidth(unsigned int& width)
{
    this->width = width;
    
    grid.resize(width, vector<int>(height));
}

unsigned int PixelGrid::getHeight()
{
    return height;
}

void PixelGrid::setHeight(unsigned int& height)
{
    this->height = height;
    
    for (auto& entry : grid)
    {
        entry.resize(height);
    }
}

PixelGrid::PixelGrid(unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
    
    grid.resize(width);
    for (auto& entry : grid)
    {
        entry.resize(height);
    }
}

int PixelGrid::getValue(unsigned int x, unsigned int y)
{
    if (x >= width)
    {
        string err = "X coordinate (" + to_string(x) + ") is not within bounds to get.";
        throw runtime_error(err);
    }
    else if (y >= height)
    {
        string err = "Y coordinate (" + to_string(y) + ") is not within bounds to get.";
        throw runtime_error(err);
    }
    
    return grid[x][y];
}

void PixelGrid::setValue(const unsigned int& x, const unsigned int& y, const int& value)
{
    if (x >= width)
    {
        string err = "X coordinate (" + to_string(x) + ") is not within bounds to set.";
        throw runtime_error(err);
    }
    else if (y >= height)
    {
        string err = "Y coordinate (" + to_string(y) + ") is not within bounds to set.";
        throw runtime_error(err);
    }
    
    grid[x][y] = value;
}

void PixelGrid::deletePixel(unsigned int& x, unsigned int& y)
{
    if (x >= width)
    {
        string err = "X coordinate (" + to_string(x) + ") is not within bounds to delete.";
        throw runtime_error(err);
    }
    else if (y >= height)
    {
        string err = "Y coordinate (" + to_string(y) + ") is not within bounds to delete.";
        throw runtime_error(err);
    }
    
    grid[x][y] = 0;
}

void PixelGrid::deleteGrid()
{
    for (unsigned int x = 0; x < getWidth(); x++)
    {
        for (unsigned int y = 0; y < getHeight(); y++)
        {
            deletePixel(x, y);
        }
    }
}

void PixelGrid::rotateGrid()
{
    vector<vector<int>> temp_grid = grid;
    
    int prev_width = width;
    int prev_height = height;
    
    deleteGrid();
    
    height = prev_width;
    width = prev_height;
    
    grid.resize(width);
    for (auto& entry : grid)
    {
        entry.resize(height);
    }
    
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            setValue(x, y, temp_grid[y][x]);
}

void PixelGrid::printGrid()
{
    for (int y = 0; y < height; y++)
    {
        cout << " | ";
        for (int x = 0; x < width; x++)
        {
            cout << getValue(x,y) << " | ";
        }
        cout << endl;
    }
}

