/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt QML Android module of the Qt Toolkit.
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

#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>

#include <QtUniAndroid/private/quniandroidarrayadapter_p.h>
#include <QtUniAndroid/private/quniandroidbutton_p.h>
#include <QtUniAndroid/private/quniandroidcalendarview_p.h>
#include <QtUniAndroid/private/quniandroidcheckbox_p.h>
#include <QtUniAndroid/private/quniandroiddatepicker_p.h>
#include <QtUniAndroid/private/quniandroidedittext_p.h>
#include <QtUniAndroid/private/quniandroidframelayout_p.h>
#include <QtUniAndroid/private/quniandroidframelayoutparams_p.h>
#include <QtUniAndroid/private/quniandroidimageview_p.h>
#include <QtUniAndroid/private/quniandroidlinearlayout_p.h>
#include <QtUniAndroid/private/quniandroidlinearlayoutparams_p.h>
#include <QtUniAndroid/private/quniandroidlistview_p.h>
#include <QtUniAndroid/private/quniandroidnumberpicker_p.h>
#include <QtUniAndroid/private/quniandroidpopupmenu_p.h>
#include <QtUniAndroid/private/quniandroidprogressbar_p.h>
#include <QtUniAndroid/private/quniandroidradiobutton_p.h>
#include <QtUniAndroid/private/quniandroidradiogroup_p.h>
#include <QtUniAndroid/private/quniandroidratingbar_p.h>
#include <QtUniAndroid/private/quniandroidrelativelayout_p.h>
#include <QtUniAndroid/private/quniandroidrelativelayoutparams_p.h>
#include <QtUniAndroid/private/quniandroidscrollview_p.h>
#include <QtUniAndroid/private/quniandroidsearchview_p.h>
#include <QtUniAndroid/private/quniandroidseekbar_p.h>
#include <QtUniAndroid/private/quniandroidspace_p.h>
#include <QtUniAndroid/private/quniandroidspinner_p.h>
#include <QtUniAndroid/private/quniandroidswitch_p.h>
#include <QtUniAndroid/private/quniandroidtabhost_p.h>
#include <QtUniAndroid/private/quniandroidtabspec_p.h>
#include <QtUniAndroid/private/quniandroidtabwidget_p.h>
#include <QtUniAndroid/private/quniandroidtextview_p.h>
#include <QtUniAndroid/private/quniandroidtimepicker_p.h>
#include <QtUniAndroid/private/quniandroidtoast_p.h>
#include <QtUniAndroid/private/quniandroidtogglebutton_p.h>
#include <QtUniAndroid/private/quniandroidviewanimator_p.h>
#include <QtUniAndroid/private/quniandroidviewflipper_p.h>
#include <QtUniAndroid/private/quniandroidviewswitcher_p.h>

QT_BEGIN_NAMESPACE

class QtQmlAndroidWidgetPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")

public:
    void registerTypes(const char *uri) override;
};

void QtQmlAndroidWidgetPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<QUniAndroidArrayAdapter>(uri, 0, 21, "ArrayAdapter");
    qmlRegisterType<QUniAndroidBaseAdapter>();
    qmlRegisterType<QUniAndroidButton>(uri, 0, 21, "Button");
    qmlRegisterType<QUniAndroidCalendarView>(uri, 0, 21, "CalendarView");
    qmlRegisterType<QUniAndroidCheckBox>(uri, 0, 21, "CheckBox");
    qmlRegisterType<QUniAndroidDatePicker>(uri, 0, 21, "DatePicker");
    qmlRegisterType<QUniAndroidEditText>(uri, 0, 21, "EditText");
    qmlRegisterType<QUniAndroidFrameLayout>(uri, 0, 21, "FrameLayout");
    qmlRegisterType<QUniAndroidFrameLayoutParams>();
    qmlRegisterType<QUniAndroidImageView>(uri, 0, 21, "ImageView");
    qmlRegisterType<QUniAndroidLinearLayout>(uri, 0, 21, "LinearLayout");
    qmlRegisterType<QUniAndroidLinearLayoutParams>();
    qmlRegisterType<QUniAndroidListView>(uri, 0, 21, "ListView");
    qmlRegisterType<QUniAndroidNumberPicker>(uri, 0, 21, "NumberPicker");
    qmlRegisterType<QUniAndroidPopupMenu>(uri, 0, 21, "PopupMenu");
    qmlRegisterType<QUniAndroidProgressBar>(uri, 0, 21, "ProgressBar");
    qmlRegisterType<QUniAndroidRadioButton>(uri, 0, 21, "RadioButton");
    qmlRegisterType<QUniAndroidRadioGroup>(uri, 0, 21, "RadioGroup");
    qmlRegisterType<QUniAndroidRatingBar>(uri, 0, 21, "RatingBar");
    qmlRegisterType<QUniAndroidRelativeLayout>(uri, 0, 21, "RelativeLayout");
    qmlRegisterType<QUniAndroidRelativeLayoutParams>();
    qmlRegisterType<QUniAndroidScrollView>(uri, 0, 21, "ScrollView");
    qmlRegisterType<QUniAndroidSearchView>(uri, 0, 21, "SearchView");
    qmlRegisterType<QUniAndroidSeekBar>(uri, 0, 21, "SeekBar");
    qmlRegisterType<QUniAndroidSpace>(uri, 0, 21, "Space");
    qmlRegisterType<QUniAndroidSpinner>(uri, 0, 21, "Spinner");
    qmlRegisterType<QUniAndroidSwitch>(uri, 0, 21, "Switch");
    qmlRegisterType<QUniAndroidTabHost>(uri, 0, 21, "TabHost");
    qmlRegisterUncreatableType<QUniAndroidTabSpec>(uri, 0, 21, "TabSpec", QStringLiteral("TabSpec is an attached property"));
    qmlRegisterType<QUniAndroidTabWidget>(uri, 0, 21, "TabWidget");
    qmlRegisterType<QUniAndroidTextView>(uri, 0, 21, "TextView");
    qmlRegisterType<QUniAndroidTimePicker>(uri, 0, 21, "TimePicker");
    qmlRegisterType<QUniAndroidToast>(uri, 0, 21, "Toast");
    qmlRegisterType<QUniAndroidToggleButton>(uri, 0, 21, "ToggleButton");
    qmlRegisterType<QUniAndroidViewAnimator>(uri, 0, 21, "ViewAnimator");
    qmlRegisterType<QUniAndroidViewFlipper>(uri, 0, 21, "ViewFlipper");
    qmlRegisterType<QUniAndroidViewSwitcher>(uri, 0, 21, "ViewSwitcher");
}

QT_END_NAMESPACE

#include "qtqmlandroidwidgetplugin.moc"
