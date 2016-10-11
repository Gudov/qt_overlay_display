#include "mainwindow.h"
#include <QApplication>
#include "widget.h"
#include "settingwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    SettingWindow setting;

    QObject::connect( &w, SIGNAL(showSettings()), &setting, SLOT(show()) );
    QObject::connect( &setting, SIGNAL(changeRGBA(int,int,int,int)), &w, SLOT(setNewRGBA(int,int,int,int)) );
    QObject::connect( &setting, SIGNAL(changeCPUNameEnabled(bool)), &w, SLOT(setCPUNameEnabled(bool)) );
    QObject::connect( &setting, SIGNAL(changeCPUCoreEnabled(bool)), &w, SLOT(setCPUCoreEnabled(bool)) );

    return a.exec();
}
