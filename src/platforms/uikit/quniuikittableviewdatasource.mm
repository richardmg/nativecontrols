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
    QUniUIKitTableView *qtableView = static_cast<QUniUIKitTableView *>(QUniUIKitBasePrivate::getAssociatedObject(tableView));
    if (!qtableView)
        return 0;

    QJSValue jsFunction = _dataSourcePrivate->m_numberOfRowsInSection;
    if (jsFunction.isUndefined())
        return 0;

    if (!jsFunction.isCallable()) {
        qWarning("TableViewDataSource: property 'numberOfSectionsInTableView' doesn't point to a JS function");
        return 0;
    }

    QJSValue jsTableView = qmlEngine(qtableView)->newQObject(qtableView);
    QJSValue returnValue = jsFunction.call(QJSValueList() << jsTableView);
    if (!returnValue.isNumber()) {
        qWarning("TableViewDataSource: property 'numberOfSectionsInTableView' doesn't return a number");
        return 0;
    }

    return returnValue.toInt();
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    QUniUIKitTableView *qtableView = static_cast<QUniUIKitTableView *>(QUniUIKitBasePrivate::getAssociatedObject(tableView));
    if (!qtableView)
        return 0;

    QJSValue jsFunction = _dataSourcePrivate->m_numberOfRowsInSection;
    if (jsFunction.isUndefined())
        return 0;

    if (!jsFunction.isCallable()) {
        qWarning("TableViewDataSource: property 'numberOfRowsInSection' doesn't point to a JS function");
        return 0;
    }

    QJSValue jsTableView = qmlEngine(qtableView)->newQObject(qtableView);
    QJSValue jsSection((int)section);
    QJSValue returnValue = jsFunction.call(QJSValueList() << jsTableView << jsSection);
    if (!returnValue.isNumber()) {
        qWarning("TableViewDataSource: property 'numberOfRowsInSection' doesn't return a number");
        return 0;
    }

    return returnValue.toInt();
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    QUniUIKitTableView *qtableView = static_cast<QUniUIKitTableView *>(QUniUIKitBasePrivate::getAssociatedObject(tableView));
    if (!qtableView)
        return [self emptyCell];

    QJSValue jsFunction = _dataSourcePrivate->m_cellForRowAtIndexPath;
    if (jsFunction.isUndefined())
        return [self emptyCell];

    if (!jsFunction.isCallable()) {
        qWarning("TableViewDataSource: property 'cellForRowAtIndexPath' doesn't point to a JS function");
        return [self emptyCell];
    }

    QUniUIKitIndexPath qindexPath(indexPath);
    QJSValue jsTableView = qmlEngine(qtableView)->newQObject(qtableView);
    QJSValue jsIndexPath = qmlEngine(qtableView)->newQObject(&qindexPath);
    QJSValue returnValue = jsFunction.call(QJSValueList() << jsTableView << jsIndexPath);
    QUniUIKitTableViewCell *qcell = dynamic_cast<QUniUIKitTableViewCell *>(returnValue.toQObject());
    if (!qcell) {
        qWarning("TableViewDataSource: property 'cellForRowAtIndexPath' doesn't return a TableViewCell");
        return [self emptyCell];
    }

    return qcell->uiTableViewCellHandle();
}

- (NSArray<NSString *> *)sectionIndexTitlesForTableView:(UITableView *)tableView
{
    QUniUIKitTableView *qtableView = static_cast<QUniUIKitTableView *>(QUniUIKitBasePrivate::getAssociatedObject(tableView));
    if (!qtableView)
        return [NSArray array];

    QJSValue jsFunction = _dataSourcePrivate->m_sectionIndexTitlesForTableView;
    if (jsFunction.isUndefined())
        return [NSArray array];

    if (!jsFunction.isCallable()) {
        qWarning("TableViewDataSource: property 'sectionIndexTitlesForTableView' doesn't point to a JS function");
        return [NSArray array];
    }

    QJSValue jsTableView = qmlEngine(qtableView)->newQObject(qtableView);
    QJSValue returnValue = jsFunction.call(QJSValueList() << jsTableView);
    QVariantList list = returnValue.toVariant().toList();

    NSMutableArray *titleArray = [NSMutableArray arrayWithCapacity:list.length()];
    for (QVariant title : list)
       [titleArray addObject:title.toString().toNSString()];

    return titleArray;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    QUniUIKitTableView *qtableView = static_cast<QUniUIKitTableView *>(QUniUIKitBasePrivate::getAssociatedObject(tableView));
    if (!qtableView)
        return nil;

    QJSValue jsFunction = _dataSourcePrivate->m_titleForHeaderInSection;
    if (jsFunction.isUndefined())
        return nil;

    if (!jsFunction.isCallable()) {
        qWarning("TableViewDataSource: property 'titleForHeaderInSection' doesn't point to a JS function");
        return nil;
    }

    QJSValue jsTableView = qmlEngine(qtableView)->newQObject(qtableView);
    QJSValue jsSection((int)section);
    QJSValue returnValue = jsFunction.call(QJSValueList() << jsTableView << jsSection);

    return returnValue.toString().toNSString();
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section
{
    QUniUIKitTableView *qtableView = static_cast<QUniUIKitTableView *>(QUniUIKitBasePrivate::getAssociatedObject(tableView));
    if (!qtableView)
        return nil;

    QJSValue jsFunction = _dataSourcePrivate->m_titleForFooterInSection;
    if (jsFunction.isUndefined())
        return nil;

    if (!jsFunction.isCallable()) {
        qWarning("TableViewDataSource: property 'titleForFooterInSection' doesn't point to a JS function");
        return nil;
    }

    QJSValue jsTableView = qmlEngine(qtableView)->newQObject(qtableView);
    QJSValue jsSection((int)section);
    QJSValue returnValue = jsFunction.call(QJSValueList() << jsTableView << jsSection);

    return returnValue.toString().toNSString();
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

QJSValue QUniUIKitTableViewDataSource::numberOfSectionsInTableView() const
{
    return d_func()->m_numberOfSectionsInTableView;
}

void QUniUIKitTableViewDataSource::setNumberOfSectionsInTableView(const QJSValue &value)
{
    d_func()->m_numberOfSectionsInTableView = value;
}

QJSValue QUniUIKitTableViewDataSource::numberOfRowsInSection() const
{
    return d_func()->m_numberOfRowsInSection;
}

void QUniUIKitTableViewDataSource::setNumberOfRowsInSection(const QJSValue &value)
{
    d_func()->m_numberOfRowsInSection = value;
}

QJSValue QUniUIKitTableViewDataSource::cellForRowAtIndexPath() const
{
    return d_func()->m_cellForRowAtIndexPath;
}

void QUniUIKitTableViewDataSource::setCellForRowAtIndexPath(const QJSValue &value)
{
    d_func()->m_cellForRowAtIndexPath = value;
}

QJSValue QUniUIKitTableViewDataSource::sectionIndexTitlesForTableView() const
{
    return d_func()->m_sectionIndexTitlesForTableView;
}

void QUniUIKitTableViewDataSource::setSectionIndexTitlesForTableView(const QJSValue &value)
{
    d_func()->m_sectionIndexTitlesForTableView = value;
}

QJSValue QUniUIKitTableViewDataSource::titleForHeaderInSection() const
{
    return d_func()->m_titleForHeaderInSection;
}

void QUniUIKitTableViewDataSource::setTitleForHeaderInSection(const QJSValue &value)
{
    d_func()->m_titleForHeaderInSection = value;
}

QJSValue QUniUIKitTableViewDataSource::titleForFooterInSection() const
{
    return d_func()->m_titleForFooterInSection;
}

void QUniUIKitTableViewDataSource::setTitleForFooterInSection(const QJSValue &value)
{
    d_func()->m_titleForFooterInSection = value;
}

#include "moc_quniuikittableviewdatasource.cpp"

QT_END_NAMESPACE
