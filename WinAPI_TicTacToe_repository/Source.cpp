#include "Header.h"


// �������� ������� DlgProc.
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

BOOL AllArePressed(int isPressed[]);
BOOL CheckOfAWinningCombination();



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{

	MSG msg;	// ���������.
				// ������ ������� ���� ���������� �� ������ ������������ �������
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	// ���������� ����	
	ShowWindow(hDialog, nCmdShow);


	//��������� ���� ��������� ���������
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
	static HBITMAP hEmpty;	// handle �� ������������ ��������.

	static int randNumber;

	///static BOOL isPressed[9];
	static int aPressed[9];
	//TCHAR szTempNumber[MAX_PATH];
	static BOOL isAllArePressed;


	switch (uMessage)
	{
	case WM_CLOSE:
		// ��������� ����������� ������.
		DestroyWindow(hWnd); // ��������� ����.
		PostQuitMessage(0); // ������������� ���� ��������� ���������.
		return TRUE;


	case WM_INITDIALOG:
		// �������� Handle.
		hNewGame = GetDlgItem(hWnd, IDC_BUTTON_NewGame);
		hWalkFirst = GetDlgItem(hWnd, IDC_CHECK_WalkFirst);
		hText = GetDlgItem(hWnd, IDC_STATIC_text);
		// �������� Handle �����������.					// TODO delete !?
		//hEasyHard = GetDlgItem(hWnd, IDC_RADIO_EasyLevel);	// TODO ���� CheckRadioButton �� ������� delete
		// �������� ����������� ������ (��).
		/*hButton_xo_1 = GetDlgItem(hWnd, IDC_BUTTON_xo_1);*/	// TODO delete
		for (int i = 0; i < 9; i++)
		{
			hButton_xo[i] = GetDlgItem(hWnd, IDC_BUTTON_xo_1 + i);
			// ��� ������� ��� ������ �� �������.
			EnableWindow(hButton_xo[i], NULL);	// TODO FALSE
			
		}

		// ��������� bmp "�������", "�����" � "�����" � �������� �� Handle.
		hCross = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_x));
		hRound = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_o));
		//hEmpty = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_backg));	// TODO delete


		// ���������� ������ "������ �������".
		CheckRadioButton(hWnd, IDC_RADIO_EasyLevel, IDC_RADIO_HardLevel, IDC_RADIO_EasyLevel);
		// ���������� ������ "������ ������" ����.
		SendMessage(hWalkFirst, BM_SETCHECK, WPARAM(BST_UNCHECKED), NULL);
		// ������ ����� "����".
		eNowWalks = eWalkComp;		// TODO ??? - ���������� ��� = ����� �� �����.
		

		// ����� �����.
		SetWindowText(hWnd, L"�������� ������");
		SetWindowText(hText, L"��� ������ ���� ������� \"����� ����\"");
		
	


		return TRUE;

	case WM_COMMAND:
		/*========================================================*/
		/*========================================================*/
		/*========================================================*/
		// ����� ����.
		if (LOWORD(wParam) == IDC_BUTTON_NewGame)
		{
			// �������� ������� ������.
			for (int i = 0; i < 9; i++)
			{
				// ���������� �� ������ �������� "������� �� ���������".
				SendMessage(
					GetDlgItem(hWnd, IDC_BUTTON_xo_1 + i),
					BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
					LPARAM(hEmpty));

				// ������ ������ ���������.
				EnableWindow(GetDlgItem(hWnd, IDC_BUTTON_xo_1 + i), TRUE);

				// ���������� ������ �� ������.
				//isPressed[i] = FALSE;
				// TODO NewNew
				aPressed[i] = eeEmpty;
			}

			// � ������� ������ ������ "�".
			eeFigure = eeCross;

			isAllArePressed = FALSE;

			// ��������� ��������� ������ "������ ������".
			// ���� ������ ����������
			if (SendMessage(hWalkFirst, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				// �� ��� ������.
				// (���� �������).	// TODO delete
				eNowWalks = eWalkUser;
				SetWindowText(hWnd, L"test ��� ������");	// TODO delete

				SetWindowText(hText, L"��� ���");
			}
			// ����� ���� �� ����������
			else
			{

				// -
				// TODO - �������� ����� ����� ������ ����� �������� ���� "�������� ����������"
				// ������ ������ - ����� ��������.
				// test
				// �������� ��� �� ������
				if (!AllArePressed(aPressed)) {
					// �������� ���� ������ - ���� ���� �� ��������!	// TODO re
					///do
					///{
					///	randNumber = rand() % 9;
					///} while (isPressed[randNumber] == TRUE);		// TODO (not) working !!!
					
					// TODO NewNew
					// ���� �� ��� ������, �� ������� ����� ������ ��������
					// ���� �� ������ "�� �������".
					do
					{
						randNumber = rand() % 9;
					} while (aPressed[randNumber] != eeEmpty);
				}

				// �� ��� �����.
				// ������ �������� ��� �� ���������!	// TODO algoritm or random
				SendMessage(
					//GetDlgItem(hWnd, LOWORD(wParam)),
					GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber),	// TODO 5 �������� �� ���������� randShot
					BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
					LPARAM(hCross));
				// ���������� ������� ������.
				///isPressed[randNumber] = TRUE;
				// TODO NewNew
				// ���������� ������� ������.
				aPressed[randNumber] = eeCross;

				// ������ ������ ����������.
				EnableWindow(GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber), FALSE);
				// ������ ������
				eNowWalks = eWalkUser;
				// ������ ������
				eeFigure = eeRound;

				// ������ ��� ��������
				// ��� �����	// TODO algoritm
				SetWindowText(hWnd, L"test ��� �����");	// TODO delete
			}


			// �������� ������ (�� ��������� ��� ����� ����
			// ������ ����� ����).


			// 
			//if (eNowWalks == eWalkUser)
			//{
			//	// ������ user ����� "x"
			//	eFigure = eCross;
			//}


			// ??? ����� ����1 ����2?
		}
		/*========================================================*/
		/*========================================================*/
		/*========================================================*/
		// ������ ���������.
		else if (LOWORD(wParam) == IDC_RADIO_EasyLevel)
		{
			MessageBox(hWnd, L"����� ����� \"������ �������\"",
				L"��������", MB_OK | MB_ICONINFORMATION);
		}
		// ������� ���������.
		else if (LOWORD(wParam) == IDC_RADIO_HardLevel)
		{
			MessageBox(hWnd, L"����� ����� \"������� �������\"",
				L"��������", MB_OK | MB_ICONINFORMATION);
		}
		// User ����� ������ (����������).
		else if (LOWORD(wParam) == IDC_CHECK_WalkFirst)
		{
			//eNowWalks = eWalkUser;

			// ��������� ���������
			//eFigure = eCross;

			/*MessageBox(hWnd, L"����� ������ \"������ ������\"",
				L"��������", MB_OK | MB_ICONINFORMATION);*/
		}
		/*========================================================*/
		/*========================================================*/
		/*========================================================*/

		// ��� ������� �� ������� ����.
		//if (LOWORD(wParam) == IDC_BUTTON_xo_1)
		if (LOWORD(wParam) >= IDC_BUTTON_xo_1 && LOWORD(wParam) <= IDC_BUTTON_xo_9)
		{
			// ���� ����� User.
			if (eNowWalks == eWalkUser)
			{

				// ������ ������.
				if (eeFigure == eeCross)
				{
					// ������ "�������".
					SendMessage(
						GetDlgItem(hWnd, LOWORD(wParam)),
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hCross));
					// ���������� ������� ������.
					///isPressed[GetDlgCtrlID(GetDlgItem(hWnd, LOWORD(wParam))) - IDC_BUTTON_xo_1] = TRUE;

					// TODO NewNew
					aPressed[GetDlgCtrlID(GetDlgItem(hWnd, LOWORD(wParam))) - IDC_BUTTON_xo_1] = eeCross;

					eeFigure = eeRound;	// ������ ������.
				}
				else if (eeFigure == eeRound)
				{
					// ������ "�����".
					SendMessage(
						GetDlgItem(hWnd, LOWORD(wParam)),
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hRound));
					// ���������� ������� ������.
					///isPressed[GetDlgCtrlID(GetDlgItem(hWnd, LOWORD(wParam))) - IDC_BUTTON_xo_1] = TRUE;

					// TODO NewNew
					aPressed[GetDlgCtrlID(GetDlgItem(hWnd, LOWORD(wParam))) - IDC_BUTTON_xo_1] = eeRound;

					eeFigure = eeCross;	// ������ ������.
				}
				

				eNowWalks = eWalkComp;

				SetWindowText(hText, L"����� ����");

				/// ���� ���� ���������� ����������.
				///if (CheckOfAWinningCombination() == TRUE)
				///{
					///for (int i = 0; i < 9; ++i)
					///{
						// ������ ��� ������ �� ���������.
						///EnableWindow(GetDlgItem(hWnd, IDC_BUTTON_xo_1 + i), FALSE);
					///}

					// ����� � ������ ��� �������.
					/* TODO ���������� ��� �������, � ����� �������� */
				///}
				///else
				///{
					// ������ ������ ����������.
					EnableWindow(GetDlgItem(hWnd, LOWORD(wParam)), NULL);// TODO FALSE
				///}
			}
			

			

			/*====================================================================================*/
			// �������� ���� ����
			if (eNowWalks == eWalkComp)
			{
				/*randNumber = (rand() % 9);*/

				// -
				// TODO - �������� ����� ����� ������ ����� �������� ���� "�������� ����������"
				// ������ ������ - ����� ��������.
				// test
				// �������� ��� �� ������
				if (!AllArePressed(aPressed))
				{
					// �������� ���� ������ - ���� ���� �� ��������!	// TODO re
					///do
					///{
					///	randNumber = rand() % 9;
						//SetWindowText(hWnd, MAKEINTRESOURCE(randNumber));
					///} while (isPressed[randNumber] == TRUE);		// TODO not working !!!

					// TODO NewNew
					// ���� �� ��� ������, �� ������� ����� ������ ��������
					// ���� �� ������ "�� �������".
					do
					{
						randNumber = rand() % 9;
					} while (aPressed[randNumber] != eeEmpty);
				}
				

				// ������ �������� ��� �� ���������!	// TODO algoritm or random

				// ������ ������.
				if (eeFigure == eeCross)
				{
					// ������ "�������".
					SendMessage(
						GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber),	// TODO 5 �������� �� ���������� randShot
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hCross));
					// ���������� ������� ������.
					///isPressed[randNumber] = TRUE;
					// TODO NewNew
					aPressed[randNumber] = eeCross;

					eeFigure = eeRound;	// ������ ������.
				}
				else if (eeFigure == eeRound)
				{
					// ������ "�����".
					SendMessage(
						GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber),	// TODO 5 �������� �� ���������� randShot
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hRound));
					// ���������� ������� ������.
					///isPressed[randNumber] = TRUE;
					// TODO NewNew
					aPressed[randNumber] = eeRound;

					eeFigure = eeCross;	// ������ ������.
				}

				// ������ ������
				eNowWalks = eWalkUser;
				// ��������� ��� ���� ������
				SetWindowText(hText, L"��� ���");

				// ������ ������ ����������.	// TODO FALSE
				EnableWindow(GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber), NULL);	// TODO 5 �������� �� ���������� randShot
			}
			/*======================================================================================*/



		}

		return TRUE;

	}

	return FALSE;
}



// ��������� bmp	//  TODO ����� ��� ������� ������
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

	// ���� ���������� ����������. 
	if (/* condition */ FALSE)
	{
		/* code */
	}

	return TRUE;
}