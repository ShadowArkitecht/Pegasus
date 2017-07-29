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

#ifndef _PEGASUS_RESOURCE_HANDLE_HPP_
#define _PEGASUS_RESOURCE_HANDLE_HPP_

//====================
// C++ includes
//====================
#include <type_traits>              // Checking that the inheritance for the template is correct.

//====================
// Pegasus includes
//====================
#include <pegasus/core/asset.hpp>  // The object within the handle must be an asset.

namespace pegasus
{
	template <typename T>
	class ResourceHandle final
	{
		static_assert(std::is_base_of<Asset, T>::value, "The template must be of base-type Asset.");

	private:
		//====================
		// Member variables
		//====================
		/** The asset that the handle wraps around. */
		T* m_pResource;

	public:
		//====================
		// Ctors and dtor
		//====================
		/**
		 * @brief Default constructor for the ResourceHandle.
		 *
		 * The default ResourceHandle will initialise the asset
		 * to a null value which will have to be implicitly set before
		 * the handle can be used.
		 */
		explicit ResourceHandle();

		/**
		 * @brief Constructor for the ResourceHandle object.
		 *
		 * When the ResourceHandle is constructed, it will take a reference
		 * to the naked reference that the object will be a handle to. This
		 * object is retained during the ResourceHandle objects lifetime.
		 *
		 * @param pResource The resource of the handle.
		 */
		explicit ResourceHandle(T* pResource);

		/**
		 * @brief Copy constructor for the ResourceHandle object.
		 *
		 * When the ResourceHandle is copy constructed, it will release
		 * any previous resources that it may be maintaining and retain
		 * the resource passed in from the other handle. 
		 *
		 * @param handle The handle object to retain the data from.
		 */
		ResourceHandle(const ResourceHandle<T>& handle);

		/**
		 * @brief Destructor for the ResourceHandle.
		 *
		 * When the destructor is invoked, it will release the resource
		 * attached to this handle, decrementing its reference count and
		 * queueing for potential deletion.
		 */
		~ResourceHandle();

		//====================
		// Operators
		//====================
		/**
		 * @brief Overloading the reference operator.
		 *
		 * The operator is used to access methods and properties of
		 * the naked resource that this handle is wrapped around. 
		 *
		 * @returns A pointer to the resource attached to this handle.
		 */
		T* operator->();

		/**
		 * @brief Overloading the reference operator.
		 *
		 * The operator is used to access methods and properties of
		 * the naked resource that this handle is wrapped around. 
		 *
		 * @returns A pointer to the resource attached to this handle.
		 */
		const T* operator->() const;

		/**
		 * @brief Overloading the assignment operator.
		 *
		 * When the ResourceHandle is assigned to a different object,
		 * it will first release any resources that the current handle
		 * is maintaining. It will then use the same resource as the assigned
		 * handle and retain the memory for additional use.
		 *
		 * @param handle The handle to assign the data from.
		 *
		 * @returns A reference to the current handle object.
		 */
		ResourceHandle<T>& operator=(const ResourceHandle<T>& handle);

		//====================
		// Getters and setters
		//====================
		/**
		 * @brief Retrieves the resource attached to this handle.
		 * 
		 * When this method is invoked, it will access the raw resource
		 * that this object is handling. Care should be taken when directly
		 * manipulating the source, if the handle goes out of scope, the 
		 * resource attached to this handle could potentially be 
		 * de-allocated. This method should only be used by methods that
		 * expect a raw resource as a parameter.
		 *
		 * @returns The raw resource of this handle object.
		 */
		T* get() const;
	};

	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	template <typename T>
	ResourceHandle<T>::ResourceHandle()
		: m_pResource(nullptr)
	{
	}

	/**********************************************************/
	template <typename T>
	ResourceHandle<T>::ResourceHandle(T* pResource)
		: m_pResource(pResource)
	{
		if (m_pResource)
		{
			m_pResource->retain();
		}
	}

	/**********************************************************/
	template <typename T>
	ResourceHandle<T>::ResourceHandle(const ResourceHandle<T>& handle)
		: m_pResource(handle.m_pResource)
	{
		if (m_pResource)
		{
			m_pResource->retain();
		}
	}

	/**********************************************************/
	template <typename T>
	ResourceHandle<T>::~ResourceHandle()
	{
		if (m_pResource)
		{
			m_pResource->release();
		}
	}	

	//====================
	// Operators
	//====================
	/**********************************************************/
	template <typename T>
	T* ResourceHandle<T>::operator->()
	{
		return m_pResource;
	}

	/**********************************************************/
	template <typename T>
	const T* ResourceHandle<T>::operator->() const
	{
		return m_pResource;
	}

	/**********************************************************/
	template <typename T>
	ResourceHandle<T>& ResourceHandle<T>::operator=(const ResourceHandle<T>& handle)
	{
		if (this != &handle)
		{
			if (m_pResource)
			{
				m_pResource->release();
			}

			m_pResource = handle.m_pResource;
			if (m_pResource)
			{
				m_pResource->retain();
			}
		}

		return *this;
	}

	//====================
	// Getters and setters
	//====================
	/**********************************************************/
	template <typename T>
	T* ResourceHandle<T>::get() const
	{
		return m_pResource;
	}

} // namespace pegasus

#endif//_PEGASUS_RESOURCE_HANDLE_HPP_