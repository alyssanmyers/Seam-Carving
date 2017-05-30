3460:435 Algorithms Project 3 — Dynamic Programming Seam Carving 04/10/2017
Alyssa Myers

General Description
———————————————————
Dynamic programming algorithm for image manipulation.

Execution
—————————
1) Go to the project directory via command line.
2) sc435 is to be ran using C++11 compiler.
3) The first command line argument is the .pgm file to be manipulated.
4) The second command line argument is the number of vertical seams to remove.
5) The third command line argument is the number of horizontal seams to remove.

Seam Carving
————————————————————————————————————————————————————
o Loads a file to be processed, which is provided by the user through the command line.
o The number of vertical and horizontal lines to be removed is supplied by the user through the command line.
o Save the processed image as _original_image_file_name_processed.pgm

Files
—————
o sc435 - main file 
o PixelGrid - a 2D vector array that is easily manipulated.
o Buffer - loads and saves PGM files.
o Seam Carver - functions that perform the seam carving algorithm.

Usage
—————
1) ./sc435 _image_file_name.pgm 0 0
