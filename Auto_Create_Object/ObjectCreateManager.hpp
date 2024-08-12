#pragma once

#include <iostream>
#include <memory>

constexpr int stackMaxMemory = 20;

template <typename T>
class OnStack
{
public:
	OnStack() : m_obj() {
		std::cout << "Stack create." << std::endl;
	};
	~OnStack() {
		std::cout << "Stack release." << std::endl;
	};
	T& obj() { return m_obj; };
private:
	T m_obj;
};

template<typename T>
class OnHeap 
{
public:
	OnHeap() :m_objP(std::make_unique<T>()) {
		std::cout << "Heap create." << std::endl;
	};
	~OnHeap() {
		std::cout << "Heap release." << std::endl;
	};
	std::unique_ptr<T>& getObjPtr() { return m_objP; };
	T& obj() { return *m_objP; };
private:
	std::unique_ptr<T> m_objP;
};

template<typename T>
using ObjectCreator = typename std::conditional
<
	(sizeof(T) <= stackMaxMemory ),
	OnStack<T>,
	OnHeap<T>
>::type;
