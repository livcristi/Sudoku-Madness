#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../helper_widgets/dialog/difficultydialog.h"

#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QThread>
#include <iostream>


MainWindow::MainWindow(GUIModel & model, SudokuBoardDelegate & delegate, SudokuBoardService & service,
                       CoinService & coinService, QWidget *parent)
    : QMainWindow(parent), mModel(model), mDelegate(delegate), mService(service), mCoinService(coinService)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sudokuTableView->setModel(&mModel);
    ui->sudokuTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->sudokuTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->sudokuTableView->horizontalHeader()->hide();
    ui->sudokuTableView->verticalHeader()->hide();
    ui->sudokuTableView->setItemDelegate(&mDelegate);
    ui->sudokuTableView->setShowGrid(false);

    //QPixmap bkgnd(":/img/data/background.jpg");
    QPixmap bkgnd(R"(C:\Users\tereb\OneDrive\Desktop\Github-SM\Sudoku-Madness\data\background.jpg)");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
//    this->centralWidget()->setStyleSheet("background-image:url(\":/img/data/background.jpg\"); background-position: center; ");

    ui->coinsLabel->setText("Coins : " + QString::number(this->mCoinService.getCoins()));

    QObject::connect(&mModel, &GUIModel::gameWon, this, &MainWindow::gameEnded);
    QObject::connect(ui->pushButton, &QPushButton::clicked, this, [=](){this->bombCell(1);});
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, [=](){this->bombCell(2);});
    QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, [=](){this->bombCell(3);});
    QObject::connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startNewGame);
    QObject::connect(ui->startNewButton, &QPushButton::clicked, this, &MainWindow::startNewGame);

    ui->continueButton->setDisabled(true);

    QObject::connect(ui->quitButton, &QPushButton::clicked, this, &QMainWindow::close);

    applyDropEffect(ui->menuSudokuLabel, 0);
    applyDropEffect(ui->menuMadnessLabel, 0);
    applyDropEffect(ui->difficultyLabel);
    applyDropEffect(ui->difficultyTextLabel);
    applyDropEffect(ui->bombShopLabel);
    applyDropEffect(ui->grenadePriceLabel);
    applyDropEffect(ui->linePriceLabel);
    applyDropEffect(ui->missilePriceLabel);
    applyDropEffect(ui->coinsLabel);

    this->chronometerWidget = new ChronoUI(this);
    ui->chronometerLayout->addWidget(chronometerWidget);
    this->chronometerWidget->start();
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
        this->chronometerWidget->start();
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
