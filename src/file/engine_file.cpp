#include "Engine.h"

using namespace Engine;

   
EFileBuffer::EFileBuffer() 
{
    
}

EFileBuffer::EFileBuffer(const ESharedBuffer& buffer) 
    : fBuffer(buffer)
{
    
}

size_t EFileBuffer::GetSize() const
{
    return fBuffer.GetSizeInByte();
}

bool EFileBuffer::IsNull() const
{
    return fBuffer.IsNull();
}

void EFileBuffer::Dispose() 
{
    fBuffer.Dispose();
}


EFile::EFile(const EString& path)
    : fFilePath(path)
{
    fFileName = "";
    fFileExtension = "";
    CreatePathStrings();
}

EFile::EFile(EBaseFolder baseFolder, const EString& path)
    : EFile(Path::Join(EFolder::GetBaseFolderPath(baseFolder), path))
{
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

EString EFile::GetFullPath() const
{
    return std::filesystem::absolute(std::filesystem::path(fFilePath)).string();
}

const EString& EFile::GetPath() const
{
    return fFilePath;
}

const EString& EFile::GetFileExtension() const
{
    return fFileExtension;
}

EString EFile::GetFileAsString() const
{
    std::ifstream t(GetFullPath());
    EString result((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
    t.close();
    return result;
}

void EFile::SetFileAsString(const EString& string) const
{
    std::ofstream o(GetFullPath());
    o << string;
    o.close();
}

const EString& EFile::GetFileName() const
{
    return fFileName;
}

void EFile::LoadToMemory() 
{
    if (!fFileBuffer.IsNull())
    {
        fFileBuffer.Dispose();
    }

    std::ifstream t(GetFullPath(), std::ios::binary);
    size_t buffer_length = t.tellg();
    ESharedBuffer shared_buffer;
    shared_buffer.InitWith<byte>(new byte[buffer_length], buffer_length);

    t.seekg(0, std::ios::beg);
    t.read(shared_buffer.Data<char>(), buffer_length);
    t.close();
    fFileBuffer = EFileBuffer(shared_buffer);
}

void EFile::DisposeMemory() 
{
    if (!fFileBuffer.IsNull())
    {
        fFileBuffer.Dispose();
    }
}

EFileBuffer EFile::GetBuffer() const
{
    return fFileBuffer;
}

