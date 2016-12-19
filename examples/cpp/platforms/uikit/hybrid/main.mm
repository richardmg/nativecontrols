#include <QtGui>
#include <QtNativeControls>
#include <QtNativeUIKitControls>
#include <UIKit/UIKit.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QNativeWindow window;
    QNativeButton button1(QStringLiteral("QNativeButton"), &window);
    button1.setGeometry(10, 10, 100, 30);
    QObject::connect(&button1, &QNativeButton::clicked, [&button1](){ button1.setText(QStringLiteral("Clicked!")); });

    QNativeUIKitWindow *platformWindow = dynamic_cast<QNativeUIKitWindow *>(window.platformHandle());
    QNativeUIKitButton button2(QStringLiteral("QNativeUIKitButton"), platformWindow);
    button2.setGeometry(10, 50, 100, 30);
    QObject::connect(&button2, &QNativeUIKitButton::clicked, [&button2](){ button2.setText(QStringLiteral("Clicked!")); });

    UIButton *uiButton = reinterpret_cast<UIButton *>(button2.controlHandle());
    uiButton.tintColor = [UIColor blueColor];

    window.showFullScreen();
    return app.exec();
}
