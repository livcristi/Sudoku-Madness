#include "chronoui.h"

#include <QGraphicsDropShadowEffect>

Chronometer::Chronometer(int seconds) : elapsedSeconds(seconds), isStopped(true)
{}

void Chronometer::restart()
{
    elapsedSeconds = 0;
    mTimer.restart();
}

QTime Chronometer::getTime()
{
    if(isStopped)
        return {elapsedSeconds / 3600, (elapsedSeconds % 3600) / 60, elapsedSeconds % 60};
    else
        return QTime(elapsedSeconds / 3600, (elapsedSeconds % 3600) / 60, elapsedSeconds % 60).addMSecs((int)mTimer.elapsed());
}

void Chronometer::start()
{
    isStopped = false;
    mTimer.restart();
}

void Chronometer::stop()
{
    isStopped = true;
    elapsedSeconds += (int) mTimer.elapsed() / 1000;
}

ChronoUI::ChronoUI(int seconds, QWidget * parent) : QWidget(parent), savedSeconds(seconds)
{
    mChronometer = Chronometer(savedSeconds);

    mTimeLabel = new QLabel(this);
    mTimeLabel->setStyleSheet("font: 18pt \"Cooper Black\";background-color: rgba(173, 173, 173, 0);color: beige;");
    mTimeLabel->setMinimumWidth(200);
    auto labelEffect = new QGraphicsDropShadowEffect();
    labelEffect->setOffset(-1, -2);
    labelEffect->setColor(Qt::black);
    mTimeLabel->setGraphicsEffect(labelEffect);

    mTimeLabel->setText("0 S");
    connect(&mTimer, &QTimer::timeout, this, &ChronoUI::updateTime);
}

int ChronoUI::getTimeMinutes()
{
    auto takenTime = mChronometer.getTime();
    return takenTime.hour() * 60 + takenTime.minute();
}

void ChronoUI::updateTime()
{
    mTimeLabel->setText(getTimeString());
}

void ChronoUI::start()
{
    mChronometer.start();
    updateTime();
    mTimer.start(100);
}

QString ChronoUI::getTimeString()
{
    QString resultTime = "";
    auto takenTime = mChronometer.getTime();
    int hours = takenTime.hour();
    if(hours > 0)
    {
        resultTime += QString::number(hours) + " H ";
    }
    int minutes = takenTime.minute();
    if(minutes > 0)
    {
        resultTime += QString::number(minutes) + " M ";
    }
    int seconds = takenTime.second();
    resultTime += QString::number(seconds) + " S ";
    return resultTime;
}

void ChronoUI::stop()
{
    mChronometer.stop();
}

void ChronoUI::restart()
{
    mTimeLabel->setText("0 S");
    mChronometer.restart();
    mTimer.start(100);
}

void ChronoUI::addSeconds(int seconds)
{
    savedSeconds = seconds;
    mChronometer = Chronometer(seconds);
}

int ChronoUI::getTimeSeconds()
{
    auto chronoTime = mChronometer.getTime();
    return chronoTime.hour() * 3600 + chronoTime.minute() * 60 + chronoTime.second();
}
