//g++ main.cpp -o main  -lsfml-graphics -lsfml-window -lsfml-system && ./main

#include <iostream>
#include <vector>
#include <string>
#include "./headers/Food.h"
#include "./headers/Snake.h"
#include "./headers/Bodypart.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using std::cout;
using std::vector;
using std::string;

class Food;
class Snake;

const int CELL_NUMBER = 24;
const int CELL_DIM = 20;
const int VEC_SIZE = 24;
const int WINDOW_SIZE = 480;


void game_loop(vector< vector<sf::RectangleShape> > grid){
    
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed the random number generator

    sf::RenderWindow window( sf::VideoMode( WINDOW_SIZE, WINDOW_SIZE ), "Snake Game" );    
    Snake snake(WINDOW_SIZE / 2, WINDOW_SIZE / 2);
    Food food_elem = snake.generate_food(snake);
    int movement = 1;
    vector<int> game_state;
    int games_played = 0;
        
    vector<int> snake_direction = {0, 1, 0, 0};

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)window.close();

            if(event.key.code == sf::Keyboard::Left ){
                snake_direction = {1,0,0,0};  
                movement = -1;
            }
            
            else if (event.key.code == sf::Keyboard::Right)   {
                snake_direction= {0,1,0,0};
                movement =  1;
            }
            
            else if (event.key.code == sf::Keyboard::Up   )   {
                snake_direction= {0,0,1,0};
                movement =  2;
            }
            
            else if (event.key.code == sf::Keyboard::Down ) {  
                snake_direction= {0,0,0,1};
                movement = -2;
            }
        }
        
        game_state = snake.calculate_game_state(food_elem);
        game_state.insert(game_state.end(), snake_direction.begin(), snake_direction.end());
    
        for(auto i : grid)
            for(auto j : i)
                window.draw(j);
        
        snake.check_food(food_elem);

        snake.move(movement);


        if(snake.check_death()){
            snake = Snake(WINDOW_SIZE / 2, WINDOW_SIZE / 2);
            food_elem = snake.generate_food(snake);
            games_played += 1;
            // break; 
        }

        snake.draw(window);
        window.draw(food_elem.food_piece);
        window.display();

        // print game state
        cout<<"snake direction = "<< snake.direction << " snake length = "<< snake.snake_body.size() <<'\n';
        for(int i = 0; i<game_state.size(); i++){
            cout<<game_state[i]<<" ";
            if((i + 1)%11 == 0 && i>0)
                cout<<"\n";
        }
        cout<<"\n";

        sf::sleep(sf::seconds(0.1));

    }

    cout<<"end of game, final score:"<< snake.snake_body.size();

}

int main(){

    sf::RectangleShape cell;
    cell.setSize( sf::Vector2f( 18, 18 ) );
    cell.setFillColor( sf::Color::Green );
    vector< vector<sf::RectangleShape> > grid(CELL_NUMBER, vector<sf::RectangleShape>(CELL_NUMBER));

    for(int i = 0; i<CELL_NUMBER; i++)
        for(int j = 0; j < CELL_NUMBER; j++){
            cell.setPosition(sf::Vector2f(i * CELL_DIM, j * CELL_DIM));
            grid[i][j] =  cell;
        }
    

    game_loop(grid);

    return 0;

}
































// #include <iostream>
// #include <boost/asio.hpp>

// using namespace boost::asio;
// using namespace boost::system;

// std::string x(){

//     io_service ioService;

//     ip::tcp::resolver resolver(ioService);
//     ip::tcp::resolver::query query("127.0.0.1", "8000");  // Replace with your API's IP and port

//     ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

//     ip::tcp::socket socket(ioService);
//     connect(socket, endpoint_iterator);

//     std::string request = "GET /api/get-number/ HTTP/1.1\r\n"
//                           "Host: 127.0.0.1:8000\r\n"  // Replace with your API's IP and port
//                           "Connection: close\r\n\r\n";

//     write(socket, buffer(request));

//     streambuf response;
//     read_until(socket, response, "\r\n\r\n");

//     std::string response_body = "";
//     if (response.size() > 4) {
            
//             std::istream response_stream(&response);
//             std::string header;
//             while (std::getline(response_stream, header) && header != "\r") {
//                 // Process headers if needed
//             }

//             std::stringstream ss;
//             ss << response_stream.rdbuf();
//             response_body = ss.str();

//     }
//     if(response_body.length() > 0)
//         std::cout << "Response body: " << response_body << " lne " << response_body.length() << std::endl;

//     ioService.run();

//     return response_body;

// }


// int main() {
    

//     std::string res = "";

//     while(true){
//         while(res.length() == 0){

//             res = x();

//         }
//         res = "";
//     }


//     return 0;
// }



