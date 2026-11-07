#include <tool_functions/path_tools.h>
#include <tool_functions/string_tools.h>

namespace SPTool {
    std::string PathToChar(const std::filesystem::path& path) {
#ifdef _WIN32
        return WidetoChar(path.wstring());
#else
        return path.string();
#endif
    }
}