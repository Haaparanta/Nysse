#include <QApplication>
#include <memory>
#include "gamewindow.h"
#include "gameengine.hh"
#include "dialog.h"


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(offlinedata);

    std::shared_ptr<Vesa::Gameengine> engine(new Vesa::Gameengine());

    QApplication a(argc, argv);

    Vesa::MainWindow* Game;
    Game = new Vesa::MainWindow();

    engine->takeUi(Game);
    engine->startGame();
    Game->show();

    int result = a.exec();

    delete Game;
    Game = NULL;

    return result;

}
