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

#ifndef QNATIVEAPPKITWINDOW_H
#define QNATIVEAPPKITWINDOW_H

#include <QtNativeControls/quniplatformwindow.h>

#include <QtNativeAppKitControls/quniappkitview.h>

QT_BEGIN_NAMESPACE

class QNativeAppKitWindowPrivate;
class QNativeAppKitViewController;
Q_FORWARD_DECLARE_OBJC_CLASS(NSWindow);

class Q_NATIVEAPPKITCONTROLS_EXPORT QNativeAppKitWindow : public QNativeAppKitBase, public virtual QNativePlatformWindow
{
    Q_OBJECT
    Q_PROPERTY(QNativeAppKitViewController *contentViewController READ contentViewController WRITE setContentViewController NOTIFY contentViewControllerChanged)

public:
    QNativeAppKitWindow();
    virtual ~QNativeAppKitWindow();

    virtual qreal width() const override;
    virtual qreal height() const override;

    virtual bool isVisible() const override;
    virtual void setVisible(bool isVisible) override;
    virtual void showFullScreen() override;

    virtual bool event(QEvent *e) override;

    NSWindow *nsWindowHandle();

    void setContentViewController(QNativeAppKitViewController *contentViewController);
    QNativeAppKitViewController *contentViewController() const;

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
    void widthChanged(qreal w);
    void heightChanged(qreal h);
    void visibleChanged(bool isVisible);
    void contentViewControllerChanged(QNativeAppKitViewController *controller);

protected:
    QNativeAppKitWindow(QNativeAppKitWindowPrivate &dd);
    void childEvent(QChildEvent *event) override;

private:
    Q_DECLARE_PRIVATE(QNativeAppKitWindow)
    Q_DISABLE_COPY(QNativeAppKitWindow)
};

QT_END_NAMESPACE

#endif // QNATIVEAPPKITWINDOW_H
