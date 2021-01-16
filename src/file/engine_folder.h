#pragma once

namespace Engine {

    enum EBaseFolder
    {
        RES,
        APPLICATION,
        PLUGIN,
    };

    class EFolder
    {
    public:
    private:
        EString fFullPath;
    public:
        EFolder(const EString& path);
        EFolder(EBaseFolder f, const EString& path = "");

        const EString& GetFullPath() const;

        bool Exist() const;

        std::filesystem::directory_iterator Iterator() const;

    private:
       static EString GetBaseFolderPath(EBaseFolder f);
    };

}