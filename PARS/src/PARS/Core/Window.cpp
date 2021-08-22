#include "stdafx.h"
#include "PARS/Core/Window.h"
#include "PARS/Core/Application.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Layer/LayerManager.h"

#include "imgui.h"
#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_dx12.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace PARS
{
    UPtr<WindowInfo> Window::s_WindowInfo = nullptr;

    Window::Window(const std::wstring& title)
        : m_Title(title)
    {
        Initialize();
    }
    
    void Window::Initialize()
    {
        s_WindowInfo = CreateUPtr<WindowInfo>();

        s_WindowInfo->m_hInstance = GetModuleHandle(NULL);

        WNDCLASSEXW wcex;

        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = s_WindowInfo->m_hInstance;
        wcex.hIcon = LoadIcon(s_WindowInfo->m_hInstance, IDI_WINLOGO);
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = m_Title.c_str();
        wcex.hIconSm = wcex.hIcon;

        RegisterClassExW(&wcex);

        int posX = (GetSystemMetrics(SM_CXSCREEN) - s_WindowInfo->m_Width) / 2;
        int posY = (GetSystemMetrics(SM_CYSCREEN) - s_WindowInfo->m_Height) / 2;

        s_WindowInfo->m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_Title.c_str(), m_Title.c_str(),
            WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
            0, 0, s_WindowInfo->m_Width, s_WindowInfo->m_Height, NULL, NULL, s_WindowInfo->m_hInstance, NULL);

        m_InputManager = CreateUPtr<InputManager>(s_WindowInfo->m_hwnd);

        ShowWindow(s_WindowInfo->m_hwnd, SW_SHOW);
        SetForegroundWindow(s_WindowInfo->m_hwnd);
        SetFocus(s_WindowInfo->m_hwnd);
    }

    void Window::Shutdown()
    {
        DestroyWindow(s_WindowInfo->m_hwnd);
        UnregisterClass(m_Title.c_str(), s_WindowInfo->m_hInstance);
    }

    void Window::Update()
    {
        m_InputManager->Update();
    }

    void Window::AddFpsToWindowName(UINT fps)
    {
        std::wstring name = m_Title + L" (FPS : " + std::to_wstring(fps) + L")";
        SetWindowTextW(s_WindowInfo->m_hwnd, name.c_str());
    }

    void WindowInfo::ChangeWindowInfo()
    {
        const auto& directX = DirectX12::GetDirectX12();
        if (directX != nullptr)
            directX->ResizeWindow();
    }

    LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hwnd, message, wParam, lParam))
            return true;

        LRESULT result = NULL;
        const auto& manager = Input::GetInputManager();
        const auto& layerManager = LayerManager::GetLayerManager();
        const auto& factory = RenderFactory::GetRenderFactory();

        switch (message)
        {
        case WM_SIZE:
        { 
            if (wParam == SIZE_MINIMIZED)
            {
                Application::SetAppState(AppState::Paused);
            }
            else if (wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED)
            {
                Application::SetAppState(AppState::Active);
                s_WindowInfo->m_Width = LOWORD(lParam);
                s_WindowInfo->m_Height = HIWORD(lParam);
                s_WindowInfo->ChangeWindowInfo();
                if (layerManager != nullptr)
                {
                    layerManager->ResizeLayer();
                }
            }
        }
        break;
        case WM_MOVE:
            if (layerManager != nullptr)
            {
                layerManager->ResizeLayer();
            }
            break;
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
            KeyCallback(manager, message, wParam, lParam);
            break;        
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_MOUSEMOVE:
            MouseButtonCallback(manager, message, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        default:
           result = DefWindowProc(hwnd, message, wParam, lParam);
        }

        return result;
    }
}

