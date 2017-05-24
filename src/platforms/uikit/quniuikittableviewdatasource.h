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

#ifndef QUNIUIKITTABLEVIEWDATASOURCE_H
#define QUNIUIKITTABLEVIEWDATASOURCE_H

#include <QtQml/qjsvalue.h>
#include <QtUniUIKitControls/quniuikitbase.h>

QT_BEGIN_NAMESPACE

class QUniUIKitTableViewDataSourcePrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(NSObject);
Q_FORWARD_DECLARE_OBJC_CLASS(UITableViewDataSource);

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitTableViewDataSource : public QUniUIKitBase
{
    Q_OBJECT
    Q_PROPERTY(QJSValue numberOfSectionsInTableView READ numberOfSectionsInTableView WRITE setNumberOfSectionsInTableView NOTIFY numberOfSectionsInTableViewChanged)
    Q_PROPERTY(QJSValue numberOfRowsInSection READ numberOfRowsInSection WRITE setNumberOfRowsInSection NOTIFY numberOfRowsInSectionChanged)
    Q_PROPERTY(QJSValue cellForRowAtIndexPath READ cellForRowAtIndexPath WRITE setCellForRowAtIndexPath NOTIFY cellForRowAtIndexPathChanged)
    Q_PROPERTY(QJSValue sectionIndexTitlesForTableView READ sectionIndexTitlesForTableView WRITE setSectionIndexTitlesForTableView NOTIFY sectionIndexTitlesForTableViewChanged)
    Q_PROPERTY(QJSValue titleForHeaderInSection READ titleForHeaderInSection WRITE setTitleForHeaderInSection NOTIFY titleForHeaderInSectionChanged)
    Q_PROPERTY(QJSValue titleForFooterInSection READ titleForFooterInSection WRITE setTitleForFooterInSection NOTIFY titleForFooterInSectionChanged)

public:
    QUniUIKitTableViewDataSource(QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitTableViewDataSource();

    NSObject *uiTableViewDataSourceHandle();

    QJSValue numberOfSectionsInTableView() const;
    void setNumberOfSectionsInTableView(const QJSValue &value);

    QJSValue numberOfRowsInSection() const;
    void setNumberOfRowsInSection(const QJSValue &value);

    QJSValue cellForRowAtIndexPath() const;
    void setCellForRowAtIndexPath(const QJSValue &value);

    QJSValue sectionIndexTitlesForTableView() const;
    void setSectionIndexTitlesForTableView(const QJSValue &value);

    QJSValue titleForHeaderInSection() const;
    void setTitleForHeaderInSection(const QJSValue &value);

    QJSValue titleForFooterInSection() const;
    void setTitleForFooterInSection(const QJSValue &value);

Q_SIGNALS:
    void numberOfSectionsInTableViewChanged(QUniUIKitTableViewDataSource *dataSource);
    void numberOfRowsInSectionChanged(QUniUIKitTableViewDataSource *dataSource);
    void cellForRowAtIndexPathChanged(QUniUIKitTableViewDataSource *dataSource);
    void sectionIndexTitlesForTableViewChanged(QUniUIKitTableViewDataSource *dataSource);
    void titleForHeaderInSectionChanged(QUniUIKitTableViewDataSource *dataSource);
    void titleForFooterInSectionChanged(QUniUIKitTableViewDataSource *dataSource);

private:
    Q_DECLARE_PRIVATE(QUniUIKitTableViewDataSource)
    Q_DISABLE_COPY(QUniUIKitTableViewDataSource)
};

QT_END_NAMESPACE

#endif // QUNIUIKITTABLEVIEWDATASOURCE_H
