#include "Header.h"


// Прототип функции DlgProc.
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

BOOL AllArePressed(int isPressed[]);
BOOL CheckOfAWinningCombination();



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

	static int randNumber;

	///static BOOL isPressed[9];
	static int aPressed[9];
	//TCHAR szTempNumber[MAX_PATH];
	static BOOL isAllArePressed;


	switch (uMessage)
	{
	case WM_CLOSE:
		// Закрываем немодальный диалог.
		DestroyWindow(hWnd); // разрушаем окно.
		PostQuitMessage(0); // останавливаем цикл обработки сообщений.
		return TRUE;


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
			EnableWindow(hButton_xo[i], NULL);	// TODO FALSE
			
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
		eNowWalks = eWalkComp;		// TODO ??? - просмотрел код = особо не нужно.
		

		// Пишем текст.
		SetWindowText(hWnd, L"Крестики нолики");
		SetWindowText(hText, L"Для начала игры нажмите \"Новая игра\"");
		
	


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

				// Изначально кнопки не нажаты.
				//isPressed[i] = FALSE;
				// TODO NewNew
				aPressed[i] = eeEmpty;
			}

			// У первого игрока всегда "х".
			eeFigure = eeCross;

			isAllArePressed = FALSE;

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

				// -
				// TODO - возможно можно будет убрато после рабочего кода "проверка победителя"
				// Первый анализ - нужно оставить.
				// test
				// проверим все ли нажаты
				if (!AllArePressed(aPressed)) {
					// проверка ранд номера - если есть то заменить!	// TODO re
					///do
					///{
					///	randNumber = rand() % 9;
					///} while (isPressed[randNumber] == TRUE);		// TODO (not) working !!!
					
					// TODO NewNew
					// Если не все нажаты, то выберем новую кнопку рандомно
					// пока не найдем "не нажатую".
					do
					{
						randNumber = rand() % 9;
					} while (aPressed[randNumber] != eeEmpty);
				}

				// То ход Компа.
				// Ставим рандомно или по алгоритму!	// TODO algoritm or random
				SendMessage(
					//GetDlgItem(hWnd, LOWORD(wParam)),
					GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber),	// TODO 5 заменить на переменную randShot
					BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
					LPARAM(hCross));
				// Запоминаем нажатую кнопку.
				///isPressed[randNumber] = TRUE;
				// TODO NewNew
				// Запоминаем нажатую кнопку.
				aPressed[randNumber] = eeCross;

				// Делаем кнопку неактивной.
				EnableWindow(GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber), FALSE);
				// Меняем игрока
				eNowWalks = eWalkUser;
				// Меняем фигуру
				eeFigure = eeRound;

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
			// Если ходит User.
			if (eNowWalks == eWalkUser)
			{

				// Ставим фигуру.
				if (eeFigure == eeCross)
				{
					// Ставим "крестик".
					SendMessage(
						GetDlgItem(hWnd, LOWORD(wParam)),
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hCross));
					// Запоминаем нажатую кнопку.
					///isPressed[GetDlgCtrlID(GetDlgItem(hWnd, LOWORD(wParam))) - IDC_BUTTON_xo_1] = TRUE;

					// TODO NewNew
					aPressed[GetDlgCtrlID(GetDlgItem(hWnd, LOWORD(wParam))) - IDC_BUTTON_xo_1] = eeCross;

					eeFigure = eeRound;	// меняем фигуру.
				}
				else if (eeFigure == eeRound)
				{
					// Ставим "нолик".
					SendMessage(
						GetDlgItem(hWnd, LOWORD(wParam)),
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hRound));
					// Запоминаем нажатую кнопку.
					///isPressed[GetDlgCtrlID(GetDlgItem(hWnd, LOWORD(wParam))) - IDC_BUTTON_xo_1] = TRUE;

					// TODO NewNew
					aPressed[GetDlgCtrlID(GetDlgItem(hWnd, LOWORD(wParam))) - IDC_BUTTON_xo_1] = eeRound;

					eeFigure = eeCross;	// меняем фигуру.
				}
				

				eNowWalks = eWalkComp;

				SetWindowText(hText, L"Ходит комп");

				/// Если есть выигрышная комбинация.
				///if (CheckOfAWinningCombination() == TRUE)
				///{
					///for (int i = 0; i < 9; ++i)
					///{
						// Делаем все кнопки не активными.
						///EnableWindow(GetDlgItem(hWnd, IDC_BUTTON_xo_1 + i), FALSE);
					///}

					// Пишем в статик кто выиграл.
					/* TODO определить кто выиграл, и потом написать */
				///}
				///else
				///{
					// Делаем кнопку неактивной.
					EnableWindow(GetDlgItem(hWnd, LOWORD(wParam)), NULL);// TODO FALSE
				///}
			}
			

			

			/*====================================================================================*/
			// Например жмет Комп
			if (eNowWalks == eWalkComp)
			{
				/*randNumber = (rand() % 9);*/

				// -
				// TODO - возможно можно будет убрато после рабочего кода "проверка победителя"
				// Первый анализ - нужно оставить.
				// test
				// проверим все ли нажаты
				if (!AllArePressed(aPressed))
				{
					// проверка ранд номера - если есть то заменить!	// TODO re
					///do
					///{
					///	randNumber = rand() % 9;
						//SetWindowText(hWnd, MAKEINTRESOURCE(randNumber));
					///} while (isPressed[randNumber] == TRUE);		// TODO not working !!!

					// TODO NewNew
					// Если не все нажаты, то выберем новую кнопку рандомно
					// пока не найдем "не нажатую".
					do
					{
						randNumber = rand() % 9;
					} while (aPressed[randNumber] != eeEmpty);
				}
				

				// Ставим рандомно или по алгоритму!	// TODO algoritm or random

				// Ставим фигуру.
				if (eeFigure == eeCross)
				{
					// Ставим "крестик".
					SendMessage(
						GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber),	// TODO 5 заменить на переменную randShot
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hCross));
					// Запоминаем нажатую кнопку.
					///isPressed[randNumber] = TRUE;
					// TODO NewNew
					aPressed[randNumber] = eeCross;

					eeFigure = eeRound;	// меняем фигуру.
				}
				else if (eeFigure == eeRound)
				{
					// Ставим "нолик".
					SendMessage(
						GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber),	// TODO 5 заменить на переменную randShot
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hRound));
					// Запоминаем нажатую кнопку.
					///isPressed[randNumber] = TRUE;
					// TODO NewNew
					aPressed[randNumber] = eeRound;

					eeFigure = eeCross;	// меняем фигуру.
				}

				// Меняем игрока
				eNowWalks = eWalkUser;
				// Сообщение для след игрока
				SetWindowText(hText, L"Ваш ход");

				// Делаем кнопку неактивной.	// TODO FALSE
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

BOOL AllArePressed(int aPressed[]) {
	for (int i = 0; i < 9; i++)
	{
		if (aPressed[i] == eeEmpty)
		{
			return FALSE;
		}
	}

	return TRUE;
}



BOOL CheckOfAWinningCombination(){

	// Ищем выигрышную комбинацию. 
	if (/* condition */ FALSE)
	{
		/* code */
	}

	return TRUE;
}