#pragma once
#include <qobject.h>
#include <QPainter>
#include <QPicture>
#include <QDebug>

#include <iostream>
#include <random>

#include "graffitiSetting.h"
#include "pictureCompare.h"
class graffitiWorker :
	public QObject
{
	Q_OBJECT
public:
	graffitiWorker();
	~graffitiWorker();

	double getSSIM(QImage s1, QImage s2, double pixelRadius);
	QColor getRandColor() { return QColor((*u)(e), (*u)(e), (*u)(e)); }
	QLine getRandLine() { return QLine((*W)(e), (*H)(e), (*W)(e), (*H)(e)); }
	int getRandPenWidth() { return abs((int)ceil((*ndWidth)(e))); }
	QPoint getRandPoint() { return QPoint((*W)(e), (*H)(e)); };
	int getRandAngle() { return (*uAngle)(e); }
	QRect getRandRectangle() { int s = (*udSize)(e);  return QRect(getRandPoint(), QSize(s, s)); }

	void deleteAllowed(void *p) { if (p != nullptr)delete p; }
	bool running() { return isRunning; }

public slots:
	void graffiti(GRAFFITISETTINGARG);
	void workerTerminate();
	void workerStop() { isStop = true; }

private:
	double Rpixel = 0.0;

	double criterion;
	double criterion1;
	bool isTerminate = false;
	bool isStop = false;
	bool isRunning = false;

	//随机数
	default_random_engine e;
	int maxH, maxW;
	uniform_int_distribution<int> *H = nullptr;
	uniform_int_distribution<int> *W = nullptr;
	uniform_int_distribution<int> *u = new uniform_int_distribution<int>(0, 255);
	normal_distribution<double> *ndWidth = new normal_distribution<double>(8, 3);
	uniform_int_distribution<int> *udSize = nullptr;
	uniform_int_distribution<int> *uAngle = nullptr;

	//初始化，重置随机数
	void initRandom(int height,int width);

	//绘图用类
	QImage source;
	QImage drawFile;
	QImage drawFile1;
	bool lastSuccess = false;
	QColor color;
	int penWidth;
	QLine line;
	QPoint point;
	QBrush brush;
	QPen pen;
	QPainter p;
	QRectF rect;
	long long count = 0;

	//指向不同绘图风格
	void (graffitiWorker::*drawFunc)();
	void lineGraffiti();
	void pointGraffiti();
	void arcGraffiti();
	void centralPointGraffiti();

	//指向不同判据
	bool (graffitiWorker::*criteria)();
	bool criteriaSSIM() { return criterion < 0.8; }
	bool criteriaPSNR() { return criterion < 55; }
	//获取不同的判据
	double (graffitiWorker::*getCriterion)();
	double getCriterionSSIM() { return getSSIM(source, drawFile1, Rpixel); }
	double getCriterionPSNR() { return getPSNR_Color_CPU(source.constBits(), drawFile1.constBits(), source.height(), source.width()); }
	//比较是否更接近原图
	bool (graffitiWorker::*saveThisTimeGraffiti)();
	bool saveThisTimeGraffitiSSIM() { return criterion1 > criterion; }
	bool saveThisTimeGraffitiPSNR() { return criterion1 > criterion; }
	//不同的输出
	void (graffitiWorker::*output)();
	void outputSSIM() { outputString(QString("the SSIM= %1").arg(criterion1)); }
	void outputPSNR() { outputString(QString("the PSNR(Color)= %1").arg(criterion1)); }

signals:
	void outputString(QString);
	void reflashGraffitiFile(QImage);
	void saveImage(QImage);
};

