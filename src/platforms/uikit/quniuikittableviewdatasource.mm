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
#include <QtQml/qqmlengine.h>

#include <QtUniUIKitControls/quniuikittableviewdatasource.h>
#include <QtUniUIKitControls/quniuikittableview.h>
#include <QtUniUIKitControls/quniuikitindexpath.h>
#include <QtUniUIKitControls/quniuikittableviewcell.h>
#include <QtUniUIKitControls/private/quniuikittableviewdatasource_p.h>
#include <QtUniUIKitControls/private/quniuikittableview_p.h>
#include <QtUniUIKitControls/private/quniuikitpropertymacros_p.h>

@interface QUniUITableViewDataSource : NSObject <UITableViewDataSource>
{
    QT_PREPEND_NAMESPACE(QUniUIKitTableViewDataSourcePrivate) *_dataSourcePrivate;
}
@end

@implementation QUniUITableViewDataSource

-(id)initWithQUniUIKitTableViewDataSourcePrivate:(QT_PREPEND_NAMESPACE(QUniUIKitTableViewDataSourcePrivate) *)dataSourcePrivate
{
    self = [self init];
    if (self) {
        _dataSourcePrivate = dataSourcePrivate;
    }

    return self;
}

- (UITableViewCell *)emptyCell
{
    // Rather than causing an exception to be thrown if we fail getting a valid cell in
    // method 'cellForRowAtIndexPath', we return an emtpy cell to UIKit.
    return [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@""] autorelease];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    GET_PROPERTY_QJSVALUE(_dataSourcePrivate->m_numberOfSectionsInTableView, QUniUIKitTableView, tableView)
    return property.toInt();
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    GET_PROPERTY_QJSVALUE_BEGIN(_dataSourcePrivate->m_numberOfRowsInSection, QUniUIKitTableView, tableView)
    args << QJSValue((int)section);
    GET_PROPERTY_QJSVALUE_END
    return property.toInt();
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    GET_PROPERTY_QJSVALUE_BEGIN(_dataSourcePrivate->m_cellForRowAtIndexPath, QUniUIKitTableView, tableView)
    QUniUIKitIndexPath qindexPath(indexPath);
    args << engine->newQObject(&qindexPath);
    GET_PROPERTY_QJSVALUE_END

    if (QUniUIKitTableViewCell *cell = dynamic_cast<QUniUIKitTableViewCell *>(property.toQObject()))
        return cell->uiTableViewCellHandle();
    else
        return [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@""] autorelease];
}

- (NSArray<NSString *> *)sectionIndexTitlesForTableView:(UITableView *)tableView
{
    GET_PROPERTY_QJSVALUE(_dataSourcePrivate->m_sectionIndexTitlesForTableView, QUniUIKitTableView, tableView)
    QVariantList list = property.toVariant().toList();

    NSMutableArray *titleArray = [NSMutableArray arrayWithCapacity:list.length()];
    for (QVariant title : list)
       [titleArray addObject:title.toString().toNSString()];

    return titleArray;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    GET_PROPERTY_QJSVALUE_BEGIN(_dataSourcePrivate->m_titleForHeaderInSection, QUniUIKitTableView, tableView)
    args << QJSValue((int)section);
    GET_PROPERTY_QJSVALUE_END
    return property.toString().toNSString();
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section
{
    GET_PROPERTY_QJSVALUE_BEGIN(_dataSourcePrivate->m_titleForFooterInSection, QUniUIKitTableView, tableView)
    args << QJSValue((int)section);
    GET_PROPERTY_QJSVALUE_END
    return property.isUndefined() ? nil : property.toString().toNSString();
}

@end

QT_BEGIN_NAMESPACE

QUniUIKitTableViewDataSourcePrivate::QUniUIKitTableViewDataSourcePrivate(int version)
    : QUniUIKitBasePrivate(version)
{
    m_dataSource = [[QUniUITableViewDataSource alloc] initWithQUniUIKitTableViewDataSourcePrivate:this];
}

QUniUIKitTableViewDataSourcePrivate::~QUniUIKitTableViewDataSourcePrivate()
{
    [m_dataSource release];
}

QUniUIKitTableViewDataSource::QUniUIKitTableViewDataSource(QUniUIKitBase *parent)
    : QUniUIKitBase(*new QUniUIKitTableViewDataSourcePrivate(), parent)
{
}

QUniUIKitTableViewDataSource::~QUniUIKitTableViewDataSource()
{
}

NSObject *QUniUIKitTableViewDataSource::uiTableViewDataSourceHandle() const
{
    return d_func()->m_dataSource;
}

IMPLEMENT_PROPERTY_QJSVALUE(QUniUIKitTableViewDataSource, numberOfSectionsInTableView, setNumberOfSectionsInTableView, toInt)
IMPLEMENT_PROPERTY_QJSVALUE(QUniUIKitTableViewDataSource, numberOfRowsInSection, setNumberOfRowsInSection, toInt)
IMPLEMENT_PROPERTY_QJSVALUE(QUniUIKitTableViewDataSource, titleForHeaderInSection, setTitleForHeaderInSection, toString)
IMPLEMENT_PROPERTY_QJSVALUE(QUniUIKitTableViewDataSource, cellForRowAtIndexPath, setCellForRowAtIndexPath, toQObject)
IMPLEMENT_PROPERTY_QJSVALUE(QUniUIKitTableViewDataSource, sectionIndexTitlesForTableView, setSectionIndexTitlesForTableView, toVariant)
IMPLEMENT_PROPERTY_QJSVALUE(QUniUIKitTableViewDataSource, titleForFooterInSection, setTitleForFooterInSection, toString)

#include "moc_quniuikittableviewdatasource.cpp"

QT_END_NAMESPACE
