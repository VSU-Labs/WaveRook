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
    void setExit(int x, int y);
    void removeWall(int x, int y);

    void setValue(int x, int y, QString s);
    QStandardItemModel* getModel() const;
    QString getCh(int x, int y) const;
    int getPlayerX() const;
    int getPlayerY() const;

    int solve();
    void clear();

private:
    enum class Cell {
        EXIT = -3, WALL = -2, PLAYER = 0, EMPTY = -1
    };
    struct Point;

    static QString cellToString(Cell cell);
    static Cell stringToCell(QString ch);

    bool pointInMap(Point p);
    bool isEmpty(Point p);
    bool isExit(Point p);
private:
    int w, h;
    int pX = 0;
    int pY = 0;
    int eX = 1;
    int eY = 1;
    std::vector<std::vector<Cell>> map;
};

#endif // LABIRINTH_H
