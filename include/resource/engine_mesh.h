#pragma once

namespace Engine {

    class EMesh : public EResource
    {
    public:
        struct EVertex
        {
            
        };
    public:
        EMesh(const EString& name, const EString& filePath = "");
        ~EMesh();

        virtual bool OnLoad() override;
    };

}