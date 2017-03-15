#ifndef QNATIVEUIKITBASE_H
#define QNATIVEUIKITBASE_H

#include <QObject>

#include <QtUniControls/quniplatformbase.h>
#include <QtUniUIKitControls/quniuikitcontrolsglobal.h>
#include <QtUniUIKitControls/quniuikitqmlbase.h>

QT_BEGIN_NAMESPACE

class QUniUIKitBasePrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(UIView);

class Q_NATIVEUIKITCONTROLS_EXPORT QUniUIKitBase : public QUniUIKitQmlBase, public virtual QUniPlatformBase
{
    Q_OBJECT
    Q_PROPERTY(QUniUIKitBase *parent READ parentBase WRITE setParent NOTIFY parentChanged DESIGNABLE false)

public:
    QUniUIKitBase(QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitBase();

    void setParent(QUniUIKitBase *parent);
    QUniUIKitBase *parentBase();

    void setPlatformParent(QUniPlatformBase *) override;

Q_SIGNALS:
    void parentChanged(QUniUIKitBase *parent);

protected:
    QUniUIKitBase(QUniUIKitBasePrivate &dd, QUniUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniUIKitBase)
    Q_DISABLE_COPY(QUniUIKitBase)

    friend class QUniUIKitPlatformPlugin;
};

QT_END_NAMESPACE

#endif // QNATIVEUIKITBASE_H
