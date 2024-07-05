#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
#include "../Mario.h"

#define FIREBALL_WIDTH 7
#define FIREBALL_HEIGHT 7
#define FIREBALL_DISTANCE_LAST 250


class CFireBall : public CGameObject {
protected:
    float velocityX;
    float velocityY;
    float start_x;
    float start_y;
    CMario* mario;

public:
    CFireBall(float x, float y, float velocityX, float velocityY, CMario* mario) : CGameObject(x, y) {
        this->velocityX = velocityX;
        this->velocityY = velocityY;
   	    start_x = x;
        start_y = y;
        this->mario = mario;
        SetCollidable(true);
        SetBlocking(false);

    }
    
    virtual void OnCollisionWith(LPCOLLISIONEVENT e)
    {
        if (!e->obj->IsBlocking()) return;
		if (dynamic_cast<CMario*> (e->obj))
		{
			DebugOutTitle(L"Fireball Collision Mario");
			return;
		}
		if (e->ny != 0)
		{
			vy = 0;
		}
    };

    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = nullptr) override {
        // Update fireball position based on its velocity
        x += velocityX * dt;
        y += velocityY * dt;
        
        float marioX, marioY;
        mario->GetPosition(marioX, marioY);

        if (mario->GetLevel() == MARIO_LEVEL_SMALL) {
			if (abs(x - marioX) < MARIO_BIG_BBOX_WIDTH / 2 && abs(y - marioY) < MARIO_SMALL_BBOX_HEIGHT / 2)
			{
                mario->MarioChangeSmallerLevel();
                isDeleted = true;
			}
		}
		else if (abs(x - marioX) < FIREBALL_WIDTH / 2 && abs(y - marioY) < MARIO_BIG_BBOX_HEIGHT / 2)
		{
            isDeleted = true;
            mario->MarioChangeSmallerLevel();
		}
        
        
        float dx = abs(start_x - x);
        float dy = abs(start_y - y);
        if (dx > FIREBALL_DISTANCE_LAST || dy > FIREBALL_DISTANCE_LAST) {
            isDeleted = true;
        }
        CGameObject::Update(dt);
        CCollision::GetInstance()->Process(this, dt, coObjects);
    }

    virtual void Render() override {
       //CSprites::GetInstance()->Get(5305)->Draw(x, y);
       CAnimations::GetInstance()->Get(ID_ANI_FIREBALL)->Render(x, y);
       //RenderBoundingBox();
    }

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override {
        left = x - FIREBALL_WIDTH / 2;
        top = y - FIREBALL_HEIGHT / 2;
        right = left + FIREBALL_WIDTH;
        bottom = top + FIREBALL_HEIGHT;
    }


};