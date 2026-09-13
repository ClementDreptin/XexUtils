#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <xtl.h>

#include "Filesystem.h"
#include "Kernel.h"
#include "Log.h"
#include "Optional.h"

namespace XexUtils
{
namespace Fs
{

const char Path::s_Separator = '\\';

Path::Path()
{
}

Path::Path(const std::string &path)
    : m_Path(path)
{
}

Path::Path(std::string &&path)
    : m_Path(std::move(path))
{
}

Path::Path(const char *path)
    : m_Path(path)
{
}

Path::Path(const Path &other)
    : m_Path(other.m_Path)
{
}

Path::Path(Path &&other)
    : m_Path(std::move(other.m_Path))
{
}

Path &Path::operator=(const Path &other)
{
    if (this == &other)
        return *this;

    m_Path = other.m_Path;

    return *this;
}

Path &Path::operator=(Path &&other)
{
    if (this == &other)
        return *this;

    m_Path = std::move(other.m_Path);

    return *this;
}

Path::~Path()
{
}

Path Path::Drive() const
{
    size_t colonPos = m_Path.find_first_of(':');

    if (colonPos == std::string::npos)
        return Path();

    return Path(m_Path.substr(0, colonPos + 1));
}

Path Path::Basename() const
{
    size_t lastSeparatorPos = m_Path.find_last_of(s_Separator);
    size_t lastDotPos = m_Path.find_last_of('.');
    size_t colonPos = m_Path.find_first_of(':');
    size_t characterBeforeFileNamePos = lastSeparatorPos != std::string::npos ? lastSeparatorPos : colonPos;

    // Case of path only containing a drive
    if (colonPos == m_Path.size() - 1)
        return Path();

    // Case of file name starting with a dot and no extension (like .gitignore)
    if (lastDotPos == characterBeforeFileNamePos + 1)
        return Path(m_Path.substr(characterBeforeFileNamePos + 1));

    return Path(m_Path.substr(characterBeforeFileNamePos + 1, lastDotPos - characterBeforeFileNamePos - 1));
}

Path Path::Extension() const
{
    size_t lastSeparatorPos = m_Path.find_last_of(s_Separator);
    size_t lastDotPos = m_Path.find_last_of('.');
    size_t colonPos = m_Path.find_first_of(':');
    size_t characterBeforeFileNamePos = lastSeparatorPos != std::string::npos ? lastSeparatorPos : colonPos;

    // No dot or dot is the first character of the file name (like .gitignore)
    if (lastDotPos == std::string::npos || lastDotPos == characterBeforeFileNamePos + 1)
        return Path();

    return Path(m_Path.substr(lastDotPos));
}

Path Path::Filename() const
{
    return Basename().String() + Extension().String();
}

Path Path::Parent() const
{
    if (IsEmpty())
        return Path();

    if (IsRoot())
        return *this;

    // When the path is a directory (so ends with the separator), we make the offset
    // to be one character before so that lastSeparatorPos doesn't point the very last
    // separator but the one before.
    size_t offset = std::string::npos;
    if (m_Path.back() == s_Separator)
        offset = m_Path.size() - 2;

    size_t lastSeparatorPos = m_Path.find_last_of(s_Separator, offset);

    // Handle the absolute path case.
    if (lastSeparatorPos == 0)
        return Path(std::string(1, s_Separator));

    // Handle the no separator case.
    if (lastSeparatorPos == std::string::npos)
    {
        // If we have a drive but no separator, we have a path that looks like "C:File.txt"
        // so we just return the drive.
        Path drive = Drive();
        if (!drive.IsEmpty())
            return drive;

        // If we don't have a drive and no separator, we have just a filename like "File.txt"
        // so we just return an empty Path.
        return Path();
    }

    // Handle the case where the last separator is the drive root, if that the case,
    // include the separator in the Path.
    size_t endOffset = lastSeparatorPos;
    size_t colonPos = m_Path.find_first_of(':');
    if (lastSeparatorPos == colonPos + 1)
        endOffset = lastSeparatorPos + 1;

    return Path(m_Path.substr(0, endOffset));
}

Path Path::RelativePath() const
{
    return m_Path.substr(Drive().Size());
}

Path &Path::Append(const Path &path)
{
    const std::string &otherAsString = path.String();
    const std::string &currentWithoutFinalSeparator = !IsEmpty() && m_Path.back() == s_Separator ? m_Path.substr(0, m_Path.size() - 1) : m_Path;
    const std::string &otherWithoutFirstSeparator = !path.IsEmpty() && otherAsString.front() == s_Separator ? otherAsString.substr(1) : otherAsString;

    m_Path = currentWithoutFinalSeparator + s_Separator + otherWithoutFirstSeparator;

    return *this;
}

bool Path::Compare(const Path &other) const
{
    return String() == other.String();
}

bool Path::IsEmpty() const
{
    return m_Path.empty();
}

bool Path::IsRoot() const
{
    if (IsEmpty())
        return true;

    // If the path is a path of a file it can't be the root of drive
    if (!Filename().IsEmpty())
        return false;

    size_t lastSeparatorPos = m_Path.find_last_of(s_Separator);
    size_t colonPos = m_Path.find_first_of(':');

    return colonPos == m_Path.size() - 1 || lastSeparatorPos == colonPos + 1;
}

const char *Path::c_str() const
{
    return m_Path.c_str();
}

size_t Path::Size() const
{
    return m_Path.size();
}

HRESULT MountPath(const std::string &linkName, const std::string &devicePath)
{
    // The system only allows executables to access the directory they live in and binds it to
    // the "game:" drive. Nothing else is accessible unless you create a symbolic link.

    STRING link = {};
    STRING device = {};
    std::string userDestinationDrive = "\\??\\" + linkName;
    std::string systemDestinationDrive = "\\System??\\" + linkName;

    // Initialize the STRING structs
    if (KeGetCurrentProcessType() == PROC_TYPE_SYSTEM)
        RtlInitAnsiString(&link, systemDestinationDrive.c_str());
    else
        RtlInitAnsiString(&link, userDestinationDrive.c_str());

    RtlInitAnsiString(&device, devicePath.c_str());

    // Bind devicePath to the linkName.
    return ObCreateSymbolicLink(&link, &device);
}

HRESULT MountHdd()
{
    return MountPath("hdd:", "\\Device\\Harddisk0\\Partition1\\");
}

HRESULT MountUsb()
{
    return MountPath("usb:", "\\Device\\Mass0\\");
}

HRESULT UnmountPath(const std::string &linkName)
{
    STRING link = {};
    std::string userDestinationDrive = "\\??\\" + linkName;
    std::string systemDestinationDrive = "\\System??\\" + linkName;

    // Initialize the STRING structs
    if (KeGetCurrentProcessType() == PROC_TYPE_SYSTEM)
        RtlInitAnsiString(&link, systemDestinationDrive.c_str());
    else
        RtlInitAnsiString(&link, userDestinationDrive.c_str());

    // Remove the symbolic link
    return ObDeleteSymbolicLink(&link);
}

HRESULT UnmountHdd()
{
    return UnmountPath("hdd:");
}

HRESULT UnmountUsb()
{
    return UnmountPath("usb:");
}

File::File()
    : Size(0), Attributes(0), CreationTime(0), LastReadTime(0), LastWriteTime(0)
{
}

File::File(const File &other)
    : FullPath(other.FullPath), Size(other.Size), Attributes(other.Attributes), CreationTime(other.CreationTime), LastReadTime(other.LastReadTime), LastWriteTime(other.LastWriteTime)
{
}

File::File(File &&other)
    : FullPath(std::move(other.FullPath)), Size(other.Size), Attributes(other.Attributes), CreationTime(other.CreationTime), LastReadTime(other.LastReadTime), LastWriteTime(other.LastWriteTime)
{
    other.Size = 0;
    other.Attributes = 0;
    other.CreationTime = 0;
    other.LastReadTime = 0;
    other.LastWriteTime = 0;
}

File &File::operator=(const File &other)
{
    if (this == &other)
        return *this;

    FullPath = other.FullPath;
    Size = other.Size;
    Attributes = other.Attributes;
    CreationTime = other.CreationTime;
    LastReadTime = other.LastReadTime;
    LastWriteTime = other.LastWriteTime;

    return *this;
}

File &File::operator=(File &&other)
{
    if (this == &other)
        return *this;

    FullPath = std::move(other.FullPath);
    Size = other.Size;
    Attributes = other.Attributes;
    CreationTime = other.CreationTime;
    LastReadTime = other.LastReadTime;
    LastWriteTime = other.LastWriteTime;

    other.Size = 0;
    other.Attributes = 0;
    other.CreationTime = 0;
    other.LastReadTime = 0;
    other.LastWriteTime = 0;

    return *this;
}

File::~File()
{
}

bool File::operator<(const File &other) const
{
    // Compare the file names and store the comparaisons as integers (which will be either
    // 0 or 1).
    const std::string &thisFullPath = FullPath.String();
    const std::string &otherFullPath = other.FullPath.String();
    size_t comparisonLength = std::max<size_t>(thisFullPath.size(), otherFullPath.size()) + 1;

    int nameComparison = _strnicmp(thisFullPath.c_str(), otherFullPath.c_str(), comparisonLength);
    int thisNameGreaterThanOtherName = static_cast<int>(nameComparison > 0);
    int otherNameGreaterThanThisName = static_cast<int>(nameComparison < 0);

    // If the file is a directory, decrease the score by 2. The score is decreased because
    // the lower the score the closer the element will be to the start of the set and we
    // want directories to always be before files in sets.
    bool thisIsDirectory = (Attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
    bool otherIsDirectory = (other.Attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
    int thisScore = thisNameGreaterThanOtherName - static_cast<int>(thisIsDirectory * 2);
    int otherScore = otherNameGreaterThanThisName - static_cast<int>(otherIsDirectory * 2);

    return thisScore < otherScore;
}

static time_t FileTimeToTimet(const FILETIME &fileTime)
{
    uint64_t fileTimeAsUint64 =
        static_cast<uint64_t>(fileTime.dwHighDateTime) << 32 |
        static_cast<uint64_t>(fileTime.dwLowDateTime);

    return static_cast<time_t>(fileTimeAsUint64 / 10000000ULL - 11644473600ULL);
}

Optional<std::vector<File>> ReadDirectory(const Path &directoryPath)
{
    // We temporarily store the files in an std::set so that they are automatically sorted.
    // It starts with the directories in case-insensitive alphabetical order, than the
    // files in case-insensitive alphabetical order.
    std::set<File> files;

    // Check if directoryPath is a valid directory.
    // On Windows this wouldn't be needed because FindFirstFile would simply return
    // INVALID_HANDLE_VALUE and that would mean the directoryPath is not a valid directory.
    // On Xbox 360 FindFirstFile can also returrn INVALID_HANDLE_VALUE when the directory
    // is valid but empty, because there are no "." or ".." entries, so we need to make
    // a difference between the directory doesn't exist and it's empty.
    uint32_t attributes = GetFileAttributes(directoryPath.c_str());
    bool isDirectory = attributes != 0xFFFFFFFF && (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
    if (!isDirectory)
    {
        DebugPrint("[XexUtils][Fs]: Error: %s is not a valid directory.", directoryPath.c_str());
        return NullOpt();
    }

    // Initialize the search.
    Path searchPattern = directoryPath / "*";
    WIN32_FIND_DATA fileInfo = {};
    HANDLE handle = FindFirstFile(searchPattern.c_str(), &fileInfo);
    if (handle == nullptr || handle == INVALID_HANDLE_VALUE)
    {
        uint32_t error = GetLastError();

        // FindFirstFile sets the last error to ERROR_FILE_NOT_FOUND when the directory is
        // empty (cf. comment above).
        if (error == ERROR_FILE_NOT_FOUND)
            return std::vector<File>();

        DebugPrint(
            "[XexUtils][Fs]: Error: Couldn't find the first file in %s (%X).",
            directoryPath.c_str(),
            error
        );

        return NullOpt();
    }

    // Loop until no more files are found or an error occurs.
    do
    {
        File file;
        file.FullPath = directoryPath / fileInfo.cFileName;
        file.Size = static_cast<uint64_t>(fileInfo.nFileSizeHigh) << 32 | static_cast<uint64_t>(fileInfo.nFileSizeLow);
        file.Attributes = fileInfo.dwFileAttributes;
        file.CreationTime = FileTimeToTimet(fileInfo.ftCreationTime);
        file.LastReadTime = FileTimeToTimet(fileInfo.ftLastAccessTime);
        file.LastWriteTime = FileTimeToTimet(fileInfo.ftLastWriteTime);
        files.emplace(std::move(file));
    } while (FindNextFile(handle, &fileInfo));

    FindClose(handle);

    // If the search stopped for another reason than reaching the end of the directory,
    // then it's an actual error.
    uint32_t error = GetLastError();
    if (error != ERROR_NO_MORE_FILES)
    {
        DebugPrint(
            "[XexUtils][Fs]: Error: Couldn't finish reading the files in %s (%X).",
            directoryPath.c_str(),
            error
        );
        return NullOpt();
    }

    // Create a vector from the std::set.
    return std::vector<File>(files.begin(), files.end());
}

}
}
