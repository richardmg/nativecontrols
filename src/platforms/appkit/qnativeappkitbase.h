#ifndef QNATIVEAPPKITBASE_H
#define QNATIVEAPPKITBASE_H

#include <QObject>

#include <QtNativeControls/qnativeplatformbase.h>

QT_BEGIN_NAMESPACE

class QNativeAppKitBasePrivate;

class Q_NATIVECONTROLS_EXPORT QNativeAppKitBase : public QObject, public virtual QNativePlatformBase
{
    Q_OBJECT

public:
    QNativeAppKitBase(QObject *parent = nullptr);
    virtual ~QNativeAppKitBase();

protected:
    QNativeAppKitBase(QNativeAppKitBasePrivate &dd, QObject *parent = nullptr);
    virtual void setPlatformParent(QNativePlatformBase *parent) override;
    void childEvent(QChildEvent *event) override;

private:
    Q_DECLARE_PRIVATE(QNativeAppKitBase)
    Q_DISABLE_COPY(QNativeAppKitBase)

    friend class QNativeAppKitPlatformPlugin;
};

QT_END_NAMESPACE

#endif // QNATIVEAPPKITBASE_H
