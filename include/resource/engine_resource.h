#pragma once

namespace Engine {

    class EResource : public EObject
    {
    protected:
        EProperty<EString>         fFilePath;
        EProperty<bool>            fIsSaved;
    public:
        EResource(const EString& name, const EString& path);
        ~EResource();

        bool Import();
        virtual bool OnImport();
        bool Export(const EString& filePath);
        virtual bool OnExport(const EString& filePath);
        bool Save();
        virtual bool OnSave();
        bool Load();
        virtual bool OnLoad();

    };

}