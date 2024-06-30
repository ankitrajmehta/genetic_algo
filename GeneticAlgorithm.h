#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include "NeuralNetwork.h"
#include "individual.h"

class GeneticAlgorithm {
public:
    int populationSize;
    double mutationRate;
    NeuralNetwork& nn;
    std::vector<Individual> population;
    Individual best;
    int bestgen=0;
    int num_species = 1;

    GeneticAlgorithm(int populationSize, double mutationRate, NeuralNetwork& nn)
        : populationSize(populationSize), mutationRate(mutationRate), nn(nn) {
        initializePopulation();
    }

    void initializePopulation() {
        for (int i = 0; i < populationSize; ++i) {
            Individual ind;
            ind.weights = nn.getWeights();
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

    double fitnessFunction(Individual& ind,int show, int age, int gen) {
        nn.setWeights(ind.weights);
        // For Chasing food:
       // std::vector<double> inputs = {(double)ind.pos.x - (double) ind.food.x, (double)ind.pos.y - (double) ind.food.y, (double)(age/400.0) };

        //For Food box:
        // std::vector<double> inputs = {(double)ind.pos.x, (double) ind.food.x+5, (double)ind.pos.y, (double) ind.food.y+5, (double)(age/400.0) };

        //For moving right then left:
        std::vector<double> inputs = {(double)ind.pos.x, (double) ind.pos.y, (double)(age/400.0)};

        std::vector<double> outputs = nn.feedForward(inputs);
        
        // Get the position of the max value in outputs. No use now
        //int maxIndex = std::distance(outputs.begin(), std::max_element(outputs.begin(), outputs.end()));

        ind.move(outputs);
        double fitness = 0.0;

        // if (ind.pos.x == ind.food.x && ind.pos.y == ind.food.y){
        //     fitness += 1;
        //     int foodRange = 20;
        //     int min = 0;
        //     // if (age > 200)
        //     //     {min = 10;}
        //     int minX = std::max(min, ind.pos.x - foodRange);
        //     int maxX = std::min(MAP_X-1, ind.pos.x + foodRange);
        //     int minY = std::max(min, ind.pos.y - foodRange);
        //     int maxY = std::min(MAP_Y-1, ind.pos.y + foodRange);
        //     ind.food.x = random_int(minX, maxX);  // position of the food
        //     ind.food.y = random_int(minY, maxY);  // position of the food
        // }

        

        /*//SELECTION CRITERIA: Make a box of 10x10 from the food into which the individual should end up
        if (age%10 == 0)
            {if (ind.pos.x < ind.food.x || ind.pos.y < ind.food.y || ind.pos.x > ind.food.x + 10 || ind.pos.y > ind.food.y + 10)
                fitness-= 0;
            else
                {fitness += 1;}
            }

                
        if (age%30 == 0){
            int foodRange = 30;
            int min = 0;
            // if (age > 200)
            //     {min = 10;}
            int minX = std::max(min, ind.pos.x - foodRange);
            int maxX = std::min(MAP_X-foodRange+1, ind.pos.x + foodRange);
            int minY = std::max(min, ind.pos.y - foodRange);
            int maxY = std::min(MAP_Y-foodRange+1, ind.pos.y + foodRange);
            ind.food.x = random_int(minX, maxX);  // position of the food
            ind.food.y = random_int(minY, maxY);  // position of the food
        } */

       //SELECTION CRITERIA: Makes individual move towards right for 100 to 200 gens,then back to left for last 100 gen.
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


        return fitness; // Minimize error
    }

    // void evaluateFitness() {
    //     for (Individual& ind : population)
    //         ind.fitness += fitnessFunction(ind);
    // }

    Individual selectParent() {
        std::sort(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
            return a.fitness > b.fitness;
            });
        return population[0]; // Elitism: always select the best
    }



    void mutate(Individual& ind) {

        for (int& con : ind.active_connections){
            if ((((double)rand() / (RAND_MAX)) < mutationRate)){
                int new_con = random_int(0,nn.all_connections-1);
                //check if new connection is already present in connections of individual. if not, then replace current con with new con
                if (std::find(ind.active_connections.begin(), ind.active_connections.end(), new_con) == ind.active_connections.end()) 
                {
                    ind.weights[con] = 0;
                    con = new_con;
                    ind.weights[con] += ((double)rand() / (RAND_MAX)) * 2 - 1;}
                    ind.new_species = 10;
                }
            if (((double)rand() / (RAND_MAX)) < mutationRate){
                ind.weights[con] += ((double)rand() / (RAND_MAX)) * 2 - 1;}
        }
        ind.new_species--;

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

            for (Individual& ind : population){
                if (ind.dead == 0){
                    ind.fitness += fitnessFunction(ind,show, i,gen);
                    ind.fitness_history.push_back(ind.fitness);

                    if (show == 1)
                        show = 0;

                }
            }
        }


        std::vector<Individual> newPopulation;
        Individual parent = selectParent();
        parent.clean();
        newPopulation.push_back(parent);

        // for (Individual& ind : population) {
        //     if (ind.new_species>1){
        //         ind.clean();
        //         mutate(ind);
        //         newPopulation.push_back(ind);
        //         num_species++;
        //     }
        // }


        while (newPopulation.size() < populationSize) {
            Individual offspring = parent;
            offspring.clean();
            offspring.new_species = 0;
            mutate(offspring);
            newPopulation.push_back(offspring);
        }

 

        std::cout << "Generation " << gen << " Best Fitness: " << population[0].fitness << std::endl;
        std::cout << "With pos " << population[0].pos.x<< ", " << population[0].pos.y << ", direction: " << population[0].direction<< " num of species "<< num_species<<std::endl;

        if (population[0].fitness > best.fitness){
            best = population[0];
            bestgen = gen;
        }

        population = newPopulation;

    }
};

#endif 

