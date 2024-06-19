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
    int best=0;
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

    double fitnessFunction(Individual& ind) {
        nn.setWeights(ind.weights);
        // Example: simple fitness function for XOR problem
        std::vector<double> inputs = {(double)ind.pos.x - ind.food.x, (double)ind.pos.y - ind.food.y};
        std::vector<double> outputs = nn.feedForward(inputs);
        
        // Get the position of the max value in outputs
        int maxIndex = std::distance(outputs.begin(), std::max_element(outputs.begin(), outputs.end()));
        ind.move(maxIndex);

        double fitness = 0.0;
        if (ind.pos.x == ind.food.x && ind.pos.y == ind.food.y){
            fitness = 1;
            int foodRange = 10;
            int minX = std::max(0, ind.pos.x - foodRange);
            int maxX = std::min(MAP_X-1, ind.pos.x + foodRange);
            int minY = std::max(0, ind.pos.y - foodRange);
            int maxY = std::min(MAP_Y-1, ind.pos.y + foodRange);
            ind.food.x = random_int(minX, maxX);  // position of the food
            ind.food.y = random_int(minY, maxY);  // position of the food
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
        for (int i = 0; i < steps_per_gen; ++i){
            for (Individual& ind : population){
                if (ind.dead == 0){
                    ind.fitness += fitnessFunction(ind);
                }
            }
        }
        std::vector<Individual> newPopulation;
        while (newPopulation.size() < populationSize) {
            Individual parent = selectParent();
            Individual offspring = parent;
            offspring.fitness = 0.0;
            offspring.pos = position(random_int(),random_int());
            mutate(offspring);
            newPopulation.push_back(offspring);
        }
        std::cout << "Generation " << gen << " Best Fitness: " << population[0].fitness << std::endl;
        std::cout << "With pos " << population[0].pos.x<< ", " << population[0].pos.y << ", direction: " << population[0].direction<< " food at "<< population[0].food.x<<", "<<population[0].food.y<<std::endl;
        if (population[0].fitness > best){
            best = population[0].fitness;
            bestgen = gen;
        }


        population = newPopulation;

    }
};

#endif 

