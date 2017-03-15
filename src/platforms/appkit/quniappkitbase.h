#ifndef QNATIVEAPPKITBASE_H
#define QNATIVEAPPKITBASE_H

#include <QObject>

#include <QtNativeControls/quniplatformbase.h>
#include <QtNativeAppKitControls/quniappkitcontrolsglobal.h>
#include <QtNativeAppKitControls/quniappkitqmlbase.h>

QT_BEGIN_NAMESPACE

class QNativeAppKitBasePrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(NSView);

class Q_NATIVEAPPKITCONTROLS_EXPORT QNativeAppKitBase : public QNativeAppKitQmlBase, public virtual QNativePlatformBase
{
    Q_OBJECT
    Q_PROPERTY(QNativeAppKitBase *parent READ parentBase WRITE setParent NOTIFY parentChanged DESIGNABLE false)

public:
    QNativeAppKitBase(QNativeAppKitBase *parent = nullptr);
    virtual ~QNativeAppKitBase();

    void setParent(QNativeAppKitBase *parent);
    QNativeAppKitBase *parentBase();

    void setPlatformParent(QNativePlatformBase *) override;

Q_SIGNALS:
    void parentChanged(QNativeAppKitBase *parent);

protected:
    QNativeAppKitBase(QNativeAppKitBasePrivate &dd, QNativeAppKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativeAppKitBase)
    Q_DISABLE_COPY(QNativeAppKitBase)

    friend class QNativeAppKitPlatformPlugin;
};

QT_END_NAMESPACE

#endif // QNATIVEAPPKITBASE_H
