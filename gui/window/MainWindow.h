#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>
#include "../../service/game_service/sudoku_service/SudokuBoardService.h"
#include "../model/GUIModel.h"
#include "../../service/game_service/money_service/CoinService.h"
#include "../helper_widgets/chronometer/chronoui.h"
#include "../delegate/SudokuBoardDelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    GUIModel & mModel;
    SudokuBoardDelegate & mDelegate;
    SudokuBoardService & mService;
    CoinService & mCoinService;
    ChronoUI * chronometerWidget;
    QStateMachine * machine;

public:
    MainWindow(GUIModel & model, SudokuBoardDelegate & delegate, SudokuBoardService & service, CoinService & coinService, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    void setUpGUI();
    void connectSignalAndSlots();
    void changeDifficulty(const std::string & difficulty);
    void bombCell(int type);
    void applyDropEffect(QLabel * label, int page = 1);
    void showHelpDialog();
    void startStopTimer();
    void continueGame();
    void saveAndQuit();

public slots:
    void gameEnded();
    void startNewGame();
};
#endif // MAINWINDOW_H
