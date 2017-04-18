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

#include <QtUniUIKitControls/quniuikitsearchfield.h>
#include <QtUniUIKitControls/private/quniuikitsearchfield_p.h>

@interface QUniUIKitSearchFieldDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QUniUIKitSearchFieldPrivate) *_searchField;
}
@end

@implementation QUniUIKitSearchFieldDelegate

-(id)initWithQUniUIKitSearchFieldPrivate:(QT_PREPEND_NAMESPACE(QUniUIKitSearchFieldPrivate) *)searchField
{
    self = [self init];
    if (self) {
        _searchField = searchField;
    }

    return self;
}

@end

QT_BEGIN_NAMESPACE

QUniUIKitSearchFieldPrivate::QUniUIKitSearchFieldPrivate(int version)
    : QUniUIKitControlPrivate(version)
    , m_delegate(nullptr)
{
}

QUniUIKitSearchFieldPrivate::~QUniUIKitSearchFieldPrivate()
{
    [m_delegate release];
}

UIView *QUniUIKitSearchFieldPrivate::createView()
{
    m_delegate = [[QUniUIKitSearchFieldDelegate alloc] initWithQUniUIKitSearchFieldPrivate:this];

    UISearchBar *uiSearchField = [[[UISearchBar alloc] init] autorelease];
    [uiSearchField sizeToFit];

    return uiSearchField;
}

QUniUIKitSearchField::QUniUIKitSearchField(QUniUIKitBase *parent)
    : QUniUIKitControl(*new QUniUIKitSearchFieldPrivate(), parent)
{
}

QUniUIKitSearchField::QUniUIKitSearchField(const QString &text, QUniUIKitBase *parent)
    : QUniUIKitControl(*new QUniUIKitSearchFieldPrivate(), parent)
{
    setText(text);
}

QUniUIKitSearchField::QUniUIKitSearchField(QUniUIKitSearchFieldPrivate &dd, QUniUIKitBase *parent)
    : QUniUIKitControl(dd, parent)
{
}

QUniUIKitSearchField::~QUniUIKitSearchField()
{
    Q_D(QUniUIKitSearchField);
    [d->m_delegate release];
}

UISearchBar *QUniUIKitSearchField::uiSearchBarHandle()
{
    return static_cast<UISearchBar *>(d_func()->view());
}

QString QUniUIKitSearchField::text()
{
    return QString::fromNSString(uiSearchBarHandle().text);
}

void QUniUIKitSearchField::setText(const QString &newText)
{
    if (newText == text())
        return;

    uiSearchBarHandle().text = newText.toNSString();
    d_func()->updateIntrinsicContentSize();

    emit textChanged(newText);
}

QString QUniUIKitSearchField::placeholderText()
{
    return QString::fromNSString(uiSearchBarHandle().placeholder);
}

void QUniUIKitSearchField::setPlaceholderText(const QString &newPlaceholderText)
{
    if (newPlaceholderText == placeholderText())
        return;

    uiSearchBarHandle().placeholder = newPlaceholderText.toNSString();
    d_func()->updateIntrinsicContentSize();

    emit placeholderTextChanged(newPlaceholderText);
}

#include "moc_quniuikitsearchfield.cpp"
