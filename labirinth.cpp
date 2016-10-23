#include "labirinth.h"

#include <QDebug>
#include <queue>

Labirinth::Labirinth(int w, int h)
    : w(w), h(h)
{
    std::vector<Cell> row(w, Cell::EMPTY);
    map.resize(h, row);
    map[pX][pY] = Cell::PLAYER;
    map[eX][eY] = Cell::EXIT;
}

void Labirinth::setWall(int x, int y)
{
    if (x == pX && y == pY) {
        qWarning() << "Can't put wall and player in one cell";
        return;
    }

    if (x == eX && y == eY) {
        qWarning() << "Can't put wall and exit in one cell";
        return;
    }

    map[y][x] = Cell::WALL;
}

void Labirinth::setPlayer(int x, int y)
{
    map[pY][pX] = Cell::EMPTY;
    map[y][x] = Cell::PLAYER;
    pX = x;
    pY = y;
}

void Labirinth::setExit(int x, int y)
{
    map[eY][eX] = Cell::EMPTY;
    map[y][x] = Cell::EXIT;
    eX = x;
    eY = y;
}

void Labirinth::removeWall(int x, int y)
{
    if (map[y][x] == Cell::WALL) {
        map[y][x] = Cell::EMPTY;
    }
}

void Labirinth::setValue(int x, int y, QString s)
{
    Cell cell = stringToCell(s);
    switch (cell) {
    case Cell::EXIT:
        setExit(x, y);
        break;
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
            Cell cell = map[i][j];
            QString ch = cellToString(cell);
            QStandardItem *item = new QStandardItem(ch);
            model->setItem(i, j, item);
        }
    }

    return model;
}

QString Labirinth::getCh(int x, int y) const
{
    Labirinth::Cell cell = map[y][x];
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
    case Cell::EXIT:
        return QString("E");
    case Cell::EMPTY:
        return QString(" ");
    case Cell::WALL:
        return QString("#");
    case Cell::PLAYER:
        return QString("♜");
    default:
        return QString::number(static_cast<int>(cell));
    }
}

Labirinth::Cell Labirinth::stringToCell(QString ch)
{
    if (ch == "e" || ch == "E")
        return Cell::EXIT;

    if (ch == " " || ch == "")
        return Cell::EMPTY;

    if (ch == "X" || ch == "x")
        return Cell::PLAYER;

    return Cell::WALL;
}

struct Labirinth::Point {
   int x, y;
   Point operator +(Point p) {
       p += *this;
       return p;
   }

   void operator +=(Point p) {
       x += p.x;
       y += p.y;
   }
};

bool Labirinth::pointInMap(Labirinth::Point p)
{
    return 0 <= p.x && p.x < w &&
            0 <= p.y && p.y < h;
}

bool Labirinth::isEmpty(Labirinth::Point p)
{
    return map[p.y][p.x] == Cell::EMPTY;
}

bool Labirinth::isExit(Labirinth::Point p)
{
    return map[p.y][p.x] == Cell::EXIT;
}

int Labirinth::solve()
{
    clear();

    const Labirinth::Point direction[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int steps = w * h;
    std::queue<Point> queue;
    queue.push({pX, pY});

    while (queue.size() != 0) {
        Point p = queue.front();
        queue.pop();
        for (Point d : direction) {
            Point cur = p + d;
            while (pointInMap(cur) && (isEmpty(cur) || isExit(cur))) {
                int step = static_cast<int>(map[p.y][p.x]) + 1;
                if (isExit(cur)) {
                    steps = std::min(step, steps);
                }
                int value = static_cast<int>(map[cur.y][cur.x]);
                if (value != 0 || value >= step) {
                    map[cur.y][cur.x] = static_cast<Cell>(step);
                    queue.push(cur);
                }
                cur += d;
            }
        }
    }

    if (steps == w * h)
        return -1;

    setExit(eX, eY);
    return steps;
}

void Labirinth::clear()
{
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int val = static_cast<int>(map[y][x]);
            if (val > 0) {
                map[y][x] = Cell::EMPTY;
            }
        }
    }
}
