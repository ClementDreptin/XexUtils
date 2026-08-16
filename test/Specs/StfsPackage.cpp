#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void StfsPackage()
{
    Describe("StfsPackage::ReadHeader");

    It("reads the header of a theme package", []() {
        XexUtils::StfsPackage nxeart("game:\\fixtures\\stfs\\nxeart");
        auto header = nxeart.ReadHeader();

        TEST_EQ(header.HasValue(), true);
        TEST_EQ(header->SignatureType, StfsSignatureType_Live);
    });

    It("reads the header of a title update package", []() {
        XexUtils::StfsPackage titleUpdate("game:\\fixtures\\stfs\\title-update");
        auto header = titleUpdate.ReadHeader();

        TEST_EQ(header.HasValue(), true);
        TEST_EQ(header->SignatureType, StfsSignatureType_Live);
    });

    It("reads the header of a demo package", []() {
        XexUtils::StfsPackage demo("game:\\fixtures\\stfs\\demo");
        auto header = demo.ReadHeader();

        TEST_EQ(header.HasValue(), true);
        TEST_EQ(header->SignatureType, StfsSignatureType_Live);
    });

    It("reads the header of a gamesave package", []() {
        XexUtils::StfsPackage gamesave("game:\\fixtures\\stfs\\gamesave");
        auto header = gamesave.ReadHeader();

        TEST_EQ(header.HasValue(), true);
        TEST_EQ(header->SignatureType, StfsSignatureType_Con);
    });

    It("fails if the package doesn't exist", []() {
        XexUtils::StfsPackage inexistant("game:\\fixtures\\stfs\\inexistant");
        auto header = inexistant.ReadHeader();

        TEST_EQ(header.HasValue(), false);
    });

    Describe("StfsPackage::ReadMetadata");

    It("reads the metadata of a theme package", []() {
        XexUtils::StfsPackage nxeart("game:\\fixtures\\stfs\\nxeart");
        auto metadata = nxeart.ReadMetadata();

        TEST_EQ(metadata.HasValue(), true);
        TEST_EQ(metadata->ContentType, StfsContentType_Theme);
        TEST_EQ(metadata->ExecutionId.PublisherId, 0x1234);
        TEST_EQ(metadata->ExecutionId.GameId, 0x5678);
        TEST_EQ(metadata->VolumeDescriptorType, StfsVolumeDescriptorType_Stfs);
        TEST_EQ_W(metadata->DisplayNames[0], std::wstring(L"nxeart"));
        TEST_EQ_W(metadata->DisplayDescriptions[0], std::wstring(L"fake game assets"));
        TEST_EQ_W(metadata->TitleName, std::wstring(L"fake game"));
        TEST_EQ(metadata->TransferFlags, StfsTransferFlags_DeviceIdTransfer | StfsTransferFlags_ProfileIdTransfer);
        TEST_EQ(metadata->ThumbnailImageSize, 0xF4);
        TEST_EQ(metadata->TitleThumbnailImageSize, 0xF4);
        TEST_EQ(metadata->ThumbnailImage[0], 0x89);      // .
        TEST_EQ(metadata->ThumbnailImage[1], 0x50);      // 'P'
        TEST_EQ(metadata->ThumbnailImage[2], 0x4E);      // 'N'
        TEST_EQ(metadata->ThumbnailImage[3], 0x47);      // 'G'
        TEST_EQ(metadata->TitleThumbnailImage[0], 0x89); // .
        TEST_EQ(metadata->TitleThumbnailImage[1], 0x50); // 'P'
        TEST_EQ(metadata->TitleThumbnailImage[2], 0x4E); // 'N'
        TEST_EQ(metadata->TitleThumbnailImage[3], 0x47); // 'G'
    });

    It("reads the metadata of a title update package", []() {
        XexUtils::StfsPackage titleUpdate("game:\\fixtures\\stfs\\title-update");
        auto metadata = titleUpdate.ReadMetadata();

        TEST_EQ(metadata.HasValue(), true);
        TEST_EQ(metadata->ContentType, StfsContentType_Installer);
        TEST_EQ(metadata->ExecutionId.PublisherId, 0x1234);
        TEST_EQ(metadata->ExecutionId.GameId, 0x5678);
        TEST_EQ(metadata->VolumeDescriptorType, StfsVolumeDescriptorType_Stfs);
        TEST_EQ_W(metadata->DisplayNames[0], std::wstring(L"Title Update"));
    });

    It("reads the metadata of a demo package", []() {
        XexUtils::StfsPackage demo("game:\\fixtures\\stfs\\demo");
        auto metadata = demo.ReadMetadata();

        TEST_EQ(metadata.HasValue(), true);
        TEST_EQ(metadata->ContentType, StfsContentType_GameDemo);
        TEST_EQ(metadata->ExecutionId.PublisherId, 0x1234);
        TEST_EQ(metadata->ExecutionId.GameId, 0x5678);
        TEST_EQ(metadata->VolumeDescriptorType, StfsVolumeDescriptorType_Stfs);
        TEST_EQ_W(metadata->DisplayNames[0], std::wstring(L"fake game"));
        TEST_EQ_W(metadata->DisplayDescriptions[0], std::wstring(L"fake game demo"));
        TEST_EQ_W(metadata->TitleName, std::wstring(L"fake game"));
        TEST_EQ(metadata->TransferFlags, StfsTransferFlags_DeviceIdTransfer | StfsTransferFlags_ProfileIdTransfer);
        TEST_EQ(metadata->ThumbnailImageSize, 0x8E);
        TEST_EQ(metadata->TitleThumbnailImageSize, 0x8E);
        TEST_EQ(metadata->ThumbnailImage[0], 0x89);      // .
        TEST_EQ(metadata->ThumbnailImage[1], 0x50);      // 'P'
        TEST_EQ(metadata->ThumbnailImage[2], 0x4E);      // 'N'
        TEST_EQ(metadata->ThumbnailImage[3], 0x47);      // 'G'
        TEST_EQ(metadata->TitleThumbnailImage[0], 0x89); // .
        TEST_EQ(metadata->TitleThumbnailImage[1], 0x50); // 'P'
        TEST_EQ(metadata->TitleThumbnailImage[2], 0x4E); // 'N'
        TEST_EQ(metadata->TitleThumbnailImage[3], 0x47); // 'G'
    });

    It("reads the metadata of a gamesave package", []() {
        XexUtils::StfsPackage gamesave("game:\\fixtures\\stfs\\gamesave");
        auto metadata = gamesave.ReadMetadata();

        TEST_EQ(metadata.HasValue(), true);
        TEST_EQ(metadata->ContentType, StfsContentType_SavedGame);
        TEST_EQ(metadata->ExecutionId.PublisherId, 0xFFFF);
        TEST_EQ(metadata->ExecutionId.GameId, 0x11D);
        TEST_EQ(metadata->VolumeDescriptorType, StfsVolumeDescriptorType_Stfs);
        TEST_EQ_W(metadata->DisplayNames[0], std::wstring(L"game3"));
        TEST_EQ(metadata->TransferFlags, StfsTransferFlags_DeviceIdTransfer);
        TEST_EQ(metadata->ThumbnailImageSize, 0x78D);
        TEST_EQ(metadata->TitleThumbnailImageSize, 0x20A);
        TEST_EQ(metadata->ThumbnailImage[0], 0x89);      // .
        TEST_EQ(metadata->ThumbnailImage[1], 0x50);      // 'P'
        TEST_EQ(metadata->ThumbnailImage[2], 0x4E);      // 'N'
        TEST_EQ(metadata->ThumbnailImage[3], 0x47);      // 'G'
        TEST_EQ(metadata->TitleThumbnailImage[0], 0x89); // .
        TEST_EQ(metadata->TitleThumbnailImage[1], 0x50); // 'P'
        TEST_EQ(metadata->TitleThumbnailImage[2], 0x4E); // 'N'
        TEST_EQ(metadata->TitleThumbnailImage[3], 0x47); // 'G'
    });

    It("fails if the package doesn't exist", []() {
        XexUtils::StfsPackage inexistant("game:\\fixtures\\stfs\\inexistant");
        auto metadata = inexistant.ReadMetadata();

        TEST_EQ(metadata.HasValue(), false);
    });

    Describe("StfsPackage::Mount");

    It("mounts the files of a theme package", []() {
        XexUtils::StfsPackage nxeart("game:\\fixtures\\stfs\\nxeart");

        HRESULT hr = nxeart.Mount("nxeart");
        TEST_EQ(hr, S_OK);

        auto files = Fs::ReadDirectory("nxeart:\\");
        TEST_EQ(files.HasValue(), true);
        TEST_EQ(files->size(), 3);
        TEST_EQ((*files)[0].cFileName, std::string("DashStyle"));
        TEST_EQ((*files)[1].cFileName, std::string("nxebg.jpg"));
        TEST_EQ((*files)[2].cFileName, std::string("nxeslot.jpg"));
    });

    It("mounts the files of a title update package", []() {
        XexUtils::StfsPackage titleUpdate("game:\\fixtures\\stfs\\title-update");

        HRESULT hr = titleUpdate.Mount("titleUpdate");
        TEST_EQ(hr, S_OK);

        auto files = Fs::ReadDirectory("titleUpdate:\\");
        TEST_EQ(files.HasValue(), true);
        TEST_EQ(files->size(), 2);
        TEST_EQ((*files)[0].cFileName, std::string("12345678.ini"));
        TEST_EQ((*files)[1].cFileName, std::string("fake-game.xexp"));
    });

    It("mounts the files of a demo package", []() {
        XexUtils::StfsPackage demo("game:\\fixtures\\stfs\\demo");

        HRESULT hr = demo.Mount("demo");
        TEST_EQ(hr, S_OK);

        auto files = Fs::ReadDirectory("demo:\\");
        TEST_EQ(files.HasValue(), true);
        TEST_EQ(files->size(), 1);
        TEST_EQ((*files)[0].cFileName, std::string("fake-game.xex"));
    });

    It("mounts the files of a gamesave package", []() {
        XexUtils::StfsPackage gamesave("game:\\fixtures\\stfs\\gamesave");

        HRESULT hr = gamesave.Mount("gamesave");
        TEST_EQ(hr, S_OK);

        auto files = Fs::ReadDirectory("gamesave:\\");
        TEST_EQ(files.HasValue(), true);
        TEST_EQ(files->size(), 1);
        TEST_EQ((*files)[0].cFileName, std::string("savegame.txt"));
    });

    It("fails if the package doesn't exist", []() {
        XexUtils::StfsPackage inexistant("game:\\fixtures\\stfs\\inexistant");
        HRESULT hr = inexistant.Mount("inexistant");

        TEST_EQ(hr, ERROR_FILE_NOT_FOUND);
    });

    Describe("StfsPackage::Unmount");

    It("unmounts the files of a theme package", []() {
        XexUtils::StfsPackage nxeart("game:\\fixtures\\stfs\\nxeart");

        HRESULT hr = nxeart.Mount("nxeart");
        auto files = Fs::ReadDirectory("nxeart:\\");
        TEST_EQ(files.HasValue(), true);

        hr = nxeart.Unmount();
        TEST_EQ(hr, S_OK);
        files = Fs::ReadDirectory("nxeart:\\");
        TEST_EQ(files.HasValue(), false);
    });

    It("unmounts the files of a title update package", []() {
        XexUtils::StfsPackage titleUpdate("game:\\fixtures\\stfs\\title-update");

        HRESULT hr = titleUpdate.Mount("titleUpdate");
        auto files = Fs::ReadDirectory("titleUpdate:\\");
        TEST_EQ(files.HasValue(), true);

        hr = titleUpdate.Unmount();
        TEST_EQ(hr, S_OK);
        files = Fs::ReadDirectory("titleUpdate:\\");
        TEST_EQ(files.HasValue(), false);
    });

    It("unmounts the files of a demo package", []() {
        XexUtils::StfsPackage demo("game:\\fixtures\\stfs\\demo");

        HRESULT hr = demo.Mount("demo");
        auto files = Fs::ReadDirectory("demo:\\");
        TEST_EQ(files.HasValue(), true);

        hr = demo.Unmount();
        TEST_EQ(hr, S_OK);
        files = Fs::ReadDirectory("demo:\\");
        TEST_EQ(files.HasValue(), false);
    });

    It("unmounts the files of a gamesave package", []() {
        XexUtils::StfsPackage gamesave("game:\\fixtures\\stfs\\gamesave");

        HRESULT hr = gamesave.Mount("gamesave");
        auto files = Fs::ReadDirectory("gamesave:\\");
        TEST_EQ(files.HasValue(), true);

        hr = gamesave.Unmount();
        TEST_EQ(hr, S_OK);
        files = Fs::ReadDirectory("gamesave:\\");
        TEST_EQ(files.HasValue(), false);
    });

    It("fails if the package was never mounted", []() {
        XexUtils::StfsPackage nxeart("game:\\fixtures\\stfs\\nxeart");

        HRESULT hr = nxeart.Unmount();
        TEST_EQ(hr, E_FAIL);
    });
}
