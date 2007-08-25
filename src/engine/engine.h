#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <tools/smart_pointer.h>
#include <tools/singleton.h>

/*!
*@brief Manage all operations
*/
class CEngine: public CSmartCpt, public TSingleton<CEngine>
{
	public:
		/*!
		*@brief ctor
		*/
		CEngine(){}
	
		/*!
		*@brief dtor
		*/
		~CEngine(){}
	
};
#endif //_ENGINE_H_
