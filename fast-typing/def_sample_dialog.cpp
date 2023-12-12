#include "def_sample_dialog.h"
#include "ui_def_sample_dialog.h"
#include <QDebug>

def_sample_dialog::def_sample_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::def_sample_dialog)
{
    ui->setupUi(this);

}

def_sample_dialog::~def_sample_dialog()
{
    delete ui;
}

void def_sample_dialog::set_current_file(QString filename)
{
    curr_filename = filename;
}

QFileInfo def_sample_dialog::get_chosen_file()
{
    return file_list[cindex];
}

void def_sample_dialog::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    cindex = current->data(Qt::UserRole).toUInt();
}

void def_sample_dialog::load_all_samples(const QString dir_path)
{
    QDir directory(dir_path);

    QStringList name_filters;
    name_filters.append("*.txt");

    directory.setNameFilters(name_filters);
    directory.setFilter(QDir::Files | QDir::NoDotAndDotDot);

    file_list = directory.entryInfoList();

    QListWidget *list_widget = findChild<QListWidget*>("listWidget");

    int i = 0;
    QListWidgetItem *citem = nullptr;

    foreach (const QFileInfo &fileInfo, file_list)
    {
        //qDebug() << "File Name:" << fileInfo.fileName();
        //qDebug() << "Absolute Path:" << fileInfo.absoluteFilePath();
        //qDebug() << "Size:" << fileInfo.size() << "bytes";
        //qDebug() << "-------------------";

        QListWidgetItem* item = new QListWidgetItem();

        item->setText(fileInfo.fileName());
        item->setData(Qt::UserRole, QVariant(i));

        if(fileInfo.fileName() == curr_filename)
            citem = item;

        list_widget->addItem(item);
        i++;
    }

    if(citem)
        list_widget->setCurrentItem(citem);
    else
        list_widget->setCurrentRow(0);
}

