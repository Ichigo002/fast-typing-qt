#include "win.h"
#include "ui_win.h"

win::win(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::win)
{
    ui->setupUi(this);

    settings = new QSettings("settings.ini");

    output = findChild<QTextEdit*>("textEdit_output");

    reset_game();
}

win::~win()
{
    delete ui;
}

void win::load_sample_file(const QString filename)
{
    QFile file(filename);
    QString tmps;

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        tmps = in.readAll();
        file.close();
    }
    else
    {
        qDebug() << "Failed to open the file sample: " << filename;
        qDebug() << "Creating default short sample";

        tmps = "Failed to open last chosen sample: " + filename +
                ". Go to Menu -> Choose Sample. Or you can type this text ;)";
    }
    sample_text_list = tmps.split(" ");
}

void win::reset_game()
{
    running_game = false;

    past_output = "";

    QString filepath = default_sample_dir + "/" +
                settings->value(SETT_CURR_SAMPLE_FILE).toString();
    load_sample_file(filepath);

    cword_index = -1;
    refresh_text_view();
    cword_index = 0;
    findChild<QLineEdit*>("lineEdit_input")->setText("");

}

void win::end_game()
{
    qDebug() << "END GAME!!!";
    reset_game();
}

QString win::get_word(int index)
{
    return sample_text_list[index];
}

void win::set_cword_status(bool is_correct)
{
    QString color = is_correct ? color_correct : color_incorrect;

    past_output +=  "<span style=\" font-size:" + QString::number(font_size_pt) +
                    "pt; color:" + color + ";\">" +
                    sample_text_list[cword_index] + " </span>";

    refresh_text_view();
}

void win::refresh_text_view()
{
    QString buff = past_output;
    buff += "<span style=\" font-size:" + QString::number(font_size_pt)+
            "pt; color:" + color_standart + ";\">";

    for(uint i = cword_index+1; i < sample_text_list.length(); i++)
    {
        buff += sample_text_list[i] + " ";
    }

    buff += "</span>";

    output->setText(buff);
}

void win::on_lineEdit_input_textChanged(const QString &arg1)
{
    running_game = true;

    if(!arg1.contains(' '))
        return;

    if(cword_index >= sample_text_list.length())
        end_game();

    set_cword_status(get_word(cword_index) + ' ' == arg1);
    cword_index++;

    findChild<QLineEdit*>("lineEdit_input")->setText("");
}






