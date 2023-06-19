#include <nds.h>
#include <maxmod9.h>
#include <stdio.h>
#include <gl2d.h>

#include "soundbank.h"
#include "soundbank_bin.h"

volatile int frame = 0;

void Vblank() {
	frame++;
}

int main() {

	int scene = 0;
	int selectedbtn = 0;

	int PlayerY = 96;
	int Player2Y = 96;
	int BallX = 128;
	int BallY = 96;

	int hits;

	bool GoingRight = true;
	bool GoingUp = true;

	bool pressed = false;

	bool paused = false;

	videoSetMode(MODE_5_3D);
	glScreen2D();

	irqSet(IRQ_VBLANK, Vblank);

	consoleDemoInit();

	mmInitDefaultMem((mm_addr)soundbank_bin);

	// load sound effects
	mmLoadEffect( SFX_UISELECT );
	mmLoadEffect( SFX_WALLHIT );
	mmLoadEffect( SFX_UIPRESS );
	mm_sound_effect ui_select = {
		{ SFX_UISELECT } ,			// id
		(int)(1.0f * (1<<10)),	// rate
		0,		// handle
		255,	// volume
		255,	// panning
	};

	mm_sound_effect wallhit = {
		{ SFX_WALLHIT } ,			// id
		(int)(1.0f * (1<<10)),	// rate
		0,		// handle
		255,	// volume
		255,	// panning
	};

	while(1) {

		int keys_pressed, keys_released;

		scanKeys();

		keys_pressed = keysDown();
		keys_released = keysUp();

		if ( keys_pressed & KEY_A ) {
			//mmEffectEx(&ui_select);
		}
		
		

		if(selectedbtn >= 3)
		{
			selectedbtn = 0;
		}
		if(selectedbtn <= -1)
		{
			selectedbtn = 2;
		}
		// Graphics

		glBegin2D();

		glBoxFilled(0, 0, 256, 1, RGB15(255,255,255));
		glBoxFilled(0, 190, 256, 191, RGB15(255,255,255));
		glBoxFilled(0, 0, 1, 191, RGB15(255,255,255));
		glBoxFilled(255, 0, 253, 191, RGB15(255,255,255));
		iprintf("\x1b[2;0H         Im-Pong-Sibble");
		iprintf("\x1b[3;0H          NDS Edition");
		iprintf("\x1b[4;0H     Made by Andras Daradici");
		
		
		if ( keys_released & KEY_A ) {
			pressed = false;
		}
		if(scene == 0)
		{
			iprintf("\x1b[6;0H      Press A to select mode");
			iprintf("\x1b[7;0HDPAD Up & DPAD Down to navigate");
			iprintf("\x1b[18;0H            Controls:");
			iprintf("\x1b[20;0H  Player 1: DPAD Up & DPAD Down");
			iprintf("\x1b[22;0H       Player 2: X & B");
			vramSetBankE(VRAM_E_LCD);
			
			hits = 0;
			
			if(selectedbtn == 0)
			{
				iprintf("\x1b[9;0H          Single Player <==");
				iprintf("\x1b[11;0H            Two Player       ");
				iprintf("\x1b[13;0H              Quit            ");
				if ( keys_pressed & KEY_A && pressed == false) {
					mmEffectEx(&ui_select);
					scene = 1;
					PlayerY = 96;
					BallX = 128;
					BallY = 96;
					pressed = true;
				}
				
			}
			if(selectedbtn == 1)
			{
				iprintf("\x1b[9;0H          Single Player       ");
				iprintf("\x1b[11;0H            Two Player  <==");
				iprintf("\x1b[13;0H              Quit            ");
				if ( keys_pressed & KEY_A  && pressed == false) {
					mmEffectEx(&ui_select);
					scene = 2;
					PlayerY = 96;
					Player2Y = 96;
					BallX = 128;
					BallY = 96;
				}
			}
			if(selectedbtn == 2)
			{
				iprintf("\x1b[9;0H          Single Player       ");
				iprintf("\x1b[11;0H            Two Player       ");
				iprintf("\x1b[13;0H              Quit      <==");
				if ( keys_pressed & KEY_A && pressed == false) {
					scene = 6;
					mmEffectEx(&ui_select);
				}
			}

			if ( keys_pressed & KEY_UP ) {
				selectedbtn--;
				mmEffectEx(&ui_select);
			}
			if ( keys_pressed & KEY_DOWN ) {
				selectedbtn++;
				mmEffectEx(&ui_select);
			}

			/*
			if(selectedbtn == 0)
			{
				
				glBoxFilled(68, 86, 188, 106, RGB15(255,255,255));
				glBoxFilled(70, 88, 186, 104, RGB15(255,255,255));

				glBoxFilled(68, 116, 188, 136, RGB15(255,255,255));
				glBoxFilled(70, 118, 186, 134, RGB15(0,0,0));

				glBoxFilled(68, 146, 188, 166, RGB15(255,255,255));
				glBoxFilled(70, 148, 186, 164, RGB15(0,0,0));
			}
			if(selectedbtn == 1)
			{
				glBoxFilled(68, 86, 188, 106, RGB15(255,255,255));
				glBoxFilled(70, 88, 186, 104, RGB15(0,0,0));

				glBoxFilled(68, 116, 188, 136, RGB15(255,255,255));
				glBoxFilled(70, 118, 186, 134, RGB15(255,255,255));

				glBoxFilled(68, 146, 188, 166, RGB15(255,255,255));
				glBoxFilled(70, 148, 186, 164, RGB15(0,0,0));
			}
			if(selectedbtn == 2)
			{
				glBoxFilled(68, 86, 188, 106, RGB15(255,255,255));
				glBoxFilled(70, 88, 186, 104, RGB15(0,0,0));

				glBoxFilled(68, 116, 188, 136, RGB15(255,255,255));
				glBoxFilled(70, 118, 186, 134, RGB15(0,0,0));

				glBoxFilled(68, 146, 188, 166, RGB15(255,255,255));
				glBoxFilled(70, 148, 186, 164, RGB15(255,255,255));
			}
			*/
			iprintf("\x1b[10;0H                                     ");
		}
		if(scene == 1)
		{
			iprintf("\x1b[9;0H                                     ");
			iprintf("\x1b[11;0H                                     ");
			iprintf("\x1b[13;0H                                     ");
			iprintf("\x1b[6;0H                                     ");
			iprintf("\x1b[7;0H                                     ");
			iprintf("\x1b[18;0H                                     ");
			iprintf("\x1b[20;0H                                     ");
			iprintf("\x1b[22;0H                                      ");
			if(PlayerY <= 25)
			{
				PlayerY = 25;
			}
			if(PlayerY >= 167)
			{
				PlayerY = 167;
			}
			glBoxFilled(3, PlayerY-20, 6, PlayerY+20, RGB15(255,255,255));
			glBoxFilled(BallX-2, BallY-2, BallX+2, BallY+2, RGB15(255,255,255));
			glBoxFilled(253, BallY-20, 248, BallY+20, RGB15(255,255,255));

			if(paused == false)
			{
				if(GoingRight)
				{
					BallX++;
				}
				else
				{
					BallX--;
				}
				if(GoingUp)
				{
					BallY--;
				}
				else
				{
					BallY++;
				}
				if ( keysHeld() & KEY_UP )
				{
					PlayerY-=2;
				}
				if ( keysHeld() & KEY_DOWN )
				{
					PlayerY+=2;
				}
			}

			if ( keys_pressed & KEY_START  && pressed == false)
			{
				paused = !paused;
			}

			if(BallY <= 2)
			{
				GoingUp = false;
				mmEffectEx(&wallhit);
			}
			if(BallY >= 190)
			{
				GoingUp = true;
				mmEffectEx(&wallhit);
			}
			if(BallX >= 248)
			{
				GoingRight = false;
				mmEffectEx(&wallhit);
				hits++;
			}
			if(BallX <= 8)
			{
				if(BallY <= PlayerY+22 && BallY >= PlayerY-22)
				{
					GoingRight = true;
					mmEffectEx(&wallhit);
					hits++;
				}
				else
				{
					scene = 3;
					mmEffectEx(&wallhit);
				}
			}
			if(paused == false)
			{
				iprintf("\x1b[13;0H            Score = %d",hits);
			}
			else
			{
				iprintf("\x1b[13;0H             Paused                  ");
			}
			

			

			glBoxFilled(127, 0, 129, 20, RGB15(255,255,255));
			glBoxFilled(127, 40, 129, 60, RGB15(255,255,255));
			glBoxFilled(127, 80, 129, 100, RGB15(255,255,255));
			glBoxFilled(127, 120, 129, 140, RGB15(255,255,255));
			glBoxFilled(127, 160, 129, 180, RGB15(255,255,255));
			glBoxFilled(127, 200, 129, 220, RGB15(255,255,255));
			glBoxFilled(127, 240, 129, 260, RGB15(255,255,255));
		}
		if(scene == 2)
		{
			iprintf("\x1b[9;0H                                     ");
			iprintf("\x1b[11;0H                                     ");
			iprintf("\x1b[13;0H                                     ");
			iprintf("\x1b[6;0H                                     ");
			iprintf("\x1b[7;0H                                     ");
			iprintf("\x1b[18;0H                                     ");
			iprintf("\x1b[20;0H                                     ");
			iprintf("\x1b[22;0H                                      ");
			if(PlayerY <= 25)
			{
				PlayerY = 25;
			}
			if(PlayerY >= 167)
			{
				PlayerY = 167;
			}
			if(Player2Y <= 25)
			{
				Player2Y = 25;
			}
			if(Player2Y >= 167)
			{
				Player2Y = 167;
			}
			glBoxFilled(3, PlayerY-20, 6, PlayerY+20, RGB15(255,255,255));
			glBoxFilled(BallX-2, BallY-2, BallX+2, BallY+2, RGB15(255,255,255));
			glBoxFilled(253, Player2Y-20, 248, Player2Y+20, RGB15(255,255,255));

			if(paused == false)
			{
				if(GoingRight)
				{
					BallX++;
				}
				else
				{
					BallX--;
				}
				if(GoingUp)
				{
					BallY--;
				}
				else
				{
					BallY++;
				}
				if ( keysHeld() & KEY_UP )
				{
					PlayerY-=2;
				}
				if ( keysHeld() & KEY_DOWN )
				{
					PlayerY+=2;
				}
				if ( keysHeld() & KEY_X )
				{
					Player2Y-=2;
				}
				if ( keysHeld() & KEY_B )
				{
					Player2Y+=2;
				}
			}

			if ( keys_pressed & KEY_START  && pressed == false)
			{
				paused = !paused;
			}

			if(BallY <= 2)
			{
				GoingUp = false;
				mmEffectEx(&wallhit);
			}
			if(BallY >= 190)
			{
				GoingUp = true;
				mmEffectEx(&wallhit);
			}
			if(BallX >= 248)
			{
				if(BallY <= Player2Y+22 && BallY >= Player2Y-22)
				{
					GoingRight = false;
					mmEffectEx(&wallhit);
					hits++;
				}
				else
				{
					scene = 4;
					mmEffectEx(&wallhit);
				}
			}
			if(BallX <= 8)
			{
				if(BallY <= PlayerY+22 && BallY >= PlayerY-22)
				{
					GoingRight = true;
					mmEffectEx(&wallhit);
					hits++;
				}
				else
				{
					scene = 5;
					mmEffectEx(&wallhit);
				}
			}
			if(paused == false)
			{
				iprintf("\x1b[13;0H            Score = %d",hits);
			}
			else
			{
				iprintf("\x1b[13;0H             Paused                  ");
			}

			glBoxFilled(127, 0, 129, 20, RGB15(255,255,255));
			glBoxFilled(127, 40, 129, 60, RGB15(255,255,255));
			glBoxFilled(127, 80, 129, 100, RGB15(255,255,255));
			glBoxFilled(127, 120, 129, 140, RGB15(255,255,255));
			glBoxFilled(127, 160, 129, 180, RGB15(255,255,255));
			glBoxFilled(127, 200, 129, 220, RGB15(255,255,255));
			glBoxFilled(127, 240, 129, 260, RGB15(255,255,255));
		}
		if(scene == 3)
		{
			iprintf("\x1b[9;0H            You lost!       ");
			iprintf("\x1b[10;0H Press A to go back to the menu       ");
			if ( keys_pressed & KEY_A && pressed == false) {
				mmEffectEx(&ui_select);
				scene = 0;
			}
		}
		if(scene == 4)
		{
			iprintf("\x1b[9;0H          Player 1 wins!       ");
			iprintf("\x1b[10;0H Press A to go back to the menu       ");
			if ( keys_pressed & KEY_A ) {
				mmEffectEx(&ui_select);
				scene = 0;
			}
		}
		if(scene == 5)
		{
			iprintf("\x1b[9;0H          Player 2 wins!       ");
			iprintf("\x1b[10;0H Press A to go back to the menu       ");
			if ( keys_pressed & KEY_A ) {
				mmEffectEx(&ui_select);
				scene = 0;
			}
		}
		if(scene == 6)
		{
			iprintf("\x1b[9;0H                                     ");
			iprintf("\x1b[11;0H                                     ");
			iprintf("\x1b[13;0H                                     ");
			iprintf("\x1b[6;0H                                     ");
			iprintf("\x1b[7;0H                                     ");
			iprintf("\x1b[18;0H                                     ");
			iprintf("\x1b[20;0H                                     ");
			iprintf("\x1b[22;0H                                      ");
			iprintf("\x1b[10;0H     Thank you for playing!");
			iprintf("\x1b[18;0H                                     ");
			iprintf("\x1b[20;0H                                     ");
			iprintf("\x1b[22;0H                                     ");
		}

		glEnd2D();
		glFlush(0);
		swiWaitForVBlank();

	}
	return 0;
}
