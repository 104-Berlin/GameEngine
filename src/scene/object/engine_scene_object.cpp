#include "Engine.h"

using namespace Engine;

ESceneObject::ESceneObject(const EString& name)
    :   EObject(name),
        fNextObject(this, "Next"),
        fChildObject(this, "Child"),
        fPreviousObject(this, "Prev"),
        fParentObject(this, "Parent")
{

}

ESceneObject::~ESceneObject()
{
    
}


void ESceneObject::SetNext(ESceneObject* nextObject)
{
    fNextObject.SetValue(nextObject);
}

ESceneObject* ESceneObject::GetNext() const
{
    return fNextObject.GetValue();
}

void ESceneObject::SetPrev(ESceneObject* prevObject)
{
    fPreviousObject.SetValue(prevObject);
}

ESceneObject* ESceneObject::GetPrev() const
{
    return fPreviousObject.GetValue();
}

void ESceneObject::SetChild(ESceneObject* childObject)
{
    fChildObject.SetValue(childObject);
}

ESceneObject* ESceneObject::GetChild() const
{
    return fChildObject.GetValue();
}

void ESceneObject::SetParent(ESceneObject* parentObject)
{
    fParentObject.SetValue(parentObject);
}

ESceneObject* ESceneObject::GetParent() const
{
    return fParentObject.GetValue();
}