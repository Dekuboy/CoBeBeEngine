#include <vector>
#include <memory>

namespace cobebe
{
	class Core;

	class Keyboard
	{
	public:
		bool isKey(int _key);
		bool isKeyPressed(int _key);
		bool isKeyReleased(int _key);

	private:
		friend class Core;

		std::weak_ptr<Core> m_core;

		const uint8_t* m_state;

		std::vector<int> m_keysPressed;
		std::vector<int> m_keysReleased;

		void onInit();
		void resetKeys();

	};
}