#include "Header.h"


// Прототип функции DlgProc.
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{

	MSG msg;	// структура.
				// создаём главное окно приложения на основе немодального диалога
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	// Отображаем окно	
	ShowWindow(hDialog, nCmdShow);


	//Запускаем цикл обработки сообщений
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



BOOL CALLBACK DlgProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	static HWND hNewGame;
	static HWND hWalkFirst;
	static HWND hEasyHard;

	/*static HWND hButton_xo_1;*/
	static HWND hButton_xo[9];

	static HBITMAP hCross, hRound;

	// Меняем стиль класса кнопки.
	/*HBRUSH whiteBrush = CreateSolidBrush(RGB(0, 255, 0));
	UINT styleButton_xo = GetClassLong(hButton_xo[0], GCL_STYLE);
	SetClassLong(hButton_xo[0], GCL_STYLE, styleButton_xo | (LONG)whiteBrush);*/
	//static HBRUSH whiteBrush;

	switch (uMessage)
	{
	case WM_CLOSE:
		// Закрываем немодальный диалог.
		DestroyWindow(hWnd); // разрушаем окно.
		PostQuitMessage(0); // останавливаем цикл обработки сообщений.
		return TRUE;

	case WM_PAINT:
	//	/*MessageBox(hWnd, L"wm paint",
	//		L"работает", MB_OK | MB_ICONINFORMATION);*/
		return TRUE;
	//case WM_CTLCOLORBTN:
		/*clrs = RGB(0, 255, 0);
		whiteBrush = CreateSolidBrush(clrs);
		return LRESULT(whiteBrush);*/

	case WM_INITDIALOG:
		// Получаем Handle.
		hNewGame = GetDlgItem(hWnd, IDC_BUTTON_NewGame);
		hWalkFirst = GetDlgItem(hWnd, IDC_CHECK_WalkFirst);
		// Получаем Handle радиоКнопки.					// TODO delete !?
		hEasyHard = GetDlgItem(hWnd, IDC_RADIO_EasyLevel);	// TODO если CheckRadioButton то наверно delete
		// Получаем дескрипторы кнопок (хо).
		/*hButton_xo_1 = GetDlgItem(hWnd, IDC_BUTTON_xo_1);*/
		for (int i = 0; i < 9; i++)
		{
			hButton_xo[i] = GetDlgItem(hWnd, IDC_BUTTON_xo_1 + i);
		}

		// Загружаем bmp "крестик", и "нолик" и получаем их Handle.
		hCross = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_x));
		hRound = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_x));

		// Изначально выбран "легкий уровень".
		CheckRadioButton(hWnd, IDC_RADIO_EasyLevel, IDC_RADIO_HardLevel, IDC_RADIO_EasyLevel);
		// Изначально флажок "ходить первым" снят.
		SendMessage(hWalkFirst, BM_SETCHECK, WPARAM(BST_UNCHECKED), NULL);

	

		// Загружаем bmp	//  TODO потом при нажатии кнопок
		SendMessage(hButton_xo[0], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hCross));
		

		return TRUE;

	case WM_COMMAND:
		//
		if (LOWORD(wParam) == IDC_BUTTON_NewGame)
		{
			MessageBox(hWnd, L"Нажал кнопку \"Новая игра\"",
				L"работает", MB_OK | MB_ICONINFORMATION);
		}
		else if (LOWORD(wParam) == IDC_RADIO_EasyLevel)
		{
			MessageBox(hWnd, L"Нажал радио \"Легкий уровень\"",
				L"работает", MB_OK | MB_ICONINFORMATION);
		}
		else if (LOWORD(wParam) == IDC_RADIO_HardLevel)
		{
			MessageBox(hWnd, L"Нажал радио \"Сложный уровень\"",
				L"работает", MB_OK | MB_ICONINFORMATION);
		}
		else if (LOWORD(wParam) == IDC_CHECK_WalkFirst)
		{
			MessageBox(hWnd, L"Нажал флажок \"Ходить первым\"",
				L"работает", MB_OK | MB_ICONINFORMATION);
		}


		if (LOWORD(wParam) == IDC_BUTTON_xo_1)
		{
			//SendMessage(hButton_xo_1, BM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)GetDlgItem(hWnd, IDB_BITMAP_x));	// TODO re
		}

		return TRUE;

	}

	return FALSE;
}