#pragma once

namespace Engine {


    namespace UI {

        

        void Init(EWindow& window);
        void NewFrame();
        void Render();
        ImGuiContext* GetContext();

    }


}