#include <Windows.h>
#include "Ring0Calculator.h"
#include <QDebug>
#include <QMessageBox>
#include "AboutWidget.h"


Ring0Calculator::Ring0Calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ring0CalculatorClass())
{
    ui->setupUi(this);

    this->m_calc_client = new CalculatorClient(this);

    if (!this->m_calc_client->isDriverAvailable()) {
        QMessageBox::warning(this, "Driver not found", "Please install Calculator Driver before execute this program", QMessageBox::Ok);
        exit(EXIT_FAILURE);
    }
    
    connect(ui->addButton, &QPushButton::clicked, this, &Ring0Calculator::add_button_clicked);
    connect(ui->minusButton, &QPushButton::clicked, this, &Ring0Calculator::minus_button_clicked);
    connect(ui->multiplyButton, &QPushButton::clicked, this, &Ring0Calculator::mul_button_clicked);
    connect(ui->divideButton, &QPushButton::clicked, this, &Ring0Calculator::div_button_clicked);
    connect(ui->calculateButton, &QPushButton::clicked, this, &Ring0Calculator::calc_button_clicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &Ring0Calculator::clear_button_clicked);


    connect(ui->aboutButton, &QPushButton::clicked, [=]() {
        AboutWidget about(this);
        about.exec();
     });

    connect(ui->oneButton, &QPushButton::clicked, [=]() {
        ui->resultTextEdit->moveCursor(QTextCursor::End);
        ui->resultTextEdit->insertPlainText("1");
        ui->resultTextEdit->setTextCursor(ui->resultTextEdit->textCursor());
    });

    connect(ui->twoButton, &QPushButton::clicked, [=]() {
        ui->resultTextEdit->moveCursor(QTextCursor::End);
        ui->resultTextEdit->insertPlainText("2");
        ui->resultTextEdit->setTextCursor(ui->resultTextEdit->textCursor());
    });

    connect(ui->threeButton, &QPushButton::clicked, [=]() {
        ui->resultTextEdit->moveCursor(QTextCursor::End);
        ui->resultTextEdit->insertPlainText("3");
        ui->resultTextEdit->setTextCursor(ui->resultTextEdit->textCursor());
    });

    connect(ui->fourButton, &QPushButton::clicked, [=]() {
        ui->resultTextEdit->moveCursor(QTextCursor::End);
        ui->resultTextEdit->insertPlainText("4");
        ui->resultTextEdit->setTextCursor(ui->resultTextEdit->textCursor());
    });

    connect(ui->fiveButton, &QPushButton::clicked, [=]() {
        ui->resultTextEdit->moveCursor(QTextCursor::End);
        ui->resultTextEdit->insertPlainText("5");
        ui->resultTextEdit->setTextCursor(ui->resultTextEdit->textCursor());
    });

    connect(ui->sixButton, &QPushButton::clicked, [=]() {
        ui->resultTextEdit->moveCursor(QTextCursor::End);
        ui->resultTextEdit->insertPlainText("6");
        ui->resultTextEdit->setTextCursor(ui->resultTextEdit->textCursor());
    });

    connect(ui->sevenButton, &QPushButton::clicked, [=]() {
        ui->resultTextEdit->moveCursor(QTextCursor::End);
        ui->resultTextEdit->insertPlainText("7");
        ui->resultTextEdit->setTextCursor(ui->resultTextEdit->textCursor());
    });

    connect(ui->eightButton, &QPushButton::clicked, [=]() {
        ui->resultTextEdit->moveCursor(QTextCursor::End);
        ui->resultTextEdit->insertPlainText("8");
        ui->resultTextEdit->setTextCursor(ui->resultTextEdit->textCursor());
    });

    connect(ui->nineButton, &QPushButton::clicked, [=]() {
        ui->resultTextEdit->moveCursor(QTextCursor::End);
        ui->resultTextEdit->insertPlainText("9");
        ui->resultTextEdit->setTextCursor(ui->resultTextEdit->textCursor());
    });

    connect(ui->zeroButton, &QPushButton::clicked, [=]() {
        if (ui->resultTextEdit->toPlainText() == "") {
            return;
        }
        ui->resultTextEdit->moveCursor(QTextCursor::End);
        ui->resultTextEdit->insertPlainText("0");
        ui->resultTextEdit->setTextCursor(ui->resultTextEdit->textCursor());
    });

}

void Ring0Calculator::add_button_clicked() 
{
    qDebug() << "[Ring0Calculator] - add_button_clicked";
    this->m_operator = OPS_ADD;
    this->m_operand = ui->resultTextEdit->toPlainText().toInt();
    qDebug() << "[Ring0Calculator] - add operand= " << this->m_operand;
    ui->resultTextEdit->clear();

}

void Ring0Calculator::minus_button_clicked() 
{
    qDebug() << "[Ring0Calculator] - minus_button_clicked";
    this->m_operator = OPS_MINUS;
    this->m_operand = ui->resultTextEdit->toPlainText().toInt();
    qDebug() << "[Ring0Calculator] - minus operand= " << this->m_operand;
    ui->resultTextEdit->clear();

}

void Ring0Calculator::mul_button_clicked() 
{
    qDebug() << "[Ring0Calculator] - mul_button_clicked";
    this->m_operator = OPS_MUL;
    this->m_operand = ui->resultTextEdit->toPlainText().toInt();
    qDebug() << "[Ring0Calculator] - mul operand= " << this->m_operand;
    ui->resultTextEdit->clear();

}

void Ring0Calculator::div_button_clicked() 
{
    qDebug() << "[Ring0Calculator] - div_button_clicked";
    this->m_operator = OPS_DIV;
    this->m_operand = ui->resultTextEdit->toPlainText().toInt();
    qDebug() << "[Ring0Calculator] - div operand= " << this->m_operand;
    ui->resultTextEdit->clear();

}


void Ring0Calculator::calc_button_clicked()
{
    qDebug() << "[Ring0Calculator] - calc_button_clicked";
    int current_operand = ui->resultTextEdit->toPlainText().toInt();

    switch (this->m_operator)
    {
    case OPS_ADD: {
        this->m_result = this->m_calc_client->add(this->m_operand, current_operand);
        break;
    }
    case OPS_MINUS: {
        this->m_result = this->m_calc_client->minus(this->m_operand, current_operand);
        break;
    }
    case OPS_MUL: {
        this->m_result = this->m_calc_client->mul(this->m_operand, current_operand);
        break;
    }
    case OPS_DIV: {
        this->m_result = this->m_calc_client->div(this->m_operand, current_operand);
        break;
    }
    default:
        this->m_result = -1;
        break;
    }

    ui->resultTextEdit->clear();
    ui->resultTextEdit->setText(QString::number(this->m_result));
    this->m_result = 0;
    this->m_operand = 0;
    this->m_operator = OPS_NONE;
}

void Ring0Calculator::clear_button_clicked()
{
    qDebug() << "[Ring0Calculator] - clear_button_clicked";
    this->m_result = 0;
    this->m_operator = OPS_NONE;
    ui->resultTextEdit->clear();

}

Ring0Calculator::~Ring0Calculator()
{
    delete ui;
}
