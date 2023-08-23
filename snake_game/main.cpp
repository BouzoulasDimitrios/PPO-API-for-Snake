#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <string>
#include "./headers/Food.h"
#include "./headers/Snake.h"
#include "./headers/Bodypart.h"
#include "./headers/json.hpp"
#include <boost/system/error_code.hpp>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
boost::system::error_code error;

using namespace boost::asio;
using namespace boost::system;
using std::cout;
using std::vector;
using std::string;
using nlohmann::json;

class Food;
class Snake;

const int CELL_NUMBER = 24;
const int CELL_DIM = 20;
const int VEC_SIZE = 24;
const int WINDOW_SIZE = 480;
const string host = "127.0.0.1"; // Replace with your API's IP
const string port = "8000";      // Replace with the port
const string path = "/api/get-number/";


std::string synchronousHttpGetWithJsonBody(const std::string& jsonBody) {
    std::string requestBody = jsonBody;

    std::string request = "GET " + path + " HTTP/1.1\r\n"
                          "Host: " + host + "\r\n"
                          "Connection: close\r\n"
                          "Content-Type: application/json\r\n"
                          "Content-Length: " + std::to_string(requestBody.size()) + "\r\n"
                          "\r\n" + requestBody;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return "";
    }

    struct addrinfo hints, *result;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        return "";
    }

    if (connect(sockfd, result->ai_addr, result->ai_addrlen) == -1) {
        std::cerr << "Error connecting to host" << std::endl;
        freeaddrinfo(result);
        close(sockfd);
        return "";
    }

    freeaddrinfo(result);

    if (send(sockfd, request.c_str(), request.size(), 0) == -1) {
        std::cerr << "Error sending request" << std::endl;
        close(sockfd);
        return "";
    }

    char buffer[1024];
    std::string response;

    while (true) {
        int bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            break;
        }
        response.append(buffer, bytes_received);
    }

    close(sockfd);
    return response;
}


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
        
        string request_body = json(game_state).dump();

        std::string response = synchronousHttpGetWithJsonBody(request_body);
        std::cout << "Response:\n" << response << std::endl;        
        snake.draw(window);
         
        window.draw(food_elem.food_piece);
        window.display();

        // print game state
        cout<<"snake direction = "<< snake.direction << " snake length = "<< snake.snake_body.size() <<'\n';
        for(int i = 0; i<game_state.size(); i++){
            cout<<game_state[i]<<" ";
            if((i + 1)%11 == 0 && i>0) cout<<"\n";
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

}


