#pragma once

#include "../GameObject/GameObject.h"
#include "../Game/Animation.h"
#include "../Game/Animations.h"
#include "../GameObject/AssetIDs.h"
#include "../Mario.h"
#include "PlayScene.h"


class CLetter : public CGameObject {
public:
	int letter;
	CLetter(float x, float y, int letter) : CGameObject(x, y) {
	this->letter = letter;
	}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(OBJECT_TYPE_LETTER_NUMBER_BAR + letter)->Draw(x, y);
	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
};

#define WORLD_X -155
#define LIVE_X -155
#define POINT_X -130
#define TIME_X -25
#define COIN_X -20
#define TOP_Y -7

#define STAMINA_X -90
#define STAMINA_WHITE_X -131
#define BLACK_STAMINA 37
#define WHITE_STAMINA 38
#define WHITE_P 39

#define BOTTOM_Y 2

class CInfoBar : public CGameObject {
public:
	CGameObject* mario;
	CPlayScene* playscene;
	int charToNumber(char c) {
		if (c >= 'A' && c <= 'Z') {
			return c - 'A' + 1; // Maps A to 1, B to 2, ..., Z to 26
		}
		else if (c >= '0' && c <= '9') {
			return c - '0' + 27; // Maps 0 to 27, 1 to 28, ..., 9 to 36
		}
		return -1; // Return -1 or throw an exception for invalid input
	}

	std::vector<int> stringToNumbers(const std::string& str) {
		std::vector<int> numbers;
		for (char c : str) {
			int number = charToNumber(c);
			if (number != -1) { // Check for valid conversion
				numbers.push_back(number);
			}
		}
		return numbers;
	}

	CInfoBar(float x, float y, CGameObject* mario, CPlayScene* playscene) : CGameObject(x, y) {
		this->mario = mario;
		this->playscene = playscene;
	}



	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		CMario* mario = dynamic_cast<CMario*>(this->mario);
		s->Get(ID_SPRITE_INFO_BAR)->Draw(x, y);

		s->Get(ID_SPRITE_LETTER_1)->Draw(x + WORLD_X, y + TOP_Y);

		std::vector<int> live = stringToNumbers(to_string(mario->GetLive()));
		for (int i = 0; i < static_cast<int>(live.size()); i++) {
			CLetter* letter = new CLetter(x + LIVE_X + i * 8, y + BOTTOM_Y, live[i]);
			letter->Render();
		}

		string pointString = to_string(mario->GetPoint());
		if (pointString.length() < 7) {
			pointString = string(7 - pointString.length(), '0') + pointString;
		}

		std::vector<int> point = stringToNumbers(pointString);
		for (int i = 0; i < static_cast<int>(point.size()); i++) {
			CLetter* letter = new CLetter(x + POINT_X + i * 8, y + BOTTOM_Y, point[i]);
			letter->Render();
		}

		std::vector<int> time = stringToNumbers(to_string(mario->GetTimeRemaining()));
		for (int i = 0; i < static_cast<int>(time.size()); i++) {
			CLetter* letter = new CLetter(x + TIME_X + i * 8, y + BOTTOM_Y, time[i]);
			letter->Render();
		}

		std::vector<int> coin = stringToNumbers(to_string(mario->GetCoin()));
		for (int i = 0; i < static_cast<int>(coin.size()); i++) {
			CLetter* letter = new CLetter(x + COIN_X + i * 8, y + TOP_Y, coin[i]);
			letter->Render();
		}

		CLetter* letter = new CLetter(x + STAMINA_X, y + TOP_Y - 2, BLACK_STAMINA);
		letter->Render();

		int running_count = mario->GetRunningCount();
		for (int i = 0; i < running_count; i++) {
			if (i == 6)
				{
				CLetter* letter = new CLetter(x + STAMINA_WHITE_X - 1 + i * 13, y + TOP_Y - 2, WHITE_P);
				letter->Render();
				break;
			}
			else {
				CLetter* letter = new CLetter(x + STAMINA_WHITE_X + i * 12, y + TOP_Y - 2, WHITE_STAMINA);
				letter->Render();
			}
		}

	};
	void Update(DWORD dt) {
		CMario* mario = dynamic_cast<CMario*>(this->mario);
		if (mario->GetLive() != 0) {
			this->Render();
		}
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }


};
