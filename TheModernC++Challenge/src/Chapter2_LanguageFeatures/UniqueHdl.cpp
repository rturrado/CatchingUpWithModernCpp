#include "UniqueHdl.h"

#include <windows.h>

// Opens the Windows file handle, if possible
unique_hdl::unique_hdl(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD  dwCreationDisposition,
    DWORD  dwFlagsAndAttributes,
    HANDLE  hTemplateFile) noexcept
{
    hdl_ = CreateFileW(
        lpFileName,
        dwDesiredAccess,
        dwShareMode,
        lpSecurityAttributes,
        dwCreationDisposition,
        dwFlagsAndAttributes,
        hTemplateFile);
}

unique_hdl::unique_hdl(const unique_hdl& other) noexcept
    : hdl_{ other.hdl_ }
{
    // Do nothing
}

unique_hdl::unique_hdl(unique_hdl&& other) noexcept
    : hdl_{ other.hdl_ }
{
    other.hdl_ = INVALID_HANDLE_VALUE;
}

[[nodiscard]] unique_hdl& unique_hdl::operator=(const unique_hdl& other) noexcept
{
    hdl_ = other.hdl_;
    return *this;
}

[[nodiscard]] unique_hdl& unique_hdl::operator=(unique_hdl&& other) noexcept
{
    hdl_ = other.hdl_;
    other.hdl_ = INVALID_HANDLE_VALUE;
    return *this;
}

unique_hdl::~unique_hdl() noexcept
{
    if (hdl_ != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hdl_);
    }
}

[[nodiscard]] unique_hdl::operator bool() noexcept
{
    return hdl_ != INVALID_HANDLE_VALUE;
}

[[nodiscard]] HANDLE unique_hdl::get() noexcept
{
    return hdl_;
}
