#ifndef QNATIVEPUSHBUTTON_IOS_P_H
#define QNATIVEPUSHBUTTON_IOS_P_H

#include <QtCore/private/qobject_p.h>

#include <QtGui/QWindow>

#include "qnativecontrol_ios_p.h"

QT_BEGIN_NAMESPACE

class QNativeButton;

class QNativeButtonPrivate : public QNativeControlPrivate
{
    Q_DECLARE_PUBLIC(QNativeButton)

public:
    explicit QNativeButtonPrivate(int version = QObjectPrivateVersion);
};

QT_END_NAMESPACE

#endif // QNATIVEPUSHBUTTON_IOS_P_H
