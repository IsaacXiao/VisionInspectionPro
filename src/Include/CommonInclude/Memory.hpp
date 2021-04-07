

////
////此头文件中定义了与内存相关的函数或外包类型
////

#ifndef MEMORY_HPP
#define MEMORY_HPP


//#include <type_traits>


template<typename PtrT>
inline bool IsNull(PtrT ptr) noexcept
{
	return ptr == nullptr;
}

template<typename PtrT>
inline void DeletePtr(PtrT ptr)
{
	//if( !std::is_null_pointer<decltype(ptr)>::value )
	if( !IsNull(ptr) )
	{
		delete ptr;
		ptr = nullptr;
	}
}

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