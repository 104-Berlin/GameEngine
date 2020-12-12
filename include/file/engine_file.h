#pragma once

namespace Engine {

    namespace Path {
        template <typename ...T>
        EString Join(const T&... args)
        {
            EString result;
            std::vector<const char*> strings = {args...};
            for (size_t i = 0; i < strings.size() - 1; i++)
            {
                result += EString(strings[i]) + kPathSeparator;
            }
            result += strings[strings.size() - 1];
            return result;
        }
    }

    class EFile
    {
    private:
        EString fFilePath;
        EString fFileExtension;
        EString fFileName;
    public:
        EFile(const EString& path);
        ~EFile();

        bool Exist() const;
        const EString& GetFilePath() const;
        const EString& GetFileExtension() const;
        const EString& GetFileName() const;
    private:
        void CreatePathStrings();
    };

}
