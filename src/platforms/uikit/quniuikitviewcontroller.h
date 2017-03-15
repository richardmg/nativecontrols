#ifndef QNATIVEUIKITVIEWCONTROLLER_H
#define QNATIVEUIKITVIEWCONTROLLER_H

#include <QObject>

#include <QtNativeUIKitControls/quniuikitbase.h>
#include <QtNativeControls/quniplatformpage.h>

QT_BEGIN_NAMESPACE

class QUniUIKitView;
class QUniUIKitViewControllerPrivate;
class QUniUIKitTabBarItem;
Q_FORWARD_DECLARE_OBJC_CLASS(UIViewController);

class Q_NATIVEUIKITCONTROLS_EXPORT QUniUIKitViewController : public QUniUIKitBase, public virtual QUniPlatformPage
{
    Q_OBJECT
    Q_PROPERTY(QUniUIKitView *view READ view WRITE setView NOTIFY viewChanged)

public:
    QUniUIKitViewController(QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitViewController();

    QUniUIKitView *view() const;
    void setView(QUniUIKitView *platformContentView);

    QUniUIKitViewController *parentViewController();

    void setTabBarItem(QUniUIKitTabBarItem *tabBarItem);
    QUniUIKitTabBarItem *tabBarItem() const;

    UIViewController *uiViewControllerHandle();

    bool setNativeParent(QObject *parent) override;
    bool setNativeParent(const QByteArray &type, void *parent) override;
    bool addNativeChild(QObject *child) override;
    bool addNativeChild(const QByteArray &type, void *child) override;
    QByteArrayList supportedNativeChildTypes() override;
    QByteArrayList supportedNativeParentTypes() override;

Q_SIGNALS:
    void viewChanged(QUniUIKitView *contentView);

protected:
    QUniUIKitViewController(QUniUIKitViewControllerPrivate &dd, QUniUIKitBase *parent = nullptr);
    void childEvent(QChildEvent *event) override;

private:
    Q_DECLARE_PRIVATE(QUniUIKitViewController)
    Q_DISABLE_COPY(QUniUIKitViewController)
};

QT_END_NAMESPACE

#endif // QNATIVEUIKITVIEWCONTROLLER_H
