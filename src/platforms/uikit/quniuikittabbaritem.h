#ifndef QNATIVEUIKITTABBARITEM_H
#define QNATIVEUIKITTABBARITEM_H

#include <QObject>

#include <QtUniControls/quniplatformtabspagetab.h>
#include <QtUniUIKitControls/quniuikitview.h>

QT_BEGIN_NAMESPACE

class QUniUIKitTabBarItemPrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(UITabBarItem);

class Q_NATIVEUIKITCONTROLS_EXPORT QUniUIKitTabBarItem : public QUniUIKitBase, public virtual QUniPlatformTabsPageTab
{
    Q_OBJECT

public:
    explicit QUniUIKitTabBarItem(QUniUIKitBase *parent = nullptr);
    explicit QUniUIKitTabBarItem(const QString &title, QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitTabBarItem();

    virtual QString title() const override;
    virtual void setTitle(const QString &title) override;

    UITabBarItem *uiTabBarItemHandle();

protected:
    QUniUIKitTabBarItem(QUniUIKitTabBarItemPrivate &dd, QUniUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniUIKitTabBarItem)
    Q_DISABLE_COPY(QUniUIKitTabBarItem)
};

QT_END_NAMESPACE

#endif // QNATIVEUIKITTABBARITEM_H
