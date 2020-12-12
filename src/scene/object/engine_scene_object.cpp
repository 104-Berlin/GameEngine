#include "Engine.h"

using namespace Engine;

ESceneObject::ESceneObject(const EString& name)
    :   EObject(name),
        fScene(nullptr),
        fNextObject(this, "Next"),
        fChildObject(this, "Child"),
        fPreviousObject(this, "Prev"),
        fParentObject(this, "Parent")
{

}

ESceneObject::~ESceneObject()
{
    
}

void ESceneObject::UnlinkObject()
{
    ESceneObject* temp = GetNext();
    if (GetNext())
    {
        GetNext()->SetPrev(GetPrev());
    }
    if (GetPrev())
    {
        GetPrev()->SetNext(temp);
    }
    if (GetParent() && GetParent()->GetChild() == this)
    {
        if (GetNext())
        {
            GetParent()->SetChild(GetNext());
        }
        else
        {
            GetParent()->SetChild(GetChild());
            GetChild()->SetParent(GetParent());
        }
    }
}

void ESceneObject::SetScene(EScene* scene)
{
    fScene = scene;
}

void ESceneObject::SetNewNext(ESceneObject* nextObject)
{
    nextObject->UnlinkObject();

    if (GetNext()) 
    {
        GetNext()->SetPrev(nextObject);
    }
    fNextObject.SetValue(nextObject);
    nextObject->SetPrev(this);
    nextObject->SetParent(GetParent());
    nextObject->SetNext(GetNext());
}

void ESceneObject::SetNext(ESceneObject* nextObject)
{
    fNextObject.SetValue(nextObject);
}

ESceneObject* ESceneObject::GetNext() const
{
    return fNextObject.GetValue();
}

void ESceneObject::SetNewPrev(ESceneObject* prevObject)
{
    prevObject->UnlinkObject();

    if (GetPrev())
    {
        GetPrev()->SetNext(prevObject);
        prevObject->SetPrev(fPreviousObject.GetValue());
    }
    else if (GetParent())
    {
        GetParent()->SetChild(prevObject);
    }
    else if (fScene)
    {
        fScene->SetEntryObject(prevObject->GetUuid());
    }
    else
    {
        prevObject->SetPrev(nullptr);
    }

    prevObject->SetNext(this);
    prevObject->SetParent(GetParent());
    SetPrev(prevObject);

}

void ESceneObject::SetPrev(ESceneObject* prevObject)
{
    fPreviousObject.SetValue(prevObject);
}

ESceneObject* ESceneObject::GetPrev() const
{
    return fPreviousObject.GetValue();
}

void ESceneObject::SetNewChild(ESceneObject* childObject)
{
    ESceneObject* parent = childObject->GetParent();
    while (parent)
    {
        if (parent == this)
        {
            // cant place parent in one of its children
            return;
        }
        parent = parent->GetParent();
    }

    childObject->UnlinkObject();

    if (!GetChild())
    {
        SetChild(childObject);
        childObject->SetPrev(nullptr);
    }
    else
    {
        ESceneObject* firstChild = GetChild();
        while (firstChild->GetNext())
        {
            firstChild = firstChild->GetNext();
        }
        firstChild->SetNext(childObject);
        childObject->SetPrev(firstChild);
    }
    childObject->SetParent(this);
    childObject->SetNext(nullptr);
}

void ESceneObject::SetChild(ESceneObject* childObject)
{
    fChildObject.SetValue(childObject);
}

ESceneObject* ESceneObject::GetChild() const
{
    return fChildObject.GetValue();
}

void ESceneObject::SetNewParent(ESceneObject* parentObject)
{
    parentObject->SetNewChild(this);
}

void ESceneObject::SetParent(ESceneObject* parentObject)
{
    fParentObject.SetValue(parentObject);
}

ESceneObject* ESceneObject::GetParent() const
{
    return fParentObject.GetValue();
}
