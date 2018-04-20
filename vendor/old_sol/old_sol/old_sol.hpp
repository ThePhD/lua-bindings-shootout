// The MIT License (MIT)

// Copyright (c) 2013-2015 Rapptz and contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// This file was generated with a script.
// Generated 2018-04-20 21:43:25.654000 UTC
// This header was generated with sol v1.1.0 (revision 1c8ec15)
// https://github.com/Rapptz/sol

#ifndef SOL_SINGLE_INCLUDE_HPP
#define SOL_SINGLE_INCLUDE_HPP

// beginning of C:\Users\Rig\Desktop\sol\sol\state.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\error.hpp

#include <stdexcept>
#include <string>

namespace old_sol {
class error : public std::runtime_error {
public:
    error(const std::string& str): std::runtime_error("lua: error: " + str) {}
};
} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\error.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\table.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\proxy.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\traits.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\tuple.hpp

#include <tuple>
#include <cstddef>

namespace old_sol {
template<typename... Ts>
struct reverse_tuple;

template<>
struct reverse_tuple<std::tuple<>> {
    using type = std::tuple<>;
};

template<typename T, typename... Ts>
struct reverse_tuple<std::tuple<T, Ts...>> {
    using head = std::tuple<T>;
    using tail = typename reverse_tuple<std::tuple<Ts...>>::type;
    using type = decltype(std::tuple_cat(std::declval<tail>(), std::declval<head>()));
};

template<size_t... Ns>
struct indices { typedef indices type; };

template<size_t N, size_t... Ns>
struct build_indices : build_indices<N - 1, N - 1, Ns...> {};

template<size_t... Ns>
struct build_indices<0, Ns...> : indices<Ns...> {};

template<size_t N, size_t... Ns>
struct build_reverse_indices : build_reverse_indices<N - 1, Ns..., N - 1> {};

template<size_t... Ns>
struct build_reverse_indices<0, Ns...> : indices<Ns...> {};

template<typename... Args>
struct types : build_indices<sizeof...(Args)> { typedef types type; };

namespace detail {
template<class Acc, class... Args>
struct reversed_ : Acc{};

template<typename... RArgs, typename Arg, typename... Args>
struct reversed_<types<RArgs...>, Arg, Args...> : reversed_<types<Arg, RArgs...>, Args...>{};

template<typename Arg>
struct chop_one : types<> {};

template<typename Arg0, typename Arg1, typename... Args>
struct chop_one<types<Arg0, Arg1, Args...>> : types<Arg1, Args...> {};

template<typename Arg, typename... Args>
struct chop_one<types<Arg, Args...>> : types<Args...> {};
} // detail

template<typename... Args>
struct reversed : detail::reversed_<types<>, Args...>{};

template<typename... Args>
struct tuple_types : types<Args...> {};

template<typename... Args>
struct tuple_types<std::tuple<Args...>> : types<Args...> {};

template<typename Arg>
struct remove_one_type : detail::chop_one<Arg> {};

template<typename... Tn>
struct constructors {};

const auto default_constructor = constructors<types<>>{};

template <typename T>
using ref = std::reference_wrapper<T>;

} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\tuple.hpp

#include <type_traits>
#include <functional>

namespace old_sol {
template<typename T>
struct identity { typedef T type; };

template<typename... Args>
struct is_tuple : std::false_type{ };

template<typename... Args>
struct is_tuple<std::tuple<Args...>> : std::true_type{ };

template<typename T>
struct unwrap {
    typedef T type;
};

template<typename T>
struct unwrap<std::reference_wrapper<T>> {
    typedef typename std::add_lvalue_reference<T>::type type;
};

template<typename T>
struct remove_member_pointer;

template<typename R, typename T>
struct remove_member_pointer<R T::*> {
    typedef R type;
};

template<typename T, template<typename...> class Templ>
struct is_specialization_of : std::false_type { };
template<typename... T, template<typename...> class Templ>
struct is_specialization_of<Templ<T...>, Templ> : std::true_type { };

template<class T, class...>
struct are_same : std::true_type { };

template<class T, class U, class... Args>
struct are_same<T, U, Args...> : std::integral_constant <bool, std::is_same<T, U>::value && are_same<T, Args...>::value> { };

template<typename T>
using Type = typename T::type;

template<bool B>
using Bool = std::integral_constant<bool, B>;

template<typename T>
using Not = Bool<!T::value>;

template<typename Condition, typename Then, typename Else>
using If = typename std::conditional<Condition::value, Then, Else>::type;

template<typename Condition, typename Then, typename Else>
using TypeIf = typename std::conditional<Condition::value, Type<Then>, Type<Else>>::type;

template<typename... Args>
struct And : Bool<true> {};

template<typename T, typename... Args>
struct And<T, Args...> : If<T, And<Args...>, Bool<false>> {};

template<typename... Args>
struct Or : Bool<true> {};

template<typename T, typename... Args>
struct Or<T, Args...> : If<T, Bool<true>, Or<Args...>> {};

template<typename... Args>
using EnableIf = typename std::enable_if<And<Args...>::value, int>::type;

template<typename... Args>
using DisableIf = typename std::enable_if<Not<And<Args...>>::value, int>::type;

template<typename T>
using Unqualified = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template<typename T>
using Decay = typename std::decay<T>::type;

template<typename T>
using Unwrap = typename unwrap<T>::type;

template<typename... Args>
struct return_type {
    typedef std::tuple<Args...> type;
};

template<typename T>
struct return_type<T> {
    typedef T type;
};

template<>
struct return_type<> : types<>{
    typedef void type;
};

namespace detail {

template<typename T, bool isclass = std::is_class<Unqualified<T>>::value>
struct is_function_impl : std::is_function<typename std::remove_pointer<T>::type> {};

template<typename T>
struct is_function_impl<T, true> {
    using yes = char;
    using no = struct { char s[2]; };

    struct F { void operator()(); };
    struct Derived : T, F {};
    template<typename U, U> struct Check;

    template<typename V>
    static no test(Check<void (F::*)(), &V::operator()>*);

    template<typename>
    static yes test(...);

    static const bool value = sizeof(test<Derived>(0)) == sizeof(yes);
};

template<class F>
struct check_deducible_signature {
    struct nat {};
    template<class G>
    static auto test(int) -> decltype(&G::operator(), void());
    template<class>
    static auto test(...) -> nat;

    using type = std::is_void<decltype(test<F>(0))>;
};
} // detail

template<class F>
struct has_deducible_signature : detail::check_deducible_signature<F>::type { };

template<typename T>
using has_deducible_signature_t = typename has_deducible_signature<T>::type;

template<typename T>
struct Function : Bool<detail::is_function_impl<T>::value> {};

namespace detail {
template<typename Signature, bool b = has_deducible_signature<Signature>::value>
struct fx_traits;

template<typename Signature>
struct fx_traits<Signature, true> : fx_traits<decltype(&Signature::operator()), false> {

};

template<typename T, typename R, typename... Args>
struct fx_traits<R(T::*)(Args...), false> {
    static const std::size_t arity = sizeof...(Args);
    static const bool is_member_function = true;
    typedef std::tuple<Args...> arg_tuple_type;
    typedef types<Args...> args_type;
    typedef R(T::* function_pointer_type)(Args...);
    typedef typename std::remove_pointer<function_pointer_type>::type function_type;
    typedef R(*free_function_pointer_type)(Args...);
    typedef R return_type;
    typedef typename std::remove_pointer<free_function_pointer_type>::type signature_type;
    template<std::size_t i>
    using arg = typename std::tuple_element<i, arg_tuple_type>::type;
};

template<typename T, typename R, typename... Args>
struct fx_traits<R(T::*)(Args...) const, false> {
    static const std::size_t arity = sizeof...(Args);
    static const bool is_member_function = true;
    typedef std::tuple<Args...> arg_tuple_type;
    typedef types<Args...> args_type;
    typedef R(T::* function_pointer_type)(Args...);
    typedef typename std::remove_pointer<function_pointer_type>::type function_type;
    typedef R(*free_function_pointer_type)(Args...);
    typedef R return_type;
    typedef typename std::remove_pointer<free_function_pointer_type>::type signature_type;
    template<std::size_t i>
    using arg = typename std::tuple_element<i, arg_tuple_type>::type;
};

template<typename R, typename... Args>
struct fx_traits<R(Args...), false> {
    static const std::size_t arity = sizeof...(Args);
    static const bool is_member_function = false;
    typedef std::tuple<Args...> arg_tuple_type;
    typedef types<Args...> args_type;
    typedef R(function_type)(Args...);
    typedef R(*function_pointer_type)(Args...);
    typedef R(*free_function_pointer_type)(Args...);
    typedef R return_type;
    typedef typename std::remove_pointer<free_function_pointer_type>::type signature_type;
    template<std::size_t i>
    using arg = typename std::tuple_element<i, arg_tuple_type>::type;
};

template<typename R, typename... Args>
struct fx_traits<R(*)(Args...), false> {
    static const std::size_t arity = sizeof...(Args);
    static const bool is_member_function = false;
    typedef std::tuple<Args...> arg_tuple_type;
    typedef types<Args...> args_type;
    typedef R(function_type)(Args...);
    typedef R(*function_pointer_type)(Args...);
    typedef R(*free_function_pointer_type)(Args...);
    typedef R return_type;
    typedef typename std::remove_pointer<free_function_pointer_type>::type signature_type;
    template<std::size_t i>
    using arg = typename std::tuple_element<i, arg_tuple_type>::type;
};

} // detail

template<typename Signature>
struct function_traits : detail::fx_traits<Signature> {};

template<typename Signature>
using function_args_t = typename function_traits<Signature>::args_type;

template<typename Signature>
using function_signature_t = typename function_traits<Signature>::signature_type;

template<typename Signature>
using function_return_t = typename function_traits<Signature>::return_type;

namespace detail {
template<typename Signature, bool b = std::is_member_object_pointer<Signature>::value>
struct member_traits : function_traits<Signature> {

};

template<typename Signature>
struct member_traits<Signature, true> {
    typedef typename remove_member_pointer<Signature>::type Arg;
    typedef typename remove_member_pointer<Signature>::type R;
    typedef Signature signature_type;
    static const bool is_member_function = false;
    static const std::size_t arity = 1;
    typedef std::tuple<Arg> arg_tuple_type;
    typedef types<Arg> args_type;
    typedef R return_type;
    typedef R(function_type)(Arg);
    typedef R(*function_pointer_type)(Arg);
    typedef R(*free_function_pointer_type)(Arg);
    template<std::size_t i>
    using arg = typename std::tuple_element<i, arg_tuple_type>::type;
};
} // detail

template<typename Signature>
struct member_traits : detail::member_traits<Signature> {

};

struct has_begin_end_impl {
    template<typename T, typename U = Unqualified<T>,
                         typename B = decltype(std::declval<U&>().begin()),
                         typename E = decltype(std::declval<U&>().end())>
    static std::true_type test(int);

    template<typename...>
    static std::false_type test(...);
};

template<typename T>
struct has_begin_end : decltype(has_begin_end_impl::test<T>(0)) {};

struct has_key_value_pair_impl {
    template<typename T, typename U = Unqualified<T>,
             typename V = typename U::value_type,
             typename F = decltype(std::declval<V&>().first),
             typename S = decltype(std::declval<V&>().second)>
    static std::true_type test(int);

    template<typename...>
    static std::false_type test(...);
};

template<typename T>
struct has_key_value_pair : decltype(has_key_value_pair_impl::test<T>(0)) {};

template<typename T>
auto unwrapper(T&& item) -> decltype(std::forward<T>(item)) {
    return std::forward<T>(item);
}

template<typename Arg>
Unwrap<Arg> unwrapper(std::reference_wrapper<Arg> arg) {
    return arg.get();
}

} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\traits.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\object.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\reference.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\types.hpp

#include <lua.hpp>

namespace old_sol {
struct nil_t {};
const nil_t nil {};
inline bool operator==(nil_t, nil_t) { return true; }
inline bool operator!=(nil_t, nil_t) { return false; }

struct void_type : types<void> {}; // This is important because it allows myobject.call( Void, ... ) to work
const void_type Void {};

template<typename... T>
struct function_sig_t {};
using function_t = function_sig_t<>;

struct upvalue {
    void* value;
    upvalue(void* data) : value(data) {}
    operator void*() const { return value; }
};

struct light_userdata {
    void* value;
    light_userdata(void* data) : value(data) {}
    operator void*() const { return value; }
};

struct userdata {
    void* value;
    userdata(void* data) : value(data) {}
    operator void*() const { return value; }
};

enum class call_syntax {
    dot = 0,
    colon = 1
};

enum class type : int {
    none          = LUA_TNONE,
    nil           = LUA_TNIL,
    string        = LUA_TSTRING,
    number        = LUA_TNUMBER,
    thread        = LUA_TTHREAD,
    boolean       = LUA_TBOOLEAN,
    function      = LUA_TFUNCTION,
    userdata      = LUA_TUSERDATA,
    lightuserdata = LUA_TLIGHTUSERDATA,
    table         = LUA_TTABLE,
    poly          = none   | nil     | string   | number   | thread       |
                    table  | boolean | function | userdata | lightuserdata
};

inline int type_panic(lua_State* L, int index, type expected, type actual) {
    return luaL_error(L, "stack index %d, expected %s, received %s", index, lua_typename(L, static_cast<int>(expected)), lua_typename(L, static_cast<int>(actual)));
}

inline int no_panic(lua_State*, int, type, type) {
    return 0;
}

inline void type_error(lua_State* L, int expected, int actual) {
    luaL_error(L, "expected %s, received %s", lua_typename(L, expected), lua_typename(L, actual));
}

inline void type_error(lua_State* L, type expected, type actual) {
    type_error(L, static_cast<int>(expected), static_cast<int>(actual));
}

inline void type_assert(lua_State* L, int index, type expected, type actual) {
	if (expected != type::poly && expected != actual) {
		type_panic(L, index, expected, actual);
	}
}

inline void type_assert(lua_State* L, int index, type expected) {
    int actual = lua_type(L, index);
    if(expected != type::poly && static_cast<int>(expected) != actual) {
        type_error(L, static_cast<int>(expected), actual);
    }
}

inline std::string type_name(lua_State*L, type t) {
    return lua_typename(L, static_cast<int>(t));
}

template<typename T>
class usertype;
class table;
class function;
class object;

template <typename T, typename = void>
struct lua_type_of : std::integral_constant<type, type::userdata> {

};

template <>
struct lua_type_of<std::string> : std::integral_constant<type, type::string> {

};

template <std::size_t N>
struct lua_type_of<char[N]> : std::integral_constant<type, type::string> {

};

template <>
struct lua_type_of<const char*> : std::integral_constant<type, type::string> {

};

template <>
struct lua_type_of<bool> : std::integral_constant<type, type::boolean> {

};

template <>
struct lua_type_of<nil_t> : std::integral_constant<type, type::nil> {

};

template <>
struct lua_type_of<table> : std::integral_constant<type, type::table> {

};

template <>
struct lua_type_of<object> : std::integral_constant<type, type::poly> {

};

template <>
struct lua_type_of<light_userdata> : std::integral_constant<type, type::lightuserdata> {

};

template <>
struct lua_type_of<function> : std::integral_constant<type, type::function> {

};

template <typename T>
struct lua_type_of<T*> : std::integral_constant<type, type::userdata> {

};

template <typename T>
struct lua_type_of<T, typename std::enable_if<std::is_arithmetic<T>::value>::type> : std::integral_constant<type, type::number> {

};

template<typename T>
inline type type_of() {
    return lua_type_of<Unqualified<T>>::value;
}

inline type type_of(lua_State* L, int index) {
    return static_cast<type>(lua_type(L, index));
}

template <typename T>
struct lua_type_of<T, typename std::enable_if<std::is_enum<T>::value>::type> : std::integral_constant<type, type::number> {

};

} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\types.hpp

namespace old_sol {
class reference {
private:
    lua_State* L = nullptr; // non-owning
    int ref = LUA_NOREF;

    int copy() const {
        push();
        return luaL_ref(L, LUA_REGISTRYINDEX);
    }
public:
    reference() noexcept = default;

    reference(lua_State* L, int index): L(L) {
        lua_pushvalue(L, index);
        ref = luaL_ref(L, LUA_REGISTRYINDEX);
    }

    virtual ~reference() {
        luaL_unref(L, LUA_REGISTRYINDEX, ref);
    }

    int push() const noexcept {
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
		return 1;
    }

    reference(reference&& o) noexcept {
        L = o.L;
        ref = o.ref;

        o.L = nullptr;
        o.ref = LUA_NOREF;
    }

    reference& operator=(reference&& o) noexcept {
        L = o.L;
        ref = o.ref;

        o.L = nullptr;
        o.ref = LUA_NOREF;

        return *this;
    }

    reference(const reference& o) noexcept {
        L = o.L;
        ref = o.copy();
    }

    reference& operator=(const reference& o) noexcept {
        L = o.L;
        ref = o.copy();
        return *this;
    }

    type get_type() const {
        push();
        int result = lua_type(L, -1);
        lua_pop(L, 1);
        return static_cast<type>(result);
    }

    lua_State* state() const noexcept {
        return L;
    }
};
} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\reference.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\stack.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\usertype_traits.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\demangle.hpp

#include <array>
#include <cstdlib>

#if defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>
#endif

namespace old_sol {
namespace detail {
#ifdef _MSC_VER
inline std::string get_type_name(const std::type_info& id) {
    return id.name();
}

#elif defined(__GNUC__) || defined(__clang__)
inline std::string get_type_name(const std::type_info& id) {
    int status;
    char* unmangled = abi::__cxa_demangle(id.name(), 0, 0, &status);
    std::string realname = unmangled;
    std::free(unmangled);
    return realname;
}

#else
#error Compiler not supported for demangling
#endif // compilers

inline std::string demangle(const std::type_info& id) {
    std::string realname = get_type_name(id);
    const static std::array<std::string, 2> removals = {{ "struct ", "class " }};
    const static std::array<std::string, 2> replacements = {{ "::", "_" }};
    for(std::size_t r = 0; r < removals.size(); ++r) {
        auto found = realname.find(removals[r]);
        while(found != std::string::npos) {
            realname.erase(found, removals[r].size());
            found = realname.find(removals[r]);
       }
    }

    for(std::size_t r = 0; r < replacements.size(); r+=2) {
        auto found = realname.find(replacements[r]);
        while(found != std::string::npos) {
            realname.replace(found, replacements[r].size(), replacements[r + 1]);
            found = realname.find(replacements[r], found);
        }
    }

    return realname;
}
} // detail
} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\demangle.hpp

namespace old_sol {

template<typename T>
struct usertype_traits {
    static const std::string name;
    static const std::string metatable;
    static const std::string gctable;
};

template<typename T>
const std::string usertype_traits<T>::name = detail::demangle(typeid(T));

template<typename T>
const std::string usertype_traits<T>::metatable = std::string("old_sol.").append(detail::demangle(typeid(T)));

template<typename T>
const std::string usertype_traits<T>::gctable = std::string("old_sol.").append(detail::demangle(typeid(T))).append(".\xE2\x99\xBB");

}

// end of C:\Users\Rig\Desktop\sol\sol\usertype_traits.hpp

#include <utility>
#include <cstring>

namespace old_sol {
namespace detail {
template<typename T>
inline T* get_ptr(T& val) {
    return std::addressof(val);
}

template<typename T>
inline T* get_ptr(std::reference_wrapper<T> val) {
    return std::addressof(val.get());
}

template<typename T>
inline T* get_ptr(T* val) {
    return val;
}

template<typename Decorated>
struct return_forward {
    typedef Unqualified<Decorated> T;

    T& operator()(T& value) const {
        return value;
    }

    T&& operator()(T&& value) const {
        return std::move(value);
    }

    T operator()(const T& value) const {
        return value;
    }

    // handle retarded libraries
    T operator()(const T&& value) const {
        return value;
    }
};
} // detail

namespace stack {
namespace detail {
template<typename T, typename Key, typename... Args>
inline int push_userdata(lua_State* L, Key&& metatablekey, Args&&... args) {
    T* pdatum = static_cast<T*>(lua_newuserdata(L, sizeof(T)));
    std::allocator<T> alloc{};
    alloc.construct(pdatum, std::forward<Args>(args)...);
    luaL_getmetatable(L, std::addressof(metatablekey[0]));
    lua_setmetatable(L, -2);
    return 1;
}
} // detail

template<typename T, typename = void>
struct getter;
template<typename T, typename = void>
struct pusher;
template<typename T, type = lua_type_of<T>::value, typename = void>
struct checker;

template<typename T, typename... Args>
inline int push(lua_State* L, T&& t, Args&&... args) {
    return pusher<Unqualified<T>>{}.push(L, std::forward<T>(t), std::forward<Args>(args)...);
}

template<typename T, std::size_t... I>
inline int push_tuple(lua_State* L, indices<I...>, T&& tuplen) {
    using swallow = char[1 + sizeof...(I)];
    int pushcount = 0;
    swallow {'\0', (pushcount += old_sol::stack::push(L, std::get<I>(tuplen)), '\0')... };
    return pushcount;
}

template<typename T, typename Arg, typename... Args>
inline int push(lua_State* L, Arg&& arg, Args&&... args) {
    return pusher<Unqualified<T>>{}.push(L, std::forward<Arg>(arg), std::forward<Args>(args)...);
}

inline int push_args(lua_State*) {
    // do nothing
    return 0;
}

template<typename T, typename... Args>
inline int push_args(lua_State* L, T&& t, Args&&... args) {
    int pushcount = push(L, std::forward<T>(t));
    using swallow = char[];
    void(swallow{'\0', (pushcount += push(L, std::forward<Args>(args)), '\0')... });
    return pushcount;
}

template<typename T, typename U = Unqualified<T>>
inline auto get(lua_State* L, int index = -1) -> decltype(getter<U>{}.get(L, index)) {
    return getter<U>{}.get(L, index);
}

template<typename T>
auto pop(lua_State* L) -> decltype(get<T>(L)) {
    typedef decltype(get<T>(L)) ret_t;
    ret_t r = get<T>(L);
    lua_pop(L, 1);
    return r;
}

template<typename T>
struct get_return {
    typedef decltype(get<T>(nullptr)) type;
};

template <typename T, type expected, typename>
struct checker {
    template <typename Handler>
    static bool check (lua_State* L, int index, const Handler& handler) {
        const type indextype = type_of(L, index);
        bool success = expected == indextype;
        if (!success) {
            // expected type, actual type
            handler(L, index, expected, indextype);
        }
        return success;
    }
};

template <typename T, typename Handler>
bool check(lua_State* L, int index, Handler&& handler) {
    typedef Unqualified<T> Tu;
    checker<Tu> c;
    return c.check(L, index, std::forward<Handler>(handler));
}

template <typename T>
bool check(lua_State* L, int index) {
    auto handler = type_panic;
    return check<T>(L, index, handler);
}

template<typename T, typename>
struct getter {
    template<typename U = T, EnableIf<std::is_floating_point<U>> = 0>
    static U get(lua_State* L, int index = -1) {
        return static_cast<U>(lua_tonumber(L, index));
    }

    template<typename U = T, EnableIf<std::is_integral<U>, std::is_signed<U>> = 0>
    static U get(lua_State* L, int index = -1) {
        return static_cast<T>(lua_tointeger(L, index));
    }

    template<typename U = T, EnableIf<std::is_integral<U>, std::is_unsigned<U>> = 0>
    static U get(lua_State* L, int index = -1) {
        typedef typename std::make_signed<U>::type signed_int;
        return static_cast<U>(stack::get<signed_int>(L, index));
    }

    template<typename U = T, EnableIf<std::is_base_of<reference, U>> = 0>
    static U get(lua_State* L, int index = -1) {
        return T(L, index);
    }

    template<typename U = T, EnableIf<Not<std::is_base_of<reference, U>>, Not<std::is_integral<U>>, Not<std::is_floating_point<U>>> = 0>
    static U& get(lua_State* L, int index = -1) {
        void* udata = lua_touserdata(L, index);
        T* obj = static_cast<T*>(udata);
        return *obj;
    }
};

template<typename T>
struct getter<T*> {
    static T* get(lua_State* L, int index = -1) {
        void* udata = lua_touserdata(L, index);
        T** obj = static_cast<T**>(udata);
        return *obj;
    }
};

template<typename T>
struct getter<T&> {
    static T& get(lua_State* L, int index = -1) {
        void* udata = lua_touserdata(L, index);
        T** obj = static_cast<T**>(udata);
        return **obj;
    }
};

template<typename T>
struct getter<std::reference_wrapper<T>> {
    static T& get(lua_State* L, int index = -1) {
        return getter<T&>{}.get(L, index);
    }
};

template<>
struct getter<type> {
    static type get(lua_State *L, int index){
        return static_cast<type>(lua_type(L, index));
    }
};

template<>
struct getter<bool> {
    static bool get(lua_State* L, int index) {
        return lua_toboolean(L, index) != 0;
    }
};

template<>
struct getter<std::string> {
    static std::string get(lua_State* L, int index = -1) {
        std::string::size_type len;
        auto str = lua_tolstring(L, index, &len);
        return { str, len };
    }
};

template<>
struct getter<const char*> {
    static const char* get(lua_State* L, int index = -1) {
        return lua_tostring(L, index);
    }
};

template<>
struct getter<nil_t> {
    static nil_t get(lua_State* L, int index = -1) {
        if(lua_isnil(L, index) == 0) {
            throw old_sol::error("not nil");
        }
        return nil_t{ };
    }
};

template<>
struct getter<userdata> {
    static userdata get(lua_State* L, int index = -1) {
        return{ lua_touserdata(L, index) };
    }
};

template<>
struct getter<light_userdata> {
    static light_userdata get(lua_State* L, int index = 1) {
        return{ lua_touserdata(L, index) };
    }
};

template<>
struct getter<upvalue> {
    static upvalue get(lua_State* L, int index = 1) {
        return{ lua_touserdata(L, lua_upvalueindex(index)) };
    }
};

template<>
struct getter<void*> {
    static void* get(lua_State* L, int index = 1) {
        return lua_touserdata(L, index);
    }
};

template<typename T, typename>
struct pusher {
    template<typename U = T, EnableIf<std::is_floating_point<U>> = 0>
    static int push(lua_State* L, const T& value) {
        lua_pushnumber(L, value);
        return 1;
    }

    template<typename U = T, EnableIf<std::is_integral<U>, std::is_signed<U>> = 0>
    static int push(lua_State* L, const T& value) {
        lua_pushinteger(L, value);
        return 1;
    }

    template<typename U = T, EnableIf<std::is_integral<U>, std::is_unsigned<U>> = 0>
    static int push(lua_State* L, const T& value) {
         typedef typename std::make_signed<T>::type signed_int;
         return stack::push(L, static_cast<signed_int>(value));
    }

    template<typename U = T, EnableIf<has_begin_end<U>, Not<has_key_value_pair<U>>> = 0>
    static int push(lua_State* L, const T& cont) {
        lua_createtable(L, cont.size(), 0);
        unsigned index = 1;
        for(auto&& i : cont) {
            // push the index
            pusher<unsigned>{}.push(L, index++);
            // push the value
            pusher<Unqualified<decltype(i)>>{}.push(L, i);
            // set the table
            lua_settable(L, -3);
        }
        return 1;
    }

    template<typename U = T, EnableIf<has_begin_end<U>, has_key_value_pair<U>> = 0>
    static int push(lua_State* L, const T& cont) {
        lua_createtable(L, cont.size(), 0);
        for(auto&& pair : cont) {
            pusher<Unqualified<decltype(pair.first)>>{}.push(L, pair.first);
            pusher<Unqualified<decltype(pair.second)>>{}.push(L, pair.second);
            lua_settable(L, -3);
        }
        return 1;
    }

    template<typename U = T, EnableIf<std::is_base_of<reference, U>> = 0>
    static int push(lua_State*, T& ref) {
       return ref.push();
    }

    template<typename U = Unqualified<T>, EnableIf<Not<has_begin_end<U>>, Not<std::is_base_of<reference, U>>, Not<std::is_integral<U>>, Not<std::is_floating_point<U>>> = 0>
    static int push(lua_State* L, T& t) {
        return detail::push_userdata<U>(L, usertype_traits<T>::metatable, t);
    }

    template<typename U = Unqualified<T>, EnableIf<Not<has_begin_end<U>>, Not<std::is_base_of<reference, U>>, Not<std::is_integral<U>>, Not<std::is_floating_point<U>>> = 0>
    static int push(lua_State* L, T&& t) {
        return detail::push_userdata<U>(L, usertype_traits<T>::metatable, std::move(t));
    }
};

template<typename T>
struct pusher<T*> {
    static int push(lua_State* L, T* obj) {
        return detail::push_userdata<T*>(L, usertype_traits<T*>::metatable, obj);
    }
};

template<typename T>
struct pusher<std::reference_wrapper<T>> {
    static int push(lua_State* L, const std::reference_wrapper<T>& t) {
        return stack::push(L, std::addressof(t.get()));
    }
};

template<>
struct pusher<bool> {
    static int push(lua_State* L, const bool& b) {
        lua_pushboolean(L, b);
        return 1;
    }
};

template<>
struct pusher<nil_t> {
    static int push(lua_State* L, const nil_t&) {
        lua_pushnil(L);
        return 1;
    }
};

template<>
struct pusher<lua_CFunction> {
    static int push(lua_State* L, lua_CFunction func, int n = 0) {
        lua_pushcclosure(L, func, n);
        return 1;
    }
};

template<>
struct pusher<void*> {
    static int push(lua_State* L, void* userdata) {
        lua_pushlightuserdata(L, userdata);
        return 1;
    }
};

template<>
struct pusher<upvalue> {
    static int push(lua_State* L, upvalue upvalue) {
        lua_pushlightuserdata(L, upvalue);
        return 1;
    }
};

template<>
struct pusher<light_userdata> {
    static int push(lua_State* L, light_userdata userdata) {
        lua_pushlightuserdata(L, userdata);
        return 1;
    }
};

template<>
struct pusher<userdata> {
    template<typename T, typename U = Unqualified<T>>
    static int push(lua_State* L, T&& data) {
        U* userdata = static_cast<U*>(lua_newuserdata(L, sizeof(U)));
        new(userdata)U(std::forward<T>(data));
        return 1;
    }
};

template<>
struct pusher<const char*> {
    static int push(lua_State* L, const char* str) {
        lua_pushlstring(L, str, std::char_traits<char>::length(str));
        return 1;
    }
};

template<size_t N>
struct pusher<char[N]> {
    static int push(lua_State* L, const char (&str)[N]) {
        lua_pushlstring(L, str, N - 1);
        return 1;
    }
};

template<>
struct pusher<std::string> {
    static int push(lua_State* L, const std::string& str) {
        lua_pushlstring(L, str.c_str(), str.size());
        return 1;
    }
};

template<typename... Args>
struct pusher<std::tuple<Args...>> {
    template <typename Tuple>
    static int push(lua_State* L, Tuple&& tuplen) {
        return push_tuple(L, build_indices<sizeof...(Args)>(), std::forward<Tuple>(tuplen));
    }
};

namespace detail {
template<typename T>
inline int push_as_upvalues(lua_State* L, T& item) {
    typedef typename std::decay<T>::type TValue;
    const static std::size_t itemsize = sizeof(TValue);
    const static std::size_t voidsize = sizeof(void*);
    const static std::size_t voidsizem1 = voidsize - 1;
    const static std::size_t data_t_count = (sizeof(TValue) + voidsizem1) / voidsize;
    typedef std::array<void*, data_t_count> data_t;

    data_t data{{}};
    std::memcpy(std::addressof(data[0]), std::addressof(item), itemsize);
    int pushcount = 0;
    for(auto&& v : data) {
        pushcount += push(L, upvalue(v));
    }
    return pushcount;
}

template<typename T>
inline std::pair<T, int> get_as_upvalues(lua_State* L, int index = 1) {
    const static std::size_t data_t_count = (sizeof(T)+(sizeof(void*)-1)) / sizeof(void*);
    typedef std::array<void*, data_t_count> data_t;
    data_t voiddata{ {} };
    for(std::size_t i = 0, d = 0; d < sizeof(T); ++i, d += sizeof(void*)) {
        voiddata[i] = get<upvalue>(L, index++);
    }
    return std::pair<T, int>(*reinterpret_cast<T*>(static_cast<void*>(voiddata.data())), index);
}

template <bool b>
struct check_arguments {
    template <std::size_t... I, typename... Args>
    static bool check(lua_State* L, int firstargument, indices<I...>, types<Args...>) {
        bool checks = true;
        using swallow = int[sizeof...(Args)+2];
        (void)swallow {
            0, (checks &= stack::check<Args>(L, firstargument + I))..., 0
        };
        return checks;
    }
};

template <>
struct check_arguments<false> {
    template <std::size_t... I, typename... Args>
    static bool check(lua_State*, int, indices<I...>, types<Args...>) {
        return true;
    }
};

template <bool checkargs = false, std::size_t... I, typename R, typename... Args, typename Fx, typename... FxArgs, typename = typename std::enable_if<!std::is_void<R>::value>::type>
inline R call(lua_State* L, int start, indices<I...>, types<R>, types<Args...> ta, Fx&& fx, FxArgs&&... args) {
    const int stacksize = lua_gettop(L);
    const int firstargument = static_cast<int>(start + stacksize - std::max(sizeof...(Args)-1, static_cast<std::size_t>(0)));

    detail::check_arguments<checkargs>{}.check(L, firstargument, ta, ta);

    return fx(std::forward<FxArgs>(args)..., stack::get<Args>(L, firstargument + I)...);
}

template <bool checkargs = false, std::size_t... I, typename... Args, typename Fx, typename... FxArgs>
inline void call(lua_State* L, int start, indices<I...>, types<void>, types<Args...> ta, Fx&& fx, FxArgs&&... args) {
    const int stacksize = lua_gettop(L);
    const int firstargument = static_cast<int>(start + stacksize - std::max(sizeof...(Args)-1, static_cast<std::size_t>(0)));

    bool checks = detail::check_arguments<checkargs>{}.check(L, firstargument, ta, ta);
    if ( !checks )
        throw error("Arguments not of the proper types for this function call");

    fx(std::forward<FxArgs>(args)..., stack::get<Args>(L, firstargument + I)...);
}
} // detail

template <bool checkargs = false, typename R, typename... Args, typename Fx, typename... FxArgs, typename = typename std::enable_if<!std::is_void<R>::value>::type>
inline R call(lua_State* L, int start, types<R> tr, types<Args...> ta, Fx&& fx, FxArgs&&... args) {
    return detail::call(L, start, ta, tr, ta, std::forward<Fx>(fx), std::forward<FxArgs>(args)...);
}

template <bool checkargs = false, typename R, typename... Args, typename Fx, typename... FxArgs, typename = typename std::enable_if<!std::is_void<R>::value>::type>
inline R call(lua_State* L, types<R> tr, types<Args...> ta, Fx&& fx, FxArgs&&... args) {
    return call(L, 0, ta, tr, ta, std::forward<Fx>(fx), std::forward<FxArgs>(args)...);
}

template <bool checkargs = false, typename... Args, typename Fx, typename... FxArgs>
inline void call(lua_State* L, int start, types<void> tr, types<Args...> ta, Fx&& fx, FxArgs&&... args) {
    detail::call(L, start, ta, tr, ta, std::forward<Fx>(fx), std::forward<FxArgs>(args)...);
}

template <bool checkargs = false, typename... Args, typename Fx, typename... FxArgs>
inline void call(lua_State* L, types<void> tr, types<Args...> ta, Fx&& fx, FxArgs&&... args) {
    call(L, 0, ta, tr, ta, std::forward<Fx>(fx), std::forward<FxArgs>(args)...);
}

inline call_syntax get_call_syntax(lua_State* L, const std::string& meta) {
    if (get<type>(L, 1) == type::table) {
        if (luaL_newmetatable(L, meta.c_str()) == 0) {
            lua_settop(L, -2);
            return call_syntax::colon;
        }
    }
    return call_syntax::dot;
}
} // stack
} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\stack.hpp

namespace old_sol {
class object : public reference {
public:
    object(lua_State* L, int index = -1): reference(L, index) {}
    object() = default;

    template<typename T>
    auto as() const -> decltype(stack::get<T>(state())) {
        push();
        type actual = stack::get<type>(state());
        type_assert(state(), -1, type_of<T>(), actual);
        return stack::pop<T>(state());
    }

    template<typename T>
    bool is() const {
        auto expected = type_of<T>();
        auto actual = get_type();
        return (expected == actual) || (expected == type::poly);
    }

    explicit operator bool() const {
        return !is<nil_t>();
    }
};

inline bool operator==(const object& lhs, const nil_t&) {
    return lhs.is<nil_t>();
}

inline bool operator==(const nil_t&, const object& rhs) {
    return rhs.is<nil_t>();
}

inline bool operator!=(const object& lhs, const nil_t&) {
    return !lhs.is<nil_t>();
}

inline bool operator!=(const nil_t&, const object& rhs) {
    return !rhs.is<nil_t>();
}
} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\object.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\function.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\function_types.hpp

#include <memory>
#include <unordered_map>

namespace old_sol {
namespace detail {
struct ref_call_t {
    ref_call_t() {}
};

const auto ref_call = ref_call_t{};

template<typename T, typename Func, typename = void>
struct functor {
    typedef member_traits<Func> traits_type;
    typedef typename traits_type::args_type args_type;
    typedef typename traits_type::return_type return_type;

    T* item;
    Func invocation;

    template<typename... FxArgs>
    functor(FxArgs&&... fxargs): item(nullptr), invocation(std::forward<FxArgs>(fxargs)...) {}

    bool check () const {
         return invocation != nullptr;
    }

    template<typename... Args>
    void call(types<void>, Args&&... args) {
        T& member = *item;
        (member.*invocation)(std::forward<Args>(args)...);
    }

    template<typename Ret, typename... Args>
    Ret call(types<Ret>, Args&&... args) {
        T& member = *item;
        return (member.*invocation)(std::forward<Args>(args)...);
    }

    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(std::declval<functor>().call(types<return_type>{}, std::forward<Args>(args)...)) {
        return this->call(types<return_type>{}, std::forward<Args>(args)...);
    }
};

template<typename T, typename Func>
struct functor<T, Func, typename std::enable_if<std::is_member_object_pointer<Func>::value>::type> {
    typedef member_traits<Func> traits_type;
    typedef typename traits_type::args_type args_type;
    typedef typename traits_type::return_type return_type;
    T* item;
    Func invocation;

    template<typename... FxArgs>
    functor(FxArgs&&... fxargs): item(nullptr), invocation(std::forward<FxArgs>(fxargs)...) {}

    bool check () const {
         return this->fx.invocation != nullptr;
    }

    template<typename Arg>
    void call(types<return_type>, Arg&& arg) {
        T& member = *item;
        (member.*invocation) = std::forward<Arg>(arg);
    }

    return_type call(types<return_type>) {
         T& member = *item;
         return (member.*invocation);
    }

    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(std::declval<functor>().call(types<return_type>{}, std::forward<Args>(args)...)) {
        return this->call(types<return_type>{}, std::forward<Args>(args)...);
    }
};

template<typename T, typename Func>
struct functor<T, Func, typename std::enable_if<std::is_function<Func>::value || std::is_class<Func>::value>::type> {
    typedef member_traits<Func> traits_type;
    typedef remove_one_type<typename traits_type::args_type> args_type;
    typedef typename traits_type::return_type return_type;
    typedef typename std::conditional<std::is_pointer<Func>::value || std::is_class<Func>::value, Func, typename std::add_pointer<Func>::type>::type function_type;
    T* item;
    function_type invocation;

private:
    bool check(std::false_type) const {
        return true;
    }

    bool check(std::true_type) const {
        return this->invocation != nullptr;
    }

public:

    template<typename... FxArgs>
    functor(FxArgs&&... fxargs): item(nullptr), invocation(std::forward<FxArgs>(fxargs)...) {}

    bool check () const {
         return this->check(std::is_function<Func>());
    }

    template<typename... Args>
    void call(types<void>, Args&&... args) {
        T& member = *item;
        invocation(member, std::forward<Args>(args)...);
    }

    template<typename Ret, typename... Args>
    Ret call(types<Ret>, Args&&... args) {
        T& member = *item;
        return invocation(member, std::forward<Args>(args)...);
    }

    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(std::declval<functor>().call(types<return_type>{}, std::forward<Args>(args)...)) {
        return this->call(types<return_type>{}, std::forward<Args>(args)...);
    }
};
} // detail

template<typename Function>
struct static_function {
    typedef typename std::remove_pointer<typename std::decay<Function>::type>::type function_type;
    typedef function_traits<function_type> traits_type;

    template<typename... Args>
    static int typed_call(types<void> tr, types<Args...> ta, function_type* fx, lua_State* L) {
        stack::call(L, 0, tr, ta, fx);
        std::ptrdiff_t nargs = sizeof...(Args);
        lua_pop(L, nargs);
        return 0;
    }

    template<typename... Args>
    static int typed_call(types<>, types<Args...> t, function_type* fx, lua_State* L) {
        return typed_call(types<void>(), t, fx, L);
    }

    template<typename... Ret, typename... Args>
    static int typed_call(types<Ret...>, types<Args...> ta, function_type* fx, lua_State* L) {
        typedef typename return_type<Ret...>::type return_type;
        return_type r = stack::call(L, 0, types<return_type>(), ta, fx);
        int nargs = static_cast<int>(sizeof...(Args));
        lua_pop(L, nargs);
        return stack::push(L, detail::return_forward<return_type>{}(r));
    }

    static int call(lua_State* L) {
        auto udata = stack::detail::get_as_upvalues<function_type*>(L);
        function_type* fx = udata.first;
        int r = typed_call(tuple_types<typename traits_type::return_type>(), typename traits_type::args_type(), fx, L);
        return r;
    }

    int operator()(lua_State* L) {
        return call(L);
    }
};

template<typename T, typename Function>
struct static_member_function {
    typedef typename std::remove_pointer<typename std::decay<Function>::type>::type function_type;
    typedef function_traits<function_type> traits_type;

    template<typename... Args>
    static int typed_call(types<void> tr, types<Args...> ta, T& item, function_type& ifx, lua_State* L) {
        auto fx = [&item, &ifx](Args&&... args) -> void { (item.*ifx)(std::forward<Args>(args)...); };
        stack::call(L, 0, tr, ta, fx);
        int nargs = static_cast<int>(sizeof...(Args));
        lua_pop(L, nargs);
        return 0;
    }

    template<typename... Args>
    static int typed_call(types<>, types<Args...> t, T& item, function_type& ifx, lua_State* L) {
        return typed_call(types<void>(), t, item, ifx, L);
    }

    template<typename... Ret, typename... Args>
    static int typed_call(types<Ret...> tr, types<Args...> ta, T& item, function_type& ifx, lua_State* L) {
        typedef typename return_type<Ret...>::type return_type;
        auto fx = [&item, &ifx](Args&&... args) -> return_type { return (item.*ifx)(std::forward<Args>(args)...); };
        return_type r = stack::call(L, 0, tr, ta, fx);
        int nargs = static_cast<int>(sizeof...(Args));
        lua_pop(L, nargs);
        return stack::push(L, detail::return_forward<return_type>{}(r));
    }

    static int call(lua_State* L) {
        auto memberdata = stack::detail::get_as_upvalues<function_type>(L, 1);
        auto objdata = stack::detail::get_as_upvalues<T*>(L, memberdata.second);
        function_type& memfx = memberdata.first;
        T& obj = *objdata.first;
        int r = typed_call(tuple_types<typename traits_type::return_type>(), typename traits_type::args_type(), obj, memfx, L);
        return r;
    }

    int operator()(lua_State* L) {
        return call(L);
    }
};

struct base_function {
    static int base_call(lua_State* L, void* inheritancedata) {
        if(inheritancedata == nullptr) {
            throw error("call from Lua to C++ function has null data");
        }

        base_function* pfx = static_cast<base_function*>(inheritancedata);
        base_function& fx = *pfx;
        int r = fx(L);
        return r;
    }

    static int ref_base_call(lua_State* L, void* inheritancedata) {
        if(inheritancedata == nullptr) {
            throw error("call from Lua to C++ function has null data");
        }

        base_function* pfx = static_cast<base_function*>(inheritancedata);
        base_function& fx = *pfx;
        int r = fx(L, detail::ref_call);
        return r;
    }

    static int base_gc(lua_State*, void* udata) {
        if(udata == nullptr) {
            throw error("call from lua to C++ gc function with null data");
        }

        base_function* ptr = static_cast<base_function*>(udata);
        std::default_delete<base_function> dx{};
        dx(ptr);
        return 0;
    }

    static int call(lua_State* L) {
        void** pinheritancedata = static_cast<void**>(stack::get<upvalue>(L, 1).value);
        return base_call(L, *pinheritancedata);
    }

    static int gc(lua_State* L) {
        void** pudata = static_cast<void**>(stack::get<userdata>(L, 1).value);
        return base_gc(L, *pudata);
    }

    template<std::size_t I>
    struct usertype {
        static int call(lua_State* L) {
            // Zero-based template parameter, but upvalues start at 1
            return base_call(L, stack::get<upvalue>(L, I + 1));
        }

        static int ref_call(lua_State* L) {
            return ref_base_call(L, stack::get<upvalue>(L, I + 1));
        }

        template <std::size_t limit>
        static void func_gc (std::true_type, lua_State*) {

        }

        template <std::size_t limit>
        static void func_gc (std::false_type, lua_State* L) {
            // Shut up clang tautological error without throwing out std::size_t
            for(std::size_t i = 0; i < limit; ++i) {
                upvalue up = stack::get<upvalue>(L, static_cast<int>(i + 1));
                base_function* obj = static_cast<base_function*>(up.value);
                std::allocator<base_function> alloc{};
                alloc.destroy(obj);
                alloc.deallocate(obj, 1);
            }
        }

        static int gc(lua_State* L) {
            func_gc<I>(std::integral_constant<bool, (I < 1)>(), L);
            return 0;
        }
    };

    virtual int operator()(lua_State*) {
        throw error("failure to call specialized wrapped C++ function from Lua");
    }

    virtual int operator()(lua_State*, detail::ref_call_t) {
        throw error("failure to call reference specialized wrapped C++ function from Lua");
    }

    virtual ~base_function() {}
};

template<typename Function>
struct functor_function : public base_function {
    typedef decltype(&Function::operator()) function_type;
    typedef function_return_t<function_type> return_type;
    typedef function_args_t<function_type> args_type;
    Function fx;

    template<typename... FxArgs>
    functor_function(FxArgs&&... fxargs): fx(std::forward<FxArgs>(fxargs)...) {}

    template<typename... Args>
    int operator()(types<void> r, types<Args...> t, lua_State* L) {
        stack::call(L, 0, r, t, fx);
        int nargs = static_cast<int>(sizeof...(Args));
        lua_pop(L, nargs);
        return 0;
    }

    template<typename... Args>
    int operator()(types<>, types<Args...> t, lua_State* L) {
        return (*this)(types<void>(), t, L);
    }

    template<typename... Ret, typename... Args>
    int operator()(types<Ret...> tr, types<Args...> ta, lua_State* L) {
        return_type r = stack::call(L, 0, tr, ta, fx);
        int nargs = static_cast<int>(sizeof...(Args));
        lua_pop(L, nargs);
        return stack::push(L, r);
    }

    virtual int operator()(lua_State* L) override {
        return (*this)(tuple_types<return_type>(), args_type(), L);
    }

    virtual int operator()(lua_State* L, detail::ref_call_t) override {
        return (*this)(tuple_types<return_type>(), args_type(), L);
    }
};

template<typename Function, typename T>
struct member_function : public base_function {
    typedef typename std::remove_pointer<Decay<Function>>::type function_type;
    typedef function_return_t<function_type> return_type;
    typedef function_args_t<function_type> args_type;
    struct functor {
        T member;
        function_type invocation;

        template<typename Tm, typename... FxArgs>
        functor(Tm&& m, FxArgs&&... fxargs): member(std::forward<Tm>(m)), invocation(std::forward<FxArgs>(fxargs)...) {}

        template<typename... Args>
        return_type operator()(Args&&... args) {
           return (member.*invocation)(std::forward<Args>(args)...);
        }
    } fx;

    template<typename Tm, typename... FxArgs>
    member_function(Tm&& m, FxArgs&&... fxargs): fx(std::forward<Tm>(m), std::forward<FxArgs>(fxargs)...) {}

    template<typename... Args>
    int operator()(types<void> tr, types<Args...> ta, lua_State* L) {
        stack::call(L, 0, tr, ta, fx);
        return 0;
    }

    template<typename... Args>
    int operator()(types<>, types<Args...> t, lua_State* L) {
        return (*this)(types<void>(), t, L);
    }

    template<typename... Ret, typename... Args>
    int operator()(types<Ret...> tr, types<Args...> ta, lua_State* L) {
        return_type r = stack::call(L, 0, tr, ta, fx);
        int nargs = static_cast<int>(sizeof...(Args));
        lua_pop(L, nargs);
        return stack::push(L, detail::return_forward<return_type>{}(r));
    }

    virtual int operator()(lua_State* L) override {
        return (*this)(tuple_types<return_type>(), args_type(), L);
    }

    virtual int operator()(lua_State* L, detail::ref_call_t) override {
        return (*this)(tuple_types<return_type>(), args_type(), L);
    }
};

template<typename Function, typename Tp>
struct usertype_function_core : public base_function {
    typedef typename std::remove_pointer<Tp>::type T;
    typedef typename std::remove_pointer<typename std::decay<Function>::type>::type function_type;
    typedef detail::functor<T, function_type> fx_t;
    typedef typename fx_t::traits_type traits_type;
    typedef typename fx_t::args_type args_type;
    typedef typename fx_t::return_type return_type;

    fx_t fx;

    template<typename... FxArgs>
    usertype_function_core(FxArgs&&... fxargs): fx(std::forward<FxArgs>(fxargs)...) {}

    template<typename Return, typename Raw = Unqualified<Return>>
    typename std::enable_if<std::is_same<T, Raw>::value, int>::type push(lua_State* L, Return&& r) {
        if(detail::get_ptr(r) == fx.item) {
            // push nothing
            // note that pushing nothing with the ':'
            // syntax means we leave the instance of what
            // was pushed onto the stack by lua to do the
            // function call alone,
            // and naturally lua returns that.
            // It's an "easy" way to return *this,
            // without allocating an extra userdata, apparently!
            return 1;
        }
        return stack::push(L, std::forward<Return>(r));
    }

    template<typename Return, typename Raw = Unqualified<Return>>
    typename std::enable_if<!std::is_same<T, Raw>::value, int>::type push(lua_State* L, Return&& r) {
        return stack::push(L, std::forward<Return>(r));
    }

    template<typename... Args>
    int call(types<void> r, types<Args...> t, lua_State* L) {
        //static const std::size_t skew = static_cast<std::size_t>(std::is_member_object_pointer<function_type>::value);
        stack::call(L, 0, r, t, fx);
        int nargs = static_cast<int>(sizeof...(Args));
        lua_pop(L, nargs);
        return 0;
    }

    template<typename... Args>
    int call(types<>, types<Args...> t, lua_State* L) {
         return this->call(types<void>(), t, L);
    }

    template<typename... Ret, typename... Args>
    int call(types<Ret...> tr, types<Args...> ta, lua_State* L) {
        return_type r = stack::call(L, 0, tr, ta, fx);
        int nargs = static_cast<int>(sizeof...(Args));
        lua_pop(L, nargs);
        int pushcount = push(L, detail::return_forward<return_type>{}(r));
        return pushcount;
    }

    template<typename... Ret, typename... Args>
    int operator()(types<Ret...> r, types<Args...> t, lua_State* L) {
         return this->call(r, t, L);
    }
};

template<typename Function, typename Tp>
struct usertype_function : public usertype_function_core<Function, Tp> {
    typedef usertype_function_core<Function, Tp> base_t;
    typedef typename std::remove_pointer<Tp>::type T;
    typedef typename base_t::traits_type traits_type;
    typedef typename base_t::args_type args_type;
    typedef typename base_t::return_type return_type;

    template<typename... FxArgs>
    usertype_function(FxArgs&&... fxargs): base_t(std::forward<FxArgs>(fxargs)...) {}

    template<typename Tx>
    int fx_call(lua_State* L) {
        this->fx.item = detail::get_ptr(stack::get<Tx>(L, 1));
        if(this->fx.item == nullptr) {
            throw error("userdata for function call is null: are you using the wrong syntax? (use item:function/variable(...) syntax)");
        }
        return static_cast<base_t&>(*this)(tuple_types<return_type>(), args_type(), L);
    }

    virtual int operator()(lua_State* L) override {
        return fx_call<T>(L);
    }

    virtual int operator()(lua_State* L, detail::ref_call_t) override {
        return fx_call<T*>(L);
    }
};

template<typename Function, typename Tp>
struct usertype_variable_function : public usertype_function_core<Function, Tp> {
    typedef usertype_function_core<Function, Tp> base_t;
    typedef typename std::remove_pointer<Tp>::type T;
    typedef typename base_t::traits_type traits_type;
    typedef typename base_t::args_type args_type;
    typedef typename base_t::return_type return_type;

    template<typename... FxArgs>
    usertype_variable_function(FxArgs&&... fxargs): base_t(std::forward<FxArgs>(fxargs)...) {}

    template<typename Tx>
    int fx_call(lua_State* L) {
        this->fx.item = detail::get_ptr(stack::get<Tx>(L, 1));
        if(this->fx.item == nullptr) {
            throw error("userdata for member variable is null");
        }

        int argcount = lua_gettop(L);
        switch(argcount) {
        case 2:
            return static_cast<base_t&>(*this)(tuple_types<return_type>(), types<>(), L);
        case 3:
            return static_cast<base_t&>(*this)(tuple_types<void>(), args_type(), L);
        default:
            throw error("cannot get/set userdata member variable with inappropriate number of arguments");
        }

    }

    virtual int operator()(lua_State* L) override {
        return fx_call<T>(L);
    }

    virtual int operator()(lua_State* L, detail::ref_call_t) override {
        return fx_call<T*>(L);
    }
};

template<typename Function, typename Tp>
struct usertype_indexing_function : public usertype_function_core<Function, Tp> {
    typedef usertype_function_core<Function, Tp> base_t;
    typedef typename std::remove_pointer<Tp>::type T;
    typedef typename base_t::traits_type traits_type;
    typedef typename base_t::args_type args_type;
    typedef typename base_t::return_type return_type;

    std::string name;
    std::unordered_map<std::string, std::pair<std::unique_ptr<base_function>, bool>> functions;

    template<typename... FxArgs>
    usertype_indexing_function(std::string name, FxArgs&&... fxargs): base_t(std::forward<FxArgs>(fxargs)...), name(std::move(name)) {}

    template<typename Tx>
    int fx_call(lua_State* L) {
        std::string accessor = stack::get<std::string>(L, 1 - lua_gettop(L));
        auto function = functions.find(accessor);
        if(function != functions.end()) {
            if(function->second.second) {
                stack::push<upvalue>(L, function->second.first.get());
                if(std::is_same<T*, Tx>::value) {
                    stack::push(L, &base_function::usertype<0>::ref_call, 1);
                }
                else {
                    stack::push(L, &base_function::usertype<0>::call, 1);
                }
                return 1;
            }
            else if(std::is_same<T*, Tx>::value) {
                return (*function->second.first)(L, detail::ref_call);
            }
            else {
                return (*function->second.first)(L);
            }
        }
        if (!this->fx.check()) {
            throw error("invalid indexing \"" + accessor + "\" on type: " + name);
        }
        this->fx.item = detail::get_ptr(stack::get<Tx>(L, 1));
        return static_cast<base_t&>(*this)(tuple_types<return_type>(), args_type(), L);
    }

    virtual int operator()(lua_State* L) override {
        return fx_call<T>(L);
    }

    virtual int operator()(lua_State* L, detail::ref_call_t) override {
        return fx_call<T*>(L);
    }
};

} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\function_types.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\resolve.hpp

namespace old_sol {
namespace detail {
template<typename R, typename... Args, typename F, typename = typename std::result_of<Unqualified<F>(Args...)>::type>
inline auto resolve_i(types<R(Args...)>, F&&) -> R(Unqualified<F>::*)(Args...) {
    using Sig = R(Args...);
    typedef Unqualified<F> Fu;
    return static_cast<Sig Fu::*>(&Fu::operator());
}

template<typename F, typename U = Unqualified<F>>
inline auto resolve_f(std::true_type, F&& f)
-> decltype(resolve_i(types<function_signature_t<decltype(&U::operator())>>(), std::forward<F>(f))) {
    return resolve_i(types<function_signature_t<decltype(&U::operator())>>(), std::forward<F>(f));
}

template<typename F>
inline void resolve_f(std::false_type, F&&) {
    static_assert(has_deducible_signature<F>::value,
                  "Cannot use no-template-parameter call with an overloaded functor: specify the signature");
}

template<typename F, typename U = Unqualified<F>>
inline auto resolve_i(types<>, F&& f) -> decltype(resolve_f(has_deducible_signature<U> {}, std::forward<F>(f))) {
    return resolve_f(has_deducible_signature<U> {}, std::forward<F>(f));
}

template<typename... Args, typename F, typename R = typename std::result_of<F&(Args...)>::type>
inline auto resolve_i(types<Args...>, F&& f) -> decltype( resolve_i(types<R(Args...)>(), std::forward<F>(f))) {
    return resolve_i(types<R(Args...)>(), std::forward<F>(f));
}

template<typename Sig, typename C>
inline Sig C::* resolve_v(std::false_type, Sig C::* mem_func_ptr) {
    return mem_func_ptr;
}

template<typename Sig, typename C>
inline Sig C::* resolve_v(std::true_type, Sig C::* mem_variable_ptr) {
    return mem_variable_ptr;
}
} // detail

template<typename... Args, typename R>
inline auto resolve(R fun_ptr(Args...)) -> R(*)(Args...) {
    return fun_ptr;
}

template<typename Sig>
inline Sig* resolve(Sig* fun_ptr) {
    return fun_ptr;
}

template<typename... Args, typename R, typename C>
inline auto resolve(R(C::*mem_ptr)(Args...)) -> R(C::*)(Args...) {
    return mem_ptr;
}

template<typename Sig, typename C>
inline Sig C::* resolve(Sig C::* mem_ptr) {
    return detail::resolve_v(std::is_member_object_pointer<Sig C::*>(), mem_ptr);
}

template<typename... Sig, typename F>
inline auto resolve(F&& f) -> decltype(detail::resolve_i(types<Sig...>(), std::forward<F>(f))) {
    return detail::resolve_i(types<Sig...>(), std::forward<F>(f));
}
} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\resolve.hpp

#include <cstdint>

namespace old_sol {
class function : public reference {
private:
    void luacall(std::size_t argcount, std::size_t resultcount) const {
        lua_call(state(), static_cast<uint32_t>(argcount), static_cast<uint32_t>(resultcount));
    }

    template<std::size_t... I, typename... Ret>
    std::tuple<Ret...> invoke(indices<I...>, types<Ret...>, std::size_t n) const {
        luacall(n, sizeof...(Ret));
        const int nreturns = static_cast<int>(sizeof...(Ret));
        const int stacksize = lua_gettop(state());
        const int firstreturn = std::max(0, stacksize - nreturns) + 1;
        auto r = std::make_tuple(stack::get<Ret>(state(), firstreturn + I)...);
        lua_pop(state(), nreturns);
        return r;
    }

    template<std::size_t I, typename Ret>
    Ret invoke(indices<I>, types<Ret>, std::size_t n) const {
        luacall(n, 1);
        return stack::pop<Ret>(state());
    }

    template <std::size_t I>
    void invoke(indices<I>, types<void>, std::size_t n) const {
        luacall(n, 0);
    }

    void invoke(indices<>, types<>, std::size_t n) const {
        auto tr = types<void>();
        invoke(tr, tr, n);
    }

public:
    function() = default;
    function(lua_State* L, int index = -1): reference(L, index) {
        type_assert(L, index, type::function);
    }
    function(const function&) = default;
    function& operator=(const function&) = default;

    template<typename... Args>
    void operator()(Args&&... args) const {
        call<>(std::forward<Args>(args)...);
    }

    template<typename... Ret, typename... Args>
    typename return_type<Ret...>::type operator()(types<Ret...>, Args&&... args) const {
        return call<Ret...>(std::forward<Args>(args)...);
    }

    template<typename... Ret, typename... Args>
    typename return_type<Ret...>::type call(Args&&... args) const {
        push();
        int pushcount = stack::push_args(state(), std::forward<Args>(args)...);
        auto tr = types<Ret...>();
        return invoke(tr, tr, pushcount);
    }
};

namespace stack {
template<typename... Sigs>
struct pusher<function_sig_t<Sigs...>> {

    template<typename R, typename... Args, typename Fx, typename = typename std::result_of<Fx(Args...)>::type>
    static void set_memfx(types<R(Args...)> t, lua_State* L, Fx&& fx) {
        typedef Decay<Unwrap<Fx>> raw_fx_t;
        typedef R(* fx_ptr_t)(Args...);
        typedef std::is_convertible<raw_fx_t, fx_ptr_t> is_convertible;
        set_isconvertible_fx(is_convertible(), t, L, std::forward<Fx>(fx));
    }

    template<typename Fx>
    static void set_memfx(types<>, lua_State* L, Fx&& fx) {
        typedef Unqualified<Unwrap<Fx>> fx_t;
        typedef decltype(&fx_t::operator()) Sig;
        set_memfx(types<function_signature_t<Sig>>(), L, std::forward<Fx>(fx));
    }

    template<typename... Args, typename R>
    static void set(lua_State* L, R fxptr(Args...)){
        set_fx(std::false_type(), L, fxptr);
    }

    template<typename Sig>
    static void set(lua_State* L, Sig* fxptr){
       set_fx(std::false_type(), L, fxptr);
    }

    template<typename... Args, typename R, typename C, typename T>
    static void set(lua_State* L, R (C::*memfxptr)(Args...), T&& obj) {
        typedef Bool<is_specialization_of<T, std::reference_wrapper>::value || std::is_pointer<T>::value> is_reference;
        set_reference_fx(is_reference(), L, memfxptr, std::forward<T>(obj));
    }

    template<typename Sig, typename C, typename T>
    static void set(lua_State* L, Sig C::* memfxptr, T&& obj) {
        typedef Bool<is_specialization_of<T, std::reference_wrapper>::value || std::is_pointer<T>::value> is_reference;
        set_reference_fx(is_reference(), L, memfxptr, std::forward<T>(obj));
    }

    template<typename... Sig, typename Fx>
    static void set(lua_State* L, Fx&& fx) {
        set_memfx(types<Sig...>(), L, std::forward<Fx>(fx));
    }

    template<typename Fx, typename R, typename... Args>
    static void set_isconvertible_fx(std::true_type, types<R(Args...)>, lua_State* L, Fx&& fx) {
        typedef R(* fx_ptr_t)(Args...);
        fx_ptr_t fxptr = unwrapper(std::forward<Fx>(fx));
        set(L, fxptr);
    }

    template<typename Fx, typename R, typename... Args>
    static void set_isconvertible_fx(std::false_type, types<R(Args...)>, lua_State* L, Fx&& fx) {
        typedef Decay<Unwrap<Fx>> fx_t;
        std::unique_ptr<base_function> sptr(new functor_function<fx_t>(std::forward<Fx>(fx)));
        set_fx<Fx>(L, std::move(sptr));
    }

    template<typename Fx, typename T>
    static void set_reference_fx(std::true_type, lua_State* L, Fx&& fx, T&& obj) {
        set_fx(std::true_type(), L, std::forward<Fx>(fx), std::forward<T>(obj));
    }

    template<typename Fx, typename T>
    static void set_reference_fx(std::false_type, lua_State* L, Fx&& fx, T&& obj) {
        typedef typename std::remove_pointer<Decay<Fx>>::type clean_fx;
        std::unique_ptr<base_function> sptr(new member_function<clean_fx, T>(std::forward<T>(obj), std::forward<Fx>(fx)));
        return set_fx<Fx>(L, std::move(sptr));
    }

    template<typename Fx, typename T>
    static void set_fx(std::true_type, lua_State* L, Fx&& fx, T&& obj) {
        // Layout:
        // idx 1...n: verbatim data of member function pointer
        // idx n + 1: is the object's void pointer
        // We don't need to store the size, because the other side is templated
        // with the same member function pointer type
        Decay<Fx> memfxptr(std::forward<Fx>(fx));
        auto userptr = old_sol::detail::get_ptr(obj);
        void* userobjdata = static_cast<void*>(userptr);
        lua_CFunction freefunc = &static_member_function<Decay<decltype(*userptr)>, Fx>::call;

        int upvalues = stack::detail::push_as_upvalues(L, memfxptr);
        upvalues += stack::push(L, userobjdata);

        stack::push(L, freefunc, upvalues);
    }

    template<typename Fx>
    static void set_fx(std::false_type, lua_State* L, Fx&& fx) {
        Decay<Fx> target(std::forward<Fx>(fx));
        lua_CFunction freefunc = &static_function<Fx>::call;

        int upvalues = stack::detail::push_as_upvalues(L, target);
        stack::push(L, freefunc, upvalues);
    }

    template<typename Fx>
    static void set_fx(lua_State* L, std::unique_ptr<base_function> luafunc) {
        auto&& metakey = usertype_traits<Unqualified<Fx>>::metatable;
        const char* metatablename = std::addressof(metakey[0]);
        base_function* target = luafunc.release();
        void* userdata = reinterpret_cast<void*>(target);
        lua_CFunction freefunc = &base_function::call;

        if(luaL_newmetatable(L, metatablename) == 1) {
            lua_pushstring(L, "__gc");
            stack::push(L, &base_function::gc);
            lua_settable(L, -3);
            lua_pop(L, 1);
        }

        stack::detail::push_userdata<void*>(L, metatablename, userdata);
        stack::push(L, freefunc, 1);
    }

    template<typename... Args>
    static int push(lua_State* L, Args&&... args) {
        // Set will always place one thing (function) on the stack
        set(L, std::forward<Args>(args)...);
        return 1;
    }
};

template<typename Signature>
struct pusher<std::function<Signature>> {
    static int push(lua_State* L, std::function<Signature> fx) {
        return pusher<function_t>{}.push(L, std::move(fx));
    }
};

template<typename Signature>
struct getter<std::function<Signature>> {
    typedef function_traits<Signature> fx_t;
    typedef typename fx_t::args_type args_t;
    typedef typename tuple_types<typename fx_t::return_type>::type ret_t;

    template<typename... FxArgs, typename... Ret>
    static std::function<Signature> get_std_func(types<FxArgs...>, types<Ret...>, lua_State* L, int index = -1) {
        typedef typename function_traits<Signature>::return_type return_t;
        old_sol::function f(L, index);
        auto fx = [f, L, index](FxArgs&&... args) -> return_t {
            return f(types<Ret...>(), std::forward<FxArgs>(args)...);
        };
        return std::move(fx);
    }

    template<typename... FxArgs>
    static std::function<Signature> get_std_func(types<FxArgs...>, types<void>, lua_State* L, int index = -1) {
        old_sol::function f(L, index);
        auto fx = [f, L, index](FxArgs&&... args) -> void {
            f(std::forward<FxArgs>(args)...);
        };
        return std::move(fx);
    }

    template<typename... FxArgs>
    static std::function<Signature> get_std_func(types<FxArgs...> t, types<>, lua_State* L, int index = -1) {
        return get_std_func(std::move(t), types<void>(), L, index);
    }

    static std::function<Signature> get(lua_State* L, int index) {
        return get_std_func(args_t(), ret_t(), L, index);
    }
};
} // stack
} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\function.hpp

namespace old_sol {
template<typename Table, typename Key>
struct proxy {
private:
    Table& tbl;
    Key& key;

public:

    template<typename T>
    proxy(Table& table, T&& key) : tbl(table), key(std::forward<T>(key)) {}

    template<typename T>
    T get() const {
        return tbl.template get<T>(key);
    }

    template<typename T>
    proxy& set(T&& item) {
        tbl.set(key, std::forward<T>(item));
        return *this;
    }

    template<typename... Args>
    proxy& set_function(Args&&... args) {
        tbl.set_function(key, std::forward<Args>(args)...);
        return *this;
    }

    template<typename U, EnableIf<Function<Unqualified<U>>> = 0>
    void operator=(U&& other) {
        tbl.set_function(key, std::forward<U>(other));
    }

    template<typename U, DisableIf<Function<Unqualified<U>>> = 0>
    void operator=(U&& other) {
        tbl.set(key, std::forward<U>(other));
    }

    operator nil_t() const {
        return get<nil_t>();
    }

    operator object() const {
        return get<object>();
    }

    operator function() const {
        return get<function>();
    }

    operator Unqualified<Table>() const {
        return get<Unqualified<Table>>();
    }

    operator std::string() const {
        return get<std::string>();
    }

    template<typename T = void>
    operator bool() const {
        return get<bool>();
    }

    template<typename T = void>
    operator double() const {
        return get<double>();
    }

    template<typename T = void>
    operator float() const {
        return get<float>();
    }

    template<typename T = void>
    operator int() const {
        return get<int>();
    }

    template<typename... Ret, typename... Args>
    typename return_type<Ret...>::type call(Args&&... args) {
        return tbl.template get<function>(key)(types<Ret...>(), std::forward<Args>(args)...);
    }
};

template<typename Table, typename Key, typename T>
inline bool operator==(T&& left, const proxy<Table, Key>& right) {
    return left == right.template get<Decay<T>>();
}

template<typename Table, typename Key, typename T>
inline bool operator==(const proxy<Table, Key>& right, T&& left) {
    return right.template get<Decay<T>>() == left;
}

template<typename Table, typename Key, typename T>
inline bool operator!=(T&& left, const proxy<Table, Key>& right) {
    return right.template get<Decay<T>>() != left;
}

template<typename Table, typename Key, typename T>
inline bool operator!=(const proxy<Table, Key>& right, T&& left) {
    return right.template get<Decay<T>>() != left;
}
} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\proxy.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\usertype.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\default_construct.hpp

namespace old_sol {
struct default_construct {
    template<typename T, typename... Args>
    void operator()(T&& obj, Args&&... args) const {
        std::allocator<Unqualified<T>> alloc{};
        alloc.construct(obj, std::forward<Args>(args)...);
    }
};

template <typename T>
struct placement_construct {
    T obj;

    template <typename... Args>
    placement_construct( Args&&... args ) : obj(std::forward<Args>(args)...) {

    }

    template<typename... Args>
    void operator()(Args&&... args) const {
        std::allocator<Unqualified<T>> alloc{};
        alloc.construct(obj, std::forward<Args>(args)...);
    }
};

} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\default_construct.hpp

// beginning of C:\Users\Rig\Desktop\sol\sol\deprecate.hpp

#ifndef SOL_DEPRECATED
    #ifdef _MSC_VER
        #define SOL_DEPRECATED __declspec(deprecated)
    #elif __GNUC__
        #define SOL_DEPRECATED __attribute__((deprecated))
    #else
        #define SOL_DEPRECATED [[deprecated]]
    #endif // compilers
#endif // SOL_DEPRECATED

namespace old_sol {
namespace detail {
   template <typename T>
   struct SOL_DEPRECATED deprecate_type {
       using type = T;
   };
} // detail
} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\deprecate.hpp

#include <vector>
#include <algorithm>

namespace old_sol {
namespace detail {
template<typename T, typename... Args>
inline std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
} // detail

const std::array<std::string, 2> meta_variable_names = {{
    "__index",
    "__newindex"
}};

const std::array<std::string, 19> meta_function_names = {{
    "__index",
    "__newindex",
    "__mode",
    "__call",
    "__metatable",
    "__tostring",
    "__len",
    "__unm",
    "__add",
    "__sub",
    "__mul",
    "__div",
    "__mod",
    "__pow",
    "__concat",
    "__eq",
    "__lt",
    "__le",
    "__gc",
}};

enum class meta_function {
    index,
    new_index,
    mode,
    call,
    metatable,
    to_string,
    length,
    unary_minus,
    addition,
    subtraction,
    multiplication,
    division,
    modulus,
    power_of,
    involution = power_of,
    concatenation,
    equal_to,
    less_than,
    less_than_or_equal_to,
};

template<typename T>
class usertype {
private:
    typedef std::unordered_map<std::string, std::pair<std::unique_ptr<base_function>, bool>> function_map_t;
    function_map_t indexmetafunctions, newindexmetafunctions;
    std::vector<std::string> functionnames;
    std::vector<std::unique_ptr<base_function>> metafunctions;
    std::vector<luaL_Reg> metafunctiontable;
    std::vector<luaL_Reg> ptrmetafunctiontable;
    lua_CFunction cleanup;

    template<typename... TTypes>
    struct constructor {
        template<typename... Args>
        static void do_constructor(lua_State* L, T* obj, call_syntax syntax, int, types<Args...>) {
            default_construct fx{};
            stack::call(L, -1 + static_cast<int>(syntax), types<void>(), types<Args...>(), fx, obj);
        }

        static void match_constructor(lua_State*, T*, call_syntax, int) {
            throw error("No matching constructor for the arguments provided");
        }

        template<typename ...CArgs, typename... Args>
        static void match_constructor(lua_State* L, T* obj, call_syntax syntax, int argcount, types<CArgs...> t, Args&&... args) {
            if(argcount == sizeof...(CArgs)) {
                do_constructor(L, obj, syntax, argcount, t);
                return;
            }
            match_constructor(L, obj, syntax, argcount, std::forward<Args>(args)...);
        }

        static int construct(lua_State* L) {
            auto&& meta = usertype_traits<T>::metatable;
            call_syntax syntax = stack::get_call_syntax(L, meta);
            int argcount = lua_gettop(L);

            void* udata = lua_newuserdata(L, sizeof(T));
            T* obj = static_cast<T*>(udata);
            match_constructor(L, obj, syntax, argcount - static_cast<int>(syntax), typename identity<TTypes>::type()...);

            if(luaL_newmetatable(L, std::addressof(meta[0])) == 1) {
                lua_pop(L, 1);
                std::string err = "Unable to get usertype metatable for ";
                err += meta;
                throw error(err);
            }
            lua_setmetatable(L, -2);

            return 1;
        }
    };

    struct destructor {
        static int destruct(lua_State* L) {
            userdata udata = stack::get<userdata>(L, 1);
            T* obj = static_cast<T*>(udata.value);
            std::allocator<T> alloc{};
            alloc.destroy(obj);
            return 0;
        }
    };

    template<std::size_t N>
    void build_cleanup() {
        cleanup = &base_function::usertype<N>::gc;
    }

    template<std::size_t N>
    void build_function_tables(function_map_t*& index, function_map_t*& newindex) {
        int extracount = 0;
        if(!indexmetafunctions.empty()) {
            if(index == nullptr) {
                auto idxptr = detail::make_unique<usertype_indexing_function<void (T::*)(), T>>("__index", nullptr);
                index = &(idxptr->functions);
                functionnames.emplace_back("__index");
                metafunctions.emplace_back(std::move(idxptr));
                std::string& name = functionnames.back();
                metafunctiontable.push_back({ name.c_str(), &base_function::usertype<N>::call });
                ptrmetafunctiontable.push_back({ name.c_str(), &base_function::usertype<N>::ref_call });
                ++extracount;
            }
            auto& idx = *index;
            for(auto&& namedfunc : indexmetafunctions) {
                idx.emplace(std::move(namedfunc.first), std::move(namedfunc.second));
            }
        }
        if(!newindexmetafunctions.empty()) {
            if(newindex == nullptr) {
                auto idxptr = detail::make_unique<usertype_indexing_function<void (T::*)(), T>>("__newindex", nullptr);
                newindex = &(idxptr->functions);
                functionnames.emplace_back("__newindex");
                metafunctions.emplace_back(std::move(idxptr));
                std::string& name = functionnames.back();
                if(extracount > 0) {
                    metafunctiontable.push_back({ name.c_str(), &base_function::usertype<N + 1>::call });
                    ptrmetafunctiontable.push_back({ name.c_str(), &base_function::usertype<N + 1>::ref_call });
                }
                else {
                    metafunctiontable.push_back({ name.c_str(), &base_function::usertype<N>::call });
                    ptrmetafunctiontable.push_back({ name.c_str(), &base_function::usertype<N>::ref_call });
                }
                ++extracount;
            }
            auto& idx = *newindex;
            for(auto&& namedfunc : newindexmetafunctions) {
                idx.emplace(std::move(namedfunc.first), std::move(namedfunc.second));
            }
        }
        switch(extracount) {
        case 2:
            build_cleanup<N + 2>();
            break;
        case 1:
            build_cleanup<N + 1>();
            break;
        case 0:
        default:
            build_cleanup<N + 0>();
            break;
        }
    }

    template<std::size_t N, typename Base, typename Ret>
    bool build_function(std::true_type, function_map_t*&, function_map_t*&, std::string funcname, Ret Base::* func) {
        static_assert(std::is_base_of<Base, T>::value, "Any registered function must be part of the class");
        typedef typename std::decay<decltype(func)>::type function_type;
        indexmetafunctions.emplace(funcname, std::make_pair(detail::make_unique<usertype_variable_function<function_type, T>>(func), false));
        newindexmetafunctions.emplace(funcname, std::make_pair(detail::make_unique<usertype_variable_function<function_type, T>>(func), false));
        return false;
    }

    template<typename Arg, typename... Args, typename Ret>
    std::unique_ptr<base_function> make_function(const std::string&, Ret(*func)(Arg, Args...)) {
        typedef Unqualified<Arg> Argu;
        static_assert(std::is_base_of<Argu, T>::value, "Any non-member-function must have a first argument which is covariant with the desired userdata type.");
        typedef typename std::decay<decltype(func)>::type function_type;
        return detail::make_unique<usertype_function<function_type, T>>(func);
    }

    template<typename Base, typename Ret>
    std::unique_ptr<base_function> make_variable_function(std::true_type, const std::string&, Ret Base::* func) {
        static_assert(std::is_base_of<Base, T>::value, "Any registered function must be part of the class");
        typedef typename std::decay<decltype(func)>::type function_type;
        return detail::make_unique<usertype_variable_function<function_type, T>>(func);
    }

    template<typename Base, typename Ret>
    std::unique_ptr<base_function> make_variable_function(std::false_type, const std::string&, Ret Base::* func) {
        static_assert(std::is_base_of<Base, T>::value, "Any registered function must be part of the class");
        typedef typename std::decay<decltype(func)>::type function_type;
        return detail::make_unique<usertype_function<function_type, T>>(func);
    }

    template<typename Base, typename Ret>
    std::unique_ptr<base_function> make_function(const std::string& name, Ret Base::* func) {
        typedef typename std::decay<decltype(func)>::type function_type;
        return make_variable_function(std::is_member_object_pointer<function_type>(), name, func);
    }

    template<typename Fx>
    std::unique_ptr<base_function> make_function(const std::string&, Fx&& func) {
        typedef Unqualified<Fx> Fxu;
        typedef typename std::tuple_element<0, typename function_traits<Fxu>::arg_tuple_type>::type TArg;
        typedef Unqualified<TArg> TArgu;
        static_assert(std::is_base_of<TArgu, T>::value, "Any non-member-function must have a first argument which is covariant with the desired userdata type.");
        typedef typename std::decay<decltype(func)>::type function_type;
        return detail::make_unique<usertype_function<function_type, T>>(func);
    }

    template<std::size_t N, typename Fx>
    bool build_function(std::false_type, function_map_t*& index, function_map_t*& newindex, std::string funcname, Fx&& func) {
        typedef typename std::decay<Fx>::type function_type;
        auto metamethod = std::find(meta_function_names.begin(), meta_function_names.end(), funcname);
        if(metamethod != meta_function_names.end()) {
            functionnames.push_back(std::move(funcname));
            std::string& name = functionnames.back();
            auto indexmetamethod = std::find(meta_variable_names.begin(), meta_variable_names.end(), name);
            std::unique_ptr<base_function> ptr(nullptr);
            if(indexmetamethod != meta_variable_names.end()) {
                auto idxptr = detail::make_unique<usertype_indexing_function<function_type, T>>(name, func);
                switch(std::distance(indexmetamethod, meta_variable_names.end())) {
                case 0:
                    index = &(idxptr->functions);
                    break;
                case 1:
                    newindex = &(idxptr->functions);
                    break;
                default:
                    break;
                }
                ptr = std::move(idxptr);
            }
            else {
                ptr = make_function(funcname, std::forward<Fx>(func));
            }
            metafunctions.emplace_back(std::move(ptr));
            metafunctiontable.push_back( { name.c_str(), &base_function::usertype<N>::call } );
            ptrmetafunctiontable.push_back( { name.c_str(), &base_function::usertype<N>::ref_call } );
            return true;
        }
        indexmetafunctions.emplace(funcname, std::make_pair(make_function(funcname, std::forward<Fx>(func)), true));
        return false;
    }

    template<std::size_t N, typename Fx, typename... Args>
    void build_function_tables(function_map_t*& index, function_map_t*& newindex, std::string funcname, Fx&& func, Args&&... args) {
        typedef typename std::is_member_object_pointer<Unqualified<Fx>>::type is_variable;
        static const std::size_t V = static_cast<std::size_t>(!is_variable::value);
        if(build_function<N>(is_variable(), index, newindex, std::move(funcname), std::forward<Fx>(func))) {
            build_function_tables<N + V>(index, newindex, std::forward<Args>(args)...);
        }
        else {
            build_function_tables<N>(index, newindex, std::forward<Args>(args)...);
        }
    }

    template<std::size_t N, typename Base, typename Ret, typename... Args>
    void build_function_tables(function_map_t*& index, function_map_t*& newindex, meta_function metafunc, Ret Base::* func, Args&&... args) {
        std::size_t idx = static_cast<std::size_t>(metafunc);
        const std::string& funcname = meta_function_names[idx];
        build_function_tables<N>(index, newindex, funcname, std::move(func), std::forward<Args>(args)...);
    }

public:
    template<typename... Args>
    usertype(Args&&... args): usertype(default_constructor, std::forward<Args>(args)...) {}

    template<typename... Args>
    SOL_DEPRECATED usertype(std::string, std::string, Args&&... args): usertype(default_constructor, std::forward<Args>(args)...) {}

    template<typename... Args>
    SOL_DEPRECATED usertype(const char*, std::string, Args&&... args): usertype(default_constructor, std::forward<Args>(args)...) {}

    template<typename... Args, typename... CArgs>
    SOL_DEPRECATED usertype(std::string, constructors<CArgs...> c, Args&&... args) : usertype(std::move(c), std::forward<Args>(args)...) {}

    template<typename... Args, typename... CArgs>
    SOL_DEPRECATED usertype(const char*, constructors<CArgs...> c, Args&&... args) : usertype(std::move(c), std::forward<Args>(args)...) {}

    template<typename... Args, typename... CArgs>
    usertype(constructors<CArgs...>, Args&&... args) {
        functionnames.reserve(sizeof...(args) + 2);
        metafunctiontable.reserve(sizeof...(args));
        ptrmetafunctiontable.reserve(sizeof...(args));

        function_map_t* index = nullptr;
        function_map_t* newindex = nullptr;
        build_function_tables<0>(index, newindex, std::forward<Args>(args)...);
        indexmetafunctions.clear();
        newindexmetafunctions.clear();
        functionnames.push_back("new");
        metafunctiontable.push_back({ functionnames.back().c_str(), &constructor<CArgs...>::construct });
        functionnames.push_back("__gc");
        metafunctiontable.push_back({ functionnames.back().c_str(), &destructor::destruct });
        // ptr_functions does not participate in garbage collection/new,
        // as all pointered types are considered
        // to be references. This makes returns of
        // `std::vector<int>&` and `std::vector<int>*` work

        metafunctiontable.push_back({ nullptr, nullptr });
        ptrmetafunctiontable.push_back({ nullptr, nullptr });
    }

    int push(lua_State* L) {
        // push pointer tables first,
        // but leave the regular T table on last
        // so it can be linked to a type for usage with `.new(...)` or `:new(...)`
        push_metatable(L, usertype_traits<T*>::metatable,
                       metafunctions, ptrmetafunctiontable);
        lua_pop(L, 1);

        push_metatable(L, usertype_traits<T>::metatable,
                       metafunctions, metafunctiontable);
        set_global_deleter(L);
        return 1;
    }

private:
    template<typename Meta, typename MetaFuncs, typename MetaFuncTable>
    static void push_metatable(lua_State* L, Meta&& metakey, MetaFuncs&& metafuncs, MetaFuncTable&& metafunctable) {
        luaL_newmetatable(L, std::addressof(metakey[0]));
        if(metafunctable.size() > 1) {
            // regular functions accessed through __index semantics
            int up = push_upvalues(L, metafuncs);
            luaL_setfuncs(L, metafunctable.data(), up);
        }
    }

    void set_global_deleter(lua_State* L) {
        // Automatic deleter table -- stays alive until lua VM dies
        // even if the user calls collectgarbage()
        lua_createtable(L, 0, 0);
        lua_createtable(L, 0, 1);
        int up = push_upvalues<true>(L, metafunctions);
        lua_pushcclosure(L, cleanup, up);
        lua_setfield(L, -2, "__gc");
        lua_setmetatable(L, -2);
        // gctable name by default has ♻ part of it
        lua_setglobal(L, std::addressof(usertype_traits<T>::gctable[0]));
    }

    template<bool release = false, typename TCont>
    static int push_upvalues(lua_State* L, TCont&& cont) {
        int n = 0;
        for(auto& c : cont) {
            if(release) {
               stack::push<upvalue>(L, c.release());
            }
            else {
                stack::push<upvalue>(L, c.get());
            }
            ++n;
        }
        return n;
    }
};

namespace stack {
template<typename T>
struct pusher<usertype<T>> {
    static int push(lua_State* L, usertype<T>& user) {
        return user.push(L);
    }
};
} // stack
} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\usertype.hpp

namespace old_sol {
class table : public reference {
    friend class state;
    template<typename T, typename U>
    typename stack::get_return<T>::type single_get(U&& key) const {
        push();
        stack::push(state(), std::forward<U>(key));
        lua_gettable(state(), -2);
        type_assert(state(), -1, type_of<T>());
        auto&& result = stack::pop<T>(state());
        lua_pop(state(), 1);
        return result;
    }

    template<typename Keys, typename... Ret, std::size_t... I>
    typename return_type<typename stack::get_return<Ret>::type...>::type tuple_get(types<Ret...>, indices<I...>, Keys&& keys) const {
        return std::make_tuple(single_get<Ret>(std::get<I>(keys))...);
    }

    template<typename Keys, typename Ret>
    typename stack::get_return<Ret>::type tuple_get(types<Ret>, indices<0>, Keys&& keys) const {
        return single_get<Ret>(std::get<0>(keys));
    }

public:
    table() noexcept : reference() {}
    table(lua_State* L, int index = -1) : reference(L, index) {
        type_assert(L, index, type::table);
    }

    template<typename... Ret, typename... Keys>
    typename return_type<typename stack::get_return<Ret>::type...>::type get(Keys&&... keys) const {
        types<Ret...> tr;
        return tuple_get(tr, tr, std::make_tuple(std::forward<Keys>(keys)...));
    }

    template<typename T, typename U>
    table& set(T&& key, U&& value) {
        push();
        stack::push(state(), std::forward<T>(key));
        stack::push(state(), std::forward<U>(value));
        lua_settable(state(), -3);
        lua_pop(state(), 1);
        return *this;
    }

    template<typename T>
    SOL_DEPRECATED table& set_userdata(usertype<T>& user) {
        return set_usertype(user);
    }

    template<typename Key, typename T>
    SOL_DEPRECATED table& set_userdata(Key&& key, usertype<T>& user) {
        return set_usertype(std::forward<Key>(key), user);
    }

    template<typename T>
    table& set_usertype(usertype<T>& user) {
        return set_usertype(usertype_traits<T>::name, user);
    }

    template<typename Key, typename T>
    table& set_usertype(Key&& key, usertype<T>& user) {
        push();
        stack::push(state(), std::forward<Key>(key));
        stack::push(state(), user);
        lua_settable(state(), -3);
        lua_pop(state(), 1);
        return *this;
    }

    template<typename Fx>
    void for_each(Fx&& fx) const {
        push();
        stack::push(state(), nil);
        while (lua_next(this->state(), -2)) {
            old_sol::object key(state(), -2);
            old_sol::object value(state(), -1);
            fx(key, value);
            lua_pop(state(), 1);
        }
        pop();
    }

    size_t size() const {
        push();
        size_t result = lua_rawlen(state(), -1);
        pop();
        return result;
    }

    template<typename T>
    proxy<table, T> operator[](T&& key) {
        return proxy<table, T>(*this, std::forward<T>(key));
    }

    template<typename T>
    proxy<const table, T> operator[](T&& key) const {
        return proxy<const table, T>(*this, std::forward<T>(key));
    }

    void pop(int n = 1) const noexcept {
        lua_pop(state(), n);
    }

    template<typename... Args, typename R, typename Key>
    table& set_function(Key&& key, R fun_ptr(Args...)){
        set_resolved_function(std::forward<Key>(key), fun_ptr);
        return *this;
    }

    template<typename Sig, typename Key>
    table& set_function(Key&& key, Sig* fun_ptr){
        set_resolved_function(std::forward<Key>(key), fun_ptr);
        return *this;
    }

    template<typename... Args, typename R, typename C, typename T, typename Key>
    table& set_function(Key&& key, R (C::*mem_ptr)(Args...), T&& obj) {
        set_resolved_function(std::forward<Key>(key), mem_ptr, std::forward<T>(obj));
        return *this;
    }

    template<typename Sig, typename C, typename T, typename Key>
    table& set_function(Key&& key, Sig C::* mem_ptr, T&& obj) {
        set_resolved_function(std::forward<Key>(key), mem_ptr, std::forward<T>(obj));
        return *this;
    }

    template<typename... Sig, typename Fx, typename Key>
    table& set_function(Key&& key, Fx&& fx) {
        set_fx(types<Sig...>(), std::forward<Key>(key), std::forward<Fx>(fx));
        return *this;
    }

private:
    template<typename R, typename... Args, typename Fx, typename Key, typename = typename std::result_of<Fx(Args...)>::type>
    void set_fx(types<R(Args...)>, Key&& key, Fx&& fx) {
        set_resolved_function<R(Args...)>(std::forward<Key>(key), std::forward<Fx>(fx));
    }

    template<typename Fx, typename Key>
    void set_fx(types<>, Key&& key, Fx&& fx) {
        typedef Unqualified<Unwrap<Fx>> fx_t;
        typedef decltype(&fx_t::operator()) Sig;
        set_fx(types<function_signature_t<Sig>>(), std::forward<Key>(key), std::forward<Fx>(fx));
    }

    template<typename... Sig, typename... Args, typename Key>
    void set_resolved_function(Key&& key, Args&&... args) {
        std::string fkey(std::forward<Key>(key));
        push();
        int tabletarget = lua_gettop(state());
        stack::push<function_sig_t<Sig...>>(state(), std::forward<Args>(args)...);
        lua_setfield(state(), tabletarget, fkey.c_str());
        pop();
    }
};
} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\table.hpp

namespace old_sol {
namespace detail {
inline int atpanic(lua_State* L) {
    const char* message = lua_tostring(L, -1);
    std::string err = message ? message : "An unexpected error occured and forced the lua state to call atpanic";
    throw error(err);
}
} // detail

enum class lib : char {
    base,
    package,
    coroutine,
    string,
    os,
    math,
    table,
    debug,
    bit32,
    io,
    count
};

class state {
private:
    std::unique_ptr<lua_State, void(*)(lua_State*)> L;
    table reg;
    table global;
public:
    state():
    L(luaL_newstate(), lua_close),
    reg(L.get(), LUA_REGISTRYINDEX),
    global(reg.get<table>(LUA_RIDX_GLOBALS)) {
        lua_atpanic(L.get(), detail::atpanic);
    }

    lua_State* lua_state() const {
        return L.get();
    }

    template<typename... Args>
    void open_libraries(Args&&... args) {
        static_assert(are_same<lib, Args...>::value, "all types must be libraries");
        if(sizeof...(args) == 0) {
            luaL_openlibs(L.get());
            return;
        }

        lib libraries[1 + sizeof...(args)] = { lib::count, std::forward<Args>(args)... };

        for(auto&& library : libraries) {
            switch(library) {
            case lib::base:
                luaL_requiref(L.get(), "base", luaopen_base, 1);
                lua_pop(L.get(), 1);
                break;
            case lib::package:
                luaL_requiref(L.get(), "package", luaopen_package, 1);
                lua_pop(L.get(), 1);
                break;
            case lib::coroutine:
                luaL_requiref(L.get(), "coroutine", luaopen_coroutine, 1);
                lua_pop(L.get(), 1);
                break;
            case lib::string:
                luaL_requiref(L.get(), "string", luaopen_string, 1);
                lua_pop(L.get(), 1);
                break;
            case lib::table:
                luaL_requiref(L.get(), "table", luaopen_table, 1);
                lua_pop(L.get(), 1);
                break;
            case lib::math:
                luaL_requiref(L.get(), "math", luaopen_math, 1);
                lua_pop(L.get(), 1);
                break;
            case lib::bit32:
                luaL_requiref(L.get(), "bit32", luaopen_bit32, 1);
                lua_pop(L.get(), 1);
                break;
            case lib::io:
                luaL_requiref(L.get(), "io", luaopen_io, 1);
                lua_pop(L.get(), 1);
                break;
            case lib::os:
                luaL_requiref(L.get(), "os", luaopen_os, 1);
                lua_pop(L.get(), 1);
                break;
            case lib::debug:
                luaL_requiref(L.get(), "debug", luaopen_debug, 1);
                lua_pop(L.get(), 1);
                break;
            case lib::count:
                break;
            }
        }
    }

    void script(const std::string& code) {
        if(luaL_dostring(L.get(), code.c_str())) {
            lua_error(L.get());
        }
    }

    void open_file(const std::string& filename) {
        if(luaL_dofile(L.get(), filename.c_str())) {
            lua_error(L.get());
        }
    }

    template<typename... Args, typename... Keys>
    auto get(Keys&&... keys) const
    -> decltype(global.get<Args...>(std::forward<Keys>(keys)...)) {
       return global.get<Args...>(std::forward<Keys>(keys)...);
    }

    template<typename T, typename U>
    state& set(T&& key, U&& value) {
        global.set(std::forward<T>(key), std::forward<U>(value));
        return *this;
    }

    template<typename T>
    SOL_DEPRECATED table& set_userdata(usertype<T>& user) {
        return set_usertype(user);
    }

    template<typename Key, typename T>
    SOL_DEPRECATED table& set_userdata(Key&& key, usertype<T>& user) {
        return set_usertype(std::forward<Key>(key), user);
    }

    template<typename Class, typename... CTor, typename... Args>
    SOL_DEPRECATED state& new_userdata(const std::string& name, Args&&... args) {
        return new_usertype<Class>(name, std::forward<Args>(args)...);
    }

    template<typename Class, typename... CArgs, typename... Args>
    SOL_DEPRECATED state& new_userdata(const std::string& name, constructors<CArgs...> ctor, Args&&... args) {
        return new_usertype(name, std::move(ctor), std::forward<Args>(args)...);
    }

    template<typename T>
    state& set_usertype(usertype<T>& user) {
        return set_usertype(usertype_traits<T>::name, user);
    }

    template<typename Key, typename T>
    state& set_usertype(Key&& key, usertype<T>& user) {
        global.set_usertype(std::forward<Key>(key), user);
        return *this;
    }

    template<typename Class, typename... CTor, typename... Args>
    state& new_usertype(const std::string& name, Args&&... args) {
        constructors<types<CTor...>> ctor{};
        return new_usertype<Class>(name, ctor, std::forward<Args>(args)...);
    }

    template<typename Class, typename... CArgs, typename... Args>
    state& new_usertype(const std::string& name, constructors<CArgs...> ctor, Args&&... args) {
        usertype<Class> utype(ctor, std::forward<Args>(args)...);
        set_usertype(name, utype);
        return *this;
    }

    template <typename Fx>
    void for_each(Fx&& fx) {
        global.for_each(std::forward<Fx>(fx));
    }

    template<typename T>
    table create_table(T&& key, int narr = 0, int nrec = 0) {
        lua_createtable(L.get(), narr, nrec);
        table result(L.get());
        lua_pop(L.get(), 1);
        global.set(std::forward<T>(key), result);
        return result;
    }

    table create_table(int narr = 0, int nrec = 0) {
        lua_createtable(L.get(), narr, nrec);
        table result(L.get());
        lua_pop(L.get(), 1);
        return result;
    }

    table global_table() const {
        return global;
    }

    table registry() const {
        return reg;
    }

    template<typename T>
    proxy<table, T> operator[](T&& key) {
        return global[std::forward<T>(key)];
    }

    template<typename T>
    proxy<const table, T> operator[](T&& key) const {
        return global[std::forward<T>(key)];
    }

    template<typename... Args, typename R, typename Key>
    state& set_function(Key&& key, R fun_ptr(Args...)){
        global.set_function(std::forward<Key>(key), fun_ptr);
        return *this;
    }

    template<typename Sig, typename Key>
    state& set_function(Key&& key, Sig* fun_ptr){
        global.set_function(std::forward<Key>(key), fun_ptr);
        return *this;
    }

    template<typename... Args, typename R, typename C, typename T, typename Key>
    state& set_function(Key&& key, R (C::*mem_ptr)(Args...), T&& obj) {
        global.set_function(std::forward<Key>(key), mem_ptr, std::forward<T>(obj));
        return *this;
    }

    template<typename Sig, typename C, typename T, typename Key>
    state& set_function(Key&& key, Sig C::* mem_ptr, T&& obj) {
        global.set_function(std::forward<Key>(key), mem_ptr, std::forward<T>(obj));
        return *this;
    }

    template<typename... Sig, typename Fx, typename Key>
    state& set_function(Key&& key, Fx&& fx) {
        global.set_function<Sig...>(std::forward<Key>(key), std::forward<Fx>(fx));
        return *this;
    }
};
} // old_sol

// end of C:\Users\Rig\Desktop\sol\sol\state.hpp

#endif // SOL_SINGLE_INCLUDE_HPP
