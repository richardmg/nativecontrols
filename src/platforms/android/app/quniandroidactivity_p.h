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

#ifndef QUNIANDROIDACTIVITY_P_H
#define QUNIANDROIDACTIVITY_P_H

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

#include <QtUniAndroid/private/quniandroidcontextwrapper_p.h>

QT_BEGIN_NAMESPACE

class QUniAndroidView;
class QUniAndroidMenu;
class QUniAndroidWindow;
class QUniAndroidActionBar;
class QUniAndroidActivityPrivate;

class Q_UNIANDROID_EXPORT QUniAndroidActivity : public QUniAndroidContextWrapper
{
    Q_OBJECT
    Q_PROPERTY(QUniAndroidWindow *window READ window CONSTANT)
    Q_PROPERTY(QUniAndroidActionBar *actionBar READ actionBar WRITE setActionBar)
    Q_PROPERTY(QUniAndroidMenu *optionsMenu READ optionsMenu WRITE setOptionsMenu)
    Q_PROPERTY(QUniAndroidView *contentView READ contentView WRITE setContentView)

public:
    explicit QUniAndroidActivity(QObject *parent = nullptr);

    QUniAndroidWindow *window() const;

    QUniAndroidActionBar *actionBar() const;
    void setActionBar(QUniAndroidActionBar *bar);

    QUniAndroidMenu *optionsMenu() const;
    void setOptionsMenu(QUniAndroidMenu *menu);

    QUniAndroidView *contentView() const;
    void setContentView(QUniAndroidView *view);

public Q_SLOTS:
    void start();

protected:
    void classBegin() override;
    void componentComplete() override;

private:
    Q_DISABLE_COPY(QUniAndroidActivity)
    Q_DECLARE_PRIVATE(QUniAndroidActivity)
};

QT_END_NAMESPACE

#endif // QUNIANDROIDACTIVITY_P_H
