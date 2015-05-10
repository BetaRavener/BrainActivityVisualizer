BrainActivityVisualizer
=======================

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
7. Build