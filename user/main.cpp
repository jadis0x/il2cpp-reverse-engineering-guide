

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "il2cpp-appdata.h"
#include "helpers.h"

#include <chrono>
#include <thread>

#include "Il2CppHelper.h"

using namespace app;

extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";


void Run()
{
	// Initialize thread data - DO NOT REMOVE
	il2cpp_thread_attach(il2cpp_domain_get());

	il2cppi_new_console();

	Il2CppHelper* _Il2CppHelper = new Il2CppHelper();

	while (true) {
		if (GetAsyncKeyState(VK_F1) & 0x8000) {
			const Il2CppImage* _AssemblyCSharp = _Il2CppHelper->GET_IL2CPP_IMAGE("Assembly-CSharp.dll");

			_Il2CppHelper->GetMethodInfo(_AssemblyCSharp, "SetFOV", 1, "NolanBehaviour", "");
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}