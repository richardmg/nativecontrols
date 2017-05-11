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
#include <QtUniUIKitControls/quniuikitlabel.h>
#include <QtUniUIKitControls/private/quniuikittableviewcell_p.h>

@implementation QUniUITableViewCell

-(id)initWithQUniUIKitTableViewCellPrivate:(QT_PREPEND_NAMESPACE(QUniUIKitTableViewCellPrivate) *)tableViewCellPrivate
{
    NSString *id = tableViewCellPrivate->m_reuseIndentifier.toNSString();
    UITableViewCellStyle cellStyle = static_cast<UITableViewCellStyle>(tableViewCellPrivate->m_cellStyle);
    self = [self initWithStyle:cellStyle reuseIdentifier:id];
    if (self) {
        _tableViewCellPrivate = tableViewCellPrivate;
    }

    return self;
}

-(QUniUIKitTableViewCell *)qUniUiKitTableViewCellHandle
{
    return _tableViewCellPrivate->q_func();
}

@end

QT_BEGIN_NAMESPACE

QUniUIKitTableViewCellPrivate::QUniUIKitTableViewCellPrivate(int version)
    : QUniUIKitViewPrivate(version)
    , m_textLabel(nullptr)
    , m_detailTextLabel(nullptr)
    , m_cellStyle(QUniUIKitTableViewCell::StyleDefault)
{
    // Avoid assiging UITableViewCellStyleDefault directly into the enum, since
    // then we require all users of the header file to compile as obj-c++.
    Q_ASSERT(int(QUniUIKitTableViewCell::StyleDefault) == int(UITableViewCellStyleDefault));
}

QUniUIKitTableViewCellPrivate::~QUniUIKitTableViewCellPrivate()
{
}

void QUniUIKitTableViewCellPrivate::createNSObject()
{
    QUniUITableViewCell *uiCell = [[QUniUITableViewCell alloc] initWithQUniUIKitTableViewCellPrivate:this];
    [uiCell autorelease];
    setNSObject(uiCell);
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

QUniUIKitLabel *QUniUIKitTableViewCell::textLabel() const
{
    Q_D(const QUniUIKitTableViewCell);
    if (!d->m_textLabel) {
        QUniUIKitTableViewCell *me = const_cast<QUniUIKitTableViewCell *>(this);
        me->d_func()->m_textLabel = new QUniUIKitLabel(me->uiTableViewCellHandle().textLabel, me);
    }
    return d->m_textLabel;
}

QUniUIKitLabel *QUniUIKitTableViewCell::detailTextLabel() const
{
    Q_D(const QUniUIKitTableViewCell);
    if (!d->m_detailTextLabel) {
        QUniUIKitTableViewCell *me = const_cast<QUniUIKitTableViewCell *>(this);
        me->d_func()->m_detailTextLabel = new QUniUIKitLabel(me->uiTableViewCellHandle().detailTextLabel, me);
    }
    return d->m_detailTextLabel;
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
    if (d->isNSObjectCreated()) {
        qWarning("TableViewCell: reuseIdentifer cannot change once the backing UITableViewCell has been created!");
        return;
    }

    d->m_reuseIndentifier = newReuseIdentifier;
}

QUniUIKitTableViewCell::CellStyle QUniUIKitTableViewCell::cellStyle() const
{
    return d_func()->m_cellStyle;
}

void QUniUIKitTableViewCell::setCellStyle(QUniUIKitTableViewCell::CellStyle cellStyle)
{
    Q_D(QUniUIKitTableViewCell);
    if (d->m_cellStyle == cellStyle)
        return;

    if (d->isNSObjectCreated()) {
        qWarning("TableViewCell: cellStyle cannot change once the backing UITableViewCell has been created!");
        return;
    }

    d->m_cellStyle = cellStyle;
    emit cellStyleChanged(cellStyle);
}

#include "moc_quniuikittableviewcell.cpp"

QT_END_NAMESPACE

