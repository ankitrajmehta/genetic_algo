#include "NeuralNetwork.h"
#include "GeneticAlgorithm.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
int main(int argc, char* args[]) {
    srand(static_cast<unsigned>(time(0)));
    NeuralNetwork nn(5, 4, 2);
    int populationSize = 500;
    GeneticAlgorithm ga(populationSize, 0.2, nn);
    
    int generations = 30;
    int step_per_gen = 400;
    // SDL_Window* window=nullptr;
    // SDL_Renderer* renderer=nullptr;
    // SDL_Init(SDL_INIT_VIDEO);
    // SDL_CreateWindowAndRenderer(100 * 4, 100 * 4, 0, &window, &renderer);
    // SDL_RenderSetScale(renderer, 4, 4);
    // SDL_SetRenderDrawColor(renderer,0,0,0,255);


    for (int gen = 0; gen < generations; ++gen) {
        randomizeFoodPositions();
        ga.evolve(gen, step_per_gen);

        // Rend kk(ga.population);

        // for(int ind=0;ind<1;ind+=30){ 
        //     SDL_SetRenderDrawColor(renderer,0,0,0,255);
        //     SDL_RenderClear(renderer);

        //     SDL_SetRenderDrawColor(renderer,255,255,255,255);
        //     for(int step=0;step<400 && gen>10;step++){
        //         SDL_RenderDrawPoint(renderer,ga.population[ind].movement_history[step].x,ga.population[ind].movement_history[step].y);
        //         if(step%1==0){SDL_RenderPresent(renderer);}
        //         std::cout<<"SP"<<step<<"turn"<<ind<<"x:"<<ga.population[ind].movement_history[step].x<<"y:"<<ga.population[ind].movement_history[step].y<<std::endl;
        //     }
    

        // }
        //SDL_Delay(500);
        
    
    }

    std::cout<<"best fitness: "<<ga.best.fitness<< " Gen: "<< ga.bestgen << " Id: "<<ga.best.species_id<<std::endl;
    std::cout<<"Weights shape: " << ga.best.weights.size() << std::endl;
    for (int i = 0; i < ga.best.active_connections.size(); ++i) {
        std::cout << ga.best.active_connections[i] << " ";
    }   
    for (int i = 0; i < ga.best.weights.size(); ++i) {
        std::cout << ga.best.weights[i] << " ";
    }
    std::cout << "Movement History of Best: " << std::endl;

    for (int i = 0; i < ga.best.movement_history.size(); i+=20) {
        std::cout<<i<<". " << ga.best.movement_history[i].x<< " "<<ga.best.movement_history[i].y<<" Fitness: "<<ga.best.fitness_history[i]<<"  Food "<<ga.best.food_history[i].x<<" "<<ga.best.food_history[i].y<<std::endl;
    }
    return 0;
}


