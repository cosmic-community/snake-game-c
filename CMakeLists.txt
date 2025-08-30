# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(sfml 2.6 REQUIRED COMPONENTS system window graphics audio)

# Add executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Game.cpp
    src/Snake.cpp
    src/Food.cpp
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} 
    sfml-system 
    sfml-window 
    sfml-graphics 
    sfml-audio
)

# Copy resources to build directory (if any)
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources 
#      DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Platform specific settings
if(WIN32)
    # Windows specific settings
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE TRUE)
endif()

if(UNIX AND NOT APPLE)
    # Linux specific settings
    target_link_libraries(${PROJECT_NAME} pthread)
endif()