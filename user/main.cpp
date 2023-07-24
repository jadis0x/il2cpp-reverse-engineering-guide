

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

	std::cout << "[F1]: Print Assembly Map\n";
	std::cout << "[F2]: Get Method Info\n";
	std::cout << "[F3]: Get Clasess of bolt.dll\n";
	std::cout << "[F4]: Get Clasess of bolt.user.dll\n";
	std::cout << "[DELETE]: Clear Console\n";

	while (true) {
		if (GetAsyncKeyState(VK_F1) & 0x8000) {
			const Il2CppImage* _AssemblyCSharp = _Il2CppHelper->GET_IL2CPP_IMAGE("Assembly-CSharp.dll");

			_Il2CppHelper->GetMethodInfo(_AssemblyCSharp, "SetFOV", 1, "NolanBehaviour", "");
		}

		if (GetAsyncKeyState(VK_F2) & 0x8000) {
			const Il2CppImage* _BoltDll = _Il2CppHelper->GET_IL2CPP_IMAGE("bolt.dll");

			if (_BoltDll) {
				_Il2CppHelper->GetClassesAndNamesFromAssembly(_BoltDll);
			}
		}

		if (GetAsyncKeyState(VK_F3) & 0x8000) {
			const Il2CppImage* _assemblyCSHARP = _Il2CppHelper->GET_IL2CPP_IMAGE("Assembly-CSharp.dll");

			if (_assemblyCSHARP) {
				_Il2CppHelper->GetClassesAndNamesFromAssembly(_assemblyCSHARP);
			}
		}

		if (GetAsyncKeyState(VK_F5) & 0x8000) {
			// Get the active domain
			const Il2CppDomain* domain = il2cpp_domain_get();

			// Define variables to hold the assembly list
			const Il2CppAssembly** assemblies;
			size_t size;

			// Use the il2cpp_domain_get_assemblies function to retrieve all assemblies
			assemblies = il2cpp_domain_get_assemblies(domain, &size);

			for (size_t i = 0; i < size; ++i) {
				const Il2CppAssembly* assembly = assemblies[i];

				if (assembly) {
					// Get the assembly name using il2cpp_image_get_name function
					const char* assemblyName = il2cpp_image_get_name(assembly->image);
					std::cout << assemblyName << "\n";
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}