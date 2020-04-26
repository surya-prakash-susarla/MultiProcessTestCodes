#include <iostream>
#include <functional>
#include <process.h>
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>
#include "ProcessDeclarations.h"

int main(int argv, const char* argc[]) {

	if (argv == 1) {

		PROCESS_INFORMATION* main_proc_info;
		PROCESS_INFORMATION* secondary_proc_info;
		PROCESS_INFORMATION* tertiary_proc_info;
		LaunchProcess(START_PARAMS::MAIN_PROCESS, main_proc_info);
		LaunchProcess(START_PARAMS::SECONDARY_PROCESS, secondary_proc_info);
		LaunchProcess(START_PARAMS::TERTIARY_PROCESS, tertiary_proc_info);

		HANDLE proc_handles[3];
		proc_handles[0] = main_proc_info->hProcess;
		proc_handles[1] = secondary_proc_info->hProcess;
		proc_handles[2] = tertiary_proc_info->hProcess;

		WaitForMultipleObjects(3, proc_handles, true, 0xFFFFFFFF);
	}
	else if (argv == 2) {

		switch ( static_cast<START_PARAMS>(std::atoi(argc[1]))) {
		case START_PARAMS::MAIN_PROCESS: {
			LaunchProcess(START_PARAMS::MAIN_PROCESS);
			break;
		}
		case START_PARAMS::SECONDARY_PROCESS: {
			LaunchProcess(START_PARAMS::SECONDARY_PROCESS);
			break;
		}
		case START_PARAMS::TERTIARY_PROCESS: {
			LaunchProcess(START_PARAMS::TERTIARY_PROCESS);
			break;
		}
		}

	}
	else {
		std::cout << "ERROR IN INIT" << std::endl;
	}

	int end_sentinel;
	std::cin >> end_sentinel;

	return 0;
}