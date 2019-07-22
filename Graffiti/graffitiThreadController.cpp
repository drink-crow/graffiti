#include "graffitiThreadController.h"



graffitiThreadController::graffitiThreadController()
{
	worker = new graffitiWorker;
	worker->moveToThread(&workerThread);
	connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
	connect(this, &graffitiThreadController::startWorker, worker, &graffitiWorker::graffiti);
	connect(worker, SIGNAL(outputString(QString)), this, SLOT(outputString(QString)));
	connect(worker, SIGNAL(reflashGraffitiFile(QImage)), this, SLOT(reflashGraffitiFile(QImage)));
	//当线程中的类在运行函数还没结束的时候是不会响应别的信号的	
	//connect(this, &graffitiThreadController::terminateWorker, worker, &graffitiWorker::workerTerminate);
	connect(worker, SIGNAL(saveImage(QImage)), this, SLOT(saveGraffiti(QImage)));

	workerThread.start();
}


graffitiThreadController::~graffitiThreadController()
{
	workerThread.quit();
	workerThread.wait();
}

void graffitiThreadController::startGraffiti(GRAFFITISETTINGARG)
{
	emit startWorker(GRAFFITISETTING_EMIT_ARG);
}

void graffitiThreadController::terminateGraffiti()
{
	//emit terminateWorker();
	worker->workerTerminate();
}

void graffitiThreadController::reflashGraffitiFile(QImage in)
{
	emit reflashGraffitiFileToMain(in);
}

void graffitiThreadController::saveGraffiti(QImage s)
{
	emit saveGraffitiToMain(s);
}

void graffitiThreadController::stopGraffiti()
{
	worker->workerStop();
}

void graffitiThreadController::outputString(QString str)
{
	emit outputStringToMain(str);
}
