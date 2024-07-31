#ifndef RENDERER_H
#define RENDERER_H
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include "GeneticAlgorithm.h"
#include "NeuralNetwork.h"
#include "individual.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

template <typename T>
class Rend{
    public:
    std::vector<T>& population;
    
    Rend(std::vector<T>& pop):population(pop){};
    void draw(SDL_Renderer* renderer,int gen){
        SDL_SetRenderDrawColor(renderer,0,255,255,255);
        //SDL_RenderClear(renderer);
        for(int ind=0;ind<100 && gen%5==0;ind+=10){    
        SDL_SetRenderDrawColor(renderer,random_int(0,255),random_int(0,255),random_int(0,255),255);
        
            for(int step=0;step<400;step++){
                SDL_RenderDrawPoint(renderer,population[ind].movement_history[step].x,population[ind].movement_history[step].y);
                if(step%20==0){SDL_RenderPresent(renderer); SDL_Delay(100);}
               
                //std::cout<<"SP"<<step<<"turn"<<ind<<"x:"<<population[ind].movement_history[step].x<<"y:"<<population[ind].movement_history[step].y<<std::endl;
            }
            //SDL_RenderPresent(renderer);
        
        }
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        }
    void draw2(SDL_Renderer* renderer,int gen){
        SDL_Rect rect;
       
        rect.w = 10;
        rect.h = 10;
    
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        //SDL_SetRenderDrawColor(renderer,0,255,255,255);
        //SDL_SetRenderDrawColor(renderer,random_int(0,255),random_int(0,255),random_int(0,255),255);
        
            for(int step=0;step<400 && gen>=6 && gen%10==0;step++){
                //SDL_RenderDrawPoint(renderer,population[0].movement_history[step].x,population[0].movement_history[step].y);
                rect.x = population[0].food_history[step].x;
                rect.y = population[0].food_history[step].y;
                SDL_SetRenderDrawColor(renderer,150,0,0,50);
                SDL_RenderFillRect(renderer,&rect);
                SDL_SetRenderDrawColor(renderer,0,255,255,255);
                for(int ind=0;ind<20;ind++){
                    SDL_RenderDrawPoint(renderer,population[ind].movement_history[step].x,population[ind].movement_history[step].y);
                }
                //SDL_RenderDrawPoint(renderer,population[0].movement_history[step].x,population[0].movement_history[step].y);
                SDL_RenderPresent(renderer);
                SDL_Delay(50);
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_RenderClear(renderer);
               
                //std::cout<<"SP"<<step<<"turn"<<ind<<"x:"<<population[ind].movement_history[step].x<<"y:"<<population[ind].movement_history[step].y<<std::endl;
            }
            //SDL_RenderPresent(renderer);
        
        
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        
    }


    
};
#endif
