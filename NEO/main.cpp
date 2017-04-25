#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include <QStandardPaths>
#include <QDirModel>

#include "blecontroller.h"
#include "chargermodel.h"
#include "filehelper.h"
#include "programparser.h"
#include "storagemodel.h"
#include "blehelper.h"

#include "apphelper.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    //QApplication app(argc, argv);

    //BLEController& bleController = BLEController::getInstance();
    BLEController bleController;
    BLEHelper::getInstance().bleController = &bleController;

    ChargerModel& chargerModel = ChargerModel::getInstance();
    FileHelper& fileHelper = FileHelper::getInstance();
    ProgramParser programParser;
    StorageModel& storageModel = StorageModel::getInstance();
    AppHelper ah;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("bleController", &bleController);
    engine.rootContext()->setContextProperty("chargerModel", &chargerModel);
    engine.rootContext()->setContextProperty("fileHelper", &fileHelper);
    engine.rootContext()->setContextProperty("programParser", &programParser);
    engine.rootContext()->setContextProperty("storageModel", &storageModel);
    engine.rootContext()->setContextProperty("app", &ah);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
