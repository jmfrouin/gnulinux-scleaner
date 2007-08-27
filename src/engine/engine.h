#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <tools/smart_pointer.h>
#include <tools/singleton.h>
#include <plugins/plugin_manager.h>

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
	
	public:
        /*!
         *@brief Call load plugins in PluginManager.
         *@param path The folder location.
         *@return Number of plugins founded.
         */
        int loadPlugins (const std::string& path);

		/*!
		*@brief Load GFX interface build on wxWidgets
		*@return true is everything is OK, dalse otherwise.
		*/
		bool loadInterface();
	
	private:
		TSmartPtr<CPluginManager> 	m_pfm;
	
};
#endif //_ENGINE_H_
