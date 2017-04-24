#ifndef QUNIUIKITTABBARCONTROLLER_H
#define QUNIUIKITTABBARCONTROLLER_H

#include <QObject>

#include <QtUniUIKitControls/quniuikitviewcontroller.h>

QT_BEGIN_NAMESPACE

class QUniUIKitTabBarControllerPrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(UITabBarController);

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitTabBarController : public QUniUIKitViewController
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

#endif // QUNIUIKITTABBARCONTROLLER_H
