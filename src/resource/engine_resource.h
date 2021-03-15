#pragma once

namespace Engine {

    class E_API EResource
    {
    protected:
        EFile   fFile;
        EString fEngineDir;
    public:
        EResource(const EString& path);
        virtual ~EResource() = default;

        void SetEngineDirectory(const EString& path);

        EString GetFilePath() const;
        const EString& GetName() const;
        EString GetNameIdent() const;
        EString GetEnginePath() const;
    };

}