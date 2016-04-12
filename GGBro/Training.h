//
//  Training.h
//  GGBro
//
//  Created by Jay Byam And Jonathan Newell

#ifndef Training_h
#define Training_h

#include "Tournament.h"
#include <fstream>
#include <string>
using namespace std;

class Training {
public:
	vector<AI> population;
	Clock trainTimer;
	int generation = 1;
	string saveLocation;
	int saveInterval = 50;

	//default ctor
	Training() {
		int minute = 60;
		int hour = 60 * minute;
		int day = 24 * hour;
		int week = 7 * day;
		trainTimer.maxtime = 3 * day + 23 * hour + 45 * minute;
	}

	Training(int populationSize) {
		int minute = 60;
		int hour = 60 * minute;
		int day = 24 * hour;
		int week = 7 * day;
		trainTimer.maxtime = 5 * minute;
		setupTraining(populationSize);
	}

	// Setup Training
	//	Setup training
	void setupTraining(int populationSize) {
		population = vector<AI>(populationSize);
	}

	void setMaxTime(int week, int day, int hour, int minute, int seconds) {
		int minutes = 60 * minute;
		int hours = 3600 * hour;
		int days = 86400 * day;
		int weeks = 604800 * week;
		trainTimer.maxtime = weeks + days + hours + minutes + seconds;
	}

	// Train
	//	Commence training
	void train() {
		// validate training can begin
		if (population.size() < 2) {
			throw std::logic_error("The population size is not sufficient to start training.");
		}
		// start training
		trainTimer.start = high_resolution_clock::now();
		while (duration<double>(high_resolution_clock::now() - trainTimer.start).count() < trainTimer.maxtime) {
			if (generation % saveInterval == 0) {
				save();
			}
			Tournament tourney(population);
			tourney.commence();
			ratePopulation(tourney);
			evolve();
			++generation;
		}
	}

	// Rate Population
	//	rates the current population based on the given tournament
	void ratePopulation(Tournament& t) {
		int popSize = population.size();
		for (int i = 0; i < popSize; i++) {
			population[i].score = t.scores[i];
		}
	}

	// Evolve
	//	culls the lower half of the population based on score
	//	and fills the population with new AI
	void evolve() {
		sort(population.begin(), population.end());
		reverse(population.begin(), population.end());
		int halfIdx = population.size() / 2;
		// decide number of AI to splice and evolve
		int nSplice = halfIdx * 0.3;
		int nEvolve = halfIdx - nSplice;

		uniform_int_distribution<int> randomIdx(0, halfIdx - 1);
		default_random_engine generator(high_resolution_clock::now().time_since_epoch().count());
		vector<AI> newAI;
		// splice networks
		for (int i = 0; i < nSplice; i++) {
			// select mum and dad netorks to splice
			int mumIdx = randomIdx(generator);
			int dadIdx = randomIdx(generator);
			while (mumIdx == dadIdx) dadIdx = randomIdx(generator);
			// splice networks
			newAI.push_back(population[mumIdx] + population[dadIdx]);
		}
		// evolve networks
		for (int i = 0; i < nEvolve; i++) {
			newAI.push_back(population[i].evolve());
		}

		population.resize(halfIdx);
		population.insert(population.end(), newAI.begin(), newAI.end());

	}

	// Load from file
	//	loads the last saved generation
	void resume() {
		int populationSize;
		ifstream saveFile("lastSave.data");
		saveFile >> generation >> populationSize;
		ifstream AIFile("generation_" + to_string(generation) + ".data");
		for (int i = 0; i < populationSize; ++i) {
			AI inputAI;
			AIFile >> inputAI;
			population.push_back(inputAI);
		}
	}

	// Save to file
	//	Saves the current generation to file
	void save() {
		ofstream AIFile("generation_" + to_string(generation) + ".data");
		for (AI& ai : population) {
			AIFile << ai << endl;
		}
		AIFile.close();
		AIFile.open("lastSave.data");
		AIFile << generation << endl << population.size();
		AIFile.close();
	}
};


#endif // !Training_h
