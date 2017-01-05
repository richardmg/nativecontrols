#include <QtGui>
#include <QtNativeControls>

#if defined(Q_OS_MACOS)
#include <QtNativeAppKitControls>
#include <AppKit/AppKit.h>
#endif

#if defined(Q_OS_IOS) || defined(Q_OS_TVOS)
#include <QtNativeUIKitControls>
#include <UIKit/UIKit.h>
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QNativeWindow window;
    QNativeButton nativeButton(QStringLiteral("QNativeButton"), &window);
    nativeButton.setGeometry(10, 10, 100, 30);
    QObject::connect(&nativeButton, &QNativeButton::clicked,
                     [&nativeButton](){ nativeButton.setText(QStringLiteral("Clicked!")); });

#if defined(Q_OS_MACOS)
    if (QNativeAppKitWindow *nativeAppKitWindow = dynamic_cast<QNativeAppKitWindow *>(window.platformHandle())) {
        QNativeAppKitButton *nativeAppKitButton = new QNativeAppKitButton(nativeAppKitWindow);
        nativeAppKitButton->setGeometry(10, 50, 100, 30);
        QObject::connect(nativeAppKitButton, &QNativeAppKitButton::clicked,
                         [&nativeAppKitButton](){ nativeAppKitButton->setText(QStringLiteral("Clicked!")); });

        NSButton *nsButton = nativeAppKitButton->nsButtonHandle();
        nsButton.title = @"Click me";
#if QT_OSX_PLATFORM_SDK_EQUAL_OR_ABOVE(101202)
        if ([[NSProcessInfo processInfo] isOperatingSystemAtLeastVersion:(NSOperatingSystemVersion){10, 12, 2}])
            nsButton.bezelColor = [NSColor redColor];
#endif

        NSWindow *nsWindow = nativeAppKitWindow->nsWindowHandle();
        nsWindow.backgroundColor = [NSColor blueColor];
    }
#endif

#if defined(Q_OS_IOS) || defined(Q_OS_TVOS)
    if (QNativeUIKitWindow *nativeUIKitWindow = dynamic_cast<QNativeUIKitWindow *>(window.platformHandle())) {
        QNativeUIKitButton *nativeUIKitButton = new QNativeUIKitButton(nativeUIKitWindow);
        nativeUIKitButton->setGeometry(10, 50, 100, 30);
        QObject::connect(nativeUIKitButton, &QNativeUIKitButton::clicked,
                         [&nativeUIKitButton](){ nativeUIKitButton->setText(QStringLiteral("Clicked!")); });

        UIButton *uiButton = nativeUIKitButton->uiButtonHandle();
        [uiButton setTitle:@"Click me" forState:UIControlStateNormal];
        uiButton.tintColor = [UIColor redColor];

        UIWindow *uiWindow = nativeUIKitWindow->uiWindowHandle();
        uiWindow.backgroundColor = [UIColor blueColor];
    }
#endif

    window.showFullScreen();
    return app.exec();
}
