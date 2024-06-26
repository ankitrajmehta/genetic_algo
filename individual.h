#include <iostream>
#include "NeuralNetwork.h"

struct position{
    int x;
    int y;
    position(float x=0, float y=0){
        this->x = x;
        this->y = y;
    }
};

int random_int(int start=0, int end=100){
    
    std::random_device rd;
    std::mt19937 gen(rd());
    // Define the uniform integer distribution for numbers between start and end
    std::uniform_int_distribution<> dis(start, end);
    double random_number = dis(gen);
    return random_number;
}


int id = 0;

const int MAP_X = 100;
const int MAP_Y = 100;


class Individual{
    public:

        std::vector<double> weights;

        float fitness=0;
        unsigned short id;
        int dead = 0;
        
        position pos;
        position food;

        int direction = 0; // 0 = up-left, 1 = up, 2 = up-right, 3 = left, 4 = right, 5 = down-left, 6 = down, 7 = down-right

        Individual(){
            id++;
            pos = position(0,0);
            food = position(1,1);
        }

        void move(int next_direction){
            direction = next_direction;
            if (0 == dead){
                if (next_direction == 0){
                    if (pos.x > 0 && pos.y > 0) {
                        pos.x -= 1;
                        pos.y -= 1;
                    }
                }
                else if (next_direction == 1){
                    if (pos.y > 0) {
                        pos.y -= 1;
                    }
                }
                else if (next_direction == 2){
                    if (pos.x < MAP_X - 1 && pos.y > 0) {
                        pos.x += 1;
                        pos.y -= 1;
                    }
                }
                else if (next_direction == 3){
                    if (pos.x > 0) {
                        pos.x -= 1;
                    }
                }
                else if (next_direction == 4){
                    if (pos.x < MAP_X - 1) {
                        pos.x += 1;
                    }
                }
                else if (next_direction == 5){
                    if (pos.x > 0 && pos.y < MAP_Y - 1) {
                        pos.x -= 1;
                        pos.y += 1;
                    }
                }
                else if (next_direction == 6){
                    if (pos.y < MAP_Y - 1) {
                        pos.y += 1;
                    }
                }
                else if (next_direction == 7){
                    if (pos.x < MAP_X - 1 && pos.y < MAP_Y - 1) {
                        pos.x += 1;
                        pos.y += 1;
                    }
                }
                else if (next_direction == 8){
                    // No movement
                }
            }
        }

        
};