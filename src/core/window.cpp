/*
* Sparky Engine
* 2017 - Benjamin Carter (bencarterdev@outlook.com)
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it freely,
* subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented;
*    you must not claim that you wrote the original software.
*    If you use this software in a product, an acknowledgement
*    in the product documentation would be appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such,
*    and must not be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

//====================
// C++ includes
//====================
#include <stdexcept> // Throwing runtime exceptions.

//====================
// Sparky includes
//====================
#include <sparky/core/window.hpp>               // Class declaration.
#include <sparky/utilities/logger_factory.hpp>  // Getting the relevant logs.
#include <sparky/core/config_file.hpp>          // Retrieving variables from the configuration file.

//====================
// Library includes
//====================
#include <GL/glew.h> // Initializing OpenGL.

namespace sparky
{
	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	Window::Window()
		: NonCopyable(), m_logger(LoggerFactory::getLogger("file.logger")), m_pHandle(nullptr), m_context(),
			m_settings(), m_title(), m_size(), m_running(false)
	{
		// Empty.
	}

	/**********************************************************/	
	Window::~Window()
	{
		if (m_context)
		{
			SDL_GL_DeleteContext(m_context);
		}

		if (m_pHandle)
		{
			SDL_DestroyWindow(m_pHandle);
			m_pHandle = nullptr;
		}
	}

	//====================
	// Getters and setters
	//====================
	/**********************************************************/
	const Context& Window::getContext() const
	{
		return m_settings;
	}

	/**********************************************************/
	const std::string& Window::getTitle() const
	{
		return m_title;
	}

	/**********************************************************/
	void Window::setTitle(const std::string& title)
	{
		m_title = title;
	}

	/**********************************************************/
	glm::ivec2 Window::getSize() const
	{
		return m_size;
	}

	/**********************************************************/
	void Window::setSize(const glm::ivec2& size)
	{
		SDL_SetWindowSize(m_pHandle, size.x, size.y);
		m_size = size;
	}

	/**********************************************************/
	bool Window::isRunning() const
	{
		return m_running;
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	void Window::create(const ConfigFile& config)
	{
		// Set the member variables from the configuration file.
		m_title = config.get<std::string>("Window.title");
		m_size = config.get<glm::ivec2>("Window.size");
		// Initialize SDL and the needed modules.
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO))
		{
			throw std::runtime_error("Window failed to initialize: " + std::string(SDL_GetError()));
		}

		// Create the SDL window with the default position and the width and height.
		m_pHandle = SDL_CreateWindow(m_title.c_str(), 
			                         SDL_WINDOWPOS_UNDEFINED,
			                         SDL_WINDOWPOS_UNDEFINED,
			                         m_size.x,
			                         m_size.y,
			                         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

		// Check if the window initialized correctly.
		if (!m_pHandle)
		{
			throw std::runtime_error("Window failed to initialize: " + std::string(SDL_GetError()));
		}

		// Create the context for OpenGL.
		m_context = SDL_GL_CreateContext(m_pHandle);
		// The context settings loaded from the configuration file.
		m_settings.depthBits = config.get<unsigned int>("Graphics.depth_bits");
		m_settings.stencilBits = config.get<unsigned int>("Graphics.stencil_bits");
		m_settings.majorVersion = config.get<unsigned int>("Graphics.major_version");
		m_settings.minorVersion = config.get<unsigned int>("Graphics.minor_version");
		// Set the default SDL gl variables.
		SDL_GL_SetSwapInterval(1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, m_settings.depthBits);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, m_settings.stencilBits);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, m_settings.majorVersion);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, m_settings.minorVersion);
		// Needed flag to get glew to work on linux/mac.
		glewExperimental = GL_TRUE;
		// Checking the glew initialization.
		GLenum error = glewInit();
		// Checking it initialized successfully.
		if (error != GLEW_OK)
		{
			throw std::runtime_error("GLEW failed to initialize: ");
		}
		// Enable some core opengl settings.
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		// The window creation is successful.
		m_running = true;
		m_logger.debug("Window creation successful.");
	}

	/**********************************************************/
	void Window::close()
	{
		m_running = false;
	}

	/**********************************************************/
	void Window::clear() const
	{
		glClearColor(0.5, 0.5, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	/**********************************************************/
	void Window::swap() const
	{
		SDL_GL_SwapWindow(m_pHandle);
	}

} // namespace sparky