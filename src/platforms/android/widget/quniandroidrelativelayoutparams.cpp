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

#include "quniandroidrelativelayoutparams_p.h"
#include "quniandroidmarginlayoutparams_p_p.h"
#include "quniandroidrelativelayout_p.h"
#include "quniandroidview_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidRelativeLayoutParamsPrivate : public QUniAndroidMarginLayoutParamsPrivate
{
public:
    QUniAndroidView *above = nullptr;
    QUniAndroidView *below = nullptr;
    QUniAndroidView *alignTop = nullptr;
    QUniAndroidView *alignLeft = nullptr;
    QUniAndroidView *alignRight = nullptr;
    QUniAndroidView *alignBottom = nullptr;
    QUniAndroidView *alignStart = nullptr;
    QUniAndroidView *alignEnd = nullptr;
    QUniAndroidView *alignBaseline = nullptr;
    QUniAndroidView *toLeftOf = nullptr;
    QUniAndroidView *toRightOf = nullptr;
    QUniAndroidView *toStartOf = nullptr;
    QUniAndroidView *toEndOf = nullptr;

    bool alignParentTop = false;
    bool alignParentLeft = false;
    bool alignParentRight = false;
    bool alignParentBottom = false;
    bool alignParentStart = false;
    bool alignParentEnd = false;
    bool alignWithParent = false;
    bool centerHorizontal = false;
    bool centerVertical = false;
    bool centerInParent = false;
};

QUniAndroidRelativeLayoutParams::QUniAndroidRelativeLayoutParams(QUniAndroidView *view)
    : QUniAndroidMarginLayoutParams(*(new QUniAndroidRelativeLayoutParamsPrivate), view)
{
}

QUniAndroidView *QUniAndroidRelativeLayoutParams::above() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->above;
}

void QUniAndroidRelativeLayoutParams::setAbove(QUniAndroidView *view)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (view == d->above)
        return;

    d->above = view;
    invalidate();
    emit aboveChanged();
}

QUniAndroidView *QUniAndroidRelativeLayoutParams::below() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->below;
}

void QUniAndroidRelativeLayoutParams::setBelow(QUniAndroidView *view)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (view == d->below)
        return;

    d->below = view;
    invalidate();
    emit belowChanged();
}

QUniAndroidView *QUniAndroidRelativeLayoutParams::alignTop() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->alignTop;
}

void QUniAndroidRelativeLayoutParams::setAlignTop(QUniAndroidView *view)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (view == d->alignTop)
        return;

    d->alignTop = view;
    invalidate();
    emit alignTopChanged();
}

QUniAndroidView *QUniAndroidRelativeLayoutParams::alignLeft() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->alignLeft;
}

void QUniAndroidRelativeLayoutParams::setAlignLeft(QUniAndroidView *view)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (view == d->alignLeft)
        return;

    d->alignLeft = view;
    invalidate();
    emit alignLeftChanged();
}

QUniAndroidView *QUniAndroidRelativeLayoutParams::alignRight() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->alignRight;
}

void QUniAndroidRelativeLayoutParams::setAlignRight(QUniAndroidView *view)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (view == d->alignRight)
        return;

    d->alignRight = view;
    invalidate();
    emit alignRightChanged();
}

QUniAndroidView *QUniAndroidRelativeLayoutParams::alignBottom() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->alignBottom;
}

void QUniAndroidRelativeLayoutParams::setAlignBottom(QUniAndroidView *view)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (view == d->alignBottom)
        return;

    d->alignBottom = view;
    invalidate();
    emit alignBottomChanged();
}

QUniAndroidView *QUniAndroidRelativeLayoutParams::alignStart() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->alignStart;
}

void QUniAndroidRelativeLayoutParams::setAlignStart(QUniAndroidView *view)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (view == d->alignStart)
        return;

    d->alignStart = view;
    invalidate();
    emit alignStartChanged();
}

QUniAndroidView *QUniAndroidRelativeLayoutParams::alignEnd() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->alignEnd;
}

void QUniAndroidRelativeLayoutParams::setAlignEnd(QUniAndroidView *view)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (view == d->alignEnd)
        return;

    d->alignEnd = view;
    invalidate();
    emit alignEndChanged();
}

QUniAndroidView *QUniAndroidRelativeLayoutParams::alignBaseline() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->alignBaseline;
}

void QUniAndroidRelativeLayoutParams::setAlignBaseline(QUniAndroidView *view)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (view == d->alignBaseline)
        return;

    d->alignBaseline = view;
    invalidate();
    emit alignBaselineChanged();
}

QUniAndroidView *QUniAndroidRelativeLayoutParams::toLeftOf() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->toLeftOf;
}

void QUniAndroidRelativeLayoutParams::setToLeftOf(QUniAndroidView *view)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (view == d->toLeftOf)
        return;

    d->toLeftOf = view;
    invalidate();
    emit toLeftOfChanged();
}

QUniAndroidView *QUniAndroidRelativeLayoutParams::toRightOf() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->toRightOf;
}

void QUniAndroidRelativeLayoutParams::setToRightOf(QUniAndroidView *view)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (view == d->toRightOf)
        return;

    d->toRightOf = view;
    invalidate();
    emit toRightOfChanged();
}

QUniAndroidView *QUniAndroidRelativeLayoutParams::toStartOf() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->toStartOf;
}

void QUniAndroidRelativeLayoutParams::setToStartOf(QUniAndroidView *view)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (view == d->toStartOf)
        return;

    d->toStartOf = view;
    invalidate();
    emit toStartOfChanged();
}

QUniAndroidView *QUniAndroidRelativeLayoutParams::toEndOf() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->toEndOf;
}

void QUniAndroidRelativeLayoutParams::setToEndOf(QUniAndroidView *view)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (view == d->toEndOf)
        return;

    d->toEndOf = view;
    invalidate();
    emit toEndOfChanged();
}

bool QUniAndroidRelativeLayoutParams::alignParentTop() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->alignParentTop;
}

void QUniAndroidRelativeLayoutParams::setAlignParentTop(bool align)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (align == alignParentTop())
        return;

    d->alignParentTop = align;
    invalidate();
    emit alignParentTopChanged();
}

bool QUniAndroidRelativeLayoutParams::alignParentLeft() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->alignParentLeft;
}

void QUniAndroidRelativeLayoutParams::setAlignParentLeft(bool align)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (align == alignParentLeft())
        return;

    d->alignParentLeft = align;
    invalidate();
    emit alignParentLeftChanged();
}

bool QUniAndroidRelativeLayoutParams::alignParentRight() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->alignParentRight;
}

void QUniAndroidRelativeLayoutParams::setAlignParentRight(bool align)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (align == alignParentRight())
        return;

    d->alignParentRight = align;
    invalidate();
    emit alignParentRightChanged();
}

bool QUniAndroidRelativeLayoutParams::alignParentBottom() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->alignParentBottom;
}

void QUniAndroidRelativeLayoutParams::setAlignParentBottom(bool align)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (align == alignParentBottom())
        return;

    d->alignParentBottom = align;
    invalidate();
    emit alignParentBottomChanged();
}

bool QUniAndroidRelativeLayoutParams::alignParentStart() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->alignParentStart;
}

void QUniAndroidRelativeLayoutParams::setAlignParentStart(bool align)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (align == alignParentStart())
        return;

    d->alignParentStart = align;
    invalidate();
    emit alignParentStartChanged();
}

bool QUniAndroidRelativeLayoutParams::alignParentEnd() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->alignParentEnd;
}

void QUniAndroidRelativeLayoutParams::setAlignParentEnd(bool align)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (align == alignParentEnd())
        return;

    d->alignParentEnd = align;
    invalidate();
    emit alignParentEndChanged();
}

bool QUniAndroidRelativeLayoutParams::alignWithParent() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->alignWithParent;
}

void QUniAndroidRelativeLayoutParams::setAlignWithParent(bool align)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (align == alignWithParent())
        return;

    d->alignWithParent = align;
    invalidate();
    emit alignWithParentChanged();
}

bool QUniAndroidRelativeLayoutParams::centerHorizontal() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->centerHorizontal;
}

void QUniAndroidRelativeLayoutParams::setCenterHorizontal(bool center)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (center == centerHorizontal())
        return;

    d->centerHorizontal = center;
    invalidate();
    emit centerHorizontalChanged();
}

bool QUniAndroidRelativeLayoutParams::centerVertical() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->centerVertical;
}

void QUniAndroidRelativeLayoutParams::setCenterVertical(bool center)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (center == centerVertical())
        return;

    d->centerVertical = center;
    invalidate();
    emit centerVerticalChanged();
}

bool QUniAndroidRelativeLayoutParams::centerInParent() const
{
    Q_D(const QUniAndroidRelativeLayoutParams);
    return d->centerInParent;
}

void QUniAndroidRelativeLayoutParams::setCenterInParent(bool center)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    if (center == centerInParent())
        return;

    d->centerInParent = center;
    invalidate();
    emit centerInParentChanged();
}

QAndroidJniObject QUniAndroidRelativeLayoutParams::onCreate()
{
    return QAndroidJniObject("android/widget/RelativeLayout$LayoutParams",
                             "(II)V",
                             WRAP_CONTENT, WRAP_CONTENT);
}

static void addRule(QAndroidJniObject& instance, QUniAndroidView *view, QUniAndroidRelativeLayout::Verb verb)
{
    if (view) {
        int anchor = view->instance().callMethod<jint>("getId");
        instance.callMethod<void>("addRule", "(II)V", verb, anchor);
    }
}

static void addRule(QAndroidJniObject &instance, bool value, QUniAndroidRelativeLayout::Verb verb)
{
    if (value)
        instance.callMethod<void>("addRule", "(I)V", verb);
}

void QUniAndroidRelativeLayoutParams::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidRelativeLayoutParams);
    QUniAndroidMarginLayoutParams::onInflate(instance);

    instance.setField<jboolean>("alignWithParent", d->alignWithParent);

    addRule(instance, d->above, QUniAndroidRelativeLayout::ABOVE);
    addRule(instance, d->below, QUniAndroidRelativeLayout::BELOW);
    addRule(instance, d->alignTop, QUniAndroidRelativeLayout::ALIGN_TOP);
    addRule(instance, d->alignLeft, QUniAndroidRelativeLayout::ALIGN_LEFT);
    addRule(instance, d->alignRight, QUniAndroidRelativeLayout::ALIGN_RIGHT);
    addRule(instance, d->alignBottom, QUniAndroidRelativeLayout::ALIGN_BOTTOM);
    addRule(instance, d->alignStart, QUniAndroidRelativeLayout::ALIGN_START);
    addRule(instance, d->alignEnd, QUniAndroidRelativeLayout::ALIGN_END);
    addRule(instance, d->alignBaseline, QUniAndroidRelativeLayout::ALIGN_BASELINE);
    addRule(instance, d->toLeftOf, QUniAndroidRelativeLayout::LEFT_OF);
    addRule(instance, d->toRightOf, QUniAndroidRelativeLayout::RIGHT_OF);
    addRule(instance, d->toStartOf, QUniAndroidRelativeLayout::START_OF);
    addRule(instance, d->toEndOf, QUniAndroidRelativeLayout::END_OF);

    addRule(instance, d->alignParentTop, QUniAndroidRelativeLayout::ALIGN_PARENT_TOP);
    addRule(instance, d->alignParentLeft, QUniAndroidRelativeLayout::ALIGN_PARENT_LEFT);
    addRule(instance, d->alignParentRight, QUniAndroidRelativeLayout::ALIGN_PARENT_RIGHT);
    addRule(instance, d->alignParentBottom, QUniAndroidRelativeLayout::ALIGN_PARENT_BOTTOM);
    addRule(instance, d->alignParentStart, QUniAndroidRelativeLayout::ALIGN_PARENT_START);
    addRule(instance, d->alignParentEnd, QUniAndroidRelativeLayout::ALIGN_PARENT_END);
    addRule(instance, d->centerHorizontal, QUniAndroidRelativeLayout::CENTER_HORIZONTAL);
    addRule(instance, d->centerVertical, QUniAndroidRelativeLayout::CENTER_VERTICAL);
    addRule(instance, d->centerInParent, QUniAndroidRelativeLayout::CENTER_IN_PARENT);
}

QT_END_NAMESPACE
