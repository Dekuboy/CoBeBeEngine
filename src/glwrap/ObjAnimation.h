#include <glm/glm.hpp>

#include <vector>
#include <string>

namespace glwrap
{
	class VertexArray;
	class ObjFrame;
	class Context;

	/**
	* \brief Holds information to apply Animation to .obj
	* -Object must hold appropriately named parts in order to apply animation
	* -Animations apply rotation and translation to individual parts
	* -Animations are made up of keyframes to interpolate between
	*/
	class ObjAnimation
	{
	public:
		ObjAnimation(std::shared_ptr<VertexArray> _model);
		~ObjAnimation();

		/**
		* \brief .obj Animation file is read and converted to keyframes
		* -"n" denotes name of animation
		* -"f" denotes new frame of animation
		* -"t" denotes transformation (translate is multiplied by partSize/100 when parsed)
		* -transformation format:
		* t PartName xTranslate yTranslate zTranslate xAngle yAngle zAngle
		*/
		void parse(std::string _path);

		/**
		* \brief Check if Animation is enabled
		*/
		bool getEnabled();
		/**
		* \brief Retrieve Animation name
		*/
		std::string getName();
		/**
		* \brief Set Animation to repeat
		*/
		void setRepeating(bool _switch);
		/**
		* \brief Set Animation to apply when base model is drawn
		*/
		void setEnabled(bool _switch);
		/**
		* \brief Set Animation name to input value
		*/
		void setName(std::string _name);

		/**
		* \brief Get current frame of animation in use
		*/
		std::shared_ptr<ObjFrame> getFrame();
		/**
		* \brief Get interpolated frame between two keyframes
		*/
		std::shared_ptr<ObjFrame> getMergeFrame();
		/**
		* \brief Get current frame number in use
		*/
		int getCurrentFrame();
		/**
		* \brief Get current frame number in use
		*/
		double getTrueCurrentFrame();
		/**
		* \brief Get max frames of animation
		*/
		int getMaxFrames();
		/**
		* \brief Move frame of animation forward by _deltaTime
		*/
		void nextFrame(float _deltaTime);
		/**
		* \brief Set frame to input value
		*/
		void setCurrentFrame(double _currentFrame);

	private:
		friend class Context;

		std::shared_ptr<VertexArray> m_model; //!< Animation attached to Obj
		std::string m_name; //!< Name of animation
		double m_frame; //!< Current frame of animation
		bool m_enabled; //!< Is animation set to play when the model is drawn
		bool m_repeating; //!< Does the animation repeat once it has finished
		std::vector<std::shared_ptr<ObjFrame> > m_frames; //!< Information on the frames of animation
		std::shared_ptr<ObjFrame> m_mergeFrame; //!< Interpolated frame at current animation time
		std::weak_ptr<ObjAnimation> m_self; //!< Pointer to self to place inside ObjFrame
		std::weak_ptr<Context> m_context; //!< Pointer to glwrap context

		/**
		* \brief Split the file string of white space
		*/
		void splitString(std::string input, char splitter, 
			std::vector<std::string>* output);
		/**
		* \brief Generate interpolated frame between keyframes
		*/
		void generateMergeFrame(std::shared_ptr<ObjFrame> a, 
			std::shared_ptr<ObjFrame> b, double weight);

	};
}