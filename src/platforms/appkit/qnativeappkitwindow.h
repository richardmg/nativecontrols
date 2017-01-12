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

#ifndef QNATIVEAPPKITWINDOW_H
#define QNATIVEAPPKITWINDOW_H

#include <QtNativeControls/qnativeplatformwindow.h>

#include <QtNativeAppKitControls/qnativeappkitbase.h>

QT_BEGIN_NAMESPACE

class QNativeAppKitWindowPrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(NSWindow);

class Q_NATIVEAPPKITCONTROLS_EXPORT QNativeAppKitWindow : public QNativeAppKitBase, public virtual QNativePlatformWindow
{
    Q_OBJECT

public:
    QNativeAppKitWindow();
    virtual ~QNativeAppKitWindow();

    NSWindow *nsWindowHandle() const;

    virtual qreal width() const override;
    virtual qreal height() const override;

    virtual bool isVisible() const override;
    virtual void setVisible(bool isVisible) override;
    virtual void showFullScreen() override;

    virtual bool event(QEvent *e) override;

Q_SIGNALS:
    void widthChanged(qreal w);
    void heightChanged(qreal h);
    void visibleChanged(bool isVisible);

protected:
    QNativeAppKitWindow(QNativeAppKitWindowPrivate &dd);

private:
    Q_DECLARE_PRIVATE(QNativeAppKitWindow)
    Q_DISABLE_COPY(QNativeAppKitWindow)
};

QT_END_NAMESPACE

#endif // QNATIVEAPPKITWINDOW_H
