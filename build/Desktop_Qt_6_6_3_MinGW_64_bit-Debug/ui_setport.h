/********************************************************************************
** Form generated from reading UI file 'setport.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETPORT_H
#define UI_SETPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SetPort
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *portInput;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *userNameInput;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SetPort)
    {
        if (SetPort->objectName().isEmpty())
            SetPort->setObjectName("SetPort");
        SetPort->resize(400, 122);
        verticalLayout = new QVBoxLayout(SetPort);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(SetPort);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        portInput = new QLineEdit(SetPort);
        portInput->setObjectName("portInput");

        horizontalLayout_2->addWidget(portInput);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(SetPort);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        userNameInput = new QLineEdit(SetPort);
        userNameInput->setObjectName("userNameInput");

        horizontalLayout->addWidget(userNameInput);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(SetPort);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SetPort);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, SetPort, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, SetPort, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(SetPort);
    } // setupUi

    void retranslateUi(QDialog *SetPort)
    {
        SetPort->setWindowTitle(QCoreApplication::translate("SetPort", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SetPort", "\347\233\221\345\220\254\347\253\257\345\217\243:", nullptr));
        portInput->setText(QCoreApplication::translate("SetPort", "1234", nullptr));
        label_2->setText(QCoreApplication::translate("SetPort", "\347\224\250\346\210\267\345\220\215:", nullptr));
        userNameInput->setText(QCoreApplication::translate("SetPort", "server", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetPort: public Ui_SetPort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPORT_H
