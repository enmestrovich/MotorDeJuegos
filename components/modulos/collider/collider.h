#ifndef _COMP_COLLIDER
#define _COMP_COLLIDER

#include <vector>
#include <cmath>
#include <iostream>
#include <limits>
#include "../renderables/renderable.h"

#define M_PI           3.14159265358979323846
#define M_PI2          1.57079632679489661923
#define M_2PI          6.28318530717958647692
namespace collider {
	extern struct Hit;
	class EXPORTAR_COMPONENTE Collider : public Component {
	public:
		enum TYPE {
			BOX_2D
		};
	private:
		/// <summary>
		/// Representa el cubo que contiene el objeto
		/// </summary>
		float limites[6];
		float longitud = 0;
		//std::vector<float *> vertices;

		unsigned numeroVertices;
		std::vector<std::vector<float*>> caras;
		bool esCopia = false;
		//void borrarVertices();
		//virtual void whenChargeEntity();
		void cargarEntidad();
		

		static float checkPolygons(float aX, float aY, float* pA, unsigned lengthA, float bX, float bY, float* pB, unsigned lengthB);

	protected:
		float cX, cY, cZ;

		static std::tuple <float, float> getNormal2D(float x1, float y1, float x2, float y2);
		static float dotProduct2D(float x1, float y1, float x2, float y2);
		static std::tuple <float, float> getMinMax2D(float axisX, float axisY, float* vertex, unsigned numberVertex);
		static std::tuple <bool, bool> checkRangesForContainment(float rangeAMin, float rangeAMax, float rangeBMin, float rangeBMax);
		//float cXCalculada, cYCalculada, cZCalculada;
		friend class Transform;
		virtual void recalcular();
		TYPE tipo;
	public:
		Collider();
		Collider(Entity* entity);
		Collider(Collider& c) {
			//esCopia = true;
			cX = c.cX;
			cY = c.cY;
			cZ = c.cZ;
			longitud = c.longitud;
			/*vertices = new float* [c.numeroVertices];
			numeroVertices = c.numeroVertices;
			for (int i = 0; i < c.numeroVertices; i++) {
				vertices[i] = new float[3]{ c.vertices[i][0],c.vertices[i][1],c.vertices[i][2] };
			}*/

		}
		void setVertices(std::vector<float*>* vertices);
		void setFaces(std::vector< std::vector<const float*>>* faces);
		friend std::ostream& operator<<(std::ostream& os, Collider& c) {
			os << "Centro (" << c.cX << ", " << c.cY << ", " << c.cZ << ") Radio " << c.longitud;
			return os;
		};
		~Collider() {
			//DBG("Borro Collider");
			/*if (vertices != NULL) {
				borrarVertices();
			}*/

		}
		bool isCollisionRay(float xOrigin, float yOrigin, float zOrigin, float xTarget, float yTarget, float zTarget);
		TYPE getType() { return tipo; }
		virtual bool haveCollision(Collider* object) = 0;

		virtual std::vector<Hit> getCollisions() = 0;
		virtual std::vector<Hit> getCollisionsExpanding(float x, float y, float z) = 0;
		virtual std::vector<Hit> getCollisions(float x, float y, float z) = 0;
		

	};
	struct EXPORTAR_COMPONENTE Hit {
		Collider* object=NULL;
		float distance = 0;
		float vX = 0; //Vector de colis�n X
		float vY = 0; //Vector de colis�n Y
		float vZ = 0; //Vector de colis�n Z
		float sX = 0; //Separaci�n en X
		float sY = 0; //Separaci�n en Y
		float sZ = 0; //Separaci�n en Z
		float pX = 0;
		float pY = 0;
		float pZ = 0;
		bool collision = true;
		bool isContainer = false; //Contiene al otro objeto
		bool isContained = false; //Est� contendio en el otro objeto
	};
};

#endif // !_COMP_COLLIDER
