/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native Controls module of the Qt Toolkit.
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

#ifndef QNATIVECONTROLSPLATFORMPLUGIN_H
#define QNATIVECONTROLSPLATFORMPLUGIN_H

#include <QtCore/QtPlugin>

QT_BEGIN_NAMESPACE

#define Q_NATIVE_FORWARD_DECLARE(TYPE) class QNative ## TYPE; class QNativePlatform ## TYPE;

Q_NATIVE_FORWARD_DECLARE(Window)
Q_NATIVE_FORWARD_DECLARE(View)
Q_NATIVE_FORWARD_DECLARE(Control)
Q_NATIVE_FORWARD_DECLARE(Button)
Q_NATIVE_FORWARD_DECLARE(TextField)
Q_NATIVE_FORWARD_DECLARE(SearchField)
Q_NATIVE_FORWARD_DECLARE(Page)
Q_NATIVE_FORWARD_DECLARE(TabsPage)
Q_NATIVE_FORWARD_DECLARE(TabsPageTab)

#define QNativePlatformPluginInterface_iid "org.qt-project.Qt.Native.Platform"

class QNativePlatformPluginInterface
{
public:
    virtual ~QNativePlatformPluginInterface() {}

    virtual QNativePlatformWindow* createWindow(QNativeWindow *window) const = 0;
    virtual QNativePlatformView* createView(QNativeView *view) const = 0;
    virtual QNativePlatformControl* createControl(QNativeControl *control) const = 0;
    virtual QNativePlatformButton* createButton(QNativeButton *button) const = 0;
    virtual QNativePlatformTextField* createTextField(QNativeTextField *textField) const = 0;
    virtual QNativePlatformSearchField* createSearchField(QNativeSearchField *searchField) const = 0;
    virtual QNativePlatformPage* createPage(QNativePage *page) const = 0;
    virtual QNativePlatformTabsPage* createTabsPage(QNativeTabsPage *tabsPage) const = 0;
    virtual QNativePlatformTabsPageTab* createTabsPageTab(QNativeTabsPageTab *tabsPageTab) const = 0;
};

Q_DECLARE_INTERFACE(QNativePlatformPluginInterface, QNativePlatformPluginInterface_iid)

QT_END_NAMESPACE

#endif // QNATIVECONTROLSPLATFORMPLUGIN_H
