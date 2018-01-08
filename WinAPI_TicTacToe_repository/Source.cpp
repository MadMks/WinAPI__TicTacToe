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

	/*static HWND hButton_xo_1;*/
	static HWND hButton_xo[9];

	static HBITMAP hCross, hRound;

	// ������ ����� ������ ������.
	/*HBRUSH whiteBrush = CreateSolidBrush(RGB(0, 255, 0));
	UINT styleButton_xo = GetClassLong(hButton_xo[0], GCL_STYLE);
	SetClassLong(hButton_xo[0], GCL_STYLE, styleButton_xo | (LONG)whiteBrush);*/
	//static HBRUSH whiteBrush;

	switch (uMessage)
	{
	case WM_CLOSE:
		// ��������� ����������� ������.
		DestroyWindow(hWnd); // ��������� ����.
		PostQuitMessage(0); // ������������� ���� ��������� ���������.
		return TRUE;

	case WM_PAINT:
	//	/*MessageBox(hWnd, L"wm paint",
	//		L"��������", MB_OK | MB_ICONINFORMATION);*/
		return TRUE;
	//case WM_CTLCOLORBTN:
		/*clrs = RGB(0, 255, 0);
		whiteBrush = CreateSolidBrush(clrs);
		return LRESULT(whiteBrush);*/

	case WM_INITDIALOG:
		// �������� Handle.
		hNewGame = GetDlgItem(hWnd, IDC_BUTTON_NewGame);
		hWalkFirst = GetDlgItem(hWnd, IDC_CHECK_WalkFirst);
		// �������� Handle �����������.					// TODO delete !?
		hEasyHard = GetDlgItem(hWnd, IDC_RADIO_EasyLevel);	// TODO ���� CheckRadioButton �� ������� delete
		// �������� ����������� ������ (��).
		/*hButton_xo_1 = GetDlgItem(hWnd, IDC_BUTTON_xo_1);*/
		for (int i = 0; i < 9; i++)
		{
			hButton_xo[i] = GetDlgItem(hWnd, IDC_BUTTON_xo_1 + i);
		}

		// ��������� bmp "�������", � "�����" � �������� �� Handle.
		hCross = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_x));
		hRound = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_x));

		// ���������� ������ "������ �������".
		CheckRadioButton(hWnd, IDC_RADIO_EasyLevel, IDC_RADIO_HardLevel, IDC_RADIO_EasyLevel);
		// ���������� ������ "������ ������" ����.
		SendMessage(hWalkFirst, BM_SETCHECK, WPARAM(BST_UNCHECKED), NULL);

	

		// ��������� bmp	//  TODO ����� ��� ������� ������
		SendMessage(hButton_xo[0], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hCross));
		

		return TRUE;

	case WM_COMMAND:
		//
		if (LOWORD(wParam) == IDC_BUTTON_NewGame)
		{
			MessageBox(hWnd, L"����� ������ \"����� ����\"",
				L"��������", MB_OK | MB_ICONINFORMATION);
		}
		else if (LOWORD(wParam) == IDC_RADIO_EasyLevel)
		{
			MessageBox(hWnd, L"����� ����� \"������ �������\"",
				L"��������", MB_OK | MB_ICONINFORMATION);
		}
		else if (LOWORD(wParam) == IDC_RADIO_HardLevel)
		{
			MessageBox(hWnd, L"����� ����� \"������� �������\"",
				L"��������", MB_OK | MB_ICONINFORMATION);
		}
		else if (LOWORD(wParam) == IDC_CHECK_WalkFirst)
		{
			MessageBox(hWnd, L"����� ������ \"������ ������\"",
				L"��������", MB_OK | MB_ICONINFORMATION);
		}


		if (LOWORD(wParam) == IDC_BUTTON_xo_1)
		{
			//SendMessage(hButton_xo_1, BM_SETIMAGE, WPARAM(IMAGE_BITMAP), (LPARAM)GetDlgItem(hWnd, IDB_BITMAP_x));	// TODO re
		}

		return TRUE;

	}

	return FALSE;
}