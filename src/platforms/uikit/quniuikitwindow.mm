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

#include <UIKit/UIKit.h>

#include <QtGui/qwindow.h>
#include <QtCore/private/qobject_p.h>
#include <QtUniUIKitControls/quniuikitwindow.h>
#include <QtUniUIKitControls/quniuikitviewcontroller.h>
#include <QtUniUIKitControls/private/quniuikitwindow_p.h>
#include <QtUniUIKitControls/private/quniuikitviewcontroller_p.h>
#include <QtUniUIKitControls/private/quniuikitview_p.h>
#include <QtUniUIKitControls/private/quniuikitpropertymacros_p.h>

QT_BEGIN_NAMESPACE

QUniUIKitWindowPrivate::QUniUIKitWindowPrivate(int version)
    : QUniUIKitViewPrivate(version)
    , m_rootViewController(nullptr)
{
}

QUniUIKitWindowPrivate::~QUniUIKitWindowPrivate()
{
}

void QUniUIKitWindowPrivate::addSubViewToContentView(UIView *uiView)
{
    Q_Q(QUniUIKitWindow);
    QUniUIKitView *contentView = q->rootViewController()->view();
    QUniUIKitViewPrivate *dptr_contentView = dynamic_cast<QUniUIKitViewPrivate *>(QObjectPrivate::get(contentView));
    dptr_contentView->addSubView(uiView);
}

void QUniUIKitWindowPrivate::createNSObject()
{
    if (!m_rootViewController)
        m_rootViewController = new QUniUIKitViewController(q_func());

    setNSObject([[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease]);
}

void QUniUIKitWindowPrivate::setNSObject(NSObject *nsObject)
{
    QUniUIKitViewPrivate::setNSObject(nsObject);

    syncRootViewController();
    syncVisible();
}

void QUniUIKitWindowPrivate::syncVisible()
{
    if (!m_visible)
        return;

    [q_func()->uiWindowHandle() makeKeyAndVisible];
    emit q_func()->visibleChanged(m_visible);
}

void QUniUIKitWindowPrivate::syncRootViewController()
{
    q_func()->uiWindowHandle().rootViewController = m_rootViewController->uiViewControllerHandle();
    emit q_func()->rootViewControllerChanged(m_rootViewController);
}

QUniUIKitWindow::QUniUIKitWindow()
    : QUniUIKitView(*new QUniUIKitWindowPrivate(), nullptr)
{
}

QUniUIKitWindow::QUniUIKitWindow(QUniUIKitWindowPrivate &dd)
    : QUniUIKitView(dd, nullptr)
{
}

QUniUIKitWindow::~QUniUIKitWindow()
{
}

SYNTHESIZE_QPROPERTY_CACHED_POINTER(rootViewController, RootViewController, QUniUIKitViewController, QUniUIKitWindow)
SYNTHESIZE_QPROPERTY_CACHED(visible, Visible, bool, QUniUIKitWindow)

UIWindow *QUniUIKitWindow::uiWindowHandle()
{
    return static_cast<UIWindow *>(d_func()->view());
}

void QUniUIKitWindow::showFullScreen()
{
    setVisible(true);
}

#include "moc_quniuikitwindow.cpp"

QT_END_NAMESPACE
