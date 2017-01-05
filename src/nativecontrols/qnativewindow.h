/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
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

#ifndef QNATIVEWINDOW_H
#define QNATIVEWINDOW_H

#include <QtNativeControls/qnativebase.h>
#include <QtNativeControls/qnativecontrolsglobal.h>

QT_BEGIN_NAMESPACE

class QNativeWindowPrivate;
class QNativePlatformWindow;

class Q_NATIVECONTROLS_EXPORT QNativeWindow : public QNativeBase
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(qreal width READ width NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height NOTIFY heightChanged)

public:
    explicit QNativeWindow();
    virtual ~QNativeWindow();

    qreal width() const;
    qreal height() const;

    bool isVisible() const;
    void setVisible(bool visible);
    void showFullScreen();

Q_SIGNALS:
    void widthChanged(qreal w);
    void heightChanged(qreal h);
    void visibleChanged(bool visible);

protected:
    QNativeWindow(QNativeWindowPrivate &dd, QObject *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativeWindow)
    Q_DISABLE_COPY(QNativeWindow)
};

QT_END_NAMESPACE

#endif // QNATIVEWINDOW_H
