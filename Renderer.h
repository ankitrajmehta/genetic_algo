#ifndef RENDERER_H
#define RENDERER_H
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
// #include "GeneticAlgorithm.h"
// #include "NeuralNetwork.h"
// #include "individual.h"
#include <SDL2/SDL.h>
class Rend{
    public:
    std::vector<Individual> population;
    Rend(std::vector<Individual> pop):population{pop}{};

    
    void draw(){
        //std::cout<<population[0].movement_history[0].x<<std::endl;
        SDL_Window* window=nullptr;
        SDL_Renderer* renderer=nullptr;
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(100,100,0,&window,&renderer);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        for(int ind=0;ind<400;ind++){
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            for(int step=0;step<500;step++ ){
                SDL_RenderDrawPoint(renderer,population[step].movement_history[ind].x,population[step].movement_history[ind].y);
                SDL_RenderPresent(renderer);
            }
            SDL_RenderClear(renderer);
        }


    }
};
#endif