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

#include "quniandroidview_p.h"
#include "quniandroidview_p_p.h"
#include "quniandroiddrawable_p.h"
#include "quniandroidcolordrawable_p.h"
#include "quniandroidlayoutparams_p.h"
#include "quniandroidanimation_p.h"
#include "qtnativeandroidfunctions_p.h"
#include <QtCore/qcoreapplication.h>
#include <QtCore/qcoreevent.h>
#include <QtCore/qhash.h>

QT_BEGIN_NAMESPACE

static void native_onClick(JNIEnv *env, jobject object, jlong instance)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidView *view = reinterpret_cast<QUniAndroidView *>(instance);
    if (view)
        QMetaObject::invokeMethod(view, "click", Qt::QueuedConnection);
}

static void native_onFocusChange(JNIEnv *env, jobject object, jlong instance, jboolean hasFocus)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidView *view = reinterpret_cast<QUniAndroidView *>(instance);
    if (view)
        QMetaObject::invokeMethod(view, "_q_updateFocus", Qt::QueuedConnection, Q_ARG(bool, hasFocus));
}

static void native_onLayoutChange(JNIEnv *env, jobject object, jlong instance, jint left, jint top, jint right, jint bottom)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidView *view = reinterpret_cast<QUniAndroidView *>(instance);
    if (view)
        QMetaObject::invokeMethod(view, "_q_updateGeometry", Qt::QueuedConnection, Q_ARG(int, top), Q_ARG(int, left), Q_ARG(int, right), Q_ARG(int, bottom));
}

static bool native_onLongClick(JNIEnv *env, jobject object, jlong instance)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidView *view = reinterpret_cast<QUniAndroidView *>(instance);
    if (view) {
        //qDebug() << "onLongClick:" << view;
        QMetaObject::invokeMethod(view, "longClick", Qt::QueuedConnection);
    }
    return true; // TODO: accept
}

static void registerNativeViewMethods(jobject listener)
{
    JNINativeMethod methods[] {{"onClick", "(J)V", reinterpret_cast<void *>(native_onClick)},
                               {"onFocusChange", "(JZ)V", reinterpret_cast<void *>(native_onFocusChange)},
                               {"onLayoutChange", "(JIIII)V", reinterpret_cast<void *>(native_onLayoutChange)}
                               /*{"onLongClick", "(J)V", reinterpret_cast<void *>(native_onLongClick)}*/};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(listener);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

void QUniAndroidViewPrivate::init()
{
    Q_Q(QUniAndroidView);
    static int nextId = 0;
    id = ++nextId;

    if (context)
        q->setContext(context);

    // TODO: find a better place for this (upon construction of the native control perhaps?)
    q->requestPolish();
}

QQmlListProperty<QUniAndroidView> QUniAndroidViewPrivate::children()
{
    Q_Q(QUniAndroidView);
    return QQmlListProperty<QUniAndroidView>(q, this,
                                                &QUniAndroidViewPrivate::children_append,
                                                &QUniAndroidViewPrivate::children_count,
                                                &QUniAndroidViewPrivate::children_at,
                                                &QUniAndroidViewPrivate::children_clear);
}

void QUniAndroidViewPrivate::children_append(QQmlListProperty<QUniAndroidView> *list, QUniAndroidView *child)
{
    if (QUniAndroidView *view = qobject_cast<QUniAndroidView *>(list->object))
        view->addChild(child);
}

int QUniAndroidViewPrivate::children_count(QQmlListProperty<QUniAndroidView> *list)
{
    if (QUniAndroidViewPrivate *d = static_cast<QUniAndroidViewPrivate *>(list->data))
        return d->childViews.count();
    return 0;
}

QUniAndroidView *QUniAndroidViewPrivate::children_at(QQmlListProperty<QUniAndroidView> *list, int index)
{
    if (QUniAndroidViewPrivate *d = static_cast<QUniAndroidViewPrivate *>(list->data))
        return d->childViews.at(index);
    return nullptr;
}

void QUniAndroidViewPrivate::children_clear(QQmlListProperty<QUniAndroidView> *list)
{
    if (QUniAndroidViewPrivate *d = static_cast<QUniAndroidViewPrivate *>(list->data)) {
        while (!d->childViews.isEmpty())
            d->childViews.first()->setParentView(0);
    }
}

void QUniAndroidViewPrivate::_q_updateBackground()
{
    Q_Q(QUniAndroidView);
    if (!q->isValid() || !background)
        return;

    QAndroidJniObject view = q->instance();
    QAndroidJniObject bg = background->instance();
    QtUniAndroid::callFunction([=]() {
        view.callMethod<void>("setBackground", "(Landroid/graphics/drawable/Drawable;)V", bg.object());
    });
}

void QUniAndroidViewPrivate::_q_updateAnimation()
{
    Q_Q(QUniAndroidView);
    if (!q->isValid() || !animation || !animation->isValid())
        return;

    QAndroidJniObject view = q->instance();
    QAndroidJniObject anim = animation->instance();
    QtUniAndroid::callFunction([=]() {
        view.callMethod<void>("startAnimation", "(Landroid/view/animation/Animation;)V", anim.object());
    });
}

bool QUniAndroidViewPrivate::_q_updateFocus(bool arg)
{
    Q_Q(QUniAndroidView);
    if (arg == q->hasFocus())
        return false;

    focus = arg;
    emit q->focusChanged(arg);
    return true;
}

void QUniAndroidViewPrivate::_q_updateLayoutParams()
{
    Q_Q(QUniAndroidView);
    if (!q->isValid() || !layoutParams)
        return;

    QAndroidJniObject view = q->instance();
    QAndroidJniObject params = layoutParams->instance();
    QtUniAndroid::callFunction([=]() {
        view.callMethod<void>("setLayoutParams",
                              "(Landroid/view/ViewGroup$LayoutParams;)V",
                              params.object());
    });
}

void QUniAndroidViewPrivate::_q_updateGeometry(int t, int l, int r, int b)
{
    Q_Q(QUniAndroidView);
    if (t != q->top()) {
        top = t;
        emit q->topChanged(t);
        emit q->yChanged(q->y());
    }
    if (l != q->left()) {
        left = l;
        emit q->leftChanged(l);
        emit q->xChanged(q->x());
    }
    if (r != q->right()) {
        right = r;
        emit q->rightChanged(r);
        emit q->widthChanged(q->width());
    }
    if (b != q->bottom()) {
        bottom = b;
        emit q->bottomChanged(b);
        emit q->heightChanged(q->height());
    }
}

QUniAndroidView::QUniAndroidView(QUniAndroidContext *context)
    : QUniAndroidContextual(*(new QUniAndroidViewPrivate), context)
{
    Q_D(QUniAndroidView);
    d->init();
}

QUniAndroidView::QUniAndroidView(QUniAndroidViewPrivate &dd, QUniAndroidContext *context)
    : QUniAndroidContextual(dd, context)
{
    Q_D(QUniAndroidView);
    d->init();
}

QUniAndroidView::~QUniAndroidView()
{
    Q_D(QUniAndroidView);
    foreach (QUniAndroidView *child, d->childViews)
        child->setParentView(0);
    if (d->parent)
        setParentView(0);
}

int QUniAndroidView::identifier() const
{
    Q_D(const QUniAndroidView);
    return d->id;
}

void QUniAndroidView::setIdentifier(int identifier)
{
    Q_D(QUniAndroidView);
    d->id = identifier;
}

QUniAndroidView *QUniAndroidView::parentView() const
{
    Q_D(const QUniAndroidView);
    return d->parent;
}

void QUniAndroidView::setParentView(QUniAndroidView *parent)
{
    Q_D(QUniAndroidView);
    if (d->parent == parent)
        return;

    if (d->parent)
        d->parent->removeChild(this);
    d->parent = parent;
    viewChange(ViewParentChange, parent);
    if (parent)
        parent->addChild(this);
    emit parentChanged(parent);
}

QList<QUniAndroidView *> QUniAndroidView::childViews() const
{
    Q_D(const QUniAndroidView);
    return d->childViews;
}

QUniAndroidLayoutParams *QUniAndroidView::layoutParams() const
{
    Q_D(const QUniAndroidView);
    return d->layoutParams;
}

void QUniAndroidView::setLayoutParams(QUniAndroidLayoutParams *params)
{
    Q_D(QUniAndroidView);
    if (d->layoutParams == params)
        return;

    if (d->layoutParams) {
        QObjectPrivate::disconnect(d->layoutParams, &QUniAndroidObject::instanceChanged, d, &QUniAndroidViewPrivate::_q_updateLayoutParams);
        d->layoutParams->destruct();
    }
    d->layoutParams = params;
    if (d->layoutParams) {
        QObjectPrivate::connect(d->layoutParams, &QUniAndroidObject::instanceChanged, d, &QUniAndroidViewPrivate::_q_updateLayoutParams);
        if (isValid())
            d->layoutParams->construct();
    }
}

QUniAndroidDrawable *QUniAndroidView::background() const
{
    Q_D(const QUniAndroidView);
    return d->background;
}

void QUniAndroidView::setBackground(QUniAndroidDrawable *background, int resource)
{
    Q_D(QUniAndroidView);
    if (d->background == background)
        return;

    if (d->background) {
        QObjectPrivate::disconnect(d->background, &QUniAndroidObject::instanceChanged, d, &QUniAndroidViewPrivate::_q_updateBackground);
        d->background->destruct();
    }
    d->background = background;
    d->backgroundResource = resource;
    if (d->background) {
        QObjectPrivate::connect(d->background, &QUniAndroidObject::instanceChanged, d, &QUniAndroidViewPrivate::_q_updateBackground);
        if (!resource)
            d->background->construct();
    }
    emit backgroundChanged(background);
}

QUniAndroidAnimation *QUniAndroidView::animation() const
{
    Q_D(const QUniAndroidView);
    return d->animation;
}

void QUniAndroidView::setAnimation(QUniAndroidAnimation *animation)
{
    Q_D(QUniAndroidView);
    if (d->animation == animation)
        return;

    if (d->animation) {
        QObjectPrivate::disconnect(d->animation, &QUniAndroidObject::instanceChanged, d, &QUniAndroidViewPrivate::_q_updateAnimation);
        d->animation->destruct();
    }
    d->animation = animation;
    if (d->animation) {
        QObjectPrivate::connect(d->animation, &QUniAndroidObject::instanceChanged, d, &QUniAndroidViewPrivate::_q_updateAnimation);
        if (isValid())
            d->animation->construct();
    }
    emit animationChanged(animation);
}

int QUniAndroidView::backgroundColor() const
{
    Q_D(const QUniAndroidView);
    QUniAndroidColorDrawable *drawable = qobject_cast<QUniAndroidColorDrawable *>(d->background);
    if (drawable)
        return drawable->color();
    return 0; // TODO
}

void QUniAndroidView::setBackgroundColor(int color)
{
    setBackground(new QUniAndroidColorDrawable(color, this));
}

int QUniAndroidView::backgroundResource() const
{
    Q_D(const QUniAndroidView);
    return d->backgroundResource;
}

void QUniAndroidView::setBackgroundResource(int resource)
{
    Q_D(QUniAndroidView);
    if (d->backgroundResource == resource)
        return;

    setBackground(new QUniAndroidDrawable(this), resource);
    emit backgroundResourceChanged(resource);
}

bool QUniAndroidView::isVisible() const
{
    Q_D(const QUniAndroidView);
    return d->visible;
}

void QUniAndroidView::setVisible(bool visible)
{
    Q_D(QUniAndroidView);
    if (d->visible == visible)
        return;

    d->visible = visible;
    // TODO: VISIBLE(0), INVISIBLE(4), GONE(8)
    QtUniAndroid::callIntMethod(instance(), "setVisibility", visible ? 0 : 4);
    emit visibleChanged(visible);
}

bool QUniAndroidView::hasFocus() const
{
    Q_D(const QUniAndroidView);
    if (d->focus.isNull())
        return false;
    return d->focus;
}

qreal QUniAndroidView::x() const
{
    return left() + translationX();
}

void QUniAndroidView::setX(qreal x)
{
    setTranslationX(x - left());
}

qreal QUniAndroidView::y() const
{
    return top() + translationY();
}

void QUniAndroidView::setY(qreal y)
{
    setTranslationY(y - top());
}

qreal QUniAndroidView::z() const
{
    return elevation() + translationZ();
}

void QUniAndroidView::setZ(qreal z)
{
    setTranslationZ(z - elevation());
}

int QUniAndroidView::top() const
{
    Q_D(const QUniAndroidView);
    if (d->top.isNull())
        return 0;
    return d->top;
}

void QUniAndroidView::setTop(int top)
{
    Q_D(QUniAndroidView);
    if (!d->top.isNull() && d->top == top)
        return;

    d->top = top;
    QtUniAndroid::callIntMethod(instance(), "setTop", top);
    emit topChanged(top);
    emit yChanged(y());
}

int QUniAndroidView::left() const
{
    Q_D(const QUniAndroidView);
    if (d->left.isNull())
        return 0;
    return d->left;
}

void QUniAndroidView::setLeft(int left)
{
    Q_D(QUniAndroidView);
    if (!d->left.isNull() && d->left == left)
        return;

    d->left = left;
    QtUniAndroid::callIntMethod(instance(), "setLeft", left);
    emit leftChanged(left);
    emit xChanged(x());
}

int QUniAndroidView::right() const
{
    Q_D(const QUniAndroidView);
    if (d->right.isNull())
        return 0;
    return d->right;
}

void QUniAndroidView::setRight(int right)
{
    Q_D(QUniAndroidView);
    if (!d->right.isNull() && d->right == right)
        return;

    d->right = right;
    QtUniAndroid::callIntMethod(instance(), "setRight", right);
    emit rightChanged(right);
    emit widthChanged(width());
}

int QUniAndroidView::bottom() const
{
    Q_D(const QUniAndroidView);
    if (d->bottom.isNull())
        return 0;
    return d->bottom;
}

void QUniAndroidView::setBottom(int bottom)
{
    Q_D(QUniAndroidView);
    if (!d->bottom.isNull() && d->bottom == bottom)
        return;

    d->bottom = bottom;
    QtUniAndroid::callIntMethod(instance(), "setBottom", bottom);
    emit bottomChanged(bottom);
    emit heightChanged(height());
}

int QUniAndroidView::width() const
{
    return right() - left();
}

void QUniAndroidView::setWidth(int width)
{
    setRight(left() + width);
}

int QUniAndroidView::height() const
{
    return bottom() - top();
}

void QUniAndroidView::setHeight(int height)
{
    setBottom(top() + height);
}

int QUniAndroidView::padding() const
{
    Q_D(const QUniAndroidView);
    if (!d->padding.isNull())
        return d->padding;
    return 0;
}

void QUniAndroidView::setPadding(int padding)
{
    Q_D(QUniAndroidView);
    if (!d->padding.isNull() && d->padding == padding)
        return;

    d->padding = padding;
    emit paddingChanged(padding);
}

int QUniAndroidView::paddingTop() const
{
    Q_D(const QUniAndroidView);
    if (d->paddingTop.isNull())
        return padding();
    return d->paddingTop;
}

void QUniAndroidView::setPaddingTop(int padding)
{
    Q_D(QUniAndroidView);
    if (!d->paddingTop.isNull() && d->paddingTop == padding)
        return;

    d->paddingTop = padding;
    emit paddingTopChanged(padding);
}

int QUniAndroidView::paddingLeft() const
{
    Q_D(const QUniAndroidView);
    if (d->paddingLeft.isNull())
        return padding();
    return d->paddingLeft;
}

void QUniAndroidView::setPaddingLeft(int padding)
{
    Q_D(QUniAndroidView);
    if (!d->paddingLeft.isNull() && d->paddingLeft == padding)
        return;

    d->paddingLeft = padding;
    emit paddingLeftChanged(padding);
}

int QUniAndroidView::paddingRight() const
{
    Q_D(const QUniAndroidView);
    if (d->paddingRight.isNull())
        return padding();
    return d->paddingRight;
}

void QUniAndroidView::setPaddingRight(int padding)
{
    Q_D(QUniAndroidView);
    if (!d->paddingRight.isNull() && d->paddingRight == padding)
        return;

    d->paddingRight = padding;
    emit paddingRightChanged(padding);
}

int QUniAndroidView::paddingBottom() const
{
    Q_D(const QUniAndroidView);
    if (d->paddingBottom.isNull())
        return padding();
    return d->paddingBottom;
}

void QUniAndroidView::setPaddingBottom(int padding)
{
    Q_D(QUniAndroidView);
    if (!d->paddingBottom.isNull() && d->paddingBottom == padding)
        return;

    d->paddingBottom = padding;
    emit paddingBottomChanged(padding);
}

qreal QUniAndroidView::alpha() const
{
    Q_D(const QUniAndroidView);
    if (!d->alpha.isNull())
        return d->alpha;
    return 0;
}

void QUniAndroidView::setAlpha(qreal alpha)
{
    Q_D(QUniAndroidView);
    if (!d->alpha.isNull() && qFuzzyCompare(d->alpha, alpha))
        return;

    d->alpha = alpha;
    QtUniAndroid::callRealMethod(instance(), "setAlpha", alpha);
    emit alphaChanged(alpha);
}

qreal QUniAndroidView::scaleX() const
{
    Q_D(const QUniAndroidView);
    if (!d->scaleX.isNull())
        return d->scaleX;
    return 0;
}

void QUniAndroidView::setScaleX(qreal scaleX)
{
    Q_D(QUniAndroidView);
    if (!d->scaleX.isNull() && qFuzzyCompare(d->scaleX, scaleX))
        return;

    d->scaleX = scaleX;
    QtUniAndroid::callRealMethod(instance(), "setScaleX", scaleX);
    emit scaleXChanged(scaleX);
}

qreal QUniAndroidView::scaleY() const
{
    Q_D(const QUniAndroidView);
    if (!d->scaleY.isNull())
        return d->scaleY;
    return 0;
}

void QUniAndroidView::setScaleY(qreal scaleY)
{
    Q_D(QUniAndroidView);
    if (!d->scaleY.isNull() && qFuzzyCompare(d->scaleY, scaleY))
        return;

    d->scaleY = scaleY;
    QtUniAndroid::callRealMethod(instance(), "setScaleY", scaleY);
    emit scaleYChanged(scaleY);
}

qreal QUniAndroidView::pivotX() const
{
    Q_D(const QUniAndroidView);
    if (!d->pivotX.isNull())
        return d->pivotX;
    return 0;
}

void QUniAndroidView::setPivotX(qreal pivotX)
{
    Q_D(QUniAndroidView);
    if (!d->pivotX.isNull() && qFuzzyCompare(d->pivotX, pivotX))
        return;

    d->pivotX = pivotX;
    QtUniAndroid::callRealMethod(instance(), "setPivotX", pivotX);
    emit pivotXChanged(pivotX);
}

qreal QUniAndroidView::pivotY() const
{
    Q_D(const QUniAndroidView);
    if (!d->pivotY.isNull())
        return d->pivotY;
    return 0;
}

void QUniAndroidView::setPivotY(qreal pivotY)
{
    Q_D(QUniAndroidView);
    if (!d->pivotY.isNull() && qFuzzyCompare(d->pivotY, pivotY))
        return;

    d->pivotY = pivotY;
    QtUniAndroid::callRealMethod(instance(), "setPivotY", pivotY);
    emit pivotYChanged(pivotY);
}

qreal QUniAndroidView::rotation() const
{
    Q_D(const QUniAndroidView);
    if (!d->rotation.isNull())
        return d->rotation;
    return 0;
}

void QUniAndroidView::setRotation(qreal rotation)
{
    Q_D(QUniAndroidView);
    if (!d->rotation.isNull() && qFuzzyCompare(d->rotation, rotation))
        return;

    d->rotation = rotation;
    QtUniAndroid::callRealMethod(instance(), "setRotation", rotation);
    emit rotationChanged(rotation);
}

qreal QUniAndroidView::rotationX() const
{
    Q_D(const QUniAndroidView);
    if (!d->rotationX.isNull())
        return d->rotationX;
    return 0;
}

void QUniAndroidView::setRotationX(qreal rotationX)
{
    Q_D(QUniAndroidView);
    if (!d->rotationX.isNull() && qFuzzyCompare(d->rotationX, rotationX))
        return;

    d->rotationX = rotationX;
    QtUniAndroid::callRealMethod(instance(), "setRotationX", rotationX);
    emit rotationXChanged(rotationX);
}

qreal QUniAndroidView::rotationY() const
{
    Q_D(const QUniAndroidView);
    if (!d->rotationY.isNull())
        return d->rotationY;
    return 0;
}

void QUniAndroidView::setRotationY(qreal rotationY)
{
    Q_D(QUniAndroidView);
    if (!d->rotationY.isNull() && qFuzzyCompare(d->rotationY, rotationY))
        return;

    d->rotationY = rotationY;
    QtUniAndroid::callRealMethod(instance(), "setRotationY", rotationY);
    emit rotationYChanged(rotationY);
}

qreal QUniAndroidView::translationX() const
{
    Q_D(const QUniAndroidView);
    if (!d->translationX.isNull())
        return d->translationX;
    return 0;
}

void QUniAndroidView::setTranslationX(qreal translationX)
{
    Q_D(QUniAndroidView);
    if (!d->translationX.isNull() && qFuzzyCompare(d->translationX, translationX))
        return;

    d->translationX = translationX;
    QtUniAndroid::callRealMethod(instance(), "setTranslationX", translationX);
    emit translationXChanged(translationX);
    emit xChanged(x());
}

qreal QUniAndroidView::translationY() const
{
    Q_D(const QUniAndroidView);
    if (!d->translationY.isNull())
        return d->translationY;
    return 0;
}

void QUniAndroidView::setTranslationY(qreal translationY)
{
    Q_D(QUniAndroidView);
    if (!d->translationY.isNull() && qFuzzyCompare(d->translationY, translationY))
        return;

    d->translationY = translationY;
    QtUniAndroid::callRealMethod(instance(), "setTranslationY", translationY);
    emit translationYChanged(translationY);
    emit yChanged(y());
}

qreal QUniAndroidView::translationZ() const
{
    Q_D(const QUniAndroidView);
    if (!d->translationZ.isNull())
        return d->translationZ;
    return 0;
}

void QUniAndroidView::setTranslationZ(qreal translationZ)
{
    Q_D(QUniAndroidView);
    if (!d->translationZ.isNull() && qFuzzyCompare(d->translationZ, translationZ))
        return;

    d->translationZ = translationZ;
    QtUniAndroid::callRealMethod(instance(), "setTranslationZ", translationZ);
    emit translationZChanged(translationZ);
    emit zChanged(z());
}

qreal QUniAndroidView::elevation() const
{
    Q_D(const QUniAndroidView);
    if (!d->elevation.isNull())
        return d->elevation;
    return 0;
}

void QUniAndroidView::setElevation(qreal elevation)
{
    Q_D(QUniAndroidView);
    if (!d->elevation.isNull() && qFuzzyCompare(d->elevation, elevation))
        return;

    d->elevation = elevation;
    QtUniAndroid::callRealMethod(instance(), "setElevation", elevation);
    emit elevationChanged(elevation);
    emit zChanged(z());
}

void QUniAndroidView::viewChange(ViewChange change, const ViewChangeData &data)
{
    Q_UNUSED(data);
    switch (change) {
    case ViewParentChange:       // data.view
    case ViewChildAddedChange:   // data.view
    case ViewChildRemovedChange: // data.view
    case ViewVisibilityChange:   // data.boolean
    default:
        break;
    }
}

void QUniAndroidView::addChild(QUniAndroidView *child)
{
    Q_D(QUniAndroidView);
    if (d->childViews.contains(child))
        return;

    d->childViews.append(child);
    viewChange(ViewChildAddedChange, child);
    emit childrenChanged(d->childViews);
}

void QUniAndroidView::removeChild(QUniAndroidView *child)
{
    Q_D(QUniAndroidView);
    if (!d->childViews.removeOne(child))
        return;

    viewChange(ViewChildRemovedChange, child);
    emit childrenChanged(d->childViews);
}

QAndroidJniObject QUniAndroidView::onCreate()
{
    Q_ASSERT(!QtUniAndroid::isMainQtThread());

    return QAndroidJniObject("android/view/View",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QUniAndroidView::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidView);
    Q_ASSERT(!QtUniAndroid::isMainQtThread());

    QUniAndroidContextual::onInflate(instance);

    d->listener = QAndroidJniObject("org/qtproject/qt5/android/bindings/view/QtUniViewListener",
                                    "(Landroid/view/View;J)V",
                                    instance.object(),
                                    reinterpret_cast<jlong>(this));

    instance.callMethod<void>("setId", "(I)V", d->id);

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        registerNativeViewMethods(d->listener.object());
        nativeMethodsRegistered = true;
    }

    // TODO: VISIBLE(0), INVISIBLE(4), GONE(8)
    instance.callMethod<void>("setVisibility", "(I)V", d->visible ? 0 : 4);
    if (!d->padding.isNull() || !d->paddingTop.isNull() || !d->paddingLeft.isNull() || !d->paddingRight.isNull() || !d->paddingBottom.isNull())
        instance.callMethod<void>("setPadding", "(IIII)V", paddingLeft(), paddingTop(), paddingRight(), paddingBottom());
    if (!d->top.isNull())
        instance.callMethod<void>("setTop", "(I)V", d->top);
    if (!d->left.isNull())
        instance.callMethod<void>("setLeft", "(I)V", d->left);
    if (!d->right.isNull())
        instance.callMethod<void>("setRight", "(I)V", d->right);
    if (!d->bottom.isNull())
        instance.callMethod<void>("setBottom", "(I)V", d->bottom);
    if (!d->alpha.isNull())
        instance.callMethod<void>("setAlpha", "(F)V", d->alpha);
    if (!d->scaleX.isNull())
        instance.callMethod<void>("setScaleX", "(F)V", d->scaleX);
    if (!d->scaleY.isNull())
        instance.callMethod<void>("setScaleY", "(F)V", d->scaleY);
    if (!d->pivotX.isNull())
        instance.callMethod<void>("setPivotX", "(F)V", d->pivotX);
    if (!d->pivotY.isNull())
        instance.callMethod<void>("setPivotY", "(F)V", d->pivotY);
    if (!d->rotation.isNull())
        instance.callMethod<void>("setRotation", "(F)V", d->rotation);
    if (!d->rotationX.isNull())
        instance.callMethod<void>("setRotationX", "(F)V", d->rotationX);
    if (!d->rotationY.isNull())
        instance.callMethod<void>("setRotationY", "(F)V", d->rotationY);
    if (!d->translationX.isNull())
        instance.callMethod<void>("setTranslationX", "(F)V", d->translationX);
    if (!d->translationY.isNull())
        instance.callMethod<void>("setTranslationY", "(F)V", d->translationY);
    if (!d->translationZ.isNull())
        instance.callMethod<void>("setTranslationZ", "(F)V", d->translationZ);
    if (!d->elevation.isNull())
        instance.callMethod<void>("setElevation", "(F)V", d->elevation);

    if (d->backgroundResource != 0) {
        QAndroidJniObject background = ctx().callObjectMethod("getDrawable", "(I)Landroid/graphics/drawable/Drawable;", d->backgroundResource);
        d->background->inflate(background);
    }
}

void QUniAndroidView::requestPolish()
{
    Q_D(QUniAndroidView);
    if (!d->polishing) {
        d->polishing = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::PolishRequest));
    }
}

void QUniAndroidView::polish()
{
}

bool QUniAndroidView::event(QEvent *event)
{
    Q_D(QUniAndroidView);
    if (event->type() == QEvent::PolishRequest) {
        QUniAndroidView *view = qobject_cast<QUniAndroidView *>(parent());
        if (view)
            setParentView(view);
        polish();
        d->polishing = false;
    }
    return QUniAndroidContextual::event(event);
}

void QUniAndroidView::objectChange(ObjectChange change)
{
    Q_D(QUniAndroidView);
    QUniAndroidContextual::objectChange(change);
    if (change == InstanceChange) {
        d->_q_updateLayoutParams();
        d->_q_updateBackground();
        d->_q_updateAnimation();
    }
}

QT_END_NAMESPACE

#include "moc_quniandroidview_p.cpp"
