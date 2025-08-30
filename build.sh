#!/bin/bash
# build.sh

echo "Building Snake Game..."

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Navigate to build directory
cd build

# Configure with CMake
echo "Configuring project..."
cmake ..

# Check if configuration was successful
if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

# Build the project
echo "Compiling..."
cmake --build . --config Release

# Check if build was successful
if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo "Run the game with: ./SnakeGame"
else
    echo "Build failed!"
    exit 1
fi