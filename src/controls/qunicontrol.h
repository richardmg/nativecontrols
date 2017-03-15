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

#ifndef QNATIVECONTROL_H
#define QNATIVECONTROL_H

#include <QtCore/qobject.h>
#include <QtGui/qwindow.h>

#include <QtQml/qqml.h>

#include <QtNativeControls/quniview.h>
#include <QtNativeControls/qunicontrolsglobal.h>

QT_BEGIN_NAMESPACE

class QUniPlatformControl;
class QUniControlPrivate;

class Q_NATIVECONTROLS_EXPORT QUniControl : public QUniView
{
    Q_OBJECT

public:
    explicit QUniControl(QUniBase *parentControl = nullptr);
    virtual ~QUniControl();

protected:
    QUniControl(QUniControlPrivate &dd, QUniBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniControl)
    Q_DISABLE_COPY(QUniControl)
};

QT_END_NAMESPACE

#endif // QNATIVECONTROL_H
