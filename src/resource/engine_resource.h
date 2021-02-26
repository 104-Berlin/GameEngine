#pragma once

namespace Engine {

    class E_API EResource
    {
    protected:
        EFile fFile;
    public:
        EResource(const EString& path);

        EString GetFilePath() const;
        const EString& GetName() const;
        EString GetNameIdent() const;

        bool Load();
        virtual bool OnLoad();

        
    };

}