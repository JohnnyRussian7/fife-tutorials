
#include "IFileSystem.h"
#include "FileSystem.h"

IFileSystem* CreateFileSystem(const FileSystemSettings& settings)
{
    return new FileSystem(settings);
}