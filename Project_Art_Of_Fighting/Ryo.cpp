#include "Ryo.h"



Ryo::Ryo(int player)
{
	characterType = RYO;
	this->player = player;
	specialDmg = 15;

	colliderOffsetX = 15;
	//idle animation (arcade sprite sheet)
	//Rect Colliders
	SDL_Rect rect1 = { -10,-40,25,20 };
	SDL_Rect rect2 = { -20,-20,45,60 };
	SDL_Rect rect3 = { -25,40,50,30 };

	//Jump Colliders
	SDL_Rect head_jump_collider = { -10,-55,25,20 };
	SDL_Rect body_jump_collider = { -20,-40,45,60 };
	SDL_Rect legs_jump_collider = { -25,10,50,30 };

	//Jump Punch Colliders
	SDL_Rect head_jumppunch_collider = { -10,-55,25,20 };
	SDL_Rect body_jumppunch_collider = { -25,-44,35,60 };
	SDL_Rect legs_jumppunch_collider = { -30,5,37,30 };


	//Jump Kick Colliders
	SDL_Rect head_jumpkick_collider = { -10,-50,25,20 };
	SDL_Rect body_jumpkick_collider = { -25,-44,35,45 };
	SDL_Rect legs_jumpkick_collider = { -30,-5,47,30 };

	//Crouch Rect Colliders
	SDL_Rect head_crouch_collider = { -10,-8,25,20 };
	SDL_Rect body_crouch_collider = { -20,8,50,58 };

	//Crouch Punch Rect Colliders
	SDL_Rect head_crouchPunch_collider = { 5,-8,25,20 };
	SDL_Rect body_crouchPunch_collider = { -10,8,50,58 };

	//Recover Colliders
	SDL_Rect head_recover_collider = { -10,-19,25,27 };
	SDL_Rect body_recover_collider = { -29,8,55,58 };

	//Kick Colliders
	SDL_Rect head_kick_collider = { -30,-50,25,20 };
	SDL_Rect body_kick_collider = { -30,-30,33,60 };
	SDL_Rect legs_kick_collider = { -27,30,30,40 };

	//Hit Collider
	SDL_Rect hit_punch_colllider = { 20,-25,43,10 };
	SDL_Rect hit_kick_collider = { 5,-45,60,40 };

	//IDLE
	idle.SetReverseOffset({ -27,-43 }, 2);
	idle.PushBack({ 0, 8, 66, 108 }, -29, -43, 2, rect1, rect2, rect3);
	idle.SetReverseOffset({ -28,-43 }, 2);
	idle.PushBack({ 68, 8, 67, 108 }, -29, -43, 2, rect1, rect2, rect3);
	idle.SetReverseOffset({ -30,-43 }, 2);
	idle.PushBack({ 135 , 8, 69, 108 }, -29, -43, 2, rect1, rect2, rect3);


	idle.speed = 0.25f;

	//crouch animation (arcade sprite sheet)

	crouch.SetReverseOffset({ -21,-18 }, 2);
	crouch.PushBack({ 0, 503, 60, 83 }, -29, -18, 2, head_crouch_collider, body_crouch_collider);
	crouch.SetReverseOffset({ -28,-8 }, 2);
	crouch.PushBack({ 815, 43, 62, 73 }, -24, -8, 2, head_crouch_collider, body_crouch_collider);
	crouch.speed = 0.5f;
	crouch.loop = false;

	//crouched punch animation (arcade sprite sheet)
	crouch_punch.SetReverseOffset({ -22,-9 }, 2);
	crouch_punch.PushBack({ 416, 42, 53, 74 }, -19, -9, 2, { -5,-8,25,20 }, body_crouchPunch_collider);
	crouch_punch.SetReverseOffset({ -63,-10 }, 4);
	crouch_punch.PushBack({ 469, 41,109, 75 }, -33, -10, 4, head_crouchPunch_collider, body_crouchPunch_collider, {}, { 30,5,43,10 });
	crouch_punch.SetReverseOffset({ -35,-10 }, 4);
	crouch_punch.PushBack({ 578, 41, 67, 75 }, -21, -10, 4, { -5,-8,25,20 }, body_crouchPunch_collider);
	crouch_punch.speed = 0.5f;
	crouch_punch.damage = 20;
	crouch_punch.loop = false;

	//crouched kick animation (arcade sprite sheet)
	crouch_kick.SetReverseOffset({ -21,-1 }, 3);
	crouch_kick.PushBack({ 867,169,55,66 }, -24, -1, 3, { -5,-8,25,20 }, body_crouchPunch_collider);
	crouch_kick.SetReverseOffset({ -65,-3 }, 4);
	crouch_kick.PushBack({ 0,280,127,68 }, -50, -3, 4, { -5, -8, 25, 20 }, body_crouchPunch_collider, {}, { 10, 40, 70, 23 });
	crouch_kick.SetReverseOffset({ -21,-1 }, 3);
	crouch_kick.PushBack({ 867,169,55,66 }, -24, -1, 3, { -5,-8,25,20 }, body_crouchPunch_collider);
	crouch_kick.speed = 0.5f;
	crouch_kick.damage = 20;
	crouch_kick.loop = false;

	// walk forward animation (arcade sprite sheet)
	forward.SetReverseOffset({ -25, -43 }, 3);
	forward.PushBack({ 693, 348, 58 , 108 }, -21, -43, 3, rect1, rect2, rect3);
	forward.SetReverseOffset({ -25, -43 }, 3);
	forward.PushBack({ 751, 348, 69 , 108 }, -32, -43, 3, rect1, rect2, rect3);
	forward.SetReverseOffset({ -25, -43 }, 3);
	forward.PushBack({ 820, 348, 58 , 108 }, -21, -43, 3, rect1, rect2, rect3);
	forward.SetReverseOffset({ -28, -43 }, 3);
	forward.PushBack({ 878, 348, 67 , 108 }, -29, -43, 3, rect1, rect2, rect3);
	forward.speed = 0.25f;

	// walk backward animation (arcade sprite sheet)
	backward.SetReverseOffset({ -21, -42 }, 3);
	backward.PushBack({ 577, 479, 59 , 107 }, -29, -42, 3, rect1, rect2, rect3);
	backward.SetReverseOffset({ -21, -44 }, 3);
	backward.PushBack({ 636, 477, 54 , 109 }, -25, -44, 3, rect1, rect2, rect3);
	backward.SetReverseOffset({ -21, -42 }, 3);
	backward.PushBack({ 690, 478, 61 , 107 }, -32, -42, 3, rect1, rect2, rect3);
	backward.SetReverseOffset({ -21, -44 }, 3);
	backward.PushBack({ 636, 477, 54 , 109 }, -25, -44, 3, rect1, rect2, rect3);
	backward.speed = 0.25f;

	// punch animation (arcade sprite sheet)
	punch.SetReverseOffset({ -19, -41 }, 2);
	punch.PushBack({ 488, 350, 58, 106 }, -29, -41, 2, rect1, rect2, rect3);
	punch.SetReverseOffset({ -50, -41 }, 3);
	punch.PushBack({ 546, 350, 89 , 106 }, -29, -41, 3, rect1, rect2, rect3, hit_punch_colllider);
	punch.SetReverseOffset({ -19, -41 }, 3);
	punch.PushBack({ 488, 350, 58, 106 }, -29, -41, 3, rect1, rect2, rect3);
	punch.speed = 0.5f;
	punch.loop = false;
	punch.damage = 10;

	// kick animation (arcade sprite sheet)
	kick.SetReverseOffset({ -15, -45 }, 4);
	kick.PushBack({ 669, 235, 60, 110 }, -35, -45, 4, head_kick_collider, body_kick_collider, legs_kick_collider);
	kick.SetReverseOffset({ -13,-48 }, 4);
	kick.PushBack({ 729, 235, 61 , 113 }, -38, -48, 4, head_kick_collider, body_kick_collider, legs_kick_collider);
	kick.SetReverseOffset({ -49, -48 }, 8);
	kick.PushBack({ 790, 235, 103, 113 }, -44, -48, 8, head_kick_collider, body_kick_collider, legs_kick_collider, hit_kick_collider);
	kick.SetReverseOffset({ -13,-48 }, 4);
	kick.PushBack({ 729, 235, 61 , 113 }, -38, -48, 4, head_kick_collider, body_kick_collider, legs_kick_collider, hit_kick_collider);
	kick.speed = 1.0f;
	kick.damage = 10;
	kick.loop = false;

	//jump animation (arcade sprite sheet)
	jump.loop = false;
	jump.SetReverseOffset({ -23, -18 }, 4);
	jump.PushBack({ 0, 503, 60, 83 }, -29, -18, 4, head_recover_collider, body_recover_collider);
	jump.SetReverseOffset({ -23, -65 }, 5);
	jump.PushBack({ 60, 456, 66 , 130 }, -29, -65, 5, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 0, -8 });
	jump.SetReverseOffset({ -23, -58 }, 7);
	jump.PushBack({ 126, 471, 62, 113 }, -29, -58, 7, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 0,-4 });
	jump.SetReverseOffset({ -20, -58 }, 3);
	jump.PushBack({ 188, 474, 57 , 110 }, -26, -58, 3, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 0,-4 });
	jump.SetReverseOffset({ -20, -58 }, 9);
	jump.PushBack({ 245, 492, 52 , 92 }, -26, -58, 9, head_jump_collider, body_jump_collider, legs_jump_collider);
	jump.SetReverseOffset({ -20, -58 }, 5);
	jump.PushBack({ 245, 492, 52 , 92 }, -26, -58, 5, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 0,+2 });
	jump.SetReverseOffset({ -19, -55 }, 13);
	jump.PushBack({ 299, 471 , 57 , 115 }, -25, -55, 13, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 0,+5 });
	jump.SetReverseOffset({ -23, -18 }, 6);
	jump.PushBack({ 0, 503, 60, 83 }, -29, -18, 6, head_jump_collider, body_jump_collider, legs_jump_collider);
	jump.speed = 0.9f;

	//jump forward animation (arcade sprite sheet)
	jump_forward.loop = false;
	jump_forward.SetReverseOffset({ -29,-18 }, 4);
	jump_forward.PushBack({ 0, 503, 60, 83 }, -29, -18, 4, head_recover_collider, body_recover_collider);
	jump_forward.SetReverseOffset({ -29,-65 }, 5);
	jump_forward.PushBack({ 60, 456, 66 , 130 }, -29, -65, 5, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 3,-8 });
	jump_forward.SetReverseOffset({ -29,-58 }, 7);
	jump_forward.PushBack({ 126, 471, 62, 113 }, -29, -58, 7, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 3,-4 });
	jump_forward.SetReverseOffset({ -26,-58 }, 3);
	jump_forward.PushBack({ 188, 474, 57 , 110 }, -26, -58, 3, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 3,-3 });
	jump_forward.SetReverseOffset({ -26,-58 }, 10);
	jump_forward.PushBack({ 245, 492, 52 , 92 }, -26, -58, 10, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 2,+1 });
	jump_forward.SetReverseOffset({ -26,-58 }, 5);
	jump_forward.PushBack({ 245, 492, 52 , 92 }, -26, -58, 5, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 2,+2 });
	jump_forward.SetReverseOffset({ -25,-55 }, 12);
	jump_forward.PushBack({ 299, 471 , 57 , 115 }, -25, -55, 12, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 2,+5 });
	jump_forward.SetReverseOffset({ -29,-18 }, 6);
	jump_forward.PushBack({ 0, 503, 60, 83 }, -29, -18, 6, head_jump_collider, body_jump_collider, legs_jump_collider, { 0, 0 });
	jump_forward.speed = 0.9f;

	//jump backward animation (arcade sprite sheet)
	jump_backward.loop = false;
	jump_backward.SetReverseOffset({ -29,-18 }, 4);
	jump_backward.PushBack({ 0, 503, 60, 83 }, -29, -18, 4, head_recover_collider, body_recover_collider);
	jump_backward.SetReverseOffset({ -29,-65 }, 5);
	jump_backward.PushBack({ 60, 456, 66 , 130 }, -29, -65, 5, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { -3,-8 });
	jump_backward.SetReverseOffset({ -29,-58 }, 7);
	jump_backward.PushBack({ 126, 471, 62, 113 }, -29, -58, 7, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { -3,-4 });
	jump_backward.SetReverseOffset({ -26,-58 }, 3);
	jump_backward.PushBack({ 188, 474, 57 , 110 }, -26, -58, 3, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { -3,-3 });
	jump_backward.SetReverseOffset({ -26,-58 }, 10);
	jump_backward.PushBack({ 245, 492, 52 , 92 }, -26, -58, 10, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { -2,+1 });
	jump_backward.SetReverseOffset({ -26,-58 }, 5);
	jump_backward.PushBack({ 245, 492, 52 , 92 }, -26, -58, 5, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { -2,+2 });
	jump_backward.SetReverseOffset({ -25,-55 }, 12);
	jump_backward.PushBack({ 299, 471 , 57 , 115 }, -25, -55, 12, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { -2,+5 });
	jump_backward.SetReverseOffset({ -29,-18 }, 6);
	jump_backward.PushBack({ 0, 503, 60, 83 }, -29, -18, 6, head_jump_collider, body_jump_collider, legs_jump_collider);
	jump_backward.speed = 0.9f;

	//falling animation
	fall.loop = false;
	fall.SetReverseOffset({ -25, -55 }, 12);
	fall.PushBack({ 299, 471 , 57 , 115 }, -25, -55, 12, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,+5 });


	//Recover animation
	recover.loop = false;
	recover.SetReverseOffset({ -21,-18 }, 3);
	recover.PushBack({ 0, 503, 60, 83 }, -29, -18, 3, head_recover_collider, body_recover_collider, { 0, 0 });
	recover.speed = 0.5f;

	//jump + kick animation (arcade sprite sheet)
	jumpkick.SetReverseOffset({ -27,-55 }, 2);
	jumpkick.PushBack({ 562,146,57,89 }, -32, -55, 2, head_jumpkick_collider, body_jumpkick_collider, legs_jumpkick_collider);
	jumpkick.SetReverseOffset({ -50,-48 }, 4);
	jumpkick.PushBack({ 619,149,96,86 }, -40, -48, 4, head_jumpkick_collider, body_jumpkick_collider, legs_jumpkick_collider, { 10,10,45,30 });
	jumpkick.SetReverseOffset({ -27,-55 }, 4);
	jumpkick.PushBack({ 562,146,57,89 }, -32, -55, 4, head_jumpkick_collider, body_jumpkick_collider, legs_jumpkick_collider);
	jumpkick.loop = false;
	jumpkick.damage = 20;
	jumpkick.speed = 0.5f;

	//jump + punch animation (arcade sprite sheet)
	jumppunch.SetReverseOffset({ -24,-55 }, 3);
	jumppunch.PushBack({ 715,141,66,94 }, -38, -55, 3, head_jumppunch_collider, body_jumppunch_collider, legs_jumppunch_collider);
	jumppunch.SetReverseOffset({ -45,-55 }, 4);
	jumppunch.PushBack({ 781,157,86,78 }, -38, -55, 4, head_jumppunch_collider, body_jumppunch_collider, legs_jumppunch_collider, { 5,-20,45,25 });
	jumppunch.SetReverseOffset({ -24,-55 }, 4);
	jumppunch.PushBack({ 715,141,66,94 }, -38, -55, 4, head_jumppunch_collider, body_jumppunch_collider, legs_jumppunch_collider);
	jumppunch.speed = 0.5f;
	jumppunch.damage = 20;
	jumppunch.loop = false;

	// ko'ou ken animation (arcade sprite sheet)
	koouKen.SetReverseOffset({ -24,-42 }, 4);
	koouKen.PushBack({ 178, 878, 65, 107 }, -31, -42, 4, rect1, rect2, rect3);
	koouKen.SetReverseOffset({ -22,-58 }, 6);
	koouKen.PushBack({ 864, 734, 75, 123 }, -44, -58, 6, rect1, rect2, rect3);
	koouKen.SetReverseOffset({ -22,-42 }, 4);
	koouKen.PushBack({ 243, 878, 88 , 107 }, -57, -42, 4, rect1, rect2, rect3);
	koouKen.SetReverseOffset({ -20,-42 }, 10);
	koouKen.PushBack({ 331, 878, 85, 107 }, -50, -42, 10, rect1, rect2, rect3);
	koouKen.SetReverseOffset({ -30,-42 }, 5);
	koouKen.PushBack({ 416, 878, 81 , 107 }, -46, -42, 5, rect1, rect2, rect3);
	koouKen.SetReverseOffset({ -70,-42 }, 30);
	koouKen.PushBack({ 497, 878, 102 , 107 }, -22, -42, 30, rect1, rect2, rect3);
	koouKen.speed = 0.9f;
	koouKen.loop = false;

	//win animation
	win.PushBack({ 820 ,1140,50,112 }, 0, 0, 0);
	win.PushBack({ 875 ,1148,66,104 }, 0, 0, 0);

	//defeat animation
	defeat.PushBack({ 508 ,1023,66,110 }, 0, 0, 0);
	defeat.PushBack({ 582 ,1045,64,88 }, 0, 0, 0);
	defeat.PushBack({ 649 ,1069,60,64 }, 0, 0, 0);


	//DAMAGES
	pose_idle_receive_standing_punch_kick_plus_jump_punch.SetReverseOffset({ -23,-43 }, 3);
	pose_idle_receive_standing_punch_kick_plus_jump_punch.PushBack({ 492 ,1261,68,109 }, -36, -43, 3);
	pose_idle_receive_standing_punch_kick_plus_jump_punch.SetReverseOffset({ -21,-45 }, 3);
	pose_idle_receive_standing_punch_kick_plus_jump_punch.PushBack({ 565,1259,80,111 }, -50, -45, 3);
	pose_idle_receive_standing_punch_kick_plus_jump_punch.SetReverseOffset({ -23,-43 }, 3);
	pose_idle_receive_standing_punch_kick_plus_jump_punch.PushBack({ 492 ,1261,68,109 }, -36, -43, 3, {}, {}, {}, {}, {4,0});
	pose_idle_receive_standing_punch_kick_plus_jump_punch.speed = 0.8f;
	pose_idle_receive_standing_punch_kick_plus_jump_punch.loop = false;

	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 745,1144,64,109 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 586,1144,68,108 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 446,1138,60,114 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 0,1283,112,83 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 230,1288,108,78 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 118,1263,97,103 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 230,1288,108,78 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 358,1325,118,42 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 815, 43, 62, 73 }, -24, -8, 2);// getting up == crouch animation
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 0, 503, 60, 83 }, -29, -18, 2);

	pose_idle_receive_crouch_kick.PushBack({ 745,1144,64,109 }, 0, 0, 0);
	pose_idle_receive_crouch_kick.PushBack({ 586,1144,68,108 }, 0, 0, 0);

	/*pose_idle_receive_crouch_punch.PushBack({ 119,1146,55,106 }, 0, 0, 0);
	pose_idle_receive_crouch_punch.PushBack({ 247,1149,46,158 }, 0, 0, 0);*/

	//-----WHILE CROUCH-----//
	//RECIEVE KICK
	pose_crouch_receive_standing_crouch_kick.PushBack({ 299,1178,73,73 },0, 0,2);
	pose_crouch_receive_standing_crouch_kick.speed = 0.5f;
	pose_crouch_receive_standing_crouch_kick.loop = false;

	//RECIEVE PUNCH
	pose_crouch_receive_crouch_punch.SetReverseOffset({ -23, -10 }, 3);
	pose_crouch_receive_crouch_punch.PushBack({ 376,1177,65,75 }, -32, -10, 3);
	pose_crouch_receive_crouch_punch.SetReverseOffset({ -20, -8 }, 3);
	pose_crouch_receive_crouch_punch.PushBack({ 299,1178,73,73 }, -43, -8, 3);
	pose_crouch_receive_crouch_punch.speed = 0.5f;
	pose_crouch_receive_crouch_punch.loop = false;

	//BLOCKING ANIMATIONS
	//Standing block
	standing_block.SetReverseOffset({ -20,-37 }, 3);
	standing_block.PushBack({671,1267,58,103},-32,-37,3,rect1,rect2,rect3);
	standing_block.SetReverseOffset({ -20,-38 }, 5);
	standing_block.PushBack({734,1266,58,104},-32,-38,5, rect1, rect2, rect3);
	standing_block.speed = 0.3f;
	standing_block.loop = false;

	//Crouch block
	crouch_block.SetReverseOffset({ -20,-5 }, 3);
	crouch_block.PushBack({3,1181,54,71},-24,-5,3);
	crouch_block.SetReverseOffset({ -19,-6 }, 4);
	crouch_block.PushBack({59,1180,56,72},-27,-6,4);
	crouch_block.speed = 0.3;
	crouch_block.loop = false;
	
	exitBlock.SetReverseOffset({ -20,-37 }, 1);
	exitBlock.PushBack({ 671,1267,58,103 }, -32, -37, 2, {}, {}, {}, {}, { 1,0 });	
	exitBlock.SetReverseOffset({ -20,-37 }, 1);
	exitBlock.PushBack({ 671,1267,58,103 }, -32, -37, 2, {}, {}, {}, {}, { -1,0 });	
	exitBlock.SetReverseOffset({ -20,-37 }, 1);
	exitBlock.PushBack({ 671,1267,58,103 }, -32, -37, 2, {}, {}, {}, {}, { 1,0 });	
	exitBlock.SetReverseOffset({ -20,-37 }, 1);
	exitBlock.PushBack({ 671,1267,58,103 }, -32, -37, 2, {}, {}, {}, {}, { -1,0 });	
	exitBlock.SetReverseOffset({ -20,-37 }, 6);
	exitBlock.PushBack({ 671,1267,58,103 }, -32, -37, 6, {}, {}, {}, {}, { -1,0 });
	exitBlock.SetReverseOffset({ -20,-38 }, 5);
	exitBlock.PushBack({ 734,1266,58,104 }, -32, -38, 5);
	exitBlock.speed = 0.5f;
	exitBlock.loop = false;

	for (int i = 0; i < 30; i++)
	{
		Input_Queue[i].Input = IN_EMPTY;
	}

	FirstInQueue = &Input_Queue[0].Input;
	LastInQueue = &Input_Queue[0].Input;

}

Ryo::~Ryo()
{

	//if (graphics != nullptr)
	//{
	//	App->textures->Unload(graphics);
	//	graphics = nullptr;
	//}
	//if (punchfx != nullptr)
	//{
	//	App->audio->Unload_effects(punchfx);
	//	punchfx = nullptr;
	//}
	//if (kickfx != nullptr)
	//{
	//	App->audio->Unload_effects(kickfx);
	//	kickfx = nullptr;
	//}
	//if (kooukenfx != nullptr)
	//{
	//	App->audio->Unload_effects(kooukenfx);
	//	kooukenfx = nullptr;
	//}
	//if (jumpfx != nullptr)
	//{
	//	App->audio->Unload_effects(jumpfx);
	//	jumpfx = nullptr;
	//}
	//if (dmg != nullptr)
	//{
	//	App->audio->Unload_effects(dmg);
	//	dmg = nullptr;
	//}
}

 bool Ryo::Start()
{
	 
	 if (player == 1) {
		 if(graphics == nullptr)
		 graphics = App->textures->Load("Assets/ryo_sprite_sheet.png");
	 }
	 else if (player == 2) {
		 if(graphics == nullptr)
		 graphics = App->textures->Load("Assets/ryo_sprite_sheet_2.png");
	 }
	 if(punchfx == nullptr)
		punchfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_punch.wav");
	 if (kickfx == nullptr)
		kickfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_kick.wav");
	 if (kooukenfx == nullptr)
		kooukenfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_kooken.wav");
	 if (jumpfx == nullptr)
		jumpfx = App->audio->Load_effects("Assets/Audio/FX/Jump.wav");
	 if (dmg == nullptr)
		dmg = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_dmg.wav");

	 //Add Combos
	 AddCombo(6, IN_KOOU_KEN, 1, IN_CROUCH_UP, IN_UNKNOWN, IN_RIGHT_DOWN, IN_RIGHT_UP, IN_UNKNOWN, IN_PUNCH);
	 AddCombo(4, IN_KOOU_KEN, 1, IN_CROUCH_UP, IN_RIGHT_DOWN, IN_RIGHT_UP, IN_PUNCH);
	 AddCombo(5, IN_KOOU_KEN, 1, IN_CROUCH_UP, IN_UNKNOWN, IN_RIGHT_DOWN, IN_RIGHT_UP, IN_PUNCH);
	 AddCombo(3, IN_KOOU_KEN, 1, IN_CROUCH_UP, IN_RIGHT_DOWN, IN_PUNCH);


	 AddCombo(5, IN_KOOU_KEN, 2, IN_CROUCH_DOWN, IN_UNKNOWN, IN_LEFT_DOWN, IN_UNKNOWN, IN_PUNCH);
	 AddCombo(4, IN_KOOU_KEN, 2, IN_CROUCH_DOWN, IN_LEFT_DOWN, IN_UNKNOWN, IN_PUNCH);
	 AddCombo(4, IN_KOOU_KEN, 2, IN_UNKNOWN, IN_CROUCH_DOWN, IN_LEFT_DOWN, IN_PUNCH);
	 AddCombo(6, IN_KOOU_KEN, 2, IN_UNKNOWN, IN_CROUCH_DOWN, IN_LEFT_DOWN, IN_RIGHT_DOWN, IN_UNKNOWN, IN_PUNCH);

	return true;
}

 bool Ryo::CleanUp()
 {
	if (graphics != nullptr)
	{
		App->textures->Unload(graphics);
		graphics = nullptr;
	}
	if (punchfx != nullptr)
	{
		App->audio->Unload_effects(punchfx);
		punchfx = nullptr;
	}
	if (kickfx != nullptr)
	{
		App->audio->Unload_effects(kickfx);
		kickfx = nullptr;
	}
	if (kooukenfx != nullptr)
	{
		App->audio->Unload_effects(kooukenfx);
		kooukenfx = nullptr;
	}
	if (jumpfx != nullptr)
	{
		App->audio->Unload_effects(jumpfx);
		jumpfx = nullptr;
	}
	if (dmg != nullptr)
	{
		App->audio->Unload_effects(dmg);
		dmg = nullptr;
	}

	for (int i = 0; i < SpecialLenght; i++)
	{
		if (PlayerSpecialMoves[i] != nullptr)
			delete PlayerSpecialMoves[i];
	}

	 return true;
 }

 void Ryo::AddCombo(int NumberOfInputs, inputs EndState, int ComboSide,inputs Inp...)
 {

	 va_list args;
	 va_start(args, Inp);

	 Special_Move *Combo = new Special_Move();

	 Combo->InputsToCompleteMovement[0] = Inp;
	 for (int i = 1; i < NumberOfInputs; i++)
	 {
		 Combo->InputsToCompleteMovement[i] = va_arg(args, inputs);;
	 }

	 Combo->MovementLenght = NumberOfInputs;
	 Combo->Completed_Input = EndState;
	 Combo->Combo_Side = ComboSide;
	 PlayerSpecialMoves[SpecialLenght] = Combo;
	 SpecialLenght++;

	 va_end(args);

 }

 void Ryo::AddInput(inputs Inp, float time)
 {

	 //Is new Input diferent from last one, check to avoid multiframed input
	 if (Input_Queue[TopPosition - 1].Input != Inp)
	 {
		 //Then add input to queue
		 //TopPosition is now greater
		 //TODO: Check is queue is full to start decreasing inputs
		 if (TopPosition + 1 <= 30)
		 {

			 Input_Queue[TopPosition].Input = Inp;
			 Input_Queue[TopPosition].Time = time;
			 
			 LastInQueue = &Input_Queue[TopPosition].Input;

			 if (TopPosition + 1 == IN_EMPTY)
			 {
				 FirstInQueue = &Input_Queue[0].Input;
			 }
			 else
			 {
				 FirstInQueue = &Input_Queue[TopPosition + 1].Input;
			 }

			 //SDL_Log("%d Num: %d", TopPosition, Input_Queue[TopPosition]);
			 TopPosition++;




		 }
		 else
		 {
			 TopPosition = 0;
			 Input_Queue[TopPosition].Input = Inp;
			 Input_Queue[TopPosition].Time = time;
			 LastInQueue = &Input_Queue[TopPosition].Input;
			 TopPosition++;
		 }

		 LOG("\nA");

	 }

 }

 inputs Ryo::CheckCombos(ModulePlayer_1* P1, ModulePlayer_2* P2)
 {

	 int Check = TopPosition;
	 int Completed = 0;
	 //CheckAllCombos
	 for (int i = 0; i < SpecialLenght; i++)
	 {

		 Check = TopPosition;
		 Completed = 0;
		 //Check All inputs that form the combo
		 for (int j = PlayerSpecialMoves[i]->MovementLenght - 1; j >= 0; j--)
		 {

			 //Next move wont top out the queue
			 if (Check - 1 >= 0)
			 {
				 if (Input_Queue[Check - 1].Input == PlayerSpecialMoves[i]->InputsToCompleteMovement[j])
				 {
					 if (Input_Queue[Check - 1].Time - Input_Queue[Check - 2].Time <= 225)
						 Completed++;
				 }

				 Check--;
			 }
			 if (Check - 1 < 0)
			 {
				 Check = 30;
			 }




		 }

		 if (Completed == PlayerSpecialMoves[i]->MovementLenght)
		 {
			 if ((P1 && P1->Side == PlayerSpecialMoves[i]->Combo_Side) || (P2 && P2->Side == PlayerSpecialMoves[i]->Combo_Side)) 
			 {
				 LOG("\n Combo Completed");
				 return PlayerSpecialMoves[i]->Completed_Input;
			 }
			 else
			 {
				 return IN_EMPTY;
			 }
		 }

	 }

	 return IN_EMPTY;

 }