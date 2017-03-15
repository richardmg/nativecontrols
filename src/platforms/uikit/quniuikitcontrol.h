#ifndef QNATIVEUIKITCONTROL_H
#define QNATIVEUIKITCONTROL_H

#include <QObject>

#include <QtNativeControls/quniplatformcontrol.h>
#include <QtNativeUIKitControls/quniuikitview.h>

QT_BEGIN_NAMESPACE

class QUniUIKitControlPrivate;

class Q_NATIVEUIKITCONTROLS_EXPORT QUniUIKitControl : public QUniUIKitView, public virtual QUniPlatformControl
{
    Q_OBJECT

public:
    QUniUIKitControl(QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitControl();

protected:
    QUniUIKitControl(QUniUIKitControlPrivate &dd, QUniUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniUIKitControl)
    Q_DISABLE_COPY(QUniUIKitControl)
};

QT_END_NAMESPACE

#endif // QNATIVEUIKITCONTROL_H
