#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include "labirinth.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labirinth = new Labirinth(8, 8);
    updateTableView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_solve_clicked()
{
    int steps = labirinth->solve();
    updateTableView();
    QMessageBox::warning(this, "Amount fo steps", QString::number(steps));
}

void MainWindow::updateTableView()
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
        updateTableView();
    });
}

void MainWindow::on_clear_clicked()
{
    labirinth->clear();
    updateTableView();
}
