#if defined(UNICODE) && !defined(_UNICODE)
#endif

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const char *WindowsClassName = "ApiWindowClass";
const char *WindowsApplicationName = "Milion tu i teraz";

MSG Message;

#define ODP_A 100
#define ODP_B 200
#define ODP_C 300
#define ODP_D 400
#define ADD 900
#define ADD2 901
#define TXT 800

HWND a_hPrzycisk;
HWND b_hPrzycisk;
HWND c_hPrzycisk;
HWND d_hPrzycisk;
HWND add_hPrzycisk;
HWND AddPyt;
HWND PolePytan;
HWND hWnd;

int nr_pyt=1;

LRESULT CALLBACK WindowProcedure( HWND glowne, UINT msg, WPARAM wParam, LPARAM lParam);
void zapisz_pyt(HWND PolePytan);
void guziki(HWND g);
string wczytaj_pyt();
string wczytaj_odp();
int sprawdz(string odp, int ODP);
string j, l;
void pytanie(HWND glowne)
{
    j=wczytaj_pyt();
    l=wczytaj_odp();
    LPCSTR k=j.c_str(), m=l.c_str();
    PolePytan = CreateWindowEx(0, "STATIC", k, WS_CHILD|WS_VISIBLE|SS_CENTER, 50, 120, 680, 180, glowne, NULL, NULL, NULL);
}

int WINAPI WinMain( HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR szCmdLine,
                   int iCmdShow )
{
    WNDCLASSEX mln;
	mln.cbSize = sizeof(WNDCLASSEX);
	mln.style = 0;
	mln.lpfnWndProc = WindowProcedure;
	mln.cbClsExtra = 0;
	mln.cbWndExtra = 0;
	mln.hInstance = hInstance;
	mln.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	mln.hCursor = LoadCursor(NULL, IDC_ARROW);
	mln.hbrBackground = (HBRUSH) ( COLOR_WINDOW + 2);
	mln.lpszMenuName = NULL;
	mln.lpszClassName = WindowsClassName;
	mln.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if ( !RegisterClassEx(&mln)) {
		MessageBox(NULL, "Nie zarejestrowano klasy", "Error", 0);

		return 0;
	}

	HWND glowne = CreateWindowEx(WS_EX_WINDOWEDGE,
                              WindowsClassName,
                              WindowsApplicationName,
                              WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT,
                              CW_USEDEFAULT,
                              800, 600,
                              NULL,
                              NULL,
                              hInstance,
                              NULL);
	{
		ShowWindow( glowne, iCmdShow );
		UpdateWindow( glowne );

		MessageBox(NULL, "Zaczynasz grÍ o milion! wybieraj odpowiedzi na zadane pytania!", "", MB_ICONINFORMATION | MB_OK);

        guziki(glowne);
        pytanie(glowne);

	}

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
        }

}


LRESULT CALLBACK WindowProcedure( HWND glowne,
                                 UINT msg,
                                 WPARAM wParam,
                                 LPARAM lParam) {

	switch (msg) {
		case WM_CREATE:
		   break;

		case WM_COMMAND:
        {
            switch(wParam){
			    case ADD:

					CreateWindowExW(0, L"BUTTON", L"add", WS_CHILD | WS_VISIBLE, 5, 25, 30, 20, glowne, (HMENU)ADD2, NULL, NULL);
					AddPyt = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 40, 5, 700, 100, glowne, (HMENU)TXT, NULL, NULL );
					break;
				case ODP_A:
				    if(sprawdz(l, ODP_A)==1){
					MessageBoxW(glowne, L"Wybrano A dobrze", L"Komunikat", NULL);
					pytanie(glowne);
				    }
				    else {
                        MessageBox(glowne, "èle! To KONIEC", "Komunikat", NULL);
                        PostQuitMessage(0);
				    }
					break;
				case ODP_B:
					if(sprawdz(l, ODP_B)==1){
					MessageBoxW(glowne, L"Wybrano B dobrze", L"Komunikat", NULL);
					pytanie(glowne);
				    }
				    else {
                        MessageBox(glowne, "èle! To KONIEC", "Komunikat", NULL);
                        PostQuitMessage(0);
				    }
					break;
				case ODP_C:
					if(sprawdz(l, ODP_C)==1){
					MessageBoxW(glowne, L"Wybrano C dobrze", L"Komunikat", NULL);
					pytanie(glowne);
				    }
				    else {
                        MessageBox(glowne, "èle! To KONIEC", "Komunikat", NULL);
                        PostQuitMessage(0);
				    };
					break;
				case ODP_D:
				    if(sprawdz(l, ODP_D)==1){
                        MessageBoxW(glowne, L"Wybrano D dobrze", L"Komunikat", NULL);
                        pytanie(glowne);

				    }
				    else {
                        MessageBox(glowne, "èle! To KONIEC", "Komunikat", NULL);
                        PostQuitMessage(0);
				    }
					break;

                case ADD2:
                    MessageBox(glowne, "Dodano pytanie", "Komunikat", NULL);
                            zapisz_pyt(AddPyt);//instrukcje zczytania z okienka EDIT
                                                //instrukcje zapisu do pliku
					break;
			}
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

void zapisz_pyt(HWND dodaj){
    CHAR Buff[200];
    fstream plik;
    plik.open("test.txt", ios::out | ios::app );

    GetWindowText(dodaj, Buff, 200);
    plik<<Buff<<endl;
    plik.close();
    DestroyWindow(dodaj);
}

string wczytaj_pyt(){
    string linia;
    fstream plik;
    plik.open("test.txt", ios::in);
        for(int i=1; i<=nr_pyt-1; i++)
            getline(plik, linia);
    getline(plik, linia);
    if(plik.eof()) linia = "WYGRA£Eå";
    nr_pyt+=2;
    return linia;
}

string wczytaj_odp(){
    string linia;
    fstream plik;
    plik.open("test.txt", ios::in);
          for(int i=2; i<=nr_pyt-1; i++)
            getline(plik, linia);
    getline(plik, linia);
    return linia;
}

int sprawdz(string odp, int ODP){
    int spr;
    if(odp== "A")  spr = 100;
        else    if(odp== "B")  spr = 200;
                    else    if(odp== "C")  spr = 300;
                                else    if(odp== "D")  spr = 400;

    if (spr==ODP)   return 1;
            else return 0;
}
void guziki(HWND glowne)
{
        HWND a_hPrzycisk = CreateWindowExW(0, L"BUTTON", L"A", WS_CHILD | WS_VISIBLE, 80, 320, 300, 90, glowne, (HMENU)ODP_A, NULL, NULL);

        HWND b_hPrzycisk = CreateWindowExW(0, L"BUTTON", L"B", WS_CHILD | WS_VISIBLE, 390, 320, 300, 90, glowne, (HMENU)ODP_B, NULL, NULL);

        HWND c_hPrzycisk = CreateWindowExW(0, L"BUTTON", L"C", WS_CHILD | WS_VISIBLE, 80, 420, 300, 90, glowne, (HMENU)ODP_C, NULL, NULL);

        HWND d_hPrzycisk = CreateWindowExW(0, L"BUTTON", L"D", WS_CHILD | WS_VISIBLE, 390, 420, 300, 90, glowne, (HMENU)ODP_D, NULL, NULL);

        HWND add_hPrzycisk = CreateWindowExW(0, L"BUTTON", L"+", WS_CHILD | WS_VISIBLE, 5, 5, 20, 20, glowne, (HMENU)ADD, NULL, NULL);

}
