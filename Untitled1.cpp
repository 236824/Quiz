#if defined(UNICODE) && !defined(_UNICODE)
#endif
//#define UNICODE
#include <windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;
const char *WindowsClassName = "ApiWindowClass";
const char *WindowsApplicationName = "Milion tu i teraz"; //1

MSG Message;

#define ODP_A 1000
#define ODP_B 2000
#define ODP_C 3000
#define ODP_D 4000
#define ADD 9000
#define TXT 8000

HWND hText;
/*
LPSTR Bufor, BuforZap, napis;                                          //Do obslugi plikow
DWORD dwRozmiar, dwRozmiarZap, dwPrzeczyt, dwZapisane;          //
HANDLE hPlik;                                                   //
*/
LRESULT CALLBACK WindowProcedure( HWND glowne, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_CREATE:
				CreateWindowExW(0, L"BUTTON", L"+", WS_CHILD | WS_VISIBLE, 5, 5, 20, 20, glowne, (HMENU)ADD, NULL, NULL);

				CreateWindowExW(0, L"Static", L"TEKST", WS_CHILD|WS_VISIBLE|SS_CENTER, 50, 120, 680, 180, glowne, NULL, NULL, NULL);

				CreateWindowExW(0, L"BUTTON", L"A", WS_CHILD | WS_VISIBLE, 80, 320, 300, 90, glowne, (HMENU)ODP_A, NULL, NULL);

				CreateWindowExW(0, L"BUTTON", L"B", WS_CHILD | WS_VISIBLE, 390, 320, 300, 90, glowne, (HMENU)ODP_B, NULL, NULL);

				CreateWindowExW(0, L"BUTTON", L"C", WS_CHILD | WS_VISIBLE, 80, 420, 300, 90, glowne, (HMENU)ODP_C, NULL, NULL);

				CreateWindowExW(0, L"BUTTON", L"D", WS_CHILD | WS_VISIBLE, 390, 420, 300, 90, glowne, (HMENU)ODP_D, NULL, NULL);
				break;

		case WM_COMMAND:
			switch(wParam){
				case ADD:
					MessageBoxW(glowne, L"Dodawanie pytania", L"Komunikat", NULL);
					//void Button_GetText( hwndCtl, napis, 100 );
					CreateWindowExW( WS_EX_CLIENTEDGE, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 25, 5, 700, 100, NULL, (HMENU)TXT, NULL, NULL );
                    //EnableWindow( hText, TRUE );
                    //if(wParam == TXT) break;
					break;
				case ODP_A:
					MessageBoxW(glowne, L"Wybrano A", L"Komunikat", NULL);
					break;
				case ODP_B:
					MessageBoxW(glowne, L"Wybrano B", L"Komunikat", NULL);
					break;
				case ODP_C:
					MessageBoxW(glowne, L"Wybrano C", L"Komunikat", NULL);
					break;
				case ODP_D:
					MessageBoxW(glowne, L"Wybrano D", L"Komunikat", NULL);
					break;

				//	case TXT
				default:
					MessageBoxW(glowne, L"Nic nie wybrano", L"Komunikat", MB_ICONERROR);
					break;
			}
			break;

		case WM_CLOSE:
			DestroyWindow(glowne);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(glowne, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow )
{
	WNDCLASSEX mln; //1
	mln.cbSize = sizeof(WNDCLASSEX);
	mln.style = 0;
	mln.lpfnWndProc = WindowProcedure; //1
	mln.cbClsExtra = 0;
	mln.cbWndExtra = 0;
	mln.hInstance = hInstance;
	mln.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	mln.hCursor = LoadCursor(NULL, IDC_ARROW);
	mln.hbrBackground = (HBRUSH) ( COLOR_WINDOW + 2);//GetStockObject( WHITE_BRUSH );
	mln.lpszMenuName = NULL;
	mln.lpszClassName = WindowsClassName;
	mln.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if ( !RegisterClassEx(&mln)) {
		MessageBox(NULL, "Nie zarejestrowano klasy", "Error", 0);

		return 0;
	}
	//początek obsłógi pliku
	LPSTR Bufor, BuforZap;
    DWORD dwRozmiar, dwRozmiarZap, dwPrzeczyt, dwZapisane;
    HANDLE hPlik;
//w poniższym createfile przy zapisie chyba zamiast open_existing powinno być allwas_create
	hPlik = CreateFile( "test.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL );
        if( hPlik == INVALID_HANDLE_VALUE ) {
            MessageBox( NULL, "Nie można otworzyć pliku.", "Błąd", MB_ICONEXCLAMATION );
            PostQuitMessage( 0 ); // Zakoñcz program
            }
    dwRozmiar = GetFileSize( hPlik, NULL );
        if( dwRozmiar == 0xFFFFFFFF ) {
            MessageBox( NULL, "Nieprawidłowy rozmiar pliku!", "Błąd", MB_ICONEXCLAMATION );
            PostQuitMessage( 0 ); // Zakoñcz program
        }
/*    dwRozmiarZap = GetWindowTextLength( glowne );
        if( dwRozmiar == 0xFFFFFFFF ) {
            MessageBox( NULL, "Nieprawidłowy rozmiar pliku!", "Błąd", MB_ICONEXCLAMATION );
            PostQuitMessage( 0 ); // Zakoñcz program
        }*/

    Bufor =( LPSTR ) GlobalAlloc( GPTR, dwRozmiar + 1 );
        if( Bufor == NULL ) {
            MessageBox( NULL, "Za mało pamięci!", "Błąd", MB_ICONEXCLAMATION );
            PostQuitMessage( 0 ); // Zakoñcz program
        }
    BuforZap =( LPSTR ) GlobalAlloc( GPTR, dwRozmiarZap + 1 );
        if( Bufor == NULL ) {
            MessageBox( NULL, "Za mało pamiêci!", "Błąd", MB_ICONEXCLAMATION );
            PostQuitMessage( 0 ); // Zakoñcz program
        }

        if( !ReadFile( hPlik, Bufor, dwRozmiar, & dwPrzeczyt, NULL ) ) {
            MessageBox( NULL, "Błąd czytania z pliku", "Błąd", MB_ICONEXCLAMATION );
            PostQuitMessage( 0 ); // Zakoñcz program
        }
    //  SetWindowText( glowne, Bufor ); // zrób coœ z tekstem, np. wyœwietl go
//*    GetWindowText( glowne, BuforZap, dwRozmiarZap ); // skopiuj do bufora tekst z jakiegoś okna
    Bufor[ dwRozmiar ] = 0;
    BuforZap[ dwRozmiar ] = 0; // dodaj zero na koñcu stringa
  //  SetWindowText( glowne, Bufor ); // zrób coœ z tekstem, np. wyœwietl go
    if( !WriteFile( hPlik, BuforZap, dwRozmiarZap, & dwZapisane, NULL ) ) {
        MessageBox( NULL, "Błąd zapisu do pliku", "Błąd!", MB_ICONEXCLAMATION );
        PostQuitMessage( 0 ); // Zakończ program
    }


	HWND glowne = CreateWindowEx(WS_EX_WINDOWEDGE, WindowsClassName, WindowsApplicationName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
	{
		ShowWindow( glowne, iCmdShow );
		UpdateWindow( glowne );

		MessageBox(NULL, "Zaczynasz grę o milion! wybieraj odpowiedzi na zadane pytania!", "", MB_ICONINFORMATION | MB_OK);
		//hText = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_DISABLED | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, 25, 5, 700, 100, glowne, (HMENU)TXT, hInstance, NULL );
		//HWND hText = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, 25, 5, 700, 100, glowne, (HMENU)TXT, hInstance, NULL );
		SetWindowText( hText, "Wpisz tu coś" );
		DWORD dlugosc = GetWindowTextLength( hText );
        LPSTR Bufor =( LPSTR ) GlobalAlloc( GPTR, dlugosc + 1 );
        GetWindowText( hText, Bufor, dlugosc + 1 );
	}
		while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
		}


//    GlobalFree( Bufor ); // Zwolnij bufor
 //   GlobalFree( BuforZap );
//    CloseHandle( hPlik ); // Zamknij plik
}
