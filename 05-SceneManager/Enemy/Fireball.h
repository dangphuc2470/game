#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"

#define FIREBALL_WIDTH 7
#define FIREBALL_HEIGHT 6
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
    }

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
       //RenderBoundingBox();
    }

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override {
        left = x - FIREBALL_WIDTH / 2;
        top = y - FIREBALL_HEIGHT / 2;
        right = left + FIREBALL_WIDTH;
        bottom = top + FIREBALL_HEIGHT;
    }


};