#pragma once
#include <qobject.h>
#include <QThread>
#include "graffitiWorker.h"
#include "graffitiSetting.h"

class graffitiThreadController :
	public QObject
{
	Q_OBJECT
public:
	graffitiThreadController();
	~graffitiThreadController();

	void startGraffiti(GRAFFITISETTINGARG);
	void terminateGraffiti();
	bool isRunning() { return worker->running(); }

public slots:
	void outputString(QString);
	void reflashGraffitiFile(QImage);
	void saveGraffiti(QImage);
	void stopGraffiti();

signals:
	void startWorker(GRAFFITISETTINGARG);
	//void terminateWorker();
	void outputStringToMain(QString);
	void reflashGraffitiFileToMain(QImage);
	void saveGraffitiToMain(QImage);

private:
	QThread workerThread;
	graffitiWorker *worker;
};

