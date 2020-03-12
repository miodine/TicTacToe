#include "raylib.h"




int gsw(void) {return GetScreenWidth();}

int gsh(void) {return GetScreenHeight();}

bool subtract = false;

typedef struct Rectangle_plus_plus
{
    Rectangle core_;
    bool selected_;
    const char *fill_;
    Color frame_marker_;
    int character_;
}Rectangle_plus_plus;



enum TURN 
{
    PLAYER = 0, CPU
};
enum FILLINGS 
{
    Xval = 0, Oval, SPACEval
};


Color FB = BLACK;
int alphaFB = 100;


int main(void)
{
    
    const int side = 600;
    const int screenWidth = side;
    const int screenHeight = side;

    InitWindow(screenWidth, screenHeight, "Python kommer att traenga igenom din roevhoal");
    Rectangle_plus_plus boxes[9];
    
    const char *X = "X"; 
    const char *O = "O";
    const char *SPACE = " ";


    for(short i = 0; i<3; i++)
    {
        for(short j = 0; j <3; j++)
        {
            int split = side/3;
            boxes[i*3+j].frame_marker_ = BLACK;
            boxes[i*3+j].core_.x = split*j;
            boxes[i*3+j].core_.y = split*i;
            boxes[i*3+j].core_.width = split;
            boxes[i*3+j].core_.height = split;
            boxes[i*3+j].selected_ = false;
            boxes[i*3+j].character_ = SPACEval;  
        }
    }
  





    SetTargetFPS(30);              

    Rectangle m_cursor = {0, 0, 5, 5};
    int turn = PLAYER;


    bool game_finished = false;
    bool cred = false; 

    bool remaining_indices[9];

    for(short i=0; i<9;i++) remaining_indices[i] = true;

    while (!WindowShouldClose())    
    {
        m_cursor.x = GetMousePosition().x;
        m_cursor.y = GetMousePosition().y;        

        unsigned short control_sum = 0;
            
            for(short i = 0;i<9;i++)
                {
                if(remaining_indices[i]==false)
                control_sum++;
                }

        if(control_sum ==9) game_finished = true;

        if(turn == PLAYER && !game_finished)
        {
        for(short i = 0; i<9;i++)
            {
                if(CheckCollisionRecs(m_cursor, boxes[i].core_))
                {
                    if(boxes[i].selected_) boxes[i].frame_marker_ = RED;
                    else 
                    {
                        boxes[i].frame_marker_ = GREEN;
                        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        {
                            boxes[i].character_ = Oval;
                            boxes[i].selected_ = true;
                            turn = CPU;
                            remaining_indices[i] = false;
                        }
                    }
                }
                else boxes[i].frame_marker_ = BLACK;
            }
        }
        else if (turn == CPU && !game_finished)
        {
                while(true)
                {
                    int i = rand()%9; //STATE OF THE ART ARTIFICIAL INTELLIGENCE RIGHT HERE

                    if(!boxes[i].selected_ && remaining_indices[i]!=0)
                        {
                            boxes[i].selected_ = true;
                            boxes[i].character_ = Xval;
                            remaining_indices[i] = false;
                            turn = PLAYER;
                            break;
                        }
                }
                     
        }

            
        if (control_sum >=3)    
        {
            int t[9];
            
            short lb, step;

            step = 0;

            for(int i = 0; i < 9; i++) 
            {
                t[i] = boxes[i].character_;
                //boxes[i].frame_marker_ = BLACK;
            }



            if(t[0]==t[1] && t[1] == t[2]) 
            {
                if(t[0] == SPACEval)
                {}
                else
                {
                lb = 0; step = 1;
                cred = true;
                }
            } 
            if (t[3]==t[4] && t[4]==t[5])
            {
                if(t[3] == SPACEval)
                {}
                else
                {
                lb = 3; step = 1;
                cred = true;
                }
            }
            if (t[6]==t[7] && t[7]==t[8])
            {
                if(t[6] == SPACEval){}
                else
                {
                lb = 6; step = 1;
                cred = true;
                }
            }

            if (t[0]==t[3] && t[3]==t[6])
            {
                if(t[0] == SPACEval)
                {}
                else
                {
                lb = 0; step = 3;
                cred = true;
                }
            }

            if(t[1]==t[4] && t[4] == t[7])
            {
                if(t[1] == SPACEval)
                {}
                else
                {
                lb = 1; step = 3;
                cred = true;
                }
            }
            
            if(t[2]==t[5] && t[5]==t[8])
            {
                if(t[2] == SPACEval)
                {}
                else
                {
                lb = 2; step = 3;
                cred = true;
                }
            }


            if (t[0] == t[4] && t[4] == t[8])
            {
                if(t[0] == SPACEval)
                {}
                else
                {
                lb = 0; step = 4;
                cred = true;
                }
            }

            if(t[2] == t[4] && t[4] == t[6])
            {
                if(t[2] == SPACEval)
                {}
                else
                {
                lb = 2; step = 2;
                cred = true;
                }
                
            }
            if(8 == 8 == 8)
            {
                printf("x");
            }

            if(cred)
            {
                if(step ==0){}
                else
                {
                turn = 3;
                boxes[lb].frame_marker_ = BLUE;
                boxes[lb+step].frame_marker_ =BLUE;
                boxes[lb+2*step].frame_marker_ =BLUE;
                game_finished = true;    
                }
            
           
            }
        }   
        
        

        if(IsKeyPressed(KEY_R) && game_finished)
            {
            for(int i = 0; i<9; i++)
            {
                boxes[i].selected_ = false;
                boxes[i].character_ = SPACEval;
                boxes[i].frame_marker_ = BLACK;
                remaining_indices[i] = true;
                turn = PLAYER;
                cred = false;
                game_finished = false;
            }

            }  
        
    

        



        BeginDrawing();
            
            DrawRectangleRec(m_cursor, BLACK);
            

            for(int i = 0; i<9; i++)
            {
                DrawRectangleLinesEx(boxes[i].core_,10 ,boxes[i].frame_marker_);

                switch(boxes[i].character_)
                {
                    case Xval: 
                    DrawText(X,(boxes[i].core_.x+side/6)-30, (boxes[i].core_.y+side/6)-50,100, BLACK);
                    break;
                    
                    case Oval: 
                    DrawText(O,(boxes[i].core_.x+side/6)-30, (boxes[i].core_.y+side/6)-50,100, BLACK);
                    break;

                    case SPACEval:
                    DrawText(SPACE,(boxes[i].core_.x+side/6)-30, (boxes[i].core_.y+side/6)-50,100, BLACK); 
                }
                
                
            }

        if(game_finished)
        {
            DrawRectangle(-0.05*side,0.5*side,1.1*side,60,WHITE);
            Rectangle rec = {-0.05*side,0.5*side,1.1*side,60};


            if(FB.r>255) subtract = true;
            if(FB.r<50) subtract = false;

            if(subtract) FB.r--;
            else FB.r++;


            DrawRectangleLinesEx(rec, 10,FB);

            if (alphaFB>=100) alphaFB--; if(alphaFB<=10) alphaFB++;
            Color CURRFB = DARKBLUE;
            CURRFB.a = alphaFB;
            DrawText("Press R to restart",0.19*side,0.52*side,40, CURRFB);
        
        } 

            
            ClearBackground(RAYWHITE);
            DrawFPS(10, 10);

        EndDrawing();

    }

    CloseWindow();   
    return 0;
}

