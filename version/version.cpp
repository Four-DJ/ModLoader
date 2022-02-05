#include "mono.h"

HINSTANCE mHinstDLL = nullptr;
#ifdef _WIN64
extern "C"
#endif
uintptr_t mProcs[17] = { 0 };

const char* mImportNames[] = { "GetFileVersionInfoA", "GetFileVersionInfoByHandle", "GetFileVersionInfoExA", "GetFileVersionInfoExW", "GetFileVersionInfoSizeA", "GetFileVersionInfoSizeExA", "GetFileVersionInfoSizeExW", "GetFileVersionInfoSizeW", "GetFileVersionInfoW", "VerFindFileA", "VerFindFileW", "VerInstallFileA", "VerInstallFileW", "VerLanguageNameA", "VerLanguageNameW", "VerQueryValueA", "VerQueryValueW" };

void Inject() {
	Sleep(500);
	initMonoFunctions();

	fnThreadAttach(fnGetRootDomain());
	MonoAssembly* assembly = fnAssemblyOpen("ModLoader.dll", NULL);
	MonoImage* image = fnAssemblyGetImage(assembly);
	MonoClass* klass = fnClassFromName(image, "ModLoader", "Bootstrap");
	MonoMethod* method = fnMethodFromName(klass, "Inject", 0);
	fnRuntimeInvoke(method, NULL, NULL, NULL);
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		char szPath[MAX_PATH];

		if (!GetSystemDirectory(szPath, MAX_PATH))
			return false;

		strcat_s(szPath, "\\version.dll");

		mHinstDLL = LoadLibrary(szPath);

		if (!mHinstDLL)
			return false;

		for (int i = 0; i < 17; i++)
			mProcs[i] = reinterpret_cast<uintptr_t>(GetProcAddress(mHinstDLL, mImportNames[i]));
		if (GetModuleHandleA("UnityCrashHandler64.exe") == nullptr) {
			DisableThreadLibraryCalls(hinstDLL);
			CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Inject), nullptr, 0, nullptr);
		}
	}
	else if (fdwReason == DLL_PROCESS_DETACH) {
		FreeLibrary(mHinstDLL);
	}

	return true;
}

extern "C" {
#ifdef _WIN64
void GetFileVersionInfoA_proxy();
void GetFileVersionInfoByHandle_proxy();
void GetFileVersionInfoExA_proxy();
void GetFileVersionInfoExW_proxy();
void GetFileVersionInfoSizeA_proxy();
void GetFileVersionInfoSizeExA_proxy();
void GetFileVersionInfoSizeExW_proxy();
void GetFileVersionInfoSizeW_proxy();
void GetFileVersionInfoW_proxy();
void VerFindFileA_proxy();
void VerFindFileW_proxy();
void VerInstallFileA_proxy();
void VerInstallFileW_proxy();
void VerLanguageNameA_proxy();
void VerLanguageNameW_proxy();
void VerQueryValueA_proxy();
void VerQueryValueW_proxy();
#else
__declspec(naked) void __stdcall GetFileVersionInfoA_proxy(){ __asm { jmp mProcs[0 * 4] } }
__declspec(naked) void __stdcall GetFileVersionInfoByHandle_proxy(){ __asm { jmp mProcs[1 * 4] } }
__declspec(naked) void __stdcall GetFileVersionInfoExA_proxy(){ __asm { jmp mProcs[2 * 4] } }
__declspec(naked) void __stdcall GetFileVersionInfoExW_proxy(){ __asm { jmp mProcs[3 * 4] } }
__declspec(naked) void __stdcall GetFileVersionInfoSizeA_proxy(){ __asm { jmp mProcs[4 * 4] } }
__declspec(naked) void __stdcall GetFileVersionInfoSizeExA_proxy(){ __asm { jmp mProcs[5 * 4] } }
__declspec(naked) void __stdcall GetFileVersionInfoSizeExW_proxy(){ __asm { jmp mProcs[6 * 4] } }
__declspec(naked) void __stdcall GetFileVersionInfoSizeW_proxy(){ __asm { jmp mProcs[7 * 4] } }
__declspec(naked) void __stdcall GetFileVersionInfoW_proxy(){ __asm { jmp mProcs[8 * 4] } }
__declspec(naked) void __stdcall VerFindFileA_proxy(){ __asm { jmp mProcs[9 * 4] } }
__declspec(naked) void __stdcall VerFindFileW_proxy(){ __asm { jmp mProcs[10 * 4] } }
__declspec(naked) void __stdcall VerInstallFileA_proxy(){ __asm { jmp mProcs[11 * 4] } }
__declspec(naked) void __stdcall VerInstallFileW_proxy(){ __asm { jmp mProcs[12 * 4] } }
__declspec(naked) void __stdcall VerLanguageNameA_proxy(){ __asm { jmp mProcs[13 * 4] } }
__declspec(naked) void __stdcall VerLanguageNameW_proxy(){ __asm { jmp mProcs[14 * 4] } }
__declspec(naked) void __stdcall VerQueryValueA_proxy(){ __asm { jmp mProcs[15 * 4] } }
__declspec(naked) void __stdcall VerQueryValueW_proxy(){ __asm { jmp mProcs[16 * 4] } }
#endif
}