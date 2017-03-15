OTHER_FILES += \
    $$PWD/src/org/qtproject/qt5/android/bindings/app/QtUniActivity.java \
    $$PWD/src/org/qtproject/qt5/android/bindings/app/QtUniService.java \
    $$PWD/src/org/qtproject/qt5/android/bindings/view/QtUniMenu.java \
    $$PWD/src/org/qtproject/qt5/android/bindings/view/QtUniMenuItem.java \
    $$PWD/src/org/qtproject/qt5/android/bindings/view/QtUniViewListener.java \
    $$PWD/src/org/qtproject/qt5/android/bindings/widget/QtUniCompoundButtonListener.java \
    $$PWD/src/org/qtproject/qt5/android/bindings/widget/QtUniNumberPickerListener.java \
    $$PWD/src/org/qtproject/qt5/android/bindings/widget/QtUniRadioGroupListener.java \
    $$PWD/src/org/qtproject/qt5/android/bindings/widget/QtUniRatingBarListener.java \
    $$PWD/src/org/qtproject/qt5/android/bindings/widget/QtUniScrollView.java \
    $$PWD/src/org/qtproject/qt5/android/bindings/widget/QtUniSeekBarListener.java \
    $$PWD/src/org/qtproject/qt5/android/bindings/widget/QtUniTabHostListener.java \
    $$PWD/support/v4/widget/QtUniSwipeRefreshLayoutListener.java \
    $$PWD/support/v7/widget/QtUniRecyclerAdapter.java

java.files = $$PWD/src $$PWD/support
java.path = $$[QT_INSTALL_PREFIX]/src/android/java
!prefix_build: COPIES += java
INSTALLS += java
