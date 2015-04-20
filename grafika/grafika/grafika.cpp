//-----------------------------------------------------------------------------
///
//      Kszta³t obiektu definiowany jest w przestrzeni modelu. Obiekty mo¿emy 
//		przemieszczaæ (translacja), obracaæ (rotacja), a tak¿e zmieniaæ ich wielkoœæ
//		(skalowanie), u¿ywaj¹c "transformacji œwiata" (ang. world transform). 
//		Umieszczamy w ten sposób obiekt w uk³adzie wspó³rzêdnych sceny. Nastêpnie
//		musimy w tym uk³adzie ustawiæ kamerê (oko obserwatora), przez któr¹ bêdziemy
//		widzieæ to, co znajduje siê na scenie. Robimy to za poœrednictwem tzw. macierzy
//		widoku. Ostatnim przekszta³ceniem jest tzw. transformacja rzutowania 
//		(ang. projection transform), która umo¿liwia wykonanie dwuwymiarowego "zdjêcia"
//		naszej trójwymiarowej sceny.
//
//		W niniejszym programie korzystamy z D3DX, zestawu narzêdzi pomocniczych dla D3D.
//		U¿ywamy np. funkcji inicjuj¹cych macierze transformacji. Aby skorzystaæ z D3DX
//		nale¿y do³¹czyæ plik nag³ówkowy <d3dx9.h> i linkowaæ program z bibliotek¹ d3dx9.lib.
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
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // urz¹dzenie wyjœciowe (odpowiednik kontekstu graficznego GDI)
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // bufor wierzcho³ków

int g_nTriangles;


// definicja typu wierzcho³ka
struct CUSTOMVERTEX
{
	FLOAT x, y, z;					// wspó³rzêdne wierzcho³ka
	FLOAT norm_x, norm_y, norm_z;	// normalna do powierzchni obiektu wyprowadzona z wierzcho³ka
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

	// Ustawiamy strukturê, s³u¿¹c¹ do utworzenia urz¹dzenia wyjœciowego (D3DDevice)
	// Poniewa¿ tworzymy grafikê 3D, urz¹dzenie musi mieæ bufor z.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;		// w³¹czamy bufor z
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// tworzymy urz¹dzenie wyjœciowe (D3DDevice)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// wy³¹czamy usuwanie niewidocznych powierzchni 
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// w³¹czamy bufor z
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}




//-----------------------------------------------------------------------------
// Nazwa: InitGeometry()
// Opis: tworzenie obiektów (zawartoœci sceny) 
//-----------------------------------------------------------------------------
HRESULT InitGeometry()
{
	// Tworzymy dwa trójk¹ty - ka¿dy ma 3 wierzcho³ki opisane przez 6 liczb. 

	CUSTOMVERTEX g_Vertices[] =
	{
		// trójk¹t 1 (przedni)
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

		// trójk¹t 2 (tylny)
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

		// trójk¹t 2 (tylny)
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

	// WA¯NE - LICZBA TRÓJK¥TÓW
	g_nTriangles = 18;

	// tworzenie bufora wiercho³ków
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(3 * g_nTriangles*sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}

	// kopiujemy dane wierzcho³ków z tablicy g_Vertices[] do bufora DX
	VOID* pVertices;
	if (FAILED(g_pVB->Lock(0, sizeof(g_Vertices), (void**)&pVertices, 0)))
		return E_FAIL;
	memcpy(pVertices, g_Vertices, sizeof(g_Vertices));
	g_pVB->Unlock();

	return S_OK;
}




//-----------------------------------------------------------------------------
// Nazwa: Cleanup()
// Opis: zwalnianie zainicjowanych wczeœniej obiektów 
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
// Opis: ustawienie macierzy œwiata, widoku i rzutowania 
//-----------------------------------------------------------------------------
VOID SetupMatrices()
{
	// macierz œwiata bêdzie definiowaæ jedynie obrót obiektów w okó³ osi Y
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	// Ustawiamy macierz obrotu tak, aby uzyskaæ 1 pe³ny obrót (2*PI radianów)
	// co 10 sekund (czyli 10000ms). Aby unikn¹æ k³opotów zwi¹zanych z wykonywaniem
	// obliczeñ na bardzo du¿ych liczbach zmiennoprzecinkowych, wyznaczamy resztê 
	// z dzielenia czasu systemowego przez okres obrotu przed dokonaniem konwersji
	// na k¹t w radianach.
	D3DXMATRIXA16 matRotation;
	UINT  iTime = timeGetTime() % 10000;
	FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 10000.0f;
	D3DXMatrixRotationY(&matRotation, fAngle);

	D3DXMatrixMultiply(&matWorld, &matRotation, &matWorld);

	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// Tworzymy macierz widoku. Mo¿na j¹ zdefiniowaæ podaj¹c po³o¿enie oka,
	// punkt, na który patrzymy, oraz kierunek pionu. Poni¿ej ustawiamy oko 
	// 4 jednostki od pocz¹tku uk³adu wzd³u¿ osi Z i 3 jednostki ponad powierzchni¹
	// XZ, patrzymy w pocz¹tek uk³adu wspó³rzêdnych, a pion wskazuje oœ Y.
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, 4.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtRH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);


	// Dla macierzy rzutowania ustawiamy przekszta³cenie perspektywiczne
	// (dziêki któremu transformacja sceny trójwymiarowej na obraz
	// dwuwymiarowy przebiega z uwzglêdnieniem perspektywy, a wiêc obiekty
	// znajduj¹ce siê dalej s¹ odwzorowywane jako mniejsze). Aby stworzyæ
	// przekszta³cenie perspektywiczne, musimy podaæ pole widzenia (1/4 PI
	// to typowa wartoœæ), proporcje osi oraz blisk¹ i dalek¹ p³aszczyznê
	// odcinaj¹c¹ (które okreœlaj¹ odleg³oœci od oka, przy jakich obiekty nie s¹
	// ju¿ renderowane).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovRH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}


//-----------------------------------------------------------------------------
// Nazwa: SetupLights()
// Opis: ustawienie oœwietlenia sceny
//-----------------------------------------------------------------------------
VOID SetupLights()
{
	// Tworzymy materia³, z którego zbudowany jest obiekt. W danej chwili mo¿emy
	// u¿ywaæ tylko jednego materia³u.
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = 0.2f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 0.8f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 0.2f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	g_pd3dDevice->SetMaterial(&mtrl);

	// Tworzymy jedno, kierunkowe bia³e œwiat³o
	// Musimy te¿ uruchomiæ oœwietlenie u¿ywaj¹c sta³ej D3DRS_LIGHTING w funkcji SetRenderState
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
	// ustawiamy kolor t³a
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 70, 70), 1.0f, 0);

	// rozpoczêcie rysowania sceny
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// ustawienie œwiate³ i materia³ów 
		SetupLights();

		// ustawienie macierzy œwiata, widoku i rzutowania 
		SetupMatrices();

		g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		// renderowanie zawartoœci bufora wierzcho³ków
		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, g_nTriangles);

		g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);

		// zakoñczenie rysowania sceny
		g_pd3dDevice->EndScene();
	}

	// wyœwietlenie sceny na ekranie
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//-----------------------------------------------------------------------------
// Nazwa: MsgProc()
// Opis: obs³uga komunikatów wysy³anych do naszego okna
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
// Opis: program g³ówny
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
		// utworzenie obiektów sceny
		if (SUCCEEDED(InitGeometry()))
		{
			// wyœwietlenie okna
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

			// uruchomienie pêtli obs³ugi komunikatów
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