// Copyright (c) 2015, Shaheed Abdol
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef _UTIL_H_
#define _UTIL_H_
#include <Windows.h>

namespace util {
static void GetQualifiedPath(const std::string &relativePath,
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