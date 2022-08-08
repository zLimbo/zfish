#ifndef MY_SMART_PTR_H
#define MY_SMART_PTR_H

using __gnu_cxx::_Lock_policy;

template <typename _Tp, _Lock_policy _Lp, bool = is_array<_Tp>::value, bool = is_void<_Tp>::value>
class __shared_ptr_access {};

template <typename _Tp, _Lock_policy _Lp>
class __shared_ptr : public __shared_ptr_access<_Tp, _Lp> {};

template <typename _Tp>
class shared_ptr : public __shared_ptr<_Tp> {};

template <typename _Tp, typename... _Args>
inline shared_ptr<_Tp> make_shared(_Args&&... __args) {
    typedef typename std::remove_cv<_Tp>::type _Tp_nc;
    return std::allocate_shared<_Tp>(std::allocator<_Tp_nc>(), std::forward<_Args>(__args)...);
}

#endif  // MY_SMART_PTR_H