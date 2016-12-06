/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
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

#include <QtQuickControls2/private/qquickstyleplugin_p.h>

#include "qqc2nscontrol.h"
#include "qqc2nscontrolimageprovider.h"

#ifdef INCLUDE_FPS
#include "fps.h"
#endif

static inline void initResources()
{
//    Q_INIT_RESOURCE(QtQuickControls2macOSStylePlugin);
//#ifdef QT_STATIC
//    Q_INIT_RESOURCE(qmake_QtQuick_Controls_2_Universal);
//#endif
}

QT_BEGIN_NAMESPACE

#include <QtQuickControls2/private/qquickstyleattached_p.h>
class QQuickMacOSStyle : public QQuickStyleAttached
{
    Q_OBJECT

public:
    QQuickMacOSStyle(QObject *parent = 0) : QQuickStyleAttached(parent)
    { }

};

class QtQuickControls2macOSStylePlugin: public QQuickStylePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QtQuickControls2macOSStylePlugin(QObject *parent = nullptr);

    void registerTypes(const char *uri) override;
    void initializeEngine(QQmlEngine *engine, const char *uri) override;

    QString name() const override;
    QQuickProxyTheme *createTheme() const override;
};

QtQuickControls2macOSStylePlugin::QtQuickControls2macOSStylePlugin(QObject *parent) : QQuickStylePlugin(parent)
{
    initResources();
}

#include <QDebug>

void QtQuickControls2macOSStylePlugin::registerTypes(const char *uri)
{
    qmlRegisterUncreatableType<QQuickMacOSStyle>(uri, 2, 0, "MacOS", tr("MacOS is an attached property"));
    qmlRegisterRevision<QQuickMacOSStyle, 1>(uri, 2, 1);
    qmlRegisterType<QQC2NSControl>(uri, 2, 0, "NSControl");

#ifdef INCLUDE_FPS
    qmlRegisterType<FPS>(uri, 2, 0, "FPS");
#endif
//    QByteArray import = QByteArray(uri);
//    qmlRegisterType(typeUrl(QStringLiteral("Button.qml")), import, 2, 0, "Button");
}

void QtQuickControls2macOSStylePlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQuickStylePlugin::initializeEngine(engine, uri);
    engine->addImageProvider(QStringLiteral("nscontrol"), new ImageProviderNSControl());
}

QString QtQuickControls2macOSStylePlugin::name() const
{
    return QStringLiteral("macOS");
}

QQuickProxyTheme *QtQuickControls2macOSStylePlugin::createTheme() const
{
    return nullptr;
//    return new QQuickMacOSTheme;
}

QT_END_NAMESPACE

#include "qtquickcontrols2macosstyleplugin.moc"
