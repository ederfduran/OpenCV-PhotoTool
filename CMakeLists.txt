cmake_minimum_required (VERSION 3.11.3)
set(CMAKE_TOOLCHAIN_FILE "/Users/ederduran/Desktop/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake")

# set(CMAKE_CXX_STANDARD 17)
project(PhotoTool) 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -pthread")

# Requires OpenCV 
find_package(OpenCV REQUIRED)

# show a message with opencv version detected
message("OpenCV version : ${OpenCV_VERSION}")

#dd to our environment the headers and the directory of the specified library
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})

add_definitions(${OpenCV_DEFINITIONS})

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

# create executable
add_executable(${PROJECT_NAME} ${project_SRCS})

#link our libary
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})






