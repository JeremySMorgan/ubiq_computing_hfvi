cmake_minimum_required(VERSION 3.3)
project(hfvi)
set (CMAKE_CXX_STANDARD 11)

# Find librealsense2 installed package

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(realsense2 REQUIRED)
find_package( OpenCV REQUIRED )

#Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(LIBS glfw realsense2 ${OPENGL_LIBRARY} ${OpenCV_LIBS})


message("OPENGL_LIBRARY:\t" ${OPENGL_LIBRARY} )

#Add the application sources to the target
add_executable(${PROJECT_NAME} main.cpp)


# Link libraries to the target
target_link_libraries(${PROJECT_NAME} ${LIBS})
