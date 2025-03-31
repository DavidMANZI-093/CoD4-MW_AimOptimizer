cmake_minimum_required(VERSION 3.31.6)

project(AimOptimizer)

find_package(OpenCV REQUIRED)

# Include directories for headers
include_directories(${OpenCV_INCLUDE_DIRS} configs)

# Find all .cpp files inside tools/
file(GLOB TOOLS_SRC "tools/*.cpp")

# Create the executable with all source files
add_executable(AimOptimizer AimOptimizer.cpp ${TOOLS_SRC})

# Link against OpenCV and Direct3D11
target_link_libraries(AimOptimizer ${OpenCV_LIBS} d3d11)
