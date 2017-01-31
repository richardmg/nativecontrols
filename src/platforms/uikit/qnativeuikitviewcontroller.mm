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

#include <QtCore>

#include <QtNativeUIKitControls/qnativeuikitviewcontroller.h>
#include <QtNativeUIKitControls/qnativeuikitview.h>
#include <QtNativeUIKitControls/private/qnativeuikitviewcontroller_p.h>

QT_BEGIN_NAMESPACE

QNativeUIKitViewControllerPrivate::QNativeUIKitViewControllerPrivate(int version)
    : QNativeUIKitBasePrivate(version)
    , m_viewController(nullptr)
    , m_view(nullptr)
{
    m_viewController = [UIViewController new];
}

QNativeUIKitViewControllerPrivate::~QNativeUIKitViewControllerPrivate()
{
    [m_viewController release];
}

QNativeUIKitViewController::QNativeUIKitViewController(QNativeUIKitBase *parent)
    : QNativeUIKitBase(*new QNativeUIKitViewControllerPrivate(), parent)
{
}

QNativeUIKitViewController::QNativeUIKitViewController(QNativeUIKitViewControllerPrivate &dd, QNativeUIKitBase *parent)
    :QNativeUIKitBase(dd, parent)
{
}

QNativeUIKitViewController::~QNativeUIKitViewController()
{
}

QNativeUIKitView *QNativeUIKitViewController::view() const
{
    Q_D(const QNativeUIKitViewController);
    if (!d->m_view) {
        QNativeUIKitViewController *self = const_cast<QNativeUIKitViewController *>(this);
        self->setView(new QNativeUIKitView(self));
    }
    return d->m_view;
}

void QNativeUIKitViewController::setView(QNativeUIKitView *view)
{
    Q_D(QNativeUIKitViewController);
    if (d->m_view == view)
        return;

    d->m_view = view;
    d->m_viewController.view = d->m_view->uiViewHandle();
    emit viewChanged(view);
}

UIViewController *QNativeUIKitViewController::uiViewControllerHandle()
{
    return d_func()->m_viewController;
}

#include "moc_qnativeuikitviewcontroller.cpp"

QT_END_NAMESPACE
