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

#ifndef QNATIVEANDROIDVIEW_P_P_H
#define QNATIVEANDROIDVIEW_P_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtUniAndroid/private/quniandroidcontextual_p_p.h>
#include <QtUniAndroid/private/quniandroidoptional_p.h>
#include <QtUniAndroid/private/quniandroidview_p.h>

QT_BEGIN_NAMESPACE

class QUniAndroidViewPrivate : public QUniAndroidContextualPrivate
{
    Q_DECLARE_PUBLIC(QUniAndroidView)

public:
    static QUniAndroidViewPrivate *get(QUniAndroidView *view)
    {
        return view->d_func();
    }

    void init();

    QQmlListProperty<QUniAndroidView> children();

    static void children_append(QQmlListProperty<QUniAndroidView> *list, QUniAndroidView *child);
    static int children_count(QQmlListProperty<QUniAndroidView> *list);
    static QUniAndroidView *children_at(QQmlListProperty<QUniAndroidView> *list, int index);
    static void children_clear(QQmlListProperty<QUniAndroidView> *list);

    void _q_updateBackground();
    void _q_updateAnimation();
    bool _q_updateFocus(bool focus);
    void _q_updateLayoutParams();
    void _q_updateGeometry(int top, int left, int right, int bottom);

    int id = 0;
    QUniAndroidView *parent = nullptr;
    QList<QUniAndroidView *> childViews;
    QUniAndroidDrawable *background = nullptr;
    int backgroundResource = 0;
    QUniAndroidAnimation *animation = nullptr;
    bool polishing = false;
    bool visible = true;

    QAndroidJniObject listener;

    QUniAndroidLayoutParams *layoutParams = nullptr;

    QUniAndroidOptional<bool> focus;
    QUniAndroidOptional<int> top;
    QUniAndroidOptional<int> left;
    QUniAndroidOptional<int> right;
    QUniAndroidOptional<int> bottom;
    QUniAndroidOptional<int> padding;
    QUniAndroidOptional<int> paddingTop;
    QUniAndroidOptional<int> paddingLeft;
    QUniAndroidOptional<int> paddingRight;
    QUniAndroidOptional<int> paddingBottom;
    QUniAndroidOptional<qreal> alpha;
    QUniAndroidOptional<qreal> scaleX;
    QUniAndroidOptional<qreal> scaleY;
    QUniAndroidOptional<qreal> pivotX;
    QUniAndroidOptional<qreal> pivotY;
    QUniAndroidOptional<qreal> rotation;
    QUniAndroidOptional<qreal> rotationX;
    QUniAndroidOptional<qreal> rotationY;
    QUniAndroidOptional<qreal> translationX;
    QUniAndroidOptional<qreal> translationY;
    QUniAndroidOptional<qreal> translationZ;
    QUniAndroidOptional<qreal> elevation;
};

QT_END_NAMESPACE

#endif // QNATIVEANDROIDVIEW_P_P_H
