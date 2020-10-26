# FYS3150_project_3

Here is a model for the n-body problem with a relativistic correction. To run the program you can go into the terminal and type "make all".
If you want to run the test functions remove main.cpp from the compile part of the makefile and add unit_test.cpp instead.

In the main file you find the variables you can change and a few code examples to run the simulation. These will make a text file in the data folder. 
To see the plots you go in to python_plot files and type for example python3 planet_plot.py to see a picture of the planets orbits.
In the main.cpp the string called filename is the filename of the text file. This needs to be the same as the variable called filename at the top of the python file.

If you set the bool called relativistic_correction to true you get relativistic_correction, set it to false to turn it off.
The float beta is for the gravitational force, let it be 2 for regular gravitational force. As described in task.

The string method can be "Verlocity-Verlet", "RK4", "Euler-Cromer" or "Euler". 
