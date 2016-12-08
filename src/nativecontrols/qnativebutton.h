#ifndef QNATIVEPUSHBUTTON_H
#define QNATIVEPUSHBUTTON_H

#include "qnativecontrol.h"

QT_BEGIN_NAMESPACE

class QNativeButtonPrivate;

class Q_NATIVECONTROLS_EXPORT QNativeButton : public QNativeControl
{
    Q_OBJECT

public:
    explicit QNativeButton(QObject *parent = nullptr);
    virtual ~QNativeButton();

    virtual bool isVisible() const override;
    virtual void setVisible(bool visible) override;

protected:
    QNativeButton(QNativeButtonPrivate &dd, QObject *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativeButton)
    Q_DISABLE_COPY(QNativeButton)
};

QT_END_NAMESPACE

#endif // QNATIVEPUSHBUTTON_H
