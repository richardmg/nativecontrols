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

#include <AppKit/AppKit.h>

#include <QtCore>

#include <QtNativeControls/qnativebase.h>
#include <QtNativeAppKitControls/qnativeappkitbase.h>
#include <QtNativeAppKitControls/private/qnativeappkitbase_p.h>

QT_BEGIN_NAMESPACE

QNativeAppKitBasePrivate::QNativeAppKitBasePrivate(int version)
    : QObjectPrivate(version)
    , m_attributes(0)
    , m_view(nil)
{
}

QNativeAppKitBasePrivate::~QNativeAppKitBasePrivate()
{
    [m_view release];
}

NSView *QNativeAppKitBasePrivate::view()
{
    return m_view;
}

NSView *QNativeAppKitBasePrivate::view() const
{
    return m_view;
}

void QNativeAppKitBasePrivate::setView(NSView *view)
{
    [m_view release];
    m_view = [view retain];
}

QNativeAppKitBase::QNativeAppKitBase(QObject *parent)
    : QObject(*new QNativeAppKitBasePrivate(), parent)
{
}

QNativeAppKitBase::QNativeAppKitBase(QNativeAppKitBasePrivate &dd, QObject *parent)
    : QObject(dd, parent)
{
}

QNativeAppKitBase::~QNativeAppKitBase()
{
}

void QNativeAppKitBase::setPlatformParent(QNativePlatformBase *parent)
{
    setParent(dynamic_cast<QNativeAppKitBase *>(parent));
}

QRectF qt_mac_flipRect(const NSRect &rect, NSView *view);

static void qt_mac_removeFromSuperview(NSView *view)
{
    const BOOL hadSuperview = !!view.superview;
    const QRectF rect = qt_mac_flipRect(view.frame, view);
    [view removeFromSuperview];
    if (hadSuperview)
        view.frame = NSMakeRect(rect.x(), rect.y(), rect.width(), rect.height());
}

void QNativeAppKitBase::childEvent(QChildEvent *event)
{
    Q_D(QNativeAppKitBase);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QNativeAppKitBasePrivate *dptr_child = dynamic_cast<QNativeAppKitBasePrivate *>(QObjectPrivate::get(event->child()));
    if (!dptr_child)
        return;

    // The flipping machinery here is designed to interop with Cocoa's flipped coordinate system:
    // before we deparent a view, we flip its frame to a top-left origin and then set that as the
    // frame after the control is deparented. Then, when we parent a view, we flip its top-left
    // frame to a bottom-left (AppKit) frame after parenting it. This allows views to always use
    // top-left (Qt) origins while parenting to either flipped or non-flipped views. Note that
    // autoresizing will still interfere with top-left origins so we give fixed-size controls
    // the default AppKit autoresizing mask (NSViewMaxXMargin | NSViewMinYMargin) to compensate.
    if (event->added()) {
        if (dptr_child->view().superview)
            qt_mac_removeFromSuperview(dptr_child->view());
        [d->view() addSubview:dptr_child->view()];
        const QRectF rect = qt_mac_flipRect(dptr_child->view().frame, dptr_child->view());
        dptr_child->view().frame = NSMakeRect(rect.x(), rect.y(), rect.width(), rect.height());
    } else if (event->removed()) {
        qt_mac_removeFromSuperview(dptr_child->view());
    }
}

#include "moc_qnativeappkitbase.cpp"

QT_END_NAMESPACE
