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

void text_settings::setColors(const QString &correct_hex, const QString &incorrect_hex, const QString &normal_hex)
{
    cor_col.setNamedColor(correct_hex);
    incor_col.setNamedColor(incorrect_hex);
    std_col.setNamedColor(normal_hex);
    update_text_edit();
}

void text_settings::getColors(QString &correct_hex, QString &incorrect_hex, QString &normal_hex)
{
    correct_hex = cor_col.name();
    incorrect_hex = incor_col.name();
    normal_hex = std_col.name();
}

void text_settings::on_btn_correct_change_clicked()
{
    cor_col = get_color_picker(cor_col, "Select Color of the correct text");
    update_text_edit();
}


void text_settings::on_btn_incorrect_change_clicked()
{
    incor_col = get_color_picker(incor_col, "Select Color of the incorrect text");
    update_text_edit();
}


void text_settings::on_btn_normal_change_clicked()
{
    std_col = get_color_picker(std_col, "Select Color of the normal text");
    update_text_edit();
}

void text_settings::update_text_edit()
{
    QString s = "<span style=\" font-size:36pt; color:" + cor_col.name() + ";\">Correct </span>";
     s += "<span style=\" font-size:36pt; color:" + incor_col.name() + ";\">Incorrect </span>";
     s += "<span style=\" font-size:36pt; color:" + std_col.name() + ";\">Normal</span>";

    findChild<QTextEdit*>("textEdit")->setText(s);

}

QColor text_settings::get_color_picker(
        const QColor &current_color,
        const QString &dialog_name)
{
    QColor c = QColorDialog::getColor(current_color, this, dialog_name);

    if(c.isValid()) {
        return c;
    } else
        return current_color;
}


void text_settings::on_btn_reset_clicked()
{
    cor_col.setRgb(0, 200, 0);
    incor_col.setRgb(200, 0, 0);
    std_col.setRgb(250, 250, 250);
    update_text_edit();
}

