#include "Graffiti.h"

Graffiti::Graffiti(QWidget *parent)
	: QMainWindow(parent)
{
	isValidInputFilePath = false;
	isValidOutputFilePath = false;
	isVaildTestPicturePath = false;

	ui.setupUi(this);
	ui.modeComboBox->addItem("SSIM_CPU");
	ui.modeComboBox->addItem("PSNR_Color_CPU");
	ui.modeComboBox->setCurrentIndex(1);

	ui.drawModeComboBox->addItem("line");
	ui.drawModeComboBox->addItem("point");
	ui.drawModeComboBox->addItem("arc");
	ui.drawModeComboBox->setCurrentIndex(2);

	ui.showTestPictureLabel->hide();
	ui.graffitiFileLabel->hide();
	ui.outputTextBrowser->document()->setMaximumBlockCount(100);

	validPalette.setColor(QPalette::ColorGroup::All, QPalette::ColorRole::Foreground, Qt::GlobalColor::green);
	invalidPalette.setColor(QPalette::ColorGroup::All, QPalette::ColorRole::Foreground, Qt::GlobalColor::red);

	connect(ui.inputFilePathToolButton, SIGNAL(clicked()), this, SLOT(selectPicture()));
	connect(ui.inputFilePathLineEdit, SIGNAL(textChanged(QString)), this, SLOT(checkInputFilePath(QString)));
	connect(ui.outputFilePathToolButton, SIGNAL(clicked()), this, SLOT(selectOutputFilePath()));
	connect(ui.outputFilePathLineEdit, SIGNAL(textChanged(QString)), this, SLOT(checkOutputFilePath(QString)));
	connect(ui.startPushButton, SIGNAL(clicked()), this, SLOT(startGraffiti()));
	connect(ui.terminatePushButton, SIGNAL(clicked()), this, SLOT(terminateGraffiti()));
	connect(&workerThreadController, SIGNAL(saveGraffitiToMain(QImage)), this, SLOT(saveGraffiti(QImage)));
	connect(ui.stopPushButton, SIGNAL(clicked()), this, SLOT(stopGraffiti()));

	connect(ui.testPicturePathLineEdit, SIGNAL(textChanged(QString)), this, SLOT(checkTestPicturePath(QString)));
	connect(ui.testPicturePathToolButton, SIGNAL(clicked()), this, SLOT(selectTestPicture()));
	connect(ui.pixelRadiusDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(checkAlgorithmTestCondition()));
	connect(ui.testStartPushButton, SIGNAL(clicked()), this, SLOT(startAlgorithmTest()));

	connect(&workerThreadController, SIGNAL(outputStringToMain(QString)), this, SLOT(outputString(QString)));
	connect(&workerThreadController, SIGNAL(reflashGraffitiFileToMain(QImage)), this, SLOT(reflashGraffitiFileLabel(QImage)));

	//vector<vector<double>> t;
	//getGaussianWeightMatrix(3, &t);
}

void Graffiti::selectPicture()
{
	QString filePath = QFileDialog::getOpenFileName(this, tr("Select a picture"), "", "Images (*.png *.xpm *.jpg)", Q_NULLPTR, QFileDialog::ReadOnly);
	if (filePath.isEmpty())
		return;	
	ui.inputFilePathLineEdit->setText(filePath);
	if (ui.outputFilePathLineEdit->text().isEmpty())
	{
		ui.outputFilePathLineEdit->setText(filePath.left(filePath.lastIndexOf('/')));
	}


	//checkInputFilePath();
}

void Graffiti::outputString(QString str)
{
	QString output = (QDateTime::currentDateTime().toString("hh:mm:ss.zzz :"));
	if (str.endsWith('\n'))
	{
		str.chop(1);
	}
	output.append(str);
	ui.outputTextBrowser->append(output);
	return;
}

void Graffiti::reflashGraffitiFileLabel(QImage in)
{
	ui.graffitiFileLabel->setPixmap(QPixmap::fromImage(in));
}

void Graffiti::closeEvent(QCloseEvent * e)
{
	if (workerThreadController.isRunning())
	{
		if (QMessageBox::Yes == QMessageBox::question(this, "Exit?", "make sure to Exit graffiti without save graffiti file?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
		{
			workerThreadController.stopGraffiti();
			e->accept();
		}
	}
	else
	{
		e->accept();
	}
}

void Graffiti::checkInputFilePath(QString filePath)
{
	ui.showPictureLabel->clear();

	if(inputFile.load(filePath) && pixmapInputFile.load(filePath))
	{
		ui.inputFilePathStatuLabel->setPalette(validPalette);
		ui.inputFilePathStatuLabel->setText(tr("valid file"));

		ui.showPictureLabel->setPixmap(pixmapInputFile);
		isValidInputFilePath = true;
		checkAlgorithmTestCondition();
		checkGraffitiCondition();
	}
	else
	{
		ui.inputFilePathStatuLabel->setPalette(invalidPalette);
		ui.inputFilePathStatuLabel->setText(tr("invalid file"));

		ui.showPictureLabel->setText(tr("please choose a picture"));
		isValidInputFilePath = false;
		ui.startPushButton->setEnabled(false);
		ui.testStartPushButton->setEnabled(false);
	}
}

void Graffiti::selectOutputFilePath()
{
	QString filePath = QFileDialog::getExistingDirectory(this, "select output file directory");
	ui.outputFilePathLineEdit->setText(filePath);
}

void Graffiti::checkOutputFilePath(QString filePath)
{
	QFileInfo fi(filePath);
	if (fi.isDir())
	{
		ui.outputFilePathStatuLabel->setPalette(validPalette);
		ui.outputFilePathStatuLabel->setText("valid directory");

		isValidOutputFilePath = true;
		checkGraffitiCondition();
	}
	else
	{
		ui.outputFilePathStatuLabel->setPalette(invalidPalette);
		ui.outputFilePathStatuLabel->setText("invalid directory");

		isValidOutputFilePath = false;
		ui.startPushButton->setEnabled(false);
	}
}

//检查涂鸦的条件是否全部满足
void Graffiti::checkGraffitiCondition()
{
	if (!isValidInputFilePath || !isValidOutputFilePath)
	{
		ui.startPushButton->setEnabled(false);
		return;
	}
	if (ui.pixelRadiusDoubleSpinBox->value() <= 0)
	{
		ui.startPushButton->setEnabled(false);
		return;
	}

	ui.startPushButton->setEnabled(true);
	return;
}

void Graffiti::startGraffiti()
{
	//界面设置
	ui.modeComboBox->setEnabled(false);
	ui.outputFilePathLineEdit->setEnabled(false);
	ui.outputFilePathToolButton->setEnabled(false);
	ui.testStartPushButton->setEnabled(false);
	ui.pixelRadiusDoubleSpinBox->setEnabled(false);
	ui.inputFilePathLineEdit->setEnabled(false);
	ui.inputFilePathToolButton->setEnabled(false);
	ui.startPushButton->setEnabled(false);
	ui.terminatePushButton->setEnabled(true);
	ui.stopPushButton->setEnabled(true);
	
	//获取参数设置

	//开启另外一个线程进行绘图	
	graffitiFile = inputFile;
	ui.graffitiFileLabel->show();

	QImage s= inputFile.convertToFormat(QImage::Format_ARGB32);

	workerThreadController.startGraffiti(s, ui.pixelRadiusDoubleSpinBox->value(), ui.modeComboBox->currentIndex(), ui.drawModeComboBox->currentIndex());;

}

void Graffiti::terminateGraffiti()
{
	if (QMessageBox::Yes == QMessageBox::question(this, "terminate?", "make sure to terminate graffiti?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
	{
		ui.modeComboBox->setEnabled(true);
		ui.outputFilePathLineEdit->setEnabled(true);
		ui.outputFilePathToolButton->setEnabled(true);
		ui.testStartPushButton->setEnabled(true);
		ui.pixelRadiusDoubleSpinBox->setEnabled(true);
		ui.inputFilePathLineEdit->setEnabled(true);
		ui.inputFilePathToolButton->setEnabled(true);
		ui.startPushButton->setEnabled(true);

		ui.stopPushButton->setEnabled(true);
		ui.terminatePushButton->setEnabled(false);
		workerThreadController.terminateGraffiti();
	}
}

void Graffiti::saveGraffiti(QImage s)
{
	QString pathwithName = ui.inputFilePathLineEdit->text();
	QString name = pathwithName.right(pathwithName.length() - pathwithName.lastIndexOf('/') - 1);
	name.insert(name.indexOf('.'), QDateTime::currentDateTime().toString("dd-HH-mm"));
	outputString(QString("save graffiti named \"%1\"").arg(name));
	QString save = ui.outputFilePathLineEdit->text() + '/' + name;
	s.save(save, 0, 100);
}

void Graffiti::stopGraffiti()
{
	ui.startPushButton->setEnabled(true);
	ui.terminatePushButton->setEnabled(false);
	ui.stopPushButton->setEnabled(false);

	workerThreadController.stopGraffiti();
}

void Graffiti::selectTestPicture()
{
	QString filePath = QFileDialog::getOpenFileName(this, tr("Select a picture"), "", "Images (*.png *.xpm *.jpg)", Q_NULLPTR, QFileDialog::ReadOnly);
	if (filePath.isEmpty())
		return;
	ui.testPicturePathLineEdit->setText(filePath);
}

void Graffiti::checkTestPicturePath(QString filePath)
{
	ui.showTestPictureLabel->clear();
	ui.showTestPictureLabel->hide();

	if (pixmapTestPicture.load(filePath) && testPicture.load(filePath))
	{
		ui.testPicturePathStatuLabel->setPalette(validPalette);
		ui.testPicturePathStatuLabel->setText(tr("valid file"));

		ui.showTestPictureLabel->show();
		ui.showTestPictureLabel->setPixmap(pixmapTestPicture);
		isVaildTestPicturePath = true;
		checkAlgorithmTestCondition();
	}
	else
	{
		ui.testPicturePathStatuLabel->setPalette(invalidPalette);
		ui.testPicturePathStatuLabel->setText(tr("invalid file"));

		ui.showTestPictureLabel->hide();
		isVaildTestPicturePath = false;
		ui.testStartPushButton->setEnabled(false);
	}

}

//开始测试
void Graffiti::startAlgorithmTest()
{
	switch (ui.modeComboBox->currentIndex())
	{
	case 0:
		//SSIM_CPU
		startSSIM_CPUTest();
		break;
	case 1:
		//PSRN_Color_CPU
		startPSNR_Color_CPUTest();
		break;
	default:
		break;
	}
}

//用于检查是否能够进行测试算法
void Graffiti::checkAlgorithmTestCondition()
{
	if (!isVaildTestPicturePath || !isValidInputFilePath)
	{
		ui.testStartPushButton->setEnabled(false);
		return;
	}
	if (ui.pixelRadiusDoubleSpinBox->value() <= 0)
	{
		ui.testStartPushButton->setEnabled(false);
		return;
	}

	ui.testStartPushButton->setEnabled(true);
	return;
}

void Graffiti::startPSNR_Color_CPUTest()
{
	//首先判断设备是大端还是小端，PC端大多是小端
	//颜色是0xAARRGGBB，则从低地址开始读，先读出来的是BB，然后GG，然后RR，然后AA
	QImage s1 = inputFile.convertToFormat(QImage::Format_ARGB32);
	QImage s2 = testPicture.convertToFormat(QImage::Format_ARGB32);
	if (inputFile.width() != testPicture.width() || inputFile.height() != testPicture.height())
	{
		outputString(QString("testPicture size does not match with inputFile"));
		return;
	}	
	double psnr = getPSNR_Color_CPU(s1.constBits(), s2.constBits(), s1.height(), s1.width());
	outputString(QString("the PSNR(color): %1").arg(psnr));
}

void Graffiti::startSSIM_CPUTest()
{
	QImage i1 = inputFile.convertToFormat(QImage::Format_Grayscale8);
	QImage i2 = testPicture.convertToFormat(QImage::Format_Grayscale8);

	if (i1.width() != i2.width() || i1.height() != i2.height())
	{
		outputString("tested image size does not match origin image\n");
		return;
	}

	outputString("start algorithm test");
	outputString("please wait");

	vector<vector<int>> s1, s2;
	s1.resize(i1.height());
	s2.resize(i2.height());
	uchar *l1, *l2;
	for (int y = 0; y < i1.height(); y++)
	{
		s1[y].resize(i1.width());
		s2[y].resize(i2.width());

		l1 = i1.scanLine(y);
		l2 = i2.scanLine(y);
		for (int x = 0; x < i1.width(); x++)
		{
			s1[y][x] = static_cast<int>(l1[x]);
			s2[y][x] = static_cast<int>(l2[x]);
		}
	}

	QString res = "the SSIM = ";
	res.append(QString::number(getSSIM_CPU(s1, s2, i1.height(), i1.width(), 8, ui.pixelRadiusDoubleSpinBox->value())));
	outputString(res);
}
