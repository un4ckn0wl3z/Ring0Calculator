#pragma once
#include <Windows.h>
#include <QObject>

class CalculatorClient  : public QObject
{
	Q_OBJECT

public:
	CalculatorClient(QObject *parent);
	~CalculatorClient();

	int add(int num1, int num2);
	int minus(int num1, int num2);
	int mul(int num1, int num2);
	int div(int num1, int num2);
	bool isDriverAvailable() const;
private:
	HANDLE m_diver = NULL;
	bool m_isDriverAvailable = true;
};
