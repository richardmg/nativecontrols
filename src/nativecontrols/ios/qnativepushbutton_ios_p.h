#ifndef QNATIVEPUSHBUTTON_IOS_P_H
#define QNATIVEPUSHBUTTON_IOS_P_H

#include <QtCore/private/qobject_p.h>

#include <QtGui/QWindow>

#include "qnativecontrol_ios_p.h"

QT_BEGIN_NAMESPACE

class QNativePushButton;

class QNativePushButtonPrivate : public QNativeControlPrivate
{
    Q_DECLARE_PUBLIC(QNativePushButton)

public:
    explicit QNativePushButtonPrivate(int version = QObjectPrivateVersion);
};

QT_END_NAMESPACE

#endif // QNATIVEPUSHBUTTON_IOS_P_H
