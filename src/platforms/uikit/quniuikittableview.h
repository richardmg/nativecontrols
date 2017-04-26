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

#ifndef QUNIUIKITTABLEVIEW_H
#define QUNIUIKITTABLEVIEW_H

#include <QtUniUIKitControls/quniuikitcontrol.h>

QT_BEGIN_NAMESPACE

class QUniUIKitTableViewPrivate;
class QUniUIKitTableViewCell;
class QUniUIKitTableViewDataSource;
Q_FORWARD_DECLARE_OBJC_CLASS(UITableView);

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitTableView : public QUniUIKitControl
{
    Q_OBJECT
    Q_PROPERTY(QUniUIKitTableViewDataSource *dataSource READ dataSource WRITE setDataSource NOTIFY dataSourceChanged)

public:
    QUniUIKitTableView(QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitTableView();

    UITableView *uiTableViewHandle();

    Q_INVOKABLE QUniUIKitTableViewCell *dequeueReusableCellWithIdentifier(const QString &id);

    QUniUIKitTableViewDataSource *dataSource() const;
    void setDataSource(QUniUIKitTableViewDataSource *dataSource);

Q_SIGNALS:
    void dataSourceChanged(QUniUIKitTableViewDataSource *dataSource);

protected:
    QUniUIKitTableView(QUniUIKitTableViewPrivate &dd, QUniUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniUIKitTableView)
    Q_DISABLE_COPY(QUniUIKitTableView)
};

QT_END_NAMESPACE

#endif // QUNIUIKITTABLEVIEW_H
