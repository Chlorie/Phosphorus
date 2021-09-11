#pragma once

#include <utility>

namespace ph
{
    template <typename T>
    class Pimpl final
    {
    public:
        constexpr Pimpl() noexcept = default;

        template <typename... Args>
        explicit Pimpl(std::in_place_t, Args&&... args):
            ptr_(new T(static_cast<Args&&>(args)...)),
            deleter_(deleter_for<T>) {}

        template <std::derived_from<T> U, typename... Args>
        explicit Pimpl(std::in_place_type_t<U>, Args&&... args):
            ptr_(new U(static_cast<Args&&>(args)...)),
            deleter_(deleter_for<U>) {}

        ~Pimpl() noexcept
        {
            if (ptr_)
                deleter_(ptr_);
        }

        Pimpl(const Pimpl&) = delete;
        Pimpl& operator=(const Pimpl&) = delete;

        Pimpl(Pimpl&& other) noexcept:
            ptr_(std::exchange(other.ptr_, nullptr)), deleter_(other.deleter_) {}

        Pimpl& operator=(Pimpl&& other) noexcept
        {
            if (&other == this) return *this;
            if (ptr_) deleter_(ptr_);
            ptr_ = std::exchange(other.ptr_, nullptr);
            deleter_ = other.deleter_;
            return *this;
        }

        template <typename... Args>
        void emplace(Args&&... args)
        {
            reset();
            ptr_ = new T(static_cast<Args&&>(args)...);
            deleter_ = deleter_for<T>;
        }

        template <typename U, typename... Args>
        void emplace(std::in_place_type_t<U>, Args&&... args)
        {
            reset();
            ptr_ = new U(static_cast<Args&&>(args)...);
            deleter_ = deleter_for<U>;
        }

        T& operator*() noexcept { return *static_cast<T*>(ptr_); }
        const T& operator*() const noexcept { return *static_cast<const T*>(ptr_); }
        T* operator->() noexcept { return static_cast<T*>(ptr_); }
        const T* operator->() const noexcept { return static_cast<const T*>(ptr_); }
        T* get() noexcept { return static_cast<T*>(ptr_); }
        const T* get() const noexcept { return static_cast<const T*>(ptr_); }

        explicit operator bool() const noexcept { return ptr_ != nullptr; }

        void reset() noexcept
        {
            if (ptr_) deleter_(ptr_);
            ptr_ = nullptr;
        }

    private:
        void* ptr_ = nullptr;
        void (*deleter_)(void*) noexcept = nullptr;

        template <typename U>
        static void deleter_for(void* ptr) noexcept { delete static_cast<U*>(ptr); }
    };

    template <typename T>
    class PimplBase
    {
    public:
        [[nodiscard]] T* impl() noexcept { return impl_.get(); }
        [[nodiscard]] const T* impl() const noexcept { return impl_.get(); }

    protected:
        Pimpl<T> impl_;
    };
}
