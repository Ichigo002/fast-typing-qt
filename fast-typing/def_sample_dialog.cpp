#include "def_sample_dialog.h"
#include "ui_def_sample_dialog.h"
#include <QDebug>

def_sample_dialog::def_sample_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::def_sample_dialog)
{
    ui->setupUi(this);

    load_all_samples("samples");
}

def_sample_dialog::~def_sample_dialog()
{
    delete ui;
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
    foreach (const QFileInfo &fileInfo, file_list)
    {
        //qDebug() << "File Name:" << fileInfo.fileName();
        //qDebug() << "Absolute Path:" << fileInfo.absoluteFilePath();
        //qDebug() << "Size:" << fileInfo.size() << "bytes";
        //qDebug() << "-------------------";

        QListWidgetItem* item = new QListWidgetItem();

        item->setText(fileInfo.fileName());
        item->setData(Qt::UserRole, QVariant(i));


        list_widget->addItem(item);
        i++;
    }
}

