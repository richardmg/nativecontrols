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
#include <QtNativeAppKitControls/private/quniappkitbase_p.h>

QT_BEGIN_NAMESPACE

class QAppKitPluginTabsPageTab : public QUniAppKitViewController, public virtual QUniPlatformTabsPageTab
{
public:
    explicit QAppKitPluginTabsPageTab()
        : QUniAppKitViewController(nullptr)
    {
        // A QUniAppKitTabViewItem doesn't map directy to a QUniPlatformTabsPageTab since
        // a tab in uikit consist of a view controller with a tab bar item. So we create this
        // helper class that puts together the composition.
        m_tabViewItem = new QUniAppKitTabViewItem(this);
    }

    void setPlatformParent(QUniPlatformBase *platformParent) override
    {
        // If the new, or the old, parent is a viewcontroller, we need to
        // add, or remove, ourselves from the list of child controllers it contains.
        if (!platformParent) {
            if (QUniAppKitTabViewController *prevParent = dynamic_cast<QUniAppKitTabViewController *>(parent())) {
                QList<QUniAppKitTabViewItem *> tabItems = prevParent->tabViewItems();
                tabItems.removeOne(m_tabViewItem);
                prevParent->setTabViewItems(tabItems);
            }
        } else if (QUniAppKitTabViewController *newParent = dynamic_cast<QUniAppKitTabViewController *>(platformParent)) {
            QList<QUniAppKitTabViewItem *> tabItems = newParent->tabViewItems();
            tabItems.append(m_tabViewItem);
            newParent->setTabViewItems(tabItems);
        }

        // We also need to update the QObject parent structure for memory management
        QUniAppKitViewController::setPlatformParent(platformParent);
    }

    QString title() const override { return m_tabViewItem->title(); }
    void setTitle(const QString &title) override { m_tabViewItem->setTitle(title); }

    QUniAppKitTabViewItem *m_tabViewItem;
};

// ----------------------------------------------------------------------------------

class QUniAppKitPlatformPlugin : public QObject, QUniPlatformPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QUniPlatformPluginInterface_iid FILE "plugin.json")
    Q_INTERFACES(QUniPlatformPluginInterface)

public:
    explicit QUniAppKitPlatformPlugin(QObject* = 0) {}
    ~QUniAppKitPlatformPlugin() {}

     virtual QUniPlatformWindow* createWindow(QUniWindow *window) const override
     {
         auto platform = new QUniAppKitWindow();
         static_cast<QUniAppKitBase *>(platform)->d_func()->connectSignals(window);
         return platform;
     }

     virtual QUniPlatformView* createView(QUniView *view) const override
     {
         auto platform = new QUniAppKitView();
         static_cast<QUniAppKitBase *>(platform)->d_func()->connectSignals(view);
         return platform;
     }

     virtual QUniPlatformControl* createControl(QUniControl *control) const override
     {
         auto platform = new QUniAppKitControl();
         static_cast<QUniAppKitBase *>(platform)->d_func()->connectSignals(control);
         return platform;
     }

     virtual QUniPlatformButton* createButton(QUniButton *button) const override
     {
         auto platform = new QUniAppKitButton();
         static_cast<QUniAppKitBase *>(platform)->d_func()->connectSignals(button);
         return platform;
     }

     virtual QUniPlatformTextField* createTextField(QUniTextField *textField) const override
     {
         auto platform = new QUniAppKitTextField();
         static_cast<QUniAppKitBase *>(platform)->d_func()->connectSignals(textField);
         return platform;
     }

     virtual QUniPlatformSearchField* createSearchField(QUniSearchField *searchField) const override
     {
         auto platform = new QUniAppKitSearchField();
         static_cast<QUniAppKitBase *>(platform)->d_func()->connectSignals(searchField);
         return platform;
     }

     virtual QUniPlatformPage* createPage(QUniPage *page) const override
     {
         auto platform = new QUniAppKitViewController();
         static_cast<QUniAppKitBase *>(platform)->d_func()->connectSignals(page);
         return platform;
     }

     virtual QUniPlatformTabsPage* createTabsPage(QUniTabsPage *tabsPage) const override
     {
         auto platform = new QUniAppKitTabViewController();
         static_cast<QUniAppKitBase *>(platform)->d_func()->connectSignals(tabsPage);
         return platform;
     }

     virtual QUniPlatformTabsPageTab* createTabsPageTab(QUniTabsPageTab *tabsPageTab) const override
     {
         auto platform = new QAppKitPluginTabsPageTab();
         static_cast<QUniAppKitBase *>(platform)->d_func()->connectSignals(tabsPageTab);
         return platform;
     }

};

QT_END_NAMESPACE

#include "quniappkitplatformplugin.moc"
