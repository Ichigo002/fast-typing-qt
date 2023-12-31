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

void win::load_sample_file(const QString &filename)
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

    sample_text_list = sample_settings.non_letter_mode ?
                non_letters_remover3070(tmps) : tmps.split(" ");

    if(sample_settings.randomize_mode)
    {
        sample_text_list = randomize_sample(sample_text_list);
    }
}

QStringList win::randomize_sample(const QStringList &sample_l)
{
    QStringList r;
    int sleng = sample_l.length();

    int rv;
    for (int i = 0; i < sample_settings.number_rand_words; i++)
    {
        rv = QRandomGenerator::global()->bounded(0, sleng);
        r += sample_l[rv];
    }

    return r;
}

QStringList win::non_letters_remover3070(const QString &str)
{
    QRegularExpression regex("[^a-zA-Z ]");
    QString s = str;
    s.replace(regex, "");

    return s.split(" ");
}

void win::load_color_settings()
{
    color_correct   = settings->value(SETT_CORR_COLOR, "#00FF00").toString();
    color_incorrect = settings->value(SETT_INCORR_COLOR, "#FF0000").toString();
    color_standart = settings->value(SETT_STD_COLOR, "#FFFFFF").toString();
}

void win::load_all_fucking_settings()
{
    load_color_settings();

    sample_settings.non_letter_mode = settings->value(SETT_MODE_NON_CHARS, false).toBool();
    sample_settings.randomize_mode = settings->value(SETT_RANDOMIZE_SAMPLE, true).toBool();
    sample_settings.number_rand_words = settings->value(SETT_NUMBER_OF_RAND_WORDS, 175).toInt();
}

void win::reset_game()
{
    load_all_fucking_settings();
    input->setText("");
    input->setPlaceholderText("Start Typing");

    running_game = false;
    reset_countdown();
    refresh_countdown_txt();
    prev_line_cword = 0;
    passed_words = 0;
    scrolly = 0;
    scroll_text_view(0);

    past_output = "";

    QString filepath = default_sample_dir + "/" +
                settings->value(SETT_CURR_SAMPLE_FILE, "samples").toString();


    load_sample_file(filepath);

    load_color_settings();
    cword_index = -1;
    refresh_text_view();
    cword_index = 0;


}

void win::refresh_countdown_txt()
{
    int mins = left_time / 60;
    QString need0 = left_time - mins * 60 < 10 ? "0" : "";
    QString txt =
            QString::number(mins) + ":" + need0 + QString::number(left_time - mins * 60) + " left";
    findChild<QLabel*>("label_timer")->setText(txt);
}

void win::reset_countdown()
{
    left_time = start_time;
    if(timerId != -1) {
        killTimer(timerId);
        timerId = -1;
    }
}

void win::start_countdown()
{
    left_time = start_time;
    timerId = startTimer(1000, Qt::TimerType::PreciseTimer);
}

void win::end_gamef(bool timeover)
{
    reset_countdown();

    int ac  = (static_cast<float>(passed_words) / static_cast<float>(cword_index)) * 100;

    end_game* dialog = new end_game();
    dialog->setWPM(cword_index);
    dialog->setAccuracy(ac);
    dialog->exec();

    delete dialog;

    reset_game();
}

QString win::get_word(int index)
{
    return sample_text_list[index];
}

void win::set_cword_status(bool is_correct)
{
    passed_words += is_correct ? 1 : 0;
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

void win::timerEvent(QTimerEvent *event)
{
    left_time--;
    refresh_countdown_txt();
    if(left_time <= 0) {
        end_gamef(true);
    }
}

void win::on_lineEdit_input_textChanged(const QString &arg1)
{
    if(!running_game)
        start_countdown();
        running_game = true;


    input->setPlaceholderText("");

    if(!arg1.contains(' '))
        return;

    if(cword_index >= sample_text_list.length())
        end_gamef();

    set_cword_status(get_word(cword_index) + ' ' == arg1);
    cword_index++;

    scroll_text_view(scrolly);

    if(is_cword_in_next_line())
        scroll_one_line();

    input->setText("");
}






