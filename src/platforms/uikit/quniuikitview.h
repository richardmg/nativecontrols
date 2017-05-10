/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native UIKit Controls module of the Qt Toolkit.
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

#ifndef QNATIVUIKITVIEW_H
#define QNATIVUIKITVIEW_H

#include <QObject>

#include <QtUniUIKitControls/quniuikitresponder.h>

QT_BEGIN_NAMESPACE

class QUniUIKitViewPrivate;

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitView : public QUniUIKitResponder
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
    Q_PROPERTY(qreal intrinsicContentWidth READ intrinsicContentWidth WRITE setIntrinsicContentWidth NOTIFY intrinsicContentWidthChanged FINAL)
    Q_PROPERTY(qreal intrinsicContentHeight READ intrinsicContentHeight WRITE setIntrinsicContentHeight NOTIFY intrinsicContentHeightChanged FINAL)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged FINAL)

public:
    QUniUIKitView(QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitView();

    bool visible() const;
    void setVisible(bool visible);

    QRectF geometry() const;
    void setGeometry(const QRectF &rect);

    QRectF frameGeometry() const;

    void move(const QPointF &pos);
    void resize(const QSizeF size);

    QSizeF intrinsicSize() const;
    void setIntrinsicSize(const QSizeF &size);

    void setGeometry(qreal posx, qreal posy, qreal w, qreal h);
    void move(qreal posx, qreal posy);
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

    qreal intrinsicContentWidth() const;
    void setIntrinsicContentWidth(qreal width);
    qreal intrinsicContentHeight() const;
    void setIntrinsicContentHeight(qreal height);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    QUniUIKitView *parentView();

    UIView *uiViewHandle();

Q_SIGNALS:
    void visibleChanged(bool visible);
    void xChanged(qreal x);
    void yChanged(qreal y);
    void widthChanged(qreal w);
    void heightChanged(qreal h);
    void rightChanged(qreal right);
    void bottomChanged(qreal bottom);
    void intrinsicContentWidthChanged(qreal w);
    void intrinsicContentHeightChanged(qreal h);
    void backgroundColorChanged(const QColor &color);

protected:
    QUniUIKitView(QUniUIKitViewPrivate &dd, QUniUIKitBase *parent = nullptr);
    void childEvent(QChildEvent *event) override;

private:
    Q_DECLARE_PRIVATE(QUniUIKitView)
    Q_DISABLE_COPY(QUniUIKitView)
};

QT_END_NAMESPACE

#endif // QNATIVUIKITVIEW_H
