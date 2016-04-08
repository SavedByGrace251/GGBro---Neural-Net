//
//  Tournament.h
//  GGBro
//
//  Created by Jay Byam And Jonathan Newell

#ifndef Tournament_h
#define Tournament_h

#include "AI.h"
#include <thread>
using std::thread;

class Tournament {
public:
    vector<AI> population;
    vector<int> scores;
    int gamesPerRound = 3;
    
    Tournament(int populationSize) {
        vector<int> layers { 32, 40, 10, 1 };
        for (int i = 0; i < populationSize; ++i) {
            AI player(layers);
            player.makeBrain();
            player.idx = i;
            population.push_back(player);
        }
        scores = vector<int>(populationSize, 0);
    }
    
    Tournament(vector<AI> players) {
        population = players;
        scores = vector<int>(players.size(), 0);
    }
    
	void officiateGame(AI player1, AI player2) {
		cout << "playing game with players " << player1.idx << " and " << player2.idx << endl;
		Game checkers;

		// coin toss for player sides
		uniform_int_distribution<int> flipFlop(0, 1);
		default_random_engine generator(high_resolution_clock::now().time_since_epoch().count());
		if (flipFlop(generator) == 1) {
			checkers.setPlayers(player1, player2);
		} else {
			checkers.setPlayers(player2, player1);
		}

		// play game
		checkers.playGame();

		// Handle score
		// player 1 is red and red wins, or is black and black wins
		if ((checkers.redWin && player1.playAsRed) || (!checkers.redWin && !player1.playAsRed)) {
			scores[player1.idx] += 2;
			scores[player2.idx] -= 1;
		// player 2 is red and red wins, or is black and black wins
		} else {
			scores[player2.idx] += 2;
			scores[player1.idx] -= 1;
		}
	}
    
    void commence() {
        uniform_int_distribution<int> randomIdx(0, population.size() - 1);
        default_random_engine generator(high_resolution_clock::now().time_since_epoch().count());
		vector<thread> games;
		int popSize = population.size();
		// for each AI in the population
        for (int i = 0; i < popSize; ++i) {
			// play "gamesPerRound" games with random opponents
			for (int j = 0; j < gamesPerRound; ++j) {
				games.push_back(thread([&](int idx) {
					// start game clock
					Clock time;
					int otherIdx = randomIdx(generator);
					while (idx == otherIdx) randomIdx(generator);
					// run game
					officiateGame(population[idx], population[otherIdx]);
				}, i));
			}
        }
		for (thread& t : games) {
			t.join();
		}
    }

	void printStats() {
		for (int i = 0; i < population.size(); ++i) {
			cout << "Player " << i << " score: " << scores[i] << endl;
		}
	}
};

#endif /* Tournament_h */
