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

#ifndef _PEGASUS_STREAM_READER_HPP_
#define _PEGASUS_STREAM_READER_HPP_

//==================== 
// C++ includes
//==================== 
#include <fstream> // Reading and storing the contents of files.

//==================== 
// Pegasus includes
//==================== 
#include <pegasus/utilities/reader.hpp> // StreamReader inherits from the Reader object.

namespace pegasus
{
	class StreamReader final : public Reader
	{
	private:
		//==================== 
		// Member variables
		//==================== 
		/** The file that the stream reader is reading content from. */
		std::ifstream m_file;
		/** The current line that has been read in by the stream. */
		std::string   m_line;

	public:
		//==================== 
		// Ctors and dtor
		//==================== 
		/**
		 * @brief Default constructor.
		 *
		 * The default constructor initialises the member variables to default values.
		 * No file is opened or read when utilising this constructor. An additional call to 
		 * StreamReader::open should be made.
		 */
		explicit StreamReader();

		/**
		 * @brief Constructor that opens a file and reads in the contents.
		 *
		 * When this constructor is invoked, it will instantiate a StreamReader object and read
		 * in the contents of the specified file. If the file cannot be read, the state of the reader
		 * is set to failed. 
		 *
		 * @param filename The file directory of the file to read from disk.
		 */
		explicit StreamReader(const std::string& filename);

		/**
		 * @brief Destructor for the StreamReader.
		 *
		 * When the destructor is invoked, it will close the stream that this object has been retaining
		 * to read content.
		 */
		~StreamReader();

		//==================== 
		// Getters and setters
		//==================== 
		/**
		 * @brief Reads the next line in the currently opened file.
		 *
		 * if the file that has been read in contains multiple lines within the file, this method
		 * can be invoked to jump to the next line within the file. If the file failed to open or
		 * contains no content, this method will return an empty stream.
		 *
		 * @returns The next line within the file.
		 */
		std::istream& hasNext();

		/**
		 * @brief Retrieves the current line that has been read in from the stream.
		 *
		 * The current line is denoted with the calls to the StreamReader::hasNext method. If the
		 * method has not been invoked, the file failed to open or the content of the file are empty,
		 * an empty string will be returned. 
		 *
		 * @returns The line that has been read in by the stream reader.
		 */
		const std::string& getLine() const;

		//==================== 
		// Methods
		//==================== 
		/**
		* @brief Reads in a file from disk and readies it for continuous reading.
		*
		* When the file is opened, it is first checked that it opened successfully. If the file opened
		* with no issues the contents of the file are readied for continuous reading.
		*
		* If the file failed to load, the state of the reader will be set to failed.
		*
		* @param filename The file to open and read from disk.
		*/
		void open(const std::string& filename) override;
	};

} // namespace pegasus

#endif//_PEGASUS_STREAM_READER_HPP_

