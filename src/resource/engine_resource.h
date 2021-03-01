#pragma once

namespace Engine {

    class E_API EResource
    {
    protected:
        EFile   fFile;
        EString fEngineDir;
    public:
        EResource(const EString& path);

        void SetEngineDirectory(const EString& path);

        EString GetFilePath() const;
        const EString& GetName() const;
        EString GetNameIdent() const;
        EString GetEnginePath() const;

        bool Load();
        virtual bool OnLoad();

        
    };

}