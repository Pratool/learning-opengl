# External Dependencies
CMake is used to manage dependencies in this project.
A subset of the dependencies necessary to build and run the applications of this repository can be installed using this incomplete guide.
No attempt was made to address cross-platform issues and has only been tested on a personal machine running Ubuntu 18.04 LTS.
For the sake of brevity, I have omitted various configuration parameters and provide no warning against using danagerous commands.
You will never need super user privileges to build and install the external dependencies.
All commands provided are examples only.

## Installation
Assumes that this repository is cloned into a directory named `learning-opengl`.
1. Make build and installation directories above the repository root.
   Switch to the build directory.
```bash
cd ../..
mkdir -p extbld extinst
cd extbld
```

2. Run the CMake configuration step.  
```bash
cmake -G Ninja \
    -DCMAKE_INSTALL_PREFIX=../extinst \
    ../learning-opengl/external
```

4. Build all targets to attempt to build and install all external dependencies.
```bash
cmake --build . --target all
```
