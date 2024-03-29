#include "text.h"
#include "../../../components/modulos/renderables/renderable.h"
#include "../../../components/src/entity.h"


renderable::Text::Text() {
	numeroInstancias++;
	const char* fuenteLetra = "H:\\Desarrollo\\motor_videojuegos_2D\\recursos\\RobotoMono-VariableFont_wght.ttf";
	if (fuentesLetra.find(fuenteLetra) == fuentesLetra.end()) {
		FT_Error	error;
		FT_Library libreria;
		error = FT_Init_FreeType(&libreria);
		if (error) {
			DBG_F("Tenemos un error al cargar la librer�a de fuentes de letra");
			return;
		}
		FT_Face face;
		error = FT_New_Face(libreria,
			fuenteLetra,
			0,
			&face);
		if (error == FT_Err_Unknown_File_Format) {
			DBG_F("No hemos encontrado el fichero de fuente de letra %", fuenteLetra);
			FT_Done_FreeType(libreria);
		} else if (error) {
			DBG_F("No hemos podido carga la fuente de letra %", fuenteLetra);
			FT_Done_FreeType(libreria);
		}
		if (error) {
			return;
		}
		//Configuramos el tama�o del pixel
		FT_Set_Pixel_Sizes(face, 0, tama�oLetra);
		fuentesLetra[fuenteLetra] = std::make_tuple(libreria, face);
	}
	std::tie(libreriaParticular, faceParticular) = fuentesLetra[fuenteLetra];
	borrar();

	DBG_F("Tengo la librer�a de FREETYPE cargada");
}

renderable::Text::~Text() {
	numeroInstancias--;
	if (numeroInstancias == 0) {
		for (auto fuente : fuentesLetra) {
			auto [libreria, face] = std::get<1>(fuente);
			FT_Done_Face(face);
			FT_Done_FreeType(libreria);
		}
		fuentesLetra.clear();
	}
	delete[] texto;
}





std::tuple<unsigned, unsigned> renderable::Text::pintarTexto() {
	if (libreriaParticular == 0) {
		return std::make_tuple(0,0);
	}
	borrar();
	
	FT_Error	error;
	
	//error = FT_Set_Char_Size(face, 0, tama�oLetra, 72, 72);
	
	FT_GlyphSlot  slot = faceParticular->glyph;

	float anchoTexto = (tama�oLetra + 6) * longitudTexto;
	float anchoTextoColor = anchoTexto * 4;
	float altoTexto = (tama�oLetra + 2);
	double tama�oBitMap = anchoTextoColor * altoTexto;
	float* mapaPixeles = new float[tama�oBitMap];
	//Limpiamos el mapa de bits
	unsigned t = anchoTexto* altoTexto;
	unsigned iP = 0;
	/*for (unsigned i = 0; i < t; i++) {
		if (i < t / 2) {
			mapaPixeles[iP++] = 0.f;
			mapaPixeles[iP++] = 0.f;
			mapaPixeles[iP++] = 1.f;
		} else {
			mapaPixeles[iP++] = 0.f;
			mapaPixeles[iP++] = 1.f;
			mapaPixeles[iP++] = 0.f;
		}
		mapaPixeles[iP++] = 1.f;
	}/**/
	for (unsigned i = 0; i < tama�oBitMap; i++) {
		mapaPixeles[iP++] = 0.f;
	}
	unsigned x = 0;
	unsigned y = 0;
	unsigned posicionPixel = 0;
	
	for (int i = 0; i < longitudTexto; i++) {
		FT_UInt glyph_index = FT_Get_Char_Index(faceParticular, texto[i]);

		error = FT_Load_Glyph(faceParticular, glyph_index, FT_LOAD_DEFAULT);
		if (error)
			continue;
		error = FT_Render_Glyph(faceParticular->glyph, FT_RENDER_MODE_NORMAL);
		if (error)
			continue;
		FT_Bitmap m;
		//TODO: Quiz�s es mejor llevarlo a un m�todo, para simplificar el c�digo
		unsigned posGlyph = 0;
		float numColores = (float)(slot->bitmap.num_grays-1);
		unsigned fila = (anchoTextoColor * (altoTexto - slot->bitmap_top));
		unsigned posPixel = posicionPixel + fila;
		for (int yF = 0; yF <slot->bitmap.rows; yF++) {
			for (int xF = 0; xF < slot->bitmap.width; xF++) {
				if (posPixel + 4 < tama�oBitMap) {
					mapaPixeles[posPixel + 0] = rColor;
					mapaPixeles[posPixel + 1] = gColor;
					mapaPixeles[posPixel + 2] = bColor;
					/*if (slot->bitmap.buffer[posGlyph++] <100) {
						mapaPixeles[posPixel + 3] = aColor * 0;
					} else {
						mapaPixeles[posPixel + 3] = aColor * ((float)slot->bitmap.buffer[posGlyph] / numColores);
					}/**/
					mapaPixeles[posPixel + 3] = aColor * ((float)slot->bitmap.buffer[posGlyph++] / numColores);
					//mapaPixeles[posPixel + 3] = aColor;
				}
				posPixel += 4;
			}
			fila += anchoTextoColor;
			posPixel = posicionPixel+fila ;
		}
		posicionPixel += (slot->bitmap_left + slot->bitmap.width)*4;
	}



	float fW = (float)(anchoTexto / (Screen::getWidth() / 2.f));
	float fH = (float)(altoTexto / (Screen::getHeight() / 2.f));
	float fX = (float)(0 / (Screen::getWidth() / 2.f));
	float fY = (float)(0 / (Screen::getHeight() / 2.f));
	float fZ = (float) 0;
	float fW_2 = fW / 2.f;
	float fH_2 = fH / 2.f;
	
	std::vector<float**> triangulos;

	triangulos.push_back(new float* [3]{
		new float[3] {fX - fW_2,fY + fH, fZ},
		new float[3] {fX - fW_2,fY, fZ},
		new float[3] {fX + fW_2,fY, fZ},
		}
	);
	triangulos.push_back(new float* [3]{
		new float[3] {fX + fW_2,fY, fZ},
		new float[3] {fX + fW_2,fY + fH, fZ},
		new float[3] {fX - fW_2,fY + fH, fZ},
		}
	);
	std::vector<float*> colores;
	colores.push_back(
		new float[4]{ 1.f,1.f,1.f, 1.f }
	);
	colores.push_back(
		new float[4]{ 1.f,1.f,1.f, 1.f }
	);

	modules::graphics::Material material;
	modules::graphics::TextureImg::FORMAT_COLOR formato;
	modules::resources::Resource* res = Module::get<modules::resources::Resource>();
	material.setTexture(mapaPixeles, tama�oBitMap, anchoTexto, altoTexto);
	idMaterial=setMaterial(material,idMaterial);

	float** uv = new float* [6]{
		new float[2]{0, 0},
		new float[2]{0, 1.f},
		new float[2]{1.f, 1.f},
		new float[2]{1.f, 1.f},
		new float[2]{1.f, 0},
		new float[2]{0, 0.f},
	};/**/


	setTriangles(&triangulos, &colores, NULL, uv, renderable::Object::MODE_COLOR::TEXTURE);

	delete[]colores[0];
	delete[]colores[1];
	colores.clear();
	for (auto itr = triangulos.begin(); itr != triangulos.end(); itr++) {
		for (int i = 0; i < 3; i++) {
			delete[](*itr)[i];
		}
		delete (*itr);
	}
	for (int i = 0; i < 6; i++) {
		delete[]uv[i];
	}
	delete[]uv;/**/


	delete[] mapaPixeles;
	
	RenderableComponent* renderizador = getRenderable();
	if (renderizador) {
		renderizador->setUpdated(true);
	}/**/
	return std::tuple<unsigned,unsigned>(anchoTexto, altoTexto);
}



/**
* Pone el texto a pintar. Set the text to paint in screen
* @param chat * text Texto a pintar, deber� teminar en \0. Text to paint.
*/
std::tuple<unsigned, unsigned> renderable::Text::setText(const char* text) {
	bool cambio = false;
	unsigned longitudTextoActual = 0;
	while (text[longitudTextoActual] != '\0' && longitudTextoActual < LENGTH_TEXT_MAX){
		if (cambio || texto[longitudTextoActual] != text[longitudTextoActual]) {
			cambio = true;
			texto[longitudTextoActual] = text[longitudTextoActual];
		}
		longitudTextoActual++;
	}
	
	texto[longitudTextoActual] = '\0';
	if (cambio || longitudTexto != longitudTextoActual) {
		longitudTexto = longitudTextoActual;
		std::tie(anchoTexto,altoTexto)= pintarTexto();
	}

	return std::tuple<unsigned, unsigned>(anchoTexto, altoTexto);
}
void renderable::Text::setTriangles(std::vector<float**>* vectors, std::vector<float*>* colors, std::vector<float**>* normals, float** uvs, renderable::Object::MODE_COLOR mode) {
	modoColor = mode;

	numeroVertices = vectors->size() * 3;
	numCoordenadas = numeroVertices * 12; //3+3+4+2 (3 coordenadas + 3 normales + 4 color + 2 uv
	int numComponentes = numeroVertices * 3;
	vertices = new float[numComponentes];
	normales = new float[numComponentes];
	colores = new float[numeroVertices * 4];
	this->uvs = new float[numeroVertices * 2]; //Solo hay dos componentes por uv
	int iMalla = 0;
	int iNormales = 0;
	int iColores = 0;
	int iUVs = 0;

	for (int i = 0; i < vectors->size(); i++) {
		//No comprobamos que efectivamente existan al menos 3 coordenadas para acelerar el proceso de carga.
		float** vertice = vectors->operator[](i);
		for (int iV = 0; iV < 3; iV++) {
			for (int iC = 0; iC < 3; iC++) {
				vertices[iMalla++] = vertice[iV][iC];
			}
		}
		float normal[3] = { 0.f,0.f,1.f };
		if (normals) {
			for (int iN = 0; iN < 3; iN++) {
				for (int jN = 0; jN < 3; jN++) {
					normales[iNormales++] = normals->operator[](i)[iN][jN];
				}
			}
		} else {

			normal[0] = (vertice[0][1] - vertice[1][1]) * (vertice[0][2] + vertice[1][2]) +
				(vertice[1][1] - vertice[2][1]) * (vertice[1][2] + vertice[2][2]) +
				(vertice[2][1] - vertice[0][1]) * (vertice[2][2] + vertice[0][2]);
			normal[1] = (vertice[0][2] - vertice[1][2]) * (vertice[0][0] + vertice[1][0]) +
				(vertice[1][2] - vertice[2][2]) * (vertice[1][0] + vertice[2][0]) +
				(vertice[2][2] - vertice[0][2]) * (vertice[2][0] + vertice[0][0]);
			normal[2] = (vertice[0][0] - vertice[1][0]) * (vertice[0][1] + vertice[1][1]) +
				(vertice[1][0] - vertice[2][0]) * (vertice[1][1] + vertice[2][1]) +
				(vertice[2][0] - vertice[0][0]) * (vertice[2][1] + vertice[0][1]);
			normales[iNormales++] = normal[0];
			normales[iNormales++] = normal[1];
			normales[iNormales++] = normal[2];
			normales[iNormales++] = normal[0];
			normales[iNormales++] = normal[1];
			normales[iNormales++] = normal[2];
			normales[iNormales++] = normal[0];
			normales[iNormales++] = normal[1];
			normales[iNormales++] = normal[2];
		}
		/**/
		/* Calculo obtenido de https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal */

		//Se repite 3 veces porque cada vertice del mismo triangulo tiene la misma normal


		//LOG_DBG("Longitud del array %", sizeof(colors));
		if (colors->size() > i) {
			for (int iC = 0; iC < 3; iC++) {
				for (int jC = 0; jC < 4; jC++) {
					colores[iColores++] = colors->operator[](i)[jC];
				}

			}
		} else {
			for (int iC = 0; iC < 3; iC++) {
				for (int jC = 0; jC < 4; jC++) {
					colores[iColores++] = 1.0f;
				}
			}
		}
		if (uvs == NULL) {
			for (int iC = 0; iC < 3; iC++) {
				for (int jC = 0; jC < 2; jC++) {
					this->uvs[iUVs + jC] = 1.0f;
				}
				iUVs += 2;
			}
		} else {
			for (int iC = 0; iC < 3; iC++) {
				for (int jC = 0; jC < 2; jC++) {
					this->uvs[iUVs + jC] = uvs[i * 3 + iC][jC];
				}
				iUVs += 2;
			}
		}

	}
}


std::map<const char*, std::tuple< FT_Library, FT_Face>> renderable::Text::fuentesLetra;
unsigned renderable::Text::numeroInstancias=0;



