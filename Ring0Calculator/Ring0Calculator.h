#pragma once

#include <QtWidgets/QWidget>
#include "ui_Ring0Calculator.h"
#include "CalculatorClient.h"
#include "Utils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Ring0CalculatorClass; };
QT_END_NAMESPACE

class Ring0Calculator : public QWidget
{
    Q_OBJECT

public:
    Ring0Calculator(QWidget *parent = nullptr);
    ~Ring0Calculator();

private slots:
    void add_button_clicked();
    void minus_button_clicked();
    void mul_button_clicked();
    void div_button_clicked();
    void calc_button_clicked();
    void clear_button_clicked();

private:
    Ui::Ring0CalculatorClass *ui;
    CalculatorClient *m_calc_client = nullptr;
    Operator m_operator = OPS_NONE;
    int m_operand = 0;
    int m_result = 0;
};
