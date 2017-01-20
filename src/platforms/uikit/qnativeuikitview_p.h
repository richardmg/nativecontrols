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

#include <QtNativeUIKitControls/private/qnativeuikitbase_p.h>

QT_BEGIN_NAMESPACE

class QNativeUIKitView;
Q_FORWARD_DECLARE_OBJC_CLASS(UIView);

class QNativeUIKitViewPrivate : public QNativeUIKitBasePrivate
{
public:
    explicit QNativeUIKitViewPrivate(int version = QObjectPrivateVersion);
    virtual ~QNativeUIKitViewPrivate();

    UIView *view();
    UIView *view() const;
    void setView(UIView *view);

    CGRect alignmentRect() const;
    void setAlignmentRect(CGRect rect);
    void setGeometry(const QRectF &rect);

    virtual void connectSignals(QNativeBase *base) override;
    virtual void updateLayout(bool recursive);

    void updateImplicitSize();

    Q_DECLARE_PUBLIC(QNativeUIKitView)

protected:
    enum Attribute {
        LayedOut		= 0x00000001,
        Moved			= 0x00000002,
        Resized			= 0x00000004
    };

    uint m_attributes;

    inline void setAttribute(Attribute attribute, bool on = true)
    {
        m_attributes = on ? m_attributes |= attribute : m_attributes &= ~attribute;
    }

    inline bool testAttribute(Attribute attribute)
    {
        return bool(m_attributes & attribute);
    }

private:
    UIView *m_view;
    QSizeF m_implicitSize;
};

QT_END_NAMESPACE

#endif //QNATIVUIKITVIEW_P_H