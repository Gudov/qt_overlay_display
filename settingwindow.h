#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include "mainwindow.h"

#include <QSignalMapper>
#include <QWidget>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = 0);
    ~SettingWindow();

signals:
    void changeRGBA( int r, int g, int b, int a );
    void changeCPUNameEnabled(bool);
    void changeCPUCoreEnabled(bool);

public slots:
    void calcNewRGBA();

private slots:
    void on_color_reset_clicked();

private:
    MainWindow *parent;
    QSignalMapper *signalMapper;

    Ui::SettingWindow *ui;
};

#endif // SETTINGWINDOW_H
