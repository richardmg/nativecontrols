#ifndef QTANDROIDCARDVIEW_P_H
#define QTANDROIDCARDVIEW_P_H

#include "qtandroidframelayout_p.h"

QT_BEGIN_NAMESPACE

class QtAndroidCardView : public QtAndroidFrameLayout
{
    Q_OBJECT

public:
    explicit QtAndroidCardView(QtAndroidView *parent = 0);

protected:
    QAndroidJniObject construct() Q_DECL_OVERRIDE;
    void inflate() Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

#endif // QTANDROIDCARDVIEW_P_H
