#include <QtGui>
#include <QtNativeControls>

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QNativeWindow window;
    QNativeButton button(QStringLiteral("Click me"), &window);
    button.setGeometry(10, 10, 100, 30);
    QObject::connect(&button, &QNativeButton::clicked, [&button](){ button.setText(QStringLiteral("Thanks!")); });
    window.showFullScreen();

    return app.exec();
}
