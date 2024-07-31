#include "NeuralNetwork.h"
#include "GeneticAlgorithm.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>

int main(int argc, char* args[]) {
    srand(static_cast<unsigned>(time(0)));
    NeuralNetwork nn(5, 4, 2);
    int populationSize = 500;
    GeneticAlgorithm<foodchaser> ga(populationSize, 0.15, nn);
    
    int generations = 30;
    int step_per_gen = 400;

    SDL_Window* window=nullptr;
        SDL_Renderer* renderer=nullptr;
        
        SDL_CreateWindowAndRenderer(100*8, 100*8, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 8, 8);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
    for (int gen = 0; gen < generations; ++gen) {
        randomizeFoodPositions();
        ga.evolve(gen, step_per_gen);
       if(gen%20==0){Rend::draw(ga.population,renderer,gen);}
    
    }
    std::vector<foodchaser> best;
    for (int i = 0; i < 40; ++i) {
        best.push_back(ga.best);
    }
    Rend::draw(best,renderer,generations);



    std::cout<<"best fitness: "<<ga.best.fitness<< " Gen: "<< ga.bestgen << " Id: "<<ga.best.species_id<<std::endl;
    std::cout<<"Weights shape: " << ga.best.weights.size() << std::endl;
    for (int i = 0; i < ga.best.active_connections.size(); ++i) {
        std::cout << ga.best.active_connections[i] << " ";
    }   
    for (int i = 0; i < ga.best.weights.size(); ++i) {
        std::cout << ga.best.weights[i] << " ";
    }
    
    std::cout << "Movement History of Best: " <<ga.bestgen<< std::endl;

    for (int i = 0; i < ga.best.movement_history.size(); i+=20) {
        std::cout<<i<<". " << ga.best.movement_history[i].x<< " "<<ga.best.movement_history[i].y<<" Fitness: "<<ga.best.fitness_history[i]<<std::endl;
    }
    return 0;
}


