/*******************************************************/
// Alyssa Myers
// 3460:435 Algorithms
// Project 3 — Seam Carving
// April 10, 2017
//
// Dynamic programming algorithm for image manipulation.
/*******************************************************/

#include <regex>
#include <fstream>
#include <string>

using namespace std;

class Buffer
{
    string header;
    int gray_scale, rows, columns;
    
    vector<int> data;
    PixelGrid grid;
    
public:

    // loads a PGM image file
    void loadFile(string);
    
    // exports the updated grid to PGM file
    void exportFile(string);
    
    // retrieves the pixel grid
    PixelGrid getGrid();
    
    // updates the pixel grid
    void setGrid(PixelGrid grid);
    
    // checks if a line is a comment
    bool isComment(string);

};

void Buffer::loadFile(string path)
{
    string size, r, c, scale;
    
    ifstream ifs(path);
    
    /********************/
    // parse the header //
    /********************/
    
    // get PGM header
    do
    {
        getline(ifs, header);
    }   while (isComment(header));
    
    // get the size line
    do
    {
        getline(ifs, size);
    }   while (isComment(size));
    
    // parse the size line
    const char* character = size.c_str();
    while (*character != ' ')
        r += *character++;
    for (int i = 0; i < size.length(); i++)
    {
        c += *character++;
        i++;
    }
    rows = stoi(r);
    columns = stoi(c);
    
    // gray scale
    do
    {
        getline(ifs, scale);
    }   while (isComment(scale));
    
    gray_scale = stoi(scale);
    
    /******************/
    // parse the body //
    /******************/
    
    // reading each line, parsing it, and storing into vector
    while (!ifs.eof())
    {
        string line;
        do
        {
            getline(ifs, line);
        }   while (isComment(line));
        
        const char* position = line.c_str();
        for (int i = 0; i < line.length(); i++)
        {
            string temp;
            while (*position != ' ' && *position != '\t')
            {
                temp += *position++;
                i++;
            }
            temp += *position++;
            
            data.push_back(stoi(temp));
        }
    }
    
    // converting the linear vector of ints to a 2d PixelGrid of ints
    int pos = 0;
    unsigned int rw = rows, cm = columns;
    grid.setWidth(rw);
    grid.setHeight(cm);
    
    for (int column = 0; column < columns; ++column)
        for (int row = 0; row < rows; ++row)
            grid.setValue(row, column, data.at(pos++));
    
    ifs.close();
}

void Buffer::exportFile(string path)
{
    ofstream ofs(path);
    
    /********************/
    // write the header //
    /********************/
    
    ofs << header << endl
        << "# " << path << " Created by Alyssa" << endl
        << rows << " " << columns << endl
        << gray_scale << endl;
    
    /******************/
    // write the body //
    /******************/
    
    for (int column = 0; column < columns; ++column)
    {
        for (int row = 0; row < rows; ++row)
            ofs << grid.getValue(row, column) << " ";
        
        ofs << endl;
    }
}

PixelGrid Buffer::getGrid()
{
    return grid;
}

void Buffer::setGrid(PixelGrid grid)
{
    this->grid = grid;
    rows = grid.getWidth();
    columns = grid.getHeight();
}

bool Buffer::isComment(string str)
{
    const char* position = str.c_str();
    
    return *position == '#';
}
