#include "NeuralNetwork.h"
#include "GeneticAlgorithm.h"

int main() {
    srand(static_cast<unsigned>(time(0)));
    NeuralNetwork nn(3, 4, 2);
    int populationSize = 250;
    GeneticAlgorithm ga(populationSize, 0.15, nn);
    int generations = 30;
    int step_per_gen = 400;
    for (int gen = 0; gen < generations; ++gen) {
        ga.evolve(gen, step_per_gen);
    }

    std::cout<<"best fitness: "<<ga.best.fitness<< " Gen: "<< ga.bestgen <<std::endl;
    std::cout << "Weights shape: " << ga.best.weights.size() << std::endl;
    for (int i = 0; i < ga.best.active_connections.size(); ++i) {
        std::cout << ga.best.active_connections[i] << " ";
    }   
    for (int i = 0; i < ga.best.weights.size(); ++i) {
        std::cout << ga.best.weights[i] << " ";
    }
    std::cout << "Movement History of Best: " << std::endl;

    for (int i = 0; i < ga.best.movement_history.size(); i+=20) {
        std::cout<<i<<". " << ga.best.movement_history[i].x<< " "<<ga.best.movement_history[i].y<<" Fitness: "<<ga.best.fitness_history[i]<<std::endl;
    }
    return 0;
}


