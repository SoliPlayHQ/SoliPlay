#include <tool_functions/path_tools.h>
#include <tool_functions/string_tools.h>

// [?] 只进行过部分实机可行性测试

namespace SPTool {
    std::string PathtoChar(const std::filesystem::path& path) {
#ifdef _WIN32
        return WidetoChar(path.wstring());
#else
        return path.string();
#endif
    }
}