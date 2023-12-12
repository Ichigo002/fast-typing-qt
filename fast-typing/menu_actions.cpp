#include "win.h"
#include <QLabel>
#include <QApplication>
#include <QString>

void win::on_actionBest_Records_triggered()
{
    //make new window dialog
    QLabel *timer = findChild<QLabel*>("label_timer");

    timer->setText("9990:00 left");
}

void win::on_actionText_Settings_triggered()
{
    //Make new winodw dialog
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
    //new info dialog
}


void win::on_actionHelp_2_triggered()
{
    //new help dialog
}


