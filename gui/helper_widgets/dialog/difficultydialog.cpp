#include "difficultydialog.h"
#include "ui_difficultydialog.h"

DifficultyDialog::DifficultyDialog(QWidget * parent) : QDialog(parent), ui(new Ui::DifficultyDialog)
{
    difficulty = "easy";
    ui->setupUi(this);
    QObject::connect(ui->startButton, &QPushButton::clicked, this, &DifficultyDialog::finalSetUp);
}

std::string DifficultyDialog::getDifficulty()
{
    return difficulty;
}

DifficultyDialog::~DifficultyDialog()
{
    delete ui;
}

void DifficultyDialog::finalSetUp()
{
    difficulty = ui->difficultySetting->currentText().toStdString();
    QDialog::done(QDialog::Accepted);
}
