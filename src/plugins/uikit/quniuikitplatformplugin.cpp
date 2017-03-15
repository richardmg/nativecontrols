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

class QUIKitPluginTabsPageTab : public QUniUIKitViewController, public virtual QUniPlatformTabsPageTab
{
public:
    explicit QUIKitPluginTabsPageTab()
        : QUniUIKitViewController(nullptr)
    {
        // A QUniUIKitTabBarItem doesn't map directy to a QUniPlatformTabsPageTab since
        // a tab in uikit consist of a view controller with a tab bar item. So we create this
        // helper class that puts together the composition.
        setTabBarItem(new QUniUIKitTabBarItem(this));
    }

    void setPlatformParent(QUniPlatformBase *platformParent) override
    {
        // If the new, or the old, parent is a tab bar controller, we need to
        // add, or remove, ourselves from the list of tabs it contains.
        if (!platformParent) {
            if (QUniUIKitTabBarController *prevTabBar = dynamic_cast<QUniUIKitTabBarController *>(parent())) {
                QList<QUniUIKitViewController *> viewControllers = prevTabBar->viewControllers();
                viewControllers.removeOne(this);
                prevTabBar->setViewControllers(viewControllers);
            }
        } else if (QUniUIKitTabBarController *tabBar = dynamic_cast<QUniUIKitTabBarController *>(platformParent)) {
            QList<QUniUIKitViewController *> viewControllers = tabBar->viewControllers();
            viewControllers.append(this);
            tabBar->setViewControllers(viewControllers);
        }

        // We also need to update the QObject parent structure for memory management
        QUniUIKitViewController::setPlatformParent(platformParent);
    }

    QString title() const override { return tabBarItem()->title(); }
    void setTitle(const QString &title) override { tabBarItem()->setTitle(title); }
};

// ----------------------------------------------------------------------------------

class QUniUIKitPlatformPlugin : public QObject, QUniPlatformPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QUniPlatformPluginInterface_iid FILE "plugin.json")
    Q_INTERFACES(QUniPlatformPluginInterface)

public:
    explicit QUniUIKitPlatformPlugin(QObject* = 0) {}
    ~QUniUIKitPlatformPlugin() {}

    virtual QUniPlatformWindow* createWindow(QUniWindow *window) const override
    {
        auto platform = new QUniUIKitWindow();
        static_cast<QUniUIKitBase *>(platform)->d_func()->connectSignals(window);
        return platform;
    }

    virtual QUniPlatformView* createView(QUniView *view) const override
    {
        auto platform = new QUniUIKitView();
        static_cast<QUniUIKitBase *>(platform)->d_func()->connectSignals(view);
        return platform;
    }

    virtual QUniPlatformControl* createControl(QUniControl *control) const override
    {
        auto platform = new QUniUIKitControl();
        static_cast<QUniUIKitBase *>(platform)->d_func()->connectSignals(control);
        return platform;
    }

    virtual QUniPlatformButton* createButton(QUniButton *button) const override
    {
        auto platform = new QUniUIKitButton();
        static_cast<QUniUIKitBase *>(platform)->d_func()->connectSignals(button);
        return platform;
    }

    virtual QUniPlatformTextField* createTextField(QUniTextField *textField) const override
    {
        auto platform = new QUniUIKitTextField();
        static_cast<QUniUIKitBase *>(platform)->d_func()->connectSignals(textField);
        return platform;
    }

    virtual QUniPlatformSearchField* createSearchField(QUniSearchField *searchField) const override
    {
        auto platform = new QUniUIKitSearchField();
        static_cast<QUniUIKitBase *>(platform)->d_func()->connectSignals(searchField);
        return platform;
    }

    virtual QUniPlatformPage* createPage(QUniPage *page) const override
    {
        auto platform = new QUniUIKitViewController();
        static_cast<QUniUIKitBase *>(platform)->d_func()->connectSignals(page);
        return platform;
    }

    virtual QUniPlatformTabsPage* createTabsPage(QUniTabsPage *tabsPage) const override
    {
        auto platform = new QUniUIKitTabBarController();
        static_cast<QUniUIKitBase *>(platform)->d_func()->connectSignals(tabsPage);
        return platform;
    }

    virtual QUniPlatformTabsPageTab* createTabsPageTab(QUniTabsPageTab *tabsPageTab) const override
    {
        auto platform = new QUIKitPluginTabsPageTab();
        static_cast<QUniUIKitBase *>(platform)->d_func()->connectSignals(tabsPageTab);
        return platform;
    }

};

QT_END_NAMESPACE

#include "quniuikitplatformplugin.moc"
