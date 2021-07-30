#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../helper_widgets/dialog/difficultydialog.h"

#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QThread>
#include <iostream>
#include <QState>
#include <QIcon>


MainWindow::MainWindow(GUIModel & model, SudokuBoardDelegate & delegate, SudokuBoardService & service,
                       CoinService & coinService, QWidget *parent)
    : QMainWindow(parent), mModel(model), mDelegate(delegate), mService(service), mCoinService(coinService)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setUpGUI();
    this->connectSignalAndSlots();
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
    this->mCoinService.addCoins(ui->difficultyTextLabel->text().toStdString(), this->chronometerWidget->getTimeMinutes());
    this->chronometerWidget->stop();
    ui->coinsLabel->setText("Coins : " + QString::number(this->mCoinService.getCoins()));
}

void MainWindow::startNewGame()
{
    // Get the difficulty from the widget
    DifficultyDialog askDialog(this);
    if(askDialog.exec() == QDialog::Accepted)
    {
        // Set to game page
        ui->stackedWidget->setCurrentWidget(ui->gamePage);
        auto difficulty = askDialog.getDifficulty();
        // Change the board
        ui->difficultyTextLabel->setText(QString::fromStdString(difficulty));
        this->changeDifficulty(difficulty);
        // Begin the chronometer
        this->chronometerWidget->restart();
    }
}

void MainWindow::changeDifficulty(const std::string & difficulty)
{
    // Create a new board in the service and update it in the model
    this->mService.createNewBoard(difficulty);
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            auto modelIndex = this->mModel.index(i, j);
            emit this->mModel.dataChanged(modelIndex, modelIndex);
        }
    }
}

void MainWindow::bombCell(int type)
{
    int row = ui->sudokuTableView->selectionModel()->currentIndex().row();
    int column = ui->sudokuTableView->selectionModel()->currentIndex().column();

    // Check if the player has enough coins
    int coins = type == 1 ? 10 : type == 2 ? 20 : 40;
    if(!mCoinService.subtractCoins(coins))
    {
        QMessageBox msgBox;
        msgBox.setText("You do not have enough coins for that bomb");
        msgBox.exec();
        return;
    }
    ui->coinsLabel->setText("Coins : " + QString::number(this->mCoinService.getCoins()));

    mService.bombBoard(row, column, type);
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            auto modelIndex = this->mModel.index(i, j);
            emit this->mModel.dataChanged(modelIndex, modelIndex);
        }
    }

    if(mService.checkWinner())
        gameEnded();
}

void MainWindow::applyDropEffect(QLabel * label, int page)
{
    if(page == 1)
    {
        // Apply on menu page
        auto newLabelEffect = new QGraphicsDropShadowEffect();
        newLabelEffect->setOffset(-2, -2);
        newLabelEffect->setColor(Qt::black);
        label->setGraphicsEffect(newLabelEffect);
    }
    else
    {
        // Apply on game page
        auto newLabelEffect = new QGraphicsDropShadowEffect();
        newLabelEffect->setOffset(-1, -2);
        newLabelEffect->setColor(Qt::black);
        label->setGraphicsEffect(newLabelEffect);
    }
}

void MainWindow::setUpGUI()
{
    this->setWindowTitle("Sudoku Madness");
    this->setWindowIcon(QIcon(":/img/data/icon.jpg"));

    ui->sudokuTableView->setModel(&mModel);
    ui->sudokuTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->sudokuTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->sudokuTableView->horizontalHeader()->hide();
    ui->sudokuTableView->verticalHeader()->hide();
    ui->sudokuTableView->setItemDelegate(&mDelegate);
    ui->sudokuTableView->setShowGrid(false);

    // set the background
    this->setObjectName("CentralWidget");
    this->setStyleSheet("QWidget#CentralWidget{background-image:url(\":/img/data/background.jpg\"); background-position: center;}");

    ui->coinsLabel->setText("Coins : " + QString::number(this->mCoinService.getCoins()));

    applyDropEffect(ui->menuSudokuLabel, 0);
    applyDropEffect(ui->menuMadnessLabel, 0);
    applyDropEffect(ui->difficultyLabel);
    applyDropEffect(ui->difficultyTextLabel);
    applyDropEffect(ui->bombShopLabel);
    applyDropEffect(ui->grenadePriceLabel);
    applyDropEffect(ui->linePriceLabel);
    applyDropEffect(ui->missilePriceLabel);
    applyDropEffect(ui->coinsLabel);

    this->chronometerWidget = new ChronoUI(0, this);
    ui->chronometerLayout->addWidget(chronometerWidget);
    this->chronometerWidget->start();

    // Start stop button
    machine = new QStateMachine(this);
    auto off = new QState();
    off->assignProperty(ui->stopStartButton, "text", "Stop time");
    off->setObjectName("off");

    auto on = new QState();
    on->setObjectName("on");
    on->assignProperty(ui->stopStartButton, "text", "Start time");

    off->addTransition(ui->stopStartButton, &QAbstractButton::clicked, on);
    on->addTransition(ui->stopStartButton, &QAbstractButton::clicked, off);
    machine->addState(off);
    machine->addState(on);
    machine->setInitialState(off);
    machine->start();
}

void MainWindow::connectSignalAndSlots()
{
    QObject::connect(&mModel, &GUIModel::gameWon, this, &MainWindow::gameEnded);
    QObject::connect(ui->pushButton, &QPushButton::clicked, this, [=](){this->bombCell(1);});
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, [=](){this->bombCell(2);});
    QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, [=](){this->bombCell(3);});
    QObject::connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startNewGame);
    QObject::connect(ui->startNewButton, &QPushButton::clicked, this, &MainWindow::startNewGame);

    QObject::connect(ui->quitButton, &QPushButton::clicked, this, &QMainWindow::close);
    QObject::connect(ui->saveQuitButton, &QPushButton::clicked, this, &MainWindow::saveAndQuit);
    QObject::connect(ui->continueButton, &QPushButton::clicked, this, &MainWindow::continueGame);

    QObject::connect(ui->helpButton, &QPushButton::clicked, this, &MainWindow::showHelpDialog);

    // Start stop button
    QObject::connect(ui->stopStartButton, &QPushButton::clicked, this, &MainWindow::startStopTimer);
}

void MainWindow::startStopTimer()
{
    // todo: overcome cheating somehow
    if(ui->stopStartButton->text() == "Stop time")
    {
        this->chronometerWidget->stop();
    }
    else
    {
        this->chronometerWidget->start();
    }
}


void MainWindow::showHelpDialog()
{
    QMessageBox msgBox;
    QString helpTextGame;
    helpTextGame += "The objective of the game is to fill every row, column and grid with unique values ranging from 1 to 9.\n";
    helpTextGame += "Some cells will already contain values, their count depends on the chosen difficulty.\n";
    helpTextGame += "When you enter a value in a cell that already exists on a row, column or grid (eg: two 3s on the first row), ";
    helpTextGame += "then those cells with the equal value will have their text in red. You should avoid this in order to win the game.\n\n";

    QString helpTextBombs;
    helpTextBombs += "You can also bomb cells by purchasing bombs in the shop on the right of the screen. "
    "This will lower the amount of unique cells, giving you more options to solve the table.\n";
    helpTextBombs += "Bombs are bought using coins. You receive coins by completing Sudoku games. The higher the difficulty and lower the time, the more "
    "coins you will receive.\n";
    helpTextBombs += "Relax and have fun!";

    msgBox.setText(helpTextGame + helpTextBombs);
    msgBox.exec();
    return;
}

void MainWindow::continueGame()
{
    int seconds = this->mService.loadGameFromFile();
    if(seconds < 0)
    {
        QMessageBox msgBox;
        msgBox.setText("You must start a new game first!");
        msgBox.exec();
        return;
    }
    else
    {
        ui->stackedWidget->setCurrentWidget(ui->gamePage);
        // Change the board
        ui->difficultyTextLabel->setText(QString::fromStdString(this->mService.getCurrentDifficulty()));
        this->chronometerWidget->addSeconds(seconds);
        this->chronometerWidget->start();
    }
}

void MainWindow::saveAndQuit()
{
    int seconds = chronometerWidget->getTimeSeconds();
    this->mService.saveGameToFile(seconds);
    this->close();
}
