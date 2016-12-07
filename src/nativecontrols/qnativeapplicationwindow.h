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

#ifndef QQUICKCONTROLS2NSVIEW_H
#define QQUICKCONTROLS2NSVIEW_H

#include <QtQml/qqmlparserstatus.h>

QT_BEGIN_NAMESPACE

class QQC2NSControl : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(bool pressed READ pressed WRITE setPressed FINAL)
    Q_PROPERTY(Type type READ type WRITE setType FINAL)
    Q_PROPERTY(State state READ state WRITE setState FINAL)
    Q_PROPERTY(BezelStyle bezelStyle READ bezelStyle WRITE setBezelStyle FINAL)
    Q_PROPERTY(QSizeF size READ size NOTIFY sizeChanged FINAL)
    Q_PROPERTY(QSizeF implicitSize READ implicitSize NOTIFY implicitSizeChanged FINAL)
    Q_PROPERTY(QRectF contentRect READ contentRect NOTIFY contentRectChanged FINAL)
    Q_PROPERTY(qreal preferredWidth READ preferredWidth WRITE setPreferredWidth FINAL)
    Q_PROPERTY(qreal preferredHeight READ preferredHeight WRITE setPreferredHeight FINAL)
    Q_PROPERTY(QQuickText *text READ text WRITE setText FINAL)
    Q_PROPERTY(QUrl url READ url NOTIFY urlChanged FINAL)

    Q_INTERFACES(QQmlParserStatus)

public:
    enum Type {
        Button,
        CheckBox,
        ComboBox,
    };

    enum BezelStyle {
        RoundedBezelStyle = NSRoundedBezelStyle,
        RegularBezelStyle = NSRegularSquareBezelStyle,
        TexturedRoundedBezelStyle = NSTexturedRoundedBezelStyle
    };

    enum State {
        On = NSOnState,
        Off = NSOffState,
        Mixed = NSMixedState
    };

    Q_ENUM(Type)
    Q_ENUM(BezelStyle)
    Q_ENUM(State)

    explicit QQC2NSControl(QQuickItem *parent = nullptr);
    explicit QQC2NSControl(const QString &imageProviderId);
    ~QQC2NSControl();

    Type type() const;
    void setType(Type type);

    State state() const;
    void setState(State state);

    BezelStyle bezelStyle() const;
    void setBezelStyle(BezelStyle bezelStyle);

    bool pressed() const;
    void setPressed(bool pressed);

    QQuickText *text() const;
    void setText(QQuickText *text);

    void setPreferredWidth(qreal preferredWidth);
    qreal preferredWidth() const;

    void setPreferredHeight(qreal preferredHeight);
    qreal preferredHeight() const;

    QSizeF size() const;
    QSizeF implicitSize() const;
    QRectF contentRect() const;
    QUrl url() const;

    QPixmap takeSnapshot();

    virtual void classBegin() override {};
    virtual void componentComplete() override;

Q_SIGNALS:
    void sizeChanged();
    void implicitSizeChanged();
    void contentRectChanged();
    void urlChanged();

private:
    Type m_type;
    State m_state;
    BezelStyle m_bezelStyle;
    bool m_pressed;
    QSizeF m_size;
    QSizeF m_implicitSize;
    QRectF m_contentRect;
    QSizeF m_preferredSize;
    QQuickText *m_text;
    QUrl m_url;
    NSControl *m_control;
    bool m_componentComplete;

    QString toImageProviderId();
    void fromImageProviderId(const QString &imageProviderId);

    void updateContentRect(const CGRect &cgRect, const QMargins &margins = QMargins());
    void updateContentRect(const QRectF &rect, const QMargins &margins = QMargins());
    void updateImplicitSize(const CGSize &implicitSize);
    void updateImplicitSize(const QSizeF &implicitSize);
    void updateSize(const CGSize &size);
    void updateSize(const QSizeF &size);
    void updateFont();
    void updateUrl();

    void update();
    void updateButton();
    void updateCheckBox();
    void updateComboBox();

    static NSButton *s_nsButton;
    static NSButton *s_nsCheckBox;
    static NSComboBox *s_nsComboBox;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQC2NSControl)

#endif // QQUICKCONTROLS2NSVIEW_H
