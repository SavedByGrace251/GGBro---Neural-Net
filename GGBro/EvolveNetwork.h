//
//  EvolveNetwork.h
//  GGBro
//
//  Created by Jay Byam on 2/13/16.
//

#ifndef EvolveNetwork_h
#define EvolveNetwork_h

#include "NeuralNetwork.h"
#include "DataSet.h"
#include "Individual.h"
#include <iostream>
using std::cout;
using std::endl;
#include <random>
using std::uniform_real_distribution;
using std::uniform_int_distribution;
using std::normal_distribution;
using std::default_random_engine;

class EvolveNetwork {
public:
    NeuralNetwork network;
    vector<Individual> population;
    int populationSize;
    int tournamentSelectionNumber;
    double crossoverRate;
    double mutationRate;
    int genomeLength;
    int generations;
    double bestIndividualFitness;
    DataSet data;
    int numberOfGenesToMutate;
    
    EvolveNetwork(NeuralNetwork network, DataSet data) {
        this->network = network;
        genomeLength = network.numberOfWeights;
        populationSize = 100;
        population = vector<Individual>(populationSize);
        tournamentSelectionNumber = 10;
        crossoverRate = .9;
        mutationRate = .9;
        generations = 10000;
        this->data = data;
        bestIndividualFitness = 0.;
        numberOfGenesToMutate = 3;
        
        createPopulation(populationSize);
    }
    
    void createPopulation(int populationSize) {
        for (auto & individual : population) {
            individual.genome = randomGenome();
            individual.fitness = evaluateFitness(individual.genome);
        }
    }
    
    vector<double> randomGenome() {
        vector<double> genome;
        for (int i = 0; i < genomeLength; ++i) {
            uniform_real_distribution<double> uniform(-1, 1);
            default_random_engine engine;
            genome.push_back(uniform(engine));
        }
        return genome;
    }
    
    double evaluateFitness(vector<double> testGenome) {
        network.setWeights(testGenome);
        // Calculate mean squared error
        double squaredError = 0.0;
        int numberOfOutputs = data.numberOfOutputs();
        vector<double> networkOutput(numberOfOutputs);
        double error = 0.0;
        for (int i = 0; i < data.inputs.size(); ++i) {
            network.setInput(data.inputs[i]);
            networkOutput = network.Activate();
            for (int j = 0; j < numberOfOutputs; ++j) {
                error = networkOutput[j] - data.expectedOutputs[i][j];
                squaredError += error * error;
            }
        }
        return -squaredError / data.inputs.size();
    }
    
    void printResults() {
        int bestIndividualIdx = 0;
        int count = 0;
        for (auto & individual : population) {
            if (individual.fitness > population[bestIndividualIdx].fitness) {
                bestIndividualIdx = count;
            }
            ++count;
        }
        network.setWeights(population[bestIndividualIdx].genome);
        vector<double> networkOutputs(data.numberOfOutputs());
        for (int i = 0; i < data.inputs.size(); ++i) {
            network.setInput(data.inputs[i]);
            networkOutputs = network.Activate();
            cout << endl << "Output: ";
            for (int j = 0; j < data.numberOfOutputs(); ++j) {
                cout << networkOutputs[j];
            }
            cout << endl << "Expected: ";
            for (int j = 0; j < data.numberOfOutputs(); ++j) {
                cout << data.expectedOutputs[i][j];
            }
        }
    }
    
    vector<double> tournamentSelection() {
        uniform_int_distribution<int> uniform(0, populationSize);
        default_random_engine engine;
        int bestCandidateIdx = uniform(engine);
        for (int i = 0; i < tournamentSelectionNumber; ++i) {
            int newCandidateIdx = uniform(engine);
            if (population[newCandidateIdx].fitness > population[bestCandidateIdx].fitness) {
                bestCandidateIdx = newCandidateIdx;
            }
        }
        return population[bestCandidateIdx].genome;
    }
    
    vector<double> mutate(vector<double> childGenome) {
        uniform_int_distribution<int> uniform(0, genomeLength);
        normal_distribution<double> normal(0, 1);
        default_random_engine engine;
        for (int i = 0; i < numberOfGenesToMutate; ++i) {
            childGenome[uniform(engine)] += normal(engine);
        }
        return childGenome;
    }
    
    vector<double> crossover(vector<double> mumGenome, vector<double> dadGenome) {
        uniform_real_distribution<double> uniform(0, 1);
        default_random_engine engine;
        vector<double> childGenome(genomeLength);
        int crossoverPoint1 = uniform(engine) * genomeLength;
        int crossoverPoint2 = (genomeLength - crossoverPoint1) * uniform(engine) + crossoverPoint1;
        for (int i = 0; i < genomeLength; ++i) {
            if (i < crossoverPoint1 || i > crossoverPoint2) {
                childGenome[i] = mumGenome[i];
            } else {
                childGenome[i] = dadGenome[i];
            }
        }
        return childGenome;
    }
    
    void runEvolution() {
        for (int i = 0; i < generations; ++i) {
            if (i % 100 == 0) {
                cout << "Generation: " << i << " Best Fitness: " << bestIndividualFitness << endl;
            }
            runEvolutionStep();
        }
        printResults();
    }
    
    
};

#endif /* EvolveNetwork_h */
