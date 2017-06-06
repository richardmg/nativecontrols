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

#ifndef QUNIUIKITBASE_P_H
#define QUNIUIKITBASE_P_H

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

#include <QtUniUIKitControls/private/quniuikitqmlbase_p.h>

typedef struct CGRect CGRect;

QT_BEGIN_NAMESPACE

class QUniBase;
class QUniUIKitBase;

class QUniUIKitBasePrivate : public QUniUIKitQmlBasePrivate
{
public:
    explicit QUniUIKitBasePrivate(int version = QObjectPrivateVersion);
    virtual ~QUniUIKitBasePrivate();

    NSObject *nsObject() const;
    inline bool isNSObjectCreated() { return bool(m_nsObject); }

    Q_DECLARE_PUBLIC(QUniUIKitBase)

protected:
    virtual void createNSObject() {}
    virtual void setNSObject(NSObject *nsObject);

private:
    NSObject *m_nsObject;
#ifdef QT_DEBUG
    bool m_createNSObjectRecursionGuard;
#endif
};

void qt_setAssociatedQObject(NSObject *nsObject, QObject *qObject);
QObject *qt_getAssociatedQObject(NSObject *nsObject);

// Can be used if the nsobject has an associated QObject
#define Q_Q_NSOBJECT2(CLASSNAME, OBJC_OBJECT) \
    CLASSNAME *q = static_cast<CLASSNAME *>(qt_getAssociatedQObject(OBJC_OBJECT)); \
    Q_ASSERT(q);

// Can be used if the nsobject has an associated QObject
#define Q_D_NSOBJECT2(CLASSNAME, OBJC_OBJECT) \
    CLASSNAME##Private *d; \
    { \
        Q_Q_NSOBJECT2(CLASSNAME, OBJC_OBJECT) \
        d = static_cast<CLASSNAME##Private *>(QObjectPrivate::get(q)); \
    }

// Can be used if the nsobject implements quniuikitview_nsobject_p.h.
// Should be a bit more optimizing than using Q_Q_NSOBJECT2 directly.
#define Q_Q_NSOBJECT(CLASSNAME) \
    CLASSNAME *q; \
    if (self.q) { \
        q = static_cast<CLASSNAME *>(self.q); \
    } else { \
        q = static_cast<CLASSNAME *>(qt_getAssociatedQObject(self)); \
        Q_ASSERT(q); \
        self.q = q; \
    }

// Can be used if the nsobject implements quniuikitview_nsobject_p.h.
// Should be a bit more optimizing than using Q_D_NSOBJECT2 directly.
#define Q_D_NSOBJECT(CLASSNAME) \
    CLASSNAME##Private *d; \
    if (self.q) { \
        d = static_cast<CLASSNAME##Private *>(QObjectPrivate::get(self.q)); \
    } else { \
        self.q = static_cast<CLASSNAME *>(qt_getAssociatedQObject(self)); \
        Q_ASSERT(self.q); \
        d = static_cast<CLASSNAME##Private *>(QObjectPrivate::get(self.q)); \
    }

QT_END_NAMESPACE

#endif //QUNIUIKITBASE_P_H
