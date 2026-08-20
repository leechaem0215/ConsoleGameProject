#include "List.h"
#include <iostream>
#include <string>
#include <vector>

int main() 
{
	std::vector<std::string> testVector(100);
	//testVector.resize(100);
	
	// 캐릭터 리스트
	List<std::string> characterList;
	characterList.PushBack("Warrior");
	characterList.PushBack("Knight");
	characterList.PushBack("Archer");

	// 복사 생성.
	List<std::string> copiedList(characterList); 	// 복사된 목록 첫번째 값 바꿔보겠음
	copiedList[0] = "BlackKnight";

	// 이동 생성.
	List<std::string> copiedList2(std::move(copiedList)); // 기존 객체 이동처리해서 넘기겠음

	// 범위-기반 루프로 출력.
	for (const auto& value : characterList)
	{
		std::cout << value << "\n";
	}
}