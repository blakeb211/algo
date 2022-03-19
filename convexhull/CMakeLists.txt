cmake_minimum_required(VERSION 3.22)

# set proj name
project(ConvexHull)

# add executable
add_executable(ConvexHull main.cpp convexlib.cpp)
set_property(TARGET ConvexHull PROPERTY CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND EXTRA_LIBS SDL2main SDL2)
list(APPEND EXTRA_INCLUDES "/usr/include/SDL2")

target_link_libraries(ConvexHull PUBLIC ${EXTRA_LIBS})
target_include_directories(ConvexHull PUBLIC 
                          "${PROJECT_BINARY_DIR}" 
                          ${EXTRA_INCLUDES})

# testing
enable_testing()
add_test(NAME Runs COMMAND ConvexHull)
