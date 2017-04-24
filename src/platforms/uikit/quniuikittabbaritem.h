#ifndef QUNIUIKITTABBARITEM_H
#define QUNIUIKITTABBARITEM_H

#include <QObject>

#include <QtUniUIKitControls/quniuikitview.h>

QT_BEGIN_NAMESPACE

class QUniUIKitTabBarItemPrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(UITabBarItem);

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitTabBarItem : public QUniUIKitBase
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

public:
    explicit QUniUIKitTabBarItem(QUniUIKitBase *parent = nullptr);
    explicit QUniUIKitTabBarItem(const QString &title, QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitTabBarItem();

    QString title() const;
    void setTitle(const QString &newTitle);

    UITabBarItem *uiTabBarItemHandle();

Q_SIGNALS:
    void titleChanged(const QString &title);

protected:
    QUniUIKitTabBarItem(QUniUIKitTabBarItemPrivate &dd, QUniUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniUIKitTabBarItem)
    Q_DISABLE_COPY(QUniUIKitTabBarItem)
};

QT_END_NAMESPACE

#endif // QUNIUIKITTABBARITEM_H
