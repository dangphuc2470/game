#pragma once
#include "../05-SceneManager/GameObject/GameObject.h"
#include "../05-SceneManager/Game/Animation.h"
#include "../05-SceneManager/Game/Animations.h"
#include "../05-SceneManager/Game/debug.h"
#include "../05-SceneManager/GameObject/AssetIDs.h"
#include "Landscape/Background.h"
#include "./Enemy/NewFireball.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.156f
#define MARIO_FIREBALL_SPEED	0.01f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f
#define MARIO_PIPE_SPEED			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

// RACOON MARIO
#define ID_ANI_MARIO_RACOON_IDLE_RIGHT 1700
#define ID_ANI_MARIO_RACOON_IDLE_LEFT 1701

#define ID_ANI_MARIO_RACOON_WALKING_RIGHT 1800
#define ID_ANI_MARIO_RACOON_WALKING_LEFT 1801

#define ID_ANI_MARIO_RACOON_RUNNING_RIGHT 1900
#define ID_ANI_MARIO_RACOON_RUNNING_LEFT 1901

#define ID_ANI_MARIO_RACOON_BRACE_RIGHT 2000
#define ID_ANI_MARIO_RACOON_BRACE_LEFT 2001

#define ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT 2100
#define ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT 2101

#define ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT 2200
#define ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT 2201

#define ID_ANI_MARIO_RACOON_FLY_RIGHT 2300
#define ID_ANI_MARIO_RACOON_FLY_LEFT 2301

#define ID_ANI_MARIO_RACOON_SIT_RIGHT 2400
#define ID_ANI_MARIO_RACOON_SIT_LEFT 2401
#define ID_ANI_MARIO_BOOM 2501

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACOON 3

#define MARIO_BIG_BBOX_WIDTH  12
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_RACOON_BBOX_HEIGHT 24
#define MARIO_RACOON_BBOX_WIDTH  12
#define MARIO_BIG_SITTING_BBOX_WIDTH  12
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)
#define MARIO_SIT_HEIGHT_ADJUST_RACOON ((MARIO_RACOON_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)
#define MARIO_RACOON_HEIGHT_ADJUST ((MARIO_RACOON_BBOX_HEIGHT-MARIO_BIG_BBOX_HEIGHT)/2)
#define MARIO_RACOON_SIT_HEIGHT_ADJUST ((MARIO_RACOON_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)
#define MARIO_SMALL_BBOX_WIDTH  12
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_SPINNING_TIME 200
#define MARIO_FLY_TIME 500
#define MARIO_FLY_SPEED 0.004f
#define MARIO_UNTOUCHABLE_TIME 2500  //Todo: change to 2.5s
#define MARIO_UNTOUCHABLE_BLINK_TIME 60
#define MARIO_BOOM_TIME 210
#define MARIO_PIPE_TIME 2000
#define LIVE_TIME 300 // 300s
#define MARIO_DIE_TIME 3000
#define MARIO_DECREASE_RUNNING_COUNT_TIME 220
#define MARIO_INCREASE_RUNNING_COUNT_TIME 300
#define MAX_STAMITA 9
#define STAMINA_TO_FLY 7
#define MARIO_MAP_MOVE_CORRECTION 5
#define MARIO_RACOON_GRAVITY_J 0.15f
#define MARIO_TOTAL_FLY_TIME 5000


class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level;
	int untouchable;
	int time_remaining = LIVE_TIME;
	ULONGLONG untouchable_start;
	ULONGLONG fly_start;
	ULONGLONG running_start;
	ULONGLONG last_invisible_time = -1;
	ULONGLONG one_second_count = -1;
	ULONGLONG die_start = -1;
	ULONGLONG fly_total_start = -1;
	BOOLEAN isOnPlatform;
	BOOLEAN isFlying;
	BOOLEAN isFlyable;
	BOOLEAN noFlash = false;
	BOOLEAN noBoom = false;
	int* coin;
	int running_count = 0;
	CGameObject* holdingObject = NULL;
	bool isReadyToHold = false;
	bool renderInvisibleSprite = false;
	bool isGetDownPipe = false;
	bool isGetUpPipe = false;
	bool isNoCountDown = false;
	bool isSpinning = false;
	bool isFacingRight = true;
	bool isFallingSlow = false;
	int* point;
	int* live;
	ULONGLONG spinning_start = -1;
	ULONGLONG getDownPipeStart = -1;
	ULONGLONG getUpPipeStart = -1;
	float targetX, targetY;
	CGameObject* guideObject = NULL;
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithTheVoid(LPCOLLISIONEVENT e);
	void OnCollisionWithPtooie(LPCOLLISIONEVENT e);
	void OnCollisionWithFireball(LPCOLLISIONEVENT e);
	void OnCollisionWithSpawner(LPCOLLISIONEVENT e);
	void OnCollisionWithButton(LPCOLLISIONEVENT e);
	void OnCollisionWithTeleport(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	//void OnCollisionWithGuider(LPCOLLISIONEVENT e);
	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();

public:
	CMario(float x, float y, int* coin, int* point, int* live, bool isNoCountDown) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;
		this->isNoCountDown = isNoCountDown;
		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		running_start = -1;
		fly_start = -1;
		die_start = -1;
		isOnPlatform = false;
		isFlying = false;
		isFlyable = true;
		one_second_count = GetTickCount64();
		this->coin = coin;
		this->point = point;
		this->live = live;
		//SetGuideObject();
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	//void SetGuideObject();
	void AppearPoint(int point);

	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel() { return level; }
	void StartUntouchable(bool noFlash = false, bool noBoom = false) {
		untouchable = 1; 
		untouchable_start = GetTickCount64();
		this->noFlash = noFlash;
		this->noBoom = noBoom;
		renderInvisibleSprite = true;
		last_invisible_time = GetTickCount64();
	}

	void StartSpinning();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetHoldingObject(CGameObject* obj) { holdingObject = obj; }
	void SetReadyToHold(bool ready) { isReadyToHold = ready; }
	bool GetReadyToHold() { return isReadyToHold; }
	void SetIsFlying(bool flying) {
		isFlying = flying;
		if (!flying)
			ay = MARIO_GRAVITY;
		else
			ay = MARIO_GRAVITY*0.1;
		fly_start = GetTickCount64();
	}
	bool GetIsOnPlatform() { return isOnPlatform; }

	void SetGravity(float gravity) { ay = gravity; }
	bool GetIsFlying() { return isFlying; }
	bool GetIsFlyable() { return isFlyable; }
	void SetIsFlyable(bool flyable) {
		isFlyable = flyable;
	}
	void SetIsFacingRight(bool facingRight) { isFacingRight = facingRight; }
	void SetIsOnPlatform(bool onPlatform) { isOnPlatform = onPlatform; 
	if (!isOnPlatform)
	{
		ay = MARIO_GRAVITY;
	}
	isFallingSlow = false;
	}
	void SetRunningStartToNow() { running_start = GetTickCount64(); }
	void MarioChangeSmallerLevel()
	{
		switch (level)
		{
		case MARIO_LEVEL_BIG:
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
			break;
		case MARIO_LEVEL_RACOON:
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
			break;

		default:
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
			break;
		}

	}

	void GetDownPipe() {
		isGetDownPipe = true;
		getDownPipeStart = GetTickCount64();
	}

	void GetUpPipe() {
		isGetUpPipe = true;
		getUpPipeStart = GetTickCount64();
		
	}

	void AddPoint(int point)
	{
		SetPoint(GetPoint() + point);
	}

	void AddCoin(int coin)
	{
		SetCoin(GetCoin() + coin);
	}

	void AddLive(int live)
	{
		SetLive(GetLive() + live);
	}

	int GetLive() { return *live; }
	void SetLive(int l) { *live = l; }
	void SetPoint(int p) { *point = p; }
	int GetPoint() { return *point; }
	int GetCoin() { return *coin; }
	void SetCoin(int c) { *coin = c; }
	int GetTimeRemaining() { return time_remaining; }
	void SetTimeRemaining(int t) { time_remaining = t; }
	int GetRunningCount() { return running_count; }
	void SetRunningCount(int r) { running_count = r; }
};


class CMarioMap: public CGameObject
{
	CMap* map;
	float targetX, targetY;
	int ax = 0; int  ay = 0;

	int currentIndexX = 0;
	int currentIndexY = 1;
public:
	CMarioMap(float x, float y, CGameObject* obj) : CGameObject(x, y) {
		targetX = x;
		targetY = y;
		map = dynamic_cast<CMap*>(obj);
		SetBlocking(0);
		SetCollidable(0);
	}


	void Render()
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_MARIO_MAP)->Render(x, y);

		
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		//Debug out current index x y
		

		if (x < targetX)
		{
			x += MARIO_RUNNING_SPEED * dt;
			if (x > targetX)
				x = targetX;
		}
		else if (x > targetX)
		{
			x -= MARIO_RUNNING_SPEED * dt;
			if (x < targetX)
				x = targetX;
		}
		if (y < targetY)
		{
			y += MARIO_RUNNING_SPEED * dt;
			if (y > targetY)
				y = targetY;
		}
		else if (y > targetY)
		{
			y -= MARIO_RUNNING_SPEED * dt;
			if (y < targetY)
				y = targetY;
		}




		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }



	void MoveRight() {
		if (currentIndexX < static_cast<int>(map->mapX.size()) - 1) {
			currentIndexX++;
			targetX = map->mapX[currentIndexX];
		}
	}

	void MoveLeft() {
		if (currentIndexX > 0) {
			currentIndexX--;
			targetX = map->mapX[currentIndexX];
		}
	}

	void MoveUp() {
		if (currentIndexY > 0) {
			currentIndexY--;
			targetY = map->mapY[currentIndexY];
		}
	}

	void MoveDown() {
		if (currentIndexY < static_cast<int>(map->mapY.size()) - 1) {
			currentIndexY++;
			targetY = map->mapY[currentIndexY];
		}
	}

	void MoveToMap()
	{
		map->MoveToMap(currentIndexX, currentIndexY, this);
	}


};