#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
#include "../Mario.h"
#define GUIDE_BBOX_WIDTH 1
#define GUIDE_BBOX_HEIGHT 21
#define GUIDE_MARIO_BBOX_WIDTH 13
#define GUIDE_MARIO_BBOX_HEIGHT 13
#define GUIDE_GRAVITY 0.0001f
#define GUIDE_MARIO_SPEED 0.05f

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

    virtual  void DeleteKoopa();

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
        

        if (dynamic_cast<CMario*> (e->obj))
        {
            //DebugOutTitle(L"GuideObject Collision Mario");
            return;
        }

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














//
//
//
//class CGuideObjectMario : public CGameObject
//{
//    CMario* mario;
//public:
//    CGuideObjectMario(CMario* mario)
//    {
//        this->mario = mario;
//        SetCollidable(true);
//    }
//    virtual void Render()
//    {
//        RenderBoundingBox();
//    }
//    virtual int IsCollidable() { return isCollidable; };
//    virtual int IsBlocking() { return 0; }
//    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
//    {
//        left = x - GUIDE_MARIO_BBOX_WIDTH / 2;
//        top = y - GUIDE_MARIO_BBOX_HEIGHT / 2;
//        right = left + GUIDE_MARIO_BBOX_WIDTH;
//        bottom = top + GUIDE_MARIO_BBOX_HEIGHT;
//    };
//
//    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
//
//    virtual void OnNoCollision(DWORD dt)
//    {
//        x += vx * dt;
//		y += vy * dt;
//    };
//
//    virtual void OnCollisionWith(LPCOLLISIONEVENT e)
//    {
//        DebugOutTitle(L"GuideObjectMario Collision");
//    }
//};