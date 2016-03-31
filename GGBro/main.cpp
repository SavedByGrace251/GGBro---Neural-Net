//
//  main.cpp
//  GGBro
//
//  Created by Jay Byam on 2/6/16.
//

#include "Board.h"
#include "Piece.h"
#include "AI.h"
#include "Checkers.h"
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

struct AlphaBeta {
	double alpha = -1;
	double beta = 2;
	bool isAlpha;
};



// search boards for a given time
int searchBoards(Clock& time, vector<Board>& boards, AI& player, bool isAlpha, int& depthReached) {
	++depthReached;
	int n = boards.size();
	string minOrMax;
	if (isAlpha) {
		minOrMax = "MAX";
	} else {
		minOrMax = "MIN";
	}
	cout << "min or max: " << minOrMax << " depth: " << depthReached << " number of boards: " << n << endl;
	vector<Board> nextLevel;
	vector<Board> newBoards;
	for (int i = 0; (i < n) && (duration<double>(high_resolution_clock::now() - time.start).count() < time.maxtime); i++) {
		if (duration<double>(high_resolution_clock::now() - time.start).count() < time.maxtime) {
			newBoards = boards[i].generateLegalMoves();
			player.evaluate(newBoards, isAlpha);
			nextLevel.insert(nextLevel.end(), newBoards.begin(), newBoards.end());
		} else {
			cout << "TIME EXCEEDED - " << duration<double>(high_resolution_clock::now() - time.start).count() << endl;
		}
	}
	sort(nextLevel.begin(), nextLevel.end());
	if (duration<double>(high_resolution_clock::now() - time.start).count() < time.maxtime) {
		if (nextLevel.size() > 0) {
			n += searchBoards(time, nextLevel, player, !isAlpha, depthReached);
		}
	}
	cout << "TIME EXCEEDED - " << duration<double>(high_resolution_clock::now() - time.start).count() << endl;
	return n;
}

void timeNetwork(NeuralNetwork& net) {
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
	duration<double> timeSpan;

	int count = 0;
	t1 = high_resolution_clock::now();
	while (count < 250000) {
		net.Activate();
		++count;
	}
	t2 = high_resolution_clock::now();
	timeSpan = duration_cast<duration<double>>(t2 - t1);

	cout << "Net evaluations per second: " << count / timeSpan.count() << endl;
}

void timeBoardGenerator(AI& player) {
	duration<double> timeSpan;

	Board initboard("______B___________________R_____");
	vector<Board> newboards = initboard.generateLegalMoves();
	bool isAlpha = true;
	Clock time;
	double offset = 0;
	time.maxtime = 2 - offset;
	int depthreached = -1;
	int numberOfBoards = 0;
	time.start = high_resolution_clock::now();
	numberOfBoards = searchBoards(time, newboards, player, isAlpha, depthreached);
	timeSpan = duration_cast<duration<double>>(high_resolution_clock::now() - time.start);

	cout << "number of boards generated: " << numberOfBoards << endl;
	cout << "depth of boards reached: " << depthreached << endl;
	cout << "board generation time: " << timeSpan.count() << endl << endl;
	for (Board& b : newboards) {

	}
}

int main() {
	vector<int> layers{32, 40, 10, 1};
	AI player(layers);
	player.makeBrain();
	player.playAsRed = true;
	
	AI player1(layers);
	player1.makeBrain();
	AI player2(layers);
	player2.makeBrain();
	vector<duration<double>> times;

	Clock time;
	time.start = high_resolution_clock::now();
	int numberOfGames = 5;
	for (int i = 1; i <= numberOfGames; ++i) {
		uniform_int_distribution<int> flipFlop(0, 1);
		default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		Game checkers;
		if (flipFlop(generator) == 1) {
			checkers.setPlayers(player1, player2);
		} else {
			checkers.setPlayers(player2, player1);
		}
		
		while (!checkers.gameFinished) {
			checkers.takeTurn();
		}
		checkers.score();
		cout << checkers;

		cout << "Game took " << times.back().count() << " seconds" << endl;
		if (checkers.draw) {
			cout << "Game " << i << ": Draw" << endl;
		} else if (checkers.redWin) {
			cout << "Game " << i << ": Red Wins" << endl;
		} else {
			cout << "Game " << i << ": Black Wins" << endl;
		}
		player1.makeBrain();
		player2.makeBrain();
	}
	duration<double> timeSpan = duration<double>(high_resolution_clock::now() - time.start);
	cout << "Total game time: " << timeSpan.count() << endl;
	cout << "Average game time: " << timeSpan.count() / numberOfGames << endl;
	cout << "Player 1 score: " << player1.score << endl;
	cout << "Player 2 score: " << player2.score << endl;
	
	//timeBoardGenerator(player);

	cout << "press ENTER to continue";
	while (cin.get() != '\n');
	return 0;
}