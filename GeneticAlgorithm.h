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

    GeneticAlgorithm(int populationSize, double mutationRate, NeuralNetwork& nn)
        : populationSize(populationSize), mutationRate(mutationRate), nn(nn) {
        initializePopulation();
    }

    void initializePopulation() {
        for (int i = 0; i < populationSize; ++i) {
            Individual ind;
            ind.weights = nn.getWeights();
            for (double& weight : ind.weights)
                weight = ((double)rand() / (RAND_MAX)) * 2 - 1;
            ind.fitness = 0.0;
            population.push_back(ind);
        }
    }

    double fitnessFunction(Individual& ind,int show, int age, int gen) {
        nn.setWeights(ind.weights);
        // Example: simple fitness function for XOR problem
        std::vector<double> inputs = {(double)ind.pos.x, (double) ind.food.x+5, (double)ind.pos.y,(double) ind.food.y+5, (double)(age/400.0) };
        std::vector<double> outputs = nn.feedForward(inputs);
        
        // Get the position of the max value in outputs
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

        

        /*  //SELECTION CRITERIA: Make a box of 10x10 from the food into which the individual should end up
        if (age%10 == 0)
            {if (ind.pos.x < ind.food.x || ind.pos.y < ind.food.y || ind.pos.x > ind.food.x + 10 || ind.pos.y > ind.food.y + 10)
                fitness-= 0;
            else
                {fitness += 1;}
            }

                
        if (age%20 == 0){
            int foodRange = 10;
            int min = 0;
            // if (age > 200)
            //     {min = 10;}
            int minX = std::max(min, ind.pos.x - foodRange);
            int maxX = std::min(MAP_X-21, ind.pos.x + foodRange);
            int minY = std::max(min, ind.pos.y - foodRange);
            int maxY = std::min(MAP_Y-21, ind.pos.y + foodRange);
            ind.food.x = random_int(minX, maxX);  // position of the food
            ind.food.y = random_int(minY, maxY);  // position of the food
        } */

        //SELECTION CRITERIA: Makes individual move towards right for first 20 gens, then first right then back to left for rest 80 gen.
        if (age>300 && gen>20){
            if(ind.pos.x <10){
                fitness+=1;
            }
            if (ind.pos.x>50){
                fitness-=1;
            }
        }

        else if(age> 100 && age < 200){
            if(ind.pos.x > 90){
                fitness+=1;
            }
            if (ind.pos.x < 50){
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
        for (double& weight : ind.weights) {
            if (((double)rand() / (RAND_MAX)) < mutationRate)
                weight += ((double)rand() / (RAND_MAX)) * 2 - 1;
        }
    }

    void evolve(int gen, int steps_per_gen) {
        int show = 1;
        for (int i = 0; i < steps_per_gen; ++i){
            // if (i%20 == 0){
            //     std::cout << "With pos " << population[0].pos.x<< ", " << population[0].pos.y<<" fit "<<population[0].fitness<<std::endl;
            // }   
            for (Individual& ind : population){
                if (ind.dead == 0){
                    ind.fitness += fitnessFunction(ind,show, i,gen);

                    if (show == 1)
                        show = 0;

                }
            }
        }
        std::vector<Individual> newPopulation;
        while (newPopulation.size() < populationSize) {
            Individual parent = selectParent();
            Individual offspring = parent;
            offspring.fitness = 0.0;
            offspring.pos = position(0*random_int(),0*random_int());
            offspring.direction = 0;
            mutate(offspring);
            newPopulation.push_back(offspring);
        }
        std::cout << "Generation " << gen << " Best Fitness: " << population[0].fitness << std::endl;
        std::cout << "With pos " << population[0].pos.x<< ", " << population[0].pos.y << ", direction: " << population[0].direction<< " food at "<< population[0].food.x<<", "<<population[0].food.y<<std::endl;
        if (population[0].fitness > best.fitness){
            best = population[0];
            bestgen = gen;
        }

        population = newPopulation;

    }
};

#endif 

