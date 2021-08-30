#include "window.h"
//dll
LRESULT CALLBACK windowProcedure(
	window::wnd   hwnd    // Window Handle (Window object)
	, UINT   msg     // Window Message  
	, WPARAM wParam  // Additional message information
	, LPARAM lParam  // Additional message information 
)
 {
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOVE:
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

bool window::initwindow(wndc wc)
{
	wc.lpszClassName = L"hi";
	wc.lpfnWndProc = windowProcedure;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)5; // (HBRUSH) CreateSolidBrush(RGB(10, 20, 30)); // 
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBoxW(NULL, L"registration :(", L"oof", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	return true;
}
window::brush window::createbrush(rgb color)
{
	return CreateSolidBrush(color);
}
HWND window::createwindow(wnd hwnd, wndc wc, const char title[], int x, int y, int width, int height) {
	return CreateWindow(L"hi", (LPCWSTR)title, WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, hInstance, nullptr);
}
void window::showwindow(wnd hwnd)
{
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}
void window::message_handler(msg& msg)
{
	if (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
void window::line(renderer render, int x, int y, int x1, int y1, rgb color, int style, int width) {
	pens pen = CreatePen(style, width, color);
	HGDIOBJ original = SelectObject(render, pen);
	MoveToEx(render, x, y, (LPPOINT)NULL);
	SelectObject(render, pen);
	LineTo(render, x1, y1);
	SelectObject(render, original);
	DeleteObject(pen);
}
void window::move(renderer render, int x, int y)
{
	MoveToEx(render, x, y, (LPPOINT)NULL);
}
void window::polybezier(renderer render, const points* point, DWORD numpoints, rgb color, int style, int width)
{
	pens pen = CreatePen(style, width, color);
	HGDIOBJ original = SelectObject(render, pen);
	SelectObject(render, pen);
	PolyBezier(render, point, numpoints);
	SelectObject(render, original);
	DeleteObject(pen);
}
void window::polyline(renderer render, const points* point, int numpoints, rgb color, int style, int width)
{
	pens pen = CreatePen(style, width, color);
	HGDIOBJ original = SelectObject(render, pen);
	SelectObject(render, pen);
	Polyline(render, point, numpoints);
	SelectObject(render, original);
	DeleteObject(pen);
}
void window::ellipse(renderer render, int left, int top, int right, int bottom, rgb color, int style, int width)
{
	pens pen = CreatePen(style, width, color);
	HGDIOBJ original = SelectObject(render, pen);
	SelectObject(render, pen);
	Ellipse(render, left, top, right, bottom);
	SelectObject(render, original);
	DeleteObject(pen);
}
void window::rect(renderer render, int left, int top, int right, int bottom, rgb color, int style, int width)
{
	pens pen = CreatePen(style, width, color);
	HGDIOBJ original = SelectObject(render, pen);
	SelectObject(render, pen);
	Rectangle(render, left, top, right, bottom);
	SelectObject(render, original);
	DeleteObject(pen);
}
void window::fillrect(renderer render, const rectangle* rect, brush brush)
{
	FillRect(render, rect, brush);
}
void window::polygon(renderer render, const points* point, int numvertices, rgb color, int style, int width)
{
	pens pen = CreatePen(style, width, color);
	HGDIOBJ original = SelectObject(render, pen);
	SelectObject(render, pen);
	Polygon(render, point, numvertices);
	SelectObject(render, original);
	DeleteObject(pen);
}
window::renderer window::draw(wnd wnd) {
	return GetDC(wnd);
}

bool window::stopdraw(wnd wnd, renderer render) {
	ReleaseDC(wnd, render);
	return true;
}
void window::arc(renderer render, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, rgb color, int style, int width) {
	pens pen = CreatePen(style, width, color);
	HGDIOBJ original = SelectObject(render, pen);
	SelectObject(render, pen);
	Arc(render, x1, y1, x2, y2, x3, y3, x4, y4);
	SelectObject(render, original);
	DeleteObject(pen);
}