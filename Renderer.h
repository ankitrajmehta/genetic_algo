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
#include <SDL2/SDL_image.h>

class Rend{
    public:
    
    static void draw(std::vector<rightleft>& population,SDL_Renderer* renderer,int gen){
        
         SDL_Surface* surface=nullptr;
        IMG_Init(IMG_INIT_PNG);
        SDL_Init(SDL_INIT_VIDEO);
        
        SDL_SetRenderDrawColor(renderer,0,255,255,255);
        //SDL_RenderClear(renderer);
        for(int step=0;step<400;step++){    
        SDL_SetRenderDrawColor(renderer,random_int(0,255),random_int(0,255),random_int(0,255),255);
        if(step>=0 && step<100){
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                
                SDL_RenderClear(renderer);
                
                surface=IMG_Load("C:/Users/VICTUS/Desktop/genetic_algo264864/asset/2nd.png");
                
                SDL_Texture* ourjpg=SDL_CreateTextureFromSurface(renderer,surface);
                
                SDL_RenderCopy(renderer,ourjpg,NULL,NULL);
                
                SDL_SetRenderDrawColor(renderer,random_int(0,255),random_int(0,255),random_int(0,255),255);
                }

                else if(step>=100 && step<200){
                    SDL_SetRenderDrawColor(renderer,0,0,0,255);
                    
                    SDL_RenderClear(renderer);
                    
                    surface=IMG_Load("C:/Users/VICTUS/Desktop/genetic_algo264864/asset/1st.png");
                    
                    SDL_Texture* ourjpg=SDL_CreateTextureFromSurface(renderer,surface);
                    
                    SDL_RenderCopy(renderer,ourjpg,NULL,NULL);
                    
                    SDL_SetRenderDrawColor(renderer,random_int(0,255),random_int(0,255),random_int(0,255),255);
                }
                else if(step>=200 && step<300){
                    SDL_SetRenderDrawColor(renderer,0,0,0,255);
                    
                    SDL_RenderClear(renderer);
                    
                    surface=IMG_Load("C:/Users/VICTUS/Desktop/genetic_algo264864/asset/2nd.png");
                    
                    SDL_Texture* ourjpg=SDL_CreateTextureFromSurface(renderer,surface);
                    
                    SDL_RenderCopy(renderer,ourjpg,NULL,NULL);
                    
                    SDL_SetRenderDrawColor(renderer,random_int(0,255),random_int(0,255),random_int(0,255),255);
                }
                else if(step>=300 && step<400){
                    SDL_SetRenderDrawColor(renderer,0,0,0,255);
                    
                    SDL_RenderClear(renderer);
                    
                    surface=IMG_Load("C:/Users/VICTUS/Desktop/genetic_algo264864/asset/3rd.png");
                    
                    SDL_Texture* ourjpg=SDL_CreateTextureFromSurface(renderer,surface);
                    
                    SDL_RenderCopy(renderer,ourjpg,NULL,NULL);
                    
                    SDL_SetRenderDrawColor(renderer,255,0,random_int(0,255),255);

                }

            for(int ind=0;ind<20;ind++){


                


                SDL_RenderDrawPoint(renderer,population[ind].movement_history[step].x,population[ind].movement_history[step].y);
                
                
               
                //std::cout<<"SP"<<step<<"turn"<<ind<<"x:"<<population[ind].movement_history[step].x<<"y:"<<population[ind].movement_history[step].y<<std::endl;
            }
            SDL_RenderPresent(renderer);
            //SDL_RenderPresent(renderer);
         SDL_Delay(50);
        }
        
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        
        SDL_RenderClear(renderer);
        
        }


    static void draw(std::vector<foodchaser>& population ,SDL_Renderer* renderer,int gen){
        int a = population[0].fitness_history[399];
        std::cout<<"Health"<<a<<std::endl;
        SDL_Surface* surface=nullptr;
        IMG_Init(IMG_INIT_PNG);
        SDL_Init(SDL_INIT_VIDEO);
        if(a<0){
            surface=IMG_Load("C:/Users/VICTUS/Desktop/genetic_algo264864/asset/neg.png");
        }
        else if(a>=0 && a<10){
            surface=IMG_Load("C:/Users/VICTUS/Desktop/genetic_algo264864/asset/0.png");

        }
        else if(a>=10 && a<20){
            surface=IMG_Load("C:/Users/VICTUS/Desktop/genetic_algo264864/asset/10.png");
            
        }else if(a>=20 && a<30){
            surface=IMG_Load("C:/Users/VICTUS/Desktop/genetic_algo264864/asset/20.png");
            
        }else if(a>=30 && a<40){
            surface=IMG_Load("C:/Users/VICTUS/Desktop/genetic_algo264864/asset/30.png");
            
        }
        else{
            surface=IMG_Load("C:/Users/VICTUS/Desktop/genetic_algo264864/asset/40.png");
        }
        
        
        SDL_Texture* ourjpg=SDL_CreateTextureFromSurface(renderer,surface);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,ourjpg,NULL,NULL);
        SDL_Rect rect;
       
        rect.w = 10;
        rect.h = 10;
    
        
        //SDL_SetRenderDrawColor(renderer,0,255,255,255);
        //SDL_SetRenderDrawColor(renderer,random_int(0,255),random_int(0,255),random_int(0,255),255);
        
            for(int step=0;step<400  ;step++){
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
                SDL_Delay(40);
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_RenderClear(renderer);
                // SDL_RenderCopy(renderer,ourjpg,NULL,NULL);
               
                //std::cout<<"SP"<<step<<"turn"<<ind<<"x:"<<population[ind].movement_history[step].x<<"y:"<<population[ind].movement_history[step].y<<std::endl;
            }
            //SDL_RenderPresent(renderer);
        
        
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        
    }


    
};
#endif
