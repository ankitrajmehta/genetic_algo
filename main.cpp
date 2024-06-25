#include "NeuralNetwork.h"
#include "GeneticAlgorithm.h"

int main() {
    srand(static_cast<unsigned>(time(0)));
    NeuralNetwork nn(5, 8, 2);
    int populationSize = 100;
    GeneticAlgorithm ga(populationSize, 0.1, nn);
    int generations = 100;
    int step_per_gen = 400;
    for (int gen = 0; gen < generations; ++gen) {
        ga.evolve(gen, step_per_gen);
    }

    std::cout<<"best fitness: "<<ga.best.fitness<< " Gen: "<< ga.bestgen <<std::endl;
    return 0;
}


