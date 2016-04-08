//
//  Board.h
//  GGBro
//
//  Created by Jay Byam And Jonathan Newell

#ifndef AI_h
#define AI_h

#include "NeuralNetwork.h"
#include "Board.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <thread>
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

struct Clock {
	high_resolution_clock::time_point start;
	double maxtime = 0.5;
};

class AI {
public:
	string AIType;
	NeuralNetwork brain;
	bool playAsRed = true;
	double kingVal;
	Clock thinker;
    int idx;

	// default ctor
	AI() {}

	// secondary ctor
	//	Takes a vector of ints representing the sctructure for the AI's NeuralNetwork
	AI(vector<int> layers) {
		brain = NeuralNetwork(layers);
		kingVal = 1.4;
		AIType = "Primordial";
		makeBrain();
	}

	// Secondary ctor
	//	Takes a NeralNetwork and applies it as the brain of this AI
	AI(NeuralNetwork brain_) {
		brain = brain_;
		kingVal = 1.4;
		AIType = "Created";
	}

	// Secondary ctor
	//	Takes a NeuralNetwork and applies it as the brain of this AI
	//	Also takes a struct of the piece values for the evolved value of the pieces
	AI(NeuralNetwork brain_, double kingValue_) {
		brain = brain_;
		kingVal = kingValue_;
		AIType = "Evolved";
	}

	// Make Brain
	//	constructs a random brain for this AI
	void makeBrain() {
		uniform_real_distribution<double> uniform(-1.0, 1.0);
		default_random_engine engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		// initialize layer's weights
		for (int i = 1; i < brain.structure.size(); ++i) {
			vector<vector<double>> layer(brain.structure[i]);
			for (int j = 0; j < layer.size(); ++j) {
				vector<double> weights(brain.structure[i - 1]);
				for (int k = 0; k < weights.size(); ++k) {
					weights[k] = uniform(engine);
				}
				layer[j] = weights;
			}
			// set layer's weights
			brain.setWeights(i, layer);
		}
	}

	// Evolve
	//	Evolve this AI to produce a child AI
	AI& evolve() {
		vector<vector<vector<double>>> genome = brain.getGenome();
		normal_distribution<double> normal(0.0, 0.4);
		default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		for (vector<vector<double>> & layer : genome) {
			for (vector<double> & neuron : layer) {
				for (double & weight : neuron) {
					weight += normal(generator);
				}
			}
		}
		AI childAI(NeuralNetwork(genome), kingVal + normal(generator));
		return childAI;
	}

	// Merge
	//	takes in a given AI and merges it with the current AI to form a new child AI
	AI& operator+(AI& other) {
		vector<vector<vector<double>>> momGenome = this->brain.getGenome();
		vector<vector<vector<double>>> dadGenome = other.brain.getGenome();
		// validation
		if (momGenome.size() != dadGenome.size()) throw std::invalid_argument("The two networks given have different structures and connot produce a child.");
		for (int i = 0; i < momGenome.size(); i++) {
			if (momGenome[i].size() != dadGenome[i].size()) throw std::invalid_argument("The two networks given have different structures and connot produce a child.");
		}
		// set random engines
		uniform_int_distribution<int> flipFlop(0, 1);
		default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		vector<vector<vector<double>>> child;
		// set layer 0 gene to child
		child.push_back(momGenome[0]);
		// start gene splicing
		for (int i = 1; i < momGenome.size(); ++i) {
			vector<vector<double>> gene(momGenome[i].size());
			// determin splice spot
			uniform_int_distribution<int> splice(0, momGenome[i].size() - 1);
			int spliceSpot = splice(generator);
			// decide dad splice or mom splice
			if (flipFlop(generator) == 1) {
				// do dad splice
				for (int j = 0; j < gene.size(); j++) {
					if (j < spliceSpot) {
						gene[j] = dadGenome[i][j];
					} else {
						gene[j] = momGenome[i][j];
					}
				}
			} else {
				// do mom splice
				for (int j = 0; j < gene.size(); j++) {
					if (j > spliceSpot) {
						gene[j] = dadGenome[i][j];
					} else {
						gene[j] = momGenome[i][j];
					}
				}
			}
			// add gene to child
			child.push_back(gene);
		}
		AI newAI(NeuralNetwork(child), kingVal);
		newAI.AIType = "Spliced";
		return newAI;
	}

	// Evaluate
	//	evaluates the given vector of Boards
	void evaluate(vector<Board>& boards, bool isAlpha) {
		int bSize = boards.size();
		for (int i = 0; i < bSize; i++) {
			evaluateBoard(boards[i], isAlpha);
		}
	}

	void evaluateBoard(Board& board, bool isAlpha) {
		if (playAsRed) {
			if (board.blackEliminated) {
				board.setRank(1, isAlpha);
				return;
			}
			if (board.redEliminated) {
				board.setRank(0, isAlpha);
				return;
			}
		} else {
			if (board.blackEliminated) {
				board.setRank(0, isAlpha);
				return;
			}
			if (board.redEliminated) {
				board.setRank(1, isAlpha);
				return;
			}
		}
		brain.setInput(board.state);
		board.setRank(brain.Activate()[0], isAlpha);
	}

	// Make Move
	//	Searches the given board and makes a move by returning the desired board
	Board makeMove(Board& currentBoard) {

		double blackVal = 1;
		double redVal = -1;
		if (playAsRed) {
			blackVal = -1;
			redVal = 1;
		}

		if (currentBoard.endState) {
			return{};
		}
		vector<vector<Board>> newBoards(20);
		for (vector<Board>& b : newBoards) {
			b.reserve(10);
		}
		currentBoard.generateLegalMoves(newBoards[0], redVal, blackVal, kingVal);
		int numPossibleMoves = newBoards[0].size();
		double greatestRank = 0;
		if (numPossibleMoves == 0) {
			if (currentBoard.redTurn) {
				currentBoard.redEliminated = true;
			} else {
				currentBoard.blackEliminated = true;
			}
			currentBoard.endState = true;
			return currentBoard;
		}
		for (int i = 0; i < numPossibleMoves; i++) {
			newBoards[0][i].parentBoard = nullptr;
		}
		int numberOfBoards = 0;
		int maxDepth = 4;
		thinker.start = high_resolution_clock::now();
		do {
			numberOfBoards = searchBoards(newBoards, true, 1, maxDepth);
			sort(newBoards[0].begin(), newBoards[0].end());
			++maxDepth;
		} while ((duration<double>(high_resolution_clock::now() - thinker.start).count() < thinker.maxtime) && maxDepth < 20);
		sort(newBoards[0].begin(), newBoards[0].end());
		return newBoards[0][0];
	}

	// Search Boards
	int searchBoards(vector<vector<Board>>& boards, bool isAlpha, int depthReached, int maxDepth) {
		int nBoards = boards[depthReached - 1].size();
		int n = nBoards;
		if (depthReached <= maxDepth) {
			for (int i = 0; (i < nBoards) && (duration<double>(high_resolution_clock::now() - thinker.start).count() < thinker.maxtime); i++) {
				if (duration<double>(high_resolution_clock::now() - thinker.start).count() < thinker.maxtime) {
					boards[depthReached - 1][i].generateLegalMoves(boards[depthReached]);
					//if (boards[depthReached].size() > 10) {
					//	cout << "Preallocate MORE THAN 10";
					//}
					if (duration<double>(high_resolution_clock::now() - thinker.start).count() < thinker.maxtime) {
						if (boards.size() > 0) {
							n += searchBoards(boards, !isAlpha, depthReached + 1, maxDepth);
						}
					}
				}
			}
		} else {
			evaluate(boards[depthReached], isAlpha);
		}
		return n;
	}
};

#endif // !AI
