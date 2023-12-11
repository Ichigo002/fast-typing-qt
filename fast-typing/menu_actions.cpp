#include "win.h"
#include <QLabel>
#include <QApplication>


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


void win::on_actionChoose_Default_Samples_triggered()
{

}


void win::on_actionLoad_Custom_Sample_triggered()
{

}


void win::on_actionHelp_triggered()
{

}


void win::on_actionHelp_2_triggered()
{

}


