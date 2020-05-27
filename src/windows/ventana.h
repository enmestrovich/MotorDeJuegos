#ifndef __VENTANAWND
#define __VENTANAWND



#include <iostream>
#include <Windows.h>
#include "../Motor gr�fico/src/motor.h"
#include "../utilidades/librerias/dll.h"
#include "../utilidades/log/log.h"
//#include "..\Motor gr�fico\terceros\opengl\src\opengl.h"



class Ventana {
	private: 
		const char* nombreVentana;
		int comandoVentana;
		HWND hwnd;
		static modulos::graficos::Grafico* motorGrafico;
		
	public: 
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		//static HDC ghDC;

	public: 
		Ventana(const char*, HINSTANCE, int);
		int abrirVentana();
		//static BOOL bSetupPixelFormat(HDC);

};
#endif // !__VENTANAWND