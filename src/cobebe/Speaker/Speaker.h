#include <AL/al.h>
#include <AL/alc.h>

#include <string>
#include <vector>
#include <cobebe/Core/Component.h>

namespace cobebe
{
	class Sound;
	class Transform;

	class Speaker : public Component
	{
	public:
		Speaker(const std::string _path);

		~Speaker();

	private:
		ALuint m_sourceId;

		std::weak_ptr<Transform> m_transform; /// Pointer to Transform component
		std::string m_path;
		std::shared_ptr<Sound> m_soundSrc;
		bool m_isPlaying;

		void onInit();
		void onTick();

	};
}