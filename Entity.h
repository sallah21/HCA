#pragma once
#include <vector>
#include <iostream>
template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
class Entity
{
	std::vector<T> data;
public:
	std::vector<T> getLocation()const { return this->data; }
	void setData(const std::vector<T> v){
		this->data = v;
	}
	size_t getSize() const { return this->data.size(); }
	Entity(std::vector<T> v) {//! tworzenie obiektu Entity
		this->data = v;
	}
	Entity(int size) { //! tworzenie pustego  obiektu Entity
		    std::vector<T> x(size, 0.0);
			this->data= x;
	}
};

