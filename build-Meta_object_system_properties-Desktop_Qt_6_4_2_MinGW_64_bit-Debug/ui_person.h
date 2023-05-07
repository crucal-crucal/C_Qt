/********************************************************************************
** Form generated from reading UI file 'person.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSON_H
#define UI_PERSON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_Person
{
public:

    void setupUi(QDialog *Person)
    {
        if (Person->objectName().isEmpty())
            Person->setObjectName("Person");
        Person->resize(400, 300);

        retranslateUi(Person);

        QMetaObject::connectSlotsByName(Person);
    } // setupUi

    void retranslateUi(QDialog *Person)
    {
        Person->setWindowTitle(QCoreApplication::translate("Person", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Person: public Ui_Person {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSON_H
