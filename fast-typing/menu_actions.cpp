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

    defsam_dialog->exec();

    load_sample_file(defsam_dialog->get_chosen_file().filePath());
    reset_game();
    //qDebug() <<"result: "<< QString::number(result);
    //qDebug() << "Filename: " << defsam_dialog->get_chosen_file();


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


