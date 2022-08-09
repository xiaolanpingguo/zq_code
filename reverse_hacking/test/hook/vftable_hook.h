#pragma once


#include <Windows.h>
#include <cassert>


/*
    how to use:
    VfTableHook vfTableHook;
    vfTableHook.init(class_obj);
    m_original = vfTableHook.hookFunction(hooked, vftable_index);
*/

bool isCodePtr(void* ptr)
{
    constexpr static DWORD protectFlags = PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;
    MEMORY_BASIC_INFORMATION out;
    ::VirtualQuery(ptr, &out, sizeof out);
    return out.Type && !(out.Protect & (PAGE_GUARD | PAGE_NOACCESS)) && out.Protect & protectFlags;
}

class VfTableHook
{
public:
    VfTableHook()
        : m_newVmt{ nullptr }
        , m_oldVmt{ nullptr }
    {
    }

    ~VfTableHook()
    {
        if (m_newVmt)
        {
            delete[](m_newVmt - 1);
            m_newVmt = nullptr;
        }
    }

    bool init(void* obj)
    {
        void** vtbl = *reinterpret_cast<void***>(obj);
        if (m_oldVmt == nullptr)
        {
            copyToNewVfTable(vtbl);
        }

        hook(obj);
        return true;
    }

    void unhook(void* obj) const
    {
        void**& vtbl = *reinterpret_cast<void***>(obj);
        assert(vtbl == m_oldVmt || vtbl == m_newVmt);
        vtbl = m_oldVmt;
    }

    template <typename Fn>
    Fn hookFunction(Fn hookedFn, const std::size_t index)
    {
        m_newVmt[index] = (void*)(hookedFn);
        return (Fn)(m_oldVmt[index]);
    }

    template <typename Fn = std::uintptr_t>
    Fn getOriginalFunction(const std::size_t index) { return (Fn)(m_oldVmt[index]); }

private:
    void copyToNewVfTable(void** originalTable)
    {
        m_oldVmt = originalTable;

        std::size_t size = 0;
        while (m_oldVmt[size] && isCodePtr(m_oldVmt[size]))
        {
            ++size;
        }

        // m_oldVmt - 1: RTTI
        m_newVmt = new void* [size + 1] + 1;
        auto p = m_oldVmt - 1;
        memcpy(m_newVmt - 1, m_oldVmt - 1, sizeof(void*) * (size + 1));
    }

    void hook(void* obj) const
    {
        void**& vtbl = *reinterpret_cast<void***>(obj);
        assert(vtbl == m_oldVmt || vtbl == m_newVmt);
        vtbl = m_newVmt;
    }

private:
    void** m_newVmt;
    void** m_oldVmt;
};