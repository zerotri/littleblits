#pragma once

#include <cstdint>
#include <functional>

namespace Rockit {
    class Coroutine {
    public:
        enum class Status {
            None,
            Started,
            Suspended,
            Running,
            Ended,
            Error
        };

        enum class StackSize {
            Tiny = 4 * 1024,
            Small = 16 * 1024,
            Medium = 64 * 1024,
            Large = 512 * 1024,
            Huge = 1024 * 1024,
        };

        using Context = void *;
        using UserData = void *;
        using Entrypoint = std::function<UserData(Coroutine &coroutine, Coroutine::UserData userData)>;

    protected:
        Coroutine *caller = nullptr;
        const char *description = nullptr;
        Context context = nullptr;
        UserData data = nullptr;
        Entrypoint entrypoint = nullptr;
        Status status = Status::None;
        std::size_t stackSize = (size_t) StackSize::Tiny;
    private:
        static UserData EnterIntoCoroutine();

        static UserData ExitFromCoroutine();

    public:
        static Coroutine *GetCurrentlyActiveCoroutine();

        static Context GetCurrentlyActiveContext();

    public:
        Coroutine() = default;

        explicit Coroutine(Context context, const char *description = nullptr);

        Coroutine(StackSize stackSize, Entrypoint entrypoint, const char *description = nullptr);

        ~Coroutine();

        [[nodiscard]] bool IsActive() const;

        [[nodiscard]] bool IsRunning() const;

        UserData Resume(UserData data);

        UserData Yield(Coroutine::UserData data);

        UserData SwapToContext();

        UserData GetUserData() { return data; };

        void SetUserData(UserData newData) { data = newData; };

        Status GetStatus() { return status; };

        void SetStatus(Status newStatus) { status = newStatus; };

        Coroutine *GetCaller() const { return caller; };

        void SetCaller(Coroutine *newCaller) { caller = newCaller; };

        Context GetContext() const { return context; };

        void SetContext(Context newContext) { context = newContext; };

        const char *GetDescription() const { return description; }
    };

    Coroutine::UserData Resume(Coroutine *coroutine, Coroutine::UserData data);

    Coroutine::UserData Yield(Coroutine::UserData data);
};