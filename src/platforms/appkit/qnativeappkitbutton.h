/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native AppKit Controls module of the Qt Toolkit.
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

#ifndef QNATIVEAPPKITBUTTON_H
#define QNATIVEAPPKITBUTTON_H

#include <QtNativeControls/qnativeplatformbutton.h>
#include <QtNativeAppKitControls/qnativeappkitcontrol.h>

QT_BEGIN_NAMESPACE

class QNativeAppKitButtonPrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(NSButton);

class Q_NATIVEAPPKITCONTROLS_EXPORT QNativeAppKitButton : public QNativeAppKitControl, public virtual QNativePlatformButton
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    QNativeAppKitButton(QNativeAppKitBase *parent = nullptr);
    QNativeAppKitButton(const QString &text, QNativeAppKitBase *parent = nullptr);
    virtual ~QNativeAppKitButton();

    NSButton *nsButtonHandle();

    virtual QString text() override;
    virtual void setText(const QString &text) override;

Q_SIGNALS:
    void textChanged(const QString &text);
    void clicked();

protected:
    QNativeAppKitButton(QNativeAppKitButtonPrivate &dd, QNativeAppKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativeAppKitButton)
    Q_DISABLE_COPY(QNativeAppKitButton)
};

QT_END_NAMESPACE

#endif // QNATIVEAPPKITBUTTON_H
