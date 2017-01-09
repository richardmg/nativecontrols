#include <QtGui>
#include <QtNativeControls>

#ifdef Q_OS_DARWIN
extern void main_objc(QNativeWindow &window, QNativeButton &nativeButton);
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QNativeWindow window;
    QNativeButton nativeButton(QStringLiteral("QNativeButton"), &window);
    nativeButton.move(10, 20);
    QObject::connect(&nativeButton, &QNativeButton::clicked,
                     [&nativeButton](){ nativeButton.setText(QStringLiteral("Clicked!")); });

#ifdef Q_OS_DARWIN
    main_objc(window, nativeButton);
#endif

    window.showFullScreen();
    return app.exec();
}
