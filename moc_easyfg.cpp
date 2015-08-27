/****************************************************************************
** Meta object code from reading C++ file 'easyfg.h'
**
** Created: Fri Feb 4 20:52:06 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "easyfg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'easyfg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyScene[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      22,    8,    8,    8, 0x05,
      37,    8,    8,    8, 0x05,
      53,    8,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_MyScene[] = {
    "MyScene\0\0mouseMoved()\0mousePressed()\0"
    "mouseReleased()\0mouseLeft()\0"
};

const QMetaObject MyScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_MyScene,
      qt_meta_data_MyScene, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyScene::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyScene))
        return static_cast<void*>(const_cast< MyScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int MyScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mouseMoved(); break;
        case 1: mousePressed(); break;
        case 2: mouseReleased(); break;
        case 3: mouseLeft(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MyScene::mouseMoved()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MyScene::mousePressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MyScene::mouseReleased()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MyScene::mouseLeft()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      57,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      27,   11,   11,   11, 0x08,
      42,   11,   11,   11, 0x08,
      55,   11,   11,   11, 0x08,
      68,   11,   11,   11, 0x08,
      81,   11,   11,   11, 0x08,
      94,   11,   11,   11, 0x08,
     111,   11,   11,   11, 0x08,
     124,   11,   11,   11, 0x08,
     141,   11,   11,   11, 0x08,
     162,   11,   11,   11, 0x08,
     180,   11,   11,   11, 0x08,
     193,   11,   11,   11, 0x08,
     206,   11,   11,   11, 0x08,
     219,   11,   11,   11, 0x08,
     232,   11,   11,   11, 0x08,
     245,   11,   11,   11, 0x08,
     258,   11,   11,   11, 0x08,
     271,   11,   11,   11, 0x08,
     284,   11,   11,   11, 0x08,
     297,   11,   11,   11, 0x08,
     310,   11,   11,   11, 0x08,
     323,   11,   11,   11, 0x08,
     336,   11,   11,   11, 0x08,
     349,   11,   11,   11, 0x08,
     362,   11,   11,   11, 0x08,
     375,   11,   11,   11, 0x08,
     399,   11,   11,   11, 0x08,
     423,   11,   11,   11, 0x08,
     450,   11,   11,   11, 0x08,
     474,   11,   11,   11, 0x08,
     513,   11,   11,   11, 0x08,
     545,   11,   11,   11, 0x08,
     577,   11,   11,   11, 0x08,
     606,   11,   11,   11, 0x08,
     633,   11,   11,   11, 0x08,
     676,   11,   11,   11, 0x08,
     714,   11,   11,   11, 0x08,
     749,   11,   11,   11, 0x08,
     777,   11,   11,   11, 0x08,
     805,   11,   11,   11, 0x08,
     833,   11,   11,   11, 0x08,
     858,   11,   11,   11, 0x08,
     883,   11,   11,   11, 0x08,
     911,   11,   11,   11, 0x08,
     939,   11,   11,   11, 0x08,
     967,   11,   11,   11, 0x08,
     999,   11,   11,   11, 0x08,
    1031,   11,   11,   11, 0x08,
    1062,   11,   11,   11, 0x08,
    1107,   11,   11,   11, 0x08,
    1150,   11,   11,   11, 0x08,
    1181,   11,   11,   11, 0x08,
    1201,   11,   11,   11, 0x08,
    1223,   11,   11,   11, 0x08,
    1246,   11,   11,   11, 0x08,
    1263,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0Shortcut_F11()\0Shortcut_ESC()\0"
    "Shortcut_P()\0Shortcut_I()\0Shortcut_X()\0"
    "Shortcut_Y()\0Shortcut_CtrlA()\0"
    "Shortcut_B()\0Shortcut_equal()\0"
    "Shortcut_substract()\0Shortcut_divide()\0"
    "Shortcut_R()\0Shortcut_A()\0Shortcut_C()\0"
    "Shortcut_M()\0Shortcut_0()\0Shortcut_1()\0"
    "Shortcut_2()\0Shortcut_3()\0Shortcut_4()\0"
    "Shortcut_5()\0Shortcut_6()\0Shortcut_7()\0"
    "Shortcut_8()\0Shortcut_9()\0Shortcut_o()\0"
    "on_openButton_clicked()\0on_backButton_clicked()\0"
    "on_forwardButton_clicked()\0"
    "on_saveButton_clicked()\0"
    "on_scaleComboBox_currentIndexChanged()\0"
    "on_offsetSpinBox_valueChanged()\0"
    "on_cutoffSpinBox_valueChanged()\0"
    "on_referenceButton_clicked()\0"
    "on_currentButton_clicked()\0"
    "on_referenceComboBox_currentIndexChanged()\0"
    "on_pseudocolorCheckBox_stateChanged()\0"
    "on_invertedCheckBox_stateChanged()\0"
    "on_XCheckBox_stateChanged()\0"
    "on_X1SpinBox_valueChanged()\0"
    "on_X2SpinBox_valueChanged()\0"
    "on_XCopyButton_clicked()\0"
    "on_YCopyButton_clicked()\0"
    "on_YCheckBox_stateChanged()\0"
    "on_Y1SpinBox_valueChanged()\0"
    "on_Y2SpinBox_valueChanged()\0"
    "on_xshiftSpinBox_valueChanged()\0"
    "on_yshiftSpinBox_valueChanged()\0"
    "on_beamCheckBox_stateChanged()\0"
    "on_graphicsView_customContextMenuRequested()\0"
    "on_scaleLabel_customContextMenuRequested()\0"
    "on_hideSidebarButton_clicked()\0"
    "mouseMovedOnScene()\0mousePressedOnScene()\0"
    "mouseReleasedOnScene()\0mouseLeftScene()\0"
    "CopyFigure()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Ui::MainWindowClass"))
        return static_cast< Ui::MainWindowClass*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Shortcut_F11(); break;
        case 1: Shortcut_ESC(); break;
        case 2: Shortcut_P(); break;
        case 3: Shortcut_I(); break;
        case 4: Shortcut_X(); break;
        case 5: Shortcut_Y(); break;
        case 6: Shortcut_CtrlA(); break;
        case 7: Shortcut_B(); break;
        case 8: Shortcut_equal(); break;
        case 9: Shortcut_substract(); break;
        case 10: Shortcut_divide(); break;
        case 11: Shortcut_R(); break;
        case 12: Shortcut_A(); break;
        case 13: Shortcut_C(); break;
        case 14: Shortcut_M(); break;
        case 15: Shortcut_0(); break;
        case 16: Shortcut_1(); break;
        case 17: Shortcut_2(); break;
        case 18: Shortcut_3(); break;
        case 19: Shortcut_4(); break;
        case 20: Shortcut_5(); break;
        case 21: Shortcut_6(); break;
        case 22: Shortcut_7(); break;
        case 23: Shortcut_8(); break;
        case 24: Shortcut_9(); break;
        case 25: Shortcut_o(); break;
        case 26: on_openButton_clicked(); break;
        case 27: on_backButton_clicked(); break;
        case 28: on_forwardButton_clicked(); break;
        case 29: on_saveButton_clicked(); break;
        case 30: on_scaleComboBox_currentIndexChanged(); break;
        case 31: on_offsetSpinBox_valueChanged(); break;
        case 32: on_cutoffSpinBox_valueChanged(); break;
        case 33: on_referenceButton_clicked(); break;
        case 34: on_currentButton_clicked(); break;
        case 35: on_referenceComboBox_currentIndexChanged(); break;
        case 36: on_pseudocolorCheckBox_stateChanged(); break;
        case 37: on_invertedCheckBox_stateChanged(); break;
        case 38: on_XCheckBox_stateChanged(); break;
        case 39: on_X1SpinBox_valueChanged(); break;
        case 40: on_X2SpinBox_valueChanged(); break;
        case 41: on_XCopyButton_clicked(); break;
        case 42: on_YCopyButton_clicked(); break;
        case 43: on_YCheckBox_stateChanged(); break;
        case 44: on_Y1SpinBox_valueChanged(); break;
        case 45: on_Y2SpinBox_valueChanged(); break;
        case 46: on_xshiftSpinBox_valueChanged(); break;
        case 47: on_yshiftSpinBox_valueChanged(); break;
        case 48: on_beamCheckBox_stateChanged(); break;
        case 49: on_graphicsView_customContextMenuRequested(); break;
        case 50: on_scaleLabel_customContextMenuRequested(); break;
        case 51: on_hideSidebarButton_clicked(); break;
        case 52: mouseMovedOnScene(); break;
        case 53: mousePressedOnScene(); break;
        case 54: mouseReleasedOnScene(); break;
        case 55: mouseLeftScene(); break;
        case 56: CopyFigure(); break;
        default: ;
        }
        _id -= 57;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
