#ifndef TEXT_SETTINGS_H
#define TEXT_SETTINGS_H

#include <QDialog>

namespace Ui {
class text_settings;
}

class text_settings : public QDialog
{
    Q_OBJECT

public:
    explicit text_settings(QWidget *parent = nullptr);
    ~text_settings();

    void setColors(QString &correct_hex, QString &incorrect_hex, QString &normal_hex);

private:
    Ui::text_settings *ui;
};

#endif // TEXT_SETTINGS_H
