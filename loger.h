#ifndef LOGER_H
#define LOGER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVector>
#include <Qtimer>

class loger : public QWidget
{
Q_OBJECT

public:
    loger( QWidget *parent );

    void push( int number );
    void setColorRGBA( int r, int g, int b, int a );

protected:
    void paintEvent(QPaintEvent *event);

    QColor color;
    QVector<int> pos;

    int step;
};

#endif // LOGER_H
