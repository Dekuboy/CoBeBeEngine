#include <glwrap/glwrap.h>
#include <cobebe/Core/Component.h>
#include <list>

namespace cobebe
{
	class ObjPartAnimation;
	class Renderer;

	class ObjAnimationController : public Component
	{
	public:
		ObjAnimationController(std::shared_ptr<glwrap::VertexArray> _model);

		~ObjAnimationController();

		void loadAnimation(std::string _path);

		int playAnimation(std::string _name, bool _repeating = false);
		void playAnimation(int _id, bool _repeating = false);
		int playOnlyAnimation(std::string _name, bool _repeating = false);
		void playOnlyAnimation(int _id, bool _repeating = false);
		int stopAnimation(std::string _name);
		void stopAnimation(int _id);
		void stopAllAnimations();
		int setAnimationSpeed(std::string _name, double _speed);
		void setAnimationSpeed(int _id, double _speed);

		int getAnimationId(std::string _name);
		void incrementAnimations(float _deltaTime);

		void setToDraw();

	private:
		friend class Renderer;

		std::list<std::shared_ptr<ObjPartAnimation> > m_animations;
		std::shared_ptr<glwrap::VertexArray> m_model;

		std::vector<double> m_animationTimes;
		std::vector<bool> m_enabled;
		std::vector<bool> m_repeating;

		std::vector<double> m_speeds;

		void updateValues();

	};
}