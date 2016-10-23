#include "labirinth.h"

#include <QDebug>

Labirinth::Labirinth(int w, int h)
    : w(w), h(h)
{
    std::vector<Cell> row(w, Cell::EMPTY);
    labirinthMap.resize(h, row);
    labirinthMap[pX][pY] = Cell::PLAYER;
}

void Labirinth::setWall(int x, int y)
{
    if (x == pX && y == pY) {
        qWarning() << "Can't put wall and player in one cell";
        return;
    }

    labirinthMap[y][x] = Cell::WALL;
}

void Labirinth::setPlayer(int x, int y)
{
    labirinthMap[pY][pX] = Cell::EMPTY;
    labirinthMap[y][x] = Cell::PLAYER;
    pX = x;
    pY = y;
}

void Labirinth::removeWall(int x, int y)
{
    if (labirinthMap[y][x] == Cell::WALL) {
        labirinthMap[y][x] = Cell::EMPTY;
    }
}

void Labirinth::setValue(int x, int y, QString s)
{
    Cell cell = stringToCell(s);
    switch (cell) {
    case Cell::PLAYER:
        setPlayer(x, y);
        break;
    case Cell::WALL:
        setWall(x, y);
        break;
    case Cell::EMPTY:
        removeWall(x, y);
        break;
    default:
        break;
    }
}

QStandardItemModel* Labirinth::getModel() const
{
    QStandardItemModel *model = new QStandardItemModel();
    model->setRowCount(w);
    model->setColumnCount(h);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            Cell cell = labirinthMap[i][j];
            QString ch = cellToString(cell);
            QStandardItem *item = new QStandardItem(ch);
            model->setItem(i, j, item);
        }
    }

    return model;
}

QString Labirinth::getCh(int x, int y) const
{
    Labirinth::Cell cell = labirinthMap[y][x];
    return cellToString(cell);
}

int Labirinth::getPlayerX() const
{
    return pX;
}

int Labirinth::getPlayerY() const
{
    return pY;
}

QString Labirinth::cellToString(Labirinth::Cell cell)
{
    switch (cell) {
    case Cell::EMPTY:
        return QString(" ");
    case Cell::WALL:
        return QString("#");
    case Cell::PLAYER:
        return QString("♜");
    default:
        return QString(static_cast<int>(cell));
    }
}

Labirinth::Cell Labirinth::stringToCell(QString ch)
{
    if (ch == " " || ch == "")
        return Cell::EMPTY;

    if (ch == "X" || ch == "x")
        return Cell::PLAYER;

    return Cell::WALL;
}
