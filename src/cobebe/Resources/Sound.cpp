#include <cobebe/Resources/Sound.h>
#include <cobebe/Speaker/stb_vorbis.h>

namespace cobebe
{
	Sound::~Sound()
	{
		/*
		* Clean up OpenAL data.
		*
		* Note: Sound Buffers cannot be freed until all sources using it are deleted
		*/
		alDeleteBuffers(1, &m_bufferId);
	}

	void Sound::onLoad(const std::string& _path)
	{
		/*
		* Create OpenAL sound buffer
		*/
		m_bufferId = 0;
		alGenBuffers(1, &m_bufferId);

		ALenum format = 0;
		ALsizei freq = 0;
		std::vector<char> bufferData;
		loadOgg(_path, bufferData, format, freq, 1);

		alBufferData(m_bufferId, format, &bufferData.at(0),
			static_cast<ALsizei>(bufferData.size()), freq);
	}

	void Sound::loadOgg(const std::string& _path, std::vector<char>& _buffer,
		ALenum& _format, ALsizei& _freq, bool _mono)
	{
		int channels = 0;
		int sampleRate = 0;
		short* output = NULL;

		size_t samples = stb_vorbis_decode_filename(
			FileManager::returnPath(_path).c_str(), &channels, &sampleRate, &output);

		if (samples == -1)
		{
			throw std::exception();
		}

		// Record the sample rate required by OpenAL
		_freq = sampleRate;

		// Record the format required by OpenAL
		if (channels == 1)
		{
			_format = AL_FORMAT_MONO16;
		}
		else
		{
			if (_mono)
			{
				// Force format to be mono (Useful for positional audio)
				_format = AL_FORMAT_MONO16;
				_freq *= 2;
			}
			else
			{
				_format = AL_FORMAT_STEREO16;
			}
		}

		// Allocate enough space based on short (two chars) multipled by the number of
		// channels and length of clip
		_buffer.resize(sizeof(*output) * channels * samples);
		memcpy(&_buffer.at(0), output, _buffer.size());

		// Clean up the read data
		free(output);
	}
}