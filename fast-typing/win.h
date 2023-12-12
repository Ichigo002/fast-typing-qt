#ifndef WIN_H
#define WIN_H

#include <QMainWindow>
#include "def_sample_dialog.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QSettings>

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

private:
    void load_sample_file(const QString filename);
    void reset_text_view();
    void reset_game();

    void load_settings();
    void save_settings();

    // Change this later when you add QSettings!
    QString get_def_sample_filepath() { return "samples/default_sample.txt"; }

    Ui::win *ui;
    QString sample_txt;
    QString default_sample_dir = "samples";

private:
    /*Settings section:*/
    QSettings *settings;
#define SETT_CURR_SAMPLE_FILE "current_sample_filename"


};
#endif // WIN_H
