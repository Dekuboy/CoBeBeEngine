#ifndef _GLWRAP_VERTEXARRAY
#define _GLWRAP_VERTEXARRAY
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
namespace glwrap
{
	struct TriFace;

	class Context;
	class VertexBuffer;
	class ObjPart;
	class ObjAnimation;
	class ShaderProgram;

	/**
	* \brief Holds information on a model loaded into GL (obj)
	*/
	class VertexArray
	{
	public:
		VertexArray();
		VertexArray(std::string _path);

		/**
		* \brief Parse obj file and read into GL
		*/
		void parse(std::string _path);
		/**
		* \brief Parse obj file and read into Gl
		* -if(_tanBitan) calculate tangent bitangent attributes for TBN matrix
		*/
		virtual void parse(std::string, bool _tanBitan);

		/**
		* \brief Sets buffer of name _attribute to "Default" part
		* -does not work if VertexArray has parsed an obj file
		*/
		void setBuffer(std::string _attribute, std::shared_ptr<VertexBuffer> _buffer);

		/**
		* \brief Retrieve the size of VertexArray based on xyz values
		*/
		glm::vec3 getSize();
		/**
		* \brief Set cull animation
		* -if(true) when ShaderProgram calls cullAndDraw() then
		*    ObjPart will assume non-moving parts are within the view if the 
		*    model is in view
		* -useful for smaller objects with moving parts with a larger reach
		*/
		void setCullAnimation(bool _switch);
		/**
		* \brief Get cull animation
		*/
		bool getCullAnimation();

		/**
		* \brief Attach Animation to object from file path
		*/
		std::shared_ptr<ObjAnimation> addAnimation(std::string _path);
		int playAnimationOnce(std::string _name);
		void playAnimationOnce(int _index);
		int enableAnimation(std::string _name);
		void enableAnimation(int _index);
		int enableOnlyAnimation(std::string _name);
		void enableOnlyAnimation(int _index);
		int disableAnimation(std::string _name);
		void disableAnimation(int _index);
		void disableAllAnimations();

		/**
		* \brief Retrieve all the tri information of the model
		*/
		std::vector<std::shared_ptr<TriFace> > getFaces();
		/**
		* \brief Retrieve all the parts that make up the model
		*/
		std::vector<std::shared_ptr<ObjPart> > getParts();
		/**
		* \brief Retrieve part that is called _name
		*/
		std::shared_ptr<ObjPart> getPart(std::string _name);
		/**
		* Retrieve list of attached animations
		*/
		std::vector<std::shared_ptr<ObjAnimation> > getAnimations();

	protected:
		friend class Context;
		friend class ShaderProgram;

		bool m_dirty; //!< If the buffers have been altered, update in GL
		std::vector<std::shared_ptr<TriFace> > m_faces; //!< Retains information on all tris in the model
		std::vector<std::shared_ptr<ObjPart> > m_parts; //!< Information on individual parts of the model
		std::vector<std::shared_ptr<ObjAnimation> > m_animations; //!< List of animations attached to the model
		std::weak_ptr<VertexArray> m_self; //!< Pointer to self to set in individual parts
		std::weak_ptr<Context> m_context; //!< Pointer to glwrap context

		glm::vec3 m_minPoint; //!< Minimum xyz values
		glm::vec3 m_maxPoint; //!< Maximum xyz values
		glm::vec3 m_size; //!< total size of the model

		bool m_cullAnimated; //!< Set to cull parts individually and assume part is on screen if model is

		/**
		* \brief Separates strings into substrings based on white space
		*/
		void splitStringWhitespace(std::string& _input, std::vector<std::string>& _output);
		/**
		* \brief Splits string based on input value as a splitter
		*/
		void splitString(std::string& _input, char _splitter, std::vector<std::string>& _output);
		/**
		* \brief Checks if vertex values are the minimum or maximum of the model
		*/
		void checkMinMax(glm::vec3& _vertexPosition);

		/**
		* \brief Calls upon the part list and draws vertex arrays
		* -to be called by ShaderProgram
		*/
		void draw();
		/**
		* \brief Calls upon the part list and draws vertex arrays if in view
		* -to be called by ShaderProgram
		* -uses values from current active ShaderProgram to cull
		*/
		void cullAndDraw();
		/**
		* \brief Draws individual part of object by name
		*/
		void drawPart(std::string _partName);

	};
}

#endif