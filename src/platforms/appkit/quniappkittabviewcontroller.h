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

#ifndef QNATIVEAPPKITTABVIEWCONTROLLER_H
#define QNATIVEAPPKITTABVIEWCONTROLLER_H

#include <QObject>

#include <QtUniAppKitControls/quniappkitviewcontroller.h>
#include <QtUniControls/quniplatformtabspage.h>

QT_BEGIN_NAMESPACE

class QUniAppKitTabViewControllerPrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(NSTabViewController);

class Q_NATIVEAPPKITCONTROLS_EXPORT QUniAppKitTabViewController : public QUniAppKitViewController, public virtual QUniPlatformTabsPage
{
    Q_OBJECT

public:
    QUniAppKitTabViewController(QUniAppKitBase *parent = nullptr);
    virtual ~QUniAppKitTabViewController();

    void setTabViewItems(QList<QUniAppKitTabViewItem *> list);
    QList<QUniAppKitTabViewItem *> tabViewItems() const;

    NSTabViewController *nsTabViewControllerHandle();
    QUniAppKitView *view() const;

protected:
    QUniAppKitTabViewController(QUniAppKitTabViewControllerPrivate &dd, QUniAppKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniAppKitTabViewController)
    Q_DISABLE_COPY(QUniAppKitTabViewController)
};

QT_END_NAMESPACE

#endif // QNATIVEAPPKITTABVIEWCONTROLLER_H