#include <QtGui>
#include <QtNativeControls>
#include <QtNativeUIKitControls>
#include <UIKit/UIKit.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QNativeWindow window;
    QNativeButton nativeButton(QStringLiteral("QNativeButton"), &window);
    nativeButton.setGeometry(10, 10, 100, 30);
    QObject::connect(&nativeButton, &QNativeButton::clicked, [&nativeButton](){ nativeButton.setText(QStringLiteral("Clicked!")); });

    QNativeUIKitWindow *nativeUIKitWindow = dynamic_cast<QNativeUIKitWindow *>(window.platformHandle());
    QNativeUIKitButton nativeUIKitButton(QStringLiteral("QNativeUIKitButton"), nativeUIKitWindow);
    nativeUIKitButton.setGeometry(10, 50, 100, 30);
    QObject::connect(&nativeUIKitButton, &QNativeUIKitButton::clicked, [&nativeUIKitButton](){ nativeUIKitButton.setText(QStringLiteral("Clicked!")); });

    UIButton *uiButton = nativeUIKitButton.uiButtonHandle();
    uiButton.tintColor = [UIColor redColor];
    [uiButton setTitle:@"Yup" forState:UIControlStateNormal];

    window.showFullScreen();
    return app.exec();
}
