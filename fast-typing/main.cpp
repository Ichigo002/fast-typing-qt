#include "win.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // QSS Style File
    QFile ssFile("./dark-theme.qss");
    ssFile.open(QFile::ReadOnly);
    QString style = QLatin1String(ssFile.readAll());
    a.setStyleSheet(style);

    // Translation
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "fast-typing_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    win w;
    w.show();
    return a.exec();
}
