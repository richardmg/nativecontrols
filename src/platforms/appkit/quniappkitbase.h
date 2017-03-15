#ifndef QNATIVEAPPKITBASE_H
#define QNATIVEAPPKITBASE_H

#include <QObject>

#include <QtUniControls/quniplatformbase.h>
#include <QtUniAppKitControls/quniappkitcontrolsglobal.h>
#include <QtUniAppKitControls/quniappkitqmlbase.h>

QT_BEGIN_NAMESPACE

class QUniAppKitBasePrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(NSView);

class Q_NATIVEAPPKITCONTROLS_EXPORT QUniAppKitBase : public QUniAppKitQmlBase, public virtual QUniPlatformBase
{
    Q_OBJECT
    Q_PROPERTY(QUniAppKitBase *parent READ parentBase WRITE setParent NOTIFY parentChanged DESIGNABLE false)

public:
    QUniAppKitBase(QUniAppKitBase *parent = nullptr);
    virtual ~QUniAppKitBase();

    void setParent(QUniAppKitBase *parent);
    QUniAppKitBase *parentBase();

    void setPlatformParent(QUniPlatformBase *) override;

Q_SIGNALS:
    void parentChanged(QUniAppKitBase *parent);

protected:
    QUniAppKitBase(QUniAppKitBasePrivate &dd, QUniAppKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniAppKitBase)
    Q_DISABLE_COPY(QUniAppKitBase)

    friend class QUniAppKitPlatformPlugin;
};

QT_END_NAMESPACE

#endif // QNATIVEAPPKITBASE_H
