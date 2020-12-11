#pragma once

namespace Engine {

    class ESceneObject : public EObject
    {
    private:
        EObjectProperty<ESceneObject>       fNextObject;
        EObjectProperty<ESceneObject>       fChildObject;
        EObjectProperty<ESceneObject>       fParentObject;
        EObjectProperty<ESceneObject>       fPreviousObject;
    public:
        ESceneObject(const EString& name);
        ~ESceneObject();

        void            SetNext(ESceneObject* nextObject);
        ESceneObject*   GetNext() const;
        void            SetPrev(ESceneObject* nextObject);
        ESceneObject*   GetPrev() const;
        void            SetChild(ESceneObject* nextObject);
        ESceneObject*   GetChild() const;
        void            SetParent(ESceneObject* nextObject);
        ESceneObject*   GetParent() const;
    };

}