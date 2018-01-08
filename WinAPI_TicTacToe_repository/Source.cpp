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


		// ����� �����.
		SetWindowText(hWnd, L"�������� ������");
		SetWindowText(hText, L"��� ������ ���� ������� \"����� ����\"");
		
	

		
		//SetClassLong(hButton_xo[0], GCL_STYLE, styleButton_xo | (LONG)whiteBrush);	// TODO delete  - not work

		return TRUE;

	case WM_COMMAND:
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

			// ??? ����� ����1 ����2?
		}
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
			MessageBox(hWnd, L"����� ������ \"������ ������\"",
				L"��������", MB_OK | MB_ICONINFORMATION);
		}


		// ��� ������� �� ������� ����.
		//if (LOWORD(wParam) == IDC_BUTTON_xo_1)
		if (LOWORD(wParam) >= IDC_BUTTON_xo_1 && LOWORD(wParam) <= IDC_BUTTON_xo_9)
		{

			// ������ "�������".
			SendMessage(
				GetDlgItem(hWnd, LOWORD(wParam)),
				BM_SETIMAGE, WPARAM(IMAGE_BITMAP),
				LPARAM(hCross));
			// ������ "�����".
			// TODO ��� ��� ������...

			// ������ ������ ����������.
			EnableWindow(GetDlgItem(hWnd, LOWORD(wParam)), NULL);

		}

		return TRUE;

	}

	return FALSE;
}



// ��������� bmp	//  TODO ����� ��� ������� ������
//SendMessage(hButton_xo[0], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hCross));
//SendMessage(hButton_xo[1], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hRound));