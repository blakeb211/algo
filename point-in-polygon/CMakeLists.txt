cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set proj name
project(pip)

# set up includes and libs
list(APPEND EXTRA_LIBS SDL2main SDL2)
list(APPEND EXTRA_INCLUDES "/usr/include/SDL2")

# add main executable
add_executable(pip main.cpp piplib.cpp)
set_property(TARGET pip PROPERTY CXX_STANDARD 17)
target_link_libraries(pip PUBLIC ${EXTRA_LIBS})
target_include_directories(pip PUBLIC 
                          "${PROJECT_BINARY_DIR}" 
                          ${EXTRA_INCLUDES})

# add test executable
add_executable(testbed testbed.cpp piplib.cpp)
set_property(TARGET testbed PROPERTY CXX_STANDARD 17)
target_link_libraries(testbed PUBLIC)
target_include_directories(testbed PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )


# testing
enable_testing()
add_test(NAME Test1 COMMAND testbed -1) 
