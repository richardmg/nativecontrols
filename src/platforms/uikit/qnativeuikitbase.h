#ifndef QNATIVEIOSBASE_H
#define QNATIVEIOSBASE_H

#include <QObject>

#include <QtNativeControls/qnativeplatformbase.h>
#include <QtNativeUIKitControls/qnativeuikitcontrolsglobal.h>

QT_BEGIN_NAMESPACE

class QNativeUIKitBasePrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(UIView);

class Q_NATIVEUIKITCONTROLS_EXPORT QNativeUIKitBase : public QObject, public virtual QNativePlatformBase
{
    Q_OBJECT

public:
    QNativeUIKitBase(QNativeUIKitBase *parent = nullptr);

    void setParent(QNativeUIKitBase *parent);
    void setParent(QNativeBase *parent);

    UIView *uiViewHandle();

    virtual ~QNativeUIKitBase();

protected:
    QNativeUIKitBase(QNativeUIKitBasePrivate &dd, QNativeUIKitBase *parent = nullptr);
    virtual void setPlatformParent(QNativePlatformBase *parent) override;
    void childEvent(QChildEvent *event) override;

private:
    Q_DECLARE_PRIVATE(QNativeUIKitBase)
    Q_DISABLE_COPY(QNativeUIKitBase)

    friend class QNativeUIKitPlatformPlugin;
};

QT_END_NAMESPACE

#endif // QNATIVEIOSBASE_H
