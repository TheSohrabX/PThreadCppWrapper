#pragma once

#include <bits/shared_ptr.h>
#include <functional>
#include <iostream>
#include <pthread.h>
#include <tuple>
#include <type_traits>

namespace Spthread
{

template <typename T>
struct is_lambda
{
    inline static constexpr auto value = std::is_class<
      typename std::remove_reference<typename std::remove_pointer<T>::type>::type>::value;
};

template <class... Types>
using DecayedTuple = std::tuple<std::decay_t<Types>...>;

template <class Class, class Function, class... Args>
auto
invoke(Class *instance, Function &&func, Args &&...args)
{
    if constexpr(std::is_member_function_pointer_v<Function>)
        (instance->*func)(std::forward<Args>(args)...);
    else
        func(std::forward<Args>(args)...);
}

template <class Function, class... Args>
static void *
invoker(void *arg)
{
    DecayedTuple<Function, Args...> *raw = reinterpret_cast<DecayedTuple<Function, Args...> *>(arg);

    std::shared_ptr<DecayedTuple<Function, Args...>> data =
      std::make_shared<DecayedTuple<Function, Args...>>(*raw);

    constexpr auto invoke = [](std::decay_t<Function> function,
                               std::decay_t<Args>... args) -> auto {
        return std::invoke(function, args...);
    };

    std::apply(invoke, std::move(*data.get()));

    return nullptr;
}

template <
  typename Function,
  typename... Args,
  typename std::enable_if<std::is_function<typename std::remove_pointer<Function>::type>::value ||
                            std::is_function<Function>::value || is_lambda<Function>::value,
                          int>::type = 0>
auto
run(pthread_t &thread, Function &&func, Args &&...args)
{
    DecayedTuple<Function, Args...> tuple {std::forward<Function>(func),
                                           std::forward<Args>(args)...};

    auto  tuplePtr   = std::make_shared<DecayedTuple<Function, Args...>>(tuple);

    void *pthreadArg = tuplePtr.get();

    pthread_create(&thread, nullptr, &invoker<Function, Args...>, pthreadArg);
}

template <class Class,
          typename Function,
          typename... Args,
          typename std::enable_if<std::is_member_function_pointer<Function>::value, int>::type = 0>
auto
run(pthread_t &thread, Class *instance, Function &&func, Args &&...args)
{
    run(
      thread,
      [](auto *instance, auto func, auto &...args) {
          invoke<Class, Function, Args...>(std::forward<decltype(instance)>(instance),
                                           std::forward<decltype(func)>(func),
                                           std::forward<decltype(args)>(args)...);
      },
      instance, func, std::forward<decltype(args)>(args)...);
}

template <
  typename Function,
  typename... Args,
  typename std::enable_if<std::is_function<typename std::remove_pointer<Function>::type>::value ||
                            std::is_function<Function>::value || is_lambda<Function>::value,
                          int>::type = 0>
auto
singleShot(Function &&func, Args &&...args)
{
    pthread_t thread;
    run(thread, std::forward<Function>(func), std::forward<Args>(args)...);
}

template <class Class,
          typename Function,
          typename... Args,
          typename std::enable_if<std::is_member_function_pointer<Function>::value, int>::type = 0>
auto
singleShot(Class *instance, Function &&func, Args &&...args)
{
    pthread_t thread;
    run(thread, instance, std::forward<Function>(func), std::forward<Args>(args)...);
}

class Thread
{

public:
    Thread();

    ~Thread();

    void start();

    static pthread_t
    currentThreadID()
    {
        return pthread_self();
    }

protected:
    virtual void run() = 0;

private:
    pthread_t m_thread;
};

};    // namespace Spthread

// template <class Class,
//           typename Function,
//           typename... Args,
//           typename std::enable_if<std::is_member_function_pointer<Function>::value, int>::type = 0>
// auto
// run(pthread_t &thread, Class *instance, Function &&func, Args &&...args)
// {
//     struct ThreadData
//     {
//         Class              *instance;
//         Function            func;
//         std::tuple<Args...> args;
//     };

//     ThreadData d {instance, std::forward<Function>(func), {std::forward<Args>(args)...}};

//     std::shared_ptr<ThreadData> data = std::make_shared<ThreadData>(d);

//     run(
//       thread,
//       [data](auto &...args) {
//           invoke<Class, Function, Args...>(std::forward<Class *>(data->instance),
//                                            std::forward<Function>(data->func),
//                                            std::forward<decltype(args)>(args)...);
//       },
//       std::forward<decltype(args)>(args)...);
// }

