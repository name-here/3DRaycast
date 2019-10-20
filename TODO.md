# 3DRaytrace TODO List(s)

### To Do:

<!-- - classes.cpp line 182: add position to ball shadow casting(??) -->
- Find the normal of a triangle when it is created
- Finish triangle.cast
- Make triangle.cast work for shadows
- Optimize getting rays for camera (maybe don't use sine/cosine)
- Optimize operator== on points if possible
- Optimize various functions in objects.cpp (cast functions) to use -=, +=, etc.
- Have all variables set by the object hit by the ray be set only for that object instead of being set by each successive object until it gets to the right one.
- Go through code and trim out unnecessary variables and stuff
- Make lists in World object private and create some other way of changing the properties of objects in them (add functions should return pointer/id)
- Find way of updating all relevant planeDist on window resize (difficult if multiple cameras)
- Add textured objects (texture system, textures maybe as part of generic Object?)
- Use square of distance to check closest to save sqrt() call
- Add multithreading (COMPLICATED)
- Don't include same inline functions in multiple files
- Add high DPI capability
- Move all global variables into main() or other functions
- Change Ray objects to store a point and a vector instead of two points (still usint Point objects for both?)
- Clean up includes (if necessary)
- Replace number/ID systems with pointers
- Replace simple square root color nonlinearization to something more correct (Account for screen gama or whatever, LIKELY COMPLICATED)
- Add complete list of dependencies to README
- Make Fresnel stuff actually physically accurate
- Fix having to press ESC twice to exit control on the web build
- Move (some) constants to a separate constants file
- Change CRay::finishCast(), CRay::lightColor, and CRay::addLight so that light can go over camera's max exposure and overexpose pixels (LIKELY COMPLICATED)
- Add HDR monitor support (MAYBE COMPLICATED)
- Go through entire code base and tweak formatting to be consistent
- Give objects textures
- Fix sparkles (random pixels or short lines of pixels lighting up) when looking up at bottom of reflective plane

### Partially Done:

- Properly clean up World objects on exit (I think I did it?)
- Optimize Plane::cast to not create new Point and Ray objects
- Fix issue of no shadows on line of x=0 (Maybe done?, probably not)
- Add cube object
- Optimize things like [variable] = Point() to set all of the values to 0 instead of constructing a new object, and replace similar constructions with Point.set() function  (also Camera.move)
- Change all instances of setting points by components to use Point.set() function
- Make used CRay(s) not part of main file (maybe put into Camera class)
- Make shadows more realistic (add indirect lighting, integrate into normal cast)

### Done:

- Make the plane cast actually get what axis it is on from the variable
- Figure out mouseX and mouseY polarity
- Restructure so that world object contains all objects to be cast
- Make use of Point object universal
- Fix shadows!
- Make use of Color objects universal
- Fix color issues caused by non-linear association of RGB values and brightness
- Finish camera.rotate and camera.getRay to make them actually work with rotation
- Find the required vectors for the camera when it is created
- Move this TODO list to a separate file
- Redefine operators and such to work with points(and rays?) (Operator overloading)
- Add shadows for plane.cast
- Transfer reflections(maybe more) to World.cast()
- Check if cstdint package is actually needed in world.cpp
- Avoid drawing spheres that are behind the camera
- Make window resizable
- Add reflections to all objects
- Link SDL2 into application (see "macosx" [hg.libsdl.org/SDL/file/default/docs/](http://hg.libsdl.org/SDL/file/default/docs/))  OR  add Xcode files to github
- Make new file for world and make camera part of world class
- Move Point object into separate file
- Fix black lines between some pixels when pixelSize > 1
- Add movement controls [for debug / testing]
- Solve Camera funcs(see start of draw()) not working without another func after it
- add INTERSECT_ERR functionality to planes

### Maybe Do:

- Separate alpha from color object (not needed for some uses of Color)
- Add and impliment/use ray.length
- Optimize cross and dot products
- Find way not to trust passed width and height values (bad values could allow for overflow and potential security vulnerability)
- Move Color to new file
- Move color setting into world.cast (??)
- make Vector object (separate from Point object?) to distinguish between uses
- Add player / first-person object(class) which does camera controls
- Have planes return opposite normal vector for rays coming from back side (make planes double sided in terms of normals)


