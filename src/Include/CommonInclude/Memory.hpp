

////
////此头文件中定义了与内存相关的函数或外包类型
////

#ifndef MEMORY_HPP
#define MEMORY_HPP


#include <type_traits>


template<typename PtrT>
inline bool IsNull(PtrT ptr) noexcept
{
	return ptr == nullptr;
}

template<typename PtrT>
inline void DeletePtr(PtrT ptr)
{
	if( std::is_null_pointer<decltype(ptr)>::value )
	{
		delete ptr;
		ptr = nullptr;
	}
}


////
////C风格的二维数组外包类.
////这对客户的资源管理带来了很大的便利性.
////其提供了隐式类型转换操作.
////
//用对象管理资源
template<typename T>
struct Dim2ArrayWrapper
{
	Dim2ArrayWrapper( int row, int col ) : row_( row ){
		p_ = new T*[ row ];
		for( int i = 0 ; i < row; ++i ){
			p_[ i ] = new T[ col ];
		}
	}

	~Dim2ArrayWrapper(){
		for( int i = 0 ; i < row_; ++i ){
			delete[] p_[i]; 
		}
		delete[] p_;
	}

	T** Ptr(){
		return p_;
	}

	T* operator[]( const int row ){
		return p_[ row ];
	}

private:
	T**		p_;
	int		row_;
};


#endif