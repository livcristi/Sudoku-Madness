#ifndef CHRONOUI_H
#define CHRONOUI_H

#include <QElapsedTimer>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QWidget>


class Chronometer {
private:
    QElapsedTimer mTimer;
public:
    void restart();

    QTime getTime();
};

class ChronoUI : public QWidget {
Q_OBJECT
private:
    Chronometer mChronometer;
    QTimer mTimer;
    QLabel *mTimeLabel;
public:
    explicit ChronoUI(QWidget *parent = nullptr);

    int getTimeMinutes();

private:
    QString getTimeString();

public slots:

    void updateTime();

    void start();
};

#endif // CHRONOUI_H
