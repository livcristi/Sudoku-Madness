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
    this->resize(300, 300);

    this->tableView = new QTableView();
    this->tableView->setModel(&mModel);
    this->tableView->resizeColumnsToContents();
    this->tableView->horizontalHeader()->hide();
    this->tableView->verticalHeader()->hide();

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tableView);
}
