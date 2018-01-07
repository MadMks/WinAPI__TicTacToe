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

	switch (uMessage)
	{
	case WM_CLOSE:
		// ��������� ����������� ������.
		DestroyWindow(hWnd); // ��������� ����.
		PostQuitMessage(0); // ������������� ���� ��������� ���������.
		return TRUE;

	case WM_INITDIALOG:
		// �������� ���������� ������.
		hNewGame = GetDlgItem(hWnd, IDC_BUTTON_NewGame);
		// �������� ���������� ������.
		hWalkFirst = GetDlgItem(hWnd, IDC_CHECK_WalkFirst);
		// �������� ���������� �����������.					// TODO delete !?
		hEasyHard = GetDlgItem(hWnd, IDC_RADIO_EasyLevel);	// TODO ���� CheckRadioButton �� ������� delete

		// ���������� ������ "������ �������".
		CheckRadioButton(hWnd, IDC_RADIO_EasyLevel, IDC_RADIO_HardLevel, IDC_RADIO_EasyLevel);
		// ���������� ������ "������ ������" ����.
		SendMessage(hWalkFirst, BM_SETCHECK, WPARAM(BST_UNCHECKED), NULL);

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
		return TRUE;

	}

	return FALSE;
}