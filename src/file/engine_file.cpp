#include "Engine.h"

using namespace Engine;


EFile::EFile(const EString& path)
    : fFilePath(path)
{
    fFileName = "";
    fFileExtension = "";
    CreatePathStrings();
}

void EFile::CreatePathStrings()
{
    size_t dot_index = fFilePath.find_last_of(".");
    size_t last_slash_index = fFilePath.find_last_of(kPathSeparator);
    if (last_slash_index == EString::npos)
    {
        last_slash_index = 0;
    }

    if (dot_index != EString::npos)
    {
        fFileName = fFilePath.substr(last_slash_index + 1, dot_index - last_slash_index - 1);
        fFileExtension = fFilePath.substr(dot_index + 1);
    }
}

EFile::~EFile()
{

}

bool EFile::Exist() const
{
    std::ifstream file(fFilePath);
    return file.good();
}

const EString& EFile::GetFilePath() const
{
    return fFilePath;
}

const EString& EFile::GetFileExtension() const
{
    return fFileExtension;
}

const EString& EFile::GetFileName() const
{
    return fFileName;
}
