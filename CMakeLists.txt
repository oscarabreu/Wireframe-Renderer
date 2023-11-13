cmake_minimum_required(VERSION 3.0)
project(MyProject)

# Compiler settings
set(CMAKE_CXX_COMPILER g++)
add_compile_options(-Wall) # Add any other CPPFLAGS you might have

# Globbing source files
file(GLOB SOURCES "*.cpp")

# Define the executable
add_executable(main ${SOURCES})

# Link libraries
target_link_libraries(main m) # 'm' is for the math library

# Specify where to output the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
