// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// DLL entry point

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "il2cpp-init.h"
#include "main.h"

// DLL entry point
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        init_il2cpp();
        CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Run), NULL, 0, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

