#pragma once

#include "Node.h"
#include <cstdint>
#include <iostream>

// 연결리스트 클래스
template<typename T>
class LinkedList
{
public:
	LinkedList()
		:head(nullptr), count(0)
	{

	}
	~LinkedList()
	{
		// 전체 노드를 제거하는 함수 구현 후 호출
		Clear();

	}

	// 연결리스트 가장 앞(헤드)에 노드 추가하는 함수
	void AddToHead(const T& data)
	{
		// 새로운 노드 생성
		Node<T>* newNode = new Node<T>(data);

		// 포인터 정리
		// 기존의 헤드를 새로운 헤드의 다음 노드로 설정
		newNode->next = head;
		head = newNode;

		// 저장된 자료 수 업뎃
		++count;
	}

	// 새로운 노드 추가
	// 데이터 값 정렬을 기반으로 추가 (작은거 앞, 큰거 뒤, 오른차순)
	void Insert(const T& data)
	{
		// 새로운 노드 생성
		Node<T>* newNode = new Node<T>(data);

		// 추가할 노드 위치 찾기
		Node<T>* current = head;
		Node<T>* trail = nullptr;	// 꼬리,

		// 전체 조건 -> 저장되는 데이터가 비교 연상이 가능하다는 전제
		while (current && current->data < data) // 앞이 작으면 검사
		{
			// 이전 위치 저장
			trail = current;

			// 현재 위치 업데이트
			current = current->next;
		}

		// 찾은 위치가 헤드인 경우
		if (trail == nullptr) 
		{
			newNode->next = head;
			head = newNode;
		}
		// 헤드가 아니라 다른 위치인 경우
		else
		{
			newNode->next = current;
			trail->next = newNode;
		}

		// 데이터 증가 처리
		++count;
	}

	// 순회하면서 연결 리스트 출력
	void Print() const
	{
		const Node<T>* current = head;

		while (current) {
			// 출력
			std::cout << "Data: " << current->Data << "\n";

			// 다음 노드로 이동
			current = current->next;
		}
	}


	// Getter
	size_t Count() const { retuen count; }
	bool Empty() const { return head == nullptr; }
private:
	// 초기화 함수(노드를 모두 제거하는 함수)
	void Clear()
	{
		// 헤드부터 시작
		Node<T>* current = head;

		// 현재 노드 삭제 -> 다음 노드로 이동
		while (current)
		{
			Node<T>* deleteNode = current;
			current = current->nect;

			delete deleteNode;
		}

		// 값 비우기
		head = nullptr;
		count = 0;
	}



private:
	// 연결 리스트의 첫 노드(헤드)
	Node<T>* head = nullptr;

	// 연결 리스트에 저장된 자료 수
	size_t count = 0;
};