#include "core/assets.h"

Font fonteMenu;

void carregarAssetsGlobais(void)
{
    fonteMenu =
        LoadFontEx(
            "assets/fonts/Exo2-Bold.ttf",
            64,
            0,
            0
        );
}