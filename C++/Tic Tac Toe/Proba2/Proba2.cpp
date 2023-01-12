// Proba2.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include "framework.h"
#include "Proba2.h"
#include <mmsystem.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;   // current instance
HWND form;
int dontetlen = 0;
POINT MousePos;
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PROBA2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROBA2));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROBA2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PROBA2);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; // Store instance handle in our global variable

	form = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!form)
	{
		return FALSE;
	}

	ShowWindow(form, nCmdShow);
	UpdateWindow(form);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
bool CPU = 0;
int lepeskoz;
int hatar;
POINT pontok;
int tabla[10][10];
int gyozelem = 0;
int elso_lepes;
bool zero = 1;
void kattintas1(POINT mouse);
void kattintas2(POINT mouse);
void tabla_kirajzol();
void init();
void bejeloles(int x, int y, int azonosito);
void palya();
void tabla_torles();
int dontetlenn(int dontetlen);
int kereses_gyozelem(int azonosito, int max_num);
int keres_fuggatlo_felfele(int azonosito, int max_num);
int keres_fuggatlo_lefele(int azonosito, int max_num);
int	keres_fugg(int azonosito, int max_num);
int	keres_horiz(int azonosito, int max_num);
int get_random_free_cells();
int keres_szabad_horiz(int azonosito, int max_num);
int keres_szabad_fugg(int azonosito, int max_num);
int keres_szabad_fuggatlo_lefele(int azonosito, int max_num);
int keres_szabad_fuggatlo_felfele(int azonosito, int max_num);
int kiegeszit_felkesz(int azonosito, int max_num, int tipus);
int gyors_ellenorzes(int azonosito, int max_num);
int MI_tamad();
int MI_blokkol();
void MI_kovetkezo_lepes();
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)


{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case 1:
		{
			::MessageBox(NULL, TEXT(" Játékos a játékos ellen "), TEXT(""), MB_OK);
			tabla_torles();
			CPU = 0;
			init();
			break;
		}
		case 2:
		{
			::MessageBox(NULL, TEXT(" CPU a játékos ellen "), TEXT(""), MB_OK);
			tabla_torles();
			CPU = 1;
			init();
			break;
		}
		case 3:
		{
			::MessageBox(NULL, TEXT(" Játék újraindítva  "), TEXT(""), MB_OK);
			tabla_torles();
			init();
			break;
		}
		case 4:
		{
			::MessageBox(NULL, TEXT(" Te az X-el vagy  "), TEXT(""), MB_OK);
			tabla_torles();
			zero = 0;
			init();
			break;
		}
		case 5:
		{
			::MessageBox(NULL, TEXT(" Te a 0-val vagy  "), TEXT(""), MB_OK);
			tabla_torles();
			zero = 1;
			init();
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_CREATE:
	{
		CreateWindow(TEXT("button"), TEXT("P v P"), WS_VISIBLE | WS_CHILD, 450, 10, 180, 55, hWnd, (HMENU)1, NULL, NULL);
		CreateWindow(TEXT("button"), TEXT("P v C"), WS_VISIBLE | WS_CHILD, 450, 70, 180, 55, hWnd, (HMENU)2, NULL, NULL);
		CreateWindow(TEXT("button"), TEXT("Restart"), WS_VISIBLE | WS_CHILD, 450, 130, 180, 55, hWnd, (HMENU)3, NULL, NULL);
		CreateWindow(TEXT("button"), TEXT("X"), WS_VISIBLE | WS_CHILD, 650, 10, 180, 55, hWnd, (HMENU)4, NULL, NULL);
		CreateWindow(TEXT("button"), TEXT("0"), WS_VISIBLE | WS_CHILD, 650, 70, 180, 55, hWnd, (HMENU)5, NULL, NULL);
		init();
		return 0;
		break;
	}
	case WM_LBUTTONDOWN:
		MousePos.x = LOWORD(lParam);
		MousePos.y = HIWORD(lParam);
		kattintas1(MousePos);
		return 0;
		break;
	case WM_RBUTTONDOWN:
		MousePos.x = LOWORD(lParam);
		MousePos.y = HIWORD(lParam);
		if (!CPU)
		{
			kattintas2(MousePos);
		}
		return 0;
		break;
	case WM_PAINT:
		tabla_kirajzol();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
void init()
{
	lepeskoz = (400 - 30) / 3;
	hatar = (4 * lepeskoz) + 5;
}
void tabla_torles()
{
	int i, j;
	gyozelem = 0;
	elso_lepes = 0;
	CPU = 0;
	dontetlen = 0;
	if (zero)
	{
		zero = 0;
	}
	for (i = 0; i < 3; ++i)
		for (j = 0; j < 3; ++j)
		{
			tabla[i][j] = 0;
		}
	palya();
}
void kattintas1(POINT mouse)
{
	if (gyozelem > 0)return;
	int x_adat = (mouse.x / lepeskoz);
	int y_adat = (mouse.y / lepeskoz);
	if (x_adat < 3 && y_adat < 3)
	{
		if (tabla[y_adat][x_adat] > 0) return;
		else
		{

			bejeloles(x_adat, y_adat, 1);

			if (kereses_gyozelem(1, 3) == 1)
			{
				::MessageBox(NULL, TEXT(" Nyert a 1. játékos  "), TEXT(""), MB_OK);
				gyozelem = 1;
				return;

			}
		}
	}
	if (CPU)
		MI_kovetkezo_lepes();
}

void kattintas2(POINT mouse)
{
	if (gyozelem > 0) return;
	int x_adat = (mouse.x / lepeskoz);
	int y_adat = (mouse.y / lepeskoz);
	if (x_adat < 3 && y_adat < 3)
	{
		if (tabla[y_adat][x_adat] > 0) return;
		else
		{

			bejeloles(x_adat, y_adat, 2);

			if (kereses_gyozelem(2, 3) == 1)
			{
				::MessageBox(NULL, TEXT(" Nyert a 2. játékos  "), TEXT(""), MB_OK);
				gyozelem = 1;
				return;
			}
		}
	}
}



void bejeloles(int x, int y, int azonosito)
{
	tabla[y][x] = azonosito;
	tabla_kirajzol();
	dontetlen++;
	dontetlenn(dontetlen);
}
int dontetlenn(int dontetlen)
{
	if (!gyozelem)
		if (dontetlen == 9) {
			::MessageBox(NULL, TEXT(" Döntetlen "), TEXT(""), MB_OK);

			return 1;
		}
}
void palya()
{

	int i;
	PAINTSTRUCT ps;
	HBRUSH hBrush;
	RECT rect;
	HDC hdc2;
	HPEN vonalstilus;

	{
		vonalstilus = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));

		hdc2 = GetDC(form);
		BeginPaint(form, &ps);
		hBrush = CreateSolidBrush(RGB(204, 204, 204));
		SetRect(&rect, 0, 0, 400, 600);
		FillRect(hdc2, &rect, hBrush);
		EndPaint(form, &ps);

		SelectObject(hdc2, vonalstilus);
		for (i = 5; i < hatar; i += lepeskoz)
		{
			MoveToEx(hdc2, i, 5, NULL);
			LineTo(hdc2, i, hatar - lepeskoz);
		}
		for (i = 5; i < hatar; i += lepeskoz)
		{
			MoveToEx(hdc2, 5, i, NULL);
			LineTo(hdc2, hatar - lepeskoz, i);
		}
		ReleaseDC(form, hdc2);
		DeleteObject(vonalstilus);
	}
}
void tabla_kirajzol()
{


	int x;
	int y;
	int korx, kory, kor_szelesseg;

	PAINTSTRUCT  ps;
	HBRUSH hBrush;
	HDC hdc2;
	HPEN vonalstilus;

	vonalstilus = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	hBrush = CreateSolidBrush(RGB(34, 204, 204));

	hdc2 = GetDC(form);
	BeginPaint(form, &ps);
	SelectObject(hdc2, vonalstilus);

	palya();
	for (y = 0; y < 3; ++y)
		for (x = 0; x < 3; ++x)
		{
			korx = x * lepeskoz + 5 + (lepeskoz / 2);
			kory = y * lepeskoz + 5 + (lepeskoz / 2);
			kor_szelesseg = (lepeskoz / 2) - 5;

			if (tabla[y][x] > 0)
			{

				if (tabla[y][x] == 1)
				{


					hBrush = CreateSolidBrush(RGB(204, 204, 204)); SelectObject(hdc2, hBrush);
					Ellipse(hdc2, korx - kor_szelesseg, kory - kor_szelesseg, korx + kor_szelesseg, kory + kor_szelesseg);

				}

				/*if (tabla[y][x] == 2)
				{
					if (zero)
					{
						hBrush = CreateSolidBrush(RGB(204, 204, 34)); SelectObject(hdc2, hBrush);
						MoveToEx(hdc2, korx + kor_szelesseg, kory + kor_szelesseg, NULL);
						LineTo(hdc2, korx - kor_szelesseg, kory - kor_szelesseg);
						MoveToEx(hdc2, korx - kor_szelesseg, kory + kor_szelesseg, NULL);
						LineTo(hdc2, korx + kor_szelesseg, kory - kor_szelesseg);
					}
					else
					{
						hBrush = CreateSolidBrush(RGB(204, 204, 204)); SelectObject(hdc2, hBrush);
						Ellipse(hdc2, korx - kor_szelesseg, kory - kor_szelesseg, korx + kor_szelesseg, kory + kor_szelesseg);
					}
				}
				*/
				if (tabla[y][x] == 2)
				{

					hBrush = CreateSolidBrush(RGB(204, 204, 34)); SelectObject(hdc2, hBrush);
					MoveToEx(hdc2, korx + kor_szelesseg, kory + kor_szelesseg, NULL);
					LineTo(hdc2, korx - kor_szelesseg, kory - kor_szelesseg);
					MoveToEx(hdc2, korx - kor_szelesseg, kory + kor_szelesseg, NULL);
					LineTo(hdc2, korx + kor_szelesseg, kory - kor_szelesseg);
				}



			}
		}
	EndPaint(form, &ps);
	ReleaseDC(form, hdc2);
	DeleteObject(hBrush);
	DeleteObject(vonalstilus);
}

int keres_horiz(int azonosito, int max_num)
{
	int x;
	int y;
	int x2;
	int szamlalo;

	for (y = 0; y < 3; ++y)
		for (x = 0; x < 3; ++x)
		{
			if (tabla[y][x] == azonosito)
			{
				pontok.x = x;
				pontok.y = y;
				szamlalo = 0;									for (x2 = x; x2 < 3; ++x2)
				{
					if (tabla[y][x2] == azonosito) ++szamlalo;
					else break;
					if (szamlalo == max_num) return 1;
				}
			}
		}
	return -1;
}


int keres_fugg(int azonosito, int max_num)
{
	int y;
	int x;
	int y2;
	int szamlalo;

	for (x = 0; x < 3; ++x)
		for (y = 0; y < 3; ++y)
		{
			if (tabla[y][x] == azonosito)//itt csere
			{
				pontok.x = x;
				pontok.y = y;
				szamlalo = 0;
				for (y2 = y; y2 < 3; ++y2)
				{
					if (tabla[y2][x] == azonosito) ++szamlalo;
					else break;
					if (szamlalo == max_num) return 1;
				}
			}
		}
	return -1;
}


int keres_fuggatlo_lefele(int azonosito, int max_num)
{
	int y;
	int x;
	int y2;
	int x2;//betoldas
	int szamlalo;

	for (x = 0; x < 3; ++x)
		for (y = 0; y < 3; ++y)
		{
			if (tabla[y][x] == azonosito)//itt csere
			{
				pontok.x = x;
				pontok.y = y;
				x2 = x;//betoldas
				szamlalo = 0;
				for (y2 = y; y2 < 3; ++y2, ++x2)//betoldas
				{
					if (tabla[y2][x2] == azonosito) ++szamlalo;
					else break;
					if (szamlalo == max_num) return 1;
				}
			}
		}
	return -1;
}


int keres_fuggatlo_felfele(int azonosito, int max_num)
{
	int y;
	int x;
	int y2;
	int x2;//betoldas
	int szamlalo;

	for (x = 0; x < 3; ++x)
		for (y = 0; y < 3; ++y)
		{
			if (tabla[y][x] == azonosito)//itt csere
			{
				pontok.x = x;
				pontok.y = y;
				x2 = x;//betoldas
				szamlalo = 0;
				for (y2 = y; y2 >= 0; --y2, ++x2)//betoldas
				{
					if (tabla[y2][x2] == azonosito) ++szamlalo;
					else break;
					if (szamlalo == max_num) return 1;
				}
			}
		}
	return -1;
}
int kereses_gyozelem(int azonosito, int max_num)
{
	if (keres_horiz(azonosito, max_num) == 1) return 1;
	if (keres_fugg(azonosito, max_num) == 1) return 1;
	if (keres_fuggatlo_lefele(azonosito, max_num) == 1) return 1;
	if (keres_fuggatlo_felfele(azonosito, max_num) == 1) return 1;


	return -1;
}

int get_random_free_cells()
{
	int i;
	int j = 0;//jelzi, ha nincs üres cella
	int x = 0;
	int y = 0;

	for (y = 0; y < 3; ++y)
		for (y = 0; y < 3; ++y)
		{
			if (tabla[y][x] == 0)
			{
				pontok.x = x;
				pontok.y = y;
				j = 1;
			}
		}

	if (j == 0)
	{
		return -1;
		::MessageBox(NULL, TEXT(" Döntetlen!  "), TEXT(""), MB_DEFBUTTON2
		);
	}

	x = rand() % 3;
	y = rand() % 3;
	pontok.x = x;
	pontok.y = y;

	while (tabla[x][y] != 0)
	{
		x = rand() % 3;
		y = rand() % 3;
		pontok.x = x;
		pontok.y = y;
	}
	return 1;
}

//*******************
//MI vízszintes szabad cella keresés
//*******************
int keres_szabad_horiz(int azonosito, int max_num)
{
	int x;
	int y;
	int x2;
	int szamlalo;

	for (y = 0; y < 3; ++y)
		for (x = 0; x < 3; ++x)
		{
			if (tabla[y][x] == azonosito)
			{
				szamlalo = 0;									for (x2 = x; x2 < 3; ++x2)
				{
					if (szamlalo == max_num) break;//felesleges körök kiiktatása
					if (tabla[y][x2] == azonosito) ++szamlalo;
					else break;
					if (szamlalo == max_num)
					{
						if (x > 0)
						{
							if (tabla[y][x - 1] == 0)
							{
								pontok.x = x;
								pontok.y = y;
								return 1;
							}
						}
						if (x < (3 - max_num))
						{
							if (tabla[y][x + max_num] == 0)
							{
								pontok.x = x;
								pontok.y = y;
								return 2;
							}
						}
					}
				}
			}
		}
	return -1;
}

//*******************
//MI függõleges szabad cella keresés
//*******************
int keres_szabad_fugg(int azonosito, int max_num)
{
	int y;
	int x;
	int y2;
	int szamlalo;

	for (x = 0; x < 3; ++x)
		for (y = 0; y < 3; ++y)
		{
			if (tabla[y][x] == azonosito)
			{
				szamlalo = 0;
				for (y2 = y; y2 < 3; ++y2)
				{
					if (szamlalo == max_num) break;
					if (tabla[y2][x] == azonosito) ++szamlalo;
					else break;
					if (szamlalo == max_num)
					{
						if (y > 0)
						{
							if (tabla[y - 1][x] == 0)
							{
								pontok.x = x;
								pontok.y = y;
								return 1;
							}
						}
						if (y < (3 - max_num))
						{
							if (tabla[y + max_num][x] == 0)
							{
								pontok.x = x;
								pontok.y = y;
								return 2;
							}
						}
					}
				}
			}
		}
	return -1;
}

//*******************
//MI átlós szabad cella keresés
//*******************
int keres_szabad_fuggatlo_lefele(int azonosito, int max_num)
{
	int y;
	int x;
	int y2;
	int x2;//betoldas
	int szamlalo;

	for (x = 0; x < 3; ++x)
		for (y = 0; y < 3; ++y)
		{
			if (tabla[y][x] == azonosito)
			{
				x2 = x;//betoldas
				szamlalo = 0;
				for (y2 = y; y2 < 3; ++y2, ++x2)
				{
					if (szamlalo == max_num) break;
					if (tabla[y2][x2] == azonosito) ++szamlalo;
					else break;
					if (szamlalo == max_num)
					{
						if ((y > 0) && (x > 0))
						{
							if (tabla[y - 1][x - 1] == 0)
							{
								pontok.x = x;
								pontok.y = y;
								return 1;
							}
						}
						if ((y < (3 - max_num)) && (x < (3 - max_num)))
						{
							if (tabla[y + max_num][x + max_num] == 0)
							{
								pontok.x = x;
								pontok.y = y;
								return 2;
							}
						}
					}
				}
			}
		}
	return -1;
}

//*******************
//MI átlós szabad cella keresés
//*******************
int keres_szabad_fuggatlo_felfele(int azonosito, int max_num)
{
	int y;
	int x;
	int y2;
	int x2;//betoldas
	int szamlalo;

	for (x = 0; x < 3; ++x)
		for (y = 0; y < 3; ++y)
		{
			if (tabla[y][x] == azonosito)
			{
				x2 = x;//betoldas
				szamlalo = 0;
				for (y2 = y; y2 >= 0; --y2, ++x2)
				{
					if (szamlalo == max_num) break;
					if (tabla[y2][x2] == azonosito) ++szamlalo;
					else break;
					if (szamlalo == max_num)
					{
						if ((y > (max_num - 1)) && (x < (3 - max_num)))
						{
							if (tabla[y - max_num][x + max_num] == 0)
							{
								pontok.x = x;
								pontok.y = y;
								return 1;
							}
						}
						if ((y < 2) && (x > 0))
						{
							if (tabla[y + 1][x - 1] == 0)
							{
								pontok.x = x;
								pontok.y = y;
								return 2;
							}
						}
					}
				}
			}
		}
	return -1;
}

//*******************
//MI építkezési lépés
//*******************
int kiegeszit_felkesz(int azonosito, int max_num, int tipus)
{
	int eredmeny;

	if (tipus == 1)
	{
		eredmeny = keres_szabad_horiz(azonosito, max_num);
		if (eredmeny == 1) { bejeloles(pontok.x - 1, pontok.y, 2); return eredmeny; }
		else if (eredmeny == 2) { bejeloles(pontok.x + max_num, pontok.y, 2); return eredmeny; }
	}
	else if (tipus == 2)
	{
		eredmeny = keres_szabad_fugg(azonosito, max_num);
		if (eredmeny == 1) { bejeloles(pontok.x, pontok.y - 1, 2); return eredmeny; }
		else if (eredmeny == 2) { bejeloles(pontok.x, pontok.y + max_num, 2); return eredmeny; }
	}
	else if (tipus == 3)
	{
		eredmeny = keres_szabad_fuggatlo_lefele(azonosito, max_num);
		if (eredmeny == 1) { bejeloles(pontok.x - 1, pontok.y - 1, 2); return eredmeny; }
		else if (eredmeny == 2) { bejeloles(pontok.x + max_num, pontok.y + max_num, 2); return eredmeny; }
	}
	else if (tipus == 4)
	{
		eredmeny = keres_szabad_fuggatlo_felfele(azonosito, max_num);
		if (eredmeny == 1) { bejeloles(pontok.x + max_num, pontok.y - max_num, 2); return eredmeny; }
		else if (eredmeny == 2) { bejeloles(pontok.x - 1, pontok.y + 1, 2); return eredmeny; }
	}
	return -1;
}

//*******************
//MI építkezési lehetõség keresése
//*******************
int gyors_ellenorzes(int azonosito, int max_num)
{//-1:nincsen szabad, 1-van szabad
	if (kiegeszit_felkesz(azonosito, max_num, 1) == -1)
	{
		if (kiegeszit_felkesz(azonosito, max_num, 2) == -1)
		{
			if (kiegeszit_felkesz(azonosito, max_num, 3) == -1)
			{
				if (kiegeszit_felkesz(azonosito, max_num, 4) == -1) return -1;
				else return 1;
			}

			else return 1;
		}
		else return 1;
	}
	else return 1;
}

//*******************
//MI építkezõ-támadó lépése, ha lehetséges
//*******************
int MI_tamad()
{
	int i;
	int eredmeny;//1 lepes tortent,-1-nem tortent lepes, lehet blokkolni

	eredmeny = gyors_ellenorzes(2, 2);
	return eredmeny;
}

//*******************
//MI védekezése
//*******************
int MI_blokkol()
{
	int i;
	int eredmeny = 1;//-1 lepes tortent,1-nem tortent lepes, lehet tamadni

	for (i = 2; i > 0; --i)
	{
		if (kiegeszit_felkesz(1, i, 1) == -1)
		{
			if (kiegeszit_felkesz(1, i, 2) == -1)
			{
				if (kiegeszit_felkesz(1, i, 3) == -1)
				{
					if (kiegeszit_felkesz(1, i, 4) != -1) { eredmeny = -1; break; }
				}
				else { eredmeny = -1; break; }
			}
			else { eredmeny = -1; break; }
		}
		else { eredmeny = -1; break; }
	}
	return eredmeny;
}

//*******************
//MI védekezés, vagy támadás eldöntése
//*******************
void MI_kovetkezo_lepes()
{
	if (elso_lepes == 0)
	{
		elso_lepes = 1;
		if (get_random_free_cells() == 1) bejeloles(pontok.x, pontok.y, 2);
	}
	else
	{
		if (MI_tamad() == -1) MI_blokkol();
	}

	if (kereses_gyozelem(2, 3) == 1)
	{
		MessageBox(NULL, TEXT("A CPU nyert!"), TEXT("A CPU nyert!"), NULL);
		gyozelem = 2;
		return;
	}
}