# 3DRaytrace
The goal of this project is to create a 3D raytracer that can render various objects with reflections, refraction, and shadows.  In other words, it should be able to generate an image of a scene containing a variety of objects made of "materials" with different properties.  Unfortunately, most of these goals have not yet been achieved.

### Progress
Currently, the program is able to render flat shaded spheres and planes with simplified direct lighting, and reflections for all objects will soon be finished.  Unfortunately, all planes are restricted to being aligned with one of the three axes.  A TODO list with features to add, bugs to fix, and things to finish can be found in "[TODO.md](http://github.com/name-here/3DRaytrace/blob/master/TODO.md)".  

### Notes
- Currently, there may be bugs if there are more objects loaded than the max int value, as each object has an ID, which is stored as an int.

### Compiling
To compile, simply ```cd``` into directory containing the project files and run ```make```.  This will create the executable "3DRaytrace".  To start the program, just run the executable with ```./3DRaytrace```.

Note: You must have the development version of SDL2(download [here](http://www.libsdl.org/download-2.0.php)) installed to compile the program, and either the development or runtime version installed to run it.  As a temporary solution for Mac, the executable must be in either /Library/Frameworks (needed for compiling) or ~/Library/Frameworks.  In addition, ```$(PKGFLAGS)``` on line 8 of the Makefile must be deleted, and ``` `sdl2-config --cflags` ``` on line 2 must be replaced with ```-I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2```  Line 3, beginning with ```PKGFLAGS =```, can also be deleted.