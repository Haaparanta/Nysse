#include "statistics.h"
#include "string.h"
#include <iostream>
#include <fstream>



Mikael::Statistics::Statistics(Vesa::MainWindow* inputWindow)
{
    mainWindow_ = inputWindow;
    readHighScores();    
}

Mikael::Statistics::~Statistics()
{
    delete mainWindow_;
}


float Mikael::Statistics::monitorProgress(float batCount, float population)
{
    auto progress = batCount / population;
    return progress * 100;
}

void Mikael::Statistics::readHighScores(QString fileName)
{
    std::string delimiter = ",";
    QString filecontent;

    QFile inputFile;
    QFile fileToUse;

    inputFile.setFileName(fileName);
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        fileToUse.setFileName(fileName);
        inputFile.close();
    } else {
        fileToUse.setFileName(":/top_scores.txt");
    }

    fileToUse.open(QIODevice::ReadOnly | QIODevice::Text);
    while(!fileToUse.atEnd()) {
        QString line = fileToUse.readLine();
        line.chop(1);
        auto parts = line.split(", ");
        auto name = parts[0];
        QString scoreStr = parts[1];
        long int score = scoreStr.toLong();
        nameAndScore.push_back(std::make_pair(score, name));
    }
    fileToUse.close();
}

void Mikael::Statistics::updateHighScores(QString playerName, int score, QString fileName)
{
    nameAndScore.push_back(std::make_pair(score, playerName));

    std::sort(nameAndScore.rbegin(), nameAndScore.rend());
    int iterations = 0;
    if (nameAndScore.size() < topScores) {
        iterations = nameAndScore.size();
    } else {
        iterations = topScores;
    }

    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::WriteOnly| QIODevice::Text );
    for (int i = 0; i < iterations; i++) {
        QTextStream out (&file);
        QString toWrite = nameAndScore[i].second + ", " + QString::number(nameAndScore[i].first) + "\n";
        out << toWrite;
        }
}

bool Mikael::Statistics::isTopScore(long int score)
{
    // If there are less than 10 people in top scores, it is safe to you say you made it top10.
    // Otherwise, iterate and compare to top 10.
    if (nameAndScore.size() < topScores) {
        return true;
    }

    long unsigned int i = 0;

    for (i = 0; i < topScores; ++i) {
        auto comparable = nameAndScore[i].second.toLong();
        if ( score > comparable) {
            return true;
        }
    }
    return false;
}
