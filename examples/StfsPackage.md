# StfsPackage

Read the header of an STFS package:

```C++
void Init()
{
    XexUtils::StfsPackage gamesave("hdd:\\game\\gamesave");
    XexUtils::Optional<XexUtils::StfsHeader> header = gamesave.ReadHeader();
    if (!header)
    {
        XexUtils::Log::Print("Couldn't read the header.");
        return;
    }

    header->SignatureType; // XexUtils::StfsSignatureType_Con
    header->Signature.ConSignature.CertificateSignature; // byte array
    header->Signature.ConSignature.PublicModulus; // byte array
    // ...
}
```

Read the metadata of an STFS package:

```C++
void Init()
{
    XexUtils::StfsPackage nxeart("hdd:\\game\\nxeart");
    XexUtils::Optional<XexUtils::StfsMetadata> metadata = gamesave.ReadMetadata();
    if (!metadata)
    {
        XexUtils::Log::Print("Couldn't read the metadata.");
        return;
    }

    metadata->ContentType; // XexUtils::StfsContentType_Theme
    metadata->VolumeDescriptorType; // XexUtils::StfsVolumeDescriptorType_Stfs
    metadata->DisplayNames[0]; // L"nxeart"
    metadata->ThumbnailImage; // byte array of PNG data
    metadata->TitleThumbnailImage; // byte array of PNG data
}
```

Mount the files of an STFS package to a logical drive:

```C++
void Init()
{
    XexUtils::StfsPackage nxeart("hdd:\\game\\nxeart");
    HRESULT hr = nxeart.Mount("nxeart");
    if (FAILED(hr))
    {
        XexUtils::Log::Print("Couldn't create the nxeart:\\ drive.");
        return;
    }

    std::ifstream file("nxeart:\\nxeslot.jpg");
    // Do something with the file...
}
```

Unmount the previously mounted files of an STFS package:

```C++
void Init()
{
    XexUtils::StfsPackage nxeart("hdd:\\game\\nxeart");
    nxeart.Mount("nxeart");
    nxeart.Unmount();

    std::ifstream file("nxeart:\\nxeslot.jpg"); // Doesn't work.
}
```

> [!NOTE]
> It is not absolutely required to call `Unmount` manually. The `StfsPackage` destructor will call `Unmount` if the package is mounted.
