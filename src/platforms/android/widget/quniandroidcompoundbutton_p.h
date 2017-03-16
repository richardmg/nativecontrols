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

#ifndef QUNIANDROIDCOMPOUNDBUTTON_P_H
#define QUNIANDROIDCOMPOUNDBUTTON_P_H

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

#include <QtUniAndroid/private/quniandroidbutton_p.h>

QT_BEGIN_NAMESPACE

class QUniAndroidCompoundButtonPrivate;

class Q_UNIANDROID_EXPORT QUniAndroidCompoundButton : public QUniAndroidButton
{
    Q_OBJECT
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked NOTIFY checkedChanged)

public:
    explicit QUniAndroidCompoundButton(QUniAndroidContext *context = nullptr);

    bool isChecked() const;
    void setChecked(bool checked);

public Q_SLOTS:
    void toggle();

Q_SIGNALS:
    void checkedChanged();

protected:
    QUniAndroidCompoundButton(QUniAndroidCompoundButtonPrivate &dd, QUniAndroidContext *context = nullptr);

    QAndroidJniObject onCreate() override;
    void onInflate(QAndroidJniObject &instance) override;

private:
    Q_DISABLE_COPY(QUniAndroidCompoundButton)
    Q_DECLARE_PRIVATE(QUniAndroidCompoundButton)

    Q_PRIVATE_SLOT(d_func(), bool _q_updateChecked(bool checked))
};

QT_END_NAMESPACE

#endif // QUNIANDROIDCOMPOUNDBUTTON_P_H
