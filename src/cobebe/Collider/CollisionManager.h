#include <vector>
#include <memory>

namespace cobebe
{
	class Collider;

	/**
	* \brief 
	*/
	class CollisionManager
	{
	public:
		/**
		* \brief 
		*/
		void checkColliding();

	private:
		std::vector<std::weak_ptr<Collider>> m_colliders;

		void checkCollisions(int _id);


	};
}