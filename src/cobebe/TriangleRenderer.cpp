#include "TriangleRenderer.h"
#include "Exception.h"

void TriangleRenderer::onInit()
{

	const GLfloat positions[] = {
	  0.0f, 0.5f, 0.0f,
	  -0.5f, -0.5f, 0.0f,
	  0.5f, -0.5f, 0.0f
	};

	const GLfloat colors[] = {
	  1.0f, 0.0f, 0.0f, 1.0f,
	  0.0f, 0.0f, 1.0f, 1.0f,
	  0.0f, 1.0f, 0.0f, 1.0f
	};

	const GLchar *vertexShaderSrc =
		"attribute vec3 in_Position;" \
		"attribute vec4 in_Color;" \
		"" \
		"varying vec4 ex_Color;" \
		"" \
		"void main()" \
		"{" \
		"  gl_Position = vec4(in_Position, 1.0);" \
		"  ex_Color = in_Color;" \
		"}" \
		"";

	const GLchar *fragmentShaderSrc =
		"varying vec4 ex_Color;" \
		"void main()" \
		"{" \
		"  gl_FragColor = ex_Color;" \
		"}" \
		"";

	GLuint positionsVboId = 0;

	// Create a new VBO on the GPU and bind it
	glGenBuffers(1, &positionsVboId);

	if (!positionsVboId)
	{
		throw Exception("PosVbo");
	}

	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint colorsVboId = 0;

	// Create a colors VBO on the GPU and bind it
	glGenBuffers(1, &colorsVboId);

	if (!colorsVboId)
	{
		throw Exception("ColVbo");
	}

	glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);

	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_vaoId = 0;

	// Create a new VAO on the GPU and bind it
	glGenVertexArrays(1, &m_vaoId);

	if (!m_vaoId)
	{
		throw Exception("Vao");
	}

	glBindVertexArray(m_vaoId);

	// Bind the position VBO, assign it to position 0 on the bound VAO and flag it to be used
	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);

	// Bind the color VBO, assign it to position 1 on the bound VAO and flag it to be used
	glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(1);

	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw Exception("VertShader");
	}

	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw Exception("FragShader");
	}

	m_programId = glCreateProgram();
	glAttachShader(m_programId, vertexShaderId);
	glAttachShader(m_programId, fragmentShaderId);
	glBindAttribLocation(m_programId, 0, "in_Position");
	glBindAttribLocation(m_programId, 1, "in_Color");

	if (glGetError() != GL_NO_ERROR)
	{
		throw Exception("Bind");
	}

	glLinkProgram(m_programId);
	glGetProgramiv(m_programId, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw Exception("Link");
	}

	glDetachShader(m_programId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(m_programId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

void TriangleRenderer::onDisplay()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_programId);
	glBindVertexArray(m_vaoId);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	glUseProgram(0);

}