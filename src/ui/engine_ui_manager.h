#pragma once

namespace Engine {

    namespace ImGuiHelper
    {
        E_API void ResetImGuiState();
    }
    E_API class EUIManager
    {
    private:
        EVector<ERef<EUIPanel>>     fRegisteredPanels;
    public:

        EVector<ERef<EUIPanel>>     GetPanels() const;
        void RegisterPanel(ERef<EUIPanel> panel);
    };

}