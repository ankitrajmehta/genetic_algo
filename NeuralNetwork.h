#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm> 

// Activation function
inline double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Derivative of the sigmoid function
inline double sigmoidDerivative(double x) {
    return x * (1.0 - x);
}

inline double relu(double x) {
    return x > 0 ? x : 0;
}   

inline double tanh(double x){
    return (2/(1+exp(-2*x)))-1;
}

const int NUM_OF_CON =9;

class NeuralNetwork {
public:
    int inputSize, hiddenSize, outputSize;
    std::vector<double> hiddenLayer, outputLayer;
    std::vector<std::vector<double>> weightsInputHidden, weightsHiddenOutput;
    int all_connections;

    std::vector<int> create_random_array() {
        std::vector<int> random_array;
        random_array.reserve(NUM_OF_CON); 
        int lower_limit = 0;
        int upper_limit = inputSize*hiddenSize + hiddenSize*outputSize;


        for (int i = 0; i < NUM_OF_CON; i++) {
            int random_number = lower_limit + (std::rand() % (upper_limit - lower_limit + 1));
            if (std::find(random_array.begin(), random_array.end(), random_number) == random_array.end()) 
            {
                random_array.push_back(random_number);
            }
            else {
                i--;
            }
        }

        return random_array;
    }

    NeuralNetwork(int inputSize, int hiddenSize, int outputSize)
        : inputSize(inputSize), hiddenSize(hiddenSize), outputSize(outputSize) {
        all_connections = inputSize*hiddenSize + hiddenSize*outputSize;
        hiddenLayer.resize(hiddenSize);
        outputLayer.resize(outputSize);
        weightsInputHidden.resize(inputSize, std::vector<double>(hiddenSize));
        weightsHiddenOutput.resize(hiddenSize, std::vector<double>(outputSize));
        // initializeWeights();
    }

    void initializeWeights() {
        for (int i = 0; i < inputSize; ++i)
            for (int j = 0; j < hiddenSize; ++j)
                weightsInputHidden[i][j] = 0*((double)rand() / (RAND_MAX)) * 2 - 1; 
        for (int i = 0; i < hiddenSize; ++i)
            for (int j = 0; j < outputSize; ++j)
                weightsHiddenOutput[i][j] = 0*((double)rand() / (RAND_MAX)) * 2 - 1;
    }

    std::vector<double> feedForward(const std::vector<double>& inputs) {
        //  if (inputs[4] > 0){
        // std::cout<<inputs[1]<<"  "<< inputs[3]<<std::endl;} // checking if inputs are correct
        // std::cout << "Length of inputs: " << inputs.size() << std::endl;}
        for (int i = 0; i < hiddenSize; ++i) {
            hiddenLayer[i] = 0.0;
            for (int j = 0; j < inputSize; ++j)
                hiddenLayer[i] += inputs[j] * weightsInputHidden[j][i];
            // hiddenLayer[i] = sigmoid(hiddenLayer[i]);
        
        }
        for (int i = 0; i < outputSize; ++i) {
            outputLayer[i] = 0.0;
            for (int j = 0; j < hiddenSize; ++j)
                outputLayer[i] += hiddenLayer[j] * weightsHiddenOutput[j][i];
             outputLayer[i] = tanh(outputLayer[i]);
        }
        return outputLayer;
    }

    std::vector<double> getWeights() const {
        std::vector<double> weights;
        for (const auto& row : weightsInputHidden)
            weights.insert(weights.end(), row.begin(), row.end());
        for (const auto& row : weightsHiddenOutput)
            weights.insert(weights.end(), row.begin(), row.end());
        return weights;
    }

    void setWeights(const std::vector<double>& weights) {
        int index = 0;
        for (int i = 0; i < inputSize; ++i)
            for (int j = 0; j < hiddenSize; ++j)
                weightsInputHidden[i][j] = weights[index++];
        for (int i = 0; i < hiddenSize; ++i)
            for (int j = 0; j < outputSize; ++j)
                weightsHiddenOutput[i][j] = weights[index++];
    }
};

#endif 


