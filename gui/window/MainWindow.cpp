#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <iostream>

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
    QObject::connect(ui->difficultySetting, &QComboBox::currentTextChanged, this, &MainWindow::changeDifficulty);
    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::bomb1Cell);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::bomb2Cell);
    QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::bomb3Cell);
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

    // Begin a new game
    this->changeDifficulty();
}

void MainWindow::changeDifficulty()
{
    // Create a new board in the service and update it in the model
    this->mService.createNewBoard(ui->difficultySetting->currentText().toStdString());
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            auto modelIndex = this->mModel.index(i, j);
            emit this->mModel.dataChanged(modelIndex, modelIndex);
        }
    }
}

void MainWindow::bomb1Cell()
{
    int row = ui->sudokuTableView->selectionModel()->currentIndex().row();
    int column = ui->sudokuTableView->selectionModel()->currentIndex().column();

    mService.bombBoard(row, column, 1);
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            auto modelIndex = this->mModel.index(i, j);
            emit this->mModel.dataChanged(modelIndex, modelIndex);
        }
    }
}

void MainWindow::bomb2Cell()
{
    int row = ui->sudokuTableView->selectionModel()->currentIndex().row();
    int column = ui->sudokuTableView->selectionModel()->currentIndex().column();

    mService.bombBoard(row, column, 2);
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            auto modelIndex = this->mModel.index(i, j);
            emit this->mModel.dataChanged(modelIndex, modelIndex);
        }
    }
}

void MainWindow::bomb3Cell()
{
    int row = ui->sudokuTableView->selectionModel()->currentIndex().row();
    int column = ui->sudokuTableView->selectionModel()->currentIndex().column();

    mService.bombBoard(row, column, 3);
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            auto modelIndex = this->mModel.index(i, j);
            emit this->mModel.dataChanged(modelIndex, modelIndex);
        }
    }
}
