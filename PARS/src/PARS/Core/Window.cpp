#include "stdafx.h"
#include "PARS/Core/Window.h"

namespace PARS
{
    Window::Window(const std::wstring& title, UINT width, UINT height)
        : m_Title(title)
        , m_Width(width)
        , m_Height(height)
    {
        Initialize();
    }
    
    void Window::Initialize()
    {
        m_hInstance = GetModuleHandle(NULL);

        WNDCLASSEXW wcex;

        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = m_hInstance;
        wcex.hIcon = LoadIcon(m_hInstance, IDI_WINLOGO);
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = m_Title.c_str();
        wcex.hIconSm = wcex.hIcon;

        RegisterClassExW(&wcex);

        int posX = (GetSystemMetrics(SM_CXSCREEN) - m_Width) / 2; 
        int posY = (GetSystemMetrics(SM_CYSCREEN) - m_Height) / 2;

        m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_Title.c_str(), m_Title.c_str(),
            WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_BORDER,
            posX, posY, m_Width, m_Height, NULL, NULL, m_hInstance, NULL);

        ShowWindow(m_hwnd, SW_SHOW);
        SetForegroundWindow(m_hwnd);
        SetFocus(m_hwnd);
    }

    LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }

        case WM_CLOSE:
        {
            PostQuitMessage(0);
            return 0;
        }
        default:
        {
            return DefWindowProc(hwnd, message, wParam, lParam);
        }
        }
    }
}

