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

struct SampleSettings {
public:
    bool randomize_mode;
    bool non_letter_mode;
    int number_rand_words;
};


class def_sample_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit def_sample_dialog(QWidget *parent = nullptr);
    ~def_sample_dialog();

    void set_current_file(QString filename);
    QFileInfo get_chosen_file();

    SampleSettings get_current_settings();
    void set_sample_settings(const SampleSettings &s);

    void load_all_samples(const QString dir_path);

private slots:

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:

    Ui::def_sample_dialog *ui;
    QFileInfoList file_list;
    QString curr_filename;
    uint cindex;

};

#endif // DEF_SAMPLE_DIALOG_H
