#include <limits>
#include <stdint.h>
#include <type_traits>
#include <iostream>

enum class etoto:int{
    eA=0,
    eB=1,
    eC=2,
    eD=3,
    eLast
};


template<typename E>
constexpr auto to_integral(E e) -> typename std::underlying_type<E>::type 
{
   return static_cast<typename std::underlying_type<E>::type>(e);
}

template<typename enum_T, typename out_T=int16_t>
out_T normalize(enum_T e){
    out_T outmax= std::numeric_limits<out_T>::max();
    return ((outmax+1)/(to_integral(enum_T::eLast)))*to_integral(e);
}

template<typename enum_T, typename in_T=int16_t>
enum_T denormalize(in_T val){
    in_T inmax = std::numeric_limits<in_T>::max(); 
    in_T out =  val/((inmax+1)/(to_integral(enum_T::eLast)));
    return (etoto(out));
}

template<typename enum_T, typename in_T=int16_t>
bool is(in_T val, enum_T e){
    in_T inmax = std::numeric_limits<in_T>::max(); 
    in_T out =  val/((inmax+1)/(to_integral(enum_T::eLast)));
    return (out>=to_integral(e) && (out<=to_integral(e)+1));
}

int main(){
    etoto e= etoto::eD;
    std::cout << normalize(e) << std::endl  ;
    if(is(int16_t(8192*3-1), e))
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;
    std::cout << int16_t(e) << std::endl  ;
    e= denormalize<etoto, int16_t>(int16_t(8192));
    std::cout << int16_t(e) << std::endl  ;
    return 0;

}