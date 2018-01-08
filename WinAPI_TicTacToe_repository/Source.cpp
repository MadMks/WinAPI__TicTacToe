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
	srand(time(NULL));

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

	static int randNumber;



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
		// Первым ходит "Комп".
		eNowWalks = eWalkComp;		// TODO ???

		// Пишем текст.
		SetWindowText(hWnd, L"Крестики нолики");
		SetWindowText(hText, L"Для начала игры нажмите \"Новая игра\"");
		
	

		
		//SetClassLong(hButton_xo[0], GCL_STYLE, styleButton_xo | (LONG)whiteBrush);	// TODO delete  - not work

		return TRUE;

	case WM_COMMAND:
		/*========================================================*/
		/*========================================================*/
		/*========================================================*/
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

			// У первого игрока всегда "х".
			eFigure = eCross;

			// Проверить состояние флажка "ходить первым".
			// Если флажок установлен
			if (SendMessage(hWalkFirst, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				// То ход игрока.
				// (ждем нажатия).	// TODO delete
				eNowWalks = eWalkUser;
				SetWindowText(hWnd, L"test Ход игрока");	// TODO delete

				SetWindowText(hText, L"Ваш ход");
			}
			// Иначе если не установлен
			else
			{
				// То ход Компа.
				// Ставим рандомно или по алгоритму!	// TODO algoritm or random
				SendMessage(
					//GetDlgItem(hWnd, LOWORD(wParam)),
					GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber),	// TODO 5 заменить на переменную randShot
					BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
					LPARAM(hCross));

				// Меняем игрока
				eNowWalks = eWalkUser;
				// Меняем фигуру
				eFigure = eRound;

				// рандом или алгоритм
				// ход компа	// TODO algoritm
				SetWindowText(hWnd, L"test Ход компа");	// TODO delete
			}


			// Обнуляем фигуру (по умолчанию при новой игре
			// первым ходит комп).


			// 
			//if (eNowWalks == eWalkUser)
			//{
			//	// значит user ходит "x"
			//	eFigure = eCross;
			//}


			// ??? метод игры1 игры2?
		}
		/*========================================================*/
		/*========================================================*/
		/*========================================================*/
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
			//eNowWalks = eWalkUser;

			// проверяем состояние
			//eFigure = eCross;

			/*MessageBox(hWnd, L"Нажал флажок \"Ходить первым\"",
				L"работает", MB_OK | MB_ICONINFORMATION);*/
		}
		/*========================================================*/
		/*========================================================*/
		/*========================================================*/

		// При нажатии на игровое поле.
		//if (LOWORD(wParam) == IDC_BUTTON_xo_1)
		if (LOWORD(wParam) >= IDC_BUTTON_xo_1 && LOWORD(wParam) <= IDC_BUTTON_xo_9)
		{
			
			if (eNowWalks == eWalkUser)
			{

				// Ставим фигуру.
				if (eFigure == eCross)
				{
					// Ставим "крестик".
					SendMessage(
						GetDlgItem(hWnd, LOWORD(wParam)),
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hCross));

					eFigure = eRound;	// меняем фигуру.
				}
				else if (eFigure == eRound)
				{
					// Ставим "нолик".
					SendMessage(
						GetDlgItem(hWnd, LOWORD(wParam)),
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hRound));

					eFigure = eCross;	// меняем фигуру.
				}

				// Ход игрока
				// и меняем игрока...

				// Ходит Комп
				/*if (eNowWalks == eWalkComp)
				{
					// Вручную и рандомно ставим текущую фигуру
					//

					eNowWalks = eWalkUser;

					SetWindowText(hText, L"Ваш ход");
				}
				else*/

				eNowWalks = eWalkComp;

				SetWindowText(hText, L"Ходит комп");

				// Делаем кнопку неактивной.
				EnableWindow(GetDlgItem(hWnd, LOWORD(wParam)), NULL);
			}
			

			

			/*====================================================================================*/
			// Например жмет Комп
			if (eNowWalks == eWalkComp)
			{
				randNumber = (rand() % 9);

				// проверка ранд номера - если есть то заменить!	// TODO re


				// Ставим рандомно или по алгоритму!	// TODO algoritm or random

				// Ставим фигуру.
				if (eFigure == eCross)
				{
					// Ставим "крестик".
					SendMessage(
						GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber),	// TODO 5 заменить на переменную randShot
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hCross));

					eFigure = eRound;	// меняем фигуру.
				}
				else if (eFigure == eRound)
				{
					// Ставим "нолик".
					SendMessage(
						GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber),	// TODO 5 заменить на переменную randShot
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hRound));

					eFigure = eCross;	// меняем фигуру.
				}

				// Меняем игрока
				eNowWalks = eWalkUser;
				// Сообщение для след игрока
				SetWindowText(hText, L"Ваш ход");

				// Делаем кнопку неактивной.
				EnableWindow(GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber), NULL);	// TODO 5 заменить на переменную randShot
			}
			/*======================================================================================*/



		}

		return TRUE;

	}

	return FALSE;
}



// Загружаем bmp	//  TODO потом при нажатии кнопок
//SendMessage(hButton_xo[0], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hCross));
//SendMessage(hButton_xo[1], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hRound));