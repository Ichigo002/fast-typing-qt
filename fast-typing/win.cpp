#include "win.h"
#include "ui_win.h"

win::win(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::win)
{
    ui->setupUi(this);

    settings = new QSettings("settings.ini");

    QString filepath = "samples/" + settings->value(SETT_CURR_SAMPLE_FILE).toString();
    load_sample_file(filepath);
    reset_game();
}

win::~win()
{
    delete ui;
}

void win::load_sample_file(const QString filename)
{
    QFile file(filename);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        sample_txt = in.readAll();
        file.close();
    }
    else
    {
        qDebug() << "Failed to open the file sample: " << filename;
        qDebug() << "Creating default short sample";

        sample_txt = "Failed to open last chosen sample: " + filename +
                ". Go to Menu -> Choose Sample. Or you can type this text ;)";
    }
}

void win::reset_text_view()
{
    QTextEdit *te = findChild<QTextEdit*>("textEdit_output");

    te->setHtml(sample_txt);
}

void win::reset_game()
{
    reset_text_view();
}






