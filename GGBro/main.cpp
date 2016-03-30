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

// generate boards to a given depth
int searchBoards(std::chrono::high_resolution_clock::time_point start, double maxtime, vector<Board>& boards, NeuralNetwork& net, int& depthReached) {
	++depthReached;
	int n = boards.size();
	cout << "depth: " << depthReached << " " << "Number of boards: " << n << endl;
	vector<Board> nextLevel;
	std::chrono::duration<double> timeSpan(std::chrono::high_resolution_clock::now() - start);
	if (timeSpan.count() < maxtime) {
		for (int i = 0; i < boards.size(); i++) {
			std::chrono::duration<double> timeSpan(std::chrono::high_resolution_clock::now() - start);
			if (timeSpan.count() < maxtime) {
				vector<Board> newBoards = boards[i].generateLegalMoves();
				nextLevel.insert(nextLevel.end(), newBoards.begin(), newBoards.end());
			}
		}
		if (nextLevel.size() > 0) n += searchBoards(start, maxtime, nextLevel, net, depthReached);
	}
	return n;
}

void timeNetwork(NeuralNetwork& net) {
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	std::chrono::duration<double> timeSpan;

	int count = 0;
	t1 = std::chrono::high_resolution_clock::now();
	while (count < 250000) {
		net.Activate();
		++count;
	}
	t2 = std::chrono::high_resolution_clock::now();
	timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

	cout << "Net evaluations per second: " << count / timeSpan.count() << endl;
}

void timeBoardGenerator(AI& player) {
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	std::chrono::duration<double> timeSpan;

	moveMap moves;
	t1 = std::chrono::high_resolution_clock::now();
	Board initboard("rrrrrr__rr_r__b_____b__bb__bbbbb");
	t2 = std::chrono::high_resolution_clock::now();
	timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	cout << "board creation time: " << timeSpan.count() << endl << initboard.toString() << endl;

	vector<Board> newboards = { initboard };
	double computetime = 10;
	double offset = 0.5;
	int depthreached = -1;
	t1 = std::chrono::high_resolution_clock::now();
	int n = searchBoards(t1, computetime - offset, newboards, player.brain, depthreached);
	t2 = std::chrono::high_resolution_clock::now();
	timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

	cout << "number of boards generated: " << n << endl;
	cout << "depth of boards reached: " << depthreached << endl;
	cout << "board generation time: " << timeSpan.count() << endl;
}

int main() {
	vector<int> layers{32, 40, 10, 1};
	AI player(layers);
	player.makeBrain();
	player.playAsRed = true;
//	Board custom("rrrr__r_rrrrr_r_bb_bbb___bbbbR_b", true);
//	for (Board b : custom.generateLegalMoves()) {
//		cout << b << endl;
//	}
//	
//	AI player1(layers);
//	player1.makeBrain();
//	AI player2(layers);
//	player2.makeBrain();
//	
//	for (int i = 1; i <= 20; ++i) {
//		Game checkers(player1, player2);
//		
//		while (!checkers.gameFinished) {
////			cout << checkers.currentBoard << endl;
//			checkers.takeTurn();
//		}
//		checkers.score();
//		
//		if (checkers.draw) {
//			cout << "Game " << i << ": Draw" << endl;
//		} else if (checkers.redWin) {
//			cout << "Game " << i << ": Red Wins" << endl;
//		} else {
//			cout << "Game " << i << ": Black Wins" << endl;
//		}
//		player1.makeBrain();
//		player2.makeBrain();
//	}
//	cout << "Player 1 score: " << player1.score << endl;
//	cout << "Player 2 score: " << player2.score << endl;
	
	timeBoardGenerator(player);

	cout << "press ENTER to continue";
	while (cin.get() != '\n');
	return 0;
}