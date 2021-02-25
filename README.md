### For Game Design 2021 - UAIC FII 

Project Proposal and technical specs : 
[document](https://github.com/LoghinVladDev/c-eng/blob/master/GD_Loghin_Vlad-Andrei_Engine_ProjectProposal.docx) Project Proposal

### Introduction

Game Engine Project. Started as a port from a small Java 2D game engine, turned into a 
3D engine in C++ OpenGL/Vulkan

### Compilation

The engine is currently in development for Windows/Linux. Only requires 
OS libraries, no need for external APIs. 

Indev compilation : 
 * Linux : GCC and Clang.
 * Windows : MinGW-w64. Not tested in MVSC
 
Compilation guide TBD, for now use CMake

The project is developed only by me at the moment, if for any reason you plan
to build / use this, keep in mind that most targets will not work (for now)

### Usage

Documentation TBA at a much later date

### Contributing

Contribution guide TBA 

### Dependencies 

CMake 3.5 or later\
Dependencies located in dependencies folder : 

 * [GLFW](https://github.com/glfw/glfw) GLFW framework for OpenGL
 * [GLAD](https://github.com/Dav1dde/glad) OpenGL loader/generator
 * [GLM](https://github.com/g-truc/glm) OpenGL mathematics
 * [Open Asset Import Library (assimp)](https://github.com/assimp/assimp) for asset import 
 * [stb\_image](https://github.com/nothings/stb) for texture image loading
