#include <interface/maininterface.h>
#include "engine.h"

int CEngine::loadPlugins(const std::string& _path)
{
	int l_ret=0;
	//Plugins manager
	m_pfm = CPluginManager::Instance();
    l_ret = m_pfm->loadPlugins(_path);
	return l_ret;
}

bool CEngine::loadInterface()
{
	bool l_ret = false;

	CMainInterface* l_Main = 0;
	l_Main = new CMainInterface(NULL, wxID_ANY, wxT(NAME), wxDefaultPosition, wxSize(365, 290));
	if(l_Main)
    {
		l_Main->Show(true);
		l_ret = true;
	}

	return l_ret;
}
