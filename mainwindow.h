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

signals:
    void showSettings();

private:
    QTimer *updateTimer;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
