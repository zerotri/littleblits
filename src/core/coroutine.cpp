#include <rockit/core/coroutine.h>
#include <malloc.h>

// Rockit Coroutines
// This coroutine class uses public domain code from Near, available here: https://github.com/creationix/libco

namespace Rockit
{
#if defined(__i386__) || defined(_M_X86)
    #error("Currently not implemented for 32bit x86")
    #define ROCKIT_COROUTINE_X86 (1)
#elif (defined(__amd64__) || defined(_M_AMD64) || defined(_M_X64))
    #define ROCKIT_COROUTINE_X86_64 (1)
#elif defined(__arm__)
    #error("Currently not implemented for arm32")
    #define ROCKIT_COROUTINE_ARM32 (1)
#elif defined(__aarch64__)
    #error("Currently not implemented for arm64")
    #define ROCKIT_COROUTINE_ARM64 (1)
#elif defined(__EMSCRIPTEN__)
    #error("Currently not implemented for emscripten")
    #define ROCKIT_COROUTINE_EMSCRIPTEN (1)
#endif

#if defined(_WIN32)
    #define ROCKIT_COROUTINE_WINDOWS (1)
#elif defined(__APPLE__)
    #define ROCKIT_COROUTINE_APPLE (1)
#else
    #define ROCKIT_COROUTINE_LINUX (1)
    #define ROCKIT_COROUTINE_MPROTECT (1)
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define ROCKIT_COROUTINE_PRIVATE __attribute__((unused)) static
#else
    #define ROCKIT_COROUTINE_PRIVATE static
#endif

#if defined(_MSC_VER)
    #define thread_local __declspec(thread)
#elif (__STDC_VERSION__ < 201112L || __cplusplus < 201103L) && (defined(__clang__) || defined(__GNUC__))
    #define ROCKIT_COROUTINE_THREAD_LOCAL thread_local
#else
    #if defined(__STDC_VERSION__)
        #define ROCKIT_COROUTINE_THREAD_LOCAL
    #elif defined(__cplusplus)
        #include <threads.h>
        #define ROCKIT_COROUTINE_THREAD_LOCAL thread_local
    #endif
#endif

#if defined(_MSC_VER)
    #define ROCKIT_COROUTINE_SECTION(name) __pragma(code_seg("." #name))
    #define ROCKIT_COROUTINE_THREAD_LOCAL __declspec(thread)
#elif defined(__APPLE__)
    #define ROCKIT_COROUTINE_SECTION(name) __attribute__((section("__TEXT,__" #name)))
    #define ROCKIT_COROUTINE_THREAD_LOCAL __thread
#else
    #define ROCKIT_COROUTINE_SECTION(name) __attribute__((section("." #name "#")))
#endif

ROCKIT_COROUTINE_PRIVATE void coroutine_return();

#if defined(ROCKIT_COROUTINE_X86_64)

static ROCKIT_COROUTINE_THREAD_LOCAL Coroutine defaultThreadCoroutine;
static ROCKIT_COROUTINE_THREAD_LOCAL Coroutine* currentCoroutine = nullptr;

static ROCKIT_COROUTINE_THREAD_LOCAL long long defaultThreadContext[64] = {0};
static ROCKIT_COROUTINE_THREAD_LOCAL Coroutine::Context activeContext = nullptr;
static void *(*swapContexts)(Coroutine::Context, Coroutine::Context) = nullptr;

#if defined(ROCKIT_COROUTINE_WINDOWS)

ROCKIT_COROUTINE_SECTION(text);
static const unsigned char coroutineSwapFunction[4096] = {
    0x48, 0x89, 0x22,              /* mov [rdx],rsp          */
    0x48, 0x8b, 0x21,              /* mov rsp,[rcx]          */
    0x58,                          /* pop rax                */
    0x48, 0x89, 0x6a, 0x08,        /* mov [rdx+ 8],rbp       */
    0x48, 0x89, 0x72, 0x10,        /* mov [rdx+16],rsi       */
    0x48, 0x89, 0x7a, 0x18,        /* mov [rdx+24],rdi       */
    0x48, 0x89, 0x5a, 0x20,        /* mov [rdx+32],rbx       */
    0x4c, 0x89, 0x62, 0x28,        /* mov [rdx+40],r12       */
    0x4c, 0x89, 0x6a, 0x30,        /* mov [rdx+48],r13       */
    0x4c, 0x89, 0x72, 0x38,        /* mov [rdx+56],r14       */
    0x4c, 0x89, 0x7a, 0x40,        /* mov [rdx+64],r15       */
  #if !defined(ROCKIT_COROUTINE_NO_SSE)
    0x0f, 0x29, 0x72, 0x50,        /* movaps [rdx+ 80],xmm6  */
    0x0f, 0x29, 0x7a, 0x60,        /* movaps [rdx+ 96],xmm7  */
    0x44, 0x0f, 0x29, 0x42, 0x70,  /* movaps [rdx+112],xmm8  */
    0x48, 0x83, 0xc2, 0x70,        /* add rdx,112            */
    0x44, 0x0f, 0x29, 0x4a, 0x10,  /* movaps [rdx+ 16],xmm9  */
    0x44, 0x0f, 0x29, 0x52, 0x20,  /* movaps [rdx+ 32],xmm10 */
    0x44, 0x0f, 0x29, 0x5a, 0x30,  /* movaps [rdx+ 48],xmm11 */
    0x44, 0x0f, 0x29, 0x62, 0x40,  /* movaps [rdx+ 64],xmm12 */
    0x44, 0x0f, 0x29, 0x6a, 0x50,  /* movaps [rdx+ 80],xmm13 */
    0x44, 0x0f, 0x29, 0x72, 0x60,  /* movaps [rdx+ 96],xmm14 */
    0x44, 0x0f, 0x29, 0x7a, 0x70,  /* movaps [rdx+112],xmm15 */
  #endif
    0x48, 0x8b, 0x69, 0x08,        /* mov rbp,[rcx+ 8]       */
    0x48, 0x8b, 0x71, 0x10,        /* mov rsi,[rcx+16]       */
    0x48, 0x8b, 0x79, 0x18,        /* mov rdi,[rcx+24]       */
    0x48, 0x8b, 0x59, 0x20,        /* mov rbx,[rcx+32]       */
    0x4c, 0x8b, 0x61, 0x28,        /* mov r12,[rcx+40]       */
    0x4c, 0x8b, 0x69, 0x30,        /* mov r13,[rcx+48]       */
    0x4c, 0x8b, 0x71, 0x38,        /* mov r14,[rcx+56]       */
    0x4c, 0x8b, 0x79, 0x40,        /* mov r15,[rcx+64]       */
  #if !defined(ROCKIT_COROUTINE_NO_SSE)
    0x0f, 0x28, 0x71, 0x50,        /* movaps xmm6, [rcx+ 80] */
    0x0f, 0x28, 0x79, 0x60,        /* movaps xmm7, [rcx+ 96] */
    0x44, 0x0f, 0x28, 0x41, 0x70,  /* movaps xmm8, [rcx+112] */
    0x48, 0x83, 0xc1, 0x70,        /* add rcx,112            */
    0x44, 0x0f, 0x28, 0x49, 0x10,  /* movaps xmm9, [rcx+ 16] */
    0x44, 0x0f, 0x28, 0x51, 0x20,  /* movaps xmm10,[rcx+ 32] */
    0x44, 0x0f, 0x28, 0x59, 0x30,  /* movaps xmm11,[rcx+ 48] */
    0x44, 0x0f, 0x28, 0x61, 0x40,  /* movaps xmm12,[rcx+ 64] */
    0x44, 0x0f, 0x28, 0x69, 0x50,  /* movaps xmm13,[rcx+ 80] */
    0x44, 0x0f, 0x28, 0x71, 0x60,  /* movaps xmm14,[rcx+ 96] */
    0x44, 0x0f, 0x28, 0x79, 0x70,  /* movaps xmm15,[rcx+112] */
  #endif
    0xff, 0xe0,                    /* jmp rax                */
};

#include <windows.h>
#undef Yield

static void initCoroutineSwapFunction() {
    #if ROCKIT_COROUTINE_MPROTECT
    DWORD old_privileges;
    VirtualProtect((void*)coroutineSwapFunction, sizeof coroutineSwapFunction, PAGE_EXECUTE_READ, &old_privileges);
    #endif
}
#else

/* ABI: SystemV */
static const unsigned char coroutineSwapFunction[4096] = {
    0x48, 0x89, 0x26,        /* mov [rsi],rsp    */
    0x48, 0x8b, 0x27,        /* mov rsp,[rdi]    */
    0x58,                    /* pop rax          */
    0x48, 0x89, 0x6e, 0x08,  /* mov [rsi+ 8],rbp */
    0x48, 0x89, 0x5e, 0x10,  /* mov [rsi+16],rbx */
    0x4c, 0x89, 0x66, 0x18,  /* mov [rsi+24],r12 */
    0x4c, 0x89, 0x6e, 0x20,  /* mov [rsi+32],r13 */
    0x4c, 0x89, 0x76, 0x28,  /* mov [rsi+40],r14 */
    0x4c, 0x89, 0x7e, 0x30,  /* mov [rsi+48],r15 */
    0x48, 0x8b, 0x6f, 0x08,  /* mov rbp,[rdi+ 8] */
    0x48, 0x8b, 0x5f, 0x10,  /* mov rbx,[rdi+16] */
    0x4c, 0x8b, 0x67, 0x18,  /* mov r12,[rdi+24] */
    0x4c, 0x8b, 0x6f, 0x20,  /* mov r13,[rdi+32] */
    0x4c, 0x8b, 0x77, 0x28,  /* mov r14,[rdi+40] */
    0x4c, 0x8b, 0x7f, 0x30,  /* mov r15,[rdi+48] */
    0xff, 0xe0,              /* jmp rax          */
};

#include <unistd.h>
#include <sys/mman.h>

static void initCoroutineSwapFunction() {
#if ROCKIT_COROUTINE_MPROTECT
    unsigned long long addr = (unsigned long long)coroutineSwapFunction;
    unsigned long long base = addr - (addr % sysconf(_SC_PAGESIZE));
    unsigned long long size = (addr - base) + sizeof coroutineSwapFunction;
    mprotect((void*)base, size, PROT_READ | PROT_EXEC);
#endif
}

#endif

// static methods
Coroutine* Coroutine::GetCurrentlyActiveCoroutine()
{
    if(!currentCoroutine)
    {
        defaultThreadCoroutine = Coroutine(Coroutine::GetCurrentlyActiveContext(), "default");
        defaultThreadCoroutine.SetStatus(Coroutine::Status::Running);
        currentCoroutine = &defaultThreadCoroutine;
    }

    return currentCoroutine;
}

Coroutine::Context Coroutine::GetCurrentlyActiveContext()
{
    if(!activeContext)
    {
        activeContext = &defaultThreadContext;
    }
    return activeContext;
}

Coroutine::UserData Coroutine::Resume(Coroutine::UserData data)
{
    Coroutine *suspendingCoroutine = Coroutine::GetCurrentlyActiveCoroutine();

    if(this->GetStatus() == Coroutine::Status::Ended)
    {
        return nullptr;
    }

    suspendingCoroutine->SetStatus(Coroutine::Status::Suspended);
    this->SetCaller(suspendingCoroutine);
    this->SetUserData(data);
    this->SetStatus(Coroutine::Status::Running);

    currentCoroutine = this;

    SwapToContext();

    UserData returnData = this->GetCaller()->GetUserData();
    return returnData;
}

Coroutine::UserData Resume(Coroutine* coroutine, Coroutine::UserData data)
{
    return coroutine->Resume(data);
}

Coroutine::UserData Coroutine::Yield(Coroutine::UserData data)
{
    Coroutine *yieldingCoroutine = Coroutine::GetCurrentlyActiveCoroutine();

    if(yieldingCoroutine->GetStatus() == Coroutine::Status::Ended)
    {
        return nullptr;
    }

    Coroutine *caller = yieldingCoroutine->GetCaller();

    yieldingCoroutine->caller->SetUserData(data);
    yieldingCoroutine->SetStatus(Status::Suspended);
    caller->SetStatus(Status::Running);

    currentCoroutine = caller;

    caller->SwapToContext();

    UserData returnData = yieldingCoroutine->GetUserData();
    return returnData;
}

Coroutine::UserData Yield(Coroutine::UserData data)
{
    Coroutine *yieldingCoroutine = Coroutine::GetCurrentlyActiveCoroutine();

    return yieldingCoroutine->Yield(data);
}

// non-static methods
Coroutine::Coroutine(Context context, const char* description)
    : description(description)
{
    SetContext(context);
    SetStatus(Status::Started);
}

Coroutine::Coroutine(StackSize stackSize, Entrypoint entrypoint, const char* description)
    : entrypoint(entrypoint), stackSize((((size_t) stackSize) + 512) & ~15), description(description)
{
    Context handle;
    if(!swapContexts) {
        initCoroutineSwapFunction();
        swapContexts = (void *(*)(Context, Context))(void*)coroutineSwapFunction;
    }

    SetStatus(Status::Started);

    if(!activeContext) activeContext = &defaultThreadContext;

    handle = (Context) malloc( (size_t) stackSize);
    if(handle) {
        long long *p = (long long*)((char*)handle + (size_t) stackSize);
        *--p = (long long)Coroutine::ExitFromCoroutine;     // if entrypoint returns, we want to return to the last one
        *--p = (long long)Coroutine::EnterIntoCoroutine;
        *(long long*)handle = (long long)p;
    }

    SetContext(handle);
}
Coroutine::~Coroutine()
{
    if(context != &defaultThreadContext)
        free(context);
}

bool Coroutine::IsActive() const {
    return (activeContext == this->GetContext());
}
bool Coroutine::IsRunning() const {
    return (status == Status::Running || status == Status::Started || status == Status::Suspended);
}

Coroutine::UserData Coroutine::SwapToContext() {
    Coroutine::Context previousContext = activeContext;
    activeContext = GetContext();
    Coroutine::UserData userData = swapContexts(activeContext, previousContext);

    return userData;
}

Coroutine::UserData Coroutine::EnterIntoCoroutine() {
    Coroutine* coroutine = Coroutine::GetCurrentlyActiveCoroutine();
    auto userData = coroutine->GetUserData();
    return coroutine->entrypoint(*coroutine, userData);
}
Coroutine::UserData Coroutine::ExitFromCoroutine() {

    Coroutine *coroutine = Coroutine::GetCurrentlyActiveCoroutine();
    Coroutine::UserData returnData = coroutine->GetUserData();
    coroutine->SetStatus(Coroutine::Status::Ended);

    while(coroutine->GetStatus() == Coroutine::Status::Ended) {
        coroutine = coroutine->GetCaller();
    }

    currentCoroutine = coroutine;
    coroutine->SetUserData(returnData);
    return coroutine->SwapToContext();
}
#endif

} // namespace Rockit
