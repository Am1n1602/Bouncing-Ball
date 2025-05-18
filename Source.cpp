#include <raylib.h>
#include <raymath.h>

int main()
{
    const int screenWidth  = 1600;
    const int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "SimplePhy");
    SetTargetFPS(60);
    InitAudioDevice();
    Sound bounce = LoadSound("resources/plastic-ball-bounce-14790.wav");
    // Define a box of 20px on each side
    Rectangle bounds = { 20, 20,
                         screenWidth  - 40,
                         screenHeight - 40 };

    // Ball state
    Vector2 ballPos = { screenWidth/4.0f, 5*screenHeight/8.0f };
    Vector2 ballVel = { 0, 0 };
    const float ballR    = 20.0f;
    const float gravity  = 900.0f;  
    float maxSpeed =  1400.0f;  

    // Drag and Launch state
    bool  dragging         = false;
    bool  launchEnabled    = false;
    Vector2 dragStartPos   = { 0, 0 };
    Vector2 dragCurrentPos = { 0, 0 };
    Vector2 dragAddedPos = { 0,0 };

    while (!WindowShouldClose())
    {
        // getting delta time 
        float dt = GetFrameTime();

        // Drag logic
        Vector2 mousePos = GetMousePosition();
        float dist = Vector2Distance(mousePos, ballPos);

        // Control max-speed

        if (IsKeyPressed(KEY_W))
        {
            maxSpeed += 200.0f;
            if (maxSpeed >= 4500.0f)
            {
                maxSpeed = 4500.0f;
            }
        }
        if (IsKeyPressed(KEY_S))
        {
            maxSpeed -= 200.0f;
            if (maxSpeed <= 400.0f)
            {
                maxSpeed = 400.0f;
            }
        }
        // Begin dragging if clicked on the ball
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && dist <= ballR)
        {
            dragging       = true;
            launchEnabled  = false;
            dragStartPos   = mousePos;
        }

        // Update drag
        if (dragging)
        {
            dragCurrentPos = mousePos;
           
        }

        // On release, calculate velocity
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && dragging)
        {
            dragging      = false;
            launchEnabled = true;

            // velocity: scale factor to increase/decrease speed
            Vector2 delta = Vector2Subtract(dragCurrentPos, dragStartPos);
            ballVel.x = -delta.x * 5.0f;
            ballVel.y = -delta.y * 5.0f;

            // Max speed 
            if (fabs(ballVel.x) > maxSpeed) ballVel.x = (ballVel.x>0?maxSpeed:-maxSpeed);
            if (fabs(ballVel.y) > maxSpeed) ballVel.y = (ballVel.y>0?maxSpeed:-maxSpeed);
        }

        // Physics sim
        if (launchEnabled)
        {
            // Apply gravity
            ballVel.y += gravity * dt;

            // Friction
            ballVel.x *= 0.99;
            ballVel.y *= 0.99;

            if (fabs(ballVel.x) <= 2.0f) ballVel.x = 0;
            if (fabs(ballVel.y) <= 2.0f) ballVel.y = 0;

            // Move
            ballPos.x += ballVel.x * dt;
            ballPos.y += ballVel.y * dt;

            // Collision with bounds
            // Left/right
            if (ballPos.x - ballR <= bounds.x)
            {
                ballPos.x = bounds.x + ballR;
                ballVel.x *= -1;
                PlaySound(bounce);
               
            }
            else if (ballPos.x + ballR >= bounds.x + bounds.width)
            {
                ballPos.x = bounds.x + bounds.width - ballR;
                ballVel.x *= -1;
                PlaySound(bounce);
            }
            // Top/bottom
            if (ballPos.y - ballR <= bounds.y)
            {
                ballPos.y = bounds.y + ballR;
                ballVel.y *= -1;
                PlaySound(bounce);
               
            }
            else if (ballPos.y + ballR >= bounds.y + bounds.height)
            {
                ballPos.y = bounds.y + bounds.height - ballR;
                ballVel.y *= -1;
                PlaySound(bounce);
                
            }
        }

        // --- Drawing ---
        BeginDrawing();
        ClearBackground(DARKGREEN);

        // Draw bounds
        DrawRectangleRec(bounds, GREEN);
        DrawRectangleLinesEx(bounds, 5, YELLOW);

        // If dragging, draw the drag vector
        if (dragging)
        {

            DrawLineEx(dragCurrentPos, ballPos,5.0, BLUE);
            DrawCircleV(dragStartPos, 5, BLUE);
        }

        // Draw the ball
        DrawCircleV(ballPos, ballR, launchEnabled ? RED : (dragging ? BLUE : RED));

        // Draw the Text
        DrawText(TextFormat("%s", "2D Bouncing Ball"),  screenWidth/2-250, 60, 40, BLACK);
        DrawText(TextFormat("%s", "Press W to increase the Max Speed"), (3 * screenWidth / 4)-150, 100, 25, WHITE);
        DrawText(TextFormat("%s", "Press S to decrease the Max Speed"), (3 * screenWidth / 4) - 150, 130, 25, WHITE);
        DrawText(TextFormat("%d", (int)maxSpeed/10), 180, 100, 30, RED);

        DrawText(TextFormat("%d", (int)ballVel.x/10), 150, 140, 30, RED);
        DrawText(TextFormat("%d", (int)ballVel.y/10), 230, 140, 30, RED);

        EndDrawing();
    }
    UnloadSound(bounce);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}



