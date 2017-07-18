/*
* Pegasus Engine
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

#ifndef _PEGASUS_WINDOW_HPP_
#define _PEGASUS_WINDOW_HPP_

//====================
// C++ includes
//====================
#include <string> // Storing the title of the window.

//====================
// Pegasus includes
//====================
#include <pegasus/utilities/non_copyable.hpp> // Window is a non-copyable object.
#include <pegasus/core/context.hpp>           // The context settings for the Window.
#include <pegasus/utilities/logger.hpp>       // Logging messages with the state of the window.

//====================
// Library includes
//====================
#include <SDL2/SDL.h>   // Opening a window and loading the context.
#include <glm/glm.hpp>  // Stores the size of the window.

namespace pegasus
{
	//====================
	// Forward declarations
	//====================
	class ConfigFile;

	class Window final : NonCopyable
	{
	private:
		//====================
		// Member variables
		//====================
		/** Logging any important information when creating the window. */
		Logger&       m_logger;
		/** The handle to the SDL window that this class encapulates. */
		SDL_Window*   m_pHandle;
		/** Initializing the context between SDL and OpenGL. */
		SDL_GLContext m_context;
		/** Stores the settings for the major and minor version of OpenGL. */
		Context       m_settings;
		/** The title of the window. */
		std::string   m_title;
		/** The dimensions of the window. */
		glm::ivec2    m_size;
		/** Whether the window is currently running. */
		bool          m_running;

	public:
		//====================
		// Ctors and dtors
		//====================
		/**
		 * @brief Default constructor for the Window object.
		 * 
		 * The default constructor will initialize all of the member variables
		 * to a default state. The window is not opened when the object is constructed,
		 * an additional call to Window::create() must be made.
		 */
		explicit Window();

		/**
		 * @brief Destructor for the Window object.
		 * 
		 * The destructor will destroy the retained resources for the SDL window instance
		 * and the SDL Gl context.
		 */
		~Window();
		
		//====================
		// Getters and setters
		//====================
		/**
		 * @brief Retrieves a reference to the window context.
		 * 
		 * The context contains a number of public variables that store the information 
		 * associated with the OpenGL context, such as major and minor version. The values
		 * cannot be changed outside of the configuration file that creates the window.
		 * 
		 * @return The context settings associated with this window.
		 */
		const Context& getContext() const;

		/**
		 * @brief Retrieves the title of the window.
		 * 
		 * The title of the window refers to the name of the window, which will appear in the
		 * header when the window has not been flagged as full-screen within the configuration
		 * file.
		 * 
		 * @returns A title of the window.
		 */
		const std::string& getTitle() const;

		/** 
		 * @brief Sets the title of the window.
		 * 
		 * The title of the window refers to the name of the window, which will appear in the
		 * header when the window has not been flagged as full-screen within the configuration
		 * file.
		 * 
		 * @param title A title of the window.
		 */
		void setTitle(const std::string& title);

		/**
		 * @brief Retrieves the size of the window.
		 * 
		 * The size of the window controls the dimensions of how it will appear on the desktop.
		 * The dimensions only apply if the window has not been flagged as full-screen.
		 * 
		 * @returns The dimensions of the window.
		 */
		glm::ivec2 getSize() const;

		/**
		 * @brief Sets the size of the window.
		 * 
		 * The size of the window controls the dimensions of how it will appear on the desktop.
		 * The dimensions only apply if the window has not been flagged as full-screen.
		 * 
		 * @param size The dimensions of the window.
		 */
		void setSize(const glm::ivec2& size);

		/** @brief Retrieves the current running state of the Window.
		 *
		 * When the Window is created, it is automatically set to running upon
		 * success. This method should be utilised within a loop so that the
		 * game will continue to run whilst the window is still operating.
		 *
		 * @returns    The current running state of the Window.
		 */
		bool isRunning() const;

		//====================
		// Methods
		//====================
		/** @brief Creates the Window object.
		 *
		 * The constructor of the window does not create the Window object.
		 * This method is used to construct the Window and provide additional
		 * error checking to make sure that the Window is created without
		 * potential problems. If a problem is encountered, an exception is thrown.
		 *
		 * @param config The parameters of the Window retrieved from the config file.
		 */
		void create(const ConfigFile& config);

		/** @brief Closes the current Window object.
		 *
		 * When invoked, this method will close the current Window object and 
		 * stop it from running. This method should be called when the user 
		 * wishes to exit the application and is called automatically when the
		 * 'x' of the window is clicked.
		 */
		void close();

		/** @brief Clears the buffer of the Window.
		 *
		 * This method should be called at the beginning of every render frame.
		 * This prevents artifacting from previous scenes and clears the buffer
		 * for addtional use.
		 */
		void clear() const;

		/** @brief Swaps the buffer of the Window.
		 *
		 * OpenGL utilises double buffers in order to smoothly render each
		 * scene without any artifacting of render glitches. The swap method
		 * should be called at the end of the current rendering frame.
		 */
		void swap() const;	
	};

} // namespace pegasus

#endif//_PEGASUS_WINDOW_HPP_
