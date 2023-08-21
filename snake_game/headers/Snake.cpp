#include "./Snake.h"
#include "./Bodypart.h"
#include <iostream>
#include <algorithm>

const int CELL_NUMBER = 24;
const int CELL_DIM = 20;
const int GAME_BOUNDATRY = CELL_DIM * CELL_NUMBER - 1;

Snake::Snake(int x, int y)
{
    snake_body.push_back(bodypart(x, y));
}



void Snake::move(int movement){

    int x_movement = 0;
    int y_movement = 0;
    
    bodypart head = snake_body[snake_body.size() - 1];

    if(grow == false) snake_body.erase(snake_body.begin());
    else grow = false;

    if(movement == -direction ) movement = direction;    

    if(movement == -1)
        x_movement = -20;
    else if(movement == 1)
        x_movement = 20;
    else if(movement == -2)
        y_movement = 20;
    else if(movement == 2)
        y_movement = -20;
    
    sf::Vector2f coordinates = head.shape.getPosition();
    
    snake_body.push_back(bodypart((coordinates.x + x_movement), (coordinates.y + y_movement)));

    direction = movement;

    return;
}




void Snake::check_food(Food & fd){
    
        if(fd.food_piece.getPosition() == snake_body[snake_body.size() - 1].shape.getPosition()){
            grow = true;
            fd = generate_food(*this);
        }

    return;
}


bool Snake::check_death(){

    bodypart head = snake_body[snake_body.size()-1];

    int head_x = head.shape.getPosition().x;
    int head_y = head.shape.getPosition().y;

    if( (head_x > GAME_BOUNDATRY || head_x < 0 ) || ( head_y > GAME_BOUNDATRY || head_y < 0 ) ) return true;

    for(int i = 0; i < snake_body.size()-1; i++)
        if(head.shape.getPosition() == snake_body[i].shape.getPosition()) 
            return true; 

    return false;
}


void Snake::draw(sf::RenderWindow & window){
    for(int i =0; i<snake_body.size(); i++){ window.draw(snake_body[i].shape);}
}


std::vector<int> Snake::calculate_game_state(Food food_item){

    // std::cout<<"1";
    int head_x = snake_body[snake_body.size() - 1].shape.getPosition().x;
    int head_y = snake_body[snake_body.size() - 1].shape.getPosition().y;
    sf::Vector2f head_pos = snake_body[snake_body.size() - 1].shape.getPosition();
    sf::Vector2f food_pos = food_item.food_piece.getPosition();
    std::vector<int> game_state{};
    std::vector<sf::Vector2f> body_positions{};
    
    for(int i = 0; i<snake_body.size(); i++){
        body_positions.push_back(snake_body[i].shape.getPosition());
    }

    for(int xs = head_x -5*20; xs <= head_x + 5*20; xs+=20){
        for(int ys = head_y -5*20; ys <= head_y + 5*20; ys+=20){
            
            // std::cout<<"x = " << xs << " y = " << ys; 
            
            //CHECK IF OUT OF BOUNDS
            if((xs < 0 || xs > 480) || (ys < 0 || ys > 480)){
                // std::cout<<" is out of bounds\n"; 
                game_state.push_back(-1);
                continue;
            }

            //CHECK IF A BODY PART IS IN THE FRAME
            if(std::find(body_positions.begin(), body_positions.end(), sf::Vector2f(xs, ys)) != body_positions.end()) {
                // std::cout<<" is a bodypart\n"; 
                game_state.push_back(-1);
                continue;
            } 

            if(food_pos == sf::Vector2f(xs, ys)){
                // std::cout<<" is food\n"; 
                game_state.push_back(1);
                continue;
            }
            
            // std::cout<<" is empty\n"; 
            game_state.push_back(0);

        }   

    }

    return game_state;

}



Food Snake::generate_food(Snake snake){

    std::vector<int> x_pos, y_pos;
    int x,y;
    
    for(bodypart pos : snake.snake_body){
        x_pos.push_back(pos.shape.getPosition().x);
        y_pos.push_back(pos.shape.getPosition().y);
    }

    bool bodypart_found = false;

    while(!bodypart_found){
        
        std::cout<<"started making food\n";
    
        bodypart_found = true;

        x = (rand() % 24) * 20;  
        y = (rand() % 24) * 20;

        for(auto i : x_pos){ 
            for(auto j : y_pos){ 
                if(y == j && x == i) bodypart_found = false; }
        }

        std::cout<<"x = "<< x << " y = "<< y<<"\n";

        std::cout<<"STOPPED making food\n";

    }

    Food new_food(x, y);

    return new_food;
}




