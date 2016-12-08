#ifndef QNATIVEPUSHBUTTON_H
#define QNATIVEPUSHBUTTON_H

#include "qnativecontrol.h"

QT_BEGIN_NAMESPACE

class QNativePushButtonPrivate;

class Q_NATIVECONTROLS_EXPORT QNativePushButton : public QNativeControl
{
    Q_OBJECT

public:
    explicit QNativePushButton(QObject *parent = nullptr);
    virtual ~QNativePushButton();

    virtual bool isVisible() const override;
    virtual void setVisible(bool visible) override;

protected:
    QNativePushButton(QNativePushButtonPrivate &dd, QObject *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativePushButton)
    Q_DISABLE_COPY(QNativePushButton)
};

QT_END_NAMESPACE

#endif // QNATIVEPUSHBUTTON_H
