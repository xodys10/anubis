#include <Windows.h>
#include <process.h>
#include <MinHook.h>
#include "Extra.hpp"
#include "Overlay.hpp"

static HWND GetWindowHandle();
using MenuLayer_t = bool(*)(void* thisptr);

class HookManager
{
public:

    bool Install(void* target)
    {
        if (m_Installed || target == nullptr) return false;

        MH_Initialize();

        m_Target = target;

        MH_CreateHook(target, &Detour,  reinterpret_cast<void**>(&m_Original));
        MH_EnableHook(m_Target);

        m_Installed = true;
        return true;
    }

    void Uninstall()
    {
        if (!m_Installed) return;
        
        MH_DisableHook(m_Target);
        MH_RemoveHook(m_Target);

        m_Installed = false;
        m_Target = nullptr;
        m_Original = nullptr;
    }

    static HookManager& Instance()
    {
        static HookManager instance;
        return instance;
    }

private:

    HookManager() = default;
    ~HookManager() = default;

    static bool Detour(void* thisptr)
    {
        auto& instance = Instance();
        bool result = instance.m_Original ? instance.m_Original(thisptr) : true;

        HWND hwnd = GetWindowHandle();
        if (hwnd) instance.m_Overlay.Init(hwnd);

        return result;
    }

    bool m_Installed = false;
    void* m_Target;
    MenuLayer_t m_Original = nullptr;
    Overlay m_Overlay;
};

static HWND GetWindowHandle()
{
    HWND hwnd = nullptr;

    // since we know the class of gd is always GLFW30
    // and the caption is Geometry Dash, we can get the handle like that

    const char* targetClassName = "GLFW30";
    const char* targetCaption = "Geometry Dash";

    hwnd = FindWindow(targetClassName, targetCaption);
    return hwnd;
}

unsigned __stdcall MainThread(void*)
{
    HMODULE hModule = GetModuleHandleA(NULL);
    uintptr_t offset = 0x31ebd0;

    void* target = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(hModule) + offset);
    HookManager::Instance().Install(target);

    return 0;
}

DLLEXPORT void StartThread()
{
    HANDLE hThread = reinterpret_cast<HANDLE>(
        _beginthreadex(
            nullptr, 0, MainThread, nullptr, 0, nullptr
        )
    );

    if (hThread) CloseHandle(hThread);
}

BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hInstDLL);
        StartThread();
    }
    
    return TRUE;
}
