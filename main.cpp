#include <iostream>
#include <random>

int inov_id = 0;

int num_connections = 6;
int input_neurons = 2;
int hidden_neurons_A = 2;
int output_neurons = 4;


struct position{
    int x;
    int y;
    position(float x=0, float y=0){
        this->x = x;
        this->y = y;
    }
};

float random_float(int start=0, int end=1){
    
    std::random_device rd;
    std::mt19937 gen(rd());
    // Define the uniform integer distribution for numbers between start and end
    std::uniform_int_distribution<> dis(start, end);
    double random_number = dis(gen);
    return random_number;
}




class individual{
    public:
        float fitness;
        unsigned short id;
        int dead = 0;
        
        position pos;

        int direction = 0; // 0 = up-left, 1 = up, 2 = up-right, 3 = left, 4 = right, 5 = down-left, 6 = down, 7 = down-right

        individual(){
            id = inov_id++;
            create();
        }

        void create(){
            fitness = 0;
            dead = 0;
            pos = position(random_float(0,100), random_float(0,100));
        }

        void move(int next_direction){
            direction = next_direction;
            if (0==dead){
                if (next_direction == 0){
                    pos.x -= 1;
                    pos.y -= 1;
                }
                else if (next_direction == 1){
                    pos.y -= 1;
                }
                else if (next_direction == 2){
                    pos.x += 1;
                    pos.y -= 1;
                }
                else if (next_direction == 3){
                    pos.x -= 1;
                }
                else if (next_direction == 4){
                    pos.x += 1;
                }
                else if (next_direction == 5){
                    pos.x -= 1;
                    pos.y += 1;
                }
                else if (next_direction == 6){
                    pos.y += 1;
                }
                else if (next_direction == 7){
                    pos.x += 1;
                    pos.y += 1;
                }
            }
        }
};

int main(){
    

    return 0;
}