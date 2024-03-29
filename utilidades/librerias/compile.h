#ifndef __COMPILE
#define __COMPILE
#include <stdlib.h>
#include <string>
#include <thread>
#ifdef WIN32
#include <windows.h>
#endif
#include "../utiles/utilidades.h"
#include "../log/log.h"
#include "../timer/watchdog.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <regex>
extern struct Global;
extern Global global;
EXPORTAR_UTILIDADES class Compile {

private:
	static std::string rutaCompilador;
	static std::string entornoCompilador;
	static void buscarCompilador();
    static enum tipoReg{DOBLE,BOOLEANO,CADENA};
    static void leerRegistro(HKEY clave, const char* subClave, std::string& valor);
	static void leerRegistro(HKEY clave, const char* subClave, bool& valor);
	//static StateCompile estado;
public:
	enum Types{NINJA};
	
	static void compileProject(const char* project, Types tipo, std::function<void()> callbackEnd);
	static void generateProject(const char* project, Types tipo, bool generar = true);
	static const char* pathCompiler();
	static const char* compilerScope();
	static const void checkCompiled(const char* project);
	
};



#endif // !__COMPILE
