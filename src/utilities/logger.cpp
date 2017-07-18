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

//====================
// Pegasus includes
//====================
#include <pegasus/utilities/logger.hpp> // Class declaration.

namespace pegasus
{
	//====================
	// Static variables
	//====================
	/**********************************************************/
	bool Logger::m_infoEnabled = false;
	bool Logger::m_debugEnabled = false;
	bool Logger::m_warnEnabled = true;
	bool Logger::m_errorEnabled = true;

	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	Logger::Logger(std::unique_ptr<IPolicy> policy)
		: m_policy(std::move(policy)), m_stream(), m_mutex()
	{
		// Empty.
	}

	//====================
	// Private methods
	//====================
	/**********************************************************/
	void Logger::write()
	{
		m_policy->commit(m_stream.str());

		m_stream.str("");
		m_stream.clear();
	}

	//====================
	// Getters and setters
	//====================
	/**********************************************************/
	void Logger::setInfoEnabled(bool infoEnabled)
	{
		m_infoEnabled = infoEnabled;
	}

	/**********************************************************/
	void Logger::setDebugEnabled(bool debugEnabled)
	{
		m_debugEnabled = debugEnabled;
	}

	/**********************************************************/
	void Logger::setWarningEnabled(bool warnEnabled)
	{
		m_warnEnabled = warnEnabled;
	}

	/**********************************************************/
	void Logger::setErrorEnabled(bool errorEnabled)
	{
		m_errorEnabled = errorEnabled;
	}

} // namespace pegasus
