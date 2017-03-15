#ifndef QNATIVEUIKITTABBARITEM_H
#define QNATIVEUIKITTABBARITEM_H

#include <QObject>

#include <QtNativeControls/quniplatformtabspagetab.h>
#include <QtNativeUIKitControls/quniuikitview.h>

QT_BEGIN_NAMESPACE

class QNativeUIKitTabBarItemPrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(UITabBarItem);

class Q_NATIVEUIKITCONTROLS_EXPORT QNativeUIKitTabBarItem : public QNativeUIKitBase, public virtual QNativePlatformTabsPageTab
{
    Q_OBJECT

public:
    explicit QNativeUIKitTabBarItem(QNativeUIKitBase *parent = nullptr);
    explicit QNativeUIKitTabBarItem(const QString &title, QNativeUIKitBase *parent = nullptr);
    virtual ~QNativeUIKitTabBarItem();

    virtual QString title() const override;
    virtual void setTitle(const QString &title) override;

    UITabBarItem *uiTabBarItemHandle();

protected:
    QNativeUIKitTabBarItem(QNativeUIKitTabBarItemPrivate &dd, QNativeUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativeUIKitTabBarItem)
    Q_DISABLE_COPY(QNativeUIKitTabBarItem)
};

QT_END_NAMESPACE

#endif // QNATIVEUIKITTABBARITEM_H
