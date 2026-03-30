#include <fstream>
#include <XexUtils.h>

#include "../TestRunner.h"

using namespace XexUtils;
using namespace TestRunner;

void Filesystem()
{
    Describe("Fs::MountHdd");

    It("allows a game to access the hard drive", []() {
        std::ifstream file("hdd:\\launch.ini");
        TEST_EQ(file.is_open(), false);

        Fs::MountHdd();
        file.open("hdd:\\launch.ini");

        TEST_EQ(file.is_open(), true);
    });

    It("removes the hdd: symbolic link previously created with MountHdd", []() {
        Fs::MountHdd();
        std::ifstream file("hdd:\\launch.ini");
        TEST_EQ(file.is_open(), true);

        file.close();
        Fs::UnmountHdd();
        file.open("hdd:\\launch.ini");

        TEST_EQ(file.is_open(), false);
    });

    Describe("Fs::Path");

    It("concatenates an std::string with a path", []() {
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

    It("concatenates a path with an std::string", []() {
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

    It("appends a path with a leading separator to a path without a trailing separator", []() {
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

    It("appends a path without a leading separator to a path without a trailing separator", []() {
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

    It("appends a path with a leading separator to a path with a trailing separator", []() {
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

    It("appends a path without a leading separator to a path with a trailing separator", []() {
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

    It("appends an empty path to a path without a trailing separator", []() {
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

    It("appends an empty path to a path with a trailing separator", []() {
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

    It("appends a path without a leading separator to an empty path", []() {
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

    It("appends a path with a leading separator to an empty path", []() {
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

    It("checks equality on two paths", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path2("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path1 == path2, true);
    });

    It("checks equality on an std::string and a path", []() {
        std::string str1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(str1 == path1, true);
    });

    It("checks equality on a path and an std::string", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        std::string str1("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path1 == str1, true);
    });

    It("checks inequality on two paths", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path2("Documents\\File.txt");

        TEST_EQ(path1 != path2, true);
    });

    It("checks inequality on an std::string and a path", []() {
        std::string str1("C:\\Windows\\System32\\Documents\\File.txt");
        Fs::Path path1("Documents\\File.txt");

        TEST_EQ(str1 != path1, true);
    });

    It("checks inequality on a path and an std::string", []() {
        Fs::Path path1("C:\\Windows\\System32\\Documents\\File.txt");
        std::string str1("Documents\\File.txt");

        TEST_EQ(path1 != str1, true);
    });

    It("extracts the drive from a path with a drive and a relative path", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Drive(), "C:");
    });

    It("extract the drive from a path with just a drive", []() {
        Fs::Path path("C:");

        TEST_EQ(path.Drive(), "C:");
    });

    It("returns an empty path when extracting the drive from a path without a drive", []() {
        Fs::Path path("\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Drive(), "");
    });

    It("extracts the basename of a complete path", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Basename(), "File");
    });

    It("extracts the basename of a path with just a file", []() {
        Fs::Path path("File.txt");

        TEST_EQ(path.Basename(), "File");
    });

    It("returns an empty path when extracting the basename of a path with just a drive", []() {
        Fs::Path path("C:");

        TEST_EQ(path.Basename(), "");
    });

    It("extracts the basename of a path with a file starting with a dot", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\.gitignore");

        TEST_EQ(path.Basename(), ".gitignore");
    });

    It("extracts the extension of a complete path", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Extension(), ".txt");
    });

    It("returns an empty path when extracting the extension of a file with no dot", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File");

        TEST_EQ(path.Extension(), "");
    });

    It("returns an empty path when extracting the extension of a file starting with a dot", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\.gitignore");

        TEST_EQ(path.Extension(), "");
    });

    It("extracts the file name of a complete path", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Filename(), "File.txt");
    });

    It("extracts the parent of a complete path", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.Parent(), "C:\\Windows\\System32\\Documents");
    });

    It("returns an empty path when extracting the parent of an empty path", []() {
        Fs::Path path("");

        TEST_EQ(path.Parent(), "");
    });

    It("returns the current path when extracting the parent of a root path", []() {
        Fs::Path path("C:\\");

        TEST_EQ(path.Parent(), "C:\\");
    });

    It("extracts the parent of a path with a trailing separator", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\");

        TEST_EQ(path.Parent(), "C:\\Windows\\System32");
    });

    It("extracts the parent of a path with a leading separator", []() {
        Fs::Path path("\\File.txt");

        TEST_EQ(path.Parent(), "\\");
    });

    It("extracts the parent of a path with a drive and no separators", []() {
        Fs::Path path("C:File.txt");

        TEST_EQ(path.Parent(), "C:");
    });

    It("returns an empty path when extracting the parent of a parent with no separators", []() {
        Fs::Path path("File.txt");

        TEST_EQ(path.Parent(), "");
    });

    It("extracts the relative path of a complete path", []() {
        Fs::Path path("C:\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
    });

    It("returns an empty path when extracting the relative path of a path with just a drive", []() {
        Fs::Path path("C:");

        TEST_EQ(path.RelativePath(), "");
    });

    It("returns the current path when extracting the relative path of a path without a drive", []() {
        Fs::Path path("\\Windows\\System32\\Documents\\File.txt");

        TEST_EQ(path.RelativePath(), "\\Windows\\System32\\Documents\\File.txt");
    });

    It("considers a path with just a drive and a separator to be root", []() {
        Fs::Path path("C:\\");

        TEST_EQ(path.IsRoot(), true);
    });

    It("considers a path with just a drive to be root", []() {
        Fs::Path path("C:");

        TEST_EQ(path.IsRoot(), true);
    });

    It("doesn't consider a path with a drive and a file name to be root", []() {
        Fs::Path path("C:\\File.txt");

        TEST_EQ(path.IsRoot(), false);
    });

    It("doesn't consider a path with a file name to be root", []() {
        Fs::Path path("File.txt");

        TEST_EQ(path.IsRoot(), false);
    });

    It("considers an empty path to be root", []() {
        Fs::Path path("");

        TEST_EQ(path.IsRoot(), true);
    });

    It("considers a path with just a separator to be root", []() {
        Fs::Path path("\\");

        TEST_EQ(path.IsRoot(), true);
    });

    It("doesn't consider a path to a directory to be root", []() {
        Fs::Path path("\\Documents\\");

        TEST_EQ(path.IsRoot(), false);
    });
}
