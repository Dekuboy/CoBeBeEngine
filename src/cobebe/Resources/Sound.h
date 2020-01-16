#include <cobebe/Resources/Asset.h>
#include <cobebe/Resources/Resources.h>
#include <AL/al.h>
#include <AL/alc.h>

namespace cobebe
{
	class Speaker;

	/**
	* \brief Stores a sound to be played by Speaker
	*/
	class Sound : public Asset
	{
	public:
		~Sound();

	private:
		friend class Speaker;

		ALuint m_bufferId; ///< Sound buffer loaded in OpenAL

		void onLoad(const std::string& _path);
		/**
		* \brief Loads the ogg file as a sound to OpenAL
		*/
		void loadOgg(const std::string& _path, std::vector<char>& _buffer,
			ALenum& _format, ALsizei& _freq, bool _mono);

	};
}