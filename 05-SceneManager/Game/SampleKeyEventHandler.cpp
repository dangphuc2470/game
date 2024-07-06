#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "../Mario.h"
#include "../Scene/PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	CMarioMap* marioMap = (CMarioMap *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetMarioMap();
	if (marioMap != NULL)
	{
		switch (KeyCode)
		{
		case DIK_DOWN:
			marioMap->MoveDown();
			break;
		case DIK_UP:
			marioMap->MoveUp();
			break;
		case DIK_LEFT:
			marioMap->MoveLeft();
			break;
		case DIK_RIGHT:
			marioMap->MoveRight();
			break;
		case DIK_S:
			marioMap->MoveToMap();
			break;
		}

	}
	
	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
	if (mario->GetLevel() == MARIO_LEVEL_RACOON && mario->GetRunningCount() >= STAMINA_TO_FLY)
		mario->SetIsFlying(true);
	else
		mario->SetState(MARIO_STATE_JUMP);
	break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACOON);
		break;
	case DIK_4:
		mario->SetIsFlying(true);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		CGame::GetInstance()->InitiateSwitchScene(5);
		break;
	case DIK_A:
		if (!isPressingRun)
		{
			mario->SetRunningStartToNow();
			mario->SetIsFlyable(true);
		}
		isPressingRun = true;

		if (mario->GetLevel() == MARIO_LEVEL_RACOON)
			mario->StartSpinning();
		break;
	}

}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		mario->SetReadyToHold(false);
		isPressingRun = false;
		break;
	case DIK_LEFT:
		isPressingRun = false;
		break;
	case DIK_RIGHT:
		isPressingRun = false;
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	//debug out the isPressingRun
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (game->IsKeyDown(DIK_A))
	{
		mario->SetReadyToHold(true);
	}

	if (game->IsKeyDown(DIK_RIGHT))
	{
		mario->SetIsFacingRight(true);


		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		
		/*if (!isPressingRun)
			mario->SetRunningStartToNow();
		isPressingRun = true;*/
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		mario->SetIsFacingRight(false);

		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);

		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
		
		/*if (!isPressingRun)
			mario->SetRunningStartToNow();
		isPressingRun = true;*/
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}