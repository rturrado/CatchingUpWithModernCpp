#ifndef __HANDLE_H__
#define __HANDLE_H__

#include <windows.h>

class unique_hdl
{
public:
    unique_hdl(
        LPCWSTR lpFileName,
        DWORD dwDesiredAccess,
        DWORD dwShareMode,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        DWORD  dwCreationDisposition,
        DWORD  dwFlagsAndAttributes,
        HANDLE  hTemplateFile) noexcept;
    unique_hdl(const unique_hdl& other) noexcept;
    unique_hdl(unique_hdl&& other) noexcept;
    [[nodiscard]] unique_hdl& operator=(const unique_hdl& other) noexcept;
    [[nodiscard]] unique_hdl& operator=(unique_hdl&& other) noexcept;
    ~unique_hdl() noexcept;

    [[nodiscard]] explicit operator bool() noexcept;
    [[nodiscard]] HANDLE get() noexcept;
private:
    HANDLE hdl_{ INVALID_HANDLE_VALUE };
};

#endif
