#pragma once
#include <Windows.h>

typedef WNDCLASSEX wndc;
typedef HWND wnd;
typedef MSG msg;
typedef PAINTSTRUCT paint;
typedef HDC renderer;
typedef HPEN pens;
typedef HGDIOBJ obj;
typedef COLORREF rgb;
typedef POINT points;
typedef RECT rectangle;
typedef HBRUSH brush;

#define solidpen PS_SOLID
#define dashpen PS_DASH
#define dotpen PS_DOT
#define dashdotpen PS_DASHDOT
#define dashdotdot PS_DASHDOTDOT
#define nullpen PS_NULL

class window
{
public:
    bool initwindow(wndc wc);
    wnd createwindow(wnd wnd, wndc wc, LPCSTR title, int x, int y, int width, int height);
    void showwindow(wnd wnd);
    void message_handler(msg &msg);
    renderer draw(wnd wnd);
    bool stopdraw(wnd wnd, renderer render);
    brush createbrush(rgb color);

    //drawing functions
    void line(renderer render, int x, int y, int x1, int y1, rgb color, int style, int width);
    void arc(renderer render, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, rgb color, int style, int width);
    void move(renderer render, int x, int y);
    void polybezier(renderer render, const points *point, DWORD numpoints, rgb color, int style, int width);
    void polyline(renderer render, const points *point, int numpoints, rgb color, int style, int width);

    //shapes
    void ellipse(renderer render, int left, int top, int right, int bottom, rgb color, int style, int width);
    void rect(renderer render, int left, int top, int right, int bottom, rgb color, int style, int width);
    void fillrect(renderer render, const rectangle* rect, brush brush);
    void polygon(renderer render, const points *point, int numvertices, rgb color, int style, int width);



private:
    HINSTANCE hInstance = GetModuleHandle(NULL);

};

