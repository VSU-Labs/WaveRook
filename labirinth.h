#ifndef LABIRINTH_H
#define LABIRINTH_H

#include <QModelIndex>
#include <QStandardItemModel>
#include <vector>

class Labirinth
{
public:
    Labirinth(int w, int h);
    void setWall(int x, int y);
    void setPlayer(int x, int y);
    void removeWall(int x, int y);
    void setValue(int x, int y, QString s);
    QStandardItemModel* getModel() const;
    QString getCh(int x, int y) const;
    int getPlayerX() const;
    int getPlayerY() const;

    void solve();

private:
    enum class Cell {
        WALL = -2, PLAYER = -1, EMPTY = 0
    };

    static QString cellToString(Cell cell);
    static Cell stringToCell(QString ch);
    int w, h;
    int pX = 0;
    int pY = 0;
    std::vector<std::vector<Cell>> labirinthMap;
};

#endif // LABIRINTH_H
