#include <QtGui>
#include <QtQml>
#include <QtQuick>

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine(QUrl("qrc:///main.qml"));
    return app.exec();
}

