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

#ifndef QUNIANDROIDLINEARLAYOUT_P_H
#define QUNIANDROIDLINEARLAYOUT_P_H

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

#include <QtUniAndroid/private/quniandroidviewgroup_p.h>
#include <QtUniAndroid/private/quniandroidlinearlayoutparams_p.h>

QT_BEGIN_NAMESPACE

class QUniAndroidLinearLayoutPrivate;

class Q_UNIANDROID_EXPORT QUniAndroidLinearLayout : public QUniAndroidViewGroup
{
    Q_OBJECT
    Q_PROPERTY(bool baselineAligned READ isBaselineAligned WRITE setBaselineAligned NOTIFY baselineAlignedChanged)
    Q_PROPERTY(int baselineAlignedChildIndex READ baselineAlignedChildIndex WRITE setBaselineAlignedChildIndex NOTIFY baselineAlignedChildIndexChanged)
    Q_PROPERTY(bool measureWithLargestChildEnabled READ isMeasureWithLargestChildEnabled WRITE setMeasureWithLargestChildEnabled NOTIFY measureWithLargestChildEnabledChanged)
    Q_PROPERTY(Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
    Q_PROPERTY(qreal weightSum READ weightSum WRITE setWeightSum NOTIFY weightSumChanged)
    Q_ENUMS(Orientation)

public:
    explicit QUniAndroidLinearLayout(QUniAndroidContext *context = nullptr);

    static QUniAndroidLinearLayoutParams *qmlAttachedProperties(QObject *object);

    enum Orientation {
        HORIZONTAL = 0,
        VERTICAL = 1
    };

    bool isBaselineAligned() const;
    void setBaselineAligned(bool aligned);

    int baselineAlignedChildIndex() const;
    void setBaselineAlignedChildIndex(int index);

    // TODO: Drawable divider
    // TODO: int gravity

    bool isMeasureWithLargestChildEnabled() const;
    void setMeasureWithLargestChildEnabled(bool enabled);

    Orientation orientation() const;
    void setOrientation(Orientation orientation);

    qreal weightSum() const;
    void setWeightSum(qreal sum);

Q_SIGNALS:
    void baselineAlignedChanged();
    void baselineAlignedChildIndexChanged();
    void measureWithLargestChildEnabledChanged();
    void orientationChanged();
    void weightSumChanged();

protected:
    QUniAndroidLinearLayout(QUniAndroidLinearLayoutPrivate &dd, QUniAndroidContext *context = nullptr);

    QAndroidJniObject onCreate() override;
    void onInflate(QAndroidJniObject &instance) override;

private:
    Q_DISABLE_COPY(QUniAndroidLinearLayout)
    Q_DECLARE_PRIVATE(QUniAndroidLinearLayout)
};

QT_END_NAMESPACE

QML_DECLARE_TYPEINFO(QUniAndroidLinearLayout, QML_HAS_ATTACHED_PROPERTIES)

#endif // QUNIANDROIDLINEARLAYOUT_P_H
