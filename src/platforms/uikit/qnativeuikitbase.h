#ifndef QNATIVEUIKITBASE_H
#define QNATIVEUIKITBASE_H

#include <QObject>

#include <QtNativeControls/qnativebase.h>
#include <QtNativeControls/qnativeplatformbase.h>

#include <QtNativeUIKitControls/qnativeuikitcontrolsglobal.h>

QT_BEGIN_NAMESPACE

class QNativeUIKitBasePrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(UIView);

class Q_NATIVEUIKITCONTROLS_EXPORT QNativeUIKitBase : public QNativePlatformBase
{
    Q_OBJECT

public:
    QNativeUIKitBase(QNativeUIKitBase *parent = nullptr);

    virtual ~QNativeUIKitBase();

protected:
    QNativeUIKitBase(QNativeUIKitBasePrivate &dd, QNativeUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativeUIKitBase)
    Q_DISABLE_COPY(QNativeUIKitBase)

    friend class QNativeUIKitPlatformPlugin;
};

QT_END_NAMESPACE

#endif // QNATIVEUIKITBASE_H
