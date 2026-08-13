#include "Background.h"

#include <Engine/Engine.h>
#include <Render/Renderer.h>
#include <Util/ResourceManager.h>
#include <Util/Util.h>

#include <algorithm>
#include <stdexcept>

using namespace Craft;

Background::Background(
	const std::vector<std::wstring>& mapKeys
)
	: mapKeys(mapKeys)
{
	if (this->mapKeys.empty())
	{
		throw std::runtime_error(
			"Map 리소스 키가 없습니다."
		);
	}

	sortingOrder = 5;

	// 첫 번째 맵 추가
	AddRandomMap();
}

void Background::AddRandomMap()
{
	const int randomIndex =
		Util::RandomRange(
			0,
			static_cast<int>(mapKeys.size()) - 1
		);

	const std::wstring& selectedKey =
		mapKeys[randomIndex];

	const std::wstring& selectedImage =
		ResourceManager::GetText(selectedKey);

	/*
	* ChangeImage()를 호출해서
	* 해당 맵의 너비와 높이를 계산한다.
	*
	* Background 액터의 이미지는 계속 바뀌지만
	* 실제 Draw에서는 mapPieces의 이미지를 사용한다.
	*/
	ChangeImage(selectedImage);

	MapPiece newPiece;

	newPiece.image = selectedImage;
	newPiece.width = GetWidth();
	newPiece.height = GetHeight();

	if (mapPieces.empty())
	{
		// 첫 맵은 화면 오른쪽에서 시작
		newPiece.xPosition =
			static_cast<float>(
				Engine::Get().GetWidth()
				);
	}
	else
	{
		const MapPiece& lastPiece =
			mapPieces.back();

		const int randomGap =
			Util::RandomRange(
				minGap,
				maxGap
			);

		// 이전 맵의 오른쪽 끝 + 랜덤 간격
		newPiece.xPosition =
			lastPiece.xPosition
			+ lastPiece.width
			+ randomGap;
	}

	mapPieces.push_back(newPiece);
}

void Background::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 모든 맵 조각 이동
	for (MapPiece& piece : mapPieces)
	{
		piece.xPosition -= speed * deltaTime;
	}

	// 화면 왼쪽을 완전히 벗어난 맵 제거
	mapPieces.erase(
		std::remove_if(
			mapPieces.begin(),
			mapPieces.end(),
			[](const MapPiece& piece)
			{
				return piece.xPosition
					+ piece.width <= 0.0f;
			}
		),
		mapPieces.end()
	);

	/*
	* 가장 마지막 맵의 오른쪽 끝이
	* 화면 안으로 들어오기 시작하면 다음 맵 추가
	*/
	if (mapPieces.empty())
	{
		AddRandomMap();
	}
	else
	{
		const MapPiece& lastPiece =
			mapPieces.back();

		const float lastRight =
			lastPiece.xPosition
			+ lastPiece.width;

		if (lastRight <= Engine::Get().GetWidth())
		{
			AddRandomMap();
		}
	}
}

void Background::Draw()
{
	for (const MapPiece& piece : mapPieces)
	{
		const int mapY =
			Engine::Get().GetHeight()
			- piece.height;

		Renderer::Get().Submit(
			piece.image,
			Vector2(
				static_cast<int>(piece.xPosition),
				mapY
			),
			Color::White,
			sortingOrder
		);
	}
}