#include <cobebe/Resources/Asset.h>
#include <AL/al.h>
#include <AL/alc.h>

namespace cobebe
{
	class Speaker;

	class Sound : public Asset
	{
	public:
		~Sound();

	private:
		friend class Speaker;

		ALuint m_bufferId;

		void onLoad(const std::string& _path);
		void loadOgg(const std::string& _path, std::vector<char>& _buffer,
			ALenum& _format, ALsizei& _freq, bool _mono);

	};
}