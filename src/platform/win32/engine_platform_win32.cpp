#include "Engine.h"

using namespace Engine;

#ifdef EWIN
EVector<EString> Platform::OpenFileDialog(const EString& title, const EString& defaultPath, const EVector<EString>& filters)
{
    EString filter;
    for (const EString& f : filters)
    {
        filter += "." + f + ";";
    }

    OPENFILENAME ofn = {0}; 
    TCHAR szFile[260]={0};
    // Initialize remaining fields of OPENFILENAME structure
    ofn.lStructSize = sizeof(ofn); 
    ofn.hwndOwner = NULL; 
    ofn.lpstrFile = szFile; 
    ofn.nMaxFile = sizeof(szFile); 
    ofn.lpstrFilter = filter.c_str(); 
    ofn.nFilterIndex = 1; 
    ofn.lpstrFileTitle = NULL; 
    ofn.nMaxFileTitle = 0; 
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if(GetOpenFileName(&ofn) == TRUE)
    { 
    // use ofn.lpstrFile here
        return {ofn.lpstrFile};
    }
    return {};
}
#endif