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

#ifndef QQMLANDROIDVIEW_P_H
#define QQMLANDROIDVIEW_P_H

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

#include <QtQmlAndroid/private/qqmlandroidcontextual_p.h>
#include <QtQmlAndroid/private/qqmlandroidoptional_p.h>
#include <QtQml/qqml.h>

QT_BEGIN_NAMESPACE

class QQmlAndroidDrawable;
class QQmlAndroidAnimation;
class QQmlAndroidLayoutParams;

class Q_QMLANDROID_EXPORT QQmlAndroidView : public QQmlAndroidContextual
{
    Q_OBJECT
    Q_PROPERTY(QQmlAndroidView *parent READ parentView WRITE setParentView NOTIFY parentChanged)
    Q_PROPERTY(QQmlListProperty<QQmlAndroidView> children READ children NOTIFY childrenChanged)

    Q_PROPERTY(QQmlAndroidDrawable *background READ background WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(int backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(int backgroundResource READ backgroundResource WRITE setBackgroundResource NOTIFY backgroundResourceChanged)

    Q_PROPERTY(QQmlAndroidAnimation *animation READ animation WRITE setAnimation NOTIFY animationChanged)

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
    explicit QQmlAndroidView(QQmlAndroidView *parent = 0);
    ~QQmlAndroidView();

    int identifier() const;
    void setIdentifier(int id);

    QQmlAndroidView *parentView() const;
    void setParentView(QQmlAndroidView *parent);

    QList<QQmlAndroidView *> childViews() const;
    QQmlListProperty<QQmlAndroidView> children();

    QQmlAndroidLayoutParams *layoutParams() const;
    void setLayoutParams(QQmlAndroidLayoutParams *params);

    QQmlAndroidDrawable *background() const;
    void setBackground(QQmlAndroidDrawable *background, int resource = 0);

    int backgroundColor() const;
    void setBackgroundColor(int color);

    int backgroundResource() const;
    void setBackgroundResource(int resource);

    QQmlAndroidAnimation *animation() const;
    void setAnimation(QQmlAndroidAnimation *animation);

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
        ViewChangeData(QQmlAndroidView *v) : view(v) {}
        ViewChangeData(qreal n) : number(n) {}
        ViewChangeData(bool b) : boolean(b) {}

        QQmlAndroidView *view;
        qreal number;
        bool boolean;
    };

Q_SIGNALS:
    void parentChanged();
    void backgroundChanged();
    void backgroundColorChanged();
    void backgroundResourceChanged();
    void animationChanged();
    void childrenChanged();
    void visibleChanged();
    void focusChanged();
    void click();
    void xChanged();
    void yChanged();
    void zChanged();
    void topChanged();
    void leftChanged();
    void rightChanged();
    void bottomChanged();
    void widthChanged();
    void heightChanged();
    void paddingChanged();
    void paddingTopChanged();
    void paddingLeftChanged();
    void paddingRightChanged();
    void paddingBottomChanged();
    void scaleXChanged();
    void scaleYChanged();
    void pivotXChanged();
    void pivotYChanged();
    void rotationChanged();
    void rotationXChanged();
    void rotationYChanged();
    void translationXChanged();
    void translationYChanged();
    void translationZChanged();
    void elevationChanged();
    void longClick(); // TODO: accept

protected:
    virtual void polish();
    virtual void viewChange(ViewChange change, const ViewChangeData &data);

    void addChild(QQmlAndroidView *child);
    void removeChild(QQmlAndroidView *child);

    static void children_append(QQmlListProperty<QQmlAndroidView> *list, QQmlAndroidView *child);
    static int children_count(QQmlListProperty<QQmlAndroidView> *list);
    static QQmlAndroidView *children_at(QQmlListProperty<QQmlAndroidView> *list, int index);
    static void children_clear(QQmlListProperty<QQmlAndroidView> *list);

    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;
    void onInflate(QAndroidJniObject &instance) Q_DECL_OVERRIDE;

    static void onRegisterNativeMethods(jobject listener);
    static void onClick(JNIEnv *env, jobject object, jlong instance);
    static void onFocusChange(JNIEnv *env, jobject object, jlong instance, jboolean hasFocus);
    static void onLayoutChange(JNIEnv *env, jobject object, jlong instance, jint left, jint top, jint right, jint bottom);
    static bool onLongClick(JNIEnv *env, jobject object, jlong instance);

    bool event(QEvent *event) Q_DECL_OVERRIDE;

    void objectChange(ObjectChange change) Q_DECL_OVERRIDE;

private Q_SLOTS:
    void updateBackground();
    void updateAnimation();
    bool updateFocus(bool focus);
    void updateLayoutParams();
    void updateGeometry(int top, int left, int right, int bottom);

private:
    int m_id;
    QQmlAndroidView *m_parent;
    QList<QQmlAndroidView *> m_children;
    QQmlAndroidDrawable *m_background;
    int m_backgroundResource;
    QQmlAndroidAnimation *m_animation;
    bool m_polishing;
    bool m_visible;

    QAndroidJniObject m_listener;

    QQmlAndroidLayoutParams *m_layoutParams;

    QQmlAndroidOptional<bool> m_focus;
    QQmlAndroidOptional<int> m_top;
    QQmlAndroidOptional<int> m_left;
    QQmlAndroidOptional<int> m_right;
    QQmlAndroidOptional<int> m_bottom;
    QQmlAndroidOptional<int> m_padding;
    QQmlAndroidOptional<int> m_paddingTop;
    QQmlAndroidOptional<int> m_paddingLeft;
    QQmlAndroidOptional<int> m_paddingRight;
    QQmlAndroidOptional<int> m_paddingBottom;
    QQmlAndroidOptional<qreal> m_scaleX;
    QQmlAndroidOptional<qreal> m_scaleY;
    QQmlAndroidOptional<qreal> m_pivotX;
    QQmlAndroidOptional<qreal> m_pivotY;
    QQmlAndroidOptional<qreal> m_rotation;
    QQmlAndroidOptional<qreal> m_rotationX;
    QQmlAndroidOptional<qreal> m_rotationY;
    QQmlAndroidOptional<qreal> m_translationX;
    QQmlAndroidOptional<qreal> m_translationY;
    QQmlAndroidOptional<qreal> m_translationZ;
    QQmlAndroidOptional<qreal> m_elevation;
};

QT_END_NAMESPACE

#endif // QQMLANDROIDVIEW_P_H
