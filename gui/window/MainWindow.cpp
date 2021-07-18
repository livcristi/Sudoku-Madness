//
// Created by tereb on 16.07.2021.
//

#include <QVBoxLayout>
#include <QHeaderView>
#include "MainWindow.h"

MainWindow::MainWindow(SudokuBoardService &service, GUIModel &model, QWidget *parent) :
QWidget(parent), mService(service), mModel(model)
{
    this->initGUI();
}

void MainWindow::initGUI()
{
    this->resize(800, 600);

    this->tableView = new QTableView();
    this->difficultySetting = new QComboBox();
    this->bombsMenu = new QLabel("Bomb shop");

    // Set-up the table view
    this->tableView->setModel(&mModel);
    this->tableView->resizeColumnsToContents();
    this->tableView->horizontalHeader()->hide();
    this->tableView->verticalHeader()->hide();

    // Set-up the combo box
    difficultySetting->addItem("Easy");
    difficultySetting->addItem("Medium");
    difficultySetting->addItem("Hard");

    auto mainLayout = new QVBoxLayout(this);

    auto playLayout = new QHBoxLayout();
    playLayout->addWidget(tableView);
    auto playRightLayout = new QVBoxLayout();
    playRightLayout->addWidget(difficultySetting);
    playRightLayout->addWidget(bombsMenu);
    playLayout->addLayout(playRightLayout);

    mainLayout->addLayout(playLayout);
}
