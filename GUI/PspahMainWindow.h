#pragma once
#include <QWidget>
class QWidget;
class QHBoxLayout;
class QVBoxLayout;

class SerialPortSettingsWidget;
class PspahSetWidget;
class SerialPortInfoWidget;
class PspahWaveSetWidget;

class PCTPackDistributor;
#define MIN_WIDTH 950
#define MIN_HEIGHT 600

class PspahMainWindow : public QWidget
{
	Q_OBJECT
public:
	PspahMainWindow(QWidget* parent = nullptr);
	~PspahMainWindow() override;
protected:
	void resizeEvent(QResizeEvent* event) override;
private:
	void initMainLayout();
	void initSignals();
	void initRightLayout();
	void initLeftLayout();
	void transferSerialInfoWidget();
	void initPCTPackDistributor();
	void initSerialPortDistributorSignal();
	QHBoxLayout* main_layout{};
	QVBoxLayout* central_left_layout{};
	QHBoxLayout* left_bottom_layout{};
	PspahWaveSetWidget* pspah_wave_set_widget{};
	SerialPortInfoWidget* serial_port_info_widget{};
	SerialPortSettingsWidget* serial_port_settings_widget{};

	QVBoxLayout* central_right_layout{};
	PspahSetWidget* pasph_set_widget{};
	bool MainLayoutFlag{ true };

	QWidget* central_widget{};

	QThread* PCTPackDistributor_hread{};
	PCTPackDistributor* pct_pack_distributor{};
};

