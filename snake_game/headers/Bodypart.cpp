#include "./Bodypart.h"


bodypart::bodypart(int x, int y){
        
    shape.setSize( sf::Vector2f( 18, 18 ) );
    shape.setFillColor( sf::Color::Black );
    shape.setPosition(sf::Vector2f(x, y));

}


void bodypart::move(int move, int direction){

        int x_movement = 0;
        int y_movement = 0;
        
        if(move = -direction )
            move = direction;    

        if(move == -1)
            x_movement = -20;
        else if(move == 1)
            x_movement = 20;
        else if(move == -2)
            y_movement = 20;
        else if(move == 2)
            y_movement = -20;
        
        shape.move(sf::Vector2f(x_movement, y_movement));

}
