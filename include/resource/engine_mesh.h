#pragma once

namespace Engine {

    class EMesh : public Resource
    {
    public:
        struct EVertex
        {
            
        };
    public:
        EMesh(const EString& name, const EString& filePath = "");
        ~EMesh();

        virtual bool OnReload() override;
    };

}