#include "Header.h"
//#include "Game.h"


// Прототип функции DlgProc.
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

BOOL AllArePressed(int isPressed[]);
BOOL CheckOfAWinningCombination(int aPressed[]);
void Standoff(HWND hWnd, HWND hText);

void ComputerPuts(HWND hWnd, int numberButton, HBITMAP hFigure);
int GettingTheButtonNumber(int aPressed[], int eLevel, int eFigureComp);
int Algorithm(int aPressed[], int eFigureComp);
BOOL CombinationCheck(int aPressed[], int nButton, int route, int eFigure);
int SearchIsEmpty(int aPressed[], int nButton, int route);



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
	static int aPressed[9];	// состояния кнопок (не нажата/нажат крестик/нолик)
	//TCHAR szTempNumber[MAX_PATH];
	static BOOL isAllArePressed;

	static int iNumberButton;

	//static Game game;


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

		// Загружаем bmp "крестик", "нолик" и получаем их Handle.
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
				aPressed[i] = eeEmpty;
			}

			// У первого игрока всегда "х".
			eeFigure = eeCross;

			isAllArePressed = FALSE;	// TODO ??? - delete

			// Если радиоБаттон стоит на лекгом уровне.
			if (SendDlgItemMessage(hWnd,IDC_RADIO_EasyLevel, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				// то Comp ходит рандомно.
				eLevel = eEasy;
				/*MessageBox(hWnd, L"Нажал радио \"Легкий уровень\"",
					L"работает", MB_OK | MB_ICONINFORMATION);*/
			}
			// Иначе если на тяжелом уровне.
			else
			{
				// то Comp ходит по алгоритму.
				eLevel = eHard;
				/*MessageBox(hWnd, L"Нажал радио \"Сложный уровень\"",
					L"работает", MB_OK | MB_ICONINFORMATION);*/
			}

			// Проверить состояние флажка "ходить первым".
			// Если флажок установлен
			// ===== Ходит User
			if (SendMessage(hWalkFirst, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				// То ход игрока.
				// (ждем нажатия).	// TODO delete
				eNowWalks = eWalkUser;
				SetWindowText(hWnd, L"test Ход игрока");	// TODO delete

				SetWindowText(hText, L"Ваш ход");
			}
			// Иначе если не установлен
			// ===== Ходит Comp
			else
			{
				// проверим все ли нажаты
				if (!AllArePressed(aPressed)) {
					// Если не все нажаты, то выберем новую кнопку рандомно
					// пока не найдем "не нажатую".
					do
					{
						randNumber = rand() % 9;
					} while (aPressed[randNumber] != eeEmpty);
				}

				// Если		// TODO TODO TODO
				if (eLevel == eHard)
				{
					randNumber = 4;
					// Первый ход Компа всегда в центр.	
				}

				ComputerPuts(hWnd, randNumber, hCross);
				

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


		}
		/*========================================================*/
		/*========================================================*/
		/*========================================================*/
		// Легкая сложность.
		else if (LOWORD(wParam) == IDC_RADIO_EasyLevel)
		{
			/*MessageBox(hWnd, L"Нажал радио \"Легкий уровень\"",
				L"работает", MB_OK | MB_ICONINFORMATION);*/
		}
		// Тяжелая сложность.
		else if (LOWORD(wParam) == IDC_RADIO_HardLevel)
		{
			/*MessageBox(hWnd, L"Нажал радио \"Сложный уровень\"",
				L"работает", MB_OK | MB_ICONINFORMATION);*/
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
					aPressed[GetDlgCtrlID(GetDlgItem(hWnd, LOWORD(wParam))) - IDC_BUTTON_xo_1] = eeRound;

					eeFigure = eeCross;	// меняем фигуру.
				}
				
				// Смена игрока.
				eNowWalks = eWalkComp;

				SetWindowText(hText, L"Ходит комп");

				// ================================
				// Если есть выигрышная комбинация.
				if (CheckOfAWinningCombination(aPressed) == TRUE)
				{
					for (int i = 0; i < 9; ++i)
					{
						// Делаем все кнопки не активными.
						EnableWindow(GetDlgItem(hWnd, IDC_BUTTON_xo_1 + i), FALSE);
					}

					// Дальше никто не ходит.
					eNowWalks = eNoMoves;

					// Пишем в статик кто выиграл.
					MessageBox(hWnd, L"Вы выиграли",
						L"работает", MB_OK | MB_ICONINFORMATION);

					SetWindowText(hText, L"Вы выиграли");
				}
				else
				{
					// Делаем кнопку неактивной.
					EnableWindow(GetDlgItem(hWnd, LOWORD(wParam)), NULL);// TODO FALSE

					// Если после хода Userа все нажаты
					if (AllArePressed(aPressed) == TRUE)
					{
						// Дальше никто не ходит.
						eNowWalks = eNoMoves;

						// Значит "Ничья".
						Standoff(hWnd, hText);
					}
				}
			}
			

			

			/*====================================================================================*/
			// Например жмет Комп
			if (eNowWalks == eWalkComp)
			{
				// проверим все ли нажаты
				//if (!AllArePressed(aPressed))
				//{
				//	// Если не все нажаты, то выберем новую кнопку рандомно
				//	// пока не найдем "не нажатую".
				//	do
				//	{
				//		randNumber = rand() % 9;
				//	} while (aPressed[randNumber] != eeEmpty);
				//}
				
				iNumberButton = GettingTheButtonNumber(aPressed, eLevel, eeFigure);	// TODO (game, eLevel)

				// Ставим рандомно или по алгоритму!	// TODO algoritm or random

				// Ставим фигуру.
				if (eeFigure == eeCross)
				{
					// Ставим "крестик".
					ComputerPuts(hWnd, iNumberButton, hCross);
					// Запоминаем нажатую кнопку.
					aPressed[iNumberButton] = eeCross;

					eeFigure = eeRound;	// меняем фигуру.
				}
				else if (eeFigure == eeRound)
				{
					// Ставим "нолик".
					ComputerPuts(hWnd, iNumberButton, hRound);
					// Запоминаем нажатую кнопку.
					aPressed[iNumberButton] = eeRound;

					eeFigure = eeCross;	// меняем фигуру.
				}

				// Меняем игрока
				eNowWalks = eWalkUser;
				// Сообщение для след игрока
				SetWindowText(hText, L"Ваш ход");


				// ================================
				// Если есть выигрышная комбинация.
				if (CheckOfAWinningCombination(aPressed) == TRUE)
				{
					for (int i = 0; i < 9; ++i)
					{
						// Делаем все кнопки не активными.
						EnableWindow(GetDlgItem(hWnd, IDC_BUTTON_xo_1 + i), FALSE);
					}

					// Пишем в статик кто выиграл.
					MessageBox(hWnd, L"Комп выиграл",
						L"работает", MB_OK | MB_ICONINFORMATION);

					SetWindowText(hText, L"Комп выиграл");
				}
				else
				{
					// Делаем кнопку неактивной.
					EnableWindow(GetDlgItem(hWnd, IDC_BUTTON_xo_1 + iNumberButton), NULL);// TODO FALSE

					// Если после хода Сompa все нажаты.
					if (AllArePressed(aPressed) == TRUE)
					{
						// Значит "Ничья".
						Standoff(hWnd, hText);
					}
				}
			}
			/*======================================================================================*/



		}

		return TRUE;

	}

	return FALSE;
}





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



BOOL CheckOfAWinningCombination(int aPressed[]){

	// Ищем выигрышную комбинацию. 
	/*if (HorizontalCheck(aPressed, eeCross) == TRUE)
	{
		return TRUE;
	}
	else if (HorizontalCheck(aPressed, eeRound) == TRUE)
	{
		return TRUE;
	}*/
	if (
		(aPressed[0] == aPressed[1] && aPressed[1] == aPressed[2] && aPressed[2] != eeEmpty)
		||
		(aPressed[3] == aPressed[4] && aPressed[4] == aPressed[5] && aPressed[5] != eeEmpty)
		||
		(aPressed[6] == aPressed[7] && aPressed[7] == aPressed[8] && aPressed[8] != eeEmpty)
		)
	{
		return TRUE;
	}
	else if (
		(aPressed[0] == aPressed[3] && aPressed[3] == aPressed[6] && aPressed[6] != eeEmpty)
		||
		(aPressed[1] == aPressed[4] && aPressed[4] == aPressed[7] && aPressed[7] != eeEmpty)
		||
		(aPressed[2] == aPressed[5] && aPressed[5] == aPressed[8] && aPressed[8] != eeEmpty)
		)
	{
		return TRUE;
	}
	else if (
		(aPressed[0] == aPressed[4] && aPressed[4] == aPressed[8] && aPressed[8] != eeEmpty)
		||
		(aPressed[2] == aPressed[4] && aPressed[4] == aPressed[6] && aPressed[6] != eeEmpty)
		)
	{
		return TRUE;
	}

	return FALSE;
}

//BOOL HorizontalCheck(int aPressed[], int eFigure) {
//	if (
//		(aPressed[0] == aPressed[1] && aPressed[1] == aPressed[2] && aPressed[2] == eFigure)
//		||
//		(aPressed[3] == aPressed[4] && aPressed[4] == aPressed[5] && aPressed[5] == eFigure)
//		||
//		(aPressed[6] == aPressed[7] && aPressed[7] == aPressed[8] && aPressed[8] == eFigure)
//		)
//	{
//		return TRUE;
//	}
//
//	return FALSE;
//}

void Standoff(HWND hWnd, HWND hText) {
	// "Ничья".
	MessageBox(hWnd, L"Ничья",
		L"работает", MB_OK | MB_ICONINFORMATION);

	SetWindowText(hText, L"Ничья");
}


void ComputerPuts(HWND hWnd, int numberButton, HBITMAP hFigure) {
	SendMessage(
		GetDlgItem(hWnd, IDC_BUTTON_xo_1 + numberButton),
		BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
		LPARAM(hFigure));
}

int GettingTheButtonNumber(int aPressed[], int eLevel, int eFigureComp) {

	if (eLevel == eEasy)
	{
		int tempRandNumber;

		// проверим все ли нажаты
		if (!AllArePressed(aPressed))
		{
			// Если не все нажаты, то выберем новую кнопку рандомно
			// пока не найдем "не нажатую".
			do
			{
				tempRandNumber = rand() % 9;
			} while (aPressed[tempRandNumber] != eeEmpty);
		}

		return tempRandNumber;
	}
	else if (eLevel == eHard)
	{
		return Algorithm(aPressed, eFigureComp);
	}

	return 0;
}

int Algorithm(int aPressed[], int eFigureComp) {

	int eFigureUser;

	// Узнаем у кого какая фигура.
	if (eFigureComp == eeCross)
	{
		eFigureUser = eeRound;
	}
	else
	{
		eFigureUser = eeCross;
	}


	// Проверка полей противника (Usera)
	// Нападение.

	// Горизонтальные поля.
	if (CombinationCheck(aPressed, 0, d_HORIZONTAL, eFigureUser) == TRUE)
	{
		return SearchIsEmpty(aPressed, 0, d_HORIZONTAL);
	}
	else if (CombinationCheck(aPressed, 3, d_HORIZONTAL, eFigureUser) == TRUE)
	{
		return SearchIsEmpty(aPressed, 3, d_HORIZONTAL);
	}
	else if (CombinationCheck(aPressed, 6, d_HORIZONTAL, eFigureUser) == TRUE)
	{
		return SearchIsEmpty(aPressed, 6, d_HORIZONTAL);
	}
	// Вертикальные поля.
	else if (CombinationCheck(aPressed, 0, d_VERTICAL, eFigureUser) == TRUE)
	{
		return SearchIsEmpty(aPressed, 0, d_VERTICAL);
	}
	else if (CombinationCheck(aPressed, 1, d_VERTICAL, eFigureUser) == TRUE)
	{
		return SearchIsEmpty(aPressed, 1, d_VERTICAL);
	}
	else if (CombinationCheck(aPressed, 2, d_VERTICAL, eFigureUser) == TRUE)
	{
		return SearchIsEmpty(aPressed, 2, d_VERTICAL);
	}
	// Диагональ.
	else if (CombinationCheck(aPressed, 2, d_DIAGONAL_LEFT, eFigureUser) == TRUE)
	{
		return SearchIsEmpty(aPressed, 2, d_DIAGONAL_LEFT);
	}
	else if (CombinationCheck(aPressed, 0, d_DIAGONAL_RIGHT, eFigureUser) == TRUE)
	{
		return SearchIsEmpty(aPressed, 0, d_DIAGONAL_RIGHT);
	}

	// Проверка полей Компьютера (своих).
	// Защита.

	// Горизонтальные поля.
	if (CombinationCheck(aPressed, 0, d_HORIZONTAL, eFigureComp) == TRUE)
	{
		return SearchIsEmpty(aPressed, 0, d_HORIZONTAL);
	}
	else if (CombinationCheck(aPressed, 3, d_HORIZONTAL, eFigureComp) == TRUE)
	{
		return SearchIsEmpty(aPressed, 3, d_HORIZONTAL);
	}
	else if (CombinationCheck(aPressed, 6, d_HORIZONTAL, eFigureComp) == TRUE)
	{
		return SearchIsEmpty(aPressed, 6, d_HORIZONTAL);
	}
	// Вертикальные поля.
	else if (CombinationCheck(aPressed, 0, d_VERTICAL, eFigureComp) == TRUE)
	{
		return SearchIsEmpty(aPressed, 0, d_VERTICAL);
	}
	else if (CombinationCheck(aPressed, 1, d_VERTICAL, eFigureComp) == TRUE)
	{
		return SearchIsEmpty(aPressed, 1, d_VERTICAL);
	}
	else if (CombinationCheck(aPressed, 2, d_VERTICAL, eFigureComp) == TRUE)
	{
		return SearchIsEmpty(aPressed, 2, d_VERTICAL);
	}
	// Диагональ.
	else if (CombinationCheck(aPressed, 2, d_DIAGONAL_LEFT, eFigureComp) == TRUE)
	{
		return SearchIsEmpty(aPressed, 2, d_DIAGONAL_LEFT);
	}
	else if (CombinationCheck(aPressed, 0, d_DIAGONAL_RIGHT, eFigureComp) == TRUE)
	{
		return SearchIsEmpty(aPressed, 0, d_DIAGONAL_RIGHT);
	}


	// Рандомная расстановка (центр, углы, промежутки).


	return 6;
}

//BOOL CheckAllCombinations(int nButton, int route, int eFigure) {
//
//}

BOOL CombinationCheck(int aPressed[], int nButton, int route, int eFigure) {

	if (
		(aPressed[nButton] == eFigure) && ((aPressed[nButton += route]) == eFigure) && ((aPressed[nButton += route]) == eeEmpty)
		||
		(aPressed[nButton] == eFigure) && ((aPressed[nButton += route]) == eeEmpty) && ((aPressed[nButton += route]) == eFigure)
		||
		(aPressed[nButton] == eeEmpty) && ((aPressed[nButton += route]) == eFigure) && ((aPressed[nButton += route]) == eFigure)
		)
	{
		return TRUE;
	}

	return FALSE;
}

int SearchIsEmpty(int aPressed[], int nButton, int route) {

	for (int i = 0; i < 3; i++)		// TODO define SIZE_COMBINATION
	{
		if (aPressed[nButton] == eeEmpty)
		{
			return nButton;
		}

		nButton += route;
	}
}

//void RandWalkComp() {
//	// проверим все ли нажаты
//	if (!AllArePressed(aPressed))
//	{
//		// Если не все нажаты, то выберем новую кнопку рандомно
//		// пока не найдем "не нажатую".
//		do
//		{
//			randNumber = rand() % 9;
//		} while (aPressed[randNumber] != eeEmpty);
//	}
//
//
//
//	// Ставим рандомно или по алгоритму!	// TODO algoritm or random
//
//	// Ставим фигуру.
//	if (eeFigure == eeCross)
//	{
//		// Ставим "крестик".
//		SendMessage(
//			GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber),
//			BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
//			LPARAM(hCross));
//		// Запоминаем нажатую кнопку.
//		aPressed[randNumber] = eeCross;
//
//		eeFigure = eeRound;	// меняем фигуру.
//	}
//	else if (eeFigure == eeRound)
//	{
//		// Ставим "нолик".
//		SendMessage(
//			GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber),
//			BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
//			LPARAM(hRound));
//		// Запоминаем нажатую кнопку.
//		aPressed[randNumber] = eeRound;
//
//		eeFigure = eeCross;	// меняем фигуру.
//	}
//}