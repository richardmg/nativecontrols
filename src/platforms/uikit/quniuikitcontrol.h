#ifndef QUNIUIKITCONTROL_H
#define QUNIUIKITCONTROL_H

#include <QObject>

#include <QtUniControls/quniplatformcontrol.h>
#include <QtUniUIKitControls/quniuikitview.h>

QT_BEGIN_NAMESPACE

class QUniUIKitControlPrivate;

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitControl : public QUniUIKitView, public virtual QUniPlatformControl
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

#endif // QUNIUIKITCONTROL_H
