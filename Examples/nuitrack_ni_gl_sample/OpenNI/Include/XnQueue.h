/*****************************************************************************
*                                                                            *
*  OpenNI 1.x Alpha                                                          *
*  Copyright (C) 2012 PrimeSense Ltd.                                        *
*                                                                            *
*  This file is part of OpenNI.                                              *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*****************************************************************************/
#ifndef _XN_QUEUE_H
#define _XN_QUEUE_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "XnList.h"

//---------------------------------------------------------------------------
// Types
//---------------------------------------------------------------------------
/**
* The queue
*/
class XnQueue
{
public:
	/**
	* Constructor. Initialize internal representations
	*/
	XnQueue() {}
	/**
	* Destructor. Destroy internal representations
	*/
	virtual ~XnQueue() {}

	/**
	* Initialized the queue. This method should be called before calling any other method.
	*/
	virtual XnStatus Init()
	{
		return (XN_STATUS_OK);
	}

	/**
	* Push a new value to the queue
	* 
	* @param	value	[in]	The value to add to the queue
	*
	* @return	XN_STATUS_ALLOC_FAILED	Failed to add to the queue because no nodes are available.
	*/
	virtual XnStatus Push(XnValue const& value)
	{
		XnStatus nRetVal = XN_STATUS_OK;

		nRetVal = m_List.AddLast(value);
		XN_IS_STATUS_OK(nRetVal);

		return (XN_STATUS_OK);
	}
	/**
	* Pop the value at the top of the queue
	* 
	* @param	value	[out]	The value that was at the top of the queue
	*
	* @return	XN_STATUS_IS_EMPTY	The queue is empty
	*/
	virtual XnStatus Pop(XnValue& value)
	{
		if (IsEmpty())
		{
			return XN_STATUS_IS_EMPTY;
		}

		value = *(m_List.begin());
		return m_List.Remove(m_List.begin());
	}

	/**
	* Get the value at the top of the queue (it is user responsibility to check queue is not empty)
	* 
	* @return	a reference to the object at head of the queue.
	*/
	XnValue const& Top() const
	{
		return *(m_List.begin());
	}

	/**
	* Get the value at the top of the queue (it is user responsibility to check queue is not empty)
	* 
	* @return	a reference to the object at head of the queue.
	*/
	XnValue& Top()
	{
		return *(m_List.begin());
	}

	/**
	* Check if queue is empty
	*/
	XnBool IsEmpty() const
	{
		return m_List.IsEmpty();
	}

	/**
	* Get current size of queue
	*/
	virtual XnUInt32 Size() const
	{
		return m_List.Size();
	}

private:
	XN_DISABLE_COPY_AND_ASSIGN(XnQueue);

	/** The internal XnList with which the queue is implemented. */
	XnList m_List;
};

/**
* Declares a queue of type @a Type, named @a ClassName. The class uses @a Translator for translating
* from @a Type to XnValue. It is declared using the declspec @a decl.
* It inherits from @a base. Note that @a base must be a derivative of XnQueue.
*/ 
#define XN_DECLARE_QUEUE_WITH_TRANSLATOR_DECL(decl, Type, ClassName, Translator, base)	\
	class decl ClassName : public base													\
	{																					\
	public:																				\
		ClassName() {}																	\
		~ClassName()																	\
		{																				\
			/* We do this using Pop() to make sure memory is freed. */					\
			Type dummy;																	\
			while (Size() != 0)															\
				Pop(dummy);																\
		}																				\
		XnStatus Push(Type const& value)												\
		{																				\
			XnValue val = Translator::CreateValueCopy(value);							\
			XnStatus nRetVal = base::Push(val);											\
			if (nRetVal != XN_STATUS_OK)												\
			{																			\
				Translator::FreeValue(val);												\
				return (nRetVal);														\
			}																			\
			return XN_STATUS_OK;														\
		}																				\
		XnStatus Pop(Type& value)														\
		{																				\
			XnValue val;																\
			XnStatus nRetVal = base::Pop(val);											\
			if (nRetVal != XN_STATUS_OK) return (nRetVal);								\
			value = Translator::GetFromValue(val);										\
			Translator::FreeValue(val);													\
			return XN_STATUS_OK;														\
		}																				\
		inline Type const& Top() const { return Translator::GetFromValue(base::Top()); }\
		inline Type& Top() { return Translator::GetFromValue(base::Top()); }			\
	private:																			\
		XN_DISABLE_COPY_AND_ASSIGN(ClassName);											\
	};

/**
* Declares a queue of type @a Type, named @a ClassName. The class uses @a Translator for translating
* from @a Type to XnValue.
* It inherits from @a base. Note that @a base must be a derivative of XnQueue.
*/ 
#define XN_DECLARE_QUEUE_WITH_TRANSLATOR(Type, ClassName, Translator, base)				\
	XN_DECLARE_QUEUE_WITH_TRANSLATOR_DECL(, Type, ClassName, Translator, base)

/**
* Declares a queue of type @a Type, named @a ClassName, that uses the default translator.
* It is declared using the declspec @a decl.
*/ 
#define XN_DECLARE_QUEUE_DECL(decl, Type, ClassName)													\
	XN_DECLARE_DEFAULT_VALUE_TRANSLATOR_DECL(decl, Type, XN_DEFAULT_TRANSLATOR_NAME(ClassName))			\
	XN_DECLARE_QUEUE_WITH_TRANSLATOR_DECL(decl, Type, ClassName, XN_DEFAULT_TRANSLATOR_NAME(ClassName), XnQueue)

/**
* Declares a queue of type @a Type, named @a ClassName, that uses the default translator.
*/ 
#define XN_DECLARE_QUEUE(Type, ClassName)		\
	XN_DECLARE_QUEUE_DECL(, Type, ClassName)

#endif // _XN_QUEUE_H
