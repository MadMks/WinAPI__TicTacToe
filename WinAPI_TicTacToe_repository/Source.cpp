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

	switch (uMessage)
	{
	case WM_CLOSE:
		// Закрываем немодальный диалог.
		DestroyWindow(hWnd); // разрушаем окно.
		PostQuitMessage(0); // останавливаем цикл обработки сообщений.
		return TRUE;

	case WM_INITDIALOG:
		// Получаем дескриптор кнопки.
		hNewGame = GetDlgItem(hWnd, IDC_BUTTON_NewGame);
		// Получаем дескриптор флажка.
		hWalkFirst = GetDlgItem(hWnd, IDC_CHECK_WalkFirst);
		// Получаем дескриптор радиоКнопки.					// TODO delete !?
		hEasyHard = GetDlgItem(hWnd, IDC_RADIO_EasyLevel);	// TODO если CheckRadioButton то наверно delete

		// Изначально выбран "легкий уровень".
		CheckRadioButton(hWnd, IDC_RADIO_EasyLevel, IDC_RADIO_HardLevel, IDC_RADIO_EasyLevel);
		// Изначально флажок "ходить первым" снят.
		SendMessage(hWalkFirst, BM_SETCHECK, WPARAM(BST_UNCHECKED), NULL);

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
		return TRUE;

	}

	return FALSE;
}