#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
#define PIPE_BBOX_WIDTH  31
#define PIPE_BBOX_HEIGHT 192

class CVerticalPipe: public CGameObject
{
public:
    CVerticalPipe(float x, float y) : CGameObject(x, y) {}
    void Render()
    {
        CSprites* sprites = CSprites::GetInstance();
        sprites->Get(ID_SPRITE_VERTICAL_PIPE)->Draw(x, y);
        //RenderBoundingBox();
    
    };
    void Update(DWORD dt) {}
    void GetBoundingBox(float& l, float& t, float& r, float& b)
    {
        l = x - PIPE_BBOX_WIDTH / 2;
        t = y - PIPE_BBOX_HEIGHT / 2;
        r = l + PIPE_BBOX_WIDTH;
        b = t + PIPE_BBOX_HEIGHT;
    };
};

