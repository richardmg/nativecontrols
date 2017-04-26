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

#ifndef QUNIUIKITINDEXPATH_H
#define QUNIUIKITINDEXPATH_H

#include <QtCore>
#include <QtUniUIKitControls/quniuikitcontrolsglobal.h>

QT_BEGIN_NAMESPACE

class QUniUIKitIndexPathPrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(NSIndexPath);

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitIndexPath : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int section READ section)
    Q_PROPERTY(int row READ row)

public:
    QUniUIKitIndexPath(QObject *parent = nullptr);
    QUniUIKitIndexPath(int row, int section, QObject *parent = nullptr);
    QUniUIKitIndexPath(NSIndexPath *indexPath, QObject *parent = nullptr);

    Q_INVOKABLE static QUniUIKitIndexPath *create(int row, int section);

    NSIndexPath *nsIndexPathHandle();

    int row() const;
    int section() const;

private:
    Q_DECLARE_PRIVATE(QUniUIKitIndexPath)
    Q_DISABLE_COPY(QUniUIKitIndexPath)
};

QT_END_NAMESPACE

#endif // QUNIUIKITINDEXPATH_H
