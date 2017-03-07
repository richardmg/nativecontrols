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

class QAppKitPluginTabsPageTab : public QNativeAppKitViewController, public virtual QNativePlatformTabsPageTab
{
public:
    explicit QAppKitPluginTabsPageTab()
        : QNativeAppKitViewController(nullptr)
    {
        // A QNativeAppKitTabViewItem doesn't map directy to a QNativePlatformTabsPageTab since
        // a tab in uikit consist of a view controller with a tab bar item. So we create this
        // helper class that puts together the composition.
        m_tabViewItem = new QNativeAppKitTabViewItem(this);
    }

    void setPlatformParent(QNativePlatformBase *platformParent) override
    {
        // If the new, or the old, parent is a viewcontroller, we need to
        // add, or remove, ourselves from the list of child controllers it contains.
        if (!platformParent) {
            if (QNativeAppKitTabViewController *prevParent = dynamic_cast<QNativeAppKitTabViewController *>(parent())) {
                QList<QNativeAppKitViewController *> viewControllers = prevParent->childViewControllers();
                viewControllers.removeOne(this);
                prevParent->setChildViewControllers(viewControllers);
                QList<QNativeAppKitTabViewItem *> tabItems = prevParent->tabViewItems();
                tabItems.removeOne(m_tabViewItem);
                prevParent->setTabViewItems(tabItems);
            }
        } else if (QNativeAppKitTabViewController *newParent = dynamic_cast<QNativeAppKitTabViewController *>(platformParent)) {
            QList<QNativeAppKitViewController *> viewControllers = newParent->childViewControllers();
            viewControllers.append(this);
            newParent->setChildViewControllers(viewControllers);
            QList<QNativeAppKitTabViewItem *> tabItems = newParent->tabViewItems();
            tabItems.append(m_tabViewItem);
            newParent->setTabViewItems(tabItems);
        }

        // We also need to update the QObject parent structure for memory management
        QNativeAppKitViewController::setPlatformParent(platformParent);
    }

    QString title() const override { return m_tabViewItem->title(); }
    void setTitle(const QString &title) override { m_tabViewItem->setTitle(title); }

    QNativeAppKitTabViewItem *m_tabViewItem;
};

// ----------------------------------------------------------------------------------

class QNativeAppKitPlatformPlugin : public QObject, QNativePlatformPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QNativePlatformPluginInterface_iid FILE "plugin.json")
    Q_INTERFACES(QNativePlatformPluginInterface)

public:
    explicit QNativeAppKitPlatformPlugin(QObject* = 0) {}
    ~QNativeAppKitPlatformPlugin() {}

     virtual QNativePlatformWindow* createWindow(QNativeWindow *window) const override
     {
         auto platform = new QNativeAppKitWindow();
         static_cast<QNativeAppKitBase *>(platform)->d_func()->connectSignals(window);
         return platform;
     }

     virtual QNativePlatformView* createView(QNativeView *view) const override
     {
         auto platform = new QNativeAppKitView();
         static_cast<QNativeAppKitBase *>(platform)->d_func()->connectSignals(view);
         return platform;
     }

     virtual QNativePlatformControl* createControl(QNativeControl *control) const override
     {
         auto platform = new QNativeAppKitControl();
         static_cast<QNativeAppKitBase *>(platform)->d_func()->connectSignals(control);
         return platform;
     }

     virtual QNativePlatformButton* createButton(QNativeButton *button) const override
     {
         auto platform = new QNativeAppKitButton();
         static_cast<QNativeAppKitBase *>(platform)->d_func()->connectSignals(button);
         return platform;
     }

     virtual QNativePlatformTextField* createTextField(QNativeTextField *textField) const override
     {
         auto platform = new QNativeAppKitTextField();
         static_cast<QNativeAppKitBase *>(platform)->d_func()->connectSignals(textField);
         return platform;
     }

     virtual QNativePlatformSearchField* createSearchField(QNativeSearchField *searchField) const override
     {
         auto platform = new QNativeAppKitSearchField();
         static_cast<QNativeAppKitBase *>(platform)->d_func()->connectSignals(searchField);
         return platform;
     }

     virtual QNativePlatformPage* createPage(QNativePage *page) const override
     {
         auto platform = new QNativeAppKitViewController();
         static_cast<QNativeAppKitBase *>(platform)->d_func()->connectSignals(page);
         return platform;
     }

     virtual QNativePlatformTabsPage* createTabsPage(QNativeTabsPage *tabsPage) const override
     {
         auto platform = new QNativeAppKitTabViewController();
         static_cast<QNativeAppKitBase *>(platform)->d_func()->connectSignals(tabsPage);
         return platform;
     }

     virtual QNativePlatformTabsPageTab* createTabsPageTab(QNativeTabsPageTab *tabsPageTab) const override
     {
         auto platform = new QAppKitPluginTabsPageTab();
         static_cast<QNativeAppKitBase *>(platform)->d_func()->connectSignals(tabsPageTab);
         return platform;
     }

};

QT_END_NAMESPACE

#include "qnativeappkitplatformplugin.moc"
