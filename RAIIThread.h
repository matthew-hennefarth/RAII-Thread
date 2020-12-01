#ifndef RAIITHREAD_H
#define RAIITHREAD_H

#include <thread>

class RAIIThread{
    public:
        RAIIThread() = default;

        template<class Function, class... Args>
        explicit RAIIThread(Function&& F, Args... args) noexcept : m_thread(F, args...){}

        RAIIThread(RAIIThread&& other) noexcept : m_thread(std::move(other.m_thread)) {}

        /* Thread does not have a copy constructor */
        RAIIThread(const RAIIThread& t) = delete;

        ~RAIIThread(){
            if(m_thread.joinable()){
                m_thread.join();
            }
        }

        constexpr void join() {
            m_thread.join();
        }

        constexpr void detach() {
            m_thread.detach();
        }

        inline bool joinable() const noexcept {
            return m_thread.joinable();
        }

        [[nodiscard]] inline std::thread::id get_id() const noexcept {
            return m_thread.get_id();
        }

        inline auto native_handle() {
            return m_thread.native_handle();
        }

        constexpr void swap(RAIIThread& other) noexcept{
            m_thread.swap(other.m_thread);
        }

        inline RAIIThread& operator=(RAIIThread&& other) noexcept {
            m_thread = std::move(other.m_thread);
            return *this;
        }

        /* Thread does not have an assignment operator */
        RAIIThread& operator=(const RAIIThread&) = delete;

    private:
        std::thread m_thread;
};

#endif //RAIITHREAD_H
