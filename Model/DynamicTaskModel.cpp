#include "DynamicTaskModel.h"
#include "GenericPCTPackHandler.h"
#include "GUI/PspahChartView.h"
#include <QTimer>
#include <QDebug>
#include <QFileDialog>
#include <iostream>

DynamicTaskModel::DynamicTaskModel(QObject *parent)
	: QObject(parent)
{
    initData();
    connect(this, &DynamicTaskModel::dynamicTaskBegin, this, 
        &DynamicTaskModel::onDynamicTaskBegin);
    //qRegisterMetaType<QVector<QPointF>>("QList<QPointF>");
}

DynamicTaskModel::~DynamicTaskModel()
{
    emit toDeleteTimer();
    timer->deleteLater();
}

void DynamicTaskModel::setDynamicTaskType(DynamicTaskType d)
{
    task_type = d;
}

void DynamicTaskModel::onTimerStrat()
{
    timer->start();
}

void DynamicTaskModel::onTimerStop()
{
    timer->stop();
}

void DynamicTaskModel::onUpdatePCTData(GenericPCTPackHandler::PCTPackValueID ID, qreal value)
{
    if (ID == GenericPCTPackHandler::PCTPackValueID::WAVE_DATA)
    {
        if (timer->isActive()) {
            data[update_value_index] = QPointF(update_value_index, value);
            data_backup << QPointF(update_value_index, value);
            emit transmitLineSeriesData(data);
            emit transmitScatterSeriesData(data[update_value_index]);
        }
        ++update_value_index;
        //if (update_value_index == DEFAULT_DATA_SIZE- BLANK_WINDOW_WIDTH) {
        //    update_value_index = 0;
        //}
        if (update_value_index == DEFAULT_DATA_SIZE) {
            update_value_index = 0;
        }
    }
    else if (ID == GenericPCTPackHandler::PCTPackValueID::LEAD_STATUS)
    {
        if ((bool)value == true) {
            task_type = DynamicTaskType::SerialPortTask;
        }
        else {
            task_type = DynamicTaskType::DefaultTask;
        }
    }
}

void DynamicTaskModel::onResetDataBackup()
{
    initDataBackup();
}

void DynamicTaskModel::onSaveDataBackup()
{
    saveDataBackupToTxt();
}

void DynamicTaskModel::initData()
{
    data.clear();
 //   for (int i = BLANK_WINDOW_WIDTH; i < DEFAULT_DATA_SIZE; ++i) {
	//	data.append(QPointF(i, 0));
	//}
    for (int i = 0; i < DEFAULT_DATA_SIZE; ++i) {
        data.append(QPointF(i, 0));
    }
    update_value_index = 0;
    emit transmitLineSeriesData(data);
}

void DynamicTaskModel::initDataBackup()
{
    initData();
    data_backup.clear();
}

void DynamicTaskModel::onDynamicTaskBegin()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DynamicTaskModel::dynamicTask);
    timer->start(100);
}

void DynamicTaskModel::dynamicTask()
{
    timer->stop();
    //qDebug() << "DynamicTaskModel:" << objectName() << thread();
    switch (task_type) {
	case DynamicTaskType::DefaultTask:
        //qDebug() << "DefaultTask";
		dynamicTaskDeafault();
		break;
	case DynamicTaskType::SerialPortTask:
        //qDebug() << "SerialPortTask";
		break;
	default:
		break;
	}
    autoUpdateYRange();
    timer->start();
}

void DynamicTaskModel::onSetTimerInterval(int interval)
{
    timer->stop();
    timer->setInterval(interval);
    timer->start();
}

void DynamicTaskModel::dynamicTaskDeafault()
{
    data[update_value_index] = QPointF(update_value_index, 0);
    data_backup << QPointF(update_value_index, 0);
    ++update_value_index;
    if (update_value_index == DEFAULT_DATA_SIZE) {
        update_value_index = 0;
    }
    emit transmitLineSeriesData(data);
    emit transmitScatterSeriesData(data[update_value_index]);
}

void DynamicTaskModel::autoUpdateYRange()
{
    //qDebug() << "autoUpdateYRange";
    auto minmax = std::minmax_element(data.begin(), data.end(), [](const QPointF& a, const QPointF& b) {
        return a.y() < b.y();
        });
    if (minmax.first->y() == minmax.second->y())
    {
        m_YRange.min_Yvalue = AXIS_MIN_Y;
        m_YRange.max_Yvalue = AXIS_MAX_Y;
    }
    else
    {
        m_YRange.min_Yvalue = minmax.first->y();
        m_YRange.max_Yvalue = minmax.second->y();
    }
    //emit updateYRange(minValue-1000, maxValue+1000);
    emit updateYRange(m_YRange.min_Yvalue, m_YRange.max_Yvalue);
}

void DynamicTaskModel::saveDataBackupToTxt()
{
    // 获取当前时间并格式化为字符串，作为默认文件名
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
    QString defaultFileName = "data_" + currentTime + ".txt";
    // 弹出文件保存对话框
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save File", defaultFileName, "Text Files (*.txt)");

    if (!filePath.isEmpty()) {
        // 创建文件对象
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

            // 创建文本流
            QTextStream out(&file);
            // 写入数据到文本文件
            for (int i = 0; i < data_backup.size(); ++i) {
                out << data_backup[i].x() << " " << data_backup[i].y() << "\n";
            }
            // 关闭文件
            file.close();
            std::cout << "Data saved to file: " << filePath.toStdString() << std::endl;
        }
        else {
            std::cerr << "Failed to open file for writing!" << std::endl;
        }
    }
}
