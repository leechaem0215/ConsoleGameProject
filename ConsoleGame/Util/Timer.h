#pragma once
class Timer
{
public:
	Timer(float targetTime = 1.0f);

	void Tick(float deltaTime);

	void Reset();

	// 목표 시간 재설정 함수
	void SetTargetTime(float targetTime);

	// 초시계는 시간이 다 흘렀는지 확인할 수 있어야함.
	// 설정한 시간이 지났는지 확인하는 함수
	inline bool IsTimeOut() const { return elapsedTime >= targetTime; }

private:
	// 경과 시간 계산용 변수
	float elapsedTime = 0.0f;

	//  타이머 목표 시간
	float targetTime = 0.0f;
};

