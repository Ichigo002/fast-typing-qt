#ifndef WIN_H
#define WIN_H

#include <QMainWindow>
#include "def_sample_dialog.h"
#include "text_settings.h"
#include "end_game.h"
#include "about.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QTextEdit>
#include <QScrollBar>
#include <QFontMetrics>
#include <QRandomGenerator>
#include <QRegularExpression>
#include <QString>

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

    void on_lineEdit_input_textChanged(const QString &arg1);

private:
    void load_sample_file(const QString &filename);
    QStringList randomize_sample(const QStringList &sample_l);
    QStringList non_letters_remover3070(const QString &str);
    void reset_text_view();
    void load_color_settings();
    void load_all_fucking_settings();
    void reset_game();
    void refresh_countdown_txt();
    void reset_countdown();
    void start_countdown();
    void end_gamef(bool time_over = false);

    QString get_word(int index);
    void set_cword_status(bool is_correct);
    void refresh_text_view();
    void scroll_text_view(int v);
    void scroll_one_line();
    bool is_cword_in_next_line();

    Ui::win *ui;
    QString default_sample_dir = "samples";

    int timerId = -1;
    int left_time;
    int start_time = 60; // value in seconds [shall always be 60s to accurate take measurements]

    SampleSettings sample_settings;

    bool running_game;
    int cword_index; //current word index
    int passed_words; // amount of passed correctly words
    QStringList sample_text_list; // list of each word in sample
    QString past_output; // html code coloring last correct or incorrect words.
    QTextEdit* output;
    QLineEdit* input;

    QString color_correct = "green";
    QString color_incorrect = "red";
    QString color_standart = "white";
    uint font_size_pt =36;
    int scrolly;
    int scroll_factor = 55; // 36pt = 55px
    int prev_line_cword; // used to scroll content
    int text_viewport_width_px = 230; // do not change because you can break jumping to next line :)

private:
    /*Settings section:*/
    QSettings *settings;
#define SETT_CURR_SAMPLE_FILE "current_sample_filename"
#define SETT_RANDOMIZE_SAMPLE "randomize_sample_file"
#define SETT_MODE_NON_CHARS   "mode_non_letter_characters"
#define SETT_NUMBER_OF_RAND_WORDS "amount_of_random_sample"

#define SETT_CORR_COLOR "correct_text_color"
#define SETT_INCORR_COLOR "incorrect_text_color"
#define SETT_STD_COLOR "standard_text_color"

protected:
    void timerEvent(QTimerEvent *event);

};
#endif // WIN_H
