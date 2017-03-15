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

#ifndef QNATIVEAPPKITTABVIEWITEM_H
#define QNATIVEAPPKITTABVIEWITEM_H

#include <QObject>

#include <QtUniControls/quniplatformtabspagetab.h>
#include <QtUniAppKitControls/quniappkitview.h>

QT_BEGIN_NAMESPACE

class QUniAppKitTabViewItemPrivate;
class QUniAppKitViewController;
Q_FORWARD_DECLARE_OBJC_CLASS(NSTabViewItem);

class Q_NATIVEAPPKITCONTROLS_EXPORT QUniAppKitTabViewItem : public QUniAppKitBase, public virtual QUniPlatformTabsPageTab
{
    Q_OBJECT

public:
    explicit QUniAppKitTabViewItem(QUniAppKitBase *parent = nullptr);
    explicit QUniAppKitTabViewItem(const QString &title, QUniAppKitBase *parent = nullptr);
    virtual ~QUniAppKitTabViewItem();

    virtual QString title() const override;
    virtual void setTitle(const QString &title) override;

    void setViewController(QUniAppKitViewController *viewController);
    QUniAppKitViewController *viewController() const;

    NSTabViewItem *nsTabViewItemHandle();

protected:
    QUniAppKitTabViewItem(QUniAppKitTabViewItemPrivate &dd, QUniAppKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniAppKitTabViewItem)
    Q_DISABLE_COPY(QUniAppKitTabViewItem)
};

QT_END_NAMESPACE

#endif // QNATIVEAPPKITTABVIEWITEM_H