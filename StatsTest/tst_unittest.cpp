#include <QtTest>
#include <QCoreApplication>
#include <statistics.h>
#include <QMainWindow>
#include <vector>

// add necessary includes here

namespace Mikael {
    class unittest;
}

class unittest : public QObject
{
    Q_OBJECT


public:
    unittest();
    ~unittest();

private slots:

    // Test, that we read in the scores properly
    void testReadingScores();

    // Make sure we are monitoring the infection% right
    void testProgress();

    // Do we report new high scores accurately
    void testTopScore();

    // Game writes a new top score file into build folder after
    // first build & run. Verify the quality of it.
    void testWritingScores();

private:
    Mikael::Statistics* stats_ = nullptr;
};

unittest::unittest()
{
    qDebug() << "Syötä nimi ja paina hyväksymistä, jos haluat ajaa yksikkötestit";
    qDebug() << "Syötä nimi ja paina hyväksymistä, jos haluat ajaa yksikkötestit";
    qDebug() << "Syötä nimi ja paina hyväksymistä, jos haluat ajaa yksikkötestit";
    qDebug() << "Syötä nimi ja paina hyväksymistä, jos haluat ajaa yksikkötestit";
    qDebug() << "Syötä nimi ja paina hyväksymistä, jos haluat ajaa yksikkötestit";
    Vesa::MainWindow* window(new Vesa::MainWindow());
    Mikael::Statistics* stats(new Mikael::Statistics(window));
    stats_ = stats;
    QString file = ":/test_score.txt";
    stats_->readHighScores(file);

}

unittest::~unittest()
{    
    delete stats_;
}

void unittest::testReadingScores()
{
    // Making sure top score files are being read correctly
    QVERIFY2(stats_->nameAndScore.size() == stats_->topScores, "Pitäs olla 10 top scorea");
    QVERIFY2(stats_->nameAndScore[0].first == 52342, "52342 pitäs olla");
    QVERIFY2(stats_->nameAndScore[9].first == 0, "0 pitäs olla");
    QVERIFY2(stats_->nameAndScore[2].second == "Ack Ristley", "Pitäs rick rollailla");
    QVERIFY2(stats_->nameAndScore[6].second == "Black Friday", "Synkkä perjantai olis");
}

void unittest::testProgress()
{
    // 1 lepakko, 100 populaatio
    QVERIFY2(stats_->monitorProgress(1, 100) == 1, "Pitäs olla 1%");
    QVERIFY2(stats_->monitorProgress(500, 500) == 100, "Pitäs olla 100%");
}

void unittest::testTopScore()
{
    QVERIFY2(stats_->isTopScore(100009) == true, "godtier, onneksi olkoon, pitäs olla listalla");
    QVERIFY2(stats_->isTopScore(500) == true, "Tän pitäisi päästä listalle");
    QVERIFY2(stats_->isTopScore(0) == false, "Tän ei pitäs päästä listalle");
    QVERIFY2(stats_->isTopScore(323232323232) == true, "no nyt on seppä, pitäs olla nipin napin "
                                                       "johdossa");
}

void unittest::testWritingScores()
{
    // After game ends, a new top score list is made. Need to verify it was written & new top scores
    // read again properly.
    QString file = "test_score.txt";
    stats_->updateHighScores("Testinukke", 52345, file);
    stats_->nameAndScore.clear();
    stats_->readHighScores(file);

    // Test, that there is a new leader and others have move down the list by 1 step
    QVERIFY2(stats_->nameAndScore.size() == stats_->topScores, "pitäs olla 10 alkiota");
    QVERIFY2(stats_->nameAndScore[0].second == "Testinukke", "Testinuken piti päästä ekaksi");
    QVERIFY2(stats_->nameAndScore[0].first == 52345, "Testinuken pitäs voittaa");
    QVERIFY2(stats_->nameAndScore[1].first == 52342, "52342 pitäs olla");
    QVERIFY2(stats_->nameAndScore[9].first == 20000, "20000 pitäs olla ny vika");
    QVERIFY2(stats_->nameAndScore[3].second == "Ack Ristley", "Pitäs rick rollailla");
    QVERIFY2(stats_->nameAndScore[7].second == "Black Friday", "Synkkä perjantai olis");

}

QTEST_MAIN(unittest)

#include "tst_unittest.moc"
