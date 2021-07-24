#ifndef CHRONOUI_H
#define CHRONOUI_H

#include <QElapsedTimer>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QWidget>


class Chronometer
{
    QElapsedTimer t;
  public:
    void restart() { t.restart(); }
    QTime getTime() { return QTime(0,0).addMSecs(t.elapsed()); }
};

class ChronoUI : public QWidget
{
    Q_OBJECT
    Chronometer c;
    QTimer t;
    QLabel * l;
  public:
    ChronoUI(QWidget * parent = nullptr) : QWidget(parent)
    {
        l = new QLabel(this);
        l->setText("Time : " + QTime(0, 0).toString());
        connect(&t, SIGNAL(timeout()), this, SLOT(updateTime()));
    }
    int getTimeMinutes()
    {
        auto takenTime = c.getTime();
        return takenTime.hour() * 60 + takenTime.minute();
    }
  public slots:
    void updateTime()
    {
        l->setText("Time : " + c.getTime().toString());
    }
    void start()
    {
      l->setText("Time : " + QTime(0, 0).toString());
      c.restart();
      t.start(100);
    }
};

#endif // CHRONOUI_H
