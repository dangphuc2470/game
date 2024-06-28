#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_MARIO2 30

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_GOOMBA_WINGS	7
#define OBJECT_TYPE_KOOPA_RED	3
#define OBJECT_TYPE_KOOPA_RED_WINGS	8
#define OBJECT_TYPE_KOOPA_GREEN	9
#define OBJECT_TYPE_KOOPA_GREEN_WINGS	10
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_BRICK_PLATFORM 6
#define OBJECT_TYPE_LARGE_BUSH_1 100
#define OBJECT_TYPE_LARGE_BUSH_2 110
#define OBJECT_TYPE_CLOUD_1 120
#define OBJECT_TYPE_CLOUD_2 130
#define OBJECT_TYPE_SMALL_BUSH 140

#define OBJECT_TYPE_BOX_PLATFORM 150
#define OBJECT_TYPE_BLACK_BACKGROUND 170
#define OBJECT_TYPE_VERTICAL_PIPE 180
#define OBJECT_TYPE_MYSTERY_BOX 190

#define OBJECT_TYPE_PTOOIE 200
#define OBJECT_TYPE_FIREBALL 210
#define OBJECT_TYPE_MUSHROOM 220
#define OBJECT_TYPE_SPAWNER 230
#define OBJECT_TYPE_GUIDE 240
#define OBJECT_TYPE_FIREBALL 250
#define OBJECT_TYPE_WOODEN 260
#define OBJECT_TYPE_BUTTON 270
#define OBJECT_TYPE_PORTAL	50
#define OBJECT_TYPE_FLOWER	280
#define OBJECT_TYPE_CLOUD_SOLID	290
#define OBJECT_TYPE_BUNKER	300
#define OBJECT_TYPE_TELEPORT	310

#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)
#define ID_SPRITE_MARIO_INVISIBLE (14901)
#pragma endregion 

//#pragma region MARIO2
//#define ID_SPRITE_MARIO2 70000
//#define ID_SPRITE_MARIO2_BIG (ID_SPRITE_MARIO2 + 1000)
//#define ID_SPRITE_MARIO2_BIG_IDLE (ID_SPRITE_MARIO2_BIG + 100)
//#define ID_SPRITE_MARIO2_BIG_IDLE_LEFT (ID_SPRITE_MARIO2_BIG_IDLE + 10)
//#define ID_SPRITE_MARIO2_BIG_IDLE_RIGHT (ID_SPRITE_MARIO2_BIG_IDLE + 20)
//
//#define ID_SPRITE_MARIO2_BIG_WALKING (ID_SPRITE_MARIO2_BIG + 200)
//#define ID_SPRITE_MARIO2_BIG_WALKING_LEFT (ID_SPRITE_MARIO2_BIG_WALKING + 10)
//#define ID_SPRITE_MARIO2_BIG_WALKING_RIGHT (ID_SPRITE_MARIO2_BIG_WALKING + 20)
//#define ID_SPRITE_MARIO2_BIG_RUNNING (ID_SPRITE_MARIO2_BIG + 300)
//#define ID_SPRITE_MARIO2_BIG_RUNNING_LEFT (ID_SPRITE_MARIO2_BIG_RUNNING + 10)
//#define ID_SPRITE_MARIO2_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO2_BIG_RUNNING + 20)
//#define ID_SPRITE_MARIO2_BIG_JUMP (ID_SPRITE_MARIO2_BIG + 400)
//#define ID_SPRITE_MARIO2_BIG_JUMP_WALK (ID_SPRITE_MARIO2_BIG_JUMP + 10)
//#define ID_SPRITE_MARIO2_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO2_BIG_JUMP_WALK + 2)
//#define ID_SPRITE_MARIO2_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO2_BIG_JUMP_WALK + 6)
//#define ID_SPRITE_MARIO2_BIG_JUMP_RUN (ID_SPRITE_MARIO2_BIG_JUMP + 20)
//#define ID_SPRITE_MARIO2_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO2_BIG_JUMP_RUN + 2)
//#define ID_SPRITE_MARIO2_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO2_BIG_JUMP_RUN + 6)
//#define ID_SPRITE_MARIO2_BIG_SIT (ID_SPRITE_MARIO2_BIG + 500)
//#define ID_SPRITE_MARIO2_BIG_SIT_LEFT (ID_SPRITE_MARIO2_BIG_SIT + 10)
//#define ID_SPRITE_MARIO2_BIG_SIT_RIGHT (ID_SPRITE_MARIO2_BIG_SIT + 20)
//#define ID_SPRITE_MARIO2_BIG_BRACE (ID_SPRITE_MARIO2_BIG + 600)
//#define ID_SPRITE_MARIO2_BIG_BRACE_LEFT (ID_SPRITE_MARIO2_BIG_BRACE + 10)
//#define ID_SPRITE_MARIO2_BIG_BRACE_RIGHT (ID_SPRITE_MARIO2_BIG_BRACE + 20)
//#define ID_SPRITE_MARIO2_DIE (ID_SPRITE_MARIO2 + 3000)
//#define ID_SPRITE_MARIO2_SMALL (ID_SPRITE_MARIO2 + 2000)
//#define ID_SPRITE_MARIO2_SMALL_IDLE (ID_SPRITE_MARIO2_SMALL + 100)
//#define ID_SPRITE_MARIO2_SMALL_IDLE_LEFT (ID_SPRITE_MARIO2_SMALL_IDLE + 10)
//#define ID_SPRITE_MARIO2_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO2_SMALL_IDLE + 20)
//#define ID_SPRITE_MARIO2_SMALL_WALKING (ID_SPRITE_MARIO2_SMALL + 200)
//#define ID_SPRITE_MARIO2_SMALL_WALKING_LEFT (ID_SPRITE_MARIO2_SMALL_WALKING + 10)
//#define ID_SPRITE_MARIO2_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO2_SMALL_WALKING + 20)
//#define ID_SPRITE_MARIO2_SMALL_RUNNING (ID_SPRITE_MARIO2_SMALL + 300)
//#define ID_SPRITE_MARIO2_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO2_SMALL_RUNNING + 10)
//#define ID_SPRITE_MARIO2_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO2_SMALL_RUNNING + 20)
//#define ID_SPRITE_MARIO2_SMALL_JUMP (ID_SPRITE_MARIO2_SMALL + 400)
//#define ID_SPRITE_MARIO2_SMALL_JUMP_WALK (ID_SPRITE_MARIO2_SMALL_JUMP + 10)
//#define ID_SPRITE_MARIO2_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO2_SMALL_JUMP_WALK + 2)
//#define ID_SPRITE_MARIO2_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO2_SMALL_JUMP_WALK + 6)
//#define ID_SPRITE_MARIO2_SMALL_JUMP_RUN (ID_SPRITE_MARIO2_SMALL_JUMP + 20)
//#define ID_SPRITE_MARIO2_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO2_SMALL_JUMP_RUN + 2)
//#define ID_SPRITE_MARIO2_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO2_SMALL_JUMP_RUN + 6)
//#define ID_SPRITE_MARIO2_SMALL_SIT (ID_SPRITE_MARIO2_SMALL + 500)
//#define ID_SPRITE_MARIO2_SMALL_SIT_LEFT (ID_SPRITE_MARIO2_SMALL_SIT + 10)
//#define ID_SPRITE_MARIO2_SMALL_SIT_RIGHT (ID_SPRITE_MARIO2_SMALL_SIT + 20)
//#define ID_SPRITE_MARIO2_SMALL_BRACE (ID_SPRITE_MARIO2_SMALL + 500)
//#define ID_SPRITE_MARIO2_SMALL_BRACE_LEFT (ID_SPRITE_MARIO2_SMALL_BRACE + 10)
//#define ID_SPRITE_MARIO2_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO2_SMALL_BRACE + 20)
//#pragma endregion



#define ID_SPRITE_BRICK 20000
#define ID_ANI_BRICK 9000
#define ID_ANI_BRICK_BROKEN 9001

#define ID_SPRITE_MYSTERY_BOX_UNBOX (OBJECT_TYPE_MYSTERY_BOX + 1)
#define ID_ANI_MYSTERY_BOX (OBJECT_TYPE_MYSTERY_BOX + 2)

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
#define ID_ANI_GOOMBA_FLY_WALK 5002
#define ID_ANI_GOOMBA_FLY_FLY 5003
#define ID_ANI_GOOMBA_FLY_NO_WINGS 5004
#define ID_ANI_GOOMBA_FLY_DIE 5005

#define ID_ANI_KOOPA_WALKING_GREEN_LEFT 5100
#define ID_ANI_KOOPA_WALKING_GREEN_RIGHT 5101
#define ID_ANI_KOOPA_DIE_GREEN 5102
#define ID_ANI_KOOPA_FLY_GREEN_LEFT 5103
#define ID_ANI_KOOPA_FLY_GREEN_RIGHT 5104
#define ID_ANI_KOOPA_WALKING_RED_LEFT 5105
#define ID_ANI_KOOPA_WALKING_RED_RIGHT 5106
#define ID_ANI_KOOPA_DIE_RED 5107
#define ID_ANI_KOOPA_FLY_RED_LEFT 5108
#define ID_ANI_KOOPA_FLY_RED_RIGHT 5109
#define ID_ANI_KOOPA_FLASH_GREEN 5110
#define ID_ANI_KOOPA_FLASH_RED 5111

#define ID_ANI_PTOOIE_BITE 5200
//#define ID_ANI_PTOOIE_RED_RIGHT 5201
//#define ID_ANI_PTOOIE_GREEN_LEFT 5202
//#define ID_ANI_PTOOIE_GREEN_RIGHT 5203
//#define ID_ANI_PTOOIE_GREEN_BITE_LEFT 5204
//#define ID_ANI_PTOOIE_GREEN_BITE_RIGHT 5205

#define ID_ANI_FIREBALL 5301


#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)
#define ID_SPRITE_GOOMBA_WINGS (ID_SPRITE_GOOMBA + 3000)

#define ID_SPRITE_KOOPA_WALKING 70000 // No use
#define ID_SPRITE_KOOPA_WALKING_GREEN (ID_SPRITE_KOOPA_WALKING + 1000)
#define ID_SPRITE_KOOPA_DIE_GREEN (ID_SPRITE_KOOPA_WALKING + 2000)
#define ID_SPRITE_KOOPA_FLY_GREEN (ID_SPRITE_KOOPA_WALKING + 3000)
#define ID_SPRITE_KOOPA_WALKING_RED (ID_SPRITE_KOOPA_WALKING + 4000)
#define ID_SPRITE_KOOPA_DIE_RED (ID_SPRITE_KOOPA_WALKING + 5000)
#define ID_SPRITE_KOOPA_FLY_RED (ID_SPRITE_KOOPA_WALKING + 6000)



#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000 //This only use to define ID_SPRITE_CLOUD_BEGIN, ID_SPRITE_CLOUD_MIDDLE, ID_SPRITE_CLOUD_END
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)

#define ID_SPRITE_BRICK_PLATFORM 60000
#define ID_SPRITE_BRICK_PLATFORM_BEGIN (ID_SPRITE_BRICK_PLATFORM + 1000)
#define ID_SPRITE_BRICK_PLATFORM_MIDDLE (ID_SPRITE_BRICK_PLATFORM + 2000)
#define ID_SPRITE_BRICK_PLATFORM_END (ID_SPRITE_BRICK_PLATFORM + 3000)

#define ID_SPRITE_LARGE_BUSH_1 (OBJECT_TYPE_LARGE_BUSH_1 + 1)
#define ID_SPRITE_LARGE_BUSH_2 (OBJECT_TYPE_LARGE_BUSH_2 + 1)

#define ID_SPRITE_CLOUD_1 (OBJECT_TYPE_CLOUD_1 + 1)
#define ID_SPRITE_CLOUD_2 (OBJECT_TYPE_CLOUD_2 + 1)
#define ID_SPRITE_SMALL_BUSH (OBJECT_TYPE_SMALL_BUSH + 1)

#define ID_SPRITE_BOX_PLATFORM_SQUARE_PINK (OBJECT_TYPE_BOX_PLATFORM + 1)
#define ID_SPRITE_BOX_PLATFORM_RECTANGLE_PINK_GROUND_HORIZONTAL (OBJECT_TYPE_BOX_PLATFORM + 2)
#define ID_SPRITE_BOX_PLATFORM_RECTANGLE_PINK_SKY_HORIZONTAL (OBJECT_TYPE_BOX_PLATFORM + 3)
#define ID_SPRITE_BOX_PLATFORM_RECTANGLE_PINK_LARGE_HORIZONTAL (OBJECT_TYPE_BOX_PLATFORM + 4)
#define ID_SPRITE_BOX_PLATFORM_RECTANGLE_PINK_TALL_VERTICAL (OBJECT_TYPE_BOX_PLATFORM + 13)

#define ID_SPRITE_BOX_PLATFORM_GREEN_SHORT_HORIZONTAL (OBJECT_TYPE_BOX_PLATFORM + 5)
#define ID_SPRITE_BOX_PLATFORM_GREEN_SHORT_FAT_HORIZONTAL (OBJECT_TYPE_BOX_PLATFORM + 6)
#define ID_SPRITE_BOX_PLATFORM_GREEN_LONG_HORIZONTAL (OBJECT_TYPE_BOX_PLATFORM + 7)
#define ID_SPRITE_BOX_PLATFORM_GREEN_LONG_VERTICAL (OBJECT_TYPE_BOX_PLATFORM + 8)
#define ID_SPRITE_BOX_PLATFORM_BLUE_TALL (OBJECT_TYPE_BOX_PLATFORM + 9)
#define ID_SPRITE_BOX_PLATFORM_BLUE_FAT (OBJECT_TYPE_BOX_PLATFORM + 10)
#define ID_SPRITE_BOX_PLATFORM_BLUE_SHORT (OBJECT_TYPE_BOX_PLATFORM + 11)
#define ID_SPRITE_BOX_PLATFORM_WHITE_TALL (OBJECT_TYPE_BOX_PLATFORM + 12)
#define ID_SPRITE_BLACK_BACKGROUND (OBJECT_TYPE_BLACK_BACKGROUND + 1)
#define ID_SPRITE_VERTICAL_PIPE (OBJECT_TYPE_VERTICAL_PIPE + 1)
#define ID_SPRITE_MUSHROOM_RED (OBJECT_TYPE_MUSHROOM + 1)
#define ID_SPRITE_MUSHROOM_GREEN (OBJECT_TYPE_MUSHROOM + 2)
#define ID_SPRITE_WOODEN (OBJECT_TYPE_WOODEN + 1)
#define ID_SPRITE_BUTTON_PRESSED (OBJECT_TYPE_BUTTON + 1)
#define ID_ANI_BUTTON_NORMAL (OBJECT_TYPE_BUTTON + 2)
#define ID_SPRITE_FLOWER (OBJECT_TYPE_FLOWER + 1)
#define ID_SPRITE_CLOUD_SOLID (OBJECT_TYPE_CLOUD_SOLID + 1)
#define ID_SPRITE_BUNKER (OBJECT_TYPE_BUNKER + 1)