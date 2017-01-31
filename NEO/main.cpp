#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include <QStandardPaths>
#include <QDirModel>

#include "blecontroller.h"
#include "chargermodel.h"
#include "filebrowsermodel.h"


//For tests
#include <QFile>
#include <QDataStream>
#include <QStandardPaths>

/*
void saveTest()
{
    QString name("./testSaveFile.txt");

    QSaveFile sf(name);

    char data[] = {
        0x41, 0x42, 0x43,
        0x31, 0x32, 0x33
    };

    sf.write(data, 6);
    sf.commit();
}
*/

void saveTest()
{
    QString filePath(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).last() + "/testSaveFile.txt");

    QFile f(filePath);
    f.open(QIODevice::WriteOnly);

    QDataStream ds(&f);
    //QTextStream ds(&f);
    //ds.setByteOrder(QDataStream::ByteOrder(QSysInfo::ByteOrder));
    
    const char data[] = {
        0x41, 0x42, 0x43,
        0x31, 0x32, 0x33
    };
    
    QString s = QString::fromLocal8Bit(data);
    
    //QString data("ABC123");
    
    //ds.writeBytes(data, 6);
    ds << s;
    //ds.writeRawData(data, 6);
}

void loadTest()
{
    QString filePath(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).last() + "/testSaveFile.txt");

    QFile f(filePath);
    f.open(QIODevice::ReadOnly);

    qDebug() << "file size: " << f.size();

    QDataStream ds(&f);
    QString str;

    ds >> str;

    qDebug() << "Data read: " << str;
}

#include "QtDropbox2/src/qdropbox2.h"
#include <QDesktopServices>

#define APP_KEY QString("0crhqgwzoh9yymp")
#define APP_SECRET QString("9qyidlxjfxk93tp")

void dropboxTest()
{
    QUrl url = QDropbox2::authorizeLink(APP_KEY);
    qDebug() << url;
    QDesktopServices::openUrl(url);

    QDropbox2 db2(APP_KEY, APP_SECRET);

    if (db2.error() != QDropbox2::NoError)
    {
        qDebug() << "Error! " << db2.error();
        return;
    }

    QDropbox2User info;
    db2.userInfo(info);

    qDebug() << "\t            id: " << info.id();
    qDebug() << "\t          type: " << info.type();
    qDebug() << "\t          name: " << info.displayName();
    qDebug() << "\t         email: " << info.email();
    qDebug() << "\t emailVerified: " << (info.emailVerified() ? "true" : "false");
    qDebug() << "\t    isDisabled: " << (info.isDisabled() ? "true" : "false");
    qDebug() << "\t        locale: " << info.locale();
    qDebug() << "\t  referralLink: " << info.referralLink().toString();
    qDebug() << "\t      isPaired: " << (info.isPaired() ? "true" : "false");
    qDebug() << "\t       country: " << info.country();
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    /*
    qDebug() << "pathfinder: " << QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).last();
    
    saveTest();
    loadTest();
*/

    BLEController& bleController = BLEController::getInstance();
    ChargerModel chargerModel;
    FileBrowserModel fbModel;
    //fbModel.setRootPath(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).last());

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("bleController", &bleController);
    engine.rootContext()->setContextProperty("chargerModel", &chargerModel);
    engine.rootContext()->setContextProperty("fbModel", &fbModel);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
