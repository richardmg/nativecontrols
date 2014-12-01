#ifndef QTDROIDDRAWERLAYOUTPARAMS_P_H
#define QTDROIDDRAWERLAYOUTPARAMS_P_H

#include "qtdroidmarginlayoutparams_p.h"

QT_BEGIN_NAMESPACE

class QtDroidDrawerLayoutParams : public QtDroidMarginLayoutParams
{
    Q_OBJECT
    Q_PROPERTY(int gravity READ gravity WRITE setGravity NOTIFY gravityChanged) // TODO Gravity

public:
    explicit QtDroidDrawerLayoutParams(QtDroidView *view);

    int gravity() const;
    void setGravity(int gravity);

Q_SIGNALS:
    void gravityChanged();

protected:
    QAndroidJniObject construct() Q_DECL_OVERRIDE;
    void applyParams(QAndroidJniObject &params) Q_DECL_OVERRIDE;

private:
    int m_gravity;
};

QT_END_NAMESPACE

#endif // QTDROIDDRAWERLAYOUTPARAMS_P_H