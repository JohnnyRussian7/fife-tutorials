
#ifndef IFILE_SYSTEM_H_
#define IFILE_SYSTEM_H_

struct FileSystemSettings
{
    FileSystemSettings()
    {

    }

};

class IFileSystem
{
public:
    virtual ~IFileSystem() { };
};

IFileSystem* CreateFileSystem(const FileSystemSettings& settings);

#endif