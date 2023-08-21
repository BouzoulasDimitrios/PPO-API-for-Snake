#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "./Food.h"

class bodypart;

class Snake {
    
    public:
        
        int snake_length = 0;
        int direction = 1;
        bool grow = false;

        std::vector<bodypart> snake_body;

        Snake(int x, int y);
        void move(int movement);
        void check_food(Food& food);
        bool check_death();
        void draw(sf::RenderWindow& window);
        Food generate_food(Snake snake);
        std::vector<int> calculate_game_state(Food food_item);
};

#endif // SNAKE_H
