#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "gameengine.hh"
#include <QDebug>

namespace Vesa {


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Mikael::Dialog* Dialog;
    Dialog = new Mikael::Dialog();
    connect(Dialog, &Mikael::Dialog::sendName,
            this, &MainWindow::storedName);

    int dialogResult = Dialog->exec();


    map = new QGraphicsScene(this);
    ui->View->setScene(map);
    ui->View->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);

    timer_.setSingleShot(false);
    fast_timer_.setSingleShot(false);
    resource_timer.setSingleShot(false);
    infection_timer.setSingleShot(false);

    connect(&fast_timer_, &QTimer::timeout, this, &MainWindow::updateView);
    connect(&timer_, &QTimer::timeout,this, &MainWindow::updatePoints);
    connect(&resource_timer, &QTimer::timeout,this, &MainWindow::addResource);
    connect(&infection_timer,&QTimer::timeout, this, &MainWindow::updatePandemic);
    connect(ui->quit, &QPushButton::clicked,
            this, &MainWindow::close);

    if (dialogResult == 0) {
        on_quit_clicked();
    }

    points_ = 0;
    min_ = 0;
    sec_ = 0;
    song_ = new QSound(":/roll.wav");
    song_->setLoops(QSound::Infinite);
    song = new QSound(":/Super.wav");
    song->setLoops(QSound::Infinite);

    addResourceLocations();

    ui->pause->setDisabled(true);
    ui->reset->setDisabled(true);

    delete Dialog;
}

MainWindow::~MainWindow()
{
    delete song;
    delete song_;
    delete ui;
    delete gamer_;
    delete fps_;
    delete kasidesi_;
    delete vessapaperi_;
    delete maskit_;
    delete min;
    delete sec;
    delete bats_;
    delete people_;
    delete score_;
    delete instructions_;
    delete gameEndingText_;
    for (auto it : resourseandtext) {
        delete it.first;
        delete it.second;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // Moves player commanded thing
    if (gameOn) {
        int deltaX = 0;
        int deltaY = 0;
        int step_ = useUpgrade(4);
        char heading = 'x';
        if (event->key() == Qt::Key_A) {
            heading = 'A';
            deltaX -= step_;
        } else if (event->key() == Qt::Key_S) {
            heading = 'S';
            deltaY = step_;
        } else if (event->key() == Qt::Key_D) {
            heading = 'D';
            deltaX = step_;
        } else if (event->key() == Qt::Key_W) {
            heading = 'W';
            deltaY -= step_;
        } else if (event->key() == Qt::Key_Space) {
            heading = 'z';
            auto nearby = getNearbyActorsandItems(gamer_->returnloc(), useUpgrade(3));
            for (auto actor : nearby) {
                if (kasidesi > 0 && maskit > 0 && vessapaperi > 0) {
                    --kasidesi;
                    --maskit;
                    --vessapaperi;
                    for (auto infected : infectedsAndItems) {
                        auto infectedactor = infected.first;
                        if (infectedactor == actor.first) {
                            if (infected.second->cure()) {
                                qDebug() << "cure";
                                points_ += 1000;
                                --bats;
                            }
                        }
                    }
                } else {
                    qDebug() << "You run out of healing material";
                }
            }
        } else if (event->key() == Qt::Key_R) {
            collectResources();
        }

        if (heading != 'z' && heading != 'x') {
            gamer_->move(heading, deltaX, deltaY);
            playerVision();

        }
    }
}

Ui::MainWindow* MainWindow::giveMainwindow()
{
    return ui;
}

void MainWindow::addActor(Vesa::ActorItem* nActor)
{
    map->addItem(nActor);
}

std::vector<std::pair<std::shared_ptr<Interface::IActor>, ActorItem *>> MainWindow::getNearbyActorsandItems(
        Interface::Location loc, int radius)
{
    std::vector<std::pair<std::shared_ptr<Interface::IActor>, ActorItem *> > nearbyActorsanditems;
    for (auto& actors : actorsAndItems_) {
        if (actors.first->giveLocation().isClose(loc, radius)) {
            nearbyActorsanditems.push_back(actors);
        }
    }
    return nearbyActorsanditems;
}

void MainWindow::addInfected(std::pair<std::shared_ptr<Interface::IActor>, ActorItem *> Infected)
{
    infectedsAndItems.push_back(Infected);
}

void MainWindow::resetInfected()
{
    for (auto it : infectedsAndItems) {
        it.second->cure();
    }
    infectedsAndItems.clear();
}

void MainWindow::getActorsanditems(std::vector<std::pair<std::shared_ptr<Interface::IActor>, ActorItem *>>
                                   actorsAndItems)
{
    actorsAndItems_ = actorsAndItems;
}


void MainWindow::takeCity(std::shared_ptr<Interface::ICity> city)
{
    city_ = city;
}

void MainWindow::on_start_clicked()
{
    gameOn = true;
    timer_.start(1000);
    fast_timer_.start(7); // Fixed framerate 143
    resource_timer.start(5000);
    infection_timer.start(15000);
    delete gamer_;
    gamer_ = new Gamer(sceneWidth, sceneHeight, name_);

    map->addItem(gamer_);
    playerVision();    

    ui->start->setDisabled(true);
    ui->pause->setEnabled(true);
    ui->reset->setEnabled(true);

}

void MainWindow::on_pause_clicked()
{        

    if (ui->pause->text() == "Pause") {
        gameOn = false;
        ui->pause->setText("Continue");
        fast_timer_.stop();
        timer_.stop();
        resource_timer.stop();
        infection_timer.stop();

    } else {
        gameOn = true;
        ui->pause->setText("Pause");
        timer_.start(1000);
        fast_timer_.start(7);
        resource_timer.start(5000);
        infection_timer.start(15000);
    }
}

void MainWindow::on_reset_clicked()
{
    points_ = 0;
    min_ = 0;
    sec_ = 0;
    bats = 20;

    // Display does not play nicely with long int I guess?
    QString score = QString::number(points_);
    ui->score->display(score);

    ui->sec->display(sec_);
    ui->min->display(min_);

    if (ui->pause->text() == "Pause") {
        fast_timer_.stop();
        timer_.stop();
        resource_timer.stop();
        infection_timer.stop();
    }
    resetInfected();
    resetResources();
    resetUpgrades();
    song_->stop();
    ui->Playmusic->setText("Play music");
    gameOn = false;
    ui->start->setEnabled(true);
    ui->pause->setDisabled(true);
    ui->pause->setText("Pause");
    ui->reset->setDisabled(true);
    city_->startGame();
    delete gameEndingText_;

}


void MainWindow::on_quit_clicked()
{
    qDebug() << "score" << points_;
    on_reset_clicked();
}

void MainWindow::setPicture(QImage &img)
{
    // Sets backround picture
    // Removes scrollbars if you use smallpicrure
    map->setBackgroundBrush(img);
    QSize data = img.size();
    sceneWidth = data.width();
    sceneHeight = data.height();
    map->setSceneRect(0,0,sceneWidth, sceneHeight);
    if (data.width() == 500) {
        ui->View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } else {
        ui->View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ui->View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    }
}

void MainWindow::setGameBackround()
{
    // if smaller picture make smaller view and if bigger picture make wider view
    if (sceneWidth == 500 && sceneHeight == 500) {
        viewWidth = 500;
        viewHeight = 500;
        bigMap = false;
    } else {
        viewWidth = 800;
        viewHeight = 500;
    }

    int lcd_w = 100; // Width of lcd screen
    int lcd_h = 30; // height of lcd
    int but_w = 200; // Widht of button
    this->resize(viewWidth + 50 + 15 + but_w + 15 // application size
                 ,viewHeight + 100 + 50);
    ui->View->setGeometry(50, 100, viewWidth, viewHeight);

    int buffer = 50 + viewWidth + 15;
    // where everything in the window
    ui->up1->setGeometry(50,10,lcd_w,lcd_h);
    ui->lcd1->setGeometry(50,40,lcd_w,lcd_h);
    ui->up2->setGeometry(200,10,lcd_w,lcd_h);
    ui->lcd2->setGeometry(200,40,lcd_w,lcd_h);
    ui->up3->setGeometry(350,10,lcd_w,lcd_h);
    ui->lcd3->setGeometry(350,40,lcd_w,lcd_h);
    ui->up4->setGeometry(500,10,lcd_w,lcd_h);
    ui->lcd4->setGeometry(500,40,lcd_w, lcd_h);
    ui->up5->setGeometry(650,10,lcd_w,lcd_h);
    ui->lcd5->setGeometry(650,40,lcd_w, lcd_h);
    ui->score->setGeometry(buffer,25,but_w,lcd_h+lcd_h);
    ui->min->setGeometry(buffer,105,lcd_w,lcd_h);
    ui->sec->setGeometry(buffer + 100,105,lcd_w,lcd_h);
    ui->Bats->setGeometry(buffer,160,lcd_w,lcd_h);
    ui->People->setGeometry(buffer + 100,160,lcd_w,lcd_h);
    ui->start->setGeometry(buffer,195,but_w,lcd_h);
    ui->pause->setGeometry(buffer,230,but_w,lcd_h);
    ui->reset->setGeometry(buffer,265,but_w,lcd_h);
    ui->quit->setGeometry(buffer,300,but_w,lcd_h);
    ui->Playmusic->setGeometry(buffer, 335, but_w, lcd_h);

    // Labels for everything

    fps_ = new QLabel(this);
    fps_->setText("FPS:");
    fps_->setGeometry(775 + 20,10,65,lcd_h);
    ui->fps->setGeometry(775,40,65, lcd_h);
    kasidesi_ = new QLabel(this);
    kasidesi_->setPixmap(QPixmap(":/kasidesi.png"));
    kasidesi_->setGeometry(150,20,50,50);
    vessapaperi_ = new QLabel(this);
    vessapaperi_->setPixmap(QPixmap(":/Vessapaperi.png"));
    vessapaperi_->setGeometry(300,20,50,50);
    maskit_ = new QLabel(this);
    maskit_->setPixmap(QPixmap(":/mask.png"));
    maskit_->setGeometry(450,20,50,50);
    score_ = new QLabel(this);
    score_->setText("Score:");
    score_->setGeometry(buffer,10,but_w,15);
    min = new QLabel(this);
    min->setText("Time Min:");
    min->setGeometry(buffer,90,lcd_w,15);
    sec = new QLabel(this);
    sec->setText("Sec:");
    sec->setGeometry(buffer + lcd_w,90,lcd_w,15);
    bats_ = new QLabel(this);
    bats_->setText("Bats:");
    bats_->setGeometry(buffer,140,lcd_w,15);
    people_ = new QLabel(this);
    people_->setText("People:");
    people_->setGeometry(buffer + lcd_w,140,lcd_w,15);
    instructions_ = new QLabel(this);
    instructions_->setText("How to play: \nMove: WASD \nCollect: R \nHeal: Spacebar");
    instructions_->setGeometry(buffer, 380, lcd_w, 100);



    // focus policy so it doesn't mess wasd controls
    ui->up1->setFocusPolicy(Qt::NoFocus);
    ui->up2->setFocusPolicy(Qt::NoFocus);
    ui->up3->setFocusPolicy(Qt::NoFocus);
    ui->up4->setFocusPolicy(Qt::NoFocus);
    ui->up5->setFocusPolicy(Qt::NoFocus);
    ui->start->setFocusPolicy(Qt::NoFocus);
    ui->pause->setFocusPolicy(Qt::NoFocus);
    ui->reset->setFocusPolicy(Qt::NoFocus);
    ui->quit->setFocusPolicy(Qt::NoFocus);
    ui->Playmusic->setFocusPolicy(Qt::NoFocus);


    this->setPalette(Qt::white); // window background color
}

void MainWindow::playerVision()
{
    // Makes game more enjoyable, when player is in center of screen and
    // you dont have to use scrollbars.
    if (bigMap) {
        QPoint point(gamer_->giveX(), gamer_->giveY());
        ui->View->centerOn(point);
    }
}

void MainWindow::storedName(QString name)
{
    name_ = name;
}

QString MainWindow::getName()
{
    return name_;
}

void MainWindow::updatePandemic()
{
    // Give infection to nearby actors with 5% chance
    std::vector<std::pair<std::shared_ptr<Interface::IActor>, Vesa::ActorItem*>> Infectedanditems;
    for (auto it : infectedsAndItems) {
        if (it.second->hasInfection()) {
            Infectedanditems.push_back(it);
            auto nearbyPassengers = getNearbyActorsandItems(it.first->giveLocation(), 10);
            for ( auto passenger : nearbyPassengers ) {
                if (!passenger.second->hasInfection()) {
                    int luckynumber = std::rand() % 100 + 1; // between 1-100
                    if (luckynumber >= 95) {
                        passenger.second->giveInfection();
                        Infectedanditems.push_back(passenger);
                        ++bats;
                    }
                }
            }
        }
    }
    infectedsAndItems.clear();
    for (auto it : Infectedanditems) {
        addInfected(it);
    }
}

int MainWindow::reportBatCount()
{
    return bats;
}

int MainWindow::reportPopulation()
{
    return actorsAndItems_.size();
}

void MainWindow::endGame(bool defeated)
{
    gameOn = false;
    fast_timer_.stop();
    timer_.stop();
    resource_timer.stop();
    infection_timer.stop();   

    ui->pause->setDisabled(true);
    if (!song->isFinished()) {
        on_Playmusic_clicked();
    }
    gameEndingText_ = new QLabel(this);
    gameEndingText_->setGeometry(865,500,100,100);

    ui->Playmusic->setDisabled(true);
    if (!defeated) {
        song_->play();
        gameEndingText_->setText("You Have Lost \n Enjoy the Punisment");
    } else {
        gameEndingText_->setText("You Have Won \n the Game");
    }
}

long int MainWindow::getPoints()
{
    return points_;
}

void MainWindow::upgrade(int type)
{
    if (type == 0) {
        kasidesiU *= 2;
    } else if (type == 1) {
        vessapaperiU *= 2;
    } else if (type == 2) {
        maskitU *= 2;
    } else if (type == 3) {
        rangeU *= 2;
    } else if (type == 4) {
        speedU += 5;
    }
}

int MainWindow::useUpgrade(int type)
{
    if (type == 0) {
        return kasidesiU;
    } else if (type == 1) {
        return vessapaperiU;
    } else if (type == 2) {
        return maskitU;
    } else if (type == 3) {
        return rangeU;
    } else if (type == 4) {
        return speedU;
    } else {
        return 1;
    }
}

void MainWindow::resetUpgrades()
{
    kasidesiU = 5;
    vessapaperiU = 3;
    maskitU = 4;
    rangeU = 60;
    speedU = 5;
}

void MainWindow::updatePoints()
{
    // Update LCD displays and and advances time.
    if (bats < 0) {
        bats = 0;
    }
    points_ += 1; // Get one point per second
    sec_ += 1;
    if (sec_ >= 60) {
        ++min_;
        sec_ = 0;
    }
    ui->sec->display(sec_);
    ui->min->display(min_);
    ui->fps->display(refresh_rate);
    refresh_rate = 0;

    QString score = QString::number(points_);
    ui->score->display(score);

    ui->lcd1->display(kasidesi);
    ui->lcd2->display(vessapaperi);
    ui->lcd3->display(maskit);
    ui->Bats->display(bats);
    int size = actorsAndItems_.size() - bats;
    ui->People->display(size);
    ui->lcd4->display(rangeU);
    ui->lcd5->display(speedU);
}

void MainWindow::updateView()
{
    // do even and minimal screen refreshing
    ui->View->update(gamer_->giveX() - 500, gamer_->giveX() + 500, gamer_->giveY() - 500, gamer_->giveY() + 500);
    map->invalidate();
    ++refresh_rate;
}


void MainWindow::collectResources()
{
    // Collect resources so you can use them.
    // You can only collect from nearby resource locations.
    for (auto it : resourseandtext) {
        if (gamer_->returnloc().isClose(it.first->returnloc(), useUpgrade(3))) {
            int temp = it.first->returnResource();
            points_ += temp * 10;
            if (it.first->returnType() == 0) {
                kasidesi += temp;
            } else if (it.first->returnType() == 1) {
                vessapaperi += temp;
            } else if (it.first->returnType() == 2) {
                maskit += temp;
            }
            updateResource();
        }
    }
}

void MainWindow::resetResources()
{
    // reset's resources to 0.
    for (auto it : resourseandtext) {
        it.first->returnResource();
    }
}

void MainWindow::addResourceLocations()
{
    // initilizes resource locations for game.
    int i = 1;
    for (auto it : resourcelocations_) {
        Resource* item = new Resource(it.first,it.second, i/5);
        map->addItem(item);
        QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem();
        text->setPos(it.first + 17 - 25, it.second - 10 - 25);
        map->addItem(text);
        resourseandtext.push_back({item,text});
        ++i;
    }
    updateResource();
}

void MainWindow::updateResource()
{
    // update visual's aka Text objective.
    for (auto it : resourseandtext) {
        it.second->setText(QString::number(it.first->resourceAmount()));
    }
}

void MainWindow::addResource()
{
    // Add resources to map.
    for (auto it : resourseandtext) {
        int multiplier = 1;
        if (it.first->returnType() == 0) multiplier = useUpgrade(0);
        if (it.first->returnType() == 1) multiplier = useUpgrade(1);
        if (it.first->returnType() == 2) multiplier = useUpgrade(2);
        it.first->addResouce(1 * multiplier);
    }
    updateResource();
}

}

void Vesa::MainWindow::on_Playmusic_clicked()
{
    // Play music so you can enjoy this game more. :)
    if (ui->Playmusic->text()=="Play music") {
        ui->Playmusic->setText("Mute music");
        song->play();
    } else {
        song->stop();
        ui->Playmusic->setText("Play music");
    }
}


void Vesa::MainWindow::on_up1_clicked()
{
    if (kasidesi >= 10 && vessapaperi >= 10 && maskit >= 10) {
        kasidesi -= 10;
        vessapaperi -= 10;
        maskit -= 10;
        upgrade(0);
    }
}

void Vesa::MainWindow::on_up2_clicked()
{
    if (kasidesi >= 10 && vessapaperi >= 10 && maskit >= 10) {
        kasidesi -= 10;
        vessapaperi -= 10;
        maskit -= 10;
        upgrade(1);
    }
}

void Vesa::MainWindow::on_up3_clicked()
{
    if (kasidesi >= 10 && vessapaperi >= 10 && maskit >= 10) {
        kasidesi -= 10;
        vessapaperi -= 10;
        maskit -= 10;
        upgrade(2);
    }
}

void Vesa::MainWindow::on_up4_clicked()
{
    if (kasidesi >= 10 && vessapaperi >= 10 && maskit >= 10) {
        kasidesi -= 10;
        vessapaperi -= 10;
        maskit -= 10;
        upgrade(3);
    }
}

void Vesa::MainWindow::on_up5_clicked()
{
    if (kasidesi >= 10 && vessapaperi >= 10 && maskit >= 10) {
        kasidesi -= 10;
        vessapaperi -= 10;
        maskit -= 10;
        upgrade(4);
    }
}
