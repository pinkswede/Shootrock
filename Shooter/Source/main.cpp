#include "raylib.h"
#include"LevelDesign.h"
#include<stack>


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

enum struct Screens { TITLESCREEN = 0, GAMESCREEN, PAUSEMENU };

std::stack<Screens> screens;

void GuiLabel(Rectangle rect, const char* label_text)
{
    Vector2i text_size = { MeasureText(label_text, 40), 40 };
    Vector2i text_top_left = (Vector2i{ static_cast<int>(rect.x),static_cast<int>(rect.y) } + (Vector2i{ static_cast<int>(rect.width),static_cast<int>(rect.height) } - text_size) / 2);

    DrawText(label_text, text_top_left.x, text_top_left.y, 40, GRAY);
}

bool GuiButton(Rectangle rect, const char* button_text)
{
    bool clicked = false;

    Color background_color = Color{ 64, 64, 64, 255 };

    if (CheckCollisionPointRec(GetMousePosition(), rect))
    {
        background_color = Color{ 96, 96, 96, 255 };

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            background_color = Color{ 32, 32, 32, 255 };
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            clicked = true;
        }
    }

    DrawRectangle(rect.x, rect.y, rect.width, rect.height, background_color);
    GuiLabel(rect, button_text);

    return clicked;
}
void MenuInGame()         
{
    const Vector2i button_size = Vector2i(300, 64);
    const int button_margin_y = 10;
    const int button_count = 3;
    Rectangle button_rect;
    button_rect.x = (GetRenderWidth() - button_size.x) / 2;
    button_rect.y = (GetRenderHeight() - (button_size.y * button_count) - (button_count - 1) * button_margin_y) / 2;
    button_rect.width = button_size.x;
    button_rect.height = button_size.y;

    if (GuiButton(button_rect, "CONTINUE"))
    {                                                            
        screens.pop();
    }
    button_rect.y += button_size.y + button_margin_y;
  
    if (GuiButton(button_rect, "EXIT"))
    {
        screens.pop();
        screens.pop();
    }
}



int main(void)
{    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 780;
    const int screenHeight = 600;


    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    InitAudioDevice();
    
    Media::LoadMedia();
   
    screens.push(Screens::TITLESCREEN);
   
    Level gamelevel;

    gamelevel.spawnship();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Screens currentscreen = screens.top();
    
        switch (currentscreen)
        {
        case(Screens::TITLESCREEN):
                {
                     BeginDrawing();

                     ClearBackground(BLACK);

                     DrawText("SHOOT ROCK", 240, 50, 50, RED);

                     DrawText("'X' START", 290, 200, 30, LIGHTGRAY);

                     DrawText("'ESC' QUIT", 290, 300, 30, LIGHTGRAY);

                     EndDrawing();

                     if (IsKeyPressed(KEY_X))
                     {
                         screens.push(Screens::GAMESCREEN);
                     }
        
                }
                break;

        case(Screens::GAMESCREEN):
        {
            BeginDrawing();
            ClearBackground(BLACK);

            gamelevel.render();
            gamelevel.update();

            EndDrawing();

            if (gamelevel.ship_death)
            {
                screens.pop();
                gamelevel.resetlevel();
            }
            if (IsKeyPressed(KEY_ENTER))
            {
                screens.push(Screens::PAUSEMENU);
            }
        }
        break;

        case(Screens::PAUSEMENU):
        {
            BeginDrawing();
            ClearBackground(BLACK);

            MenuInGame();
            EndDrawing();
        }
        break;
        }
       
   
    }

    Media::UnloadMedia();


    CloseAudioDevice();
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}