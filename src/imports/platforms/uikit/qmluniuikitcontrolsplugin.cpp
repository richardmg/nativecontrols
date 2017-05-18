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

#define REGISTER_TYPE(NAME) qmlRegisterType<QUniUIKit##NAME>(uri, 1, 0, #NAME);

void registerTypes(const char *uri) override
{
    REGISTER_TYPE(Responder)
    REGISTER_TYPE(Control)
    REGISTER_TYPE(Window)
    REGISTER_TYPE(View)
    REGISTER_TYPE(Button)
    REGISTER_TYPE(TextField)
    REGISTER_TYPE(TextFieldDelegate)
    REGISTER_TYPE(SearchField)
    REGISTER_TYPE(Label)
    REGISTER_TYPE(Slider)
    REGISTER_TYPE(TableView)
    REGISTER_TYPE(TableViewCell)
    REGISTER_TYPE(TableViewDataSource)
    REGISTER_TYPE(ViewController)
    REGISTER_TYPE(TabBarController)
    REGISTER_TYPE(TabBarItem)
    REGISTER_TYPE(IndexPath)
    REGISTER_TYPE(Range)
}

void initializeEngine(QQmlEngine *engine, const char *uri) override
{
    Q_UNUSED(engine);
    Q_UNUSED(uri);
}

};

QT_END_NAMESPACE

#include "qmluniuikitcontrolsplugin.moc"
