#pragma once

#include "../GameObject/GameObject.h"
#include "../Game/Animation.h"
#include "../Game/Animations.h"
#include "../GameObject/AssetIDs.h"
#include "../Mario.h"


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
#define TOP_Y -7

#define BOTTOM_Y 2

class CInfoBar : public CGameObject {
public:
	CGameObject* mario;

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

	CInfoBar(float x, float y, CGameObject* mario) : CGameObject(x, y) {
		this->mario = mario;
	}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		CMario* mario = dynamic_cast<CMario*>(this->mario);
		s->Get(ID_SPRITE_INFO_BAR)->Draw(x, y);

		s->Get(ID_SPRITE_LETTER_1)->Draw(x + WORLD_X, y + TOP_Y);

		std::vector<int> live = stringToNumbers(to_string(mario->getLive()));
		for (int i = 0; i < live.size(); i++) {
			CLetter* letter = new CLetter(x + LIVE_X + i * 8, y + BOTTOM_Y, live[i]);
			letter->Render();
		}

		string pointString = to_string(mario->getPoint());
		if (pointString.length() < 7) {
			pointString = string(7 - pointString.length(), '0') + pointString;
		}

		std::vector<int> point = stringToNumbers(pointString);
		for (int i = 0; i < point.size(); i++) {
			CLetter* letter = new CLetter(x + POINT_X + i * 8, y + BOTTOM_Y, point[i]);
			letter->Render();
		}

	};
	void Update(DWORD dt) {
		
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }


};
