#ifndef QNATIVEUIKITCONTROL_H
#define QNATIVEUIKITCONTROL_H

#include <QObject>

#include <QtNativeControls/qnativeplatformcontrol.h>
#include <QtNativeUIKitControls/qnativeuikitview.h>

QT_BEGIN_NAMESPACE

class QNativeUIKitControlPrivate;

class Q_NATIVEUIKITCONTROLS_EXPORT QNativeUIKitControl : public QNativeUIKitView, public virtual QNativePlatformControl
{
    Q_OBJECT

public:
    QNativeUIKitControl(QNativeUIKitBase *parent = nullptr);
    virtual ~QNativeUIKitControl();

protected:
    QNativeUIKitControl(QNativeUIKitControlPrivate &dd, QNativeUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativeUIKitControl)
    Q_DISABLE_COPY(QNativeUIKitControl)
};

QT_END_NAMESPACE

#endif // QNATIVEUIKITCONTROL_H
