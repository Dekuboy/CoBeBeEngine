#include <AL/al.h>
#include <AL/alc.h>

#include <string>
#include <vector>
#include <cobebe/Core/Component.h>

namespace cobebe
{
	class Sound;

	class Speaker : public Component
	{
	public:
		Speaker(const std::string _path);

		~Speaker();

	private:
		ALuint m_sourceId;

		std::string m_path;
		std::shared_ptr<Sound> m_soundSrc;
		bool m_isPlaying;

		void onInit();
		void onTick();

	};
}