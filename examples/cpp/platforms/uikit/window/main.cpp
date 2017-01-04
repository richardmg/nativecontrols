#include <QtGui>
#include <QtNativeUIKitControls>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QNativeUIKitWindow window;
    QNativeUIKitButton button(QStringLiteral("Click me"), &window);
    //button.setGeometry(10, 10, 100, 30);
    QObject::connect(&button, &QNativeUIKitButton::clicked, [&button](){ button.setText(QStringLiteral("Thanks!")); });
    window.showFullScreen();

    return app.exec();
}
