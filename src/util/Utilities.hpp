#ifndef _UTIL_H_
#define _UTIL_H_
#include <Windows.h>

namespace util {
void GetQualifiedPath(const std::string &relativePath,
                             std::string *fullPath) {
  HMODULE module = GetModuleHandle(NULL);
  CHAR buffer[MAX_PATH];
  DWORD charsCopied = GetModuleFileName(module, buffer, MAX_PATH);
  if (charsCopied) {
    // This now contains the full path to the executable.
    std::string buf(buffer, charsCopied);

    size_t idx = buf.find_last_of('\\');
    buf = buf.substr(0, idx + 1);
    buf.append(relativePath);
    *fullPath = buf;
  }
}

} // namespace util

#endif // _UTIL_H_