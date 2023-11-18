#include <stdio.h>
#include "CalculatorClient.h"
#include <QDebug>

#include "..\CalculatorDriver\IOCTLs.h"
#include "..\CalculatorDriver\Common.h"

CalculatorClient::CalculatorClient(QObject *parent)
	: QObject(parent)
{
    HANDLE hDriver = CreateFile(
        L"\\\\.\\Ring0Calculator",
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr);

    if (hDriver == INVALID_HANDLE_VALUE)
    {
        qDebug() << "[Ring0Calculator] - Cannot open handler for driver";
        this->m_isDriverAvailable = false;
        return;
    }

	this->m_diver = hDriver;
}

CalculatorClient::~CalculatorClient()
{
    CloseHandle(this->m_diver);
}

int CalculatorClient::add(int num1, int num2)
{
    InputParameters input;
    input.num1 = num1;
    input.num2 = num2;
    OutputParameters output;
    DWORD bytesReturned;

    qDebug() << "[CalculatorClient] - add num1:" << input.num1 << "| num2:" << input.num2;

    BOOL success = DeviceIoControl(
        this->m_diver,
        RING0_CALCULATOR_ADD,
        &input,              // pointer to the "input"
        sizeof(input),       // the size of the "input"
        &output,             // pointer to "output"
        sizeof(output),      // size of "output"
        &bytesReturned,
        nullptr);

    if (!success)
    {
        return -1;
    }

    return output.result;


}

int CalculatorClient::minus(int num1, int num2)
{
    InputParameters input;
    input.num1 = num1;
    input.num2 = num2;
    OutputParameters output;
    DWORD bytesReturned;

    qDebug() << "[CalculatorClient] - minus num1:" << input.num1 << "| num2:" << input.num2;


    BOOL success = DeviceIoControl(
        this->m_diver,
        RING0_CALCULATOR_MINUS,
        &input,              // pointer to the "input"
        sizeof(input),       // the size of the "input"
        &output,             // pointer to "output"
        sizeof(output),      // size of "output"
        &bytesReturned,
        nullptr);

    if (!success)
    {
        return -1;
    }
    return output.result;
}

int CalculatorClient::mul(int num1, int num2)
{
    InputParameters input;
    input.num1 = num1;
    input.num2 = num2;
    OutputParameters output;
    DWORD bytesReturned;

    qDebug() << "[CalculatorClient] - mul num1:" << input.num1 << "| num2:" << input.num2;


    BOOL success = DeviceIoControl(
        this->m_diver,
        RING0_CALCULATOR_MUL,
        &input,              // pointer to the "input"
        sizeof(input),       // the size of the "input"
        &output,             // pointer to "output"
        sizeof(output),      // size of "output"
        &bytesReturned,
        nullptr);

    if (!success)
    {
        return -1;
    }
    return output.result;
}

int CalculatorClient::div(int num1, int num2)
{
    InputParameters input;
    input.num1 = num1;
    input.num2 = num2;
    OutputParameters output;
    DWORD bytesReturned;

    qDebug() << "[CalculatorClient] - div num1:" << input.num1 << "| num2:" << input.num2;

    BOOL success = DeviceIoControl(
        this->m_diver,
        RING0_CALCULATOR_DIV,
        &input,              // pointer to the "input"
        sizeof(input),       // the size of the "input"
        &output,             // pointer to "output"
        sizeof(output),      // size of "output"
        &bytesReturned,
        nullptr);

    if (!success)
    {
        return -1;
    }
    return output.result;
}

bool CalculatorClient::isDriverAvailable() const
{
    return this->m_isDriverAvailable;
}
