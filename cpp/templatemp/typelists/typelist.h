#ifndef TYPELIST_H_INCLUDED
#define TYPELIST_H_INCLUDED
#include <string>
template<class H,class T>
struct typelist {
    typedef H head;
    typedef T tail;
};

struct null_typelist {

};

template<class T>
struct cons;

template <class T1>
struct cons<void (*) (T1)> {
    typedef typelist<T1,null_typelist> type;
    static const int length=1;

};

template <class T1,class T2>
struct cons<void (*) (T1,T2)> {
    typedef typelist<T1, typelist<T2,null_typelist> > type;
    static const int length=2;

};

template <class T1,class T2,class T3>
struct cons<void (*) (T1,T2,T3)> {
    typedef typelist<T1, typelist<T2, typelist<T3,null_typelist> > >type;
    static const int length=3;
};



template <class T1,class T2,class T3,class T4>
struct cons<void (*) (T1,T2,T3,T4)> {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<null_typelist,T4> > > >type;
    static const int length=4;

};


template <class T1,class T2,class T3,class T4,class T5>
struct cons<void (*) (T1,T2,T3,T4,T5)> {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5,null_typelist> > > > >type;
    static const int length=5;

};


template <class T1,class T2,class T3,class T4,class T5, class T6>
struct cons<void (*) (T1,T2,T3,T4,T5,T6)> {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6,null_typelist> > > > > >type;
    static const int length=6;

};


template <class T1,class T2,class T3,class T4,class T5, class T6,class T7>
struct cons<void (*) (T1,T2,T3,T4,T5,T6,T7)> {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7,null_typelist> > > > > > >type;
    static const int length=7;


};

template <class T1,class T2,class T3,class T4,class T5, class T6,class T7,class T8>
struct cons<void (*) (T1,T2,T3,T4,T5,T6,T7,T8)> {
    typedef typelist<T1, typelist<T2, typelist<T3, typelist<T4, typelist<T5, typelist<T6, typelist<T7, typelist<T8,null_typelist> > > > > > > >type;
    static const int length=8;

};




template <bool,class T>
struct menable_if {
};


template <class T>
struct menable_if<true,T> {
    typedef T type;
};


template<class T>
struct TLength;

template<>
struct TLength<null_typelist>
{
    enum { value = 0};
};

template<class H,class T>
struct TLength<typelist<H,T> >
{
    enum { value = 1 + TLength<T>::value };
};




template<class T,class V>
struct Equals {
    static const bool value=false;
};

template<class T>
struct Equals<T,T> {
    static const bool value=true;
};


template<class T,class U>
struct TContains;

template<class V>
struct TContains<V,null_typelist> {
    enum { value = 0 };
};

template<class V,class H,class L>
struct TContains<V,typelist<H,L>> {
    enum { value = (Equals<V,H>::value)?true:(TContains<V,L>::value) };
};

template<class H,unsigned int>
struct TTypeAT;

template<class T,class H>
struct TTypeAT<typelist<H,T>,0> {
    typedef H resulttype;
};

template<class H,class T,unsigned int i>
struct TTypeAT<typelist<H,T>,i> {
    typedef typename TTypeAT<T,i-1>::resulttype resulttype;
};

template<class T>
struct type2string {
    static const char value='z';
};

template<>
struct type2string<int> {
    static const char value='i';
};

template<>
struct type2string<double> {
    static const char value='d';
};

template<>
struct type2string<float> {
    static constexpr const char* value="sdfsdfdf";
};
template<>
struct type2string<char> {
    static const char value='c';
};

#define TYPELIST(a) cons< void (*)a >::type


typedef TYPELIST((float, double, long double))    floating_point_types;


template<char... C>
struct typestring final {
private:
    static constexpr char const   vals[sizeof...(C)+1] = { C...,'\0' };
    static constexpr unsigned int sval = sizeof...(C);
public:

    static constexpr char const * data() noexcept
    { return &vals[0]; }

    static constexpr unsigned int size() noexcept
    { return sval; };

    static constexpr char const * cbegin() noexcept
    { return &vals[0]; }

    static constexpr char const * cend() noexcept
    { return &vals[sval]; }
};
template<char... C>
constexpr char const typestring<C...>::vals[sizeof...(C)+1];





#endif // TYPELIST_H_INCLUDED
