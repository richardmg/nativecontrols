/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
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

#ifndef QNATIVEANDROIDVIEW_P_H
#define QNATIVEANDROIDVIEW_P_H

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

#include <QtNativeAndroid/private/qnativeandroidcontextual_p.h>
#include <QtQml/qqml.h>

QT_BEGIN_NAMESPACE

class QNativeAndroidDrawable;
class QNativeAndroidAnimation;
class QNativeAndroidLayoutParams;
class QNativeAndroidViewPrivate;

class Q_NATIVEANDROID_EXPORT QNativeAndroidView : public QNativeAndroidContextual
{
    Q_OBJECT
    Q_PROPERTY(QNativeAndroidView *parent READ parentView WRITE setParentView NOTIFY parentChanged)
    Q_PRIVATE_PROPERTY(QNativeAndroidView::d_func(), QQmlListProperty<QNativeAndroidView> children READ children NOTIFY childrenChanged DESIGNABLE false)

    Q_PROPERTY(QNativeAndroidDrawable *background READ background WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(int backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(int backgroundResource READ backgroundResource WRITE setBackgroundResource NOTIFY backgroundResourceChanged)

    Q_PROPERTY(QNativeAndroidAnimation *animation READ animation WRITE setAnimation NOTIFY animationChanged)

    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool focus READ hasFocus NOTIFY focusChanged)

    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal z READ z WRITE setZ NOTIFY zChanged)

    Q_PROPERTY(int top READ top WRITE setTop NOTIFY topChanged)
    Q_PROPERTY(int left READ left WRITE setLeft NOTIFY leftChanged)
    Q_PROPERTY(int right READ right WRITE setRight NOTIFY rightChanged)
    Q_PROPERTY(int bottom READ bottom WRITE setBottom NOTIFY bottomChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)

    Q_PROPERTY(int padding READ padding WRITE setPadding NOTIFY paddingChanged)
    Q_PROPERTY(int paddingTop READ paddingTop WRITE setPaddingTop NOTIFY paddingTopChanged)
    Q_PROPERTY(int paddingLeft READ paddingLeft WRITE setPaddingLeft NOTIFY paddingLeftChanged)
    Q_PROPERTY(int paddingRight READ paddingRight WRITE setPaddingRight NOTIFY paddingRightChanged)
    Q_PROPERTY(int paddingBottom READ paddingBottom WRITE setPaddingBottom NOTIFY paddingBottomChanged)

    Q_PROPERTY(qreal alpha READ alpha WRITE setAlpha NOTIFY alphaChanged)

    Q_PROPERTY(qreal scaleX READ scaleX WRITE setScaleX NOTIFY scaleXChanged)
    Q_PROPERTY(qreal scaleY READ scaleY WRITE setScaleY NOTIFY scaleYChanged)
    Q_PROPERTY(qreal pivotX READ pivotX WRITE setPivotX NOTIFY pivotXChanged)
    Q_PROPERTY(qreal pivotY READ pivotY WRITE setPivotY NOTIFY pivotYChanged)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
    Q_PROPERTY(qreal rotationX READ rotationX WRITE setRotationX NOTIFY rotationXChanged)
    Q_PROPERTY(qreal rotationY READ rotationY WRITE setRotationY NOTIFY rotationYChanged)
    Q_PROPERTY(qreal translationX READ translationX WRITE setTranslationX NOTIFY translationXChanged)
    Q_PROPERTY(qreal translationY READ translationY WRITE setTranslationY NOTIFY translationYChanged)
    Q_PROPERTY(qreal translationZ READ translationZ WRITE setTranslationZ NOTIFY translationZChanged)

public:
    explicit QNativeAndroidView(QNativeAndroidContext *context = nullptr);
    ~QNativeAndroidView();

    int identifier() const;
    void setIdentifier(int id);

    QNativeAndroidView *parentView() const;
    void setParentView(QNativeAndroidView *parent);

    QList<QNativeAndroidView *> childViews() const;

    QNativeAndroidLayoutParams *layoutParams() const;
    void setLayoutParams(QNativeAndroidLayoutParams *params);

    QNativeAndroidDrawable *background() const;
    void setBackground(QNativeAndroidDrawable *background, int resource = 0);

    int backgroundColor() const;
    void setBackgroundColor(int color);

    int backgroundResource() const;
    void setBackgroundResource(int resource);

    QNativeAndroidAnimation *animation() const;
    void setAnimation(QNativeAndroidAnimation *animation);

    bool isVisible() const;
    void setVisible(bool visible);

    bool hasFocus() const;

    qreal x() const;
    void setX(qreal x);

    qreal y() const;
    void setY(qreal y);

    qreal z() const;
    void setZ(qreal z);

    int top() const;
    void setTop(int top);

    int left() const;
    void setLeft(int left);

    int right() const;
    void setRight(int right);

    int bottom() const;
    void setBottom(int bottom);

    int width() const;
    void setWidth(int width);

    int height() const;
    void setHeight(int height);

    int padding() const;
    void setPadding(int padding);

    int paddingTop() const;
    void setPaddingTop(int padding);

    int paddingLeft() const;
    void setPaddingLeft(int padding);

    int paddingRight() const;
    void setPaddingRight(int padding);

    int paddingBottom() const;
    void setPaddingBottom(int padding);

    qreal alpha() const;
    void setAlpha(qreal alpha);

    qreal scaleX() const;
    void setScaleX(qreal scaleX);

    qreal scaleY() const;
    void setScaleY(qreal scaleY);

    qreal pivotX() const;
    void setPivotX(qreal pivotX);

    qreal pivotY() const;
    void setPivotY(qreal pivotY);

    qreal rotation() const;
    void setRotation(qreal rotation);

    qreal rotationX() const;
    void setRotationX(qreal rotationY);

    qreal rotationY() const;
    void setRotationY(qreal rotationY);

    qreal translationX() const;
    void setTranslationX(qreal translationY);

    qreal translationY() const;
    void setTranslationY(qreal translationY);

    qreal translationZ() const;
    void setTranslationZ(qreal translationZ);

    qreal elevation() const;
    void setElevation(qreal elevation);

    void requestPolish();

    enum ViewChange {
        ViewParentChange,       // data.view
        ViewChildAddedChange,   // data.view
        ViewChildRemovedChange, // data.view
        ViewVisibilityChange,   // data.boolean
    };

    union ViewChangeData {
        ViewChangeData(QNativeAndroidView *v) : view(v) {}
        ViewChangeData(qreal n) : number(n) {}
        ViewChangeData(bool b) : boolean(b) {}

        QNativeAndroidView *view;
        qreal number;
        bool boolean;
    };

Q_SIGNALS:
    void parentChanged(QNativeAndroidView *parent);
    void backgroundChanged(QNativeAndroidDrawable *background);
    void backgroundColorChanged(int backgroundColor);
    void backgroundResourceChanged(int backgroundResource);
    void animationChanged(QNativeAndroidAnimation *animation);
    void childrenChanged(const QList<QNativeAndroidView *> &children);
    void visibleChanged(bool visible);
    void focusChanged(bool focus);
    void click();
    void xChanged(qreal x);
    void yChanged(qreal y);
    void zChanged(qreal z);
    void topChanged(int top);
    void leftChanged(int left);
    void rightChanged(int right);
    void bottomChanged(int bottom);
    void widthChanged(int width);
    void heightChanged(int height);
    void paddingChanged(int padding);
    void paddingTopChanged(int padding);
    void paddingLeftChanged(int padding);
    void paddingRightChanged(int padding);
    void paddingBottomChanged(int padding);
    void alphaChanged(qreal alpha);
    void scaleXChanged(qreal scaleX);
    void scaleYChanged(qreal scaleY);
    void pivotXChanged(qreal pivotX);
    void pivotYChanged(qreal pivotY);
    void rotationChanged(qreal rotation);
    void rotationXChanged(qreal rotationX);
    void rotationYChanged(qreal rotationY);
    void translationXChanged(qreal translationX);
    void translationYChanged(qreal translationY);
    void translationZChanged(qreal translationZ);
    void elevationChanged(qreal elevation);
    void longClick(); // TODO: accept

protected:
    QNativeAndroidView(QNativeAndroidViewPrivate &dd, QNativeAndroidContext *context = nullptr);

    virtual void polish();
    virtual void viewChange(ViewChange change, const ViewChangeData &data);

    void addChild(QNativeAndroidView *child);
    void removeChild(QNativeAndroidView *child);

    QAndroidJniObject onCreate() override;
    void onInflate(QAndroidJniObject &instance) override;

    bool event(QEvent *event) override;

    void objectChange(ObjectChange change) override;

private:
    Q_DISABLE_COPY(QNativeAndroidView)
    Q_DECLARE_PRIVATE(QNativeAndroidView)

    Q_PRIVATE_SLOT(d_func(), void _q_updateBackground())
    Q_PRIVATE_SLOT(d_func(), void _q_updateAnimation())
    Q_PRIVATE_SLOT(d_func(), bool _q_updateFocus(bool focus))
    Q_PRIVATE_SLOT(d_func(), void _q_updateLayoutParams())
    Q_PRIVATE_SLOT(d_func(), void _q_updateGeometry(int top, int left, int right, int bottom))
};

QT_END_NAMESPACE

#endif // QNATIVEANDROIDVIEW_P_H
