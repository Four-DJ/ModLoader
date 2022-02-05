#pragma once
#include <Windows.h>

typedef VOID MonoObject;
typedef VOID MonoDomain;
typedef VOID MonoAssembly;
typedef VOID MonoImage;
typedef VOID MonoClass;
typedef VOID MonoMethod;
typedef VOID MonoImageOpenStatus;

typedef void(__cdecl* t_mono_thread_attach)(MonoDomain*);
t_mono_thread_attach fnThreadAttach;
typedef  MonoDomain* (__cdecl* t_mono_get_root_domain)(void);
t_mono_get_root_domain fnGetRootDomain;
typedef MonoAssembly* (__cdecl* t_mono_assembly_open)(const char*, MonoImageOpenStatus*);
t_mono_assembly_open fnAssemblyOpen;
typedef MonoImage* (__cdecl* t_mono_assembly_get_image)(MonoAssembly*);
t_mono_assembly_get_image fnAssemblyGetImage;
typedef MonoClass* (__cdecl* t_mono_class_from_name)(MonoImage*, const char*, const char*);
t_mono_class_from_name fnClassFromName;
typedef MonoMethod* (__cdecl* t_mono_class_get_method_from_name)(MonoClass*, const char*, int);
t_mono_class_get_method_from_name fnMethodFromName;
typedef MonoObject* (__cdecl* t_mono_runtime_invoke)(MonoMethod*, void*, void**, MonoObject**);
t_mono_runtime_invoke fnRuntimeInvoke;
typedef const char* (__cdecl* t_mono_assembly_getrootdir)(void);
t_mono_assembly_getrootdir fnGetRootDir;

void initMonoFunctions() {
	HMODULE mono = GetModuleHandleA("mono-2.0-bdwgc.dll");
	fnThreadAttach = (t_mono_thread_attach)GetProcAddress(mono, "mono_thread_attach");
	fnGetRootDomain = (t_mono_get_root_domain)GetProcAddress(mono, "mono_get_root_domain");
	fnAssemblyOpen = (t_mono_assembly_open)GetProcAddress(mono, "mono_assembly_open");
	fnAssemblyGetImage = (t_mono_assembly_get_image)GetProcAddress(mono, "mono_assembly_get_image");
	fnClassFromName = (t_mono_class_from_name)GetProcAddress(mono, "mono_class_from_name");
	fnMethodFromName = (t_mono_class_get_method_from_name)GetProcAddress(mono, "mono_class_get_method_from_name");
	fnRuntimeInvoke = (t_mono_runtime_invoke)GetProcAddress(mono, "mono_runtime_invoke");
	fnGetRootDir = (t_mono_assembly_getrootdir)GetProcAddress(mono, "mono_assembly_getrootdir");
}