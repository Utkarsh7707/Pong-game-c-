#!/bin/bash

# Compile the C++ code
g++ main.cpp -o my_program -lraylib -lm -lpthread -ldl -lrt -lX11

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful!"
    echo "Running the program..."
    ./my_program
else
    echo "Compilation failed!"
fi
