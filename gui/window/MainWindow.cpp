#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(GUIModel & model, SudokuBoardService & service, QWidget *parent)
    : QMainWindow(parent), mModel(model), mService(service)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sudokuTableView->setModel(&mModel);
    ui->sudokuTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->sudokuTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->sudokuTableView->horizontalHeader()->hide();
    ui->sudokuTableView->verticalHeader()->hide();

    QObject::connect(&mModel, &GUIModel::gameWon, this, &MainWindow::gameEnded);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::gameEnded()
{
    QMessageBox msgBox;
    msgBox.setText("Congratulations! You won the game!");
    msgBox.exec();
}
