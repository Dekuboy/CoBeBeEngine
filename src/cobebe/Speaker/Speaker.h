#include <AL/al.h>
#include <AL/alc.h>

#include <string>
#include <vector>
#include <cobebe/Core/Component.h>

namespace cobebe
{
	class Sound;
	class Transform;

	/**
	* \brief Plays a sound at position relative to current Camera
	*/
	class Speaker : public Component
	{
	public:
		Speaker(const std::string _path);
		Speaker(const std::string _path, bool _isLooping);

		~Speaker();

		bool m_isGlobal; ///< Determine if Sound should play regardless of position

		void stop();

	private:
		ALuint m_sourceId; ///< Sound source added to OpenAL

		std::weak_ptr<Transform> m_transform; ///< Pointer to Transform component
		std::string m_path; ///< Folder path to asset
		std::shared_ptr<Sound> m_soundSrc; ///< Loaded asset using path
		bool m_isPlaying; ///< Check if the sound is currently playing
		bool m_isLooping; ///< Sets the sound as a loop

		void onInit();
		void onPreDisplay();

	};
}