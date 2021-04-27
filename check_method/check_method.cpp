#include <iostream>
#include <type_traits>


/*
    perverted method of finding a specific function signature))
    static polymorphism in action!!!
*/

struct A
{
    void bar();
};
struct B
{
    void bar();
};


template <typename T, typename... T1>
struct check_method
{
private:
    template <typename U>
    struct has_method
    {
    public:

        static constexpr bool value = std::is_same<void, decltype(has_method<U>::check(static_cast<U*>(nullptr)))>::value; // void in 'is_same' is returning type of our func

    private:
        static int check(...);

        template<typename C>
        static auto check(C* c)-> decltype(c->bar()); // name of our func
    };

public:
    static constexpr bool value = has_method<T>::value * (1 * ... * has_method<T1>::value);
};



int main()
{
    std::cout << check_method<A, B>::value;
}