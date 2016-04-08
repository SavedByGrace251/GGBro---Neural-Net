//	Authors: Jay Byam, Jonathan Newell
//
//  main.cpp
//  GGBro
//

#include "Board.h"
#include "Piece.h"
#include "AI.h"
#include "Checkers.h"
#include "Tournament.h"
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

// search boards for a given time
int searchBoards(Clock& time, vector<vector<Board>>& boards, AI& player, bool isAlpha, int depthReached, int maxDepth) {
	int nBoards = boards[depthReached - 1].size();
	int n = nBoards;
	if (depthReached <= maxDepth) {
		for (int i = 0; (i < nBoards) && (duration<double>(high_resolution_clock::now() - time.start).count() < time.maxtime); i++) {
			if (duration<double>(high_resolution_clock::now() - time.start).count() < time.maxtime) {
				boards[depthReached - 1][i].generateLegalMoves(boards[depthReached]);
				//if (boards[depthReached].size() > 10) {
				//	cout << "Preallocate MORE THAN 10";
				//}
				if (duration<double>(high_resolution_clock::now() - time.start).count() < time.maxtime) {
					if (boards.size() > 0) {
						n += searchBoards(time, boards, player, !isAlpha, depthReached + 1, maxDepth);
					}
				}
			}
		}
	} else {
		player.evaluate(boards[depthReached], isAlpha);
	}
	return n;
}

int BFSBoards(Clock& time, vector<vector<Board>>& boards, AI& player, bool isAlpha, int depthReached, int maxDepth) {
	++depthReached;
	int n = boards[depthReached].size();
	if (depthReached == maxDepth) {
		return n;
	}
	string minOrMax;
	if (isAlpha) {
		minOrMax = "MAX";
	} else {
		minOrMax = "MIN";
	}
	cout << "min or max: " << minOrMax << " depth: " << depthReached << " number of boards: " << n << endl;
	vector<Board> newBoards;
	for (int i = 0; (i < n) && (duration<double>(high_resolution_clock::now() - time.start).count() < time.maxtime); i++) {
		if (duration<double>(high_resolution_clock::now() - time.start).count() < time.maxtime) {
			boards[depthReached][i].generateLegalMoves(newBoards);
			//if (newBoards.size() > 8) {
			//	cout << "Preallocate MORE THAN 8";
			//}
			player.evaluate(newBoards, isAlpha);
			boards[depthReached+1].insert(boards[depthReached+1].end(), newBoards.begin(), newBoards.end());
		} else {
			cout << "TIME EXCEEDED - " << duration<double>(high_resolution_clock::now() - time.start).count() << endl;
		}
	}
	sort(boards[depthReached+1].begin(), boards[depthReached+1].end());
	if (duration<double>(high_resolution_clock::now() - time.start).count() < time.maxtime) {
		if (boards[depthReached].size() > 0) {
			n += BFSBoards(time, boards, player, !isAlpha, depthReached, maxDepth);
		}
	}
	cout << "TIME EXCEEDED - " << duration<double>(high_resolution_clock::now() - time.start).count() << endl;
	return n;
}

void timeBoardGenerator(AI& player) {
	duration<double> timeSpan;

	Board initboard;
	vector<vector<Board>> newBoards(20);
	for (vector<Board>& b : newBoards) {
		b.reserve(10);
	}
	initboard.generateLegalMoves(newBoards[0]);
	vector<double> ranks(newBoards[0].size());
	Clock time;
	time.maxtime = 15;
	int maxDepth = 8;
	int numberOfBoards;
	time.start = high_resolution_clock::now();
	do {
		numberOfBoards = searchBoards(time, newBoards, player, true, 1, maxDepth);
		cout << "Depth " << maxDepth << " search complete, current board selection: " << newBoards[0][0] << endl;
		++maxDepth;
	} while ((duration_cast<duration<double>>(high_resolution_clock::now() - time.start).count() < time.maxtime) && maxDepth < 20);
	timeSpan = duration_cast<duration<double>>(high_resolution_clock::now() - time.start);

	cout << "number of boards generated: " << numberOfBoards << endl;
	cout << "depth of boards reached: " << maxDepth << endl;
	cout << "board generation time: " << timeSpan.count() << endl << endl;
}

void testTourney(AI& player1, AI& player2) {
	Clock time;
	time.start = high_resolution_clock::now();
	int numberOfGames = 5;
	for (int i = 1; i <= numberOfGames; ++i) {
		uniform_int_distribution<int> flipFlop(0, 1);
		default_random_engine generator(time.start.time_since_epoch().count());
		Game checkers;
		if (flipFlop(generator) == 1) {
			checkers.setPlayers(player1, player2);
		} else {
			checkers.setPlayers(player2, player1);
		}
	
	checkers.playGame();
	cout << checkers << endl;
	cout << "Game took " << checkers.gameLength << " seconds" << endl;
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
}

void timeNetwork(AI& player) {
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
	duration<double> timeSpan;

	int count = 0;
	t1 = high_resolution_clock::now();
	while (count < 250000) {
		player.brain.Activate();
		++count;
	}
	t2 = high_resolution_clock::now();
	timeSpan = duration_cast<duration<double>>(t2 - t1);

	cout << "Net evaluations per second: " << count / timeSpan.count() << endl;
}

int main() {
	vector<int> layers{32, 40, 10, 1};	
	AI player1(layers);
	player1.makeBrain();
	AI player2(layers);
	player2.makeBrain();	
	
    Tournament test(4);
    test.commence();
	test.printStats();

	cout << "press ENTER to continue";
	while (cin.get() != '\n');
	return 0;
}