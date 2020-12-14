#include "Engine.h"

using namespace Engine;

EMesh::EMesh(const EString& name, const EString& path)
    : Resource(name, path)
{

}

EMesh::~EMesh()
{

}

bool EMesh::OnReload()
{
    return false;
}