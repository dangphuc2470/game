#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
#include "../Mario.h"
#define GUIDE_BBOX_WIDTH 16
#define GUIDE_BBOX_HEIGHT 21
#define GUIDE_GRAVITY 0.0001f

class CKoopa;

class CGuideObject : public CGameObject
{
    float ax;
    float ay;
    CKoopa* koopa;// The Koopa this object is guiding
public:
    CGuideObject(CKoopa* koopa)
    {
        this->ax = 0;
        this->ay = GUIDE_GRAVITY;
        this->koopa = koopa;
    }

    virtual void Render()
	{
        //CSprites::GetInstance()->Get(ID_SPRITE_CLOUD_MIDDLE)->Draw(x, y);

        //RenderBoundingBox();
    }

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x - GUIDE_BBOX_WIDTH / 2;
        top = y - GUIDE_BBOX_HEIGHT / 2;
        right = left + GUIDE_BBOX_WIDTH;
        bottom = top + GUIDE_BBOX_HEIGHT;
	};

    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

    virtual void OnNoCollision(DWORD dt)
    {
        x += vx * dt;
        y += vy * dt;
    };	
    
    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }

    virtual void OnCollisionWith(LPCOLLISIONEVENT e)
    {
        if (!e->obj->IsBlocking()) return;
        if (dynamic_cast<CMario*>(e->obj)) return;

        if (e->ny != 0)
        {
            vy = 0;
        }
        /*else if (e->nx != 0)
        {
            vx = -vx;
        }*/
    };
};