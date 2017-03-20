/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native AppKit Controls module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QUNIAPPKITWINDOW_H
#define QUNIAPPKITWINDOW_H

#include <QtUniControls/quniplatformwindow.h>

#include <QtUniAppKitControls/quniappkitview.h>

QT_BEGIN_NAMESPACE

class QUniAppKitWindowPrivate;
class QUniAppKitViewController;
Q_FORWARD_DECLARE_OBJC_CLASS(NSWindow);

class Q_UNIAPPKITCONTROLS_EXPORT QUniAppKitWindow : public QUniAppKitBase, public virtual QUniPlatformWindow
{
    Q_OBJECT
    Q_PROPERTY(QUniAppKitViewController *contentViewController READ contentViewController WRITE setContentViewController NOTIFY contentViewControllerChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged FINAL)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged FINAL)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged FINAL)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged FINAL)

public:
    QUniAppKitWindow();
    virtual ~QUniAppKitWindow();

    virtual bool isVisible() const override;
    virtual void setVisible(bool isVisible) override;
    virtual void showFullScreen() override;

    virtual QRectF geometry() const override;
    virtual void setGeometry(const QRectF &rect) override;

    virtual void setPosition(const QPointF &pos) override;
    virtual void resize(const QSizeF size) override;

    virtual bool event(QEvent *e) override;

    void setGeometry(qreal posx, qreal posy, qreal w, qreal h);
    void setPosition(qreal posx, qreal posy);
    void resize(qreal width, qreal height);

    qreal x() const;
    void setX(qreal);

    qreal y() const;
    void setY(qreal);

    qreal width() const;
    void setWidth(qreal);

    qreal height() const;
    void setHeight(qreal);

    NSWindow *nsWindowHandle();

    void setContentViewController(QUniAppKitViewController *contentViewController);
    QUniAppKitViewController *contentViewController() const;

    QRectF frame() const;
    void setFrame(const QRectF &rect);

    QRectF contentRect() const;
    QRectF contentRectForFrameRect(const QRectF &rect) const;
    QRectF frameRectForContentRect(const QRectF &rect) const;

    bool addNativeChild(QObject *child) override;
    bool addNativeChild(const QByteArray &type, void *child) override;
    QByteArrayList supportedNativeChildTypes() override;
    QByteArrayList supportedNativeParentTypes() override;

Q_SIGNALS:
    void xChanged(qreal x);
    void yChanged(qreal y);
    void widthChanged(qreal w);
    void heightChanged(qreal h);
    void visibleChanged(bool isVisible);
    void contentViewControllerChanged(QUniAppKitViewController *controller);

protected:
    QUniAppKitWindow(QUniAppKitWindowPrivate &dd);
    void childEvent(QChildEvent *event) override;

private:
    Q_DECLARE_PRIVATE(QUniAppKitWindow)
    Q_DISABLE_COPY(QUniAppKitWindow)
};

QT_END_NAMESPACE

#endif // QUNIAPPKITWINDOW_H
