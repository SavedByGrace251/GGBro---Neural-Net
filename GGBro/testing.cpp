// testing file for cpp things

#include "Board.h"
#include "Piece.h"
#include "AI.h"
#include "Checkers.h"
#include "Tournament.h"
#include "Training.h"
#include <fstream>
#include <iterator>
using namespace std;

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

void timeBoardGenerator() {
	AI player;
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

void testTourney() {
	Clock timer;
	Tournament test(15);
	timer.start = high_resolution_clock::now();
	test.commence();
	cout << endl << "************************ Tourny Stats ************************" << endl;
	cout << "tournament took " << duration<double>(high_resolution_clock::now() - timer.start).count() << " seconds." << endl;
	test.printStats(cout);
}

void timeNetwork() {
	AI player;

	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
	duration<double> timeSpan;

	int count = 0;
	t1 = high_resolution_clock::now();
	while (count < 1000000) {
		player.brain.Activate();
		++count;
	}
	t2 = high_resolution_clock::now();
	timeSpan = duration_cast<duration<double>>(t2 - t1);

	cout << "Net evaluations per second: " << count / timeSpan.count() << endl;
}

int main() {
	


	return 0;
}