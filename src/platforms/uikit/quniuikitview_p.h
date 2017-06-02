/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native UIKit Controls module of the Qt Toolkit.
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

#ifndef QNATIVUIKITVIEW_P_H
#define QNATIVUIKITVIEW_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore>

#include <QtUniUIKitControls/private/quniuikitresponder_p.h>
#include <QtUniUIKitControls/private/quniuikitoptional_p.h>

QT_BEGIN_NAMESPACE

Q_FORWARD_DECLARE_OBJC_CLASS(UIView);
Q_FORWARD_DECLARE_OBJC_CLASS(QUniUIKitViewDelegate);

class QUniUIKitViewPrivate : public QUniUIKitResponderPrivate
{
public:
    explicit QUniUIKitViewPrivate(int version = QObjectPrivateVersion);
    virtual ~QUniUIKitViewPrivate();

    // Attributes to keep track of explicit
    // application assignments
    enum Attribute {
        MovedX			= 0x00000002,
        MovedY			= 0x00000004,
        ResizedWidth	= 0x00000008,
        ResizedHeight	= 0x00000010
    };
    Q_DECLARE_FLAGS(Attributes, Attribute)

    UIView *view() const;
    void addSubView(UIView *subView);
    void updateIntrinsicContentSize();

    void onFrameChangedCallback();
    void onEmitGeometryChangesLater();

    Q_DECLARE_PUBLIC(QUniUIKitView)

private:
    CGRect alignmentRect() const;
    void setAlignmentRect(CGRect rect);
    void updateGeometry(Attributes propertiesToUpdate);
    void initConnections();
    void emitGeometryChanges(Attributes emitFlags);

    void syncX();
    void syncY();
    void syncWidth();
    void syncHeight();
    void syncAlpha();
    void syncVisible();
    void syncBackgroundColor();
    void syncIntrinsicContentWidth();
    void syncIntrinsicContentHeight();

public:
    virtual void createNSObject() override;
    virtual void setNSObject(NSObject *nsObject) override;

    Attributes m_emitMaskToUseOnFrameChanged;
    Attributes m_delayedEmitMask;
    QUniUIKitViewDelegate *m_delegate;
    QUniUIKitFallibleOptional<qreal> m_x;
    QUniUIKitFallibleOptional<qreal> m_y;
    QUniUIKitFallibleOptional<qreal> m_width;
    QUniUIKitFallibleOptional<qreal> m_height;
    QUniUIKitOptional<qreal> m_intrinsicContentWidth;
    QUniUIKitOptional<qreal> m_intrinsicContentHeight;
    QUniUIKitOptional<bool> m_visible;
    QUniUIKitOptional<qreal> m_alpha;
    QUniUIKitOptional<QColor> m_backgroundColor;
};

QT_END_NAMESPACE

#endif //QNATIVUIKITVIEW_P_H
