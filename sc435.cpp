/*******************************************************/
// Alyssa Myers
// 3460:435 Algorithms
// Project 3 — Seam Carving
// April 10, 2017
//
// Dynamic programming algorithm for image manipulation.
/*******************************************************/

#include <iostream>
#include <iomanip>
#include <regex>
#include <string>

#include "PixelGrid.cpp"
#include "Buffer.cpp"
#include "SeamCarver.cpp"

using namespace std;

int main(int argc, char* argv[])
{
    // check proper number of arguments
    if (argc == 4)
    {
        // remove file extension
        string file = regex_replace(argv[1], regex("(\\.pgm)"), "");
        
        // get number of vertical seams
        unsigned int vert_seams = atoi(argv[2]);
        
        // get number of horizontal seams
        unsigned int horiz_seams = atoi(argv[3]);
        
        cout << "Removing " << vert_seams << " vertical seams and "
             << horiz_seams << " horizontal seams from '" << file << "'..." << endl;
        
        // load the file
        Buffer buffer;
        buffer.loadFile(file + ".pgm");
        
        SeamCarver carver = SeamCarver(buffer.getGrid());
        if (vert_seams > 0)
            carver.executeAlgorithm(vert_seams, SeamDirection::VERTICAL);
        if (horiz_seams > 0)
            carver.executeAlgorithm(horiz_seams, SeamDirection::HORIZONTAL);
        buffer.setGrid(carver.getGrid());
        
        // export the file
        buffer.exportFile(file + "_processed.pgm");
    }
    else
    {
        throw runtime_error("Invalid number of arguments!");
    }
    
    return 0;
}
