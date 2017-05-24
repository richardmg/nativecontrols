#ifndef QUNIUIKITBASE_H
#define QUNIUIKITBASE_H

#include <QObject>

#include <QtUniUIKitControls/quniuikitcontrolsglobal.h>
#include <QtUniUIKitControls/quniuikitqmlbase.h>

QT_BEGIN_NAMESPACE

class QUniUIKitBasePrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(UIView);

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitBase : public QUniUIKitQmlBase
{
    Q_OBJECT
    Q_PROPERTY(QUniUIKitBase *parent READ parentBase WRITE setParent NOTIFY parentChanged DESIGNABLE false)

public:
    QUniUIKitBase(QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitBase();

    void setParent(QUniUIKitBase *parent);
    QUniUIKitBase *parentBase();

    virtual void componentComplete() override;

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

#endif // QUNIUIKITBASE_H
