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
            cout << "Game took " << checkers.gameLength << " seconds" << endl;
            if (checkers.draw) {
                cout << "Game " << i << ": Draw" << endl;
            } else if (checkers.redWin) {
                cout << "Game " << i << ": Red Wins" << endl;
            } else {
                cout << "Game " << i << ": Black Wins" << endl;
            }
            
            // Handle score
            if (checkers.redWin) {
                if (player1.playAsRed) {
                    scores[player1.idx] += 2;
                    scores[player2.idx] -= 1;
                } else {
                    scores[player2.idx] += 2;
                    scores[player1.idx] -= 1;
                }
            } else {
                if (player2.playAsRed) {
                    scores[player1.idx] += 2;
                    scores[player2.idx] -= 1;
                } else {
                    scores[player2.idx] += 2;
                    scores[player1.idx] -= 1;
                }
            }
        }
        duration<double> timeSpan = duration<double>(high_resolution_clock::now() - time.start);
        cout << "Total game time: " << timeSpan.count() << endl;
        cout << "Average game time: " << timeSpan.count() / numberOfGames << endl;
        cout << "Player " << player1.idx << " score: " << scores[player1.idx] << endl;
        cout << "Player " << player2.idx << " score: " << scores[player2.idx] << endl;
    }
    
    void commence() {
        uniform_int_distribution<int> randomIdx(0, population.size() - 1);
        default_random_engine generator(high_resolution_clock::now().time_since_epoch().count());
        for (int i = 0; i < population.size(); ++i) {
            thread games([&](int i) {
                for (int j = 0; j < gamesPerRound; ++j) {
                    thread game([&](int idx) {
                        int otherIdx = randomIdx(generator);
                        while (idx == otherIdx) randomIdx(generator);
                        officiateGame(population[idx], population[otherIdx]);
                    }, i);
                    game.join();
                }
            }, i);
            games.join();
        }
    }
};

#endif /* Tournament_h */
