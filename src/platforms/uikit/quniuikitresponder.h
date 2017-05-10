#ifndef QUNIUIKITRESPONDER_H
#define QUNIUIKITRESPONDER_H

#include <QObject>

#include <QtUniUIKitControls/quniuikitbase.h>

QT_BEGIN_NAMESPACE

class QUniUIKitResponderPrivate;

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitResponder : public QUniUIKitBase
{
    Q_OBJECT
    Q_PROPERTY(bool firstResponder READ firstResponder WRITE setFirstResponder NOTIFY firstResponderChanged)

public:
    QUniUIKitResponder(QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitResponder();

    bool firstResponder() const;
    bool setFirstResponder(bool firstResponder);

Q_SIGNALS:
    void firstResponderChanged(bool firstResponder);

protected:
    QUniUIKitResponder(QUniUIKitResponderPrivate &dd, QUniUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniUIKitResponder)
    Q_DISABLE_COPY(QUniUIKitResponder)
};

QT_END_NAMESPACE

#endif // QUNIUIKITRESPONDER_H
