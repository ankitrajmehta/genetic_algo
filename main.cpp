#include "NeuralNetwork.h"
#include "GeneticAlgorithm.h"

int main() {
    srand(static_cast<unsigned>(time(0)));
    NeuralNetwork nn(2, 19, 8);
    int populationSize = 100;
    GeneticAlgorithm ga(populationSize, 0.5, nn);
    int generations = 30;
    int step_per_gen = 200;
    for (int gen = 0; gen < generations; ++gen) {
        ga.evolve(gen, step_per_gen);
    }
    std::cout<<"best fitness: "<<ga.best<< " Gen: "<< ga.bestgen <<std::endl;
    return 0;
}


