#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtMainWindow.h"

class QtMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QtMainWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtMainWindowClass ui;

private slots:
	void on_action_Open_triggered();
	void on_action_Save_triggered();
	void on_action_SaveAs_triggered();
	void on_action_Close_triggered();

private:
	QString filePath_;
};
