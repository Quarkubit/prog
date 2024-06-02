#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class PoolAllocator
{
public:
  // Выделяет блок памяти размером size для пула.
  PoolAllocator(std::size_t size) : pool_(size) {}

  // Возвращает указатель на новый объект типа T из пула.
  T *allocate()
  {
    if (free_list_.empty())
    {
      // Если список свободных объектов пуст, выделяем новый блок памяти.
      pool_.push_back(std::vector<T>(kBlockSize));
      block_index_++;
    }
    T *obj = &pool_[block_index_][free_list_.back()];
    free_list_.pop_back();
    return obj;
  }

  // Освобождает память, выделенную для объекта obj.
  void deallocate(T *obj)
  {
    std::size_t index = obj - &pool_[block_index_][0];
    free_list_.push_back(index);
  }

  void delete_object(T *p)
  {
    deallocate(p);
  }

private:
  // Размер блока памяти, выделяемого для пула.
  static const std::size_t kBlockSize = 128;

  // Список свободных объектов в текущем блоке памяти.
  std::vector<std::size_t> free_list_;

  // Вектор блоков памяти, выделенных для пула.
  std::vector<std::vector<T>> pool_;

  // Индекс текущего блока памяти.
  std::size_t block_index_ = 0;
};

int main() {
  // Создаем пуловый аллокатор для целых чисел, который выделяет блоки памяти размером 100 байт.
  PoolAllocator<int> allocator(100);

  // Выделяем память для 10 целых чисел из пула.
  std::vector<std::unique_ptr<int, decltype(&allocator)>> ints;
  for (int i = 0; i < 10; i++) {
    int* p = allocator.allocate();
    *p = i;
    ints.emplace_back(p, &allocator);
  }

  // Выводим значения целых чисел на экран.
  for (const auto& p : ints) {
    std::cout << *p << std::endl;
  }

  // Освобождаем память, выделенную для целых чисел.
  // Умные указатели автоматически освободят память при выходе из области видимости.
  return 0;
}
