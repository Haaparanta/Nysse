#ifndef STATISTICS_H
#define STATISTICS_H
#include <QString>
#include "gamewindow.h"
#include <fstream>
#include "string.h"
#include <iostream>
#include <QString>
#include <vector>
#include <QDebug>

#include "../CourseLib/interfaces/istatistics.hh"


namespace Mikael {

class Statistics {

public:
    Statistics(Vesa::MainWindow* inputWindow = nullptr);
    ~Statistics();

    // City will call this to check whether game has ended
    float monitorProgress(float bats, float population);

    // Read in the high scores into "nameAndScore"
    void readHighScores (QString fileName = "top_scores.txt");

    // If someone made it to top 10, re-write the top_scores.txt
    void updateHighScores (QString playerName = "Jeesus", int score = 0, QString fileName = "top_scores.txt");

    // Used to determine whether udpateHighScores is being called
    bool isTopScore(long int score);

    // Store top 10 names and scores
    std::vector<std::pair<long int, QString>> nameAndScore;

    // Seems to give warnings about comparison of different signedness, unless
    // this is specified as long unsigned
    long unsigned int topScores = 10;

private:
    Vesa::MainWindow* mainWindow_ = nullptr;

};

}

#endif // STATISTICS_H
