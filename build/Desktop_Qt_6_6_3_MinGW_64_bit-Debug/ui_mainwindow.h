/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_URL;
    QAction *actionStart_Server;
    QAction *actionConnect_to_Server;
    QAction *actionCombinear;
    QAction *actionFilmovio;
    QAction *actionMyWatch;
    QAction *actionObit;
    QAction *actionPerstfic;
    QAction *actionVisualScript;
    QAction *actionWstartpage;
    QAction *action_Open_Directory;
    QAction *actOpenLocalFile;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QVideoWidget *videoDisplay;
    QHBoxLayout *horizontalLayout;
    QSlider *seekSlider;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelPosition;
    QLabel *labelDuration;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *buttonPlay;
    QPushButton *buttonPause;
    QPushButton *buttonStop;
    QPushButton *btnPlayList;
    QPushButton *buttonFullScreen;
    QLabel *label_2;
    QSlider *volumeSlider;
    QLabel *volumeLabel;
    QVBoxLayout *chatLayout;
    QVBoxLayout *participantsLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QCheckBox *muteButton;
    QListWidget *participantsWidget;
    QListWidget *chatWidget;
    QHBoxLayout *chatInputLayout;
    QLineEdit *chatInput;
    QPushButton *sendButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuConnect;
    QMenu *menuSettings;
    QMenu *menuChange_Theme;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(851, 563);
        actionOpen_URL = new QAction(MainWindow);
        actionOpen_URL->setObjectName("actionOpen_URL");
        actionStart_Server = new QAction(MainWindow);
        actionStart_Server->setObjectName("actionStart_Server");
        actionConnect_to_Server = new QAction(MainWindow);
        actionConnect_to_Server->setObjectName("actionConnect_to_Server");
        actionCombinear = new QAction(MainWindow);
        actionCombinear->setObjectName("actionCombinear");
        actionFilmovio = new QAction(MainWindow);
        actionFilmovio->setObjectName("actionFilmovio");
        actionMyWatch = new QAction(MainWindow);
        actionMyWatch->setObjectName("actionMyWatch");
        actionObit = new QAction(MainWindow);
        actionObit->setObjectName("actionObit");
        actionPerstfic = new QAction(MainWindow);
        actionPerstfic->setObjectName("actionPerstfic");
        actionVisualScript = new QAction(MainWindow);
        actionVisualScript->setObjectName("actionVisualScript");
        actionWstartpage = new QAction(MainWindow);
        actionWstartpage->setObjectName("actionWstartpage");
        action_Open_Directory = new QAction(MainWindow);
        action_Open_Directory->setObjectName("action_Open_Directory");
        action_Open_Directory->setMenuRole(QAction::MenuRole::NoRole);
        actOpenLocalFile = new QAction(MainWindow);
        actOpenLocalFile->setObjectName("actOpenLocalFile");
        actOpenLocalFile->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_5 = new QHBoxLayout(centralwidget);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        videoDisplay = new QVideoWidget(centralwidget);
        videoDisplay->setObjectName("videoDisplay");

        verticalLayout->addWidget(videoDisplay);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        seekSlider = new QSlider(centralwidget);
        seekSlider->setObjectName("seekSlider");
        seekSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(seekSlider);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        labelPosition = new QLabel(widget);
        labelPosition->setObjectName("labelPosition");

        horizontalLayout_4->addWidget(labelPosition);

        labelDuration = new QLabel(widget);
        labelDuration->setObjectName("labelDuration");

        horizontalLayout_4->addWidget(labelDuration);


        horizontalLayout->addWidget(widget);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        buttonPlay = new QPushButton(centralwidget);
        buttonPlay->setObjectName("buttonPlay");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonPlay->sizePolicy().hasHeightForWidth());
        buttonPlay->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(buttonPlay);

        buttonPause = new QPushButton(centralwidget);
        buttonPause->setObjectName("buttonPause");
        sizePolicy.setHeightForWidth(buttonPause->sizePolicy().hasHeightForWidth());
        buttonPause->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(buttonPause);

        buttonStop = new QPushButton(centralwidget);
        buttonStop->setObjectName("buttonStop");
        sizePolicy.setHeightForWidth(buttonStop->sizePolicy().hasHeightForWidth());
        buttonStop->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(buttonStop);

        btnPlayList = new QPushButton(centralwidget);
        btnPlayList->setObjectName("btnPlayList");

        horizontalLayout_2->addWidget(btnPlayList);

        buttonFullScreen = new QPushButton(centralwidget);
        buttonFullScreen->setObjectName("buttonFullScreen");

        horizontalLayout_2->addWidget(buttonFullScreen);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        volumeSlider = new QSlider(centralwidget);
        volumeSlider->setObjectName("volumeSlider");
        sizePolicy.setHeightForWidth(volumeSlider->sizePolicy().hasHeightForWidth());
        volumeSlider->setSizePolicy(sizePolicy);
        volumeSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_2->addWidget(volumeSlider);

        volumeLabel = new QLabel(centralwidget);
        volumeLabel->setObjectName("volumeLabel");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(volumeLabel->sizePolicy().hasHeightForWidth());
        volumeLabel->setSizePolicy(sizePolicy1);
        volumeLabel->setMinimumSize(QSize(30, 0));
        volumeLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_2->addWidget(volumeLabel);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 8);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);

        horizontalLayout_5->addLayout(verticalLayout);

        chatLayout = new QVBoxLayout();
        chatLayout->setObjectName("chatLayout");
        participantsLayout = new QVBoxLayout();
        participantsLayout->setObjectName("participantsLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        muteButton = new QCheckBox(centralwidget);
        muteButton->setObjectName("muteButton");

        horizontalLayout_3->addWidget(muteButton);


        participantsLayout->addLayout(horizontalLayout_3);

        participantsWidget = new QListWidget(centralwidget);
        participantsWidget->setObjectName("participantsWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(participantsWidget->sizePolicy().hasHeightForWidth());
        participantsWidget->setSizePolicy(sizePolicy2);
        participantsWidget->setMinimumSize(QSize(0, 200));
        participantsWidget->setMaximumSize(QSize(16777215, 200));

        participantsLayout->addWidget(participantsWidget);


        chatLayout->addLayout(participantsLayout);

        chatWidget = new QListWidget(centralwidget);
        chatWidget->setObjectName("chatWidget");

        chatLayout->addWidget(chatWidget);

        chatInputLayout = new QHBoxLayout();
        chatInputLayout->setObjectName("chatInputLayout");
        chatInput = new QLineEdit(centralwidget);
        chatInput->setObjectName("chatInput");

        chatInputLayout->addWidget(chatInput);

        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName("sendButton");
        sizePolicy.setHeightForWidth(sendButton->sizePolicy().hasHeightForWidth());
        sendButton->setSizePolicy(sizePolicy);

        chatInputLayout->addWidget(sendButton);


        chatLayout->addLayout(chatInputLayout);


        horizontalLayout_5->addLayout(chatLayout);

        horizontalLayout_5->setStretch(0, 3);
        horizontalLayout_5->setStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 851, 24));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuConnect = new QMenu(menubar);
        menuConnect->setObjectName("menuConnect");
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName("menuSettings");
        menuChange_Theme = new QMenu(menuSettings);
        menuChange_Theme->setObjectName("menuChange_Theme");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuConnect->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menuFile->addAction(actionOpen_URL);
        menuFile->addAction(actOpenLocalFile);
        menuFile->addAction(action_Open_Directory);
        menuConnect->addAction(actionStart_Server);
        menuConnect->addAction(actionConnect_to_Server);
        menuSettings->addAction(menuChange_Theme->menuAction());
        menuChange_Theme->addAction(actionCombinear);
        menuChange_Theme->addAction(actionFilmovio);
        menuChange_Theme->addAction(actionMyWatch);
        menuChange_Theme->addAction(actionObit);
        menuChange_Theme->addAction(actionPerstfic);
        menuChange_Theme->addAction(actionVisualScript);
        menuChange_Theme->addAction(actionWstartpage);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\220\214\346\255\245\350\247\206\351\242\221\346\222\255\346\224\276\345\231\250", nullptr));
        actionOpen_URL->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\347\275\221\347\273\234\351\223\276\346\216\245", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen_URL->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\351\223\276\346\216\245\346\210\226\346\234\254\345\234\260\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actionStart_Server->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250\346\234\215\345\212\241", nullptr));
        actionConnect_to_Server->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\346\234\215\345\212\241", nullptr));
        actionCombinear->setText(QCoreApplication::translate("MainWindow", "Combinear", nullptr));
        actionFilmovio->setText(QCoreApplication::translate("MainWindow", "Filmovio", nullptr));
        actionMyWatch->setText(QCoreApplication::translate("MainWindow", "MyWatch", nullptr));
        actionObit->setText(QCoreApplication::translate("MainWindow", "Obit", nullptr));
        actionPerstfic->setText(QCoreApplication::translate("MainWindow", "Perstfic", nullptr));
        actionVisualScript->setText(QCoreApplication::translate("MainWindow", "VisualScript", nullptr));
        actionWstartpage->setText(QCoreApplication::translate("MainWindow", "Wstartpage", nullptr));
        action_Open_Directory->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", nullptr));
        actOpenLocalFile->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\234\254\345\234\260\346\226\207\344\273\266", nullptr));
        labelPosition->setText(QString());
        labelDuration->setText(QString());
        buttonPlay->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276", nullptr));
        buttonPause->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        buttonStop->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        btnPlayList->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\345\210\227\350\241\250", nullptr));
        buttonFullScreen->setText(QCoreApplication::translate("MainWindow", "\345\205\250\345\261\217", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\351\237\263\351\207\217", nullptr));
        volumeLabel->setText(QCoreApplication::translate("MainWindow", " 10%", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\217\202\344\270\216\350\200\205:", nullptr));
        muteButton->setText(QCoreApplication::translate("MainWindow", "\351\272\246\345\205\213\351\243\216\351\235\231\351\237\263", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menuConnect->setTitle(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        menuChange_Theme->setTitle(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\344\270\273\351\242\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
