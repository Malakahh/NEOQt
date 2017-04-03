#include "apphelper.h"

#include <QtAndroidExtras/QAndroidJniObject>
#include <QDebug>

AppHelper::AppHelper(QObject *parent) : QObject(parent)
{

}

void AppHelper::exit()
{
#ifdef Q_OS_ANDROID

    qDebug() << "ANDROID";
    //QAndroidJniObject::callStaticObjectMethod("Landroid/app/ActivityManager/AppTask;", "finishAndRemoveTask", "()V");

//    jint pid = QAndroidJniObject::callStaticMethod<jint>("Landroid/os/Process;", "myPid");
//    QAndroidJniObject::callStaticMethod<void>("Landroid/os/Process;", "killProcess", "(I)V", pid);
//    QAndroidJniObject::callStaticMethod<void>("LSystem;", "exit", "()V");

    qDebug() << "ANDROID END";

#endif
}
