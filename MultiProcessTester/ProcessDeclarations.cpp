#include "ProcessDeclarations.h"

#include <chrono>
#include <thread>
#include <process.h>
#include <iostream>
#include <string>

const long long TIME_INCREMENT = 2000;

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