#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "labirinth.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labirinth = new Labirinth(5, 5);
    updateMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateMap()
{
    delete ui->tableView->model();
    QStandardItemModel *model = labirinth->getModel();
    ui->tableView->setModel(model);

    connect(model, &QStandardItemModel::itemChanged, this,
            [=](QStandardItem *item) {
        QVariant var = item->data(Qt::DisplayRole);
        QString ch = var.toString();
        int y = item->row();
        int x = item->column();
        labirinth->setValue(x, y, ch);
        updateMap();
    });
}
