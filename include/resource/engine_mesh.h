#pragma once

namespace Engine {

    class EMesh : public EResource
    {
    public:
        EMesh(const EString& name, const EString& filePath = "");
        ~EMesh();

        
    };

}