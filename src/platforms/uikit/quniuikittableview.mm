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

#include <QtUniUIKitControls/quniuikittableview.h>
#include <QtUniUIKitControls/quniuikittableviewcell.h>
#include <QtUniUIKitControls/quniuikittableviewdatasource.h>
#include <QtUniUIKitControls/private/quniuikittableview_p.h>
#include <QtUniUIKitControls/private/quniuikittableviewcell_p.h>

QT_BEGIN_NAMESPACE

QUniUIKitTableViewPrivate::QUniUIKitTableViewPrivate(int version)
    : QUniUIKitControlPrivate(version)
{
}

QUniUIKitTableViewPrivate::~QUniUIKitTableViewPrivate()
{
}

void QUniUIKitTableViewPrivate::createNSObject()
{
    UITableView *uiTableView = [[[UITableView alloc] initWithFrame:CGRectZero] autorelease];
    [uiTableView sizeToFit];
    setNSObject(uiTableView);
}

UITableView *QUniUIKitTableViewPrivate::uiTableView() const
{
    return static_cast<UITableView *>(view());
}

QUniUIKitTableView::QUniUIKitTableView(QUniUIKitBase *parent)
    : QUniUIKitControl(*new QUniUIKitTableViewPrivate(), parent)
{
}

QUniUIKitTableView::QUniUIKitTableView(QUniUIKitTableViewPrivate &dd, QUniUIKitBase *parent)
    : QUniUIKitControl(dd, parent)
{
}

QUniUIKitTableView::~QUniUIKitTableView()
{
}

UITableView *QUniUIKitTableView::uiTableViewHandle()
{
    return d_func()->uiTableView();
}

QUniUIKitTableViewCell *QUniUIKitTableView::dequeueReusableCellWithIdentifier(const QString &id)
{
    NSString *nsID = id.toNSString();
    if (UITableViewCell *cell = [uiTableViewHandle() dequeueReusableCellWithIdentifier:nsID]) {
        if ([cell isKindOfClass:[QUniUITableViewCell class]])
            return [static_cast<QUniUITableViewCell *>(cell) qUniUiKitTableViewCellHandle];
    }

    return nullptr;
}

QUniUIKitTableViewDataSource *QUniUIKitTableView::dataSource() const
{
    return d_func()->m_dataSource;
}

void QUniUIKitTableView::setDataSource(QUniUIKitTableViewDataSource *dataSource)
{
    Q_D(QUniUIKitTableView);

    if (d->m_dataSource == dataSource)
        return;

    d->m_dataSource = dataSource;
    uiTableViewHandle().dataSource = static_cast<NSObject<UITableViewDataSource> *>(dataSource->uiTableViewDataSourceHandle());

    emit dataSourceChanged(dataSource);
}

#include "moc_quniuikittableview.cpp"

QT_END_NAMESPACE

