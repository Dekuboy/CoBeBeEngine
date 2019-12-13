
namespace cobebe
{
	class Environment
	{
	private:
		float deltaTime;
		unsigned int m_width;
		unsigned int m_height;

	public:
		float getDeltaTime();
		unsigned int getWidth();
		unsigned int getHeight();
	};
}