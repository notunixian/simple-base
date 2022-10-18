#include "pch-il2cpp.h"
#include "hook.h"
#include <Windows.h>
#include "includes/detours/detours.h"
#include <iostream>
#include "directx/directx.h"
#include <fstream>
#include "helpers.h"

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
	HOOKFUNC(u00CEu00CCu00CEu00CEu00CCu00CCu00CDu00CCu00CFu00CDu00CEu00CEu00CDu00CEu00CFu00CFu00CCu00CFu00CEu00CCu00CEu00CCu00CD_u00CCu00CEu00CCu00CCu00CDu00CEu00CEu00CDu00CCu00CCu00CFu00CFu00CCu00CCu00CCu00CDu00CCu00CEu00CCu00CCu00CFu00CCu00CD,
		on_player_join);

	HOOKFUNC(u00CEu00CCu00CEu00CEu00CCu00CCu00CDu00CCu00CFu00CDu00CEu00CEu00CDu00CEu00CFu00CFu00CCu00CFu00CEu00CCu00CEu00CCu00CD_u00CFu00CEu00CDu00CFu00CFu00CFu00CDu00CDu00CCu00CEu00CFu00CFu00CDu00CEu00CFu00CEu00CEu00CEu00CEu00CDu00CCu00CCu00CC,
		on_player_leave);

	HOOKFUNC(u00CEu00CDu00CEu00CDu00CCu00CCu00CFu00CCu00CCu00CEu00CCu00CFu00CFu00CCu00CFu00CCu00CEu00CEu00CCu00CEu00CCu00CFu00CE_u00CEu00CCu00CEu00CDu00CFu00CEu00CEu00CCu00CEu00CDu00CDu00CDu00CFu00CDu00CCu00CEu00CEu00CDu00CEu00CDu00CEu00CDu00CD,
		on_avatar_download);

	HOOKFUNC(InputManager_OnUpdate, update);


	DetourTransactionCommit();
}

// this will get fairly messy when doing lots of hooks, consider splitting into multiple folders/files.

#define join_original(a, b, c) u00CEu00CCu00CEu00CEu00CCu00CCu00CDu00CCu00CFu00CDu00CEu00CEu00CDu00CEu00CFu00CFu00CCu00CFu00CEu00CCu00CEu00CCu00CD_u00CCu00CEu00CCu00CCu00CDu00CEu00CEu00CDu00CCu00CCu00CFu00CFu00CCu00CCu00CCu00CDu00CCu00CEu00CCu00CCu00CFu00CCu00CD(a, b, c)
#define leave_original(a, b, c) u00CEu00CCu00CEu00CEu00CCu00CCu00CDu00CCu00CFu00CDu00CEu00CEu00CDu00CEu00CFu00CFu00CCu00CFu00CEu00CCu00CEu00CCu00CD_u00CFu00CEu00CDu00CFu00CFu00CFu00CDu00CDu00CCu00CEu00CFu00CFu00CDu00CEu00CFu00CEu00CEu00CEu00CEu00CDu00CCu00CCu00CC(a, b, c)
#define avatar_original(a, b, c, d) u00CEu00CDu00CEu00CDu00CCu00CCu00CFu00CCu00CCu00CEu00CCu00CFu00CFu00CCu00CFu00CCu00CEu00CEu00CCu00CEu00CCu00CFu00CE_u00CEu00CCu00CEu00CDu00CFu00CEu00CEu00CCu00CEu00CDu00CDu00CDu00CFu00CDu00CCu00CEu00CEu00CDu00CEu00CDu00CEu00CDu00CD(a, b, c, d)
extern bool in_room = false;

void on_player_join(app::u00CEu00CCu00CEu00CEu00CCu00CCu00CDu00CCu00CFu00CDu00CEu00CEu00CDu00CEu00CFu00CFu00CCu00CFu00CEu00CCu00CEu00CCu00CD * class_ptr, app::u00CEu00CFu00CEu00CDu00CEu00CEu00CCu00CDu00CDu00CFu00CDu00CFu00CEu00CEu00CDu00CDu00CEu00CFu00CCu00CFu00CFu00CCu00CE * player_ptr, MethodInfo * method)
{
	// this is an odd way of doing this, but i was just looking for something i could compare.
	if (APIUser_get_CurrentUser(nullptr)->fields._displayName_k__BackingField == player_ptr->fields._u00CDu00CCu00CFu00CFu00CFu00CCu00CEu00CDu00CEu00CEu00CFu00CEu00CDu00CFu00CFu00CCu00CEu00CDu00CDu00CEu00CEu00CFu00CD_k__BackingField->fields._displayName_k__BackingField)
	{
		in_room = true;
	}

	join_original(class_ptr, player_ptr, method);
}

void on_player_leave(app::u00CEu00CCu00CEu00CEu00CCu00CCu00CDu00CCu00CFu00CDu00CEu00CEu00CDu00CEu00CFu00CFu00CCu00CFu00CEu00CCu00CEu00CCu00CD * class_ptr, app::u00CEu00CFu00CEu00CDu00CEu00CEu00CCu00CDu00CDu00CFu00CDu00CFu00CEu00CEu00CDu00CDu00CEu00CFu00CCu00CFu00CFu00CCu00CE * player_ptr, MethodInfo * method)
{
	if (APIUser_get_CurrentUser(nullptr)->fields._displayName_k__BackingField == player_ptr->fields._u00CDu00CCu00CFu00CFu00CFu00CCu00CEu00CDu00CEu00CEu00CFu00CEu00CDu00CFu00CFu00CCu00CEu00CDu00CDu00CEu00CEu00CFu00CD_k__BackingField->fields._displayName_k__BackingField)
	{
		in_room = false;
	}

	leave_original(class_ptr, player_ptr, method);
}

UniTask_1_u00CCu00CDu00CEu00CCu00CCu00CFu00CEu00CCu00CDu00CCu00CCu00CCu00CDu00CDu00CEu00CCu00CFu00CDu00CCu00CFu00CFu00CFu00CC_ on_avatar_download(ApiAvatar * avi_ptr, u00CEu00CEu00CDu00CDu00CFu00CDu00CCu00CCu00CCu00CEu00CFu00CFu00CCu00CDu00CCu00CCu00CFu00CFu00CCu00CCu00CFu00CCu00CF_u00CDu00CFu00CCu00CEu00CFu00CCu00CCu00CEu00CFu00CCu00CEu00CFu00CDu00CEu00CFu00CCu00CEu00CCu00CCu00CFu00CDu00CFu00CE * unk_ptr, bool bool_1, MethodInfo * method)
{
	std::cout << "avihook: name->" << il2cppi_to_string(avi_ptr->fields._name_k__BackingField) << " | asset_url->" << il2cppi_to_string(avi_ptr->fields._assetUrl_k__BackingField) << std::endl;

	// will pipe the results with json pretty print and stuff like that into a file at some point, don't have a lot of time as of this commit.

	return avatar_original(avi_ptr, unk_ptr, bool_1, method);
}

bool flying = false;
// this is called on update -- ref: https://docs.unity3d.com/ScriptReference/MonoBehaviour.Update.html
void update(app::InputManager * __this, app::InputUpdateType__Enum updateType, app::InputEventBuffer * eventBuffer, MethodInfo * method)
{
	/* you would want to perform a lot of stuff here
	examples:
	fly, event exploits, anything that requires being set constantly or being called constantly.
	*/

	// toggle for flying, will disable the character controller collider so we can move on our own
	if (Input_GetKeyString(reinterpret_cast<app::String*>(il2cpp_string_new("left ctrl")), nullptr) && GetAsyncKeyState(0x46) & 1) // CTRL + F
	{
		flying = !flying;
		// kms
		const auto character_controller = reinterpret_cast<app::Collider*>(
			GameObject_GetComponentByName(
			Networking_get_LocalPlayer(nullptr)->fields.gameObject,
			reinterpret_cast<app::String*>(il2cpp_string_new("CharacterController")), nullptr)); 
		Collider_set_enabled(character_controller, !flying, nullptr);
	}

	// the actual flying
	// credits: azurilix
	if (flying && in_room)
	{
		// shit gets kinda ugly here
		const auto player_transform = GameObject_get_transform(Networking_get_LocalPlayer(nullptr)->fields.gameObject, nullptr);
		auto player_pos = Transform_get_position(player_transform, nullptr);
		const auto delta_time = Time_get_deltaTime(nullptr);
		const auto speed = Input_GetKeyString(reinterpret_cast<app::String*>(il2cpp_string_new("left shift")), nullptr) ? 10.0f : 5.0f;
		const auto vert_axis = Input_GetAxis(reinterpret_cast<app::String*>(il2cpp_string_new("Vertical")), nullptr);
		const auto horz_axis = Input_GetAxis(reinterpret_cast<app::String*>(il2cpp_string_new("Horizontal")), nullptr);


		player_pos.x += Transform_get_forward(player_transform, nullptr).x * (delta_time * vert_axis) * (speed * 2);
		player_pos.x += Transform_get_right(player_transform, nullptr).x * (delta_time * horz_axis) * (speed * 2);

		player_pos.y += Transform_get_forward(player_transform, nullptr).y * (delta_time * vert_axis) * (speed * 2);
		player_pos.y += Transform_get_right(player_transform, nullptr).y * (delta_time * horz_axis) * (speed * 2);

		player_pos.z += Transform_get_forward(player_transform, nullptr).z * (delta_time * vert_axis) * (speed * 2);
		player_pos.z += Transform_get_right(player_transform, nullptr).z * (delta_time * horz_axis) * (speed * 2);

		if (Input_GetKeyString(reinterpret_cast<app::String*>(il2cpp_string_new("q")), nullptr)) player_pos.y -= delta_time * (speed * 2);
		if (Input_GetKeyString(reinterpret_cast<app::String*>(il2cpp_string_new("e")), nullptr)) player_pos.y += delta_time * (speed * 2);

		Transform_set_position(player_transform, player_pos, nullptr);
	}


	InputManager_OnUpdate(__this, updateType, eventBuffer, method);
}