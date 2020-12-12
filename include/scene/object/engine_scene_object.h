#pragma once

namespace Engine {

    class ESceneObject : public EObject
    {
    private:
        EObjectProperty<ESceneObject>       fNextObject;
        EObjectProperty<ESceneObject>       fChildObject;
        EObjectProperty<ESceneObject>       fParentObject;
        EObjectProperty<ESceneObject>       fPreviousObject;

        

        EScene*                             fScene;
    public:
        ESceneObject(const EString& name);
        ~ESceneObject();

        void SetScene(EScene* scene);

        void            SetNewNext(ESceneObject* nextObject);
        void            SetNext(ESceneObject* nextObject);
        ESceneObject*   GetNext() const;
        void            SetNewPrev(ESceneObject* prevObject);
        void            SetPrev(ESceneObject* prevObject);
        ESceneObject*   GetPrev() const;
        void            SetNewChild(ESceneObject* childObject);
        void            SetChild(ESceneObject* childObject);
        ESceneObject*   GetChild() const;
        void            SetNewParent(ESceneObject* parentObject);
        void            SetParent(ESceneObject* parentObject);
        ESceneObject*   GetParent() const;

        // Removes the object from the hierarchical tree
        void            UnlinkObject();




    };

}