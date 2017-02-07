#ifndef QNATIVEUIKITTABBARCONTROLLER_H
#define QNATIVEUIKITTABBARCONTROLLER_H

#include <QObject>

#include <QtNativeUIKitControls/qnativeuikitviewcontroller.h>
#include <QtNativeControls/qnativeplatformtabspage.h>

QT_BEGIN_NAMESPACE

class QNativeUIKitTabBarControllerPrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(UITabBarController);

class Q_NATIVEUIKITCONTROLS_EXPORT QNativeUIKitTabBarController : public QNativeUIKitViewController, public virtual QNativePlatformTabsPage
{
    Q_OBJECT

public:
    QNativeUIKitTabBarController(QNativeUIKitBase *parent = nullptr);
    virtual ~QNativeUIKitTabBarController();

    void setViewControllers(QList<QNativeUIKitViewController *> list);
    QList<QNativeUIKitViewController *> viewControllers() const;

    UITabBarController *uiTabBarControllerHandle();

protected:
    QNativeUIKitTabBarController(QNativeUIKitTabBarControllerPrivate &dd, QNativeUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativeUIKitTabBarController)
    Q_DISABLE_COPY(QNativeUIKitTabBarController)
};

QT_END_NAMESPACE

#endif // QNATIVEUIKITTABBARCONTROLLER_H
