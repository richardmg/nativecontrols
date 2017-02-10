#ifndef QNATIVEAPPKITBASE_H
#define QNATIVEAPPKITBASE_H

#include <QObject>

#include <QtNativeControls/qnativeplatformbase.h>
#include <QtNativeAppKitControls/qnativeappkitcontrolsglobal.h>
#include <QtNativeAppKitControls/qnativeappkitqmlbase.h>

QT_BEGIN_NAMESPACE

class QNativeAppKitBasePrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(NSView);

class Q_NATIVEAPPKITCONTROLS_EXPORT QNativeAppKitBase : public QNativeAppKitQmlBase, public virtual QNativePlatformBase
{
    Q_OBJECT

public:
    QNativeAppKitBase(QNativeAppKitBase *parent = nullptr);
    virtual ~QNativeAppKitBase();

    void setPlatformParent(QNativePlatformBase *) override;

protected:
    QNativeAppKitBase(QNativeAppKitBasePrivate &dd, QNativeAppKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativeAppKitBase)
    Q_DISABLE_COPY(QNativeAppKitBase)

    friend class QNativeAppKitPlatformPlugin;
};

QT_END_NAMESPACE

#endif // QNATIVEAPPKITBASE_H
