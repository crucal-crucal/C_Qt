﻿#include "mainwidget.hpp"

MainWidget::MainWidget(QWidget* parent): QMainWindow(parent) {
	createCtrl();
	customLayout();
	initConnection();
	initData();
	resize(800, 600);
}

MainWidget::~MainWidget() = default;

void MainWidget::createCtrl() {
	m_pCenterWidget = new QWidget(this);
	m_pListWidget = new QListWidget(this);
	m_pListWidget->setFixedWidth(200);

	m_pAppBarSettingsEditor = new CUVAppBarSettingsEditor(this);
	m_pAutoCompleteSettingsEditor = new CUVAutoCompleteSettingsEditor(this);
	m_pAvatarSettingsEditor = new CUVAvatarSettingsEditor(this);

	m_pHBoxLayout = new QHBoxLayout;
	m_pStackedLayout = new QStackedLayout;

	setCentralWidget(m_pCenterWidget);
	m_pCenterWidget->setLayout(m_pHBoxLayout);
}

void MainWidget::customLayout() const {
	m_pHBoxLayout->addWidget(m_pListWidget);
	m_pHBoxLayout->addLayout(m_pStackedLayout);

	m_pStackedLayout->addWidget(m_pAppBarSettingsEditor);
	m_pStackedLayout->addWidget(m_pAutoCompleteSettingsEditor);
	m_pStackedLayout->addWidget(m_pAvatarSettingsEditor);
}

void MainWidget::initConnection() {
	connect(m_pListWidget, &QListWidget::currentItemChanged, this, [=](const QListWidgetItem* current, const QListWidgetItem* previous) {
		Q_UNUSED(current)
		Q_UNUSED(previous);
		m_pStackedLayout->setCurrentIndex(m_pListWidget->currentRow());
	});
}

void MainWidget::initData() const {
	m_pListWidget->addItem("App Bar");
	m_pListWidget->addItem("Auto Complete");
	m_pListWidget->addItem("Avatar");
	m_pListWidget->addItem("Badge");
	m_pListWidget->addItem("Checkbox");
	m_pListWidget->addItem("Circular Progress");
	m_pListWidget->addItem("Dialog");
	m_pListWidget->addItem("Drawer");
	m_pListWidget->addItem("Floating Action Button");
	m_pListWidget->addItem("Flat Button");
	m_pListWidget->addItem("Icon Button");
	m_pListWidget->addItem("Menu");
	m_pListWidget->addItem("Progress");
	m_pListWidget->addItem("Radio Button");
	m_pListWidget->addItem("Raised Button");
	m_pListWidget->addItem("ScrollBar");
	m_pListWidget->addItem("Slider");
	m_pListWidget->addItem("Snackbar");
	m_pListWidget->addItem("Tabs");
	m_pListWidget->addItem("Text Field");
	m_pListWidget->addItem("Toggle");

	m_pListWidget->setCurrentRow(0);
}