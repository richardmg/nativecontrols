#include <QtGui>
#include <QtNativeUIKitControls>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QNativeUIKitWindow window;
    QNativeUIKitButton button(QStringLiteral("Click me"), &window);
    button.move(50, 100);
    QObject::connect(&button, &QNativeUIKitButton::clicked, [&button](){ button.setText(QStringLiteral("Thanks!")); });
    window.showFullScreen();

    return app.exec();
}
