# Evolutionary Creatures Simulation with Genetic Algorithms

This project simulates the evolutionary development of virtual creatures using genetic algorithms. Creatures are spawned into an environment where they reproduce, mutate, and evolve over generations. Their neural network brains adapt, leading to new species emerging and competing with established species based on defined selection criteria.

## Project Overview

The simulation operates in two modes:
1. **Right-Left Mode**: Creatures must reach the rightmost side of the environment between ages 100-200 and the leftmost side between ages 300-400.  
2. **Food Chaser Mode**: Creatures must follow and consume a randomly moving food box.

### Neural Networks
Each creature is equipped with a neural network "brain" that evolves with each generation. The maximum size of the network is pre-defined, and as creatures mutate, their neural architecture evolves with a limited number of connections. When a significantly different architecture arises, the individual is classified as a new species and protected from immediate extinction. This species is given ample time to evolve and compete with others.

### Species Protection
Newly evolved species with novel neural network architectures are given protection to allow for development, ensuring that they can adapt and potentially compete with pre-established species.

---

## Files and Components

### `Main.cpp`
- The main file where the simulation is initialized.
- You can choose between the two modes by initializing the `GeneticAlgorithm` object:
  - `GeneticAlgorithm<rightleft>` for **Right-Left Mode**.
  - `GeneticAlgorithm<foodchaser>` for **Food Chaser Mode**.
- Parameters such as mutation rate, number of generations, population size, etc., can be modified here.

### `NeuralNetwork.h`
- Defines the neural networks of the creatures.
- Handles the updates of neural architectures over generations, accommodating varying architectures for each species.

### `GeneticAlgorithm.h`
- Implements the genetic algorithm.
- Contains the fitness evaluation functions (overloaded for each mode) and species protection mechanisms.
- Includes methods for selecting parents, applying mutations, and handling species evolution.

### `Individual.h`
- Defines each individual creature.
- Manages movement and tracks individual history for performance evaluation.

---


## Features to Explore

- **Modes**: Try switching between the two simulation modes to observe different behaviors and strategies evolved by creatures.
- **Species Evolution**: Observe how species protection and unique neural architectures lead to the emergence of distinct evolutionary paths.
- **Custom Settings**: Tune mutation rates, fitness criteria, and population dynamics to shape the evolutionary pressure and behaviors in the simulation.

---
