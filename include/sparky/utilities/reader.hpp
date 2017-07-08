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

#ifndef _SPARKY_READER_HPP_
#define _SPARKY_READER_HPP_

//==================== 
// C++ includes
//==================== 
#include <string> // Loading file by using string. 

namespace sparky
{
	class Reader
	{
	protected:
		//==================== 
		// Member variables
		//====================
		/** Controls whether the reading of the file or stream succeeded. */
		bool        m_failed;

	public:
		//==================== 
		// Ctors and dtor
		//====================
		/**
		* @brief Default constructor for the Reader object.
		*/
		explicit Reader();

		/**
		* @brief Default destructor.
		*/
		virtual ~Reader() = default;

		//==================== 
		// Getters and setters
		//====================
		/**
		* @brief Retrieves the opening state of the reader.
		*
		* If the reader was able to open and read the specified file successfully, the failed
		* state will be set to false. If the file failed to open, it is classed as failed.
		*
		* @returns The failure state of the Reader.
		*/
		bool failed() const;

		//==================== 
		// Methods
		//====================
		/**
		* @brief Opens and reads the file at the specified directory.
		*
		* When the file is opened, if it is opened successfully, the result is stored
		* in the source string, which can be used externally to reference the results of the
		* open method. If the file fails to open, its state will be set to false. This method
		* is defined to be over-ridden by child classes, if the parent open method is used, it will
		* throw a NotImplementedException.
		*
		* @param filename The file to read in.
		*
		* @throws NotImplementedException If the parent open method is called.
		*/
		virtual void open(const std::string& filename);
	};

} // namespace sparky

#endif//_SPARKY_READER_HPP_