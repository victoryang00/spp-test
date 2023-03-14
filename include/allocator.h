//
// Created by victoryang00 on 3/12/23.
//

#ifndef SPP_TEST_ALLOCATOR_H
#define SPP_TEST_ALLOCATOR_H

#include <err.h>
#include <sys/mman.h>
#include <cstdlib>
#include <cstdint>

#define MAP_SPP 0x01000000

#define ETP (0) // entropy to 8 bits
#define BKT (1 << ETP) // bucket size
#define ALIGN (7) // alignment
#define MAX_EXP (17) // max size allocate
#define MIN_EXP (6) // smallest blk
#define FLI (MAX_EXP - MIN_EXP + 1) // num of first level index
#define SLI_LOG2 (4) // number of second level index
#define SLI (1<< SLI_LOG2)
#define SMALL_BLK (1 << (MIN_EXP+1))
#define ELE (1<<24) // 3 ** 24 elements
#define SEED_MAX (1 << 10)
#define PAGE_SIZE (1 << 12)
#define INDEX (FLI*SLI)
#define BUCKET_SIZE (8UL << 30) // 8GB

class MemPool { // Each MemPool consist of several SubPools.
private:
    struct FreeNode {
        FreeNode* pNext;
    };

    struct MemBlock {
        int guardian;
        void* bucket[BKT];        // array for randomization and OP entropy
        void* start;              // start address of a size class
        void* stop;               // stop address of a size class
        void* current;            // bumper pointer
        void* guardpage;
        void* subpage;
        FreeNode* head;              // head of the free list
        int32_t frequence;        // frequence of subpage
        uint64_t bitmap[ELE>>6];  // bitmap
        pthread_mutex_t lock;
        uint32_t size;
    };

    FreeNode* freeNodeHeader;
    MemBlock* memBlockHeader;

public:
    MemPool()
    {
        freeNodeHeader = NULL;
        memBlockHeader = NULL;
    }

    ~MemPool() {
    }
    void* malloc(int size) {
        return NULL;
    }
    void free(void* p) {
    }
};
template <typename Ty>
class SPPAllocator {
public:
    // Member types :

    typedef void _Not_user_specialized;
    typedef Ty value_type;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef std::ptrdiff_t difference_type;

    // Member function :
    pointer address(reference _Val) const noexcept;
    const_pointer address(const_reference _Val) const noexcept;
    void deallocate(pointer _Ptr, size_type _Count);
    pointer allocate(size_type _Count) {
        mpool.malloc(_Count);
    }
    template<class _Uty> void destroy(_Uty *_Ptr);
    template<class _Objty,
            class... _Types>
    void construct(_Objty *_Ptr, _Types&&... _Args);
private:
    static MemPool mpool;


};


#endif //SPP_TEST_ALLOCATOR_H
