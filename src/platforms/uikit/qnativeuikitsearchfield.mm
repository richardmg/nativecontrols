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

#include <QtNativeControls/qnativetextfield.h>
#include <QtNativeUIKitControls/qnativeuikitsearchfield.h>
#include <QtNativeUIKitControls/private/qnativeuikitsearchfield_p.h>

@interface QNativeUIKitSearchFieldDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QNativeUIKitSearchFieldPrivate) *_searchField;
}
@end

@implementation QNativeUIKitSearchFieldDelegate

-(id)initWithQNativeUIKitSearchFieldPrivate:(QT_PREPEND_NAMESPACE(QNativeUIKitSearchFieldPrivate) *)searchField
{
    self = [self init];
    if (self) {
        _searchField = searchField;
    }

    return self;
}

@end

QT_BEGIN_NAMESPACE

QNativeUIKitSearchFieldPrivate::QNativeUIKitSearchFieldPrivate(int version)
    : QNativeUIKitControlPrivate(version)
    , m_delegate(nullptr)
{
}

QNativeUIKitSearchFieldPrivate::~QNativeUIKitSearchFieldPrivate()
{
    [m_delegate release];
}

void QNativeUIKitSearchFieldPrivate::connectSignals(QNativeBase *base)
{
    Q_Q(QNativeUIKitSearchField);
    QNativeUIKitControlPrivate::connectSignals(base);
    const auto b = static_cast<QNativeSearchField *>(base);
    q->connect(q, &QNativeUIKitSearchField::textChanged, b, &QNativeSearchField::textChanged);
    q->connect(q, &QNativeUIKitSearchField::placeholderTextChanged, b, &QNativeSearchField::placeholderTextChanged);
}

UIView *QNativeUIKitSearchFieldPrivate::createView()
{
    m_delegate = [[QNativeUIKitSearchFieldDelegate alloc] initWithQNativeUIKitSearchFieldPrivate:this];

    UISearchBar *uiSearchField = [[[UISearchBar alloc] init] autorelease];
    [uiSearchField sizeToFit];

    return uiSearchField;
}

QNativeUIKitSearchField::QNativeUIKitSearchField(QNativeUIKitBase *parent)
    : QNativeUIKitControl(*new QNativeUIKitSearchFieldPrivate(), parent)
{
}

QNativeUIKitSearchField::QNativeUIKitSearchField(const QString &text, QNativeUIKitBase *parent)
    : QNativeUIKitControl(*new QNativeUIKitSearchFieldPrivate(), parent)
{
    setText(text);
}

QNativeUIKitSearchField::QNativeUIKitSearchField(QNativeUIKitSearchFieldPrivate &dd, QNativeUIKitBase *parent)
    : QNativeUIKitControl(dd, parent)
{
}

QNativeUIKitSearchField::~QNativeUIKitSearchField()
{
    Q_D(QNativeUIKitSearchField);
    [d->m_delegate release];
}

UISearchBar *QNativeUIKitSearchField::uiSearchBarHandle()
{
    return static_cast<UISearchBar *>(d_func()->view());
}

QString QNativeUIKitSearchField::text()
{
    return QString::fromNSString(uiSearchBarHandle().text);
}

void QNativeUIKitSearchField::setText(const QString &newText)
{
    if (newText == text())
        return;

    uiSearchBarHandle().text = newText.toNSString();
    d_func()->updateImplicitSize();

    emit textChanged(newText);
}

QString QNativeUIKitSearchField::placeholderText()
{
    return QString::fromNSString(uiSearchBarHandle().placeholder);
}

void QNativeUIKitSearchField::setPlaceholderText(const QString &newPlaceholderText)
{
    if (newPlaceholderText == placeholderText())
        return;

    uiSearchBarHandle().placeholder = newPlaceholderText.toNSString();
    d_func()->updateImplicitSize();

    emit placeholderTextChanged(newPlaceholderText);
}

#include "moc_qnativeuikitsearchfield.cpp"
