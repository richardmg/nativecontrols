#ifndef QMLNATIVEBUTTON_H
#define QMLNATIVEBUTTON_H

#include <QtCore/qobject.h>
#include <QtQml/qqmlengine.h>
#include <QtNativeControls/qnativebutton.h>

#include "qmlnativecontrol_p.h"

QT_BEGIN_NAMESPACE

class QmlNativeButton : public QmlNativeControl
{
    Q_OBJECT

public:
    explicit QmlNativeButton(QmlNativeControl *parent = nullptr);
    virtual ~QmlNativeButton() {}

private:
    QNativeButton *m_button;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QmlNativeButton)

#endif // QMLNATIVEBUTTON_H
