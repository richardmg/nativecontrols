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

#ifndef QUNIUIKITSEARCHFIELD_H
#define QUNIUIKITSEARCHFIELD_H

#include <QtUniUIKitControls/quniuikitcontrol.h>

QT_BEGIN_NAMESPACE

class QUniUIKitSearchFieldPrivate;
Q_FORWARD_DECLARE_OBJC_CLASS(UISearchBar);

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitSearchField : public QUniUIKitControl
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText NOTIFY placeholderTextChanged)

public:
    QUniUIKitSearchField(QUniUIKitBase *parent = nullptr);
    QUniUIKitSearchField(const QString &text, QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitSearchField();

    UISearchBar *uiSearchBarHandle();

    QString text();
    void setText(const QString &text);

    QString placeholderText();
    void setPlaceholderText(const QString &placeholderText);

Q_SIGNALS:
    void textChanged(const QString &text);
    void placeholderTextChanged(const QString &placeholderText);

protected:
    QUniUIKitSearchField(QUniUIKitSearchFieldPrivate &dd, QUniUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniUIKitSearchField)
    Q_DISABLE_COPY(QUniUIKitSearchField)
};

QT_END_NAMESPACE
#endif // QUNIUIKITSEARCHFIELD_H
