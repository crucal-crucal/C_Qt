//
// Created by crucal on 2024-03-17.
//
#pragma once

#include <QMainWindow>

class Q_DECL_EXPORT test : public QMainWindow {
	Q_OBJECT
  public:
	explicit test(QWidget *parent = nullptr);
	~test() override;
};
