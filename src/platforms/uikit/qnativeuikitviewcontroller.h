#ifndef QNATIVEUIKITVIEWCONTROLLER_H
#define QNATIVEUIKITVIEWCONTROLLER_H

#include <QObject>

#include <QtNativeUIKitControls/qnativeuikitbase.h>
#include <QtNativeControls/qnativeplatformpage.h>

QT_BEGIN_NAMESPACE

class QNativeUIKitView;
class QNativeUIKitViewControllerPrivate;
class QNativeUIKitTabBarItem;
Q_FORWARD_DECLARE_OBJC_CLASS(UIViewController);

class Q_NATIVEUIKITCONTROLS_EXPORT QNativeUIKitViewController : public QNativeUIKitBase, public virtual QNativePlatformPage
{
    Q_OBJECT
    Q_PROPERTY(QNativeUIKitView *view READ view WRITE setView NOTIFY viewChanged)

public:
    QNativeUIKitViewController(QNativeUIKitBase *parent = nullptr);
    virtual ~QNativeUIKitViewController();

    QNativeUIKitView *view() const;
    void setView(QNativeUIKitView *platformContentView);

    QNativeUIKitViewController *parentViewController();

    void setTabBarItem(QNativeUIKitTabBarItem *tabBarItem);
    QNativeUIKitTabBarItem *tabBarItem() const;

    UIViewController *uiViewControllerHandle();

Q_SIGNALS:
    void viewChanged(QNativeUIKitView *contentView);

protected:
    QNativeUIKitViewController(QNativeUIKitViewControllerPrivate &dd, QNativeUIKitBase *parent = nullptr);
    void childEvent(QChildEvent *event) override;

private:
    Q_DECLARE_PRIVATE(QNativeUIKitViewController)
    Q_DISABLE_COPY(QNativeUIKitViewController)
};

QT_END_NAMESPACE

#endif // QNATIVEUIKITVIEWCONTROLLER_H
