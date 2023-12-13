#include "end_game.h"
#include "ui_end_game.h"

end_game::end_game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::end_game)
{
    ui->setupUi(this);
}

end_game::~end_game()
{
    delete ui;
}

void end_game::setWPM(uint wpm)
{
    QString s = "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt; font-weight:600; font-style:italic;\"Your </span><span style=\" font-size:26pt; font-weight:600; font-style:italic; text-decoration: underline;\">score</span><span style=\" font-size:26pt; font-weight:600; font-style:italic;\"> is</span></p><p align=\"center\"><span style=\" font-size:26pt; font-weight:600; font-style:italic; color:#9141ac;\">"+QString::number(wpm)+" WPM</span></p><p align=\"center\"><span style=\" font-size:26pt; font-weight:600; font-style:italic; color:#f5c211;\">Congrats! Keep going!</span></p><p align=\"center\"><span style=\" font-size:10pt; font-weight:600; font-style:italic;\">WPM - Words Per Minute</span></p></body></html>";

    findChild<QTextEdit*>("textEdit")->setText(s);
}

void end_game::setAccuracy(uint ac)
{
    findChild<QProgressBar*>("progressBar")->setValue(ac);
}

void end_game::on_btn_addrec_clicked()
{
    accept();
}


void end_game::on_btn_close_clicked()
{
    accept();
}
