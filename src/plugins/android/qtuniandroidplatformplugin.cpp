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
#include <QtNativeAndroid/private/quniandroidbutton_p.h>
#include <QtNativeAndroid/private/quniandroidactivity_p.h>

QT_BEGIN_NAMESPACE

class QUniAndroidPlatformButton : private QUniAndroidButton, public QUniPlatformButton
{
    Q_OBJECT

public:
    QUniAndroidPlatformButton(QUniButton *button)
    {
        // TODO: signal arguments
        connect(this, &QUniAndroidView::visibleChanged, [=]() { emit button->visibleChanged(isVisible()); });
        connect(this, &QUniAndroidButton::textChanged, [=]() { emit button->textChanged(text()); });
        connect(this, &QUniAndroidButton::click, button, &QUniButton::clicked);
    }

    // QUniPlatformBase
    void setPlatformParent(QUniPlatformBase *parent) override
    {
        QUniAndroidObject *nativeParent = reinterpret_cast<QUniAndroidObject *>(parent);
        if (QUniAndroidActivity *nativeActivity = qobject_cast<QUniAndroidActivity *>(nativeParent))
            nativeActivity->setContentView(this);
        else if (QUniAndroidView *nativeView = qobject_cast<QUniAndroidView *>(nativeParent))
            setParentView(nativeView);
    }

    // QUniPlatformControl
    bool visible() const override { return QUniAndroidView::isVisible(); }
    void setVisible(bool visible) override { QUniAndroidView::setVisible(visible); }
    // TODO: QUniAndroidView::geometry() & setGeometry()
    QRectF geometry() const override { return QRectF(QUniAndroidView::x(), QUniAndroidView::y(),
                                                     QUniAndroidView::width(), QUniAndroidView::height()); }
    void setGeometry(const QRectF &rect) override
    {
        QUniAndroidView::setX(rect.x());
        QUniAndroidView::setY(rect.y());
        QUniAndroidView::setWidth(rect.width());
        QUniAndroidView::setHeight(rect.height());
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

    // QUniPlatformButton
    QString text() override { return QUniAndroidButton::text(); }
    void setText(const QString &text) override { QUniAndroidButton::setText(text); }
};

class QUniAndroidPlatformWindow : private QUniAndroidActivity, public QUniPlatformWindow
{
    Q_OBJECT

public:
    QUniAndroidPlatformWindow(QUniWindow *window)
    {
        Q_UNUSED(window);
    }

    // QUniPlatformBase
    void setPlatformParent(QUniPlatformBase *parent) override { Q_UNUSED(parent); }

    qreal width() const override { return NAN; }
    qreal height() const override { return NAN; }

    // QUniPlatformWindow ### TODO: how does this map to Activity?
    bool isVisible() const override { return true; }
    void setVisible(bool visible) override { Q_UNUSED(visible); }
    void showFullScreen() override { QUniAndroidActivity::start(); }
};

class QtNativeAndroidPlatformPlugin : public QObject, QUniPlatformPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QUniPlatformPluginInterface_iid FILE "plugin.json")
    Q_INTERFACES(QUniPlatformPluginInterface)

public:
    virtual QUniPlatformBase* create(QUniBase *nativeBase) const override
    {
        if (QUniButton *nativeButton = qobject_cast<QUniButton *>(nativeBase))
            return new QUniAndroidPlatformButton(nativeButton);
        if (QUniWindow *nativeWindow = qobject_cast<QUniWindow *>(nativeBase))
            return new QUniAndroidPlatformWindow(nativeWindow);
        return nullptr;
    }
};

QT_END_NAMESPACE

#include "qtnativeandroidplatformplugin.moc"
