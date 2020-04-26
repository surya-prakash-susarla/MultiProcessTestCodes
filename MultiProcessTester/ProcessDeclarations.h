#pragma once

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