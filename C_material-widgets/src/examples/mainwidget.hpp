#pragma once

#include <QListWidget>
#include <QMainWindow>
#include <QStackedLayout>

#include "uvappbarsettingseditor/uvappbarsettingseditor.hpp"
#include "uvautocompletesettingseditor/uvautocompletesettingseditor.hpp"
#include "uvavatarsettingseditor/uvavatarsettingseditor.hpp"

class MainWidget final : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWidget(QWidget* parent = nullptr);
	~MainWidget() override;

private:
	void createCtrl();
	void customLayout() const;
	void initConnection();
	void initData() const;

private:
	QWidget* m_pCenterWidget{ nullptr };
	QListWidget* m_pListWidget{ nullptr };

	QHBoxLayout* m_pHBoxLayout{ nullptr };
	QStackedLayout* m_pStackedLayout{ nullptr };

private:
	CUVAppBarSettingsEditor* m_pAppBarSettingsEditor{ nullptr };
	CUVAutoCompleteSettingsEditor* m_pAutoCompleteSettingsEditor{ nullptr };
	CUVAvatarSettingsEditor* m_pAvatarSettingsEditor{ nullptr };
};
