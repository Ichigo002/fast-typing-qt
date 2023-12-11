#ifndef DEF_SAMPLE_DIALOG_H
#define DEF_SAMPLE_DIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QString>
#include <QDir>
#include <QFileInfoList>
#include <QStringList>

namespace Ui {
class def_sample_dialog;
}

class def_sample_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit def_sample_dialog(QWidget *parent = nullptr);
    ~def_sample_dialog();

    QFileInfo get_chosen_file();

private slots:

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:

    void load_all_samples(const QString dir_path);

    Ui::def_sample_dialog *ui;
    QFileInfoList file_list;
    uint cindex;

};

#endif // DEF_SAMPLE_DIALOG_H
