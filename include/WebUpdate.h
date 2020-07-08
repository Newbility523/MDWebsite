#include <iostream>
#include <vector>
#include <cstring>
#include <filesystem>
#include <sys/io.h>

using namespace std;
// using namespace std::filesystem;

struct FileInfo {
    char dir[100] = "";
    char name[100] = "";
    char extend[10] = "";

    FileInfo(const char* directory, const char* fullName)
    {
        strcpy(dir, directory);
        const char* ext = strrchr(fullName, '.');
        strcpy(extend, ext);
        strncpy(name, fullName, strlen(fullName) - strlen(ext));
    }

    void FullName(char* buffer)
    {
        strcpy(buffer, name);
        strcat(buffer, extend);
    }

    void FullPath(char* buffer)
    {
        strcpy(buffer, dir);
        strcat(buffer, "\\");
        strcat(buffer, name);
        strcat(buffer, extend);
    }
};

class Updater
{
private:
    vector<FileInfo>* paths;
    vector<string> filePaths;
public:
    Updater()
    {
        paths = new vector<FileInfo>();
        filePaths = vector<string>();
    }

    void CreateCatalog(string dir)
    {
        DIR* handle = opendir(dir.c_str());

        if (handle == NULL)
        {
            return;
        }

        dirent* info = readdir(handle);
        while (info != NULL)
        {
            unsigned char type = info->d_type;
            string name = info->d_name;
            string filePath = dir + "/" + name;
            if (type == DT_DIR)
            {
                if (name != "." && name != "..")
                {
                    CreateCatalog(filePath);
                }
            }
            else if(type == DT_REG)
            {
                filePaths.push_back(filePath);
            }

            info = readdir(handle);
        }

        closedir(handle);
    }

    void DisplayVectorStr()
    {
        for (int i = 0; i < filePaths.size(); ++i)
        {
            cout << filePaths[i] << endl;
        }
    }

    FileInfo GetOne()
    {
        return (*paths)[0];
    }

    vector<string> GetFilePaths()
    {
        return filePaths;
    }
};
