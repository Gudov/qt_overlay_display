#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cpu_memory.h"
#include "settingwindow.h"

#include <QSystemTrayIcon>
#include <QPalette>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    QRect desktopSize = QApplication::desktop()->screen()->rect();

    QRect geom = this->geometry();

    this->setGeometry( (desktopSize.width() / 2) - (geom.width()/2) - 100, 0, geom.width(), geom.height() );

    updateTimer = new QTimer(this);
    updateTimer->start(250);

    QObject::connect( updateTimer, SIGNAL(timeout()), this, SLOT(updateInfo()) );

    QSystemTrayIcon *trIcon;
    trIcon = new QSystemTrayIcon();  //инициализируем объект
    trIcon->setIcon(QIcon(":/img/icon.png"));  //устанавливаем иконку
    trIcon->show();  //отображаем объект

    QObject::connect( trIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(showConfig(QSystemTrayIcon::ActivationReason)) );

    emit setNewRGBA(128,128,128,128);
}

void MainWindow::showConfig(QSystemTrayIcon::ActivationReason reason)
{
    if( reason == QSystemTrayIcon::Trigger )
    {
        emit showSettings();
    }
}

void MainWindow::setNewRGBA( int r, int g, int b, int a )
{
    this->ui->cpu_loger->setColorRGBA( r, g, b, a );
    this->ui->memory_loger->setColorRGBA( r, g, b, a );

    QString rgba;
    rgba.append("rgba(");
    rgba.append(QString::number(r));
    rgba.append(", ");
    rgba.append(QString::number(g));
    rgba.append(", ");
    rgba.append(QString::number(b));
    rgba.append(", ");
    rgba.append(QString::number( (a*2 > 255) ? (255) : (a*2) ));
    rgba.append(")");

    this->ui->cpu_max_persent->setStyleSheet("QLabel { color : " + rgba + "; }");
    this->ui->cpu_name->setStyleSheet("QLabel { color : " + rgba + "; }");
    this->ui->cpu_core->setStyleSheet("QLabel { color : " + rgba + "; }");
    this->ui->cpu_min_persent->setStyleSheet("QLabel { color : " + rgba + "; }");
    this->ui->memory_max_persent->setStyleSheet("QLabel { color : " + rgba + "; }");
    this->ui->memory_min_persent->setStyleSheet("QLabel { color : " + rgba + "; }");
    this->ui->memory_now->setStyleSheet("QLabel { color : " + rgba + "; }");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInfo()
{
    this->ui->cpu_loger->push( GetCPULoad() * 100 );
    QString rawCpuName = getCPUName();
    this->ui->cpu_name->setText( (rawCpuName.split("@"))[0] );

    this->ui->cpu_core->setText( QString("core: ") + QString::number( getCpuCoreCount() ) + "  clock: " + (rawCpuName.split("@"))[1] );

    MEMORYSTATUSEX memory_state = getMemoryState();

    this->ui->memory_loger->push( memory_state.dwMemoryLoad );
    this->ui->memory_now->setGeometry( 1000, 75 - (memory_state.dwMemoryLoad * 0.75), 47, 20 );

    if( memory_state.ullTotalPhys/DIV > 1024 )
    {
        this->ui->memory_max_persent->setText( QString::number( (memory_state.ullTotalPhys/(DIV*1024)) + 1 ) + "GB" );
    }
    else
    {
        this->ui->memory_max_persent->setText( QString::number( memory_state.ullTotalPhys/DIV ) + "MB" );
    }

    if( (memory_state.ullTotalPhys - memory_state.ullAvailPhys)/DIV > 1024 )
    {
        this->ui->memory_now->setText( QString::number( ((memory_state.ullTotalPhys - memory_state.ullAvailPhys)/(DIV*1024)) + 1 ) + "GB" );
    }
    else
    {
        this->ui->memory_now->setText( QString::number( (memory_state.ullTotalPhys - memory_state.ullAvailPhys)/DIV ) + "MB" );
    }


}
