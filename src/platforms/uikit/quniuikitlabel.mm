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

#include <QtUniUIKitControls/quniuikitlabel.h>
#include <QtUniUIKitControls/private/quniuikitlabel_p.h>

QT_BEGIN_NAMESPACE

QUniUIKitLabelPrivate::QUniUIKitLabelPrivate(int version)
    : QUniUIKitViewPrivate(version)
{
}

QUniUIKitLabelPrivate::~QUniUIKitLabelPrivate()
{
    [m_delegate release];
}

void QUniUIKitLabelPrivate::createView()
{
    UILabel *uiLabel = [[[UILabel alloc] initWithFrame:CGRectZero] autorelease];
    [uiLabel sizeToFit];
    setView(uiLabel);
}

UILabel *QUniUIKitLabelPrivate::uiLabel() const
{
    return static_cast<UILabel *>(view());
}

QUniUIKitLabel::QUniUIKitLabel(QUniUIKitBase *parent)
    : QUniUIKitView(*new QUniUIKitLabelPrivate(), parent)
{
}

QUniUIKitLabel::QUniUIKitLabel(UILabel *label, QUniUIKitBase *parent)
    : QUniUIKitView(*new QUniUIKitLabelPrivate(), parent)
{
    d_func()->setView(label);
}

QUniUIKitLabel::QUniUIKitLabel(QUniUIKitLabelPrivate &dd, QUniUIKitBase *parent)
    : QUniUIKitView(dd, parent)
{
}

QUniUIKitLabel::~QUniUIKitLabel()
{
}

UILabel *QUniUIKitLabel::uiLabelHandle()
{
    return d_func()->uiLabel();
}

QString QUniUIKitLabel::text() const
{
    return QString::fromNSString(d_func()->uiLabel().text);
}

void QUniUIKitLabel::setText(const QString &newText)
{
    if (newText == text())
        return;

    Q_D(QUniUIKitLabel);
    d->uiLabel().text = newText.toNSString();
    d->updateIntrinsicContentSize();

    emit textChanged(newText);
}

#include "moc_quniuikitlabel.cpp"

QT_END_NAMESPACE

