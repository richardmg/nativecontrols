#ifndef QUNIUIKITCONTROL_H
#define QUNIUIKITCONTROL_H

#include <QObject>

#include <QtUniUIKitControls/quniuikitview.h>

QT_BEGIN_NAMESPACE

class QUniUIKitControlPrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(UIControl);

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitControl : public QUniUIKitView
{
    Q_OBJECT

public:
    QUniUIKitControl(QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitControl();

    UIControl *uiControlHandle();

protected:
    QUniUIKitControl(QUniUIKitControlPrivate &dd, QUniUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniUIKitControl)
    Q_DISABLE_COPY(QUniUIKitControl)
};

QT_END_NAMESPACE

#endif // QUNIUIKITCONTROL_H
