#ifndef CHRONOUI_H
#define CHRONOUI_H

#include <QElapsedTimer>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QWidget>


class Chronometer
{
private:
    int elapsedSeconds;
    QElapsedTimer mTimer;
    bool isStopped;
public:
    explicit Chronometer(int seconds = 0);

    void start();

    void stop();

    void restart();

    QTime getTime();
};

class ChronoUI : public QWidget
{
Q_OBJECT
private:
    Chronometer mChronometer;
    QTimer mTimer;
    QLabel *mTimeLabel;
    int savedSeconds;
public:
    explicit ChronoUI(int seconds = 0, QWidget *parent = nullptr);

    int getTimeMinutes();

    int getTimeSeconds();

    void addSeconds(int seconds);
private:
    QString getTimeString();

public slots:

    void updateTime();

    void start();

    void stop();

    void restart();
};

#endif // CHRONOUI_H
