cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set proj name
project(ConvexHull)

# set up includes and libs
list(APPEND EXTRA_LIBS SDL2main SDL2)
list(APPEND EXTRA_INCLUDES "/usr/include/SDL2")

# add main executable
add_executable(ConvexHull main.cpp convexlib.cpp)
set_property(TARGET ConvexHull PROPERTY CXX_STANDARD 17)
target_link_libraries(ConvexHull PUBLIC ${EXTRA_LIBS})
target_include_directories(ConvexHull PUBLIC 
                          "${PROJECT_BINARY_DIR}" 
                          ${EXTRA_INCLUDES})

# add test executable
add_executable(Test1 test1.cpp convexlib.cpp)
set_property(TARGET Test1 PROPERTY CXX_STANDARD 17)
target_link_libraries(Test1 PUBLIC)
target_include_directories(Test1 PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )


# testing
enable_testing()
add_test(NAME Runs COMMAND Test1) 
