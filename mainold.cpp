#include <iostream>
#include <random>


#include <ctime>


int num_ind = 1;

int inov_id = 0;

int layers = 3;

int num_connections = 6;
int input_neurons = 2;
int hidden_neurons_A = 3;
int output_neurons = 4;

int shape[] = {input_neurons, hidden_neurons_A, output_neurons};


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
    std::uniform_real_distribution<> dis(start, end);
    double random_number = dis(gen);
    return random_number;
}

class the_ai{
    public:
        std::vector<std::vector<std::vector<float>>> weights;

    the_ai(){
        for (int i = 0; i < layers-1; i++){
            std::vector<std::vector<float>> layer;
            for (int j = 0; j < shape[i]; j++){
                std::vector<float> neuron;
                for (int k = 0; k < shape[i+1]; k++){
                    neuron.push_back(random_float());
                }
                layer.push_back(neuron);
            }
            weights.push_back(layer);
        }
    }

};


class individual{
    public:
        the_ai brain;
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
    position food = position(50,50);

    std::vector<individual> individuals;

    // Create a vector of individuals
    for (int i = 0; i < num_ind; i++) {
        individuals.push_back(individual());
    }

    for (int i = 0; i < num_ind; i++) {
        std::cout << "Individual " << i << " has position: " << individuals[i].pos.x << ", " << individuals[i].pos.y << std::endl;
    }
    bool not_found = true;
    for (int i = 0; i < num_ind; i++) {
        while(not_found){
            if (individuals[i].pos.x == food.x && individuals[i].pos.y == food.y){
                std::cout << "Individual " << i << " has found the food!" << std::endl;
                not_found = false;
            }
            else if (individuals[i].pos.x < food.x && individuals[i].pos.y < food.y){
                individuals[i].move(7);
            }
            else if (individuals[i].pos.x == food.x && individuals[i].pos.y < food.y){
                individuals[i].move(6);
            }
            else if (individuals[i].pos.x > food.x && individuals[i].pos.y < food.y){
                individuals[i].move(5);
            }
            else if (individuals[i].pos.x < food.x && individuals[i].pos.y == food.y){
                individuals[i].move(4);
            }
            else if (individuals[i].pos.x > food.x && individuals[i].pos.y == food.y){
                individuals[i].move(3);
            }
            else if (individuals[i].pos.x < food.x && individuals[i].pos.y > food.y){
                individuals[i].move(2);
            }
            else if (individuals[i].pos.x == food.x && individuals[i].pos.y > food.y){
                individuals[i].move(1);
            }
            else if (individuals[i].pos.x > food.x && individuals[i].pos.y > food.y){
                individuals[i].move(0);
            }
        std::cout << "Individual " << i << " has position: " << individuals[i].pos.x << ", " << individuals[i].pos.y << std::endl;
        }
    }
    
    for (int h = 0; h < num_ind; h++) {
          // Print the value of weights of each connection
            for (int i = 0; i < layers-1; i++) {
                std::cout << "Layer " << i+1 << " weights:" << std::endl;
                for (int j = 0; j < shape[i]; j++) {
                    for (int k = 0; k < shape[i+1]; k++) {
                        std::cout << "Connection " << j+1 << " to " << k+1 << ": " << individuals[h].brain.weights[i][j][k] << std::endl;
                    }
                }
                std::cout << std::endl;
            }
       }

       srand(static_cast<unsigned>(time(0)));
        std::cout<< "Random number: " << ((double)rand() / (RAND_MAX)) * 2 - 1 << std::endl;
  

    return 0;
}