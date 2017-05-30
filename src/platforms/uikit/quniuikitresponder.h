#ifndef QUNIUIKITRESPONDER_H
#define QUNIUIKITRESPONDER_H

#include <QObject>

#include <QtUniUIKitControls/quniuikitbase.h>

QT_BEGIN_NAMESPACE

class QUniUIKitResponderPrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(UIResponder);

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitResponder : public QUniUIKitBase
{
    Q_OBJECT
    Q_PROPERTY(bool firstResponder READ firstResponder WRITE setFirstResponder NOTIFY firstResponderChanged)
    Q_PROPERTY(bool canBecomeFirstResponder READ canBecomeFirstResponder)
    Q_PROPERTY(bool canResignFirstResponder READ canResignFirstResponder)

public:
    QUniUIKitResponder(QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitResponder();

    Q_INVOKABLE virtual bool firstResponder() const;
    Q_INVOKABLE virtual void setFirstResponder(const bool &set);
    Q_INVOKABLE virtual bool canBecomeFirstResponder() const;
    Q_INVOKABLE virtual bool canResignFirstResponder() const;

    UIResponder *uiResponder();

Q_SIGNALS:
    void firstResponderChanged(bool isFirstResponder);

protected:
    QUniUIKitResponder(QUniUIKitResponderPrivate &dd, QUniUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniUIKitResponder)
    Q_DISABLE_COPY(QUniUIKitResponder)
};

QT_END_NAMESPACE

#endif // QUNIUIKITRESPONDER_H
