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
#include <QtNativeUIKitControls>
#include <QtNativeUIKitControls/private/quniuikitbase_p.h>

QT_BEGIN_NAMESPACE

class QUIKitPluginTabsPageTab : public QNativeUIKitViewController, public virtual QNativePlatformTabsPageTab
{
public:
    explicit QUIKitPluginTabsPageTab()
        : QNativeUIKitViewController(nullptr)
    {
        // A QNativeUIKitTabBarItem doesn't map directy to a QNativePlatformTabsPageTab since
        // a tab in uikit consist of a view controller with a tab bar item. So we create this
        // helper class that puts together the composition.
        setTabBarItem(new QNativeUIKitTabBarItem(this));
    }

    void setPlatformParent(QNativePlatformBase *platformParent) override
    {
        // If the new, or the old, parent is a tab bar controller, we need to
        // add, or remove, ourselves from the list of tabs it contains.
        if (!platformParent) {
            if (QNativeUIKitTabBarController *prevTabBar = dynamic_cast<QNativeUIKitTabBarController *>(parent())) {
                QList<QNativeUIKitViewController *> viewControllers = prevTabBar->viewControllers();
                viewControllers.removeOne(this);
                prevTabBar->setViewControllers(viewControllers);
            }
        } else if (QNativeUIKitTabBarController *tabBar = dynamic_cast<QNativeUIKitTabBarController *>(platformParent)) {
            QList<QNativeUIKitViewController *> viewControllers = tabBar->viewControllers();
            viewControllers.append(this);
            tabBar->setViewControllers(viewControllers);
        }

        // We also need to update the QObject parent structure for memory management
        QNativeUIKitViewController::setPlatformParent(platformParent);
    }

    QString title() const override { return tabBarItem()->title(); }
    void setTitle(const QString &title) override { tabBarItem()->setTitle(title); }
};

// ----------------------------------------------------------------------------------

class QNativeUIKitPlatformPlugin : public QObject, QNativePlatformPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QNativePlatformPluginInterface_iid FILE "plugin.json")
    Q_INTERFACES(QNativePlatformPluginInterface)

public:
    explicit QNativeUIKitPlatformPlugin(QObject* = 0) {}
    ~QNativeUIKitPlatformPlugin() {}

    virtual QNativePlatformWindow* createWindow(QNativeWindow *window) const override
    {
        auto platform = new QNativeUIKitWindow();
        static_cast<QNativeUIKitBase *>(platform)->d_func()->connectSignals(window);
        return platform;
    }

    virtual QNativePlatformView* createView(QNativeView *view) const override
    {
        auto platform = new QNativeUIKitView();
        static_cast<QNativeUIKitBase *>(platform)->d_func()->connectSignals(view);
        return platform;
    }

    virtual QNativePlatformControl* createControl(QNativeControl *control) const override
    {
        auto platform = new QNativeUIKitControl();
        static_cast<QNativeUIKitBase *>(platform)->d_func()->connectSignals(control);
        return platform;
    }

    virtual QNativePlatformButton* createButton(QNativeButton *button) const override
    {
        auto platform = new QNativeUIKitButton();
        static_cast<QNativeUIKitBase *>(platform)->d_func()->connectSignals(button);
        return platform;
    }

    virtual QNativePlatformTextField* createTextField(QNativeTextField *textField) const override
    {
        auto platform = new QNativeUIKitTextField();
        static_cast<QNativeUIKitBase *>(platform)->d_func()->connectSignals(textField);
        return platform;
    }

    virtual QNativePlatformSearchField* createSearchField(QNativeSearchField *searchField) const override
    {
        auto platform = new QNativeUIKitSearchField();
        static_cast<QNativeUIKitBase *>(platform)->d_func()->connectSignals(searchField);
        return platform;
    }

    virtual QNativePlatformPage* createPage(QNativePage *page) const override
    {
        auto platform = new QNativeUIKitViewController();
        static_cast<QNativeUIKitBase *>(platform)->d_func()->connectSignals(page);
        return platform;
    }

    virtual QNativePlatformTabsPage* createTabsPage(QNativeTabsPage *tabsPage) const override
    {
        auto platform = new QNativeUIKitTabBarController();
        static_cast<QNativeUIKitBase *>(platform)->d_func()->connectSignals(tabsPage);
        return platform;
    }

    virtual QNativePlatformTabsPageTab* createTabsPageTab(QNativeTabsPageTab *tabsPageTab) const override
    {
        auto platform = new QUIKitPluginTabsPageTab();
        static_cast<QNativeUIKitBase *>(platform)->d_func()->connectSignals(tabsPageTab);
        return platform;
    }

};

QT_END_NAMESPACE

#include "quniuikitplatformplugin.moc"
