#pragma once
#include <QObject>
#include <QPointF>
class QTimer;
#include "GenericPCTPackHandler.h"

#define BLANK_WINDOW_WIDTH 10
#define DEFAULT_DATA_SIZE 1000

#define AXIS_MIN_X 0
#define AXIS_MAX_Y 1000
#define AXIS_MIN_Y -1000
class DynamicTaskModel  : public QObject
{
	Q_OBJECT
private:
	enum class DynamicTaskType;
public:
	DynamicTaskModel(QObject *parent=nullptr);
	~DynamicTaskModel();
	void setDynamicTaskType(DynamicTaskType);

signals:
	void dynamicTaskBegin();
	void transmitLineSeriesData(const QVector<QPointF>&);
	void transmitScatterSeriesData(const QPointF&);
	void toDeleteTimer();
	void updateMaxX(int);
	void updateYRange(qreal,qreal);
public slots:
	void onSetTimerInterval(int interval);
	void onTimerStrat();
	void onTimerStop();
	void onUpdatePCTData(GenericPCTPackHandler::PCTPackValueID, qreal);
	void onResetDataBackup();
	void onSaveDataBackup();
private:
	enum class DynamicTaskType
	{
		DefaultTask,
		SerialPortTask,
	};
	void initData();
	void initDataBackup();
	void dynamicTask();
	void onDynamicTaskBegin();
	void dynamicTaskDeafault();
	void autoUpdateYRange();
	void saveDataBackupToTxt();
	DynamicTaskType task_type{ DynamicTaskType::DefaultTask };
	QTimer* timer{};
	QVector<QPointF> data{};
	QVector<QPointF> data_backup{};
	struct YRange
	{
		qreal max_Yvalue{ 0 };
		qreal min_Yvalue{ 0 };
	};
	YRange m_YRange{ AXIS_MIN_Y , AXIS_MAX_Y };
	int update_value_index{ 0 };
};
