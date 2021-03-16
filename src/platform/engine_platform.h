#pragma once

namespace Engine {
    namespace Platform {
        extern EVector<EString> OpenFileDialog(const EString& title, const EVector<EString>& filters = {}, const EString& defaultPath = EFolder::GetBaseFolderPath(EBaseFolder::APPLICATION));
        extern EString SaveFileDialog(const EString& title);
    };
};