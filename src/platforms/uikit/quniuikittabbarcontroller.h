#ifndef QNATIVEUIKITTABBARCONTROLLER_H
#define QNATIVEUIKITTABBARCONTROLLER_H

#include <QObject>

#include <QtNativeUIKitControls/quniuikitviewcontroller.h>
#include <QtNativeControls/quniplatformtabspage.h>

QT_BEGIN_NAMESPACE

class QUniUIKitTabBarControllerPrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(UITabBarController);

class Q_NATIVEUIKITCONTROLS_EXPORT QUniUIKitTabBarController : public QUniUIKitViewController, public virtual QUniPlatformTabsPage
{
    Q_OBJECT

public:
    QUniUIKitTabBarController(QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitTabBarController();

    void setViewControllers(QList<QUniUIKitViewController *> list);
    QList<QUniUIKitViewController *> viewControllers() const;

    UITabBarController *uiTabBarControllerHandle();
    QUniUIKitView *view() const;

protected:
    QUniUIKitTabBarController(QUniUIKitTabBarControllerPrivate &dd, QUniUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniUIKitTabBarController)
    Q_DISABLE_COPY(QUniUIKitTabBarController)
};

QT_END_NAMESPACE

#endif // QNATIVEUIKITTABBARCONTROLLER_H
