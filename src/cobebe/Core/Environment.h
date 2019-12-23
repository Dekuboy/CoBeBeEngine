class Core;
namespace cobebe
{
	class Environment
	{
	public:
		Environment();

		float getDeltaTime();
		int getWidth();
		int getHeight();

	private:
		friend class Core;

		float m_deltaTime;
		int m_width;
		int m_height;

	};
}