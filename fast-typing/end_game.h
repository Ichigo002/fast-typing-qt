#ifndef END_GAME_H
#define END_GAME_H

#include <QDialog>

namespace Ui {
class end_game;
}

class end_game : public QDialog
{
    Q_OBJECT

public:
    explicit end_game(QWidget *parent = nullptr);
    ~end_game();

    void setWPM(uint wpm);
    void setAccuracy(uint ac); // arg1 is [0;100]

private slots:
    void on_btn_addrec_clicked();

    void on_btn_close_clicked();

private:
    Ui::end_game *ui;
};

#endif // END_GAME_H
