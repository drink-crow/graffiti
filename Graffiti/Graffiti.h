#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QDateTime>
#include <QMessageBox>
#include <QCloseEvent>
#include "pictureCompare.h"
#include "graffitiThreadController.h"
#include "graffitiSetting.h"
#include "ui_Graffiti.h"

class Graffiti : public QMainWindow
{
	Q_OBJECT

public:
	Graffiti(QWidget *parent = Q_NULLPTR);

public slots:
	void selectPicture();
	void checkInputFilePath(QString);
	void selectOutputFilePath();
	void checkOutputFilePath(QString);
	void checkGraffitiCondition();
	void startGraffiti();
	void terminateGraffiti();
	void saveGraffiti(QImage);
	void stopGraffiti();

	//”√”⁄≤‚ ‘µƒ≤€
	void selectTestPicture();
	void checkTestPicturePath(QString);
	void startAlgorithmTest();
	void checkAlgorithmTestCondition();

	void startPSNR_Color_CPUTest();
	void startSSIM_CPUTest();

	void outputString(QString);
	void reflashGraffitiFileLabel(QImage);

protected:
	void closeEvent(QCloseEvent *event);

private:
	Ui::GraffitiClass ui;

	QPalette validPalette;
	QPalette invalidPalette;

	QImage inputFile;
	QPixmap pixmapInputFile;
	bool isValidInputFilePath;
	bool isValidOutputFilePath;

	QImage testPicture;
	QPixmap pixmapTestPicture;
	bool isVaildTestPicturePath;

	QImage graffitiFile;
	graffitiThreadController workerThreadController;
};


