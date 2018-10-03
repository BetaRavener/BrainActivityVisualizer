BrainActivityVisualizer
=======================

### Read [Documentation in English](http://www.fit.vutbr.cz/study/DP/BP.php.cs?id=16538&file=t).

Compiling on Windows:
Prerequisites:
- CMake
- Qt5 with MinGW package
- Tinyobjloader library compiled statically
- UniShader library compiled dynamically
- GLEW library compiled dynamically with MX extension

Procedure:
- The folder with this readme is root to project and will be further referred
  to as PROJ_DIR

1. Start Qt.
2. Select open project and navigate to this project folder.
   Select CMakeLists.txt and open it.
3. Build Location
   Select build directory, preferable PROJ_DIR\build
4. Choose CMake Executable
   Input path to CMake executable (cmake.exe, not the GUI). It is located 
   in bin folder of CMake installation directory.
5. Run CMake: This step will run CMake and generate Qt project.
   Optionally provide arguments to CMake:
       Build type:
         -DCMAKE_BUILD_TYPE=Release
         -DCMAKE_BUILD_TYPE=Debug
    Select generator, use 32bit versions:
      - NMake Generator with preferred kit
      - MinGW Generator with MinGW kit
    Click "Run CMake"
6. If CMake could not locate required libraries, it will generate error message
   and provide instructions how to configure project manually. Please, follow
   the instructions until "Configuring done" is not present in the output. CMake
   should also list paths to all required libraries in that case.
   CMake-gui can be helpful in the process of project configuration. Set path to
   source code to PROJ_DIR and "Where to build the binaries" to PROJ_DIR\build.
   CMake should list all the configurable options and mark the errors with red.
7. Build the application using Qt.


In order to run the application:
1. Copy the dynamic libraries into build directory. If running outside Qt, it is
   also neccessary to copy Qt libraries. Refer to 
   http://doc.qt.io/qt-5/windows-deployment.html for futher instructions.
2. Copy the folder with shader programs into build directory.
3. Copy the content of resources folder into build directory.
4. The application is ready to be executed.
