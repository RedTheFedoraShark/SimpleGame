#include "window.h"
#include "Game.h"
#include "qcoreevent.h"
#include "qevent.h"
#include <QDebug>

window::window() {
    this->RES_X = 800;
    this->RES_Y = 600;
    this->TILE_SIZE = 100;
    this->MAP_SIZE = 7;
    this->scene = new QGraphicsScene();
    this->view  = new QGraphicsView();
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene);
    this->game = new Game(TILE_SIZE, MAP_SIZE, RES_X, RES_Y, scene);
    view->installEventFilter(game);
    view->setMinimumWidth(RES_X);
    view->setMinimumHeight(RES_Y);
    view->setSceneRect(0, 0, RES_X - 5,  RES_Y - 5);
    view->setBackgroundBrush(Qt::black);
    view->show();
    this->connect(this->game, &Game::gameOver, this, &window::gameOver);
}

void window::gameOver()
{
    this->addGameOverMessage();
    this->updateGameOverMessage();
    this->view->removeEventFilter(game);
    this->game->cleanUp();
    delete this->game;
    this->updateGameOverMessagePos();
    this->scene->update();
    this->view->installEventFilter(this);
}

void window::playAgain()
{
    this->deleteGameOverMessage();
    this->view->removeEventFilter(this);
    this->game = new Game(100, 7, 800, 600, this->scene);
    this->view->installEventFilter(this->game);
    this->connect(this->game, &Game::gameOver, this, &window::gameOver);
}

/*
    I don't understand why splitting managing gameTextItem into many subtasks minimises crashing
    but it does. If it works, it works.
    Unltil it doesn't. I don't entirely understand why it's crashing.
    I wasn't able to track down why and when after two hours. Just sometimes, on death, game crashes.
    I think it's because of Qt, not me
*/

void window::addGameOverMessage()
{
    this->gameOverMessage = new gameTextItem();
    this->scene->addItem(this->gameOverMessage);
}

void window::updateGameOverMessage()
{
    int player_points = this->game->getScore();
    QString message = "You have been defeated!\nYour final score: ";
    message = message + QString::number(player_points);
    message = message + "\n\nTo play again please hit ENTER";
    this->gameOverMessage->setText(message);
}

void window::deleteGameOverMessage()
{
    this->scene->removeItem(this->gameOverMessage);
    delete this->gameOverMessage;
}

void window::updateGameOverMessagePos()
{
    int x = RES_X/2 - this->gameOverMessage->boundingRect().width()/2;
    int y = RES_Y/2 - this->gameOverMessage->boundingRect().height()/2;
    this->gameOverMessage->setPos(x, y);
}

bool window::eventFilter(QObject *object, QEvent *event)
{
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = (QKeyEvent*)event;
        switch(key->key())
        {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            this->playAgain();
            return true;
        default:
            return QObject::eventFilter(object, event);
        }
    }
    return QObject::eventFilter(object, event);
}
