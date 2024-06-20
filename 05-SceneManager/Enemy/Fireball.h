#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
#include "../Mario.h"

#define FIREBALL_WIDTH 7
#define FIREBALL_HEIGHT 100
#define FIREBALL_DISTANCE_LAST 250


class CFireBall : public CGameObject {
protected:
    float velocityX;
    float velocityY;
    float start_x;
    float start_y;

public:
    CFireBall(float x, float y, float velocityX, float velocityY) : CGameObject(x, y) {
        this->velocityX = velocityX;
        this->velocityY = velocityY;
   	    start_x = x;
        start_y = y;
        SetCollidable(true);
        SetBlocking(true);
        DebugOutTitle(L"Fireball create");

    }
    
    virtual void OnCollisionWith(LPCOLLISIONEVENT e)
    {
        DebugOutTitle(L"Fireball collision fb awdawda");
        if (dynamic_cast<CMario*>(e->obj)) {
			/*CMario* mario = dynamic_cast<CMario*>(e->obj);
            if (mario->GetLevel() == MARIO_LEVEL_SMALL)
                {
				mario->SetState(MARIO_STATE_DIE);
			}
			else
			{
				mario->SetLevel(MARIO_LEVEL_SMALL);
				mario->SetState(MARIO_STATE_IDLE);
			}*/
            e->obj->SetState(MARIO_STATE_DIE);
			isDeleted = true;
		}
		
    };

    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = nullptr) override {
        // Update fireball position based on its velocity
        x += velocityX * dt;
        y += velocityY * dt;

        float dx = abs(start_x - x);
        float dy = abs(start_y - y);
        if (dx > FIREBALL_DISTANCE_LAST || dy > FIREBALL_DISTANCE_LAST) {
            isDeleted = true;
        }

    }

    virtual void Render() override {
       //CSprites::GetInstance()->Get(5305)->Draw(x, y);
       CAnimations::GetInstance()->Get(ID_ANI_FIREBALL)->Render(x, y);
       RenderBoundingBox();
    }

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override {
        left = x - FIREBALL_WIDTH / 2;
        top = y - FIREBALL_HEIGHT / 2;
        right = left + FIREBALL_WIDTH;
        bottom = top + FIREBALL_HEIGHT;
    }


};