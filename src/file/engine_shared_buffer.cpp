#include "Engine.h"

using namespace Engine;


ESharedBuffer::ESharedBuffer() 
{
    fBuffer = nullptr;
    fRefCount = nullptr;
    fSizeInBytes = 0;
    fElementCount = 0;
}

ESharedBuffer::ESharedBuffer(const ESharedBuffer& other) 
{
    fBuffer = other.fBuffer;
    fRefCount = other.fRefCount;
    fSizeInBytes = other.fSizeInBytes;
    fElementCount = other.fElementCount;
    (*fRefCount)++;
}

void ESharedBuffer::operator=(const ESharedBuffer& other) 
{

    fBuffer = other.fBuffer;
    fRefCount = other.fRefCount;
    fSizeInBytes = other.fSizeInBytes;
    fElementCount = other.fElementCount;
    (*fRefCount)++;
}


ESharedBuffer::~ESharedBuffer() 
{
    if (!fBuffer || !fRefCount) { return; }
    (*fRefCount)--;
    if ((*fRefCount) == 0)
    {
        fBuffer->Delete();

        delete fRefCount;
        delete fBuffer;

        fBuffer = nullptr;
        fRefCount = nullptr;
    }
}

u32 ESharedBuffer::GetElementCount() const
{
    return fElementCount;
}

size_t ESharedBuffer::GetSizeInByte() const
{
    return fSizeInBytes;
}

