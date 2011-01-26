
#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_

#include "IFileSystem.h"

class FileSystem : public IFileSystem
{
public:
    FileSystem(const FileSystemSettings& settings);
    ~FileSystem();

private:
    FileSystemSettings m_settings;
};

#endif
