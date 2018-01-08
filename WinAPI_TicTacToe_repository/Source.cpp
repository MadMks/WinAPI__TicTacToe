#include "Header.h"


// �������� ������� DlgProc.
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);



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

	// ������ ����� ������ ������.
	/*static HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 0, 0));
	static UINT styleButton_xo = GetClassLong(hButton_xo[0], GCL_STYLE);*/
	
	//static HBRUSH whiteBrush;

	static int randNumber;



	switch (uMessage)
	{
	case WM_CLOSE:
		// ��������� ����������� ������.
		DestroyWindow(hWnd); // ��������� ����.
		PostQuitMessage(0); // ������������� ���� ��������� ���������.
		return TRUE;

	/*case WM_CTLCOLORBTN:
	{
		SetTextColor((HDC)wParam, RGB(0, 0, 100));
		SetBkColor((HDC)wParam, RGB(100, 190, 198));
		return (LRESULT)CreateSolidBrush(RGB(100, 190, 198));
	}*/

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
			EnableWindow(hButton_xo[i], NULL);
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
		eNowWalks = eWalkComp;		// TODO ???

		// ����� �����.
		SetWindowText(hWnd, L"�������� ������");
		SetWindowText(hText, L"��� ������ ���� ������� \"����� ����\"");
		
	

		
		//SetClassLong(hButton_xo[0], GCL_STYLE, styleButton_xo | (LONG)whiteBrush);	// TODO delete  - not work

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
			}

			// � ������� ������ ������ "�".
			eFigure = eCross;

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
				// �� ��� �����.
				// ������ �������� ��� �� ���������!	// TODO algoritm or random
				SendMessage(
					//GetDlgItem(hWnd, LOWORD(wParam)),
					GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber),	// TODO 5 �������� �� ���������� randShot
					BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
					LPARAM(hCross));

				// ������ ������
				eNowWalks = eWalkUser;
				// ������ ������
				eFigure = eRound;

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
			
			if (eNowWalks == eWalkUser)
			{

				// ������ ������.
				if (eFigure == eCross)
				{
					// ������ "�������".
					SendMessage(
						GetDlgItem(hWnd, LOWORD(wParam)),
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hCross));

					eFigure = eRound;	// ������ ������.
				}
				else if (eFigure == eRound)
				{
					// ������ "�����".
					SendMessage(
						GetDlgItem(hWnd, LOWORD(wParam)),
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hRound));

					eFigure = eCross;	// ������ ������.
				}

				// ��� ������
				// � ������ ������...

				// ����� ����
				/*if (eNowWalks == eWalkComp)
				{
					// ������� � �������� ������ ������� ������
					//

					eNowWalks = eWalkUser;

					SetWindowText(hText, L"��� ���");
				}
				else*/

				eNowWalks = eWalkComp;

				SetWindowText(hText, L"����� ����");

				// ������ ������ ����������.
				EnableWindow(GetDlgItem(hWnd, LOWORD(wParam)), NULL);
			}
			

			

			/*====================================================================================*/
			// �������� ���� ����
			if (eNowWalks == eWalkComp)
			{
				randNumber = (rand() % 9);

				// �������� ���� ������ - ���� ���� �� ��������!	// TODO re


				// ������ �������� ��� �� ���������!	// TODO algoritm or random

				// ������ ������.
				if (eFigure == eCross)
				{
					// ������ "�������".
					SendMessage(
						GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber),	// TODO 5 �������� �� ���������� randShot
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hCross));

					eFigure = eRound;	// ������ ������.
				}
				else if (eFigure == eRound)
				{
					// ������ "�����".
					SendMessage(
						GetDlgItem(hWnd, IDC_BUTTON_xo_1 + randNumber),	// TODO 5 �������� �� ���������� randShot
						BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
						LPARAM(hRound));

					eFigure = eCross;	// ������ ������.
				}

				// ������ ������
				eNowWalks = eWalkUser;
				// ��������� ��� ���� ������
				SetWindowText(hText, L"��� ���");

				// ������ ������ ����������.
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