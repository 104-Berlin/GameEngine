#include "Engine.h"

using namespace Engine;

EFileCollection::FileMap::iterator EFileCollection::begin() 
{
    return fFileMap.begin();
}

EFileCollection::FileMap::const_iterator EFileCollection::begin() const
{
    return fFileMap.begin();
}

EFileCollection::FileMap::iterator EFileCollection::end() 
{
    return fFileMap.end();
}

EFileCollection::FileMap::const_iterator EFileCollection::end() const
{
    return fFileMap.end();
}

bool EFileCollection::GetFileAt(const EString& path, ESharedBuffer* oBuffer) 
{
    if (!oBuffer) { return false; }
    FileMap::iterator it = fFileMap.find(path);
    if (it != fFileMap.end())
    {
        *oBuffer = it->second;
        return true;
    }    
    return false;
}

