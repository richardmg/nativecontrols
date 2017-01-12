#ifndef QNATIVEAPPKITCONTROL_H
#define QNATIVEAPPKITCONTROL_H

#include <QObject>

#include <QtNativeControls/qnativeplatformcontrol.h>
#include <QtNativeAppKitControls/qnativeappkitbase.h>

QT_BEGIN_NAMESPACE

class QNativeAppKitControlPrivate;

class Q_NATIVEAPPKITCONTROLS_EXPORT QNativeAppKitControl : public QNativeAppKitBase, public virtual QNativePlatformControl
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged FINAL)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged FINAL)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged FINAL)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged FINAL)
    Q_PROPERTY(qreal implicitWidth READ implicitWidth NOTIFY implicitWidthChanged FINAL)
    Q_PROPERTY(qreal implicitHeight READ implicitHeight NOTIFY implicitHeightChanged FINAL)

public:
    QNativeAppKitControl(QNativeAppKitBase *parent = nullptr);
    virtual ~QNativeAppKitControl();

    virtual bool visible() const override;
    virtual void setVisible(bool visible) override;

    virtual QRectF geometry() const override;
    virtual void setGeometry(const QRectF &rect) override;

    virtual QRectF frameGeometry() const override;

    virtual void move(const QPointF &pos) override;
    virtual void resize(const QSizeF size) override;

    virtual QSizeF implicitSize() const override;

    void setGeometry(qreal posx, qreal posy, qreal w, qreal h);
    void move(qreal posx, qreal posy);
    void resize(qreal width, qreal height);

    qreal implicitWidth() const;
    qreal implicitHeight() const;

    qreal x() const;
    void setX(qreal);

    qreal y() const;
    void setY(qreal);

    qreal width() const;
    void setWidth(qreal);

    qreal height() const;
    void setHeight(qreal);

Q_SIGNALS:
    void visibleChanged(bool visible);
    void xChanged(qreal x);
    void yChanged(qreal y);
    void widthChanged(qreal w);
    void heightChanged(qreal h);
    void implicitWidthChanged(qreal w);
    void implicitHeightChanged(qreal h);

protected:
    QNativeAppKitControl(QNativeAppKitControlPrivate &dd, QNativeAppKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativeAppKitControl)
    Q_DISABLE_COPY(QNativeAppKitControl)
};

QT_END_NAMESPACE

#endif // QNATIVEAPPKITCONTROL_H
