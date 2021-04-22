#include <cobebe/Renderer/AnimationController.h>
#include <glwrap/glwrap.h>

namespace cobebe
{
	class Renderer;

	class GltfAnimationController : public AnimationController
	{
	public:
		GltfAnimationController(std::shared_ptr<glwrap::GltfModel> _model);
		~GltfAnimationController();

		//void loadAnimation(std::string _path);

		void setAnimationTime(int _id, float _time);

		int checkName(std::string& _name);

		void setToDraw();
		void resetModel() { m_model->disableAllAnimations(); }

	private:
		friend class Renderer;

		std::shared_ptr<glwrap::GltfModel> m_model;

		AnimationValues* checkId(int _id);
	};
}