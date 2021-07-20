#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../service/game_service/sudoku_service/SudokuBoardService.h"
#include "../model/GUIModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    GUIModel & mModel;
    SudokuBoardService & mService;

public:
    MainWindow(GUIModel & model, SudokuBoardService & service, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    void changeDifficulty();
    void bomb1Cell();
    void bomb2Cell();
    void bomb3Cell();

public slots:
    void gameEnded();
};
#endif // MAINWINDOW_H
