# Handmade_Raytracer_Project
A ray tracer project from scratch using techniques used by Casey Muratori. Its a simple one using planes and spheres employing SIMD and multithreading.

Also added a new build system completely replacing the old Visual Studio Solution files method. Using one build.bat command in the code\ folder. Running the build.bat file will compile the code along with all the cl Visual Studio compiler flags. Having a custom build.bat file makes it more easier to manage the build system.

For more information on using this build system take a look at Casey Muratori's Handmade Hero stream.

Please change the shell.bat file in the misc\ directory based on where your VCVARSALL Path is in your machine. The manual build system still uses the Microsoft Visual C++ Compiler so it needs the correct path.

https://guide.handmadehero.org/code/day001/ For setting up the initial Build Stream https://guide.handmadehero.org/code/day016/ For more info on the Visual Studio Compiler Switches.
