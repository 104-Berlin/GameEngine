//-----------------------------------------------------------------------------
//----- Copyright 104-Berlin 2021 https://github.com/104-Berlin
//-----------------------------------------------------------------------------
#pragma once

namespace Engine {

    

    // A class that can pack multiple files into one
    // Like a zip file but with no compression
    class E_API EFileCollection
    {
        using FileMap = EUnorderedMap<EString, EFileBuffer>;
    private:
        FileMap             fFileMap;
    public:
        // Initialisation
        EFileCollection() = default;
        EFileCollection(const EFileCollection& other) = default;
        ~EFileCollection() = default;

        // Iteration
        FileMap::iterator begin();
        FileMap::const_iterator begin() const;
        FileMap::iterator end();
        FileMap::const_iterator end() const;

        bool GetFileAt(const EString& path, EFileBuffer* oBuffer);


    };

}