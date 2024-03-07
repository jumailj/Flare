#include <Flare/Utils/PlatformUtils.h>

/*native file dialog*/
#include <nfd.h>

#include<Flare/Core/Log.h>


namespace Flare{

    void FileDialogs::Init() {
           //  NFD_Init(); // init the filter first
    }


    std::string FileDialogs::OpenFile(const char* filter)
    {

          // init file dialog

        NFD_Init();

        nfdchar_t *outPath;
      //  nfdfilteritem_t filterItem[2] = { { "Source code", "c,cpp,cc" }, { "Headers", "h,hpp" } };
        nfdfilteritem_t filterItem[1] = { "Source code", "*.flare" }; //TODO currently not working.
        nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 1, NULL);
        if (result == NFD_OKAY)
        {
            puts("Success!");
            puts(outPath);

            std::string value = outPath;
            LOG_WARN("file path: {0}", outPath);
            NFD_FreePath(outPath);

            return value;
        }

        return std::string();
    }


    std::string FileDialogs::SaveFile(const char* filter)
    {
        NFD_Init();

        nfdu8char_t *outPath = NULL;
        nfdu8filteritem_t filterList[] = { { "Text Files", "txt,md" }, { "Images", "png,jpg,jpeg,gif" } };
        nfdresult_t result = NFD_SaveDialogU8(&outPath, filterList, sizeof(filterList) / sizeof(nfdu8filteritem_t), NULL, "");

        if (result == NFD_OKAY) {
            printf("Success: %s\n", outPath);
            std::string value = outPath;
            return value;

            free(outPath);
        } else if (result == NFD_CANCEL) {
            printf("User pressed cancel.\n");
        } else {
            printf("Error: %s\n", NFD_GetError());
        }


        return std::string();
    }


}