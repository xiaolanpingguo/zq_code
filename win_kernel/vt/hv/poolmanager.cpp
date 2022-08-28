#include <intrin.h>
#include "poolmanager.h"
#include "common.h"
#include "log.h"
#include "allocators.h"

namespace PoolManager 
{
    /// <summary>
    /// Allocate pools and add them to pool table
    /// </summary>
    /// <param name="size">Size of pool</param>
    /// <param name="count">Number of pools to allocate</param>
    /// <param name="intention"></param>
    /// <returns></returns>
    static bool _allocatePool(unsigned __int64 size, unsigned __int32 count, allocation_intention intention)
    {
        for (unsigned int i = 0; i < count; i++)
        {
            __pool_table* single_pool = ::allocatePool<__pool_table>();
            if (single_pool == nullptr)
            {
                LOG_ERROR("Memory allocation failed");
                return false;
            }
            RtlSecureZeroMemory(single_pool, sizeof(__pool_table));

            single_pool->address = ::allocatePool<void*>(size);
            if (single_pool->address == nullptr)
            {
                LOG_ERROR("Memory allocation failed");
                return false;
            }
            RtlSecureZeroMemory((void*)single_pool->address, size);

            single_pool->intention = intention;
            single_pool->is_busy = false;
            single_pool->size = size;

            InsertTailList(g_vmm_context->pool_manager->list_of_allocated_pools, &(single_pool->pool_list));
        }

        return true;
    }

    bool requestAllocation(unsigned __int64 size, unsigned __int32 count, allocation_intention intention)
    {
        spinlock::lock(&g_vmm_context->pool_manager->lock_for_request_allocation);

        for (int i = 0; i < 10; i++)
        {
            if (g_vmm_context->pool_manager->allocation_requests->size[i] == 0)
            {
                g_vmm_context->pool_manager->allocation_requests->count[i] = count;
                g_vmm_context->pool_manager->allocation_requests->size[i] = size;
                g_vmm_context->pool_manager->allocation_requests->intention[i] = intention;
                g_vmm_context->pool_manager->is_request_for_allocation_recived = true;
                break;
            }
        }

        spinlock::unlock(&g_vmm_context->pool_manager->lock_for_request_allocation);
        return g_vmm_context->pool_manager->is_request_for_allocation_recived;
    }

    bool performAllocation()
    {
        bool status = true;

        if (!g_vmm_context->pool_manager->is_request_for_allocation_recived)
        {
            LOG_INFO("No pending allocations");
            return status;
        }

        for (int i = 0; i < 10; i++)
        {
            if (g_vmm_context->pool_manager->allocation_requests->size[i] != 0)
            {
                status = _allocatePool
                (
                    g_vmm_context->pool_manager->allocation_requests->size[i],
                    g_vmm_context->pool_manager->allocation_requests->count[i],
                    g_vmm_context->pool_manager->allocation_requests->intention[i]
                );

                if (!status)
                {
                    LOG_ERROR("Pool manager allocate and add to pool table failed");
                    break;
                }

                g_vmm_context->pool_manager->allocation_requests->size[i] = 0;
                g_vmm_context->pool_manager->allocation_requests->count[i] = 0;
                g_vmm_context->pool_manager->allocation_requests->intention[i] = INTENTION_NONE;

                LOG_INFO("Allocation successful");
            }
        }

        g_vmm_context->pool_manager->is_request_for_allocation_recived = false;

        return status;
    }

    bool initialize()
    {
        g_vmm_context->pool_manager = ::allocatePool<__pool_manager>();
        if (g_vmm_context->pool_manager == nullptr)
        {
            LOG_ERROR("Pool manager allocation failed");
            return false;
        }
        RtlSecureZeroMemory(g_vmm_context->pool_manager, sizeof(__pool_manager));

        g_vmm_context->pool_manager->allocation_requests = ::allocatePool<__request_new_allocation>();
        if (g_vmm_context->pool_manager->allocation_requests == nullptr)
        {
            LOG_ERROR("Allacation requests allocation failed");
            return false;
        }
        RtlSecureZeroMemory(g_vmm_context->pool_manager->allocation_requests, sizeof(__request_new_allocation));

        g_vmm_context->pool_manager->list_of_allocated_pools = ::allocatePool<LIST_ENTRY>();
        if (g_vmm_context->pool_manager->list_of_allocated_pools == nullptr)
        {
            LOG_ERROR("List of allocated pools allocation failed");
            return false;
        }
        RtlSecureZeroMemory(g_vmm_context->pool_manager->list_of_allocated_pools, sizeof(LIST_ENTRY));

        InitializeListHead(g_vmm_context->pool_manager->list_of_allocated_pools);

        if (!requestAllocation(sizeof(__ept_dynamic_split), 100, INTENTION_SPLIT_PML2))
        {
            LOG_ERROR("pool mangaer request allocation Failed");
            return false;
        }

        if (!requestAllocation(sizeof(__ept_hooked_page_info), 100, INTENTION_TRACK_HOOKED_PAGES))
        {
            LOG_ERROR("pool mangaer request allocation Failed");
            return false;
        }

        if (!requestAllocation(100, 100, INTENTION_EXEC_TRAMPOLINE))
        {
            LOG_ERROR("pool mangaer request allocation Failed");
            return false;
        }

        if (!requestAllocation(sizeof(__ept_hooked_function_info), 100, INTENTION_TRACK_HOOKED_FUNCTIONS))
        {
            LOG_ERROR("pool mangaer request allocation Failed");
            return false;
        }

        return performAllocation();
    }

    void uninitialize()
    {
        PLIST_ENTRY current = 0;

        if (g_vmm_context->pool_manager->list_of_allocated_pools != nullptr)
        {
            current = g_vmm_context->pool_manager->list_of_allocated_pools;

            while (g_vmm_context->pool_manager->list_of_allocated_pools != current->Flink)
            {
                current = current->Flink;

                // get the head of the record
                __pool_table* pool_table = (__pool_table*)CONTAINING_RECORD(current, __pool_table, pool_list);

                // free the alloocated buffer
                freePool(pool_table->address);

                // free the record itself
                freePool(pool_table);
            }

            freePool(g_vmm_context->pool_manager->list_of_allocated_pools);
        }

        if (g_vmm_context->pool_manager->allocation_requests != nullptr)
        {
            freePool(g_vmm_context->pool_manager->allocation_requests);
        }
    }

    void releasePool(void* address)
    {
        PLIST_ENTRY current = 0;
        current = g_vmm_context->pool_manager->list_of_allocated_pools;

        spinlock::lock(&g_vmm_context->pool_manager->lock_for_reading_pool);
        while (g_vmm_context->pool_manager->list_of_allocated_pools != current->Flink)
        {
            current = current->Flink;

            // Get the head of the record
            __pool_table* pool_table = (__pool_table*)CONTAINING_RECORD(current, __pool_table, pool_list);

            if (address == pool_table->address)
            {
                RtlSecureZeroMemory(address, pool_table->size);
                pool_table->is_busy = false;
                pool_table->recycled = true;
                break;
            }
        }

        spinlock::unlock(&g_vmm_context->pool_manager->lock_for_reading_pool);
    }

    inline const char* intention_to_string(allocation_intention intention)
    {
        switch (intention)
        {
        case INTENTION_NONE:   return "None";
        case INTENTION_TRACK_HOOKED_PAGES:   return "Track Hooked Pages";
        case INTENTION_EXEC_TRAMPOLINE: return "Trampoline";
        case INTENTION_SPLIT_PML2: return "Split Pml2";
        case INTENTION_TRACK_HOOKED_FUNCTIONS: return "Trace Hooked Functions";
        default:      return "Unknown";
        }
    }

    void dumpPoolsInfo()
    {
        PLIST_ENTRY current = g_vmm_context->pool_manager->list_of_allocated_pools;

        spinlock::lock(&g_vmm_context->pool_manager->lock_for_reading_pool);

        DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "-----------------------------------POOL MANAGER DUMP-----------------------------------\r\n");

        while (g_vmm_context->pool_manager->list_of_allocated_pools != current->Flink)
        {
            current = current->Flink;

            // Get the head of the record
            __pool_table* pool_table = (__pool_table*)CONTAINING_RECORD(current, __pool_table, pool_list);

            LOG_DUMP("Address: 0x%X    Size: %llu    Intention: %s    Is Busy: %s    Recycled: %s",
                pool_table->address, pool_table->size, intention_to_string(pool_table->intention), pool_table->is_busy ? "Yes" : "No",
                pool_table->recycled ? "Yes" : "No");
        }

        DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "-----------------------------------POOL MANAGER DUMP-----------------------------------\r\n");

        spinlock::unlock(&g_vmm_context->pool_manager->lock_for_reading_pool);
    }
}