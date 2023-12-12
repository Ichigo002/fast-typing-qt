#ifndef WIN_H
#define WIN_H

#include <QMainWindow>
#include "def_sample_dialog.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class win; }
QT_END_NAMESPACE

class win : public QMainWindow
{
    Q_OBJECT

public:
    win(QWidget *parent = nullptr);
    ~win();

private slots:
    void on_actionBest_Records_triggered();

    void on_actionText_Settings_triggered();

    void on_actionQuit_triggered();

    void on_actionChoose_Sample_triggered();

    void on_actionHelp_triggered();

    void on_actionHelp_2_triggered();

    void on_lineEdit_input_textChanged(const QString &arg1);

private:
    void load_sample_file(const QString filename);
    void reset_text_view();
    void reset_game();
    void end_game();

    QString get_word(int index);
    void set_cword_status(bool is_correct);
    void refresh_text_view();

    Ui::win *ui;
    QString default_sample_dir = "samples";

    bool running_game;
    int cword_index; //current word index
    QStringList sample_text_list; // list of each word in sample
    QString past_output; // html code coloring last correct or incorrect words.
    QTextEdit* output;

    QString color_correct = "green";
    QString color_incorrect = "red";
    QString color_standart = "white";
    uint font_size_pt = 36;

private:
    /*Settings section:*/
    QSettings *settings;
#define SETT_CURR_SAMPLE_FILE "current_sample_filename"


};
#endif // WIN_H
