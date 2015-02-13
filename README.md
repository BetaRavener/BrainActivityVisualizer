BrainActivityVisualizer
=======================

Compiling on Windows:
Prerequisites:
- CMake
- Qt5 with MinGW package

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
6. Build

http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/InstallationGuide/html/ch02s02.html