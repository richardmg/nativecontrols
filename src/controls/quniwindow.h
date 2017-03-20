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

#ifndef QUNIWINDOW_H
#define QUNIWINDOW_H

#include <QtUniControls/qunibase.h>
#include <QtUniControls/qunicontrolsglobal.h>

QT_BEGIN_NAMESPACE

class QUniWindowPrivate;
class QUniPlatformWindow;

class Q_UNICONTROLS_EXPORT QUniWindow : public QUniBase
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged FINAL)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged FINAL)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged FINAL)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged FINAL)

public:
    explicit QUniWindow();
    virtual ~QUniWindow();

    QRectF geometry() const;
    void setGeometry(const QRectF &rect);
    void setGeometry(qreal posx, qreal posy, qreal w, qreal h);

    void setPosition(const QPointF &pos);
    void setPosition(qreal posx, qreal posy);

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

    bool isVisible() const;
    void setVisible(bool visible);
    void showFullScreen();

Q_SIGNALS:
    void xChanged(qreal x);
    void yChanged(qreal y);
    void widthChanged(qreal w);
    void heightChanged(qreal h);
    void visibleChanged(bool visible);

protected:
    QUniWindow(QUniWindowPrivate &dd, QUniBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniWindow)
    Q_DISABLE_COPY(QUniWindow)
};

QT_END_NAMESPACE

#endif // QUNIWINDOW_H
