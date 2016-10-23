#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Labirinth;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateMap();

private:
    Labirinth *labirinth;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
