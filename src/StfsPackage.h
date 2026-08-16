#pragma once

#include "Filesystem.h"
#include "Kernel.h"
#include "Optional.h"

namespace XexUtils
{

struct StfsHeader;
struct StfsMetadata;

/// @brief A class to represent an STFS package.
class StfsPackage
{
public:
    /// @brief Creates an empty `StfsPackage`.
    StfsPackage();

    /// @brief Creates an `StfsPackage` from a file on disk.
    /// @param filePath The path to the file on disk.
    StfsPackage(const XexUtils::Fs::Path &filePath);

    /// @brief Unmounts the `StfsPackage` if it was mounted.
    ~StfsPackage();

    /// @brief Reads an `StfsHeader` from the file on disk.
    ///
    /// This function can fail if opening or reading the file fails.
    ///
    /// @return A valid `Optional<StfsHeader>` on success, an empty `Optional` on error.
    Optional<StfsHeader> ReadHeader() const;

    /// @brief Reads an `StfsMetadata` from the file on disk.
    ///
    /// This function can fail if opening or reading the file fails.
    ///
    /// @return A valid `Optional<StfsMetadata>` on success, an empty `Optional` on error.
    Optional<StfsMetadata> ReadMetadata() const;

    /// @brief Mounts the contents of the `StfsPackage` to a logical drive.
    ///
    /// This function can fail if `diskName` is not a valid drive name or if a drive named
    /// `diskName` already exists.
    ///
    /// @param diskName The name of the logical drive.
    /// @return `S_OK` on success, an error code on error.
    HRESULT Mount(const std::string &diskName);

    /// @brief Unmounts the logical drive previously created with `Mount()`.
    ///
    /// This function can fail if the `StfsPackage` was never mounted.
    ///
    /// @return `S_OK` on success, an error code on error.
    HRESULT Unmount();

private:
    XexUtils::Fs::Path m_FilePath;
    std::string m_MountDiskName;
};

#pragma warning(push)
#pragma warning(disable : 4480)

#pragma pack(push, 1)

// These structs and enums were found here:
// https://free60.org/System-Software/Formats/STFS/

typedef enum _StfsSignatureType
{
    StfsSignatureType_Con = 0x434F4E20,  // "CON " in ascii
    StfsSignatureType_Pirs = 0x50495253, // "PIRS" in ascii
    StfsSignatureType_Live = 0x4C495645, // "LIVE" in ascii
} StfsSignatureType;

typedef enum _StfsCertificateOwnerConsoleType : uint8_t
{
    StfsCertificateOwnerConsoleType_Devkit = 1,
    StfsCertificateOwnerConsoleType_Retail,
} StfsCertificateOwnerConsoleType;

struct StfsConSignature
{
    uint16_t PublicKeyCertificateSize;
    uint8_t CertificateOwnerConsoleId[5];
    char CertificateOwnerConsolePartNumber[20];
    StfsCertificateOwnerConsoleType CertificateOwnerConsoleType;
    char CertificateGenerationDate[8];
    uint8_t PublicExponent[4];
    uint8_t PublicModulus[0x80];
    uint8_t CertificateSignature[0x100];
    uint8_t Signature[0x80];
};

struct StfsPirsSignature
{
    uint8_t Signature[0x100];
    uint8_t Padding[0x128];
};

struct StfsLiveSignature
{
    uint8_t Signature[0x100];
    uint8_t Padding[0x128];
};

union StfsSignature {
    StfsConSignature ConSignature;
    StfsPirsSignature PirsSignature;
    StfsLiveSignature LiveSignature;
};

struct StfsHeader
{
    StfsSignatureType SignatureType;
    StfsSignature Signature;
};

struct StfsLicenseEntry
{
    uint64_t LicenceId;
    uint32_t LicenceBits;
    uint32_t LicenceFlags;
};

typedef enum _StfsContentType
{
    StfsContentType_SavedGame = 0x1,
    StfsContentType_MarketplaceContent = 0x2,
    StfsContentType_Publisher = 0x3,
    StfsContentType_Xbox360Title = 0x1000,
    StfsContentType_IPTVPauseBuffer = 0x2000,
    StfsContentType_InstalledGame = 0x4000,
    StfsContentType_XboxTitle = 0x5000,
    StfsContentType_GameOnDemand = 0x7000,
    StfsContentType_AvatarItem = 0x9000,
    StfsContentType_Profile = 0x10000,
    StfsContentType_GamerPicture = 0x20000,
    StfsContentType_Theme = 0x30000,
    StfsContentType_CacheFile = 0x40000,
    StfsContentType_StorageDownload = 0x50000,
    StfsContentType_XboxSavedGame = 0x60000,
    StfsContentType_XboxDownload = 0x70000,
    StfsContentType_GameDemo = 0x80000,
    StfsContentType_Video = 0x90000,
    StfsContentType_GameTitle = 0xA0000,
    StfsContentType_Installer = 0xB0000,
    StfsContentType_GameTrailer = 0xC0000,
    StfsContentType_ArcadeTitle = 0xD0000,
    StfsContentType_XNA = 0xE0000,
    StfsContentType_LicenseStore = 0xF0000,
    StfsContentType_Movie = 0x100000,
    StfsContentType_TV = 0x200000,
    StfsContentType_MusicVideo = 0x300000,
    StfsContentType_GameVideo = 0x400000,
    StfsContentType_PodcastVideo = 0x500000,
    StfsContentType_ViralVideo = 0x600000,
    StfsContentType_CommunityGame = 0x2000000,
} StfsContentType;

typedef enum _StfsPlatform : uint8_t
{
    StfsPlatform_Xbox360 = 2,
    StfsPlatform_PC = 4,
} StfsPlatform;

struct StfsVolumeDescriptorStfs
{
    uint8_t VolumeDescriptorSize;
    uint8_t Reserved;
    uint8_t BlockSeparation;
    uint16_t FileTableBlockCount;
    uint8_t FileTableBlockNumber[3];
    uint8_t TopHashTableHash[20];
    uint32_t TotalAllocatedBlockCount;
    uint32_t TotalUnallocatedBlockCount;
};

struct StfsVolumeDescriptorSvod
{
    uint8_t VolumeDescriptorSize;
    uint8_t BlockCacheElementCount;
    uint8_t WorkerThreadProcessor;
    uint8_t WorkerThreadPriority;
    uint8_t Hash[20];
    uint8_t DeviceFeatures;
    uint8_t DataBlockCount[3];
    uint8_t DataBlockOffset[3];
    uint8_t Padding[0x5];
};

union StfsVolumeDescriptor {
    StfsVolumeDescriptorStfs Stfs;
    StfsVolumeDescriptorSvod Svod;
};

typedef enum _StfsVolumeDescriptorType
{
    StfsVolumeDescriptorType_Stfs,
    StfsVolumeDescriptorType_Svod,
} StfsVolumeDescriptorType;

typedef uint8_t StfsTransferFlags;

enum StfsTransferFlags_
{
    StfsTransferFlags_None = 1 << 0,
    StfsTransferFlags_Unknown = 1 << 1,
    StfsTransferFlags_DeepLinkSupported = 1 << 2,
    StfsTransferFlags_DisableNetworkStorage = 1 << 3,
    StfsTransferFlags_KinectEnabled = 1 << 4,
    StfsTransferFlags_MoveOnlyTransfer = 1 << 5,
    StfsTransferFlags_DeviceIdTransfer = 1 << 6,
    StfsTransferFlags_ProfileIdTransfer = 1 << 7,
};

struct StfsMetadata
{
    StfsLicenseEntry LicenseEntries[16];
    uint8_t HeaderSha1Hash[20];
    uint32_t HeaderSize;
    StfsContentType ContentType;
    uint32_t MetadataVersion;
    uint64_t ContentSize;
    XEX_EXECUTION_ID ExecutionId;
    uint8_t ConsoleId[5];
    XUID ProfileId;
    StfsVolumeDescriptor VolumeDescriptor;
    uint32_t DataFileCount;
    uint64_t DataFileCombinedSize;
    StfsVolumeDescriptorType VolumeDescriptorType;
    uint32_t Reserved;
    uint8_t SeriesId[16];
    uint8_t SeasonId[16];
    uint16_t SeasonNumber;
    uint16_t EpisodeNumber;
    uint8_t Padding[0x28];
    uint8_t DeviceId[20];
    wchar_t DisplayNames[18][64];
    wchar_t DisplayDescriptions[18][64];
    wchar_t PublisherName[64];
    wchar_t TitleName[64];
    StfsTransferFlags TransferFlags;
    uint32_t ThumbnailImageSize;
    uint32_t TitleThumbnailImageSize;
    uint8_t ThumbnailImage[0x3D00];
    wchar_t AdditionalDisplayNames[6][64];
    uint8_t TitleThumbnailImage[0x3D00];
    wchar_t AdditionalDisplayDescriptions[6][64];
};

#pragma pack(pop)

#pragma warning(pop)

}
