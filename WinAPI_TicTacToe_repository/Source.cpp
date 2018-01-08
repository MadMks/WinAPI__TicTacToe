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
	static HWND hText;

	/*static HWND hButton_xo_1;*/
	static HWND hButton_xo[9];

	static HBITMAP hCross, hRound;
	static HBITMAP hEmpty;	// handle не существующей картинки.

	// Меняем стиль класса кнопки.
	/*static HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 0, 0));
	static UINT styleButton_xo = GetClassLong(hButton_xo[0], GCL_STYLE);*/
	
	//static HBRUSH whiteBrush;

	switch (uMessage)
	{
	case WM_CLOSE:
		// Закрываем немодальный диалог.
		DestroyWindow(hWnd); // разрушаем окно.
		PostQuitMessage(0); // останавливаем цикл обработки сообщений.
		return TRUE;

	/*case WM_CTLCOLORBTN:
	{
		SetTextColor((HDC)wParam, RGB(0, 0, 100));
		SetBkColor((HDC)wParam, RGB(100, 190, 198));
		return (LRESULT)CreateSolidBrush(RGB(100, 190, 198));
	}*/

	case WM_INITDIALOG:
		// Получаем Handle.
		hNewGame = GetDlgItem(hWnd, IDC_BUTTON_NewGame);
		hWalkFirst = GetDlgItem(hWnd, IDC_CHECK_WalkFirst);
		hText = GetDlgItem(hWnd, IDC_STATIC_text);
		// Получаем Handle радиоКнопки.					// TODO delete !?
		//hEasyHard = GetDlgItem(hWnd, IDC_RADIO_EasyLevel);	// TODO если CheckRadioButton то наверно delete
		// Получаем дескрипторы кнопок (хо).
		/*hButton_xo_1 = GetDlgItem(hWnd, IDC_BUTTON_xo_1);*/	// TODO delete
		for (int i = 0; i < 9; i++)
		{
			hButton_xo[i] = GetDlgItem(hWnd, IDC_BUTTON_xo_1 + i);
			// При запуске все кнопки не активны.
			EnableWindow(hButton_xo[i], NULL);
		}

		// Загружаем bmp "крестик", "нолик" и "пусто" и получаем их Handle.
		hCross = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_x));
		hRound = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_o));
		//hEmpty = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_backg));	// TODO delete


		// Изначально выбран "легкий уровень".
		CheckRadioButton(hWnd, IDC_RADIO_EasyLevel, IDC_RADIO_HardLevel, IDC_RADIO_EasyLevel);
		// Изначально флажок "ходить первым" снят.
		SendMessage(hWalkFirst, BM_SETCHECK, WPARAM(BST_UNCHECKED), NULL);


		// Пишем текст.
		SetWindowText(hWnd, L"Крестики нолики");
		SetWindowText(hText, L"Для начала игры нажмите \"Новая игра\"");
		
	

		
		//SetClassLong(hButton_xo[0], GCL_STYLE, styleButton_xo | (LONG)whiteBrush);	// TODO delete  - not work

		return TRUE;

	case WM_COMMAND:
		// Новая игра.
		if (LOWORD(wParam) == IDC_BUTTON_NewGame)
		{
			// Обнуляем игровые кнопки.
			for (int i = 0; i < 9; i++)
			{
				// Отправляем на кнопки картинку "которую не загружали".
				SendMessage(
					GetDlgItem(hWnd, IDC_BUTTON_xo_1 + i),
					BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
					LPARAM(hEmpty));

				// Делаем кнопки активными.
				EnableWindow(GetDlgItem(hWnd, IDC_BUTTON_xo_1 + i), TRUE);
			}

			// ??? метод игры1 игры2?
		}
		// Легкая сложность.
		else if (LOWORD(wParam) == IDC_RADIO_EasyLevel)
		{
			MessageBox(hWnd, L"Нажал радио \"Легкий уровень\"",
				L"работает", MB_OK | MB_ICONINFORMATION);
		}
		// Тяжелая сложность.
		else if (LOWORD(wParam) == IDC_RADIO_HardLevel)
		{
			MessageBox(hWnd, L"Нажал радио \"Сложный уровень\"",
				L"работает", MB_OK | MB_ICONINFORMATION);
		}
		// User ходит первым (крестиками).
		else if (LOWORD(wParam) == IDC_CHECK_WalkFirst)
		{
			MessageBox(hWnd, L"Нажал флажок \"Ходить первым\"",
				L"работает", MB_OK | MB_ICONINFORMATION);
		}


		// При нажатии на игровое поле.
		//if (LOWORD(wParam) == IDC_BUTTON_xo_1)
		if (LOWORD(wParam) >= IDC_BUTTON_xo_1 && LOWORD(wParam) <= IDC_BUTTON_xo_9)
		{

			// Ставим "крестик".
			SendMessage(
				GetDlgItem(hWnd, LOWORD(wParam)),
				BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
				LPARAM(hCross));
			// Ставим "нолик".
			// TODO код для нолика...

			// Делаем кнопку неактивной.
			EnableWindow(GetDlgItem(hWnd, LOWORD(wParam)), NULL);

		}

		return TRUE;

	}

	return FALSE;
}



// Загружаем bmp	//  TODO потом при нажатии кнопок
//SendMessage(hButton_xo[0], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hCross));
//SendMessage(hButton_xo[1], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hRound));