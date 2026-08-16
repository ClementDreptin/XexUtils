#include "pch.h"
#include "StfsPackage.h"

#include "Xam.h"

namespace XexUtils
{

StfsPackage::StfsPackage()
{
}

StfsPackage::StfsPackage(const XexUtils::Fs::Path &filePath)
    : m_FilePath(filePath)
{
}

StfsPackage::~StfsPackage()
{
    // Unmount if needed.
    if (!m_MountDiskName.empty())
        Unmount();
}

Optional<StfsHeader> StfsPackage::ReadHeader() const
{
    XASSERT(!m_FilePath.IsEmpty());

    // Open the file.
    std::ifstream file(m_FilePath.c_str(), std::ios::binary);
    if (!file.is_open())
    {
        DebugPrint(
            "[XexUtils][StfsPackage]: Error: Couldn't open %s for reading.",
            m_FilePath.c_str()
        );
        return NullOpt();
    }

    // Read the header.
    StfsHeader header = {};
    file.read(reinterpret_cast<char *>(&header), sizeof(header));
    if (!file)
    {
        DebugPrint(
            "[XexUtils][StfsPackage]: Error: Couldn't read the STFS header of %s.",
            m_FilePath.c_str()
        );
        return NullOpt();
    }

    return header;
}

Optional<StfsMetadata> StfsPackage::ReadMetadata() const
{
    XASSERT(!m_FilePath.IsEmpty());

    // Open the file.
    std::ifstream file(m_FilePath.c_str(), std::ios::binary);
    if (!file.is_open())
    {
        DebugPrint(
            "[XexUtils][StfsPackage]: Error: Couldn't open %s for reading.",
            m_FilePath.c_str()
        );
        return NullOpt();
    }

    // Move the file pointer to point to the start of the metadata. The metadata is right
    // after the header, which is at the start of the file.
    file.seekg(sizeof(StfsHeader));
    if (!file)
    {
        DebugPrint(
            "[XexUtils][StfsPackage]: Error: Couldn't set the file pointer of %s to point"
            " to the beginning of the metadata.",
            m_FilePath.c_str()
        );
        return NullOpt();
    }

    // Read the metadata.
    StfsMetadata metadata = {};
    file.read(reinterpret_cast<char *>(&metadata), sizeof(metadata));
    if (!file)
    {
        DebugPrint(
            "[XexUtils][StfsPackage]: Error: Couldn't read the STFS metadata of %s.",
            m_FilePath.c_str()
        );
        return NullOpt();
    }

    return metadata;
}

HRESULT StfsPackage::Mount(const std::string &diskName)
{
    // Store the mount disk name for later when we have to unmount.
    m_MountDiskName = diskName;

    // Do the mounting.
    std::string linkName = "\\??\\" + m_FilePath.String();
    HRESULT hr = XamContentOpenFile(
        0,
        m_MountDiskName.c_str(),
        linkName.c_str(),
        XCONTENTFLAG_OPENEXISTING,
        0,
        nullptr,
        nullptr
    );

#ifndef NDEBUG
    if (FAILED(hr))
        DebugPrint(
            "[XexUtils][StfsPackage]: Error: Couldn't mount the contents of %s at %s (%X).",
            m_FilePath.c_str(),
            m_MountDiskName.c_str(),
            hr
        );
#endif

    return hr;
}

HRESULT StfsPackage::Unmount()
{
    if (m_MountDiskName.empty())
    {
        DebugPrint("[XexUtils][StfsPackage]: Error: Can't unmount a package that was never mounted.");
        return E_FAIL;
    }

    HRESULT hr = XContentClose(m_MountDiskName.c_str(), nullptr);
    if (FAILED(hr))
    {
        DebugPrint(
            "[XexUtils][StfsPackage]: Error: Couldn't unmount the contents of %s from %s (%X).",
            m_FilePath.c_str(),
            m_MountDiskName.c_str(),
            hr
        );
        return hr;
    }

    m_MountDiskName.clear();

    return S_OK;
}

}
