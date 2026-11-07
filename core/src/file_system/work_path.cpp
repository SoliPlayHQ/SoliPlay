#include <file_system/work_path.h>
#include <tool_functions/path_tools.h>
#include <log_system.h>
#include <filesystem>

#include <windows.h>
#include <shlobj.h>

namespace SPFile {
    static std::string excute_path;
    static std::string write_path;

    // 初始化工作目录
    void initWorkPath(void) {
        // 获取执行目录
#ifdef _WIN32
        wchar_t path[MAX_PATH];
        DWORD len = GetModuleFileNameW(NULL, path, MAX_PATH);
        excute_path = SPTool::PathToChar(std::filesystem::path(path).parent_path());
        SPLog::info("Get Excution Directory Path: " + excute_path);

        PWSTR pszPath = nullptr;
        HRESULT hResult = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &pszPath);
        if (SUCCEEDED(hResult)) {
            std::filesystem::path pAppdata(pszPath);
            pAppdata /= "SoliPlay";
            CoTaskMemFree(pszPath);

            std::error_code ec;
            std::filesystem::create_directories(pAppdata, ec);
            if (ec) {
                SPLog::fatal("Can't Create Safety Directory!");
                throw std::runtime_error("Can't Create Safety Directory: " + ec.message());
            }

            write_path = SPTool::PathToChar(pAppdata);
        }
        else {
            SPLog::fatal("Can't Get Safety Directory!");
            write_path = excute_path;
        }
        SPLog::info("Get Safety Directory Path: " + write_path);
#endif
    }

    // 获取执行目录，一般为程序根目录
    std::string getExcutePath(void) {
        return excute_path;
    }

    // 获取写入目录，一般为可写入的安全目录
    std::string getWritePath(void) {
        return write_path;
    }
}