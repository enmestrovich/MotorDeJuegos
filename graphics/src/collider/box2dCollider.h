#ifndef __BOX_COLLIDER
#define __BOX_COLLIDER
#include "../../../components/modulos/collider/collider.h"
#include "../../../components/src/entity.h"
namespace collider {
	class EXPORTAR_UTILIDADES Box2dCollider : public Collider {
	private:
		//float* verticesOrigen = NULL;
		float* vertices = NULL;
		float* verticesExpandidos=NULL;
		void borrarVertices();
		Entity* gizmo = NULL;
		Entity* gizmoExpandido = NULL;
		void whenChargeEntity();
		void recalcular();
		float ancho;
		float alto;
		float ancho_2;
		float alto_2;
		//TODO: Posible punto de obtimizaci�n
		std::vector<Hit> obtenerObjetosColision();
		//TODO: Mejorara quiz�s con un puntero
		Hit obtenerObjetoColisionCaja(Box2dCollider* principal, Box2dCollider *secundario);
	public:

		Box2dCollider(Entity* object = NULL);
		~Box2dCollider();
		void setBox(float x, float y, float width, float height);
		void setBox(float width, float height);
		void setVertex(float* vec1, float* vec2, float* vec3, float* vec4);
		bool haveCollision(Collider* object);
		bool haveCollision(Collider* object, float * vertex);

		

		std::vector<Hit> getCollisions();
		
		/**
		* Get object that collision
		* Obtiene los objetos con lo que colisiona desde el centro actual, hasta el nuevo centro
		* expandiendo el �rea de colisi�n.
		* @param x float 
		* @param y float
		* @param z float
		* @return std::vector<Hit> colecci�n de objetos con los que se colisiona ordenados por distancia de menor a mayos
		**/
		std::vector<Hit> getCollisionsExpanding(float x, float y, float z);
		std::vector<Hit> getCollisions(float x, float y, float z);
		void showGizmo(bool show);

	};
};
#endif // !__BOX_COLLIDER
