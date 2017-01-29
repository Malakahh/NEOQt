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

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    qDebug() << "pathfinder: " << QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).last();
    
    saveTest();
    loadTest();

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
