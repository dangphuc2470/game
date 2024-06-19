#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>
#include "../Game/debug.h"
#include "../Game/Animation.h"
#include "../Game/Animations.h"
#include "../Game/Sprites.h"
#include "../GameObject/Collision.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define BBOX_ALPHA 0.25f		// Bounding box transparency

class CGameObject
{
protected:

	float x; 
	float y;
	float top;
	float bottom;
	float vx;
	float vy;
	int isBlocking = true;
	int nx;	 
	bool isCollidable = false;
	int state;

	

public: 
	bool isDeleted;
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetPositionTopBot(float &t, float &b) { t = this->top; b = this->bottom; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void SetBlocking(bool isBlocking) { this->isBlocking = isBlocking; }
	int GetState() { return this->state; }
	virtual void Delete() { isDeleted = true;  }
	bool IsDeleted() { return isDeleted; }
	void RenderBoundingBox();

	CGameObject();
	CGameObject(float x, float y) :CGameObject() { this->x = x; this->y = y; }


	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; 	}

	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return isCollidable; };
	virtual void SetCollidable(bool isCollidable) { this->isCollidable = isCollidable;};

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
	
	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return isBlocking; }
	virtual int IsDirectionColliable(float nx, float ny) { return 1; }


	~CGameObject();

	static bool IsDeleted(const LPGAMEOBJECT &o) { return o->isDeleted; }
};
