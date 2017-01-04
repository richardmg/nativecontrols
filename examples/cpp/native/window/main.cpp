#include <QtGui>
#include <QtNativeControls>

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QNativeWindow window;
    QNativeButton button(QStringLiteral("Click me"), &window);
    button.move(50, 100);
    QObject::connect(&button, &QNativeButton::clicked, [&button](){ button.setText(QStringLiteral("Thanks!")); });

    QNativeTextField textField(&window);
    textField.setPlaceholderText(QStringLiteral("TextField"));
    textField.move(50, 150);

    window.showFullScreen();

    return app.exec();
}
