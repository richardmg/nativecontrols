/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
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

#include <QtNativeControls>
#include <QtNativeAppKitControls>
#include <QtNativeAppKitControls/private/qnativeappkitbase_p.h>

QT_BEGIN_NAMESPACE

class QNativeAppKitPlatformPlugin : public QObject, QNativePlatformPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QNativePlatformPluginInterface_iid FILE "plugin.json")
    Q_INTERFACES(QNativePlatformPluginInterface)

public:
    explicit QNativeAppKitPlatformPlugin(QObject* = 0) {}
    ~QNativeAppKitPlatformPlugin() {}

    virtual QNativePlatformBase* create(QNativeBase *nativeBase) const override
    {
        QNativeAppKitBase *appkitBase = nullptr;
        if (dynamic_cast<QNativeWindow *>(nativeBase))
            appkitBase = new QNativeAppKitWindow();
        else if (dynamic_cast<QNativeButton *>(nativeBase))
            appkitBase = new QNativeAppKitButton(nullptr);
        else if (dynamic_cast<QNativeTextField *>(nativeBase))
            appkitBase = new QNativeAppKitTextField(nullptr);
        else if (dynamic_cast<QNativeSearchField *>(nativeBase))
            appkitBase = new QNativeAppKitSearchField(nullptr);
        else if (dynamic_cast<QNativeView *>(nativeBase))
            appkitBase = new QNativeAppKitView(nullptr);
        else
            Q_UNREACHABLE();

        appkitBase->d_func()->connectSignals(nativeBase);
        return appkitBase;
    }
};

QT_END_NAMESPACE

#include "qnativeappkitplatformplugin.moc"
