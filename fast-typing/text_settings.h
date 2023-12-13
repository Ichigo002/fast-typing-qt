#ifndef TEXT_SETTINGS_H
#define TEXT_SETTINGS_H

#include <QDialog>
#include <QDebug>
#include <QColorDialog>

namespace Ui {
class text_settings;
}

class text_settings : public QDialog
{
    Q_OBJECT

public:
    explicit text_settings(QWidget *parent = nullptr);
    ~text_settings();

    void setColors(const QString &correct_hex, const QString &incorrect_hex, const QString &normal_hex);
    void getColors(QString &correct_hex, QString &incorrect_hex, QString &normal_hex);

private slots:
    void on_btn_correct_change_clicked();

    void on_btn_incorrect_change_clicked();

    void on_btn_normal_change_clicked();

    void on_btn_reset_clicked();

private:
    void update_text_edit();
    QColor get_color_picker(
            const QColor &current_color = QColor(255, 255, 255),
            const QString &dialog_name = "Select Color");

    QColor cor_col, incor_col, std_col;
    Ui::text_settings *ui;
};

#endif // TEXT_SETTINGS_H
