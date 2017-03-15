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

#ifndef QNATIVEAPPKITVIEWCONTROLLER_H
#define QNATIVEAPPKITVIEWCONTROLLER_H

#include <QObject>

#include <QtNativeAppKitControls/quniappkitbase.h>
#include <QtNativeControls/quniplatformpage.h>

QT_BEGIN_NAMESPACE

class QUniAppKitView;
class QUniAppKitViewControllerPrivate;
class QUniAppKitTabViewItem;
Q_FORWARD_DECLARE_OBJC_CLASS(NSViewController);

class Q_NATIVEAPPKITCONTROLS_EXPORT QUniAppKitViewController : public QUniAppKitBase, public virtual QUniPlatformPage
{
    Q_OBJECT
    Q_PROPERTY(QUniAppKitView *view READ view WRITE setView NOTIFY viewChanged)

public:
    QUniAppKitViewController(QUniAppKitBase *parent = nullptr);
    ~QUniAppKitViewController();

    QUniAppKitView *view() const;
    void setView(QUniAppKitView *view);

    void setChildViewControllers(QList<QUniAppKitViewController *> list);
    QList<QUniAppKitViewController *> childViewControllers() const;

    QUniAppKitViewController *parentViewController();

    NSViewController *nsViewControllerHandle();

    bool setNativeParent(QObject *parent) override;
    bool setNativeParent(const QByteArray &type, void *parent) override;
    bool addNativeChild(QObject *child) override;
    bool addNativeChild(const QByteArray &type, void *child) override;
    QByteArrayList supportedNativeChildTypes() override;
    QByteArrayList supportedNativeParentTypes() override;

Q_SIGNALS:
    void viewChanged(QUniAppKitView *contentView);

protected:
    QUniAppKitViewController(QUniAppKitViewControllerPrivate &dd, QUniAppKitBase *parent = nullptr);
    void childEvent(QChildEvent *event) override;

private:
    Q_DECLARE_PRIVATE(QUniAppKitViewController)
    Q_DISABLE_COPY(QUniAppKitViewController)
};

QT_END_NAMESPACE

#endif // QNATIVEAPPKITVIEWCONTROLLER_H
