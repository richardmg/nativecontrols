/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
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
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtNativeControls>
#include <QtNativeAndroid/private/qnativeandroidbutton_p.h>
#include <QtNativeAndroid/private/qnativeandroidactivity_p.h>

QT_BEGIN_NAMESPACE

class QNativeAndroidPlatformButton : private QNativeAndroidButton, public QNativePlatformButton
{
    Q_OBJECT

public:
    QNativeAndroidPlatformButton(QNativeButton *button)
    {
        // TODO: signal arguments
        connect(this, &QNativeAndroidView::visibleChanged, [=]() { emit button->visibleChanged(isVisible()); });
        connect(this, &QNativeAndroidButton::textChanged, [=]() { emit button->textChanged(text()); });
        connect(this, &QNativeAndroidButton::click, button, &QNativeButton::clicked);
    }

    // QNativePlatformBase
    void setPlatformParent(QNativePlatformBase *parent) override
    {
        QNativeAndroidObject *nativeParent = reinterpret_cast<QNativeAndroidObject *>(parent);
        if (QNativeAndroidActivity *nativeActivity = qobject_cast<QNativeAndroidActivity *>(nativeParent))
            nativeActivity->setContentView(this);
        else if (QNativeAndroidView *nativeView = qobject_cast<QNativeAndroidView *>(nativeParent))
            setParentView(nativeView);
    }

    // QNativePlatformControl
    bool visible() const override { return QNativeAndroidView::isVisible(); }
    void setVisible(bool visible) override { QNativeAndroidView::setVisible(visible); }
    // TODO: QNativeAndroidView::geometry() & setGeometry()
    QRectF geometry() const override { return QRectF(QNativeAndroidView::x(), QNativeAndroidView::y(),
                                                     QNativeAndroidView::width(), QNativeAndroidView::height()); }
    void setGeometry(const QRectF &rect) override
    {
        QNativeAndroidView::setX(rect.x());
        QNativeAndroidView::setY(rect.y());
        QNativeAndroidView::setWidth(rect.width());
        QNativeAndroidView::setHeight(rect.height());
    }

    QRectF frameGeometry() const override { return geometry(); }

    void move(const QPointF &pos) override
    {
        Q_UNIMPLEMENTED();
    }

    void resize(const QSizeF size) override
    {
        Q_UNIMPLEMENTED();
    }

    QSizeF implicitSize() const
    {
        Q_UNIMPLEMENTED();
        return QSizeF();
    }

    // QNativePlatformButton
    QString text() override { return QNativeAndroidButton::text(); }
    void setText(const QString &text) override { QNativeAndroidButton::setText(text); }
};

class QNativeAndroidPlatformWindow : private QNativeAndroidActivity, public QNativePlatformWindow
{
    Q_OBJECT

public:
    QNativeAndroidPlatformWindow(QNativeWindow *window)
    {
        Q_UNUSED(window);
    }

    // QNativePlatformBase
    void setPlatformParent(QNativePlatformBase *parent) override { Q_UNUSED(parent); }

    qreal width() const override { return NAN; }
    qreal height() const override { return NAN; }

    // QNativePlatformWindow ### TODO: how does this map to Activity?
    bool isVisible() const override { return true; }
    void setVisible(bool visible) override { Q_UNUSED(visible); }
    void showFullScreen() override { QNativeAndroidActivity::start(); }
};

class QtNativeAndroidPlatformPlugin : public QObject, QNativePlatformPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QNativePlatformPluginInterface_iid FILE "plugin.json")
    Q_INTERFACES(QNativePlatformPluginInterface)

public:
    virtual QNativePlatformBase* create(QNativeBase *nativeBase) const override
    {
        if (QNativeButton *nativeButton = qobject_cast<QNativeButton *>(nativeBase))
            return new QNativeAndroidPlatformButton(nativeButton);
        if (QNativeWindow *nativeWindow = qobject_cast<QNativeWindow *>(nativeBase))
            return new QNativeAndroidPlatformWindow(nativeWindow);
        return nullptr;
    }
};

QT_END_NAMESPACE

#include "qtnativeandroidplatformplugin.moc"
