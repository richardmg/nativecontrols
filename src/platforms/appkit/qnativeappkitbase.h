#ifndef QNATIVEAPPKITBASE_H
#define QNATIVEAPPKITBASE_H

#include <QObject>

#include <QtNativeControls/qnativebase.h>
#include <QtNativeControls/qnativeplatformbase.h>

#include <QtNativeAppKitControls/qnativeappkitcontrolsglobal.h>

QT_BEGIN_NAMESPACE

class QNativeAppKitBasePrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(NSView);

class Q_NATIVEAPPKITCONTROLS_EXPORT QNativeAppKitBase : public QNativePlatformBase
{
    Q_OBJECT

public:
    QNativeAppKitBase(QNativeAppKitBase *parent = nullptr);
    virtual ~QNativeAppKitBase();

protected:
    QNativeAppKitBase(QNativeAppKitBasePrivate &dd, QNativeAppKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativeAppKitBase)
    Q_DISABLE_COPY(QNativeAppKitBase)

    friend class QNativeAppKitPlatformPlugin;
};

QT_END_NAMESPACE

#endif // QNATIVEAPPKITBASE_H
