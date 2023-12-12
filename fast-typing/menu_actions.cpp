#include "win.h"
#include <QLabel>
#include <QApplication>
#include <QString>

void win::on_actionBest_Records_triggered()
{
    //make new window dialog
}

void win::on_actionText_Settings_triggered()
{
    text_settings* dialog = new text_settings();

    QString c_hex   = settings->value(SETT_CORR_COLOR, "#00FF00").toString();
    QString inc_hex = settings->value(SETT_INCORR_COLOR, "#FF0000").toString();
    QString std_hex = settings->value(SETT_STD_COLOR, "#FFFFFF").toString();

    dialog->setColors(c_hex, inc_hex, std_hex);

    if(dialog->exec() == QDialog::Rejected)
    {
        delete dialog;
        return;
    }

    settings->setValue(SETT_CORR_COLOR, c_hex);
    settings->setValue(SETT_INCORR_COLOR, inc_hex);
    settings->setValue(SETT_STD_COLOR, std_hex);

    delete dialog;
}


void win::on_actionQuit_triggered()
{
    QCoreApplication::quit();
}


void win::on_actionChoose_Sample_triggered()
{
    def_sample_dialog *defsam_dialog = new def_sample_dialog();

    QString cfile = settings->value(SETT_CURR_SAMPLE_FILE, "").toString();
    defsam_dialog->set_current_file(cfile);
    defsam_dialog->load_all_samples(default_sample_dir);

    int c = defsam_dialog->exec();

    if(c == QDialog::Rejected)
        return;

    QFileInfo chf = defsam_dialog->get_chosen_file();
    settings->setValue(SETT_CURR_SAMPLE_FILE, chf.fileName());

    load_sample_file(chf.filePath());
    reset_game();

    delete defsam_dialog;
}

void win::on_actionHelp_triggered()
{
    about* dialog = new about();

    dialog->exec();

    delete dialog;
}

