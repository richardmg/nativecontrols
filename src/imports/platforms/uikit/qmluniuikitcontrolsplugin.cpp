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

#include <QtQml>
#include <QQmlEngine>
#include <QtUniUIKitControls>

QT_BEGIN_NAMESPACE

class QmlUniUIKitControlsPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:

QmlUniUIKitControlsPlugin(QObject *parent = nullptr) : QQmlExtensionPlugin(parent)
{
#ifdef QT_STATIC
    Q_INIT_RESOURCE(qmake_Qt_UniUIKitControls);
#endif
}

void registerTypes(const char *uri) override
{
    qmlRegisterType<QUniUIKitControl>();
    qmlRegisterType<QUniUIKitWindow>(uri, 1, 0, "Window");
    qmlRegisterType<QUniUIKitView>(uri, 1, 0, "View");
    qmlRegisterType<QUniUIKitButton>(uri, 1, 0, "Button");
    qmlRegisterType<QUniUIKitTextField>(uri, 1, 0, "TextField");
    qmlRegisterType<QUniUIKitTextFieldDelegate>(uri, 1, 0, "TextFieldDelegate");
    qmlRegisterType<QUniUIKitSearchField>(uri, 1, 0, "SearchField");
    qmlRegisterType<QUniUIKitLabel>(uri, 1, 0, "Label");
    qmlRegisterType<QUniUIKitSlider>(uri, 1, 0, "Slider");
    qmlRegisterType<QUniUIKitTableView>(uri, 1, 0, "TableView");
    qmlRegisterType<QUniUIKitTableViewCell>(uri, 1, 0, "TableViewCell");
    qmlRegisterType<QUniUIKitTableViewDataSource>(uri, 1, 0, "TableViewDataSource");
    qmlRegisterType<QUniUIKitViewController>(uri, 1, 0, "ViewController");
    qmlRegisterType<QUniUIKitTabBarController>(uri, 1, 0, "TabBarController");
    qmlRegisterType<QUniUIKitTabBarItem>(uri, 1, 0, "TabBarItem");
    qmlRegisterType<QUniUIKitIndexPath>(uri, 1, 0, "IndexPath");
}

void initializeEngine(QQmlEngine *engine, const char *uri) override
{
    Q_UNUSED(engine);
    Q_UNUSED(uri);
}

};

QT_END_NAMESPACE

#include "qmluniuikitcontrolsplugin.moc"
