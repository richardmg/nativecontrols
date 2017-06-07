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
#include <QtUniUIKitControls/private/quniuikitpropertymacros_p.h>

QT_BEGIN_NAMESPACE

QUniUIKitTableViewCellPrivate::QUniUIKitTableViewCellPrivate(int version)
    : QUniUIKitViewPrivate(version)
    , m_cellStyle(QUniUIKitTableViewCell::StyleDefault)
{
    Q_Q(QUniUIKitTableViewCell);
    // Avoid mapping enum values directly to UIKit enum values in the enum
    // declaration, since then we require all users of the header file to compile as obj-c++.
    Q_ASSERT(int(QUniUIKitTableViewCell::StyleDefault) == int(UITableViewCellStyleDefault));

    // Create temporary labels, since we cannot create a UITableViewCell
    // before we know cellStyle and reuseIdentifier.
    m_textLabel = new QUniUIKitLabel(q);
    m_detailTextLabel = new QUniUIKitLabel(q);
}

QUniUIKitTableViewCellPrivate::~QUniUIKitTableViewCellPrivate()
{
}

void QUniUIKitTableViewCellPrivate::createNSObject()
{
    NSString *id = m_reuseIdentifier.toNSString();
    UITableViewCellStyle cellStyle = static_cast<UITableViewCellStyle>(m_cellStyle);
    UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:cellStyle reuseIdentifier:id];
    setNSObject([cell autorelease]);
}

void QUniUIKitTableViewCellPrivate::setNSObject(NSObject *nsObject)
{
    QUniUIKitViewPrivate::setNSObject(nsObject);
    syncTextLabel();
    syncDetailTextLabel();
}

UITableViewCell *QUniUIKitTableViewCellPrivate::uiTableViewCell() const
{
    return static_cast<UITableViewCell *>(view());
}

void QUniUIKitTableViewCellPrivate::syncReuseIdentifier()
{
    qWarning("TableViewCell: reuseIdentifer cannot change once the backing UITableViewCell has been created!");
}

void QUniUIKitTableViewCellPrivate::syncCellStyle()
{
    qWarning("TableViewCell: cellStyle cannot change once the backing UITableViewCell has been created!");
}

void QUniUIKitTableViewCellPrivate::syncTextLabel()
{
    auto placeholder = m_textLabel;
    m_textLabel = new QUniUIKitLabel(uiTableViewCell().textLabel, q_func());
    m_textLabel->setText(placeholder->text());

    delete placeholder;
}

void QUniUIKitTableViewCellPrivate::syncDetailTextLabel()
{
    if (!uiTableViewCell().detailTextLabel)
        return;

    auto placeholder = m_detailTextLabel;
    m_detailTextLabel = new QUniUIKitLabel(uiTableViewCell().detailTextLabel, q_func());
    m_detailTextLabel->setText(placeholder->text());

    delete placeholder;
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

SYNTHESIZE_QPROPERTY_CACHED(reuseIdentifier, ReuseIdentifier, QString, QUniUIKitTableViewCell)
SYNTHESIZE_QPROPERTY_CACHED(cellStyle, CellStyle, QUniUIKitTableViewCell::CellStyle, QUniUIKitTableViewCell)
SYNTHESIZE_QPROPERTY_GETTER_CACHED_POINTER(textLabel, QUniUIKitLabel, QUniUIKitTableViewCell)
SYNTHESIZE_QPROPERTY_GETTER_CACHED_POINTER(detailTextLabel, QUniUIKitLabel, QUniUIKitTableViewCell)

#include "moc_quniuikittableviewcell.cpp"

QT_END_NAMESPACE

