#include "ProcessDeclarations.h"

#include <chrono>
#include <thread>
#include <process.h>
#include <iostream>
#include <string>
#include <Windows.h>

const long long TIME_INCREMENT = 2000;

void LaunchProcess(START_PARAMS info, PROCESS_INFORMATION* process_info) {
	std::wstring application_path(L"MultiProcessTester.exe");

	switch (info) {
	case START_PARAMS::MAIN_PROCESS:
		application_path += L"0";
		break;
	case START_PARAMS::SECONDARY_PROCESS:
		application_path += L"1";
		break;
	case START_PARAMS::TERTIARY_PROCESS:
		application_path += L"2";
		break;
	}

	STARTUPINFO* startup_info = new STARTUPINFO();
	process_info = new PROCESS_INFORMATION();

	if (CreateProcess(NULL, (LPWSTR)(application_path.c_str()), NULL, NULL, false, 0, NULL, NULL, startup_info, process_info)) {
		std::cout << "PROCESS CREATION SUCCESSFUL " << std::endl;
		std::cout << "PARENT -- " << _getpid() << std::endl;
	}
	else {
		std::cout << "PROCESS CREATION FAILED" << std::endl;
	}
}

TimeTakingTask::TimeTakingTask(long long duration) {
	duration_ = duration;
}

void TimeTakingTask::TaskImpl_() {
	long long current_time = 0;
	std::cout << "TIME TAKING TASK BEING RUN ON : " << std::this_thread::get_id() << std::endl;
	while (current_time < duration_) {
		current_time += TIME_INCREMENT;
		std::this_thread::sleep_for(std::chrono::milliseconds(TIME_INCREMENT));
	}
}

void TimeTakingTask::RunTask() {
	std::cout << "Current parent thread : " << std::this_thread::get_id() << std::endl;
	std::thread task_thread(&TimeTakingTask::TaskImpl_, this);
	task_thread.join();
}

void MainProcess::Run() {
	TimeTakingTask task_(10000);
	task_.RunTask();
}

void SecondaryProcess::Run() {
	TimeTakingTask task_(20000);
	task_.RunTask();
}

void TertiaryProcess::Run() {
	TimeTakingTask task_(30000);
	task_.RunTask();
}