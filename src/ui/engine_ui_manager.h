#pragma once

namespace Engine {

    class EUIManager
    {
    private:
        EVector<ERef<EUIPanel>>     fRegisteredPanels;
    public:

        void RegisterPanel(ERef<EUIPanel> panel);
    };

}