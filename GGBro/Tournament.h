//	Authors: Jay Byam, Jonathan Newell
//
//  Tournament.h
//  GGBro
//

#ifndef Tournament_h
#define Tournament_h

#include "AI.h"
#include <thread>
using std::thread;

class Tournament {
public:
	vector<AI> contestants;
	vector<int> scores;
	vector<int> wins;
	vector<int> losses;
	vector<int> gamesPlayed;
	vector<int> gamesAsRed;
	vector<int> winsAsRed;
	vector<int> gamesAsBlack;
	vector<int> winsAsBlack;
	vector<duration<double>> gameTimes;
	int gamesPerRound = 5;
	
	Tournament(int nContestants) {
		contestants = vector<AI>(nContestants);
		for (int i = 0; i < nContestants; ++i) {
			contestants[i].idx = i;
		}
		setup(nContestants);
	}
	
	Tournament(vector<AI> players) {
		contestants = players;
		int nContestants = contestants.size();
		for (int i = 0; i < nContestants; ++i) {
			contestants[i].idx = i;
		}
		setup(nContestants);
	}
	
	void setup(int nContestants) {
		scores = vector<int>(nContestants, 0);
		wins = vector<int>(nContestants, 0);
		losses = vector<int>(nContestants, 0);
		gamesPlayed = vector<int>(nContestants, 0);
		gamesAsRed = vector<int>(nContestants, 0);
		gamesAsBlack = vector<int>(nContestants, 0);
		winsAsRed = vector<int>(nContestants, 0);
		winsAsBlack = vector<int>(nContestants, 0);
	}

	void officiateGame(AI player1, AI player2, bool printGame = false) {
		Game checkers;

		// coin toss for player sides
		uniform_int_distribution<int> flipFlop(0, 1);
		default_random_engine generator(high_resolution_clock::now().time_since_epoch().count());
		if (flipFlop(generator) == 1) {
			gamesAsRed[player1.idx] += 1;
			gamesAsBlack[player2.idx] += 1;
			checkers.setPlayers(player1, player2);
		} else {
			gamesPlayed[player1.idx] += 1;
			gamesAsBlack[player2.idx] += 1;
			checkers.setPlayers(player2, player1);
		}

		// play game
		checkers.playGame();
		if (printGame) {
			cout << checkers << endl;
		}

		// Handle score
		// player 1 is red and red wins, or is black and black wins
		if (!checkers.draw) {
			if (checkers.redWin) { // if red won the game
				if (player1.playAsRed) { // if player 1 is red
					scores[player1.idx] += 2;
					wins[player1.idx] += 1;
					winsAsRed[player1.idx] += 1;
					scores[player2.idx] -= 1;
					losses[player2.idx] += 1;
				} else { // if player 2 is red
					scores[player2.idx] += 2;
					wins[player2.idx] += 1;
					winsAsRed[player2.idx] += 1;
					scores[player1.idx] -= 1;
					losses[player1.idx] += 1;
				}
			} else { // if black won the game
				if (player1.playAsRed) { // if player 2 is black
					scores[player2.idx] += 2;
					wins[player2.idx] += 1;
					winsAsBlack[player2.idx] += 1;
					scores[player1.idx] -= 1;
					losses[player1.idx] += 1;
				} else { // if player 1 is black
					scores[player1.idx] += 2;
					wins[player1.idx] += 1;
					winsAsBlack[player1.idx] += 1;
					scores[player2.idx] -= 1;
					losses[player2.idx] += 1;
				}
			}
		}
		gamesPlayed[player1.idx] += 1;
		gamesPlayed[player2.idx] += 1;
	}
	
	void commence() {
		uniform_int_distribution<int> randomIdx(0, contestants.size() - 1);
		default_random_engine generator(high_resolution_clock::now().time_since_epoch().count());
		vector<thread> games;
		int popSize = contestants.size();
		// for each AI in the population
		for (int i = 0; i < popSize; ++i) {
			// play "gamesPerRound" games with random opponents
			for (int j = 0; j < gamesPerRound; ++j) {
				//cout << "AI " << i << " game " << j << endl;
				games.push_back(thread([&](int idx) {
					int otherIdx = randomIdx(generator);
					while (idx == otherIdx) otherIdx = randomIdx(generator);
					// run game
					officiateGame(contestants[idx], contestants[otherIdx]);
				}, i));
			}
		}
		for (thread& t : games) {
			t.join();
		}
	}

	void printStats(ostream& os) {
		double totalTimes = 0;
		for (int i = 0; i < contestants.size(); ++i) {
			os << "Player " << i << " - score: " << scores[i] << endl;
			int draws = gamesPlayed[i] - wins[i] - losses[i];
			os << "\t** W: " << wins[i] << " L: " << losses[i] << " D: " << draws << endl;
			os << "\t** R: " << gamesAsRed[i] << " B: " << gamesAsBlack[i] << " T: " << gamesPlayed[i] << endl;
			os << "\t** wR: " << winsAsRed[i] << " wB: " << winsAsBlack[i] << endl;
		}
	}
};

#endif /* Tournament_h */
