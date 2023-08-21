#include "Food.h"



Food::Food(int x, int y) {
    food_piece.setSize(sf::Vector2f(18, 18));
    food_piece.setFillColor(sf::Color::Black);
    food_piece.setPosition(sf::Vector2f(x, y));
}



