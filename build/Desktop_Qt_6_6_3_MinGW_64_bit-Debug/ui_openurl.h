/********************************************************************************
** Form generated from reading UI file 'openurl.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENURL_H
#define UI_OPENURL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_openURL
{
public:
    QLabel *label;
    QLineEdit *urlInput;
    QDialogButtonBox *openURLbuttonBox;

    void setupUi(QDialog *openURL)
    {
        if (openURL->objectName().isEmpty())
            openURL->setObjectName("openURL");
        openURL->resize(400, 109);
        label = new QLabel(openURL);
        label->setObjectName("label");
        label->setGeometry(QRect(11, 11, 74, 20));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        urlInput = new QLineEdit(openURL);
        urlInput->setObjectName("urlInput");
        urlInput->setGeometry(QRect(11, 38, 371, 24));
        openURLbuttonBox = new QDialogButtonBox(openURL);
        openURLbuttonBox->setObjectName("openURLbuttonBox");
        openURLbuttonBox->setGeometry(QRect(180, 70, 193, 29));
        openURLbuttonBox->setOrientation(Qt::Orientation::Horizontal);
        openURLbuttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        retranslateUi(openURL);
        QObject::connect(openURLbuttonBox, &QDialogButtonBox::accepted, openURL, qOverload<>(&QDialog::accept));
        QObject::connect(openURLbuttonBox, &QDialogButtonBox::rejected, openURL, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(openURL);
    } // setupUi

    void retranslateUi(QDialog *openURL)
    {
        openURL->setWindowTitle(QCoreApplication::translate("openURL", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("openURL", "\350\276\223\345\205\245URL:", nullptr));
        urlInput->setText(QCoreApplication::translate("openURL", "https://sf1-cdn-tos.huoshanstatic.com/obj/media-fe/xgplayer_doc_video/mp4/xgplayer-demo-360p.mp4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class openURL: public Ui_openURL {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENURL_H
