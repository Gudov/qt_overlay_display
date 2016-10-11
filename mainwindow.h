#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSystemTrayIcon>
#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateInfo();
    void showConfig(QSystemTrayIcon::ActivationReason);
    void setNewRGBA( int r, int g, int b, int a );

    void setCPUNameEnabled(bool);
    void setCPUCoreEnabled(bool);

signals:
    void showSettings();

private:
    bool cpu_name_enabled = true;
    bool cpu_core_enabled = true;

    QTimer *updateTimer;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
