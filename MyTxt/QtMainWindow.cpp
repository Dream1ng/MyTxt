#include "QtMainWindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QTextBlock>


QtMainWindow::QtMainWindow(QWidget *parent)
	: QMainWindow(parent)
	, filePath_()
{
	ui.setupUi(this);

	ui.rowCountLE->setText(tr("0"));
	ui.zHeightLE->setText("0");
}

void QtMainWindow::on_action_Open_triggered()
{
	on_action_Close_triggered();

	QString caption(tr("Open File"));
	QString dir(".");
	QString filter(tr("Text File(*.txt)"));
	auto path = QFileDialog::getOpenFileName(this, caption, dir, filter);

	if (path.isEmpty())
	{
		return;
	}

	QFile file(path);

	if (!file.open(QIODevice::OpenModeFlag::ExistingOnly | QIODevice::OpenModeFlag::ReadOnly
		| QIODevice::OpenModeFlag::Text))
	{
		QString title(tr("Open Failed"));
		QString text(tr("Open \"") + path + "\" failed!");
		QMessageBox::critical(this, title, text);
	}

	QTextStream in(&file);
	QString text = in.readAll();
	ui.textPTE->setPlainText(text);
	ui.rowCountLE->setText(QString::number(ui.textPTE->document()->lineCount()));

	file.close();

	filePath_ = path;
}

void QtMainWindow::on_action_Save_triggered()
{
	int rowCount = ui.rowCountLE->text().toInt();
	QString rowText;
	QString text;

	for (int i = 0; i < rowCount; ++i)
	{
		rowText = ui.textPTE->document()->findBlockByLineNumber(i).text() 
			 + " Z" + QString::number(ui.zHeightLE->text().toDouble() / 10 * (i + 1));

		if (i != rowCount - 1)
		{
			text = text + rowText + "\n";
		}
	}

	QFile file(filePath_);

	if (!file.open(QIODevice::OpenModeFlag::ExistingOnly | QIODevice::OpenModeFlag::WriteOnly
		| QIODevice::OpenModeFlag::Text))
	{
		QString title(tr("Save Failed"));
		QString text = (tr("Save \"") + filePath_ + "\" failed!");
		QMessageBox::critical(this, title, text);
	}
	
	QTextStream out(&file);
	out << text;
	file.close();

	QString title(tr("Save Successfully"));
	text = (tr("Save \"") + filePath_ + "\" Successfully!");
	QMessageBox::information(this, title, text);
}

void QtMainWindow::on_action_SaveAs_triggered()
{

	QString caption(tr("Save File"));
	QString dir(".");
	QString filter(tr("Text File(*.txt)"));
	auto path = QFileDialog::getSaveFileName(this, caption, dir, filter);

	if (path.isEmpty())
	{
		return;
	}

	int rowCount = ui.rowCountLE->text().toInt();
	QString rowText;
	QString text;

	for (int i = 0; i < rowCount; ++i)
	{
		rowText = ui.textPTE->document()->findBlockByLineNumber(i).text()
			+ " Z" + QString::number(ui.zHeightLE->text().toDouble() / 10 * (i + 1));

		if (i != rowCount - 1)
		{
			text = text + rowText + "\n";
		}
	}

	QFile file(path);

	if (!file.open(QIODevice::OpenModeFlag::ExistingOnly | QIODevice::OpenModeFlag::WriteOnly
		| QIODevice::OpenModeFlag::Text))
	{
		QString title(tr("Save Failed"));
		QString text = (tr("Save \"") + path + "\" failed!");
		QMessageBox::critical(this, title, text);
	}

	QTextStream out(&file);
	out << text;
	file.close();

	QString title(tr("Save Successfully"));
	text = (tr("Save \"") + path + "\" Successfully!");
	QMessageBox::information(this, title, text);
}

void QtMainWindow::on_action_Close_triggered()
{
	ui.rowCountLE->setText(tr("0"));
	ui.textPTE->clear();
}
