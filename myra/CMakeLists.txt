#setting the cmake minimum project to build the project
cmake_minimum_required(VERSION 3.10) 
# setting the project name
project(myra)

# instructs the compiler sto strictly use c++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# adds include directory to the path where the compiler will look for binaries
include_directories(include)

# defines a variable source which lists all the source files
set(SOURCES 
    src/arena.cpp
)

# creates a executable named kira using the source files defined in the source variable
add_executable(myra ${SOURCES})

# ensures pkg-config is available, which is used to locate libraries and their flags.
find_package(PkgConfig REQUIRED)
# uses pkg-config to find the required libraries, cairo and X11
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(X11 REQUIRED x11)

# adds include directories for cairo and x11 to the compilers search path
include_directories(${CAIRO_INCLUDE_DIRS} ${X11_INCLUDE_DIRS})

# adds the directories containing the compiled cairo and x11 libraries to the linkers search path
link_directories(${CAIRO_LIBRARY_DIRS} ${X11_LIBRARY_DIRS})

# links kira the exec with the cairo and x11 libraries
target_link_libraries(myra ${CAIRO_LIBRARIES} ${X11_LIBRARIES})
