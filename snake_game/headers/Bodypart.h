#ifndef BODYPART_H
#define BODYPART_H

#include <SFML/Graphics.hpp>

class bodypart{

    public:

    sf::RectangleShape shape;
    bodypart(int x, int y);
    // bodypart(){}
    void move(int move, int direction);

};

#endif // SNAKE_H
