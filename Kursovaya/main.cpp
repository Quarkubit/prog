#include <iostream>
#include <vector>
#include <cstdlib>

class Pool
{
private:
    size_t block_size_;
    size_t num_blocks_;
    char *data_;
    std::vector<size_t> free_blocks_;

public:
    Pool(size_t block_size, size_t num_blocks) : block_size_(block_size), num_blocks_(num_blocks)
    {
        data_ = new char[block_size_ * num_blocks_];
        for (size_t i = 0; i < num_blocks_; i++)
        {
            free_blocks_.push_back(i);
        }
    }

    ~Pool()
    {
        delete[] data_;
    }

    void *Allocate()
    {
        if (free_blocks_.empty())
        {
            std::cerr << "Pool is out of memory" << std::endl;
            return nullptr;
        }
        size_t block_index = free_blocks_.back();
        free_blocks_.pop_back();
        return data_ + block_index * block_size_;
    }

    void Deallocate(void *ptr)
    {
        size_t block_index = (((char *)ptr - data_) / block_size_);
        free_blocks_.push_back(block_index);
    }

    size_t GetNumFreeBlocks() const
    {
        return free_blocks_.size();
    }
};

class PoolAllocator
{
private:
    Pool *CreateNewPool()
    {
        Pool *pool = new Pool(block_size_, num_blocks_per_pool_);
        pools_.push_back(pool);
        return pool;
    }

    size_t block_size_;
    size_t num_blocks_per_pool_;
    std::vector<Pool *> pools_;
    Pool *current_pool_ = nullptr;

public:
    PoolAllocator(size_t block_size, size_t num_blocks_per_pool)
        : block_size_(block_size), num_blocks_per_pool_(num_blocks_per_pool) {}

    ~PoolAllocator()
    {
        for (auto pool : pools_)
        {
            delete pool;
        }
    }

    void *Allocate()
    {
        if (current_pool_ && current_pool_->GetNumFreeBlocks() > 0)
        {
            return current_pool_->Allocate();
        }
        current_pool_ = CreateNewPool();
        return current_pool_->Allocate();
    }

    void Deallocate(void *ptr)
    {
        if (!current_pool_)
        {
            std::cerr << "Cannot deallocate memory: no current pool" << std::endl;
            return;
        }
        current_pool_->Deallocate(ptr);
        if (current_pool_->GetNumFreeBlocks() == num_blocks_per_pool_)
        {
            current_pool_ = nullptr;
        }
    }
};

int main()
{
    PoolAllocator allocator(16, 100);

    // Allocate and deallocate memory using the pool allocator
    int *a = (int *)allocator.Allocate();
    std::cout << "a is alocated\n";
    int *b = (int *)allocator.Allocate();
    std::cout << "b is alocated\n";
    allocator.Deallocate(a);
    std::cout << "a is dealocated\n";
    allocator.Deallocate(b);
    std::cout << "b is dealocated\n";
    std::cout << "\nend of program\n";

    char c;
    std::cin >> c;
    return 0;
}