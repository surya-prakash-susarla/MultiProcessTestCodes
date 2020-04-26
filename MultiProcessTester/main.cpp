#include <iostream>
#include <functional>
#include <process.h>
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include "ProcessDeclarations.h"

enum START_PARAMS {
	MAIN_PROCESS = 0,
	SECONDARY_PROCESS,
	TERTIARY_PROCESS
};

void LaunchProcess(START_PARAMS info) {
	std::wstring application_path(L"MultiProcessTester.exe");

	switch (info) {
	case MAIN_PROCESS:
		application_path += L"0";
		break;
	case SECONDARY_PROCESS:
		application_path += L"1";
		break;
	case TERTIARY_PROCESS:
		application_path += L"2";
		break;
	}

	STARTUPINFO* startup_info = new STARTUPINFO();
	PROCESS_INFORMATION* process_info = new PROCESS_INFORMATION();

	if (CreateProcess(NULL, (LPWSTR)(application_path.c_str()), NULL, NULL, false, 0, NULL, NULL, startup_info, process_info)) {
		std::cout << "PROCESS CREATION SUCCESSFUL " << std::endl;
		std::cout << "PARENT -- " << _getpid() << std::endl;
	}
	else {
		std::cout << "PROCESS CREATION FAILED" << std::endl;
	}
}

int main(int argv, const char* argc[]) {

	if (argv != 2) {
		return 0;
	}
	else {
		switch (std::atoi(argc[1])) {
		case MAIN_PROCESS: {
			LaunchProcess(MAIN_PROCESS);
			break;
		}
		case SECONDARY_PROCESS: {
			LaunchProcess(SECONDARY_PROCESS);
			break;
		}
		case TERTIARY_PROCESS: {
			LaunchProcess(TERTIARY_PROCESS);
			break;
		}
		}
	}

	int end_sentinel;
	std::cin >> end_sentinel;

	return 0;
}