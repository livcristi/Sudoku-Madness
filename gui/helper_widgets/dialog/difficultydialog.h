#ifndef DIFFICULTYDIALOG_H
#define DIFFICULTYDIALOG_H

#include <QDialog>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class DifficultyDialog; }
QT_END_NAMESPACE

class DifficultyDialog : public QDialog
{
    Q_OBJECT
public:
    DifficultyDialog(QWidget *parent = nullptr);
    std::string getDifficulty();
    virtual ~DifficultyDialog();
private:
    Ui::DifficultyDialog *ui;
    std::string difficulty;
    void finalSetUp();
};

#endif // DIFFICULTYDIALOG_H
