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

#ifndef QUNIIOSWINDOW_H
#define QUNIIOSWINDOW_H

#include <QtUniControls/quniplatformwindow.h>

#include <QtUniUIKitControls/quniuikitview.h>

QT_BEGIN_NAMESPACE

class QUniUIKitWindowPrivate;
class QUniUIKitViewController;
Q_FORWARD_DECLARE_OBJC_CLASS(UIWindow);

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitWindow : public QUniUIKitView, public virtual QUniPlatformWindow
{
    Q_OBJECT
    Q_PROPERTY(QUniUIKitViewController *rootViewController READ rootViewController WRITE setRootViewController NOTIFY rootViewControllerChanged)

public:
    QUniUIKitWindow();
    virtual ~QUniUIKitWindow();

    virtual bool isVisible() const override;
    virtual void setVisible(bool isVisible) override;
    virtual void showFullScreen() override;

    virtual QRectF geometry() const override;
    virtual void setGeometry(const QRectF &) override {}

    virtual void setPosition(const QPointF &) override {}
    virtual void resize(const QSizeF) override {}

    virtual bool event(QEvent *e) override;

    qreal width() const;
    qreal height() const;

    void setRootViewController(QUniUIKitViewController *rootViewController);
    QUniUIKitViewController *rootViewController() const;

    bool addNativeChild(QObject *child) override;
    bool addNativeChild(const QByteArray &type, void *child) override;
    QByteArrayList supportedNativeChildTypes() override;
    QByteArrayList supportedNativeParentTypes() override;

    UIWindow *uiWindowHandle();

Q_SIGNALS:
    void visibleChanged(bool isVisible);
    void rootViewControllerChanged(QUniUIKitViewController *controller);

protected:
    QUniUIKitWindow(QUniUIKitWindowPrivate &dd);

private:
    Q_DECLARE_PRIVATE(QUniUIKitWindow)
    Q_DISABLE_COPY(QUniUIKitWindow)
};

QT_END_NAMESPACE

#endif // QUNIIOSWINDOW_H
