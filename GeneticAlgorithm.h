#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include "NeuralNetwork.h"
#include "individual.h"
#include "Renderer.h"

template <typename T>
class GeneticAlgorithm {
public:
    int populationSize;
    double mutationRate;
    NeuralNetwork& nn;
    std::vector<T> population;
    T best;
    int bestgen=0;
    int num_species = 1;
    int species_id = 1;

    GeneticAlgorithm(int populationSize, double mutationRate, NeuralNetwork& nn)
        : populationSize(populationSize), mutationRate(mutationRate), nn(nn) {
        initializePopulation();
    }

    void initializePopulation() {
        std::vector<int> active_connections = nn.create_random_array();
        for (int i = 0; i < populationSize; ++i) {
            T ind;
            ind.weights = nn.getWeights();
            ind.active_connections = active_connections;
            for (double& weight : ind.weights){
                weight = 0;
            }
            for (int& con : ind.active_connections){
                ind.weights[con] = ((double)rand() / (RAND_MAX)) * 2 - 1;
            }
            population.push_back(ind);
        }
        best.fitness = -1000; // setting a lower limit for comparison
    }

    
    double fitnessFunction(foodchaser& ind, int show, int age, int gen){ 
        nn.setWeights(ind.weights);

        //For Food box:
        std::vector<double> inputs = {(double)ind.pos.x- (double) ind.food.x+4.5, (double)ind.pos.y- (double) ind.food.y+4.5, (double)(age/400.0),1.0f};
        std::vector<double> outputs = nn.feedForward(inputs);
        ind.move(outputs);
        double fitness = 0.0;

            if (age%50 == 0){
                {if (ind.pos.x < ind.food.x || ind.pos.y < ind.food.y || ind.pos.x > ind.food.x + 10 || ind.pos.y > ind.food.y + 10)
                    fitness-= 5;
                else
                    {fitness += 5;}
                }
            }

        

            ind.food.x = food_array[age/100].x;
            ind.food.y = food_array[age/100].y;

        return fitness; // Minimize error

    }

    
    double fitnessFunction(rightleft& ind, int show, int age, int gen){ 
        nn.setWeights(ind.weights);
        //For moving right then left:
        std::vector<double> inputs = {(double)ind.pos.x, (double) ind.pos.y, (double)(age/400.0), (double)1};
         std::vector<double> outputs = nn.feedForward(inputs);
        ind.move(outputs);
        double fitness = 0.0;

        if (age>300){
            if(ind.pos.x <10){
                fitness+=1;
            }
            if (ind.pos.x>49){
                fitness-=1;
            }
        }

        else if(age> 100 && age < 200){
            if(ind.pos.x > 90){
                fitness+=1;
            }
            if (ind.pos.x < 49){
                fitness-=1;
            }
        }

        if (ind.pos.y<10 || ind.pos.y>90 ){
            fitness-=1;
        }

        return fitness; // Minimize error

    }


    T selectParent() {

        std::sort(population.begin(), population.end(), [](const T& a, const T& b) {
            if (a.fitness == b.fitness) {
                return a.species_id < b.species_id;
            }
            return a.fitness > b.fitness;
        });

        return population[0]; // Elitism: always select the best
    }



    void mutate(T& ind) {
        bool mutated = false;
        ind.new_species--;
        for (int& con : ind.active_connections){
            if ((((double)rand() / (RAND_MAX)) < mutationRate) && ind.new_species < 1){
                int new_con = random_int(0,nn.all_connections-1);
                //check if new connection is already present in connections of individual. if not, then replace current con with new con
                if (std::find(ind.active_connections.begin(), ind.active_connections.end(), new_con) == ind.active_connections.end()) 
                {
                    ind.weights[con] = 0;
                    con = new_con;
                    ind.weights[con] += ((double)rand() / (RAND_MAX)) * 2 - 1;
                    ind.new_species = 5;
                    mutated = true;
                }
            }
            if (((double)rand() / (RAND_MAX)) < mutationRate){
                ind.weights[con] += ((double)rand() / (RAND_MAX)) * 2 - 1;}
        }

        if (mutated){
            species_id++;
            ind.species_id = species_id;
        }


        std::sort(ind.active_connections.begin(), ind.active_connections.end());

        // for (double& weight : ind.weights) {
        //     if (((double)rand() / (RAND_MAX)) < mutationRate)
        //         weight += ((double)rand() / (RAND_MAX)) * 2 - 1;
        // }
    }

    void evolve(int gen, int steps_per_gen) {

        num_species = 1;

        int show = 1;
        for (int i = 0; i < steps_per_gen; ++i){

            for (T& ind : population){
                if (ind.dead == 0){
                    ind.fitness += fitnessFunction(ind,show, i,gen);
                    ind.fitness_history.push_back(ind.fitness);

                    if (show == 1)
                        show = 0;
                    else
                        show = 1;

                }

            }
        }


        std::vector<T> newPopulation;
        T parent = selectParent();
        
        // Individual best_of_gen = best;
        // best_of_gen.clean();
        // newPopulation.push_back(best_of_gen);

        
        // while (newPopulation.size() < populationSize/10) {
        //     Individual offspring = parent;
        //     offspring.clean();
        //     offspring.new_species = 0;
        //     mutate(offspring);
        //     newPopulation.push_back(offspring);
        // }


        // To conserve the best parent of the generation
        T conserve_parent = parent;
        conserve_parent.clean();
        conserve_parent.new_species = 0;
        newPopulation.push_back(conserve_parent);

        for (T& ind : population) {
            if (ind.new_species>1 && newPopulation.size() < populationSize*0.9){
                num_species++;
                T old = ind;
                old.clean();
                mutate(old);
                newPopulation.push_back(old);
            }

            if (ind.fitness > best.fitness){
                best = ind;
                bestgen = gen;
            }
        }


        while (newPopulation.size() < populationSize) {
            T offspring = parent;
            offspring.clean();
            offspring.new_species = 0;
            mutate(offspring);
            newPopulation.push_back(offspring);
        }

 

        std::cout << "Generation " << gen << "\n Best Fitness: " << population[0].fitness << std::endl;
        std::cout << "With pos " << population[0].pos.x<< ", " << population[0].pos.y << ", direction: " << population[0].direction<< " num of species "<< num_species<< " Id:"<< population[0].species_id<<" Created age: "<<population[0].new_species <<std::endl;
   

        population = newPopulation;

    }
};

#endif 

