#include <raylib.h>
#include <raymath.h>

int main()
{
    const int screenWidth  = 1600;
    const int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "SimplePhy");
    SetTargetFPS(60);

    // Define a box of 20px on each side
    Rectangle bounds = { 20, 20,
                         screenWidth  - 40,
                         screenHeight - 40 };

    // Ball state
    Vector2 ballPos = { screenWidth/4.0f, 5*screenHeight/8.0f };
    Vector2 ballVel = { 0, 0 };
    const float ballR    = 20.0f;
    const float gravity  = 900.0f;  
    const float maxSpeed =  1400.0f;  

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

            // Move
            ballPos.x += ballVel.x * dt;
            ballPos.y += ballVel.y * dt;

            // Collision with bounds
            // Left/right
            if (ballPos.x - ballR <= bounds.x)
            {
                ballPos.x = bounds.x + ballR;
                ballVel.x *= -1;
            }
            else if (ballPos.x + ballR >= bounds.x + bounds.width)
            {
                ballPos.x = bounds.x + bounds.width - ballR;
                ballVel.x *= -1;
            }
            // Top/bottom
            if (ballPos.y - ballR <= bounds.y)
            {
                ballPos.y = bounds.y + ballR;
                ballVel.y *= -1;
            }
            else if (ballPos.y + ballR >= bounds.y + bounds.height)
            {
                ballPos.y = bounds.y + bounds.height - ballR;
                ballVel.y *= -1;
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
        DrawText(TextFormat("%s", "2D Ball Bouncing"),  screenWidth/2-250, 60, 40, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}



