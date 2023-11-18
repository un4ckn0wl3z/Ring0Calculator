#pragma warning(disable: 4996)
#include <ntddk.h>
#include "IOCTLs.h"
#include "Common.h"

void DriverCleanup(PDRIVER_OBJECT DriverObject);

NTSTATUS CreateClose(_In_ PDEVICE_OBJECT DeviceObject, _In_ PIRP Irp);
NTSTATUS DeviceControl(_In_ PDEVICE_OBJECT DeviceObject, _In_ PIRP Irp);

UNICODE_STRING deviceName = RTL_CONSTANT_STRING(L"\\Device\\Ring0Calculator");
UNICODE_STRING symlink = RTL_CONSTANT_STRING(L"\\??\\Ring0Calculator");

extern "C"
NTSTATUS
DriverEntry(
	_In_ PDRIVER_OBJECT DriverObject,
	_In_ PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);
	DbgPrint(("[+] DriverEntry called!\n"));
	DriverObject->DriverUnload = DriverCleanup;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DeviceControl;
	DriverObject->MajorFunction[IRP_MJ_CREATE] = CreateClose;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = CreateClose;

	PDEVICE_OBJECT deviceObject;

	NTSTATUS status = IoCreateDevice(
		DriverObject,
		0,
		&deviceName,
		FILE_DEVICE_UNKNOWN,
		0,
		FALSE,
		&deviceObject
	);

	if (!NT_SUCCESS(status))
	{
		DbgPrint("[!] Failed to create Device Object (0x%08X)\n", status);
		return status;
	}

	status = IoCreateSymbolicLink(&symlink, &deviceName);

	if (!NT_SUCCESS(status))
	{
		DbgPrint("[!] Failed to create symlink (0x%08X)\n", status);
		IoDeleteDevice(deviceObject);
		return status;
	}

	return STATUS_SUCCESS;
}


NTSTATUS DeviceControl(_In_ PDEVICE_OBJECT DeviceObject, _In_ PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	NTSTATUS status = STATUS_SUCCESS;
	ULONG_PTR length = 0;

	switch (stack->Parameters.DeviceIoControl.IoControlCode)
	{
	case RING0_CALCULATOR_ADD: 
	{
		DbgPrint(("[+] RING0_CALCULATOR_ADD requested!\n"));
		if (stack->Parameters.DeviceIoControl.InputBufferLength < sizeof(InputParameters))
		{
			status = STATUS_BUFFER_TOO_SMALL;
			DbgPrint(("[!] STATUS_BUFFER_TOO_SMALL\n"));
			break;
		}
		InputParameters *input = (InputParameters*)stack->Parameters.DeviceIoControl.Type3InputBuffer;

		if (input == nullptr)
		{
			status = STATUS_INVALID_PARAMETER;
			DbgPrint(("[!] STATUS_INVALID_PARAMETER\n"));
			break;
		}

		int num1 = input->num1;
		int num2 = input->num2;
		int result = num1 + num2;

		DbgPrint("[+] %d + %d = %d\n", num1, num2, result);

		if (stack->Parameters.DeviceIoControl.OutputBufferLength < sizeof(OutputParameters))
		{
			status = STATUS_BUFFER_TOO_SMALL;
			DbgPrint(("[!] STATUS_BUFFER_TOO_SMALL\n"));
			break;
		}

		OutputParameters *userBuffer = (OutputParameters*)Irp->UserBuffer;

		if (userBuffer == nullptr)
		{
			status = STATUS_INVALID_PARAMETER;
			DbgPrint(("[!] STATUS_INVALID_PARAMETER\n"));
			break;
		}

		userBuffer->result = result;
		length = sizeof(result);
		break;
	}
	case RING0_CALCULATOR_MINUS:
	{
		DbgPrint(("[+] RING0_CALCULATOR_MINUS requested!\n"));
		if (stack->Parameters.DeviceIoControl.InputBufferLength < sizeof(InputParameters))
		{
			status = STATUS_BUFFER_TOO_SMALL;
			DbgPrint(("[!] STATUS_BUFFER_TOO_SMALL\n"));
			break;
		}
		InputParameters* input = (InputParameters*)stack->Parameters.DeviceIoControl.Type3InputBuffer;

		if (input == nullptr)
		{
			status = STATUS_INVALID_PARAMETER;
			DbgPrint(("[!] STATUS_INVALID_PARAMETER\n"));
			break;
		}

		int num1 = input->num1;
		int num2 = input->num2;
		int result = num1 - num2;

		DbgPrint("[+] %d - %d = %d\n", num1, num2, result);

		if (stack->Parameters.DeviceIoControl.OutputBufferLength < sizeof(OutputParameters))
		{
			status = STATUS_BUFFER_TOO_SMALL;
			DbgPrint(("[!] STATUS_BUFFER_TOO_SMALL\n"));
			break;
		}

		OutputParameters* userBuffer = (OutputParameters*)Irp->UserBuffer;

		if (userBuffer == nullptr)
		{
			status = STATUS_INVALID_PARAMETER;
			DbgPrint(("[!] STATUS_INVALID_PARAMETER\n"));
			break;
		}

		userBuffer->result = result;
		length = sizeof(result);
		break;
	}
	case RING0_CALCULATOR_MUL:
	{
		DbgPrint(("[+] RING0_CALCULATOR_MUL requested!\n"));
		if (stack->Parameters.DeviceIoControl.InputBufferLength < sizeof(InputParameters))
		{
			status = STATUS_BUFFER_TOO_SMALL;
			DbgPrint(("[!] STATUS_BUFFER_TOO_SMALL\n"));
			break;
		}
		InputParameters* input = (InputParameters*)stack->Parameters.DeviceIoControl.Type3InputBuffer;

		if (input == nullptr)
		{
			status = STATUS_INVALID_PARAMETER;
			DbgPrint(("[!] STATUS_INVALID_PARAMETER\n"));
			break;
		}

		int num1 = input->num1;
		int num2 = input->num2;
		int result = num1 * num2;

		DbgPrint("[+] %d * %d = %d\n", num1, num2, result);

		if (stack->Parameters.DeviceIoControl.OutputBufferLength < sizeof(OutputParameters))
		{
			status = STATUS_BUFFER_TOO_SMALL;
			DbgPrint(("[!] STATUS_BUFFER_TOO_SMALL\n"));
			break;
		}

		OutputParameters* userBuffer = (OutputParameters*)Irp->UserBuffer;

		if (userBuffer == nullptr)
		{
			status = STATUS_INVALID_PARAMETER;
			DbgPrint(("[!] STATUS_INVALID_PARAMETER\n"));
			break;
		}

		userBuffer->result = result;
		length = sizeof(result);
		break;
	}
	case RING0_CALCULATOR_DIV:
	{
		DbgPrint(("[+] RING0_CALCULATOR_DIV requested!\n"));
		if (stack->Parameters.DeviceIoControl.InputBufferLength < sizeof(InputParameters))
		{
			status = STATUS_BUFFER_TOO_SMALL;
			DbgPrint(("[!] STATUS_BUFFER_TOO_SMALL\n"));
			break;
		}
		InputParameters* input = (InputParameters*)stack->Parameters.DeviceIoControl.Type3InputBuffer;

		if (input == nullptr)
		{
			status = STATUS_INVALID_PARAMETER;
			DbgPrint(("[!] STATUS_INVALID_PARAMETER\n"));
			break;
		}

		if (input->num2 == 0)
		{
			status = STATUS_INVALID_PARAMETER;
			DbgPrint(("[!] STATUS_INVALID_PARAMETER num2 is 0\n"));
			break;
		}

		int num1 = input->num1;
		int num2 = input->num2;
		int result = num1 / num2;

		DbgPrint("[+] %d / %d = %d\n", num1, num2, result);

		if (stack->Parameters.DeviceIoControl.OutputBufferLength < sizeof(OutputParameters))
		{
			status = STATUS_BUFFER_TOO_SMALL;
			DbgPrint(("[!] STATUS_BUFFER_TOO_SMALL\n"));
			break;
		}

		OutputParameters* userBuffer = (OutputParameters*)Irp->UserBuffer;

		if (userBuffer == nullptr)
		{
			status = STATUS_INVALID_PARAMETER;
			DbgPrint(("[!] STATUS_INVALID_PARAMETER\n"));
			break;
		}

		userBuffer->result = result;
		length = sizeof(result);
		break;
	}
	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		DbgPrint("[!] STATUS_INVALID_DEVICE_REQUEST\n");
		break;
	}

	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = length;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
}


NTSTATUS CreateClose(_In_ PDEVICE_OBJECT DeviceObject, _In_ PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	DbgPrint("[+] Ring0Calculator CreateClose called\n");
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

void DriverCleanup(PDRIVER_OBJECT DriverObject)
{
	DbgPrint("[+] Ring0Calculator DriverCleanup called\n");
	IoDeleteSymbolicLink(&symlink);
	IoDeleteDevice(DriverObject->DeviceObject);
}