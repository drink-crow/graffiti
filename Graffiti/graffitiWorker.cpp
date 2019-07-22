#include "graffitiWorker.h"



graffitiWorker::graffitiWorker()
{
}


graffitiWorker::~graffitiWorker()
{
	deleteAllowed(H);
	deleteAllowed(W);
	deleteAllowed(u);
	deleteAllowed(ndWidth);
	deleteAllowed(uAngle);
	deleteAllowed(udSize);
}

double graffitiWorker::getSSIM(QImage o1, QImage o2, double pixelRadius)
{
	QImage i1 = o1.convertToFormat(QImage::Format_Grayscale8);
	QImage i2 = o2.convertToFormat(QImage::Format_Grayscale8);

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

	return getSSIM_CPU(s1, s2, i1.height(), i1.width(), 8, pixelRadius);
}

void graffitiWorker::workerTerminate()
{
	isTerminate = true;
}

void graffitiWorker::initRandom(int height, int width)
{
	deleteAllowed(H);
	H = new uniform_int_distribution<int>(0, height);

	deleteAllowed(W);
	W = new uniform_int_distribution<int>(0, width);

	deleteAllowed(uAngle);
	uAngle = new uniform_int_distribution<int>(0, 5760);

	deleteAllowed(udSize);
	udSize = new uniform_int_distribution<int>(7, height);
}

void graffitiWorker::lineGraffiti()
{
	color = getRandColor();
	brush.setColor(color);
	penWidth = getRandPenWidth();
	pen.setWidth(penWidth);
	pen.setColor(color);
	p.begin(&drawFile1);
	p.setPen(pen);
	line = getRandLine();
	//qDebug() << "c=" << c << " w=" << penWidth << " l=" << l << endl;
	p.drawLine(line);
	p.end();
}

void graffitiWorker::pointGraffiti()
{
	point = getRandPoint();
	color = source.pixelColor(point);
	//c = getRandColor();
	brush.setColor(color);
	penWidth = getRandPenWidth();
	pen.setWidth(penWidth);
	pen.setColor(color);
	p.begin(&drawFile1);
	p.setPen(pen);
	//l = getRandLine(maxH, maxW);
	//p.drawLine(l);
	p.drawPoint(point);
	p.end();
}

void graffitiWorker::arcGraffiti()
{
	//rect = QRect(getRandPoint(),QSize(5,5));
	static uniform_int_distribution<int> aaa(0, 100);

	point = getRandPoint();
	int size = (*udSize)(e);
	rect = QRect(point, QSize(size, size));

	//color = getRandColor();
	color = source.pixelColor(point.x() + size * aaa(e) / 100, point.y() + size * aaa(e) / 100);
	penWidth = getRandPenWidth();
	pen.setColor(color);
	pen.setWidth(penWidth);
	p.begin(&drawFile1);
	p.setRenderHint(QPainter::HighQualityAntialiasing, true);
	p.setPen(pen);
	p.drawArc(rect, getRandAngle(), getRandAngle());
	p.end();
}

void graffitiWorker::centralPointGraffiti()
{

}

void graffitiWorker::graffiti(GRAFFITISETTINGARG)
{
	isRunning = true;
	if (isStop)
	{
		isStop = false;
	}
	else
	{
		emit outputString("start graffiti!");
		Rpixel = pixelRadius;
		source = s;
		drawFile = s;
		drawFile1 = s;
		drawFile.fill(Qt::GlobalColor::white);
		isTerminate = false;
		initRandom(s.height() - 1, s.width() - 1);
		brush.setStyle(Qt::SolidPattern);	
		drawFile1.fill(Qt::GlobalColor::black);
		pen.setCapStyle(Qt::RoundCap);

		//SSIM
		if (mode == 0)
		{
			criteria = &graffitiWorker::criteriaSSIM;
			getCriterion = &graffitiWorker::getCriterionSSIM;
			saveThisTimeGraffiti = &graffitiWorker::saveThisTimeGraffitiSSIM;
			output = &graffitiWorker::outputSSIM;
		}
		else if (mode == 1)
		{
			criteria = &graffitiWorker::criteriaPSNR;
			getCriterion = &graffitiWorker::getCriterionPSNR;
			saveThisTimeGraffiti = &graffitiWorker::saveThisTimeGraffitiPSNR;
			output = &graffitiWorker::outputPSNR;
		}
	}

	switch (drawMode)
	{
	case 0:
		drawFunc = &graffitiWorker::lineGraffiti;
		break;
	case 1:
		drawFunc = &graffitiWorker::pointGraffiti;
		break;
	case 2:
		drawFunc = &graffitiWorker::arcGraffiti;
		break;
	default:
		drawFunc = &graffitiWorker::arcGraffiti;
		break;
	}

	while ((this->*criteria)())
	{
		if (!lastSuccess)
		{
			drawFile1 = drawFile;
		}
		else
		{
			lastSuccess = false;
		}
		count++;
		(this->*drawFunc)();
		criterion1 = (this->*getCriterion)();
		if ((this->*saveThisTimeGraffiti)())
		{
			lastSuccess = true;
			criterion = criterion1;
			drawFile = drawFile1;
			reflashGraffitiFile(drawFile);
			(this->*output)();
		}

		//жуж╧
		if (isTerminate)
		{
			outputString(QString("graffiti terminate by user"));
			emit saveImage(drawFile);
			isRunning = false;
			return;
		}
		if (isStop)
		{
			outputString(QString("graffiti stop by user, click start button to recorer"));
			return;
		}
	}

	emit saveImage(drawFile);
	outputString(QString("count = %1 !").arg(count));
	outputString(QString("graffiti finish!"));
	isRunning = false;
}