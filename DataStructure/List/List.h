#pragma once

#include <cassert>
#include <iostream>

// 리스트 이터레이터



// 편의 목적을 위해 타입 재정의




// 템플릿 동적 배열 클래스
// 템플릿은 header에만 구현 << cpp 로 구분해서 구현하지 않음
// 템플릿은 추론 (해석) 시점이 컴파일 시간이기 때문
template<typename T>
class List
{
	
public:
	// 기본생성자 만들것임
	List()
	{
		// 시작할 때 기본 크기로 저장공간 할당
		ReAllocate(defaultSize);
	}
	~List()
	{
		delete[] data;
		data = nullptr;
	}

	// 복사 생성자
	List(const List& other)
		: size(other.size), capacity(other.capacity)
	{
		// 다른 리스트 기반으로 리스트 생성
		// 1. 저장 공간 할당
		if (other.capacity > 0) 
		{
			data = new T[other.capacity];
		}

		// 저장된 데이터 복사
		for (int ix = 0; ix < size; ++ix)
		{
			data[ix] = other.data[ix]; // 직접 대입
		}
	}

	// 복사 대입 연산자 오버로딩
	// 리스트 레퍼런스 반환하도록 할거임
	List& operator= (const List& other)
	{
		// 예외처리 (같은 객체인지 확인)
		if (this == &other)
		{
			return *this;
		}

		// 새로운 공간 할당
		T* newData = nullptr;

		if (other.capacity > 0)
		{
			newData = new T[other.capacity];

			// 값 복사
			for (int ix = 0; ix < other.size; ++ix)
			{
				// orther 의 데이터 복사
				// 기존 데이터 
				newData[ix] = other.data[ix];
			}
		}

		// 기존의 관리하던 데이터 제거
		delete[] data;

		// 값 업데이트
		data = newData;
		size = other.size;
		capacity = other.capacity;

		return *this;
	}



	// 이동 생성자
	List(List&& other)
		: size(other.size),
		capacity(other.capacity),
		data(other.data)
	{
		// 정리 작업이 이동 복사할 때 핵심이다.
		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;
	}

		// 이동 대입 연산자
	List& operator=(List&& other)
	{
		// 예외 처리.
		if (this == &other)
		{
			return *this;
		}
		// 대입 해야해서 기존 데이터 제거
		delete[] data;

		// 여기서는 얕은 복사 해주면 됌
		// 복사 처리.
		data = other.data;
		size = other.size;
		capacity = other.capacity;

		// other 값 정리.
		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;

		// this 를 참조로
		return *this;
	}


	// 맨 마지막 위치에 데이터 추가하는 함수
	void PushBack(const T& value)
	{
		// 1. 저장공간이 가득 찼으면 재할당
		if (size == capacity) 
		{
			int newCapacity = capacity == 0 ? defaultSize : capacity * scale;
			ReAllocate(newCapacity);
		}

		// 2. 값 추가
		data[size] = value;
		++size;
	}

	void PushBack(T&& value)
	{
		// 1. 저장공간이 가득 찼으면 재할당
		if (size == capacity)
		{
			int newCapacity = capacity == 0 ? defaultSize : capacity * scale;
			ReAllocate(newCapacity);
		}

		// 2. 값 추가
		data[size] = std::move(value);
		++size;
	}

	// 요소 제거 함수
	void Erase(int index)
	{
		// 범위 검사
		if (index < 0 || index >= size)
		{
			// 조용한 예외처리
			// Silent is violent 
			return;
		}

		// 제거할 인덱스 뒤의 값을 앞으로 이동처리
		for (int ix = index; ix < size - 1; ++ix)
		{
			data[ix] = std::move(data[ix + 1]);
		}

		// 값 감소 처리
		--size;
		data[size] = T{}; // T는 템플릿이라 뭐가 올지 모름 T{} 나 {} 둘다 가능
	}

	// 인덱스로 접근 가능하도록 연산자 오버로딩
	T& operator[](size_t index)
	{
		assert(index < size && "index should be less than size.");
		return data[index];
	}

	const T& operator[](size_t index) const
	{
		assert(index < size && "index should be less than size.");
		return data[index];
	}

	// 저장된 요소수를 반환하는 함수
	int Size() const { return size; }

	// 저장공간 크기 값 반환 함수
	int Capacity() const { return capacity; }

	// 배열이 비어있는지 확인하는 함수
	bool Empty() const { return size == 0; }

	// 범위 기반 루프 사용 가능하도록 추가
	T* begin() const { return data; }
	T* end() const { return data + size; }

private:
	// 재할당 메소드
	void ReAllocate(int newCapacity)
	{ 
		// 1. 새로운 공간 할당
		T* newBlock = new T[newCapacity] {};

		// 2. 기존 데이터 가져와서 저장
		for (int ix = 0; ix < size; ++ix)
		{
			// data는 폐기 예정이기 때문에 move 로 처리
			newBlock[ix] = std::move(data[ix]);
		}
		// 3. 기존 저장공간 폐기
		delete[] data;

		// 4. 새로운 저장공간으로 data 업데이트
		data = newBlock;

		// 5. 저장공간 크기 값 업데이트
		capacity = newCapacity;
	}
private:
	// 내부에서 관리하는 배열 (메모리 주소)
	T* data = nullptr;

	// 배열에 저장된 요소의 수
	int size = 0;

	// 저장공간 크기
	int capacity = 0;

	// 상수 (초기 저장공간의 크기 값)
	const int defaultSize = 2;

	// 상수 (크기가 증가하는 배수)
	const int scale = 2;

};