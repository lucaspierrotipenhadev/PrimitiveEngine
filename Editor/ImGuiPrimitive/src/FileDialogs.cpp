#include "Primitive/ImGuiPrimitive/FileDialogs.hpp"

#include <nfd.h>

namespace primitive
{
    std::optional<std::filesystem::path> FileDialogs::SaveScene()
    {
        nfdu8char_t* outputPath = nullptr;

        const nfdu8filteritem_t filters[] = {{"Primitive Scene", "pscene"}};
        const nfdresult_t result = NFD_SaveDialogU8(&outputPath, filters, 1, nullptr, "Untitled.pscene");

        if(result == NFD_OKAY)
        {
            std::filesystem::path path{outputPath};
            NFD_FreePathU8(outputPath);

            return path;
        }

        if(result == NFD_CANCEL)
        {
            return std::nullopt;
        }

        return std::nullopt;
    }

    std::optional<std::filesystem::path> FileDialogs::OpenScene()
    {
        nfdu8char_t* outputPath = nullptr;

        const nfdu8filteritem_t filters[] = {{"Primitive Scene", "pscene"}};
        const nfdresult_t result = NFD_OpenDialogU8(&outputPath, filters, 1, nullptr);

        if(result == NFD_OKAY)
        {
            std::filesystem::path path{outputPath};
            NFD_FreePathU8(outputPath);

            return path;
        }

        return std::nullopt;
    }
}