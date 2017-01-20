/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native Controls module of the Qt Toolkit.
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

#ifndef QNATIVEVIEW_H
#define QNATIVEVIEW_H

#include <QtNativeControls/qnativebase.h>
#include <QtNativeControls/qnativecontrolsglobal.h>

QT_BEGIN_NAMESPACE

class QNativeViewPrivate;
class QNativePlatformView;

class Q_NATIVECONTROLS_EXPORT QNativeView : public QNativeBase
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged FINAL)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged FINAL)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged FINAL)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged FINAL)
    Q_PROPERTY(qreal left READ left NOTIFY xChanged FINAL)
    Q_PROPERTY(qreal top READ top NOTIFY yChanged FINAL)
    Q_PROPERTY(qreal right READ right NOTIFY rightChanged FINAL)
    Q_PROPERTY(qreal bottom READ bottom NOTIFY bottomChanged FINAL)
    Q_PROPERTY(qreal implicitWidth READ implicitWidth NOTIFY implicitWidthChanged FINAL)
    Q_PROPERTY(qreal implicitHeight READ implicitHeight NOTIFY implicitHeightChanged FINAL)

public:
    explicit QNativeView(QNativeBase *parent = nullptr);
    virtual ~QNativeView();

    QNativeView *parentView();

    bool visible() const;
    void setVisible(bool visible);

    void setGeometry(const QRectF &rect);
    QRectF geometry() const;
    void setGeometry(qreal posx, qreal posy, qreal w, qreal h);

    void move(const QPointF &pos);
    void move(qreal posx, qreal posy);

    void resize(const QSizeF size);
    void resize(qreal width, qreal height);

    qreal x() const;
    void setX(qreal);

    qreal y() const;
    void setY(qreal);

    qreal width() const;
    void setWidth(qreal);

    qreal height() const;
    void setHeight(qreal);

    qreal left() const;
    qreal top() const;
    qreal right() const;
    qreal bottom() const;

    QSizeF implicitSize() const;
    qreal implicitWidth() const;
    qreal implicitHeight() const;

Q_SIGNALS:
    void visibleChanged(bool visible);
    void xChanged(qreal x);
    void yChanged(qreal y);
    void widthChanged(qreal w);
    void heightChanged(qreal h);
    void rightChanged(qreal right);
    void bottomChanged(qreal bottom);
    void implicitWidthChanged(qreal w);
    void implicitHeightChanged(qreal h);

protected:
    QNativeView(QNativeViewPrivate &dd, QNativeBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativeView)
    Q_DISABLE_COPY(QNativeView)
};

QT_END_NAMESPACE

#endif // QNATIVEVIEW_H