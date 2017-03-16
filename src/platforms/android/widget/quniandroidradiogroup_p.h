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

#ifndef QUNIANDROIDRADIOGROUP_P_H
#define QUNIANDROIDRADIOGROUP_P_H

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

#include <QtUniAndroid/private/quniandroidlinearlayout_p.h>

QT_BEGIN_NAMESPACE

class QUniAndroidRadioButton;
class QUniAndroidRadioGroupPrivate;

class Q_UNIANDROID_EXPORT QUniAndroidRadioGroup : public QUniAndroidLinearLayout
{
    Q_OBJECT
    Q_PROPERTY(QUniAndroidRadioButton *checkedButton READ checkedButton WRITE setCheckedButton NOTIFY checkedButtonChanged)

public:
    explicit QUniAndroidRadioGroup(QUniAndroidContext *context = nullptr);

    QUniAndroidRadioButton *checkedButton() const;
    void setCheckedButton(QUniAndroidRadioButton *button);

public Q_SLOTS:
    void clearCheck();

Q_SIGNALS:
    void checkedButtonChanged();

protected:
    QAndroidJniObject onCreate() override;
    void onInflate(QAndroidJniObject &instance) override;

private:
    Q_DISABLE_COPY(QUniAndroidRadioGroup)
    Q_DECLARE_PRIVATE(QUniAndroidRadioGroup)

    Q_PRIVATE_SLOT(d_func(), void _q_updateCheckedButtonId(int checkedId))
    Q_PRIVATE_SLOT(d_func(), bool _q_updateCheckedButton(QUniAndroidRadioButton *button))
};

QT_END_NAMESPACE

#endif // QUNIANDROIDRADIOGROUP_P_H
