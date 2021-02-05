#pragma once

namespace Engine {

    class EUIManager
    {
    private:
        EVector<ERef<EUIPanel>>     fRegisteredPanels;
    public:

        EVector<ERef<EUIPanel>>     GetPanels() const;
        void RegisterPanel(ERef<EUIPanel> panel);
    };

}