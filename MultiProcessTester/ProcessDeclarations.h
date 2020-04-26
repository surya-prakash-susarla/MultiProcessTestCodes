#pragma once
#include <Windows.h>

enum class START_PARAMS {
	MAIN_PROCESS = 0,
	SECONDARY_PROCESS,
	TERTIARY_PROCESS
};

void LaunchProcess(START_PARAMS info, PROCESS_INFORMATION* process_info);

class TimeTakingTask {
public:
	TimeTakingTask(long long duration);
	void RunTask();
private:
	void TaskImpl_();
	long long duration_;
};

class ProcessBase {
public:
	virtual void Run() = 0;
};

class MainProcess: public ProcessBase {
public:
	void Run() override;
};

class SecondaryProcess: public ProcessBase {
public:
	void Run() override;
};

class TertiaryProcess: public ProcessBase {
public:
	void Run() override;
};