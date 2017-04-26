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

#include <QtUniUIKitControls/quniuikittableviewcell.h>
#include <QtUniUIKitControls/private/quniuikittableviewcell_p.h>

@implementation QUniUITableViewCell

-(id)initWithQUniUIKitTableViewCellPrivate:(QT_PREPEND_NAMESPACE(QUniUIKitTableViewCellPrivate) *)quniuikittableviewcell
{
    NSString *id = quniuikittableviewcell->m_reuseIndentifier.toNSString();
    self = [self initWithStyle:UITableViewCellStyleDefault reuseIdentifier:id];
    if (self) {

        // NB: TAKE EXTRA CARE OF OWNERSHIP.
        // We should probably let UITableView take ownership over this object, so it gets deleted
        // when the table view no longer needs it. But the problem then, is that we should also
        // delete QUniUIKitTableViewCell. But that object might still be referenced from QML.
        // It might be OK as it is, since QML will probably delete QUniUIKitTableViewCell once
        // no-one uses it, which will send a release to QUniTableViewCell. And then UITableView
        // will release it once more when it doesn't need either. Which will deallocate it.

        _quniuikittableviewcell = quniuikittableviewcell;
    }

    return self;
}

-(QUniUIKitTableViewCell *)qUniUiKitTableViewCellHandle
{
    return _quniuikittableviewcell->q_func();
}

@end

QT_BEGIN_NAMESPACE

QUniUIKitTableViewCellPrivate::QUniUIKitTableViewCellPrivate(int version)
    : QUniUIKitViewPrivate(version)
{
}

QUniUIKitTableViewCellPrivate::~QUniUIKitTableViewCellPrivate()
{
}

UIView *QUniUIKitTableViewCellPrivate::createView()
{
    return [[QUniUITableViewCell alloc] initWithQUniUIKitTableViewCellPrivate:this];
}

QUniUITableViewCell *QUniUIKitTableViewCellPrivate::uiTableViewCell() const
{
    return static_cast<QUniUITableViewCell *>(view());
}

QUniUIKitTableViewCell::QUniUIKitTableViewCell(QUniUIKitBase *parent)
    : QUniUIKitView(*new QUniUIKitTableViewCellPrivate(), parent)
{
}

QUniUIKitTableViewCell::QUniUIKitTableViewCell(const QString &reuseIdentifier, QUniUIKitBase *parent)
    : QUniUIKitView(*new QUniUIKitTableViewCellPrivate(), parent)
{
    setReuseIdentifier(reuseIdentifier);
}

QUniUIKitTableViewCell::QUniUIKitTableViewCell(QUniUIKitTableViewCellPrivate &dd, QUniUIKitBase *parent)
    : QUniUIKitView(dd, parent)
{
}

QUniUIKitTableViewCell::~QUniUIKitTableViewCell()
{
}

UITableViewCell *QUniUIKitTableViewCell::uiTableViewCellHandle()
{
    return d_func()->uiTableViewCell();
}

QString QUniUIKitTableViewCell::text() const
{
    return QString::fromNSString(d_func()->uiTableViewCell().textLabel.text);
}

void QUniUIKitTableViewCell::setText(const QString &newText)
{
    if (newText == text())
        return;

    d_func()->uiTableViewCell().textLabel.text = newText.toNSString();
    d_func()->updateIntrinsicContentSize();

    emit textChanged(newText);
}

QString QUniUIKitTableViewCell::reuseIdentifier() const
{
    return d_func()->m_reuseIndentifier;
}

void QUniUIKitTableViewCell::setReuseIdentifier(const QString &newReuseIdentifier)
{
    if (newReuseIdentifier == reuseIdentifier())
        return;

    Q_D(QUniUIKitTableViewCell);
    if (d->isViewCreated()) {
        qWarning("TableViewCell: reuseIdentifer cannot change once the backing UITableViewCell has been created!");
        return;
    }

    d->m_reuseIndentifier = newReuseIdentifier;
}

#include "moc_quniuikittableviewcell.cpp"

QT_END_NAMESPACE

