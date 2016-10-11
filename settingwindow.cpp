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

    connect( this->ui->check_cpu_name, SIGNAL(clicked(bool)), this, SIGNAL(changeCPUNameEnabled(bool)) );
    connect( this->ui->check_cpu_core, SIGNAL(clicked(bool)), this, SIGNAL(changeCPUCoreEnabled(bool)) );
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

void SettingWindow::on_color_reset_clicked()
{
    emit changeRGBA( 128, 128, 128, 128 );
}
