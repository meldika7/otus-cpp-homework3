#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

#define UNUSED(variable) (void)variable;

struct deleter
{
    void operator()(void *ptr)
    {
        ::operator delete(ptr);
    }
};

template <class T>
struct custom_allocator
{
    using value_type = T;

    std::shared_ptr<void> pool;
    static constexpr std::size_t PoolSize = 1000;

    custom_allocator() noexcept
        : pool(::operator new(sizeof(uint8_t) * PoolSize), deleter())
    {
    }

    template <class U>
    custom_allocator(const custom_allocator<U> &a) noexcept
    {
        pool = a.pool;
    }

    custom_allocator select_on_container_copy_construction() const
    {
        std::cout << "cpp_11_allocator::select_on_container_copy_construction()" << std::endl;
        return custom_allocator();
    }

    T *allocate(std::size_t n)
    {
        //return static_cast<T *>(pool.get()); // dummy implementation
		std::cout << "allocate: [n = " << n << "]" << std::endl;
		auto p = std::malloc(n * sizeof(T));
		if (!p)
			throw std::bad_alloc();
		return reinterpret_cast<T *>(p);
    }
    void deallocate(T *p, std::size_t n)
    {
        // implementation
		std::cout << "deallocate: [n  = " << n << "] " << std::endl;
		std::free(p);
    }

    template <class U>
    struct rebind
    {
        typedef custom_allocator<U> other;
    };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;
};

int main()
{
    try
    {
		;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}