#include <cobebe/Renderer/AnimationController.h>
#include <glwrap/glwrap.h>
#include <list>

namespace cobebe
{
	class ObjPartAnimation;
	class Renderer;

	/**
	* \brief Controls part animation in obj model
	*/
	class ObjAnimationController : public AnimationController
	{
	public:
		ObjAnimationController(std::shared_ptr<glwrap::VertexArray> _model);
		~ObjAnimationController();

		/**
		* \brief Load animation to attach to model
		*/
		void loadAnimation(std::string _path);

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

		std::list<std::shared_ptr<ObjPartAnimation> > m_animations; //!< List of part animations
		std::shared_ptr<glwrap::VertexArray> m_model; //!< Attached model from obj file

		/**
		* \brief Checks that input Id is valid
		*/
		AnimationValues* checkId(int _id);

	};
}