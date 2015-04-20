//-----------------------------------------------------------------------------
///
//      Kszta�t obiektu definiowany jest w przestrzeni modelu. Obiekty mo�emy 
//		przemieszcza� (translacja), obraca� (rotacja), a tak�e zmienia� ich wielko��
//		(skalowanie), u�ywaj�c "transformacji �wiata" (ang. world transform). 
//		Umieszczamy w ten spos�b obiekt w uk�adzie wsp�rz�dnych sceny. Nast�pnie
//		musimy w tym uk�adzie ustawi� kamer� (oko obserwatora), przez kt�r� b�dziemy
//		widzie� to, co znajduje si� na scenie. Robimy to za po�rednictwem tzw. macierzy
//		widoku. Ostatnim przekszta�ceniem jest tzw. transformacja rzutowania 
//		(ang. projection transform), kt�ra umo�liwia wykonanie dwuwymiarowego "zdj�cia"
//		naszej tr�jwymiarowej sceny.
//
//		W niniejszym programie korzystamy z D3DX, zestawu narz�dzi pomocniczych dla D3D.
//		U�ywamy np. funkcji inicjuj�cych macierze transformacji. Aby skorzysta� z D3DX
//		nale�y do��czy� plik nag��wkowy <d3dx9.h> i linkowa� program z bibliotek� d3dx9.lib.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>


//-----------------------------------------------------------------------------
// zmienne globalne
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D = NULL; // obiekt Direct3D (obiekt COM)
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // urz�dzenie wyj�ciowe (odpowiednik kontekstu graficznego GDI)
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // bufor wierzcho�k�w

int g_nTriangles;


// definicja typu wierzcho�ka
struct CUSTOMVERTEX
{
	FLOAT x, y, z;					// wsp�rz�dne wierzcho�ka
	FLOAT norm_x, norm_y, norm_z;	// normalna do powierzchni obiektu wyprowadzona z wierzcho�ka
};

// definiujemy "flexible vertex format" (FVF) 
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL)


//-----------------------------------------------------------------------------
// Nazwa: InitD3D()
// Opis: inicjacja Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)
{
	// tworzymy obiekt D3D (obiekt COM)
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Ustawiamy struktur�, s�u��c� do utworzenia urz�dzenia wyj�ciowego (D3DDevice)
	// Poniewa� tworzymy grafik� 3D, urz�dzenie musi mie� bufor z.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;		// w��czamy bufor z
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// tworzymy urz�dzenie wyj�ciowe (D3DDevice)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// wy��czamy usuwanie niewidocznych powierzchni 
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// w��czamy bufor z
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}




//-----------------------------------------------------------------------------
// Nazwa: InitGeometry()
// Opis: tworzenie obiekt�w (zawarto�ci sceny) 
//-----------------------------------------------------------------------------
HRESULT InitGeometry()
{
	// Tworzymy dwa tr�jk�ty - ka�dy ma 3 wierzcho�ki opisane przez 6 liczb. 

	CUSTOMVERTEX g_Vertices[] =
	{
		// tr�jk�t 1 (przedni)
		/*	{  -2.0f, 3.0f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{  4.0f, 2.0f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{  -2.0f, 18.0f, 0.25f, 0.0f, 0.0f, 1.0f, },*/

		{ -0.5f, 1.0f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ -0.5f, -0.5f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ 0.0f, -0.5f, 0.25f, 0.0f, 0.0f, 1.0f, },
		//ten drugi
		{ -0.5f, 1.0f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ -0.0f, 1.0f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ 0.0f, -0.5f, 0.25f, 0.0f, 0.0f, 1.0f, },
		//trzeci
		{ -0.5f, 1.0f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ -0.0f, 0.2f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ 0.0f, 0.2f, 0.25f, 0.0f, 0.0f, 1.0f, },

		// tr�jk�t 2 (tylny)
		{ 0.0f, -0.5f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ 0.0f, -0.2f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ 0.3f, -0.2f, 0.25f, 0.0f, 0.0f, 1.0f, },

		{ 0.3f, -0.5f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ 0.0f, -0.5f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ 0.3f, -0.2f, 0.25f, 0.0f, 0.0f, 1.0f, },

		{ 0.3f, 1.0f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ -0.0f, 1.0f, 0.25f, 0.0f, 0.0f, 1.0f, }, //-
		{ 0.0f, 0.8f, 0.25f, 0.0f, 0.0f, 1.0f, },

		{ 0.3f, 1.0f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ 0.3f, 0.8f, 0.25f, 0.0f, 0.0f, 1.0f, }, //-
		{ 0.0f, 0.8f, 0.25f, 0.0f, 0.0f, 1.0f, },

		{ 0.2f, 0.8f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ -0.0f, 0.6f, 0.25f, 0.0f, 0.0f, 1.0f, }, //-
		{ 0.0f, 0.8f, 0.25f, 0.0f, 0.0f, 1.0f, },

		{ 0.0f, -0.2f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ 0.2f, -0.2f, 0.25f, 0.0f, 0.0f, 1.0f, },
		{ 0.0f, -0.0f, 0.25f, 0.0f, 0.0f, 1.0f, },


		////////////////////////////////////////////


		{ -0.5f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ 0.0f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, },
		//ten drugi
		{ -0.5f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ -0.0f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ 0.0f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, },
		//trzeci
		{ -0.5f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ -0.0f, 0.2f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ 0.0f, 0.2f, 0.5f, 0.0f, 0.0f, 1.0f, },

		// tr�jk�t 2 (tylny)
		{ 0.0f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ 0.0f, -0.2f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ 0.3f, -0.2f, 0.5f, 0.0f, 0.0f, 1.0f, },

		{ 0.3f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ 0.0f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ 0.3f, -0.2f, 0.5f, 0.0f, 0.0f, 1.0f, },

		{ 0.3f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ -0.0f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, }, //-
		{ 0.0f, 0.8f, 0.5f, 0.0f, 0.0f, 1.0f, },

		{ 0.3f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ 0.3f, 0.8f, 0.5f, 0.0f, 0.0f, 1.0f, }, //-
		{ 0.0f, 0.8f, 0.5f, 0.0f, 0.0f, 1.0f, },

		{ 0.2f, 0.8f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ -0.0f, 0.6f, 0.5f, 0.0f, 0.0f, 1.0f, }, //-
		{ 0.0f, 0.8f, 0.5f, 0.0f, 0.0f, 1.0f, },

		{ 0.0f, -0.2f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ 0.2f, -0.2f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ 0.0f, -0.0f, 0.5f, 0.0f, 0.0f, 1.0f, },

		/*{ 0.5f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ 0.3f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, },
		{ 0.0f, -0.0f, 0.5f, 0.0f, 0.0f, 1.0f, },*/

	};

	// WA�NE - LICZBA TR�JK�T�W
	g_nTriangles = 18;

	// tworzenie bufora wiercho�k�w
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(3 * g_nTriangles*sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}

	// kopiujemy dane wierzcho�k�w z tablicy g_Vertices[] do bufora DX
	VOID* pVertices;
	if (FAILED(g_pVB->Lock(0, sizeof(g_Vertices), (void**)&pVertices, 0)))
		return E_FAIL;
	memcpy(pVertices, g_Vertices, sizeof(g_Vertices));
	g_pVB->Unlock();

	return S_OK;
}




//-----------------------------------------------------------------------------
// Nazwa: Cleanup()
// Opis: zwalnianie zainicjowanych wcze�niej obiekt�w 
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if (g_pVB != NULL)
		g_pVB->Release();

	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}



//-----------------------------------------------------------------------------
// Nazwa: SetupMatrices()
// Opis: ustawienie macierzy �wiata, widoku i rzutowania 
//-----------------------------------------------------------------------------
VOID SetupMatrices()
{
	// macierz �wiata b�dzie definiowa� jedynie obr�t obiekt�w w ok� osi Y
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	// Ustawiamy macierz obrotu tak, aby uzyska� 1 pe�ny obr�t (2*PI radian�w)
	// co 10 sekund (czyli 10000ms). Aby unikn�� k�opot�w zwi�zanych z wykonywaniem
	// oblicze� na bardzo du�ych liczbach zmiennoprzecinkowych, wyznaczamy reszt� 
	// z dzielenia czasu systemowego przez okres obrotu przed dokonaniem konwersji
	// na k�t w radianach.
	D3DXMATRIXA16 matRotation;
	UINT  iTime = timeGetTime() % 10000;
	FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 10000.0f;
	D3DXMatrixRotationY(&matRotation, fAngle);

	D3DXMatrixMultiply(&matWorld, &matRotation, &matWorld);

	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// Tworzymy macierz widoku. Mo�na j� zdefiniowa� podaj�c po�o�enie oka,
	// punkt, na kt�ry patrzymy, oraz kierunek pionu. Poni�ej ustawiamy oko 
	// 4 jednostki od pocz�tku uk�adu wzd�u� osi Z i 3 jednostki ponad powierzchni�
	// XZ, patrzymy w pocz�tek uk�adu wsp�rz�dnych, a pion wskazuje o� Y.
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, 4.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtRH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);


	// Dla macierzy rzutowania ustawiamy przekszta�cenie perspektywiczne
	// (dzi�ki kt�remu transformacja sceny tr�jwymiarowej na obraz
	// dwuwymiarowy przebiega z uwzgl�dnieniem perspektywy, a wi�c obiekty
	// znajduj�ce si� dalej s� odwzorowywane jako mniejsze). Aby stworzy�
	// przekszta�cenie perspektywiczne, musimy poda� pole widzenia (1/4 PI
	// to typowa warto��), proporcje osi oraz blisk� i dalek� p�aszczyzn�
	// odcinaj�c� (kt�re okre�laj� odleg�o�ci od oka, przy jakich obiekty nie s�
	// ju� renderowane).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovRH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}


//-----------------------------------------------------------------------------
// Nazwa: SetupLights()
// Opis: ustawienie o�wietlenia sceny
//-----------------------------------------------------------------------------
VOID SetupLights()
{
	// Tworzymy materia�, z kt�rego zbudowany jest obiekt. W danej chwili mo�emy
	// u�ywa� tylko jednego materia�u.
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = 0.2f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 0.8f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 0.2f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	g_pd3dDevice->SetMaterial(&mtrl);

	// Tworzymy jedno, kierunkowe bia�e �wiat�o
	// Musimy te� uruchomi� o�wietlenie u�ywaj�c sta�ej D3DRS_LIGHTING w funkcji SetRenderState
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	vecDir = D3DXVECTOR3(0.0f,
		-0.2f,
		-1.0f);

	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Range = 1000.0f;

	g_pd3dDevice->SetLight(0, &light);
	g_pd3dDevice->LightEnable(0, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}




//-----------------------------------------------------------------------------
// Nazwa: Render()
// Opis: rysowanie sceny
//-----------------------------------------------------------------------------
VOID Render()
{
	// ustawiamy kolor t�a
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 70, 70), 1.0f, 0);

	// rozpocz�cie rysowania sceny
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// ustawienie �wiate� i materia��w 
		SetupLights();

		// ustawienie macierzy �wiata, widoku i rzutowania 
		SetupMatrices();

		g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		// renderowanie zawarto�ci bufora wierzcho�k�w
		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, g_nTriangles);

		g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);

		// zako�czenie rysowania sceny
		g_pd3dDevice->EndScene();
	}

	// wy�wietlenie sceny na ekranie
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//-----------------------------------------------------------------------------
// Nazwa: MsgProc()
// Opis: obs�uga komunikat�w wysy�anych do naszego okna
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int x, y;

	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN: //reakcja na lewy przycisk myszki
	{
							 x = LOWORD(lParam);
							 y = HIWORD(lParam);

							 return 0;
	}

	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}




//-----------------------------------------------------------------------------
// Nazwa: WinMain()
// Opis: program g��wny
//-----------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	// rejestracja klasy okna 
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"GK D3D", NULL };
	RegisterClassEx(&wc);

	// utworzenie okna naszej aplikacji 
	HWND hWnd = CreateWindow("GK D3D", "Grafika Komputerowa: DirectX",
		WS_OVERLAPPEDWINDOW, 100, 100, 512, 512,
		GetDesktopWindow(), NULL, wc.hInstance, NULL);

	// inicjacja Direct3D
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		// utworzenie obiekt�w sceny
		if (SUCCEEDED(InitGeometry()))
		{
			// wy�wietlenie okna
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

			// uruchomienie p�tli obs�ugi komunikat�w
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
					Render();	// <-- RYSOWANIE SCENY
			}
		}
	}

	UnregisterClass("GK D3D", wc.hInstance);
	return 0;
}