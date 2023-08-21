cmake_minimum_required(VERSION 3.10)

project(SnakeGame)

# Add the executable
add_executable(SnakeGame main.cpp ./headers/Food.cpp ./headers/Snake.cpp ./headers/Bodypart.cpp)

# Link libraries (if needed)
target_link_libraries(SnakeGame sfml-graphics sfml-window sfml-system)
