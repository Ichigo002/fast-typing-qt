#ifndef WIN_H
#define WIN_H

#include <QMainWindow>

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

    void on_actionChoose_Default_Samples_triggered();

    void on_actionLoad_Custom_Sample_triggered();

    void on_actionHelp_triggered();

    void on_actionHelp_2_triggered();

private:
    Ui::win *ui;
};
#endif // WIN_H
