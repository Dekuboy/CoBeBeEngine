#include <glwrap/Animation.h>
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
	class ObjAnimation : public Animation
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
		* \brief Get current frame of animation in use
		*/
		std::shared_ptr<ObjFrame> getFrame();
		/**
		* \brief Get interpolated frame between two keyframes
		*/
		std::shared_ptr<ObjFrame> getMergeFrame();
		/**
		* \brief Get max frames of animation
		*/
		int getMaxFrames();
		/**
		* \brief Move frame of animation forward by _deltaTime
		*/
		void nextFrame(float _deltaTime);

	private:
		friend class Context;

		std::shared_ptr<VertexArray> m_model; //!< Animation attached to Obj
		std::vector<std::shared_ptr<ObjFrame> > m_frames; //!< Information on the frames of animation
		std::shared_ptr<ObjFrame> m_mergeFrame; //!< Interpolated frame at current animation time
		std::weak_ptr<ObjAnimation> m_self; //!< Pointer to self to place inside ObjFrame

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