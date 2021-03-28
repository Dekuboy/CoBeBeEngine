#ifndef _GLWRAP_MODEL3D
#define _GLWRAP_MODEL3D
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace glwrap
{
	struct TriFace;
	class Context;

	class Model3D
	{
	public:
		/**
		* \brief Retrieve the size of model based on xyz values
		*/
		virtual glm::vec3 getSize() { return m_size; }
		/**
		* \brief Retrieve all the tri information of the model
		*/
		virtual std::vector<std::shared_ptr<TriFace> > getFaces() { return m_faces; }

		/**
		* \brief Set cull animation
		* -if(true) when ShaderProgram calls cullAndDraw() then
		*    ObjPart will assume non-moving parts are within the view if the
		*    model is in view
		* -useful for smaller objects with moving parts with a larger reach
		*/
		void setCullAnimation(bool _switch) { m_cullAnimated = _switch; }
		/**
		* \brief Get cull animation
		*/
		bool getCullAnimation() { return m_cullAnimated; }

	protected:
		friend class Context;
		friend class ShaderProgram;

		bool m_dirty; //!< If the buffers have been altered, update in GL
		std::vector<std::shared_ptr<TriFace> > m_faces; //!< Retains information on all tris in the model
		bool m_cullAnimated; //!< Set to cull parts individually and assume part is on screen if model is

		glm::vec3 m_minPoint; //!< Minimum xyz values
		glm::vec3 m_maxPoint; //!< Maximum xyz values
		glm::vec3 m_size; //!< total size of the model

		std::weak_ptr<Context> m_context; //!< Pointer to glwrap context

		virtual void draw() {}
		virtual void cullAndDraw() {}
	};
}
#endif