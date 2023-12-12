#include "win.h"
#include "ui_win.h"

win::win(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::win)
{
    ui->setupUi(this);

    settings = new QSettings("settings.ini");

    output = findChild<QTextEdit*>("textEdit_output");
    input  = findChild<QLineEdit*>("lineEdit_input");

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
    prev_line_cword = 0;
    scrolly = 0;
    scroll_text_view(0);

    past_output = "";

    QString filepath = default_sample_dir + "/" +
                settings->value(SETT_CURR_SAMPLE_FILE).toString();
    load_sample_file(filepath);

    cword_index = -1;
    refresh_text_view();
    cword_index = 0;
    input->setText("");
    input->setPlaceholderText("Start Typing");

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

void win::scroll_text_view(int v)
{
    QScrollBar * scb = output->verticalScrollBar();
    //qDebug() << "maxv: " << scb->maximum();
    scb->setValue(v);
}

void win::scroll_one_line()
{
    scrolly += scroll_factor;
    scroll_text_view(scrolly);
}

bool win::is_cword_in_next_line()
{
    QFontMetrics font_metrics(output->font());

    QString targetWords = "";

    for(int i = prev_line_cword; i < cword_index; i++)
    {
        targetWords += sample_text_list[i] + " ";
    }

    int wordsWidth = font_metrics.horizontalAdvance(targetWords);
    if((wordsWidth / text_viewport_width_px) >= 1)
    {
        prev_line_cword = cword_index-1;
        return true;
    } else {
        return false;
    }
}

void win::on_lineEdit_input_textChanged(const QString &arg1)
{
    running_game = true;
    input->setPlaceholderText("");

    if(!arg1.contains(' '))
        return;

    if(cword_index >= sample_text_list.length())
        end_game();

    set_cword_status(get_word(cword_index) + ' ' == arg1);
    cword_index++;

    scroll_text_view(scrolly);

    if(is_cword_in_next_line())
        scroll_one_line();

    input->setText("");
}






