#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>

class Enemy : public Craft::Actor
{
	// 커스텀 타입 설정
	TYPE_DECLARATIONS(Enemy, Actor)

		// 이동할 때 쓸 열거형 지정
		enum class MoveDirection
	{
		None = -1,
		Left,
		Right
	};
public:
	// 생성자도 위치가 필요, 어떤 문자열을 보여줄지도
	Enemy(const std::wstring& image = L"(o0o)", int yPosition = 5);

private:
	// 이벤트 함수 오버라이드
	virtual void Tick(float deltaTime) override;

	// 충돌 처리 함수 오버라이드
	virtual void OnCollision(const std::shared_ptr<Actor>& other) override;

private:
	// 이동 방향 열거형 변수
	MoveDirection direction = MoveDirection::None;

	// 이동 처리하려면 이동 빠르기도 필요하다
	// 좌우 이동 처리를 위한 변수
	float xPosition = 0.0f;
	float moveSpeed = 5.0f;

	// 발사 타이머
	Timer timer;
};