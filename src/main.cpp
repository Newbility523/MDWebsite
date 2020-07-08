#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <sys/io.h>
#include <regex>
#include <fstream>
#include <string>
#include <dirent.h>
#include "WebUpdate.h"

using namespace std;
using namespace std::filesystem;

// config
const char* srcDir = "/home/carl/Note";
// const char* srcDir = "/home/carl/test";
const char* targetDir = "/home/carl/WebOutput";
const char* cmdFormat = "showdown makehtml -i %s -o %s";
const string cssPathStr = "config/css/github-markdown.css";
const char* templatePath = "config/Template.html";
regex cssRegex("<!-- cssPath -->");
regex bodyRegex("<!-- body -->");

// global
string htmlTemplate;
string cssPath;
string cssName = "github-markdown.css";

int Init()
{
    /* cout << htmlPath.parent_path() << endl;
     cout << absolute(htmlPath) << endl;*/
    string htmlPath = absolute(templatePath).string();
    if (!exists(htmlPath))
    {
        cout << "template not exists" << endl;
        return -1;
    }

    cssPath = absolute(cssPathStr).string();
    if (!exists(cssPath))
    {
        cout << "css not exists" << endl;
        return -1;
    }

    path oriCssPath(cssPath);
    string targetStr = targetDir;
    cssPath = targetStr + "/" + oriCssPath.filename().string();
    ifstream ifileStream;
    ifileStream.open(htmlPath, ios::out);
    int length;
    ifileStream.seekg(0, ios::end);
    length = ifileStream.tellg();
    char* buffer = new char[length + 1];
    ifileStream.seekg(0, ios::beg);
    ifileStream.read(buffer, length);
    buffer[length] = '\0';
    ifileStream.close();

    htmlTemplate = buffer;
    cout << htmlTemplate << endl;
    cout << cssPath << endl;

    return 0;
}

string GetCssPath(path filePath)
{
    string fullPath = filePath.string();
    int index = fullPath.find(targetDir);
    // cout << "checking " << fullPath << endl;
    // cout << "find " << targetDir << endl;

    string result = "";
    if (index != -1)
    {
        // cout << "index " << index << endl;
        for (int i = index + strlen(targetDir) + 1; i < fullPath.length(); ++i)
        {
            if (fullPath[i] == '/')
            {
                result = "../" + result;
            }
        }

        result = result + cssName;
    }
    else
    {
       result = cssPath;
    }

    // cout << "result " << result << endl;

    return result;
}

string FormatHtml(const char* buffer, path filePath)
{
    string relateCssPath = GetCssPath(filePath);
    string result = regex_replace(htmlTemplate, cssRegex, relateCssPath);
    result = regex_replace(result, bodyRegex, buffer);

    return result;
}


int CMDRunder(const char* cmd, char* result)
{
    char buffer[128];
    FILE* pipe = popen(cmd, "r");
    if (!pipe)
    {
        return 0;
    }

    while (!feof(pipe))
    {
        if (fgets(buffer, 128, pipe))
        {
            strcat(result, buffer);
        }
    }

    pclose(pipe);

    return 1;
}

string ConvertPath(const char* buffer)
{
    //<p><a href="other/OtherMD.md#third">To other</a></p>
    regex reg("(<a href=\".*?)\\.md(.*?\">)");
    string newStr = regex_replace(buffer, reg, "$1.html$2");
    return newStr;
}

void CreateCatalogue(vector<string> filePaths)
{
    string catalogueStr = u8"# Catalogue \n\n";
    const char* fmt = "* [%s](%s)\n";
    for (vector<string>::const_iterator iter = filePaths.begin(); iter != filePaths.end(); ++iter)
    {
        path path(*iter);
        if (path.extension() == ".md")
        {
            char item[100] = "";
            //path.replace_extension();
            string fullPath = path.u8string();
            //string relative = "E:\\Note\\";
            string temp = srcDir;
            string relative = temp + "/";
            fullPath = fullPath.substr(relative.length(), fullPath.length());
            snprintf(item, sizeof(item), fmt, path.stem().u8string().c_str(), fullPath.c_str());
            catalogueStr = catalogueStr + item;
        }
    }

    cout << "catalogueStr: " << catalogueStr << endl;

    string fileStr = string(srcDir) + "/Catalogue.md";
    path catalogueInfoPath(fileStr);
    fstream fstream;
    fstream.open(fileStr, ios::trunc | ios::out);
    if (fstream.good())
    {
        fstream.seekp(0, ios::beg);
        fstream.write(catalogueStr.c_str(), catalogueStr.length());
        fstream.close();

        FileInfo catalogueInfo(catalogueInfoPath.parent_path().string().c_str(), catalogueInfoPath.filename().string().c_str());
        filePaths.push_back(fileStr);
    }
    else
    {
        cout << "bad" << endl;
    }
}

void CopyStyleFile()
{
    path oriCssPath(cssPathStr);
    path newCssPaht(cssPath);

    copy(oriCssPath, newCssPaht);
}

int ClearTargetDirectory(const char* targetDir)
{
    path targetPath(targetDir);
    if (!exists(targetPath))
    {
        create_directories(targetPath);
    }

    cout << "Are you sure remove all files in " << targetPath.string() << " ? (y/Y to continue) : ";
    char isClear = getchar();
    if (isClear == 'y' || isClear == 'Y')
    {
        cout << "\nAsk permission success." << endl;
        int count = remove_all(targetPath);
        cout << "Delete count: " << count << endl;
    }
    else
    {
        cout << "\nAsk permission fail, return." << endl;
        return -1;
    }

    return 0;
}

int FileFactor(path filePath)
{
    string path = absolute(filePath).string();

    ifstream ifileStream;
    ifileStream.open(path, ios::out);
    int length;
    ifileStream.seekg(0, ios::end);
    length = ifileStream.tellg();
    char* buffer = new char[length + 1];
    ifileStream.seekg(0, ios::beg);
    ifileStream.read(buffer, length);
    buffer[length] = '\0';
    ifileStream.close();

    string raw = buffer;
    raw = ConvertPath(raw.c_str());
    raw = FormatHtml(raw.c_str(), filePath);

    const char* newBuffer = raw.c_str();

    ofstream ofileStream;
    ofileStream.open(path, ios::trunc | ios::in);
    ofileStream.write(newBuffer, strlen(newBuffer));
    //cout << "new buffer: " << newBuffer << endl;
    ofileStream.close();

    return 0;
}

int main()
{
    Init();
    Updater updater = Updater();
    updater.CreateCatalog(srcDir);
    // updater.DisplayVectorStr();

    vector<string> infos = updater.GetFilePaths();

    CreateCatalogue(infos);

    if (ClearTargetDirectory(targetDir) == -1)
    {
        return 0;
    }

    for (vector<string>::const_iterator iter = infos.begin(); iter != infos.end(); ++iter)
    {
        string oriFilePath = *iter;

        char srcFullPath[300] = "";
        // info.FullPath(srcFullPath);
        path srcPath(oriFilePath);

        string desPathStr = srcPath.string();
        desPathStr = desPathStr.substr(strlen(srcDir), desPathStr.length());
        desPathStr = targetDir + desPathStr;
        cout << desPathStr << endl;
        path desPath(desPathStr);

        if (!exists(desPath.parent_path()))
        {
            create_directories(desPath.parent_path());
        }

        if (srcPath.extension() == ".md")
        {
            desPath.replace_extension(".html");

            char cmd[300] = "";
            snprintf(cmd, 200, cmdFormat, srcPath.string().c_str(), desPath.string().c_str());
            cout << cmd << endl;

            char result[1024 * 4] = "";
            if (CMDRunder(cmd, result) == 1)
            {
                cout << "running : " << cmd << endl;
            }

            FileFactor(desPath);
        }
        else
        {
            cout << "copying file : " << desPath.filename() << endl;
            copy(srcPath, desPath);
        }
    }

    CopyStyleFile();

    return 0;
}