#ifndef UTILITY_H
#define UTILITY_H
/*
*@author Sonu Aryan
*/
struct any_t;

template<bool test,typename Type>
struct enable_if{};

template<typename T>
struct enable_if<true,T>{using type=T;};


//New code here
template<bool test,typename OnTrueType,typename OnFalseType>
struct enable_if_else{};

template<typename OnTrueType,typename OnFalseType>
struct enable_if_else<true,OnTrueType,OnFalseType>{using type=OnTrueType;};

template<typename OnTrueType,typename OnFalseType>
struct enable_if_else<false,OnTrueType,OnFalseType>{using type=OnFalseType;};
//End new Code



template<bool IfTest,bool ElseIftest,typename OnIfTrue,typename OnElseIfTrue>
struct enable_if_elseif{};

template<typename OnIfTrue,typename OnElseIfTrue>
struct enable_if_elseif<true,false,OnIfTrue,OnElseIfTrue>{using type=OnIfTrue;};

template<typename OnIfTrue,typename OnElseIfTrue>
struct enable_if_elseif<false,true,OnIfTrue,OnElseIfTrue>{using type=OnElseIfTrue;};

template<typename OnIfTrue,typename OnElseIfTrue>
struct enable_if_elseif<true,true,OnIfTrue,OnElseIfTrue>{using type=OnIfTrue;};

template<typename T1,typename T2>
struct is_same{static constexpr bool value=false;};

template<typename T>
struct is_same<T,T>{static constexpr bool value=true;};

template<typename T1,typename T2>
struct not_same{static constexpr bool value=true;};

template<typename T>
struct not_same<T,T>{static constexpr bool value=false;};

template<int Idx,typename This,typename... Types>
struct type_at{using type=typename type_at<Idx-1,Types...>::type;};

template<typename This,typename... Rest>
struct type_at<0,This,Rest...>{using type=This;};


template<typename ToFind,typename T,typename... Types>
struct index_of_type{static constexpr typename enable_if<not_same<ToFind,T>::value,int>::type I=index_of_type<ToFind,Types...>::I+1;};

template<typename T,typename... Types>
struct index_of_type<T,T,Types...>{static constexpr int I=0;};


using ulli=unsigned long long int;
template<ulli val>
struct sum_of_n{static constexpr ulli result=val+sum_of_n<val-1>::result;};

template<>
struct sum_of_n<0>{static constexpr ulli result=0;};

template<ulli val>
struct factorial{static constexpr ulli result=val*factorial<val-1>::result;};

template<>
struct factorial<0>{static constexpr ulli result=1;};

template<typename T,typename VType>
const char* visit(T value,VType visitor){return visitor(value);}

template<typename T,typename T2,typename... Tps>
struct contain_t{
	static constexpr bool found=contain_t<T,Tps...>::found;
};
template<typename T,typename... Tps>
struct contain_t<T,T,Tps...>{
	static constexpr bool found=true;
};
#endif