//
// Created by tereb on 16.07.2021.
//

#ifndef SUDOKU_MADNESS_MAINWINDOW_H
#define SUDOKU_MADNESS_MAINWINDOW_H


#include <QMainWindow>
#include <QWidget>
#include <QTableView>
#include "../model/GUIModel.h"


class MainWindow : public QWidget
{
private:
    GUIModel & mModel;
    SudokuBoardService & mService;

    QTableView * tableView;
public:
    MainWindow(SudokuBoardService & service, GUIModel & model, QWidget * parent = nullptr);
private:
    void initGUI();
};


#endif //SUDOKU_MADNESS_MAINWINDOW_H
