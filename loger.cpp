#include "loger.h"

#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QBrush>
#include <QSize>

#include <iostream>

loger::loger( QWidget *parent )
    : QWidget( parent )
{
    for( int i = 0; i < 100; i++ )
    {
        pos.append(1);
    }

    step = 0;

    this->color = QColor( 0x5f, 0x5f, 0x5f, 0x30 );
}

void loger::push( int number )
{
    step = (step + 1) % 100;
    this->pos[step] = number;
    this->repaint();
}

void loger::setColorRGBA( int r, int g, int b, int a )
{
    this->color = QColor( r, g, b, a );
}

void loger::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //QColor penColor(0x5f, 0x5f, 0x5f, 0x30);
    QPen pen( this->color, 2, Qt::SolidLine, Qt::RoundCap );
    painter.setPen( pen );

    QSize size = this->size();

    float partOfH = (float)size.height() / (float)100 ;

    float partOfW = ((float)size.width()) / (float)100;
    int current;

    for( int i = 0; i < 99; i++ )
    {
        painter.drawLine(
                            partOfW*i, (100 - pos[ (i+step+1) % 100 ]) * partOfH,
                            partOfW*(i+1), (100 - pos[ (i+step+2) % 100 ]) * partOfH
                        );
    }
}
