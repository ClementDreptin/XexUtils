#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Filesystem()
{
    Describe("Fs::Path::Path()");

    It("creates an empty Path", []() {
        auto path = Fs::Path();

        TEST_EQ(path.Drive(), "");
        TEST_EQ(path.Basename(), "");
        TEST_EQ(path.Extension(), "");
        TEST_EQ(path.Filename(), "");
        TEST_EQ(path.Parent(), "");
        TEST_EQ(path.RelativePath(), "");
        TEST_EQ(path.IsRoot(), true);
        TEST_EQ(path.String(), "");
    });

    Describe("Fs::Path::Path(const std::string &)");

    It("creates a Path from an std::string", []() {
        std::string string("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path(string);

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "C:\\Windows\\System32\\Documents");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    Describe("Fs::Path::Path(std::string &&)");

    It("creates a Path from a moved std::string", []() {
        std::string string("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path(std::move(string));

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "C:\\Windows\\System32\\Documents");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(string.size(), 0);
    });

    Describe("Fs::Path::Path(const char *)");

    It("creates a Path from a const char *", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "C:\\Windows\\System32\\Documents");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    Describe("Fs::Path::Path(const Fs::Path &)");

    It("creates a Path from another Path", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path2(path1);

        TEST_EQ(path2.String(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    Describe("Fs::Path::Path(Fs::Path &&)");

    It("creates a Path from another moved Path", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path2(std::move(path1));

        TEST_EQ(path2.String(), "C:\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(path1.Size(), 0);
    });

    Describe("Fs::Path::operator=(const Fs::Path &)");

    It("assigns another Path to the current Path", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path2 = path1;

        TEST_EQ(path2.String(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    Describe("Fs::Path::operator=(Fs::Path &&)");

    It("assigns another moved Path to the current Path", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path2 = std::move(path1);

        TEST_EQ(path2.String(), "C:\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(path1.Size(), 0);
    });

    Describe("Fs::operator+(const T &, const Fs::Path &)");

    It("concatenates an std::string with a Path", []() {
        Fs::Path path("File.txt");
        Fs::Path newPath = "C:\\Windows\\System32" + path;

        TEST_EQ(newPath.Drive(), "C:");
        TEST_EQ(newPath.Basename(), "System32File");
        TEST_EQ(newPath.Extension(), ".txt");
        TEST_EQ(newPath.Filename(), "System32File.txt");
        TEST_EQ(newPath.Parent(), "C:\\Windows");
        TEST_EQ(newPath.RelativePath(), "\\Windows\\System32File.txt");
        TEST_EQ(newPath.IsRoot(), false);
        TEST_EQ(newPath.String(), "C:\\Windows\\System32File.txt");
    });

    Describe("Fs::operator+(const Fs::Path &, const T &)");

    It("concatenates a Path with an std::string", []() {
        Fs::Path path("C:\\Windows\\System32");
        Fs::Path newPath = path + "File.txt";

        TEST_EQ(newPath.Drive(), "C:");
        TEST_EQ(newPath.Basename(), "System32File");
        TEST_EQ(newPath.Extension(), ".txt");
        TEST_EQ(newPath.Filename(), "System32File.txt");
        TEST_EQ(newPath.Parent(), "C:\\Windows");
        TEST_EQ(newPath.RelativePath(), "\\Windows\\System32File.txt");
        TEST_EQ(newPath.IsRoot(), false);
        TEST_EQ(newPath.String(), "C:\\Windows\\System32File.txt");
    });

    Describe("Fs::operator<<(std::ostream &, const Fs::Path &)");

    It("writes the Path to the output stream", []() {
        std::ostringstream os;
        os << Fs::Path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(os.str(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    Describe("Fs::Path::operator/=(const Fs::Path &)");

    It("appends a Path with a leading separator to a Path without a trailing separator", []() {
        Fs::Path path("C:\\Windows\\System32");
        path /= "\\Documents\\File.txt";

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "C:\\Windows\\System32\\Documents");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    It("appends a Path without a leading separator to a Path without a trailing separator", []() {
        Fs::Path path("C:\\Windows\\System32");
        path /= "Documents\\File.txt";

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "C:\\Windows\\System32\\Documents");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    It("appends a Path with a leading separator to a Path with a trailing separator", []() {
        Fs::Path path("C:\\Windows\\System32\\");
        path /= "\\Documents\\File.txt";

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "C:\\Windows\\System32\\Documents");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    It("appends a Path without a leading separator to a Path with a trailing separator", []() {
        Fs::Path path("C:\\Windows\\System32\\");
        path /= "Documents\\File.txt";

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "C:\\Windows\\System32\\Documents");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    It("appends an empty Path to a Path without a trailing separator", []() {
        Fs::Path path("C:\\Windows\\System32");
        path /= "";

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "");
        TEST_EQ(path.Extension(), "");
        TEST_EQ(path.Filename(), "");
        TEST_EQ(path.Parent(), "C:\\Windows");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\");
    });

    It("appends an empty Path to a Path with a trailing separator", []() {
        Fs::Path path("C:\\Windows\\System32\\");
        path /= "";

        TEST_EQ(path.Drive(), "C:");
        TEST_EQ(path.Basename(), "");
        TEST_EQ(path.Extension(), "");
        TEST_EQ(path.Filename(), "");
        TEST_EQ(path.Parent(), "C:\\Windows");
        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "C:\\Windows\\System32\\");
    });

    It("appends a Path without a leading separator to an empty Path", []() {
        Fs::Path path("");
        path /= "Documents\\File.txt";

        TEST_EQ(path.Drive(), "");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "\\Documents");
        TEST_EQ(path.RelativePath(), "\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "\\Documents\\File.txt");
    });

    It("appends a Path with a leading separator to an empty Path", []() {
        Fs::Path path("");
        path /= "\\Documents\\File.txt";

        TEST_EQ(path.Drive(), "");
        TEST_EQ(path.Basename(), "File");
        TEST_EQ(path.Extension(), ".txt");
        TEST_EQ(path.Filename(), "File.txt");
        TEST_EQ(path.Parent(), "\\Documents");
        TEST_EQ(path.RelativePath(), "\\Documents\\File.txt");
        TEST_EQ(path.IsRoot(), false);
        TEST_EQ(path.String(), "\\Documents\\File.txt");
    });

    Describe("Fs::operator/(const Fs::Path &, const Fs::Path &)");

    It("creates a new Path from appending two other Paths", []() {
        Fs::Path path1("C:\\Windows\\System32");
        Fs::Path path2("Documents\\File.txt");
        Fs::Path path3 = path1 / path2;

        TEST_EQ(path3.Drive(), "C:");
        TEST_EQ(path3.Basename(), "File");
        TEST_EQ(path3.Extension(), ".txt");
        TEST_EQ(path3.Filename(), "File.txt");
        TEST_EQ(path3.Parent(), "C:\\Windows\\System32\\Documents");
        TEST_EQ(path3.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
        TEST_EQ(path3.IsRoot(), false);
        TEST_EQ(path3.String(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    Describe("Fs::operator==(const Fs::Path &, const Fs::Path &)");

    It("returns true when the two Paths are equal", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path2("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path1 == path2, true);
    });

    It("returns false when the two Paths are not equal", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path2("C:\\Windows\\System32\\Documents\\Other.txt");

        TEST_EQ(path1 == path2, false);
    });

    Describe("Fs::operator==(const T &, const Fs::Path &)");

    It("returns true when the std::string is equal to the Path", []() {
        std::string str1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(str1 == path1, true);
    });

    It("returns false when the std::string is not equal to the Path", []() {
        std::string str1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path1("C:\\Windows\\System32\\Documents\\Other.txt");

        TEST_EQ(str1 == path1, false);
    });

    Describe("Fs::operator==(const Fs::Path &, const T &)");

    It("returns true when the Path is equal to the std::string", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        std::string str1("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path1 == str1, true);
    });

    It("returns false when the Path is not equal to the std::string", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        std::string str1("C:\\Windows\\System32\\Documents\\Other.txt");

        TEST_EQ(path1 == str1, false);
    });

    Describe("Fs::operator!=(const Fs::Path &, const Fs::Path &)");

    It("returns true when the two Paths are not equal", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path2("Documents\\File.txt");

        TEST_EQ(path1 != path2, true);
    });

    It("returns false when the two Paths are equal", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path2("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path1 != path2, false);
    });

    Describe("Fs::operator!=(const T &, const Fs::Path &)");

    It("returns true when the std::string and the Path are not equal", []() {
        std::string str1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path1("Documents\\File.txt");

        TEST_EQ(str1 != path1, true);
    });

    It("returns false when the std::string and the Path are equal", []() {
        std::string str1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(str1 != path1, false);
    });

    Describe("Fs::operator!=(const Fs::Path &, const T &)");

    It("returns true when the Path and the std::string are not equal", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        std::string str1("Documents\\File.txt");

        TEST_EQ(path1 != str1, true);
    });

    It("returns false when the Path and the std::string are equal", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        std::string str1("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path1 != str1, false);
    });

    Describe("Fs::Path::String()");

    It("returns the full Path as an std::string", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.String(), "C:\\Windows\\System32\\Documents\\File.txt");
    });

    Describe("Fs::Path::Drive()");

    It("extracts the drive from a Path with a drive and a relative path", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Drive(), "C:");
    });

    It("extract the drive from a Path with just a drive", []() {
        Fs::Path path("C:");

        TEST_EQ(path.Drive(), "C:");
    });

    It("returns an empty Path when extracting the drive from a Path without a drive", []() {
        Fs::Path path("\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Drive(), "");
    });

    Describe("Fs::Path::Basename()");

    It("extracts the basename of a complete Path", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Basename(), "File");
    });

    It("extracts the basename of a Path with just a file", []() {
        Fs::Path path("File.txt");

        TEST_EQ(path.Basename(), "File");
    });

    It("returns an empty Path when extracting the basename of a Path with just a drive", []() {
        Fs::Path path("C:");

        TEST_EQ(path.Basename(), "");
    });

    It("extracts the basename of a Path with a file starting with a dot", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\.gitignore");

        TEST_EQ(path.Basename(), ".gitignore");
    });

    Describe("Fs::Path::Extension()");

    It("extracts the extension of a complete Path", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Extension(), ".txt");
    });

    It("returns an empty Path when extracting the extension of a file with no dot", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File");

        TEST_EQ(path.Extension(), "");
    });

    It("returns an empty Path when extracting the extension of a file starting with a dot", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\.gitignore");

        TEST_EQ(path.Extension(), "");
    });

    Describe("Fs::Path::Filename()");

    It("extracts the file name of a complete Path", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Filename(), "File.txt");
    });

    It("returns an empty Path when extracting the file name of a directory", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\");

        TEST_EQ(path.Filename(), "");
    });

    Describe("Fs::Path::Parent()");

    It("extracts the parent of a complete Path", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Parent(), "C:\\Windows\\System32\\Documents");
    });

    It("returns an empty Path when extracting the parent of an empty Path", []() {
        Fs::Path path("");

        TEST_EQ(path.Parent(), "");
    });

    It("returns the current Path when extracting the parent of a root Path", []() {
        Fs::Path path("C:\\");

        TEST_EQ(path.Parent(), "C:\\");
    });

    It("extracts the parent of a Path with a trailing separator", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\");

        TEST_EQ(path.Parent(), "C:\\Windows\\System32");
    });

    It("extracts the parent of a Path with a leading separator", []() {
        Fs::Path path("\\File.txt");

        TEST_EQ(path.Parent(), "\\");
    });

    It("extracts the parent of a Path with a drive and no separators", []() {
        Fs::Path path("C:File.txt");

        TEST_EQ(path.Parent(), "C:");
    });

    It("extracts the parent of a Path with a drive and a separator", []() {
        Fs::Path path("C:\\File.txt");

        TEST_EQ(path.Parent(), "C:\\");
    });

    It("returns an empty Path when extracting the parent of a Path with no separators", []() {
        Fs::Path path("File.txt");

        TEST_EQ(path.Parent(), "");
    });

    Describe("Fs::Path::RelativePath()");

    It("extracts the relative path of a complete Path", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
    });

    It("returns an empty path when extracting the relative path of a Path with just a drive", []() {
        Fs::Path path("C:");

        TEST_EQ(path.RelativePath(), "");
    });

    It("returns the current Path when extracting the relative path of a Path without a drive", []() {
        Fs::Path path("\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
    });

    Describe("Fs::Path::RelativePath()");

    It("considers a path with just a drive and a separator to be root", []() {
        Fs::Path path("C:\\");

        TEST_EQ(path.IsRoot(), true);
    });

    Describe("Fs::Path::IsEmpty()");

    It("returns true when the Path is empty", []() {
        Fs::Path path("");

        TEST_EQ(path.IsEmpty(), true);
    });

    It("returns false when the Path is not empty", []() {
        Fs::Path path("File.txt");

        TEST_EQ(path.IsEmpty(), false);
    });

    Describe("Fs::Path::IsRoot()");

    It("considers a Path with just a drive to be root", []() {
        Fs::Path path("C:");

        TEST_EQ(path.IsRoot(), true);
    });

    It("doesn't consider a Path with a drive and a file name to be root", []() {
        Fs::Path path("C:\\File.txt");

        TEST_EQ(path.IsRoot(), false);
    });

    It("doesn't consider a Path with a file name to be root", []() {
        Fs::Path path("File.txt");

        TEST_EQ(path.IsRoot(), false);
    });

    It("considers an empty Path to be root", []() {
        Fs::Path path("");

        TEST_EQ(path.IsRoot(), true);
    });

    It("considers a Path with just a separator to be root", []() {
        Fs::Path path("\\");

        TEST_EQ(path.IsRoot(), true);
    });

    It("doesn't consider a Path to a directory to be root", []() {
        Fs::Path path("\\Documents\\");

        TEST_EQ(path.IsRoot(), false);
    });

    Describe("Fs::Path::c_str()");

    It("returns the const char * of the underlying std::string", []() {
        Fs::Path path("File.txt");

        TEST_EQ(path.c_str(), path.String().c_str());
    });

    Describe("Fs::Path::Size()");

    It("returns the size of the Path", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Size(), 38);
    });

    Describe("Fs::MountPath(const std::string &, const std::string &)");

    It("allows a game to access the hard drive", []() {
        std::ifstream file("MyMount:\\DEVKIT\\XexUtilsTests\\Tests.xex");
        TEST_EQ(file.is_open(), false);

        Fs::MountPath("MyMount:", "\\Device\\Harddisk0\\Partition1\\");
        file.open("MyMount:\\DEVKIT\\XexUtilsTests\\Tests.xex");

        TEST_EQ(file.is_open(), true);
    });

    Describe("Fs::MountHdd()");

    It("allows a game to access the hard drive", []() {
        std::ifstream file("hdd:\\DEVKIT\\XexUtilsTests\\Tests.xex");
        TEST_EQ(file.is_open(), false);

        Fs::MountHdd();
        file.open("hdd:\\DEVKIT\\XexUtilsTests\\Tests.xex");

        TEST_EQ(file.is_open(), true);
    });

    Describe("Fs::UnmountPath(const std::string &)");

    It("removes the MyMount: symbolic link previously created with MountPath", []() {
        Fs::MountPath("MyMount:", "\\Device\\Harddisk0\\Partition1\\");
        std::ifstream file("MyMount:\\DEVKIT\\XexUtilsTests\\Tests.xex");
        TEST_EQ(file.is_open(), true);

        file.close();
        Fs::UnmountPath("MyMount:");
        file.open("MyMount:\\DEVKIT\\XexUtilsTests\\Tests.xex");

        TEST_EQ(file.is_open(), false);
    });

    Describe("Fs::UnmountHdd()");

    It("removes the hdd: symbolic link previously created with MountHdd", []() {
        Fs::MountHdd();
        std::ifstream file("hdd:\\DEVKIT\\XexUtilsTests\\Tests.xex");
        TEST_EQ(file.is_open(), true);

        file.close();
        Fs::UnmountHdd();
        file.open("hdd:\\DEVKIT\\XexUtilsTests\\Tests.xex");

        TEST_EQ(file.is_open(), false);
    });

    Describe("Fs::File::File()");

    It("creates an empty File", []() {
        auto file = Fs::File();

        TEST_EQ(file.Name, "");
        TEST_EQ(file.Size, 0);
        TEST_EQ(file.Attributes, 0);
        TEST_EQ(file.CreationTime, 0);
        TEST_EQ(file.LastReadTime, 0);
        TEST_EQ(file.LastWriteTime, 0);
    });

    Describe("Fs::File::File(const Fs::File &)");

    It("creates a File from another File", []() {
        Fs::File file;
        file.Name = "file.txt";
        file.Size = 3;
        file.Attributes = FILE_ATTRIBUTE_NORMAL;
        file.CreationTime = 123;
        file.LastReadTime = 456;
        file.LastWriteTime = 789;
        Fs::File copy(file);

        TEST_EQ(copy.Name, "file.txt");
        TEST_EQ(copy.Size, 3);
        TEST_EQ(copy.Attributes, FILE_ATTRIBUTE_NORMAL);
        TEST_EQ(copy.CreationTime, 123);
        TEST_EQ(copy.LastReadTime, 456);
        TEST_EQ(copy.LastWriteTime, 789);
    });

    Describe("Fs::File::File(Fs::File &&)");

    It("creates a File from another moved File", []() {
        Fs::File file;
        file.Name = "file.txt";
        file.Size = 3;
        file.Attributes = FILE_ATTRIBUTE_NORMAL;
        file.CreationTime = 123;
        file.LastReadTime = 456;
        file.LastWriteTime = 789;
        Fs::File copy(std::move(file));

        TEST_EQ(copy.Name, "file.txt");
        TEST_EQ(copy.Size, 3);
        TEST_EQ(copy.Attributes, FILE_ATTRIBUTE_NORMAL);
        TEST_EQ(copy.CreationTime, 123);
        TEST_EQ(copy.LastReadTime, 456);
        TEST_EQ(copy.LastWriteTime, 789);

        TEST_EQ(file.Name, "");
        TEST_EQ(file.Size, 0);
        TEST_EQ(file.Attributes, 0);
        TEST_EQ(file.CreationTime, 0);
        TEST_EQ(file.LastReadTime, 0);
        TEST_EQ(file.LastWriteTime, 0);
    });

    Describe("Fs::File::operator=(const Fs::File &)");

    It("creates a File from another File", []() {
        Fs::File file;
        file.Name = "file.txt";
        file.Size = 3;
        file.Attributes = FILE_ATTRIBUTE_NORMAL;
        file.CreationTime = 123;
        file.LastReadTime = 456;
        file.LastWriteTime = 789;
        Fs::File copy = file;

        TEST_EQ(copy.Name, "file.txt");
        TEST_EQ(copy.Size, 3);
        TEST_EQ(copy.Attributes, FILE_ATTRIBUTE_NORMAL);
        TEST_EQ(copy.CreationTime, 123);
        TEST_EQ(copy.LastReadTime, 456);
        TEST_EQ(copy.LastWriteTime, 789);
    });

    Describe("Fs::File::operator=(Fs::File &&)");

    It("creates a File from another moved File", []() {
        Fs::File file;
        file.Name = "file.txt";
        file.Size = 3;
        file.Attributes = FILE_ATTRIBUTE_NORMAL;
        file.CreationTime = 123;
        file.LastReadTime = 456;
        file.LastWriteTime = 789;
        Fs::File copy = std::move(file);

        TEST_EQ(copy.Name, "file.txt");
        TEST_EQ(copy.Size, 3);
        TEST_EQ(copy.Attributes, FILE_ATTRIBUTE_NORMAL);
        TEST_EQ(copy.CreationTime, 123);
        TEST_EQ(copy.LastReadTime, 456);
        TEST_EQ(copy.LastWriteTime, 789);

        TEST_EQ(file.Name, "");
        TEST_EQ(file.Size, 0);
        TEST_EQ(file.Attributes, 0);
        TEST_EQ(file.CreationTime, 0);
        TEST_EQ(file.LastReadTime, 0);
        TEST_EQ(file.LastWriteTime, 0);
    });

    Describe("Fs::File::operator<(const Fs::File &)");

    It("sorts Files in case-insensitive alphabetical order", []() {
        Fs::File first;
        first.Name = "DirB";
        Fs::File second;
        second.Name = "dirA";

        std::set<Fs::File> files;
        files.insert(first);
        files.insert(second);

        auto it = files.begin();
        TEST_EQ(it->Name, "dirA");
        TEST_EQ((++it)->Name, "DirB");
    });

    It("puts directories before normal files", []() {
        Fs::File first;
        first.Name = "B.txt";
        first.Attributes = FILE_ATTRIBUTE_NORMAL;
        Fs::File second;
        second.Name = "a.txt";
        second.Attributes = FILE_ATTRIBUTE_NORMAL;
        Fs::File third;
        third.Name = "DirB";
        third.Attributes = FILE_ATTRIBUTE_DIRECTORY;
        Fs::File fourth;
        fourth.Name = "dirA";
        fourth.Attributes = FILE_ATTRIBUTE_DIRECTORY;

        std::set<Fs::File> files;
        files.insert(first);
        files.insert(second);
        files.insert(third);
        files.insert(fourth);

        auto it = files.begin();
        TEST_EQ(it->Name, "dirA");
        TEST_EQ((++it)->Name, "DirB");
        TEST_EQ((++it)->Name, "a.txt");
        TEST_EQ((++it)->Name, "B.txt");
    });

    It("sorts a name that is a prefix of another name before it", []() {
        Fs::File first;
        first.Name = "file.txt";
        Fs::File second;
        second.Name = "file";

        std::set<Fs::File> files;
        files.insert(first);
        files.insert(second);

        auto it = files.begin();
        TEST_EQ(it->Name, "file");
        TEST_EQ((++it)->Name, "file.txt");
    });

    Describe("Fs::ReadDirectory(const Fs::Path &)");

    It("returns a vector of Files in a directory", []() {
        auto files = Fs::ReadDirectory("game:\\fixtures\\filesystem");

        TEST_EQ(files.HasValue(), true);
        TEST_EQ(files->size(), 5);
        TEST_EQ((*files)[0].Name, "dirA");
        TEST_EQ((*files)[1].Name, "DirB");
        TEST_EQ((*files)[2].Name, "empty-dir");
        TEST_EQ((*files)[3].Name, "a.txt");
        TEST_EQ((*files)[4].Name, "B.txt");
    });

    It("returns an empty vector when the directory is empty", []() {
        auto files = Fs::ReadDirectory("game:\\fixtures\\filesystem\\empty-dir");

        TEST_EQ(files.HasValue(), true);
        TEST_EQ(files->size(), 0);
    });

    It("returns NullOpt when the directory path doesn't exist", []() {
        auto files = Fs::ReadDirectory("game:\\inexistant");

        TEST_EQ(files.HasValue(), false);
    });

    It("returns NullOpt when the path isn't a path to a directory", []() {
        auto files = Fs::ReadDirectory("game:\\fixtures\\filesystem\\file1.txt");

        TEST_EQ(files.HasValue(), false);
    });
}
