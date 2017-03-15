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

#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>

#include <QtNativeAndroid/private/quniandroidacceleratedecelerateinterpolator_p.h>
#include <QtNativeAndroid/private/quniandroidaccelerateinterpolator_p.h>
#include <QtNativeAndroid/private/quniandroidalphaanimation_p.h>
#include <QtNativeAndroid/private/quniandroidanimation_p.h>
#include <QtNativeAndroid/private/quniandroidanimationset_p.h>
#include <QtNativeAndroid/private/quniandroidanticipateinterpolator_p.h>
#include <QtNativeAndroid/private/quniandroidanticipateovershootinterpolator_p.h>
#include <QtNativeAndroid/private/quniandroidbounceinterpolator_p.h>
#include <QtNativeAndroid/private/quniandroidcycleinterpolator_p.h>
#include <QtNativeAndroid/private/quniandroiddecelerateinterpolator_p.h>
#include <QtNativeAndroid/private/quniandroidlinearinterpolator_p.h>
#include <QtNativeAndroid/private/quniandroidovershootinterpolator_p.h>
#include <QtNativeAndroid/private/quniandroidpathinterpolator_p.h>
#include <QtNativeAndroid/private/quniandroidrotateanimation_p.h>
#include <QtNativeAndroid/private/quniandroidscaleanimation_p.h>
#include <QtNativeAndroid/private/quniandroidtranslateanimation_p.h>

QT_BEGIN_NAMESPACE

class QtQmlAndroidAnimationPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")

public:
    void registerTypes(const char *uri) override;
};

void QtQmlAndroidAnimationPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<QNativeAndroidAccelerateDecelerateInterpolator>(uri, 0, 21, "AccelerateDecelerateInterpolator");
    qmlRegisterType<QNativeAndroidAccelerateInterpolator>(uri, 0, 21, "AccelerateInterpolator");
    qmlRegisterType<QNativeAndroidAlphaAnimation>(uri, 0, 21, "AlphaAnimation");
    qmlRegisterType<QNativeAndroidAnimation>(uri, 0, 21, "Animation");
    qmlRegisterType<QNativeAndroidAnimationSet>(uri, 0, 21, "AnimationSet");
    qmlRegisterType<QNativeAndroidAnticipateInterpolator>(uri, 0, 21, "AnticipateInterpolator");
    qmlRegisterType<QNativeAndroidAnticipateOvershootInterpolator>(uri, 0, 21, "AnticipateOvershootInterpolator");
    qmlRegisterType<QNativeAndroidBounceInterpolator>(uri, 0, 21, "BounceInterpolator");
    qmlRegisterType<QNativeAndroidCycleInterpolator>(uri, 0, 21, "CycleInterpolator");
    qmlRegisterType<QNativeAndroidDecelerateInterpolator>(uri, 0, 21, "DecelerateInterpolator");
    qmlRegisterUncreatableType<QNativeAndroidInterpolator>(uri, 0, 21, "Interpolator", QStringLiteral("Interpolator is abstract"));
    qmlRegisterType<QNativeAndroidLinearInterpolator>(uri, 0, 21, "LinearInterpolator");
    qmlRegisterType<QNativeAndroidOvershootInterpolator>(uri, 0, 21, "OvershootInterpolator");
    qmlRegisterType<QNativeAndroidPathInterpolator>(uri, 0, 21, "PathInterpolator");
    qmlRegisterType<QNativeAndroidRotateAnimation>(uri, 0, 21, "RotateAnimation");
    qmlRegisterType<QNativeAndroidScaleAnimation>(uri, 0, 21, "ScaleAnimation");
    qmlRegisterType<QNativeAndroidTranslateAnimation>(uri, 0, 21, "TranslateAnimation");
}

QT_END_NAMESPACE

#include "qtqmlandroidanimationplugin.moc"
