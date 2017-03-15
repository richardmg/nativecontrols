/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt QML Android module of the Qt Toolkit.
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

#include "quniandroidcolor_p.h"
#include <QtGui/qcolor.h>

QT_BEGIN_NAMESPACE

int QUniAndroidColor::alpha(int color)
{
    return static_cast<uint>(color) >> 24;
}

int QUniAndroidColor::argb(int alpha, int red, int green, int blue)
{
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

int QUniAndroidColor::blue(int color)
{
    return color & 0xFF;
}

int QUniAndroidColor::green(int color)
{
    return (color >> 8) & 0xFF;
}

int QUniAndroidColor::red(int color)
{
    return (color >> 16) & 0xFF;
}

int QUniAndroidColor::rgb(int red, int green, int blue)
{
    return (0xFF << 24) | (red << 16) | (green << 8) | blue;
}

int QUniAndroidColor::name(const QString &name)
{
    return QColor(name).rgba();
}

QObject *QUniAndroidColor::provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return new QUniAndroidColor;
}

QT_END_NAMESPACE
