#pragma once

namespace Engine {

    namespace ImGuiHelper
    {
        void ResetImGuiState();
    }
    class EUIManager
    {
    private:
        EVector<ERef<EUIPanel>>     fRegisteredPanels;
    public:

        EVector<ERef<EUIPanel>>     GetPanels() const;
        void RegisterPanel(ERef<EUIPanel> panel);
    };

}