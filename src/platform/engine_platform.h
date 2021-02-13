#pragma once

namespace Engine {
    namespace Platform {
        extern EVector<EString> OpenFileDialog(const EString& title, const EString& defaultPath, const EVector<EString>& filters);
    };
};