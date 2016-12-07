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

#include <AppKit/AppKit.h>

#include <QtGui/qpixmap.h>
#include <QtGui/qpainter.h>

#include <QtGui/private/qcoregraphics_p.h>
#include <QtQml/private/qqmlcomponentattached_p.h>

#include "qqc2nscontrol.h"

QT_BEGIN_NAMESPACE

static const int kNoSizeLimit = 0;

NSButton *QQC2NSControl::s_nsButton = 0;
NSButton *QQC2NSControl::s_nsCheckBox = 0;
NSComboBox *QQC2NSControl::s_nsComboBox = 0;

static const QChar separator(QLatin1Char(','));

QQC2NSControl::QQC2NSControl(QQuickItem *parent)
    : QObject(parent)
    , m_type(Button)
    , m_state(Off)
    , m_bezelStyle(RoundedBezelStyle)
    , m_pressed(false)
    , m_size(QSizeF())
    , m_implicitSize(QSize())
    , m_contentRect(QRectF())
    , m_preferredSize(QSizeF(-1, -1))
    , m_text(nullptr)
    , m_url(QUrl())
    , m_control(nullptr)
    , m_componentComplete(false)
{
}

QQC2NSControl::QQC2NSControl(const QString &imageProviderId)
    : QQC2NSControl(0)
{
    fromImageProviderId(imageProviderId);
    m_componentComplete = true;
    update();
}

QQC2NSControl::~QQC2NSControl()
{
}

void QQC2NSControl::componentComplete()
{
    // componentComplete is called when the object is ready to be populated. But
    // we want to wait calling update until all the properies have been assigned.
    // So henve we need this "work-around"
    QQmlComponentAttached *att = qobject_cast<QQmlComponentAttached *>(qmlAttachedPropertiesObject<QQmlComponent>(this, true));
    connect(att, &QQmlComponentAttached::completed, [=]() {
        m_componentComplete = true;
        update();
    });
}

QString QQC2NSControl::toImageProviderId()
{
    return QString::number(int(m_type))
            + separator + QString::number(int(m_state))
            + separator + QString::number(int(m_pressed))
            + separator + QString::number(m_bezelStyle);
}

void QQC2NSControl::fromImageProviderId(const QString &imageProviderId)
{
    int i = 0;
    QStringList args = imageProviderId.split(separator);

    m_type = Type(args[i++].toInt());
    m_state = State(args[i++].toInt());
    m_pressed = bool(args[i++].toInt());
    m_bezelStyle = BezelStyle(args[i++].toInt());
}

QQC2NSControl::Type QQC2NSControl::type() const
{
   return m_type;
}

void QQC2NSControl::setType(QQC2NSControl::Type type)
{
    if (m_type == type)
        return;

   m_type = type;
   update();
}

QQC2NSControl::State QQC2NSControl::state() const
{
   return m_state;
}

void QQC2NSControl::setState(QQC2NSControl::State state)
{
    if (m_state == state)
        return;

   m_state = state;
   update();
}

QQC2NSControl::BezelStyle QQC2NSControl::bezelStyle() const
{
    return m_bezelStyle;
}

void QQC2NSControl::setBezelStyle(QQC2NSControl::BezelStyle bezelStyle)
{
    if (m_bezelStyle == bezelStyle)
        return;

   m_bezelStyle = bezelStyle;
   update();
}

bool QQC2NSControl::pressed() const
{
    return m_pressed;
}

void QQC2NSControl::setPressed(bool pressed)
{
    if (m_pressed == pressed)
        return;

    m_pressed = pressed;
    update();
}

QQuickText *QQC2NSControl::text() const
{
   return m_text;
}

void QQC2NSControl::setText(QQuickText *text)
{
    if (m_text == text)
        return;

   m_text = text;
   update();
}

void QQC2NSControl::setPreferredWidth(qreal preferredWidth)
{
    // m_preferredWidth and m_preferredHeight are, together with
    // m_text, used to calculate implicitSize.
    if (m_preferredSize.width() == preferredWidth)
        return;

   m_preferredSize.setWidth(preferredWidth);
   update();
}

qreal QQC2NSControl::preferredWidth() const
{
    return m_preferredSize.width();
}

void QQC2NSControl::setPreferredHeight(qreal preferredHeight)
{
    // m_preferredWidth and m_preferredHeight are, together with
    // m_text, used to calculate implicitSize.
    if (m_preferredSize.height() == preferredHeight)
        return;

   m_preferredSize.setHeight(preferredHeight);
   update();
}

qreal QQC2NSControl::preferredHeight() const
{
    return m_preferredSize.height();
}

QSizeF QQC2NSControl::size() const
{
    return m_size;
}

QSizeF QQC2NSControl::implicitSize() const
{
    return m_implicitSize;
}

QRectF QQC2NSControl::contentRect() const
{
    return m_contentRect;
}

QUrl QQC2NSControl::url() const
{
    return m_url;
}

QPixmap QQC2NSControl::takeSnapshot()
{
    // m_control points to a shared control, so ensure to call update
    // first, or take takeSnapshot directly after construction.
    QPixmap pixmap(QSizeF::fromCGSize(m_control.bounds.size).toSize());
    pixmap.fill(Qt::transparent);
    QMacCGContext ctx(&pixmap);

    m_control.wantsLayer = YES;
    [m_control.layer drawInContext:ctx];

    return pixmap;
}

void QQC2NSControl::updateContentRect(const CGRect &cgRect, const QMargins &margins)
{
    updateContentRect(QRectF::fromCGRect(cgRect), margins);
}

void QQC2NSControl::updateContentRect(const QRectF &rect, const QMargins &margins)
{
    QRectF rectWithMargins = rect.adjusted(margins.left(), margins.top(), margins.right(), margins.bottom());

    if (rectWithMargins == m_contentRect)
        return;

    m_contentRect = rectWithMargins;
    emit contentRectChanged();
}

void QQC2NSControl::updateSize(const CGSize &size)
{
   updateSize(QSizeF::fromCGSize(size));
}

void QQC2NSControl::updateSize(const QSizeF &size)
{
    if (size == m_size)
        return;

    m_size = size;
    emit sizeChanged();
}

void QQC2NSControl::updateImplicitSize(const CGSize &size)
{
   updateImplicitSize(QSizeF::fromCGSize(size));
}

void QQC2NSControl::updateImplicitSize(const QSizeF &implicitSize)
{
    if (implicitSize == m_implicitSize)
        return;

    m_implicitSize = implicitSize;
    emit implicitSizeChanged();
}

void QQC2NSControl::updateFont()
{
    if (!m_text)
        return;

    NSString *family = m_text->font().family().toNSString();
    int pointSize = m_text->font().pointSize();
    m_control.font = [NSFont fontWithName:family size:pointSize];
}

void QQC2NSControl::updateUrl()
{
    QUrl url(QStringLiteral("image://nscontrol/") + toImageProviderId());

    if (url == m_url)
        return;

    m_url = url;
    emit urlChanged();
}

void QQC2NSControl::update()
{
    if (!m_componentComplete)
        return;

    switch(m_type) {
    case Button:
        updateButton();
        break;
    case CheckBox:
        updateCheckBox();
        break;
    case ComboBox:
        updateComboBox();
        break;
    default:
        Q_UNREACHABLE();
    }

    updateUrl();
}

void QQC2NSControl::updateButton()
{
    if (!s_nsButton)
        s_nsButton = [[NSButton alloc] initWithFrame:NSZeroRect];
    m_control = s_nsButton;

    s_nsButton.buttonType = NSMomentaryPushInButton;
    updateFont();
    s_nsButton.title = m_text ? m_text->text().toNSString() : @"";
    s_nsButton.highlighted = m_pressed;
    s_nsButton.bezelStyle = NSBezelStyle(m_bezelStyle);

    [m_control sizeToFit];
    CGRect bounds = m_control.bounds;
    updateImplicitSize(bounds.size);
    if (m_preferredSize.width() >= 0)
        bounds.size.width = m_preferredSize.width();
    updateSize(bounds.size);
    updateContentRect(bounds, QMargins(0, 0, 0, 0));
}

void QQC2NSControl::updateCheckBox()
{
    if (!s_nsCheckBox)
        s_nsCheckBox = [[NSButton alloc] initWithFrame:NSZeroRect];
    m_control = s_nsCheckBox;

    s_nsCheckBox.buttonType = NSSwitchButton;
    s_nsCheckBox.title = @"";
    s_nsCheckBox.highlighted = m_pressed;
    s_nsCheckBox.bezelStyle = NSBezelStyle(m_bezelStyle);
    s_nsCheckBox.state = m_state;

    [m_control sizeToFit];
    CGRect bounds = m_control.bounds;
    updateImplicitSize(bounds.size);
    updateSize(bounds.size);
    updateContentRect(QRectF(bounds.size.width, 0, kNoSizeLimit, bounds.size.height));
}

void QQC2NSControl::updateComboBox()
{
    if (!s_nsComboBox) {
        // [NSControl sizeToFit] fails and calculates a too small rect. So we need
        // some manual adjustments to get the correct height, while at the same
        // time, ensure that the combo is wide enough to not truncate the button on the right.
        s_nsComboBox = [[NSComboBox alloc] initWithFrame:NSMakeRect(0, 0, 70, 30)];
        NSSize size = [s_nsComboBox sizeThatFits:NSMakeSize(70, 30)];
        s_nsComboBox.bounds = NSMakeRect(0, 0, 70, size.height);
    }
    m_control = s_nsComboBox;

    s_nsComboBox.highlighted = m_pressed;

    CGRect bounds = m_control.bounds;
    updateImplicitSize(bounds.size);
    bounds.size.width = qMax(bounds.size.width, m_preferredSize.width());
    updateSize(bounds.size);
    updateContentRect(bounds, QMargins(0, 0, -30, 0));
}

#include "moc_qqc2nscontrol.cpp"

QT_END_NAMESPACE
