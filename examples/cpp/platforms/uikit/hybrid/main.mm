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
    QObject::connect(&nativeButton, &QNativeButton::clicked,
                     [&nativeButton](){ nativeButton.setText(QStringLiteral("Clicked!")); });

    if (QNativeUIKitWindow *nativeUIKitWindow = dynamic_cast<QNativeUIKitWindow *>(window.platformHandle())) {
        QNativeUIKitButton *nativeUIKitButton = new QNativeUIKitButton(nativeUIKitWindow);
        nativeUIKitButton->setGeometry(10, 50, 100, 30);
        QObject::connect(nativeUIKitButton, &QNativeUIKitButton::clicked,
                         [&nativeUIKitButton](){ nativeUIKitButton->setText(QStringLiteral("Clicked!")); });

        UIButton *uiButton = nativeUIKitButton->uiButtonHandle();
        [uiButton setTitle:@"Click me" forState:UIControlStateNormal];
        uiButton.tintColor = [UIColor redColor];
    }

    window.showFullScreen();
    return app.exec();
}
