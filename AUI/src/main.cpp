#include "stdafx.h"

// a sample exported function

HMODULE g_hInstance=NULL;
extern "C" __declspec(dllexport) BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            g_hInstance = hinstDLL;
	    OutputDebugString(_T("\r\n-----����AUI---\r\n"));
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
		OutputDebugString(_T("\r\n.......ж��AUI.....\r\n"));
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
