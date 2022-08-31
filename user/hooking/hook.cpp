#include "pch-il2cpp.h"
#include "hook.h"
#include <Windows.h>
#include "includes/detours/detours.h"
#include <iostream>
#include "directx/directx.h"

using namespace app;


bool hook(PVOID* ppPointer, PVOID pDetour, const char* functionName) {
	if (const auto error = DetourAttach(ppPointer, pDetour); error != NO_ERROR) {
		std::cout << "failed to hook " << functionName << ", error " << error << std::endl;
		return false;
	}
	std::cout << "successfully hooked method " << functionName << std::endl;
	return true;
}

#define HOOKFUNC(n, d) if (!hook(&(PVOID&)n, d, #n)) return;

bool unhook(PVOID* ppPointer, PVOID pDetour, const char* functionName) {
	if (const auto error = DetourDetach(ppPointer, pDetour); error != NO_ERROR) {
		std::cout << "failed to unhook " << functionName << ", error " << error << std::endl;
		return false;
	}
	std::cout << "successfully unhooked method " << functionName << std::endl;
	return true;
}

#define UNHOOKFUNC(n, d) if (!unhook(&(PVOID&)n, d, #n)) return;

void perform_hooks()
{
	// present hook for imgui
	do_directx_hooks();

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// method name from game, then provide the function name to your detour.
	HOOKFUNC(u00CEu00CEu00CCu00CEu00CFu00CEu00CFu00CFu00CEu00CFu00CCu00CFu00CEu00CEu00CFu00CEu00CCu00CFu00CFu00CFu00CDu00CFu00CC_u00CDu00CCu00CFu00CEu00CDu00CCu00CEu00CEu00CFu00CDu00CCu00CEu00CDu00CDu00CEu00CFu00CDu00CFu00CCu00CFu00CFu00CCu00CC,
		on_player_join);

	HOOKFUNC(u00CEu00CEu00CCu00CEu00CFu00CEu00CFu00CFu00CEu00CFu00CCu00CFu00CEu00CEu00CFu00CEu00CCu00CFu00CFu00CFu00CDu00CFu00CC_u00CDu00CDu00CFu00CEu00CDu00CFu00CCu00CEu00CFu00CDu00CFu00CFu00CFu00CDu00CDu00CEu00CCu00CDu00CDu00CEu00CEu00CDu00CC,
		on_player_leave);


	DetourTransactionCommit();
}

// this will get fairly messy when doing lots of hooks, consider splitting into multiple folders/files.

#define join_original(a, b, c) u00CEu00CEu00CCu00CEu00CFu00CEu00CFu00CFu00CEu00CFu00CCu00CFu00CEu00CEu00CFu00CEu00CCu00CFu00CFu00CFu00CDu00CFu00CC_u00CDu00CCu00CFu00CEu00CDu00CCu00CEu00CEu00CFu00CDu00CCu00CEu00CDu00CDu00CEu00CFu00CDu00CFu00CCu00CFu00CFu00CCu00CC(a, b, c)
#define leave_original(a, b, c) u00CEu00CEu00CCu00CEu00CFu00CEu00CFu00CFu00CEu00CFu00CCu00CFu00CEu00CEu00CFu00CEu00CCu00CFu00CFu00CFu00CDu00CFu00CC_u00CDu00CDu00CFu00CEu00CDu00CFu00CCu00CEu00CFu00CDu00CFu00CFu00CFu00CDu00CDu00CEu00CCu00CDu00CDu00CEu00CEu00CDu00CC(a, b, c)
extern bool in_room = false;

void on_player_join(u00CEu00CEu00CCu00CEu00CFu00CEu00CFu00CFu00CEu00CFu00CCu00CFu00CEu00CEu00CFu00CEu00CCu00CFu00CFu00CFu00CDu00CFu00CC* class_ptr, u00CFu00CDu00CCu00CDu00CEu00CCu00CDu00CEu00CFu00CDu00CFu00CCu00CFu00CDu00CCu00CDu00CFu00CDu00CFu00CFu00CCu00CFu00CE* player_ptr, MethodInfo* method)
{
	std::cout << "join";
	if (APIUser_get_CurrentUser(nullptr)->fields._username_k__BackingField == player_ptr->fields._u00CCu00CCu00CDu00CFu00CDu00CCu00CCu00CDu00CFu00CDu00CDu00CEu00CCu00CDu00CEu00CDu00CFu00CCu00CFu00CCu00CFu00CFu00CD_k__BackingField->fields._username_k__BackingField)
	{
		in_room = true;
	}

	join_original(class_ptr, player_ptr, method);
}

void on_player_leave(u00CEu00CEu00CCu00CEu00CFu00CEu00CFu00CFu00CEu00CFu00CCu00CFu00CEu00CEu00CFu00CEu00CCu00CFu00CFu00CFu00CDu00CFu00CC* class_ptr, u00CFu00CDu00CCu00CDu00CEu00CCu00CDu00CEu00CFu00CDu00CFu00CCu00CFu00CDu00CCu00CDu00CFu00CDu00CFu00CFu00CCu00CFu00CE* player_ptr, MethodInfo* method)
{
	std::cout << "leave";
	if (APIUser_get_CurrentUser(nullptr)->fields._username_k__BackingField == player_ptr->fields._u00CCu00CCu00CDu00CFu00CDu00CCu00CCu00CDu00CFu00CDu00CDu00CEu00CCu00CDu00CEu00CDu00CFu00CCu00CFu00CCu00CFu00CFu00CD_k__BackingField->fields._username_k__BackingField)
	{
		in_room = false;
	}

	leave_original(class_ptr, player_ptr, method);
}
