#include "pch-il2cpp.h"
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "includes/kiero/kiero.h"
#include "includes/imgui/imgui.h"
#include "includes/imgui/imgui_impl_win32.h"
#include "includes/imgui/imgui_impl_dx11.h"
#include <sstream>
#include <helpers.h>
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
extern bool in_room;
app::Camera* camera = nullptr;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

void esp_run()
{
	if (in_room && camera != nullptr)
	{
		auto players = app::VRCPlayerApi_get_AllPlayers(nullptr);
		auto player_amount = app::List_1_VRC_SDKBase_VRCPlayerApi__get_Count(players, nullptr);
		auto draw = ImGui::GetForegroundDrawList();
		for (auto i = 1; i < player_amount; i++)
		{
			const auto player = app::List_1_VRC_SDKBase_VRCPlayerApi__get_Item(players, i, nullptr);
			
			// forgot this check here, would cause a crash as sometimes i would access a player that was null.
			if (player == nullptr) return;
			if (player->fields.gameObject == nullptr) return;

			if (player->fields.mPlayerId == app::Networking_get_LocalPlayer(nullptr)->fields.mPlayerId) return;
			if (app::GameObject_get_activeSelf(player->fields.gameObject, nullptr) == false) return;

			const auto player_transform = app::GameObject_get_transform(player->fields.gameObject, nullptr);
			const auto player_pos = app::Transform_get_position(player_transform, nullptr);
			const auto player_chest = app::VRCPlayerApi_GetBonePosition(player, (app::HumanBodyBones__Enum)0x00000008, nullptr);
			const auto player_head = app::VRCPlayerApi_GetBonePosition(player, (app::HumanBodyBones__Enum)0x0000000A, nullptr);
			const auto player_feet = app::VRCPlayerApi_GetBonePosition(player, (app::HumanBodyBones__Enum)0x00000005, nullptr);
			const auto w2s_chest = app::Camera_WorldToScreenPoint_1(camera, player_chest, nullptr);
			const auto w2s_head = app::Camera_WorldToScreenPoint_1(camera, player_head, nullptr);
			const auto w2s_feet = app::Camera_WorldToScreenPoint_1(camera, player_head, nullptr);

			// tracers
			ImGuiIO& io = ImGui::GetIO();
			if (w2s_chest.z > 1.f)
			{
				const float h = w2s_chest.y / 32.f;
				const float w = h / 4.f;
				const float l = w2s_chest.x - w;
																							 // minus display size from w2s
																							 // ref: https://forum.unity.com/threads/worldtoscreenpoint-doesnt-work-on-y-screen-axis.34161/
				draw->AddLine(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y), ImVec2(l, io.DisplaySize.y - w2s_chest.y), ImColor(255, 255, 255, 255), 2.0F);
			}

			// names
			if (w2s_feet.z > 1.f)
			{
				const float h = w2s_head.y - w2s_feet.y;
				const float w = h / 4.f;
				const float l = w2s_feet.x - w;
				const float r = w2s_feet.x + w;

				draw->AddText(ImVec2(l, io.DisplaySize.y - w2s_head.y + h + 20.f), IM_COL32_WHITE, il2cppi_to_string(player->fields.displayName).c_str(), nullptr);
			}
			

			// simple playerlist that draws from bottom left and goes up per player.
			ImVec2 draw_pos = ImVec2{ 5, io.DisplaySize.y - (float)15 * i };
			std::ostringstream oss;

			// using oss here isn't really that great imo but i don't feel like using std::format and such.
			oss << il2cppi_to_string(player->fields.displayName) << " | [" << (int)player_pos.x << ", " << (int)player_pos.y << ", " << (int)player_pos.z << "]";
			draw->AddText(draw_pos, IM_COL32_WHITE, oss.str().c_str());
		}
	}
}


bool init = false;
bool show_demo_window = true;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			camera = app::Camera_get_current(nullptr);
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		show_demo_window = !show_demo_window;
	}

	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}

	esp_run();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::SetNextWindowPos(ImVec2(5, 5));
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Begin("##WATERMARK", (bool*)0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);
	{
		ImGui::Text("simple-base | fps: %i", (int)io.Framerate);
	}
	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

void do_directx_hooks()
{
	if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
	{
		kiero::bind(8, (void**)&oPresent, hkPresent);
	}
}