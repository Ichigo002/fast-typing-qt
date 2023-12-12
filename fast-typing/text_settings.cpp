#include "text_settings.h"
#include "ui_text_settings.h"

text_settings::text_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::text_settings)
{
    ui->setupUi(this);
}

text_settings::~text_settings()
{
    delete ui;
}

void text_settings::setColors(QString &correct_hex, QString &incorrect_hex, QString &normal_hex)
{

}
