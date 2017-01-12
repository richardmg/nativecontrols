#ifndef QNATIVEAPPKITBASE_H
#define QNATIVEAPPKITBASE_H

#include <QObject>

#include <QtNativeControls/qnativeplatformbase.h>
#include <QtNativeAppKitControls/qnativeappkitcontrolsglobal.h>

QT_BEGIN_NAMESPACE

class QNativeAppKitBasePrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(NSView);

class Q_NATIVEAPPKITCONTROLS_EXPORT QNativeAppKitBase : public QObject, public virtual QNativePlatformBase
{
    Q_OBJECT

public:
    QNativeAppKitBase(QNativeAppKitBase *parent = nullptr);
    virtual ~QNativeAppKitBase();

    void setParent(QNativeAppKitBase *parent);
    void setParent(QNativeBase *parent);

    NSView *nsViewHandle();

protected:
    QNativeAppKitBase(QNativeAppKitBasePrivate &dd, QNativeAppKitBase *parent = nullptr);
    virtual void setPlatformParent(QNativePlatformBase *parent) override;
    void childEvent(QChildEvent *event) override;

private:
    Q_DECLARE_PRIVATE(QNativeAppKitBase)
    Q_DISABLE_COPY(QNativeAppKitBase)

    friend class QNativeAppKitPlatformPlugin;
};

QT_END_NAMESPACE

#endif // QNATIVEAPPKITBASE_H
