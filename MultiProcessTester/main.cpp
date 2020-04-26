#include <iostream>
#include <functional>
#include <process.h>
#include <string>
#include <stdlib.h>
#include "ProcessDeclarations.h"

int main(int argv, const char* argc[]) {

	if (argv == 1) {

		PROCESS_INFORMATION* main_proc_info = nullptr;
		PROCESS_INFORMATION* secondary_proc_info = nullptr;
		PROCESS_INFORMATION* tertiary_proc_info = nullptr;
		LaunchProcess(START_PARAMS::MAIN_PROCESS, main_proc_info);
		LaunchProcess(START_PARAMS::SECONDARY_PROCESS, secondary_proc_info);
		LaunchProcess(START_PARAMS::TERTIARY_PROCESS, tertiary_proc_info);

		HANDLE proc_handles[3];
		proc_handles[0] = main_proc_info->hProcess;
		proc_handles[1] = secondary_proc_info->hProcess;
		proc_handles[2] = tertiary_proc_info->hProcess;

		WaitForMultipleObjects(3, proc_handles, true, 0xFFFFFFFF);
		for (HANDLE i : proc_handles)
			CloseHandle(i);
		std::cout << "-------------------------EXIT------------------------" << std::endl;
	}
	else if (argv == 2) {

		switch (static_cast<START_PARAMS>(std::atoi(argc[1]))) {
		case START_PARAMS::MAIN_PROCESS: {
			MainProcess main_process_task_runner;
			main_process_task_runner.Run();
			break;
		}
		case START_PARAMS::SECONDARY_PROCESS: {
			SecondaryProcess secondary_process_task_runner;
			secondary_process_task_runner.Run();
			break;
		}
		case START_PARAMS::TERTIARY_PROCESS: {
			TertiaryProcess tertiary_process_task_runner;
			tertiary_process_task_runner.Run();
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