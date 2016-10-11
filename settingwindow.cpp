#include "settingwindow.h"
#include "ui_settingwindow.h"

SettingWindow::SettingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);

    SettingWindow *asd = this;

    connect( this->ui->color_r, SIGNAL(valueChanged(int)), this, SLOT(calcNewRGBA()) );
    connect( this->ui->color_g, SIGNAL(valueChanged(int)), this, SLOT(calcNewRGBA()) );
    connect( this->ui->color_b, SIGNAL(valueChanged(int)), this, SLOT(calcNewRGBA()) );
    connect( this->ui->color_a, SIGNAL(valueChanged(int)), this, SLOT(calcNewRGBA()) );
}

void SettingWindow::calcNewRGBA()
{
    int r = this->ui->color_r->value();
    int g = this->ui->color_g->value();
    int b = this->ui->color_b->value();
    int a = this->ui->color_a->value();

    emit changeRGBA( r, g, b, a );
}

SettingWindow::~SettingWindow()
{
    delete ui;
}
