#include <cobebe/Renderer/AnimationController.h>
#include <glwrap/glwrap.h>
#include <list>

namespace cobebe
{
	class ObjPartAnimation;
	class Renderer;

	class ObjAnimationController : public AnimationController
	{
	public:
		ObjAnimationController(std::shared_ptr<glwrap::VertexArray> _model);
		~ObjAnimationController();

		void loadAnimation(std::string _path);

		void setAnimationTime(int _id, float _time);

		int checkName(std::string& _name);

		void setToDraw();
		void resetModel() { m_model->disableAllAnimations(); }

	private:
		friend class Renderer;

		std::list<std::shared_ptr<ObjPartAnimation> > m_animations;
		std::shared_ptr<glwrap::VertexArray> m_model;

		AnimationValues* checkId(int _id);

	};
}