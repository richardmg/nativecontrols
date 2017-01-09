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

void main_objc(QNativeWindow &window, QNativeButton &nativeButton)
{
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

    // Add QNativeUIKitButton as a direct child of QNativeWindow
    QNativeUIKitButton *nativeUIKitButton1 = new QNativeUIKitButton();
    nativeUIKitButton1->setParent(&window);
    nativeUIKitButton1->move(nativeButton.left(), nativeButton.bottom());
    [nativeUIKitButton1->uiButtonHandle() setTitle:@"QNativeUIKitButton 1" forState:UIControlStateNormal];
    QObject::connect(nativeUIKitButton1, &QNativeUIKitButton::clicked,
                     [nativeUIKitButton1](){ nativeUIKitButton1->setText(QStringLiteral("Clicked!")); });

    // You can also go the other way, creating a QNativeButton as a direct child of QNativeUIKitWindow
    QNativeButton *nativeButton2 = new QNativeButton("QNativeButton 2");
    nativeButton2->setParent(window.platformHandle());
    nativeButton2->move(nativeUIKitButton1->geometry().left(), nativeUIKitButton1->geometry().bottom());
    QObject::connect(nativeButton2, &QNativeButton::clicked,
                     [nativeButton2](){ nativeButton2->setText(QStringLiteral("Clicked!")); });

    // Add another QNativeUIKitButton as a child of QNativeUIKitWindow, but this time more explicit
    if (QNativeUIKitWindow *nativeUIKitWindow = dynamic_cast<QNativeUIKitWindow *>(window.platformHandle())) {
        QNativeUIKitButton *nativeUIKitButton2 = new QNativeUIKitButton(nativeUIKitWindow);
        nativeUIKitButton2->move(nativeButton2->geometry().left(), nativeButton2->geometry().bottom());
        QObject::connect(nativeUIKitButton2, &QNativeUIKitButton::clicked,
                         [nativeUIKitButton2](){ nativeUIKitButton2->setText(QStringLiteral("Clicked!")); });

        UIButton *uiButton = nativeUIKitButton2->uiButtonHandle();
        [uiButton setTitle:@"QNativeUIKitButton 2" forState:UIControlStateNormal];
        uiButton.tintColor = [UIColor redColor];

        UIWindow *uiWindow = nativeUIKitWindow->uiWindowHandle();
        uiWindow.backgroundColor = [UIColor blueColor];
    }

#endif
}
