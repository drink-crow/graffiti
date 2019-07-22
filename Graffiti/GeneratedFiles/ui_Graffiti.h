/********************************************************************************
** Form generated from reading UI file 'Graffiti.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAFFITI_H
#define UI_GRAFFITI_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraffitiClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *centralWidgetHorizontalLayout;
    QVBoxLayout *toolbarVerticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *groupBoxVerticalLayout;
    QLabel *inputFilePathLabel;
    QHBoxLayout *inputFilePathBoxLayout;
    QLineEdit *inputFilePathLineEdit;
    QToolButton *inputFilePathToolButton;
    QLabel *inputFilePathStatuLabel;
    QFrame *line;
    QLabel *testCompareAlgorithmLabel;
    QLabel *testPictureLabel;
    QHBoxLayout *textPIctureHorizontalLayout;
    QLineEdit *testPicturePathLineEdit;
    QToolButton *testPicturePathToolButton;
    QLabel *testPicturePathStatuLabel;
    QLabel *criterionLabel;
    QComboBox *modeComboBox;
    QHBoxLayout *pixelRadiusHorizontalLayout;
    QLabel *pixelRadiusLabel;
    QDoubleSpinBox *pixelRadiusDoubleSpinBox;
    QHBoxLayout *testHorizontalLayout;
    QPushButton *testStartPushButton;
    QLabel *drawModeLabel;
    QComboBox *drawModeComboBox;
    QFrame *line_2;
    QLabel *outputFilePathLabel;
    QHBoxLayout *outputFilePathHBoxLayout;
    QLineEdit *outputFilePathLineEdit;
    QToolButton *outputFilePathToolButton;
    QLabel *outputFilePathStatuLabel;
    QHBoxLayout *controlHorizontalLayout;
    QPushButton *startPushButton;
    QPushButton *stopPushButton;
    QPushButton *terminatePushButton;
    QTextBrowser *outputTextBrowser;
    QLabel *showPictureLabel;
    QLabel *showTestPictureLabel;
    QLabel *graffitiFileLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GraffitiClass)
    {
        if (GraffitiClass->objectName().isEmpty())
            GraffitiClass->setObjectName(QStringLiteral("GraffitiClass"));
        GraffitiClass->resize(580, 592);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GraffitiClass->sizePolicy().hasHeightForWidth());
        GraffitiClass->setSizePolicy(sizePolicy);
        GraffitiClass->setMaximumSize(QSize(1920, 1080));
        GraffitiClass->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        centralWidget = new QWidget(GraffitiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidgetHorizontalLayout = new QHBoxLayout(centralWidget);
        centralWidgetHorizontalLayout->setSpacing(6);
        centralWidgetHorizontalLayout->setContentsMargins(11, 11, 11, 11);
        centralWidgetHorizontalLayout->setObjectName(QStringLiteral("centralWidgetHorizontalLayout"));
        toolbarVerticalLayout = new QVBoxLayout();
        toolbarVerticalLayout->setSpacing(6);
        toolbarVerticalLayout->setObjectName(QStringLiteral("toolbarVerticalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(350, 0));
        groupBoxVerticalLayout = new QVBoxLayout(groupBox);
        groupBoxVerticalLayout->setSpacing(6);
        groupBoxVerticalLayout->setContentsMargins(11, 11, 11, 11);
        groupBoxVerticalLayout->setObjectName(QStringLiteral("groupBoxVerticalLayout"));
        inputFilePathLabel = new QLabel(groupBox);
        inputFilePathLabel->setObjectName(QStringLiteral("inputFilePathLabel"));

        groupBoxVerticalLayout->addWidget(inputFilePathLabel);

        inputFilePathBoxLayout = new QHBoxLayout();
        inputFilePathBoxLayout->setSpacing(6);
        inputFilePathBoxLayout->setObjectName(QStringLiteral("inputFilePathBoxLayout"));
        inputFilePathLineEdit = new QLineEdit(groupBox);
        inputFilePathLineEdit->setObjectName(QStringLiteral("inputFilePathLineEdit"));
        inputFilePathLineEdit->setInputMethodHints(Qt::ImhUrlCharactersOnly);

        inputFilePathBoxLayout->addWidget(inputFilePathLineEdit);

        inputFilePathToolButton = new QToolButton(groupBox);
        inputFilePathToolButton->setObjectName(QStringLiteral("inputFilePathToolButton"));

        inputFilePathBoxLayout->addWidget(inputFilePathToolButton);


        groupBoxVerticalLayout->addLayout(inputFilePathBoxLayout);

        inputFilePathStatuLabel = new QLabel(groupBox);
        inputFilePathStatuLabel->setObjectName(QStringLiteral("inputFilePathStatuLabel"));
        QFont font;
        font.setFamily(QStringLiteral("Cambria"));
        font.setItalic(true);
        inputFilePathStatuLabel->setFont(font);

        groupBoxVerticalLayout->addWidget(inputFilePathStatuLabel);

        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        groupBoxVerticalLayout->addWidget(line);

        testCompareAlgorithmLabel = new QLabel(groupBox);
        testCompareAlgorithmLabel->setObjectName(QStringLiteral("testCompareAlgorithmLabel"));

        groupBoxVerticalLayout->addWidget(testCompareAlgorithmLabel);

        testPictureLabel = new QLabel(groupBox);
        testPictureLabel->setObjectName(QStringLiteral("testPictureLabel"));

        groupBoxVerticalLayout->addWidget(testPictureLabel);

        textPIctureHorizontalLayout = new QHBoxLayout();
        textPIctureHorizontalLayout->setSpacing(6);
        textPIctureHorizontalLayout->setObjectName(QStringLiteral("textPIctureHorizontalLayout"));
        testPicturePathLineEdit = new QLineEdit(groupBox);
        testPicturePathLineEdit->setObjectName(QStringLiteral("testPicturePathLineEdit"));

        textPIctureHorizontalLayout->addWidget(testPicturePathLineEdit);

        testPicturePathToolButton = new QToolButton(groupBox);
        testPicturePathToolButton->setObjectName(QStringLiteral("testPicturePathToolButton"));

        textPIctureHorizontalLayout->addWidget(testPicturePathToolButton);


        groupBoxVerticalLayout->addLayout(textPIctureHorizontalLayout);

        testPicturePathStatuLabel = new QLabel(groupBox);
        testPicturePathStatuLabel->setObjectName(QStringLiteral("testPicturePathStatuLabel"));
        QFont font1;
        font1.setFamily(QStringLiteral("Calibri"));
        font1.setItalic(true);
        testPicturePathStatuLabel->setFont(font1);

        groupBoxVerticalLayout->addWidget(testPicturePathStatuLabel);

        criterionLabel = new QLabel(groupBox);
        criterionLabel->setObjectName(QStringLiteral("criterionLabel"));

        groupBoxVerticalLayout->addWidget(criterionLabel);

        modeComboBox = new QComboBox(groupBox);
        modeComboBox->setObjectName(QStringLiteral("modeComboBox"));
        modeComboBox->setInputMethodHints(Qt::ImhNone);
        modeComboBox->setEditable(false);

        groupBoxVerticalLayout->addWidget(modeComboBox);

        pixelRadiusHorizontalLayout = new QHBoxLayout();
        pixelRadiusHorizontalLayout->setSpacing(6);
        pixelRadiusHorizontalLayout->setObjectName(QStringLiteral("pixelRadiusHorizontalLayout"));
        pixelRadiusLabel = new QLabel(groupBox);
        pixelRadiusLabel->setObjectName(QStringLiteral("pixelRadiusLabel"));

        pixelRadiusHorizontalLayout->addWidget(pixelRadiusLabel);

        pixelRadiusDoubleSpinBox = new QDoubleSpinBox(groupBox);
        pixelRadiusDoubleSpinBox->setObjectName(QStringLiteral("pixelRadiusDoubleSpinBox"));
        pixelRadiusDoubleSpinBox->setDecimals(6);
        pixelRadiusDoubleSpinBox->setMinimum(0.001);
        pixelRadiusDoubleSpinBox->setMaximum(100);
        pixelRadiusDoubleSpinBox->setValue(10);

        pixelRadiusHorizontalLayout->addWidget(pixelRadiusDoubleSpinBox);


        groupBoxVerticalLayout->addLayout(pixelRadiusHorizontalLayout);

        testHorizontalLayout = new QHBoxLayout();
        testHorizontalLayout->setSpacing(6);
        testHorizontalLayout->setObjectName(QStringLiteral("testHorizontalLayout"));
        testStartPushButton = new QPushButton(groupBox);
        testStartPushButton->setObjectName(QStringLiteral("testStartPushButton"));
        testStartPushButton->setEnabled(false);

        testHorizontalLayout->addWidget(testStartPushButton);


        groupBoxVerticalLayout->addLayout(testHorizontalLayout);

        drawModeLabel = new QLabel(groupBox);
        drawModeLabel->setObjectName(QStringLiteral("drawModeLabel"));

        groupBoxVerticalLayout->addWidget(drawModeLabel);

        drawModeComboBox = new QComboBox(groupBox);
        drawModeComboBox->setObjectName(QStringLiteral("drawModeComboBox"));

        groupBoxVerticalLayout->addWidget(drawModeComboBox);

        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        groupBoxVerticalLayout->addWidget(line_2);

        outputFilePathLabel = new QLabel(groupBox);
        outputFilePathLabel->setObjectName(QStringLiteral("outputFilePathLabel"));

        groupBoxVerticalLayout->addWidget(outputFilePathLabel);

        outputFilePathHBoxLayout = new QHBoxLayout();
        outputFilePathHBoxLayout->setSpacing(6);
        outputFilePathHBoxLayout->setObjectName(QStringLiteral("outputFilePathHBoxLayout"));
        outputFilePathLineEdit = new QLineEdit(groupBox);
        outputFilePathLineEdit->setObjectName(QStringLiteral("outputFilePathLineEdit"));
        outputFilePathLineEdit->setInputMethodHints(Qt::ImhUrlCharactersOnly);

        outputFilePathHBoxLayout->addWidget(outputFilePathLineEdit);

        outputFilePathToolButton = new QToolButton(groupBox);
        outputFilePathToolButton->setObjectName(QStringLiteral("outputFilePathToolButton"));

        outputFilePathHBoxLayout->addWidget(outputFilePathToolButton);


        groupBoxVerticalLayout->addLayout(outputFilePathHBoxLayout);

        outputFilePathStatuLabel = new QLabel(groupBox);
        outputFilePathStatuLabel->setObjectName(QStringLiteral("outputFilePathStatuLabel"));
        outputFilePathStatuLabel->setFont(font1);

        groupBoxVerticalLayout->addWidget(outputFilePathStatuLabel);


        toolbarVerticalLayout->addWidget(groupBox);

        controlHorizontalLayout = new QHBoxLayout();
        controlHorizontalLayout->setSpacing(6);
        controlHorizontalLayout->setObjectName(QStringLiteral("controlHorizontalLayout"));
        startPushButton = new QPushButton(centralWidget);
        startPushButton->setObjectName(QStringLiteral("startPushButton"));
        startPushButton->setEnabled(false);

        controlHorizontalLayout->addWidget(startPushButton);

        stopPushButton = new QPushButton(centralWidget);
        stopPushButton->setObjectName(QStringLiteral("stopPushButton"));
        stopPushButton->setEnabled(false);

        controlHorizontalLayout->addWidget(stopPushButton);

        terminatePushButton = new QPushButton(centralWidget);
        terminatePushButton->setObjectName(QStringLiteral("terminatePushButton"));
        terminatePushButton->setEnabled(false);

        controlHorizontalLayout->addWidget(terminatePushButton);


        toolbarVerticalLayout->addLayout(controlHorizontalLayout);

        outputTextBrowser = new QTextBrowser(centralWidget);
        outputTextBrowser->setObjectName(QStringLiteral("outputTextBrowser"));

        toolbarVerticalLayout->addWidget(outputTextBrowser);


        centralWidgetHorizontalLayout->addLayout(toolbarVerticalLayout);

        showPictureLabel = new QLabel(centralWidget);
        showPictureLabel->setObjectName(QStringLiteral("showPictureLabel"));
        showPictureLabel->setAlignment(Qt::AlignCenter);

        centralWidgetHorizontalLayout->addWidget(showPictureLabel);

        showTestPictureLabel = new QLabel(centralWidget);
        showTestPictureLabel->setObjectName(QStringLiteral("showTestPictureLabel"));

        centralWidgetHorizontalLayout->addWidget(showTestPictureLabel);

        graffitiFileLabel = new QLabel(centralWidget);
        graffitiFileLabel->setObjectName(QStringLiteral("graffitiFileLabel"));

        centralWidgetHorizontalLayout->addWidget(graffitiFileLabel);

        GraffitiClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GraffitiClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 580, 23));
        GraffitiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GraffitiClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GraffitiClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GraffitiClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GraffitiClass->setStatusBar(statusBar);

        retranslateUi(GraffitiClass);

        modeComboBox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(GraffitiClass);
    } // setupUi

    void retranslateUi(QMainWindow *GraffitiClass)
    {
        GraffitiClass->setWindowTitle(QApplication::translate("GraffitiClass", "Graffiti", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("GraffitiClass", "graffiti properties", Q_NULLPTR));
        inputFilePathLabel->setText(QApplication::translate("GraffitiClass", "in Picture path", Q_NULLPTR));
        inputFilePathToolButton->setText(QApplication::translate("GraffitiClass", "...", Q_NULLPTR));
        inputFilePathStatuLabel->setText(QApplication::translate("GraffitiClass", "invaild path!", Q_NULLPTR));
        testCompareAlgorithmLabel->setText(QApplication::translate("GraffitiClass", "test compare algorithm", Q_NULLPTR));
        testPictureLabel->setText(QApplication::translate("GraffitiClass", "test picture", Q_NULLPTR));
        testPicturePathToolButton->setText(QApplication::translate("GraffitiClass", "...", Q_NULLPTR));
        testPicturePathStatuLabel->setText(QApplication::translate("GraffitiClass", "invaild path!", Q_NULLPTR));
        criterionLabel->setText(QApplication::translate("GraffitiClass", "Criterion", Q_NULLPTR));
        modeComboBox->setCurrentText(QString());
        pixelRadiusLabel->setText(QApplication::translate("GraffitiClass", "pixelRadius", Q_NULLPTR));
        testStartPushButton->setText(QApplication::translate("GraffitiClass", "Start test", Q_NULLPTR));
        drawModeLabel->setText(QApplication::translate("GraffitiClass", "draw mode", Q_NULLPTR));
        outputFilePathLabel->setText(QApplication::translate("GraffitiClass", "out Graffiti path", Q_NULLPTR));
        outputFilePathToolButton->setText(QApplication::translate("GraffitiClass", "...", Q_NULLPTR));
        outputFilePathStatuLabel->setText(QApplication::translate("GraffitiClass", "invaild path!", Q_NULLPTR));
        startPushButton->setText(QApplication::translate("GraffitiClass", "Start", Q_NULLPTR));
        stopPushButton->setText(QApplication::translate("GraffitiClass", "Stop", Q_NULLPTR));
        terminatePushButton->setText(QApplication::translate("GraffitiClass", "Terminate", Q_NULLPTR));
        outputTextBrowser->setDocumentTitle(QApplication::translate("GraffitiClass", "output", Q_NULLPTR));
        showPictureLabel->setText(QApplication::translate("GraffitiClass", "no file", Q_NULLPTR));
        showTestPictureLabel->setText(QApplication::translate("GraffitiClass", "no test file", Q_NULLPTR));
        graffitiFileLabel->setText(QApplication::translate("GraffitiClass", "graffiti file", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GraffitiClass: public Ui_GraffitiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAFFITI_H
