#pragma once

#include <QDialog>
#include "ui_AboutWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AboutWidgetClass; };
QT_END_NAMESPACE

class AboutWidget : public QDialog
{
	Q_OBJECT

public:
	AboutWidget(QWidget *parent = nullptr);
	~AboutWidget();

private:
	Ui::AboutWidgetClass *ui;
};
