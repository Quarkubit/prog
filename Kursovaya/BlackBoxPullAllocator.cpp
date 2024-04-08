#include <cstddef>
#include <cstdlib>
#include <new>

#define BLOCK_SIZE 16
#define BLOCK_COUNT 1024

class PoolAllocator {
private:
    void* blocks;
    std::size_t block_size;
    std::size_t block_count;
    std::size_t free_blocks;

public:
    PoolAllocator(std::size_t block_size, std::size_t block_count)
        : blocks(std::malloc(block_count * block_size)),
          block_size(block_size),
          block_count(block_count),
          free_blocks(block_count) {
        if (!blocks) {
            throw std::bad_alloc();
        }
    }

    ~PoolAllocator() {
        std::free(blocks);
    }

    void* allocate() {
        if (free_blocks == 0) {
            return nullptr;
        }

        void* block = blocks;
        blocks = static_cast<char*>(blocks) + block_size;
        free_blocks--;

        return block;
    }

    void deallocate(void* block) {
        if (static_cast<char*>(block) < static_cast<char*>(blocks) ||
            static_cast<char*>(block) >= static_cast<char*>(blocks) + (block_count * block_size)) {
            return;
        }

        blocks = static_cast<char*>(blocks) - block_size;
        free_blocks++;
    }
};

int main() {
    PoolAllocator allocator(BLOCK_SIZE, BLOCK_COUNT);

    void* block1 = allocator.allocate();
    void* block2 = allocator.allocate();
    void* block3 = allocator.allocate();

    allocator.deallocate(block2);

    void* block4 = allocator.allocate();

    return 0;
}