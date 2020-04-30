#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <process.h>
#include <thread>
#include <chrono>

void ProcessWaitLoop() {
	std::cout << "Currently on process : " << _getpid() << std::endl;
	while (true) {
		std::cout << "Waiting for message on : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
}

std::string GetLastErrorAsString()
{
	//Get the error message, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0)
		return std::string(); //No error message has been recorded

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);

	//Free the buffer.
	LocalFree(messageBuffer);

	return message;
}

int main(int argc, char* argv_[]) {
	
	std::vector<std::string> argv(argv_ + 0, argv_ + argc);

	if ((bool)(argv[0][0] == '1')) {
		std::cout << "In secondary process " << _getpid() << std::endl;
		ProcessWaitLoop();
	}
	else {
		int should_start_new_process = 0;
		std::cout << "Start new process ? ";
		std::cin >> should_start_new_process;

		if (should_start_new_process == 0)
			return 0;

		STARTUPINFO* startup_info = new STARTUPINFO();
		PROCESS_INFORMATION* process_info = new PROCESS_INFORMATION();

		const int max_buffer_capacity = 256;
		std::string path_buffer(max_buffer_capacity,' ');
		if (!GetModuleFileNameA(nullptr, &path_buffer[0], max_buffer_capacity)) {
			std::cout << "Filename could not be extracted" << std::endl;
			return 0;
		}

		std::wstring w_path_buffer(path_buffer.begin(), path_buffer.end());
		std::wstring w_path_args = L"1";
		
		std::wcout << "Starting process from : " << std::endl << w_path_buffer << std::endl;

		if (CreateProcess(&w_path_buffer[0], &w_path_args[0], nullptr, nullptr, false, CREATE_NEW_CONSOLE, nullptr, nullptr, startup_info, process_info)) {
			std::cout << "Process creation successful" << std::endl;

			ProcessWaitLoop();

			WaitForSingleObject(process_info->hProcess, INFINITE);
			CloseHandle(process_info->hProcess);
		}
		else {
			std::cout << "Process creation failed" << std::endl;
			std::cout << GetLastErrorAsString() << std::endl;
		}
	}

	int k;
	std::cin >> k;

	return 0;
}