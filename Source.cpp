#include <raylib.h>
#include <iostream>

int main()
{

	// Initialise the windows' size

	const int screen_Width = 1200;
	const int screen_Height = 800;
	InitWindow(screen_Width, screen_Height, "SimplePhy");
	SetTargetFPS(60);

	// game loop
		double time1 = 0.0;
		double time2 = 0.0;
		float ballx;
		float bally;
		ballx = screen_Width / 4;
		bally = (3 * screen_Height) / 4;
		double time3 = 0;
		bool mousepress = false;
		bool calc = false;
		float ballr = 20;
		int width1 = screen_Width - 100;
		int height1 = screen_Height - 100;
		Rectangle rect1 = { 50,50,width1,height1 };
		float ballyreal = bally;
		float time3div = 0;
		bool first = true;
	while (WindowShouldClose() == false)
	{

		Vector2 mousePos = GetMousePosition();
		float mouseX = mousePos.x - ballx;
		float mouseY = mousePos.y - bally;
		float distance = sqrtf(mouseX * mouseX + mouseY * mouseY);
		BeginDrawing();
		DrawRectangle(rect1.x, rect1.y, rect1.width, rect1.height,GREEN);
		DrawRectangleLinesEx(rect1, 10, RED);
		DrawCircle(ballx, bally, ballr, RED);

		if (time3 != 0 && (bally!=ballyreal || first)) {
			bally -= time3;
			time3 -= time3div;
			first = false;
		}
		if (bally == ballyreal) {
			bally = ballyreal;
		}
		if (bally >= height1) {
			time3 = time3 * -1;
		}
		
		if (distance <= ballr && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			calc = true;
			
			DrawCircle(ballx, bally, ballr, BLUE);
		}
		else {
			calc = false;
			
		}
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && calc) {
				time1 = GetTime();
				mousepress = true;
				first = true;
			}
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) &&mousepress) {
				time2 = GetTime();
				mousepress = false;
				time3 = time2 - time1;
				time3 = time3 * 5;
				time3div = time3 / 100;
			}

		
		EndDrawing();
	}
	CloseWindow();
	return 0;
}