/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native Controls module of the Qt Toolkit.
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

#ifndef QUNITAB_H
#define QUNITAB_H

#include <QtUniControls/qunibase.h>
#include <QtUniControls/qunicontrolsglobal.h>

QT_BEGIN_NAMESPACE

class QUniTabsPageTabPrivate;

class Q_UNICONTROLS_EXPORT QUniTabsPageTab : public QUniBase
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

public:
    explicit QUniTabsPageTab(QUniBase *parent = nullptr);
    explicit QUniTabsPageTab(const QString &title, QUniBase *parent = nullptr);
    virtual ~QUniTabsPageTab();

    QString title() const;
    void setTitle(const QString &title);

Q_SIGNALS:
    void titleChanged(const QString &title);

protected:
    QUniTabsPageTab(QUniTabsPageTabPrivate &dd, QUniBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniTabsPageTab)
    Q_DISABLE_COPY(QUniTabsPageTab)
};

QT_END_NAMESPACE

#endif // QUNITAB_H
