#include <iostream>
#include <cstdint>
#include <cassert>
#include <algorithm>
#include <array>

// 배열 클래스
// 템플릿으로 받아야함
template<typename T, size_t size>
class Array // 클래스가 만들어지면서 값이 생성
{
public:
	// 배열 연산자 오버로딩
	T& operator[](size_t index)
	{ // 범위검사 해줄거임
		assert(index < size && "index should be less than size");
		return data[index];
	}
	
	const T& operator[](size_t index) const
	{
		assert(index < size && "index should be less than size");
		return data[index];
	}

	// 배열의 시작 주소 반환
	T* begin() { return data; }

	// 배열의 마지막주소
	T* end()
	{
		// 배열 마지막 인덱스의 다음 위치
		return data + size;
	}

	T* Data() { return data; }
	const T* Length() const { return data; }
	size_t Length() const { return size; }

	/*Array(size_t size)
	{
		data[size];
		memset(data, 0, sizeof(int) * size);
	}
	*/
private:
	T data[size]{};

 };

int main() 
{
	// 배열객체 생성
	std::array<int, 20> stdArray;
	Array<int, 5> intArray; // 템플릿으로 10을 넘겨줌
	//std::fill(
	//	intArray.Data(),
	//	intArray.Data() + intArray.Length(),
	//	20
	//);

	std::fill(
		intArray.begin(),
		intArray.end(),
		100
	);

	// 범위 기반 루프
	for (const auto& value : intArray)
	{
		std:: cout << value << '5';
	}
	
	//intArray[0] = 10;
	// intArray[5] = 30; // index가 기존보다 큼
	//int intNumber = intArray[0];
	//const int& constNumber = intArray[0]; // 상수 참조로 받음 // const 레퍼런스 처리도 가능

	// 정적 배열
	const uint32_t size = 5; // 상수로 해주어야함
	int array[5] = {}; // 초기화
	array[0] = 10;
	array[1] = 20;

	int number = array[0];

	// 동적 배열 (힙에 할당되는 배열)
	uint32_t dSize = 10;
	int* dArray = new int[dSize] {}; // 동적 배열 생성 // 힙에 할당하는 경우는 가능

	delete[] dArray; // 동적 배열 해제
	dArray = nullptr;

}