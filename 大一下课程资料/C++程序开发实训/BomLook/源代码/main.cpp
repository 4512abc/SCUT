#include "CreateMap.h"
#include "MyMainWindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "text_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    // CreateMap c;
    // c.show();

    // QFile file("./time1.bin");
    // QString str="cc";
    // int time=0;
    // int score=0;
    // QDataStream in(&file);
    // file.open(QIODevice::ReadWrite);
    // in<<str<<time<<score;
    // file.close();
    // return 0;

    MyMainWindow w;
    w.show();
    return a.exec();
    // QFile accountData("AccountData.bin");
    // QDataStream out(&accountData);
    // if (!accountData.open(QIODevice::Append)) {
    //     qCritical() << "无法打开文件进行写入";
    // }
    // Player temp;
    // temp.setID(1),temp.setUserName("cc"),temp.setPwd("cc123");
    // out.setVersion(QDataStream::Qt_6_0);
    // out<<temp;
    // accountData.close();
    // return 0;
}
