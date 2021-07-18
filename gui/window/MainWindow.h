//
// Created by tereb on 16.07.2021.
//

#ifndef SUDOKU_MADNESS_MAINWINDOW_H
#define SUDOKU_MADNESS_MAINWINDOW_H


#include <QMainWindow>
#include <QWidget>
#include <QTableView>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include "../model/GUIModel.h"


class MainWindow : public QWidget
{
private:
    GUIModel & mModel;
    SudokuBoardService & mService;

    // Graphical parts
    QTableView * tableView;
    QComboBox * difficultySetting;
    QLabel * score, * time, * bombsMenu;
    QPushButton * bomb1, bomb2, bomb3;
public:
    MainWindow(SudokuBoardService & service, GUIModel & model, QWidget * parent = nullptr);
private:
    void initGUI();
};


#endif //SUDOKU_MADNESS_MAINWINDOW_H
