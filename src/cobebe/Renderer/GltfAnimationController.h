#include <cobebe/Renderer/AnimationController.h>
#include <glwrap/glwrap.h>

namespace cobebe
{
	class Renderer;

	/**
	* \brief Controls skin animation in gltf model
	*/
	class GltfAnimationController : public AnimationController
	{
	public:
		GltfAnimationController(std::shared_ptr<glwrap::GltfModel> _model);
		~GltfAnimationController();

		//void loadAnimation(std::string _path);

		/**
		* \brief Set animation of Id to input time
		*/
		void setAnimationTime(int _id, float _time);

		/**
		* \brief Find Id of input animation name
		*/
		int checkName(std::string& _name);

		/**
		* \brief Applies animation values to attached model
		*/
		void setToDraw();
		/**
		* \brief Disable animations currently playing in model
		*/
		void resetModel() { m_model->disableAllAnimations(); }

	private:
		friend class Renderer;

		std::shared_ptr<glwrap::GltfModel> m_model; //!< Attached model from gltf file
		
		/**
		* \brief Checks that input Id is valid
		*/
		AnimationValues* checkId(int _id);
	};
}