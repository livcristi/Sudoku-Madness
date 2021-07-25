#include "chronoui.h"

void Chronometer::restart()
{
    mTimer.restart();
}

QTime Chronometer::getTime()
{
    return QTime(0,0).addMSecs(mTimer.elapsed());
}

ChronoUI::ChronoUI(QWidget * parent) : QWidget(parent)
{
    mTimeLabel = new QLabel(this);

    mTimeLabel->setText("Time: 0 S");
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
    mTimeLabel->setText("Time: 0 S");
    mChronometer.restart();
    mTimer.start(100);
}

QString ChronoUI::getTimeString()
{
    QString resultTime = "Time: ";
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
