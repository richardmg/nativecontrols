#ifndef QNATIVEUIKITBASE_H
#define QNATIVEUIKITBASE_H

#include <QObject>

#include <QtNativeControls/qnativeplatformbase.h>
#include <QtNativeUIKitControls/qnativeuikitcontrolsglobal.h>
#include <QtNativeUIKitControls/qnativeuikitqmlbase.h>

QT_BEGIN_NAMESPACE

class QNativeUIKitBasePrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(UIView);

class Q_NATIVEUIKITCONTROLS_EXPORT QNativeUIKitBase : public QNativeUIKitQmlBase, public virtual QNativePlatformBase
{
    Q_OBJECT
    Q_PROPERTY(QNativeUIKitBase *parent READ parentBase WRITE setParent NOTIFY parentChanged DESIGNABLE false)

public:
    QNativeUIKitBase(QNativeUIKitBase *parent = nullptr);
    virtual ~QNativeUIKitBase();

    void setParent(QNativeUIKitBase *parent);
    QNativeUIKitBase *parentBase();

    void setPlatformParent(QNativePlatformBase *) override;

Q_SIGNALS:
    void parentChanged(QNativeUIKitBase *parent);

protected:
    QNativeUIKitBase(QNativeUIKitBasePrivate &dd, QNativeUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativeUIKitBase)
    Q_DISABLE_COPY(QNativeUIKitBase)

    friend class QNativeUIKitPlatformPlugin;
};

QT_END_NAMESPACE

#endif // QNATIVEUIKITBASE_H
