#include <iostream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include<SDL2/SDL_mixer.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <time.h>

#define p_size 300
#define p_ground 520
#define Jump -32
using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Rect temp, player1,src_player1, player2,src_player2, chose_p1, chose_p2, chose_court, power_p1, power_p2, goal, src_ball, ball, new_save, load, setting, quit, counter, title, saving_board,
            gate1, gate2, menu_back, pause, court,End, next_p1, next_p2, next_power_p1, next_power_p2, next_court, ok, process_p1, process_p2, main_menu, insert_player, lan_title, lan_en, lan_fars, condition_title, time_condition, goal_condition;
SDL_Rect obstacle1, obstacle2;/////////////////////////////////////////////

SDL_Texture* logo_img;
SDL_Texture* menu_back_img;
SDL_Texture* saving_board_img;
SDL_Texture* pause_img;
SDL_Texture* title_img;
SDL_Texture* new_save_tick_img;
SDL_Texture* new_save_untick_img;
SDL_Texture* load_tick_img;
SDL_Texture* load_untick_img;
SDL_Texture* setting_tick_img;
SDL_Texture* setting_untick_img;
SDL_Texture* quit_tick_img;
SDL_Texture* quit_untick_img;
SDL_Texture* main_menu_tick_img;
SDL_Texture* main_menu_untick_img;
SDL_Texture* lan_en_untick_img;
SDL_Texture* lan_en_tick_img;
SDL_Texture* lan_fars_untick_img;
SDL_Texture* lan_fars_tick_img;
SDL_Texture* lan_title_img;
SDL_Texture* condition_title_img;
SDL_Texture* time_condition_untick_img;
SDL_Texture* time_condition_tick_img;
SDL_Texture* goal_condition_untick_img;
SDL_Texture* goal_condition_tick_img;
SDL_Texture* insert_p1_img;
SDL_Texture* insert_p2_img;
SDL_Texture* end_img;
SDL_Texture* counter_img;
SDL_Texture* next_tick_img;
SDL_Texture* next_untick_img;
SDL_Texture* ok_img;
SDL_Texture* next_power_tick_img;
SDL_Texture* next_power_untick_img;
SDL_Texture* next_court_tick_img;
SDL_Texture* next_court_untick_img;
SDL_Texture* chose_p1_img;
SDL_Texture* chose_p2_img;
SDL_Texture* chose_court_img;
SDL_Texture* power_p1_img;
SDL_Texture* power_p2_img;
SDL_Texture* court_img;
SDL_Texture* court_p1_img;
SDL_Texture* court_p2_img;
SDL_Texture* gate1_img;
SDL_Texture* gate2_img;
SDL_Texture* goal_img;
SDL_Texture* process_img;
SDL_Texture* ball_img;
SDL_Texture* p1_idle_img;
SDL_Texture* p1_jump_img;
SDL_Texture* p1_run_img;
SDL_Texture* p1_kick_img;
SDL_Texture* p1_hit_img;
SDL_Texture* p1_ko_img;
SDL_Texture* p1_tel_img;
SDL_Texture* p1_fire_kick_img;
SDL_Texture* p2_idle_img;
SDL_Texture* p2_jump_img;
SDL_Texture* p2_run_img;
SDL_Texture* p2_kick_img;
SDL_Texture* p2_hit_img;
SDL_Texture* p2_ko_img;
SDL_Texture* p2_tel_img;
SDL_Texture* p2_fire_kick_img;
SDL_Texture* wall_1_img;
SDL_Texture* wall_2_img;
SDL_Texture* welcome;

int frameCount, fps, now1, now2, pause_frame,end_frame, temp_x_p1, temp_x_p2, limit, winner=0;
Uint32 frameStart, frameTime, frameDelay, temp1_time, temp2_time;/////////////////??????????????
int score_p1, score_p2, menu_po, end_po, lan_po, lan_now, pause_po, new_po, chose_p1_po, chose_p2_po, chose_court_po, power_p1_po, power_p2_po, B[5] = {0,255,255,255,255}, saving_po, board_po, delay;
float vx_ball, vy_ball, vx_p2, vx_p1, v1_jump, v2_jump, gravity=0.7, friction = 0.15;
float v_power_p1, v_power_p2, add1, add2;
string saving [5][9], txt, time_limit, skin_arr[3]={"Orc", "Ogre", "Gablin"}, name_p1, name_p2, show_power [5] = {"TrC", "HFB", "KFB", "InB", "MKO"}
        ,input_cheat1, input_cheat2; ///[7]
const string cheat = "SSDADSD";

bool gameIsRunning;
bool onCourt;
bool onMenu;
bool onSavingBoard;
bool onNewGame;
bool onSetting;
bool ani_menu;
bool onPause;
bool chose_char;
bool chose_name;
bool counting;
bool onGoal;
bool goal_p1;
bool goal_p2;
bool jump_p1;
bool jump_p2;
bool idle_p1;
bool idle_p2;
bool run_p1;
bool run_p2;
bool shoot_p1;
bool shoot_p2;
bool onPower_p1;
bool onPower_p2;
bool fire_kick_p1;
bool fire_kick_p2;
bool fire_head_p1;
bool fire_head_p2;
bool hit_p1;
bool hit_p2;
bool ko_p1;
bool ko_p2;
bool thief_p1;
bool thief_p2;
bool change_chose_p1;
bool change_chose_p2;
bool change_power_p1;
bool change_power_p2;
bool change_court;
bool onCheat;
bool onLogo;
bool isEnd;
bool onCheat1;
bool onCheat2;
bool ani_infiltration;

bool onKey1, onKey2;
Uint32 tempTime1, tempTime2, temp_time1, temp_time2;

struct Timer
{
    void start();
    void pause();
    Uint32 getTime();
    bool isStarted(){
        return started;
    }
    bool isPaused(){
        return paused;
    }
    Uint32 delay;
    Uint32 startTime;
    Uint32 pauseTime;
    bool paused;
    bool started;;
};

struct Player
{
    Player(int p)
    {
        player = p;
    }
    void setRellativeDirection();
    void setParameters(int p, int xh, int yh, int xb, int yb, int wb, int hb, int xf, int yf, int wf, int hf);
    SDL_Rect rect, feet, body, head;
    int player, x_head, y_head;
    int head_r = 60;
    int mass;
};

struct Ball
{
    void move();
    void setRellativeDirection()
    {
        x = ball.x+25;
        y = ball.y+25;
    }
    int x, y;
    int r = 25;
};

void init();
void update();
void input();
void render();
Uint32 callback(Uint32 interval, void* param);
void text(int x, int y, int font, const char* message, int f_size, SDL_Color color);
void set_data();
void update_data(string char1, string char2);
void reset_data(bool menu, bool board);
void set_skin(int skin1, int skin2, int court_po);
void check_ball();
void shoot1();
void shoot2();
void set_B(int i);
void setWinner();
void write_data();
void check_cheat(char input, bool player);
void set_lan(int lan);
void set_time_limit();
int pause_Out(int start, int finish, double current_frame, int nFrames);
void goal_reset()
{
    fire_kick_p1 = false;
    fire_kick_p2 = false;
    fire_head_p1 = false;
    fire_head_p2 = false;
}
struct Player p1(0);
struct Player p2(1);
struct Ball r_ball;
struct Timer timer;

int main( int argc, char * argv[] )
{
    init();
    while(gameIsRunning){
        frameCount++;
        frameStart = SDL_GetTicks();
        input();
        update();
        render();
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
        if(frameCount == 36)
            frameCount = 0;
    }
    SDL_StopTextInput();
    write_data();
    return 0;
}

void init()
{
    fps = 30;
    frameCount = -1;
    frameDelay = 1000/fps;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();
    SDL_CreateWindowAndRenderer(1280, 800, SDL_WINDOW_SHOWN, &window, &renderer);
    SDL_SetWindowTitle(window, "Head Ball : dungeons and dragons");
    gameIsRunning = true;

    onLogo = true;

    ball_img = IMG_LoadTexture(renderer, "images/ball.png");
    gate1_img = IMG_LoadTexture(renderer, "images/gate_p1.png");
    gate2_img = IMG_LoadTexture(renderer, "images/gate_p2.png");
    goal_img = IMG_LoadTexture(renderer, "images/goal.png");
    power_p1_img =IMG_LoadTexture(renderer, "images/chose/Head_fire_ball.png");
    power_p2_img =IMG_LoadTexture(renderer, "images/chose/mortal_kombat.png");
    title_img = IMG_LoadTexture(renderer, "images/title.png");

    lan_title_img = IMG_LoadTexture(renderer, "images/lan_title.png");
    lan_en_tick_img = IMG_LoadTexture(renderer, "images/buttons/lan_en_tick.png");
    lan_en_untick_img = IMG_LoadTexture(renderer, "images/buttons/lan_en_untick.png");
    lan_fars_tick_img = IMG_LoadTexture(renderer, "images/buttons/lan_fars_tick.png");
    lan_fars_untick_img = IMG_LoadTexture(renderer, "images/buttons/lan_fars_untick.png");

    chose_p1_img = IMG_LoadTexture(renderer, "images/chose/chose_p1_1.png");
    chose_p2_img = IMG_LoadTexture(renderer, "images/chose/chose_p2_0.png");
    chose_court_img = IMG_LoadTexture(renderer, "images/chose/chose_court_0.jpg");

    saving_board_img = IMG_LoadTexture(renderer, "images/saving_board.png");
    end_img = IMG_LoadTexture(renderer, "images/end.jpg");
    pause_img = IMG_LoadTexture(renderer, "images/pause2.png");
    process_img = IMG_LoadTexture(renderer, "images/power_bar.png");

    wall_1_img = IMG_LoadTexture(renderer,"images/features/wall1.png");
    wall_2_img = IMG_LoadTexture(renderer,"images/features/wall2.png");

    reset_data(true, false);
    court_img = IMG_LoadTexture(renderer, "images/courtt.jpg");
    court_p1_img = IMG_LoadTexture(renderer, "images/court_p1_goal.jpg");
    court_p2_img = IMG_LoadTexture(renderer, "images/court_p2_goal.jpg");
    welcome= IMG_LoadTexture(renderer, "images/features/court_1.png");
    menu_back_img = IMG_LoadTexture(renderer, "images/menu.jpg");
    logo_img = IMG_LoadTexture(renderer, "images/logo.jpg");

    lan_title = {450, 120, 379, 94};
    lan_en = {415, 240, 200, 94};
    lan_fars = {665, 240, 200, 94};
    condition_title = {430, 380, 420, 90};
    time_condition = {190, 496, 440, 90};
    goal_condition = {650, 496, 440, 90};
    next_p1 = {100, 430, 295, 92};
    next_p2 = {885, 430, 295, 92};
    next_power_p1 = {100, 700, 295, 92};
    next_power_p2 = {885, 700, 295, 92};
    chose_p1 = {0, 0, 500, 500};
    chose_p2 = {780, 0, 500, 500};
    power_p1 = {40, 540, 400, 150};
    power_p2 = {820, 540, 400, 150};
    insert_player = {299, 308, 682, 104};
    menu_back = {0, 0, 1280, 800};
    saving_board = {250, 230, 821, 397};
    End = {0, 225, 1280, 350};
     gate1 = {5, 330, 120, 450};
    gate2 = {1155, 330, 120, 450};
    goal = {400, 350, 484, 111};
    title = {700, 100, 500, 500};
    new_save = {450, 470, 240, 94};
    setting = {450, 580, 240, 94};
    ok = {495, 650, 300, 100};
    next_court= {465, 470, 350,100};
    chose_court={445,200 ,390,250};
    obstacle1= {70,310,70,500};
    obstacle2 = {1150,310, 70, 500};
    set_data();
    set_lan(lan_now);
}

void update()
{
    if(onLogo){
        if(pause_frame <= 60){
            pause_frame++;
        } else{
            pause_frame = 0;
            onLogo = false;
        }
    }
    else if(ani_menu){
          if(pause_frame <= 60){
            int s = pause_Out(0, 1280, pause_frame, 60);
            menu_back.x = s;
            pause_frame++;
        } else if(pause_frame <= 120){
            player1.x = -300+3*pause_frame;
            player2.x = 1250-3*pause_frame;
            src_player1.x = (pause_frame%12)*300;
            src_player2.x = 3300-(pause_frame%12)*300;
            pause_frame++;
        }else{
            pause_frame = 0;
            ani_menu = false;
        }
    }
    else{
        if(onMenu){

        }
        else if(onSavingBoard){

        }else if(onNewGame){
            if(chose_char){
                if(change_power_p1)
                 switch(power_p1_po){
                        case 0: power_p1_img = IMG_LoadTexture(renderer, "./images/chose/power0.png");  change_power_p1= false; break;
                        case 1: power_p1_img = IMG_LoadTexture(renderer, "./images/chose/power1.png");  change_power_p1= false; break;
                        case 2: power_p1_img = IMG_LoadTexture(renderer, "./images/chose/power2.png");  change_power_p1= false; break;
                        case 3: power_p1_img = IMG_LoadTexture(renderer, "./images/chose/power3.png");  change_power_p1= false; break;
                        case 4: power_p1_img = IMG_LoadTexture(renderer, "./images/chose/power4.png");  change_power_p1= false; break;
                        case 5: power_p1_img = IMG_LoadTexture(renderer, "./images/chose/power5.png");  change_power_p1= false; break;

                 }
                if(change_power_p2)
                 switch(power_p2_po){
                        case 0: power_p2_img = IMG_LoadTexture(renderer, "./images/chose/power0.png");  change_power_p2= false; break;
                        case 1: power_p2_img = IMG_LoadTexture(renderer, "./images/chose/power1.png");  change_power_p2= false; break;
                        case 2: power_p2_img = IMG_LoadTexture(renderer, "./images/chose/power2.png");  change_power_p2= false; break;
                        case 3: power_p2_img = IMG_LoadTexture(renderer, "./images/chose/power3.png");  change_power_p2= false; break;
                        case 4: power_p2_img = IMG_LoadTexture(renderer, "./images/chose/power4.png");  change_power_p2= false; break;
                        case 5: power_p2_img = IMG_LoadTexture(renderer, "./images/chose/power5.png");  change_power_p2= false; break;

                    }
                if(change_court)
                 switch(chose_court_po){
                        case 0: chose_court_img = IMG_LoadTexture(renderer, "./images/chose/chose_court_0.jpg");  change_power_p2= false; break;
                        case 1: chose_court_img = IMG_LoadTexture(renderer, "./images/chose/lava.jpg");  change_power_p2= false; break;
                        case 2: chose_court_img = IMG_LoadTexture(renderer, "./images/chose/mars.jpg");  change_power_p2= false; break;
                    }
                if(change_chose_p1)
                     switch(chose_p1_po){
                            case 0: chose_p1_img = IMG_LoadTexture(renderer, "./images/chose/chose_p1_0.png");  change_chose_p1=false; break;
                            case 1: chose_p1_img = IMG_LoadTexture(renderer, "./images/chose/chose_p1_1.png");  change_chose_p1=false; break;
                            case 2: chose_p1_img = IMG_LoadTexture(renderer, "./images/chose/chose_p1_2.png");  change_chose_p1=false; break;
                    }
                if(change_chose_p2)
                     switch(chose_p2_po){
                            case 0: chose_p2_img = IMG_LoadTexture(renderer, "./images/chose/chose_p2_0.png");  change_chose_p2=false; break;
                            case 1: chose_p2_img = IMG_LoadTexture(renderer, "./images/chose/chose_p2_1.png");  change_chose_p2=false; break;
                            case 2: chose_p2_img = IMG_LoadTexture(renderer, "./images/chose/chose_p2_2.png");  change_chose_p2=false; break;
                     }
            }else if(chose_name){

            }

        }else if(onCourt){

            if(onPause){
                if(pause_frame <= 60){
                    int s = pause_Out(640, 0, pause_frame, 60);
                    pause.x = s;
                    pause.y = s * 0.625;
                    pause.w = (640-s)*2;
                    pause.h = (640-s)*1.25;
                    pause_frame++;
                }else{

                }
            }else{
                if(counting && !ani_menu){
                    switch(pause_frame)
                    {
                        case 0: counter_img = IMG_LoadTexture(renderer, "./images/number/num3.png");    break;
                        case 1: counter_img = IMG_LoadTexture(renderer, "./images/number/num2.png");    break;
                        case 2: counter_img = IMG_LoadTexture(renderer, "./images/number/num1.png");    break;
                        default: counting = false;     break;
                    }
                    SDL_Delay(1000);
                    pause_frame++;
                }
                else{
                    if(!isEnd){
                        if(end_po == 0){
                            if(timer.getTime()-delay > limit*1000){
                                //cout << "end"<<endl;
                                isEnd = true;
                                end_frame =0;
                                setWinner();
                            }
                        }else{
                            if(timer.getTime()-delay > 90000){
                                isEnd = true;
                                end_frame =0;
                                setWinner();
                            }else if(score_p1 >=5 || score_p2 >=5 ||(score_p1 == 4 && score_p2 == 4)){
                                isEnd = true;
                                end_frame =0;
                                 setWinner();
                            }
                        }
                    }
                    if(isEnd){
                        onPower_p1=false;
                        onPower_p2=false;
                        fire_kick_p1 = false;
                        fire_kick_p2 = false;
                        fire_head_p1 = false;
                        fire_head_p2 = false;
                        hit_p2 = false;
                        hit_p1 = false;
                        ko_p2 = false;
                        ko_p1 = false;
                        player1.x = 50;
                        player2.x = 890;
                        SDL_SetTextureAlphaMod(ball_img, 255);
                         end_frame++;
                        SDL_Delay(1000);

                        if(end_frame >= 4){
                            isEnd = false;
                            goal_p1 =false;
                            goal_p2 =false;
                            reset_data(false, true);
                        }

                    }
                    if(onGoal){
                        if(thief_p1 && (power_p1_po == 3 || power_p1_po == 0) && !onPower_p1){
                            srand(time(NULL));
                            power_p1_po = rand()%5;
                        }
                        if(thief_p2 && (power_p2_po == 3 || power_p2_po == 0) && !onPower_p2){
                            srand(time(NULL));
                            power_p2_po = rand()%5;
                        }
                        onPower_p1=false;
                        onPower_p2=false;
                        fire_kick_p1 = false;
                        fire_kick_p2 = false;
                        fire_head_p1 = false;
                        fire_head_p2 = false;
                        hit_p2 = false;
                        hit_p1 = false;
                        ko_p2 = false;
                        ko_p1 = false;
                        player1.x = 50;
                        player2.x = 890;
                        SDL_SetTextureAlphaMod(ball_img, 255);
                        if(goal_p1){
                            vx_ball=5;
                            vy_ball=5;
                        }
                        else if(goal_p2){
                            vx_ball=-5;
                            vy_ball=5;
                        }
                        pause_frame++;
                        SDL_Delay(1000);

                        if(pause_frame >= 2){
                            onGoal = false;
                            goal_p1 =false;
                            goal_p2 =false;
                        }
                    }
                    else{
                            if(onKey1 && timer.getTime()-delay > tempTime1+250)
                                onKey1 = false;
                            if(onKey2 && timer.getTime()-delay > tempTime2+250)
                                onKey2 = false;

                        // game logic on court
                            p1.setRellativeDirection();
                            p2.setRellativeDirection();
                            r_ball.setRellativeDirection();
                            if(timer.getTime()-delay>= temp_time1+15000&&onCheat1){
                                onCheat1=false;
                            }
                            if(timer.getTime()-delay>= temp_time2+15000&&onCheat2){
                                onCheat2=false;
                            }

                            if(r_ball.x <= 155 && r_ball.y < 370 && vx_ball <0){
                                if(fire_kick_p1){
                                    fire_kick_p1 = false;
                                    vx_ball = 10;
                                }
                                else if(fire_kick_p2){
                                    fire_kick_p2 = false;
                                    vx_ball = 10;
                                }
                                else if(fire_head_p1){
                                    fire_kick_p2 = false;
                                    vx_ball = 10;
                                    vy_ball = 0;
                                }
                                else if(fire_head_p2){
                                    fire_kick_p2 = false;
                                    vx_ball = 10;
                                    vy_ball = 0;
                                }
                                vx_ball *= -1;
                            }
                            if(r_ball.x <= 100 && r_ball.y >= 370){
                                if(!onCheat1){
                                    ball.x = 615;
                                    ball.y = 400;
                                    vx_ball=0;
                                    vy_ball=0;
                                    score_p2++;
                                    delay+=2000;
                                    onGoal=true;
                                    goal_p2 = true;
                                }
                                else if(vx_ball <0){
                                    vx_ball*=-1;
                                    cout<<"yakhodaa"<<endl;
                                }
                                switch(score_p2){
                                    case 2: v_power_p1 = 0.75;   break;
                                    case 4: v_power_p1 = 1;  break;
                                }
                            }
                            if(r_ball.x >= 1125 && r_ball.y < 370 && vx_ball >0){
                                if(fire_kick_p1){
                                    fire_kick_p1 = false;
                                    vx_ball = -10;
                                }
                                else if(fire_kick_p2){
                                    fire_kick_p2 = false;
                                    vx_ball = -10;
                                }
                                else if(fire_head_p1){
                                    fire_kick_p2 = false;
                                    vx_ball = -10;
                                    vy_ball = 0;
                                }
                                else if(fire_head_p2){
                                    fire_kick_p2 = false;
                                    vx_ball = -10;
                                    vy_ball = 0;
                                }
                                vx_ball *= -1;
                            }
                            if(r_ball.x >= 1180 && r_ball.y >= 370){
                                if(!onCheat2){
                                    ball.x = 615;
                                    ball.y = 400;
                                    vx_ball=0;
                                    vy_ball=0;
                                    score_p1++;
                                    delay+=2000;
                                    onGoal=true;
                                    goal_p1 = true;
                                }
                                else if(vx_ball > 0){
                                        cout<<"ya khoda"<<endl;
                                    vx_ball*=-1;
                                }
                                switch(score_p1){
                                    case 2: v_power_p2 = 0.75;   break;
                                    case 4: v_power_p2 = 1;  break;
                                }
                            }
                            if(ball.y <= 15 && vy_ball <0)
                                vy_ball *= -0.5;
                            if(ball.y >= 720 && vy_ball >0)
                                vy_ball *= -0.7;
                            else if(ball.y < 720){
                                vy_ball += 0.7;
                                if(vx_ball>0)
                                    vx_ball-=friction;
                                if(vx_ball<0)
                                    vx_ball+=friction;
                            }

                            ball.x += vx_ball;
                            ball.y += vy_ball;

                            check_ball();

                            if(vx_ball != 0 || vy_ball != 0){
                                src_ball.x = (frameCount%18)*97;
                            }
                            if(ball.y > 720){
                                ball.y = 720;
                            }
                            if(process_p1.w <= 450){
                                add1 += v_power_p1;
                                process_p1.w = add1;
                            }
                            if(process_p2.w <= 450){
                                add2 += v_power_p2;
                                process_p2.w = add2;
                            }

                        float Dx_target1_p2= abs(gate1.x +gate1.w - p2.head.x- p2.head.w);
                        float Dy_target1_p2= abs(gate1.y +gate1.h - p2.head.y- p2.head.h);
                        float tan_theta2=Dy_target1_p2/Dx_target1_p2;

                            if((fire_kick_p1 || fire_head_p1) && hit_p2){
                                player2.x += vx_p2;
                                cout << temp_x_p2<< " "<< player2.x << "  "<< vx_p2 <<endl;
                            }
                            else if(ko_p2 ){
                                src_player2.x = 3300-(frameCount%12)*p_size;
                                if(timer.getTime()-delay > temp2_time+3000)
                                    ko_p2 = false;
                            }else if(run_p2){
                                    player2.x += vx_p2;
                                    p2.rect.x += vx_p2;
                                    if(SDL_HasIntersection(&p1.rect, &p2.rect) && p2.rect.y >= p1.rect.y -150){
                                        player2.x -= vx_p2;
                                        p2.rect.x -= vx_p2;
                                    }
                                    if(p2.rect.x+p2.rect.w >= 1190 && vx_p2 >0){
                                        player2.x -= vx_p2;
                                        p2.rect.x -= vx_p2;
                                    }
                                    if(p2.rect.x <= 90 && vx_p2 <0){
                                        player2.x -= vx_p2;
                                        p2.rect.x -= vx_p2;
                                    }
                            }
                            if(onPower_p2){
                                if(power_p2_po==1 && ball.y < 520){
                                    if(now2 == 0){
                                        player2.y = ball.y-125;
                                        player2.x = ball.x-70;
                                    }
                                    now2++;
                                    fire_head_p2 = true;
                                    if(now2 >= 6 )
                                        onPower_p2 = false;

                                    if(SDL_HasIntersection(&p2.rect, &ball) ){

                                        if(SDL_HasIntersection(&p2.head, &ball)){
                                            if(Dx_target1_p2>=Dy_target1_p2){
                                                vx_ball=-32;
                                                vy_ball=32*tan_theta2;
                                            }else{
                                                vx_ball=-32;
                                                vy_ball=8;
                                            }
                                        }
                                    }

                                }
                                else if(power_p2_po==2){
                                    src_player2.x = (now2%12)*p_size;
                                    if(now2 >= 12 )
                                        onPower_p2 = false;
                                    now2++;
                                    fire_kick_p2 = true;
                                    vx_ball=-40;
                                    vy_ball=0;

                                }
                                else if(power_p2_po==3){
                                    if(timer.getTime()-delay > temp2_time + 3000){
                                        SDL_SetTextureAlphaMod(ball_img, 255);
                                        onPower_p2=false;
                                    }
                                }
                                else if(power_p2_po==0){
                                    if(timer.getTime()-delay > temp2_time + 8000){
                                        onPower_p2=false;
                                    }
                                }
                                else if(power_p2_po==4){
                                    src_player2.x = (now2%12)*p_size;
                                    if(now2 >= 12 )
                                        onPower_p2 = false;
                                    now2++;
                                    ko_p1 = true;
                                }
                                if(thief_p2 && !onPower_p2){
                                    srand(time(NULL));
                                    power_p2_po = rand()%5;
                                }
                                add2=0;
                                process_p2.w=0;

                            }
                            if(idle_p2 && !hit_p2){
                                vx_p2=0;
                                src_player2.x = 3300-(frameCount%12)*p_size;

                            }
                            if(shoot_p2){
                                shoot2();
                                src_player2.x = 3300-(now2%12)*p_size;
                                now2++;
                                if(now2 >= 12)
                                    shoot_p2 = false;
                            }
                            if(jump_p2){
                                player2.y += v2_jump;
                                v2_jump += 2;
                                if(v2_jump == 0){
                                    jump_p2 = false;
                                }
                            }
                            if(!jump_p2 && player2.y < p_ground){
                               player2.y += v2_jump;
                               p2.rect.y += v2_jump;
                               if(SDL_HasIntersection(&p1.rect, &p2.rect) && p2.rect.y < p1.rect.y-150){
                                    player2.y -= v2_jump;
                                    p2.rect.y -= v2_jump;
                                    v2_jump = -10;
                               }
                               v2_jump += 2;
                            }
                            if(player2.y >= p_ground){
                                v2_jump=0;
                                player2.y = p_ground;
                            }

                        float Dx_target2_p1= abs(gate2.x +gate2.w/2 - p1.head.x- p1.head.w);
                        float Dy_target2_p1= abs(gate2.y +gate2.h/2 - p1.head.y);
                        float tan_theta1=Dy_target2_p1/Dx_target2_p1;

                            if((fire_kick_p2 || fire_head_p2) && hit_p1){
                                player1.x += vx_p1;
                            }
                            else if(ko_p1 ){
                                src_player1.x = 3300-(frameCount%12)*p_size;
                                if(timer.getTime()-delay > temp1_time+3000)
                                    ko_p1 = false;
                            }else if(run_p1){
                                player1.x += vx_p1;
                                p1.rect.x += vx_p1;
                                if(SDL_HasIntersection(&p1.rect, &p2.rect) && p1.rect.y >= p2.rect.y -150){
                                    player1.x -= vx_p1;
                                    p1.rect.x -= vx_p1;
                                }
                                if(p1.rect.x <= 90 && vx_p1 <0){
                                    player1.x -= vx_p1;
                                    p1.rect.x -= vx_p1;
                                }
                                if(p1.rect.x+p1.rect.w >= 1190 && vx_p1>0){
                                    player1.x -= vx_p1;
                                    p1.rect.x -= vx_p1;
                                }
                            }

                            if(onPower_p1){
                                if(power_p1_po==1 && ball.y < 520){
                                    if(now1 == 0){
                                        player1.y = ball.y-125;
                                        player1.x = ball.x-170;
                                    }
                                    now1++;
                                    fire_head_p1 = true;
                                    if(now1 >= 6 )
                                        onPower_p1 = false;

                                    if(SDL_HasIntersection(&p1.rect, &ball) ){

                                        if(SDL_HasIntersection(&p1.head, &ball)){
                                            if(Dx_target2_p1>=Dy_target2_p1){
                                                vx_ball=32;
                                                vy_ball=32*tan_theta1;
                                            }else{
                                                vx_ball=32;
                                                vy_ball=8;
                                            }
                                        }
                                    }

                                }
                                else if(power_p1_po==2){
                                    src_player1.x = (now1%12)*p_size;
                                    if(now1 >= 12 )
                                        onPower_p1 = false;
                                    now1++;
                                    fire_kick_p1 = true;
                                    vx_ball=40;
                                    vy_ball=0;

                                }
                                else if(power_p1_po==3){
                                    if(timer.getTime()-delay > temp1_time + 3000){
                                        SDL_SetTextureAlphaMod(ball_img, 255);
                                        onPower_p1=false;
                                    }
                                }
                                else if(power_p1_po==0){
                                    if(timer.getTime()-delay > temp1_time + 8000){
                                        onPower_p1=false;
                                    }
                                }
                                else if(power_p1_po==4){
                                    src_player1.x = (now1%12)*p_size;
                                    if(now1 >= 12 )
                                        onPower_p1 = false;
                                    now1++;
                                    ko_p2 = true;
                                }
                                if(thief_p1 && !onPower_p1){
                                    srand(time(NULL));
                                    power_p1_po = rand()%5;
                                }
                                add1=0;
                                process_p1.w=0;
                            }
                            if(idle_p1 && !hit_p1){
                                    vx_p1=0;

                                src_player1.x = (frameCount%12)*p_size;
                            }
                            if(shoot_p1){
                                shoot1();
                                src_player1.x = (now1%12)*p_size;
                                now1++;
                                if(now1 >= 12 )
                                    shoot_p1 = false;

                            }
                            if(jump_p1){
                                player1.y += v1_jump;
                                v1_jump += 2;
                                if(v1_jump == 0){
                                    jump_p1 = false;
                                }
                            }
                            if(!jump_p1 && player1.y < p_ground){
                               player1.y += v1_jump;
                               p1.rect.y += v1_jump;
                               if(SDL_HasIntersection(&p1.rect, &p2.rect) && p1.rect.y < p2.rect.y-150){
                                    player1.y -= v1_jump;
                                    p1.rect.y -= v1_jump;
                                    v1_jump = -10;
                               }
                               v1_jump += 2;
                            }
                            if(player1.y >= p_ground){
                                v1_jump=0;
                                player1.y = p_ground;
                            }
                        }
                    }
                }
            }
        }
    }
void input()
{
    SDL_Event e;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            gameIsRunning = false;
            onMenu = false;
            onCourt = false;
        }

        if(e.type == SDL_MOUSEMOTION && onSavingBoard){
             board_po = -1;
            if(e.motion.x > 831 && e.motion.x < 1071 && e.motion.y > 650 && e.motion.y < 744)
                board_po = 0;
            if(e.motion.x > 551 && e.motion.x < 791 && e.motion.y > 650 && e.motion.y < 744)
                board_po = 1;
        }

        if(e.type == SDL_MOUSEBUTTONDOWN && onSavingBoard){
            if(e.button.x > 831 && e.button.x < 1071 && e.button.y > 650 && e.button.y < 744){
                onSavingBoard = false;
                onCourt = true;
                counting = true;
                ani_menu = true;
                onPower_p1=false;
                onPower_p2=false;
                update_data(saving[saving_po][1], saving[saving_po][4]);
                pause_frame = 0;
                quit = {520, 560, 240, 94};
                main_menu = {520, 450, 240, 94};
                timer.start();
                delay = 8000;
            }
             if(e.button.x > 551 && e.button.x < 791 && e.button.y > 650 && e.button.y < 744){
                reset_data(true, false);
                e.type = NULL;
            }

            if(e.button.x > 250 && e.button.x < 1071 && e.button.y > 300 && e.button.y < 330){
                set_B(0);
            }
            if(e.button.x > 250 && e.button.x < 1071 && e.button.y > 360 && e.button.y < 390){
                set_B(1);
            }
            if(e.button.x > 250 && e.button.x < 1071 && e.button.y > 420 && e.button.y < 450){
                set_B(2);
            }
            if(e.button.x > 250 && e.button.x < 1071 && e.button.y > 480 && e.button.y < 510){
                set_B(3);
            }
            if(e.button.x > 250 && e.button.x < 1071 && e.button.y > 540 && e.button.y < 570){
                set_B(4);
            }
        }

        if(e.type == SDL_MOUSEMOTION && onNewGame){
             new_po = -1;
            if(e.button.x > 100 && e.button.x < 395 && e.button.y > 430 && e.button.y < 522)
                new_po = 0;
            if(e.button.x > 885 && e.button.x < 1180 && e.button.y > 430 && e.button.y < 522)
                new_po = 1;
            if(e.button.x > 100 && e.button.x < 395 && e.button.y > 700 && e.button.y < 792)
                new_po = 2;
            if(e.button.x > 885 && e.button.x < 1180 && e.button.y > 700 && e.button.y < 792)
                new_po = 3;
            if(e.button.x > 465 && e.button.x < 815 && e.button.y > 470 && e.button.y < 570)
                new_po = 4;


        }

        if(e.type == SDL_MOUSEBUTTONDOWN && onNewGame){
            if(chose_char){
                if(e.button.x > 100 && e.button.x < 395 && e.button.y > 430 && e.button.y < 522){
                    chose_p1_po++;
                    chose_p1_po %=3;
                    change_chose_p1 = true;
                }
                if(e.button.x > 885 && e.button.x < 1180 && e.button.y > 430 && e.button.y < 522){
                    chose_p2_po++;
                    chose_p2_po %=3;
                    change_chose_p2 = true;
                }
                if(e.button.x > 100 && e.button.x < 395 && e.button.y > 700 && e.button.y < 792){
                    power_p1_po++;
                    power_p1_po %=6;
                    change_power_p1 = true;
                }
                if(e.button.x > 885 && e.button.x < 1180 && e.button.y > 700 && e.button.y < 792){
                    power_p2_po++;
                    power_p2_po %=6;
                    change_power_p2 = true;
                }
                if(e.button.x > 465 && e.button.x < 815 && e.button.y > 470 && e.button.y < 570){
                    chose_court_po++;
                    chose_court_po %=3;
                    change_court = true;
                }
                if(e.button.x > 495 && e.button.x < 790 && e.button.y > 650 && e.button.y < 750){
                    chose_char=false;
                    chose_name=true;
                    SDL_StartTextInput();
                }
            }else if(chose_name){
                if(e.button.x > 495 && e.button.x < 790 && e.button.y > 650 && e.button.y < 750 && txt.length()>1){
                    chose_name=false;
                    name_p1 = txt.substr(1, txt.length()-1);
                    txt = " ";
                }
            }else{
                if(e.button.x > 495 && e.button.x < 790 && e.button.y > 650 && e.button.y < 750 && txt.length()>1){
                    name_p2 = txt.substr(1, txt.length()-1);
                    txt = " ";
                    SDL_StopTextInput();
                    saving_po=4;
                    saving[4][0] = name_p1;
                    saving[4][1] = skin_arr[chose_p1_po];
                    saving[4][2] = "0";
                    saving[4][3] = name_p2;
                    saving[4][4] = skin_arr[chose_p2_po];
                    saving[4][5] = "0";
                    saving[4][6] = to_string(power_p1_po);
                    saving[4][7] = to_string(power_p2_po);
                    saving[4][8] = to_string(chose_court_po);
                    update_data(skin_arr[chose_p1_po], skin_arr[chose_p2_po]);
                    onNewGame = false;
                    onCourt = true;
                    counting = true;
                    ani_menu = true;
                    pause_frame = 0;
                    quit = {520, 560, 240, 94};
                    main_menu = {520, 450, 240, 94};
                    timer.start();
                    delay = 8000;
                }
            }
        }

        if((e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN) && onNewGame){
            system("cls");
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && txt.length() >1)
                txt = txt.substr(0, txt.length()-1);
            else if(e.type == SDL_TEXTINPUT)
                txt += e.text.text;
        }
        if((e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN) && onSetting){
            system("cls");
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && time_limit.length() >1)
                time_limit = time_limit.substr(0, time_limit.length()-1);
            else if(e.type == SDL_TEXTINPUT && time_limit.length()<4)
                time_limit += e.text.text;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN && onSetting){
                cout << "clicked"<<endl;
            if(e.button.x > 415 && e.button.x < 615 && e.button.y > 240 && e.button.y < 334)
                lan_po = 0;
            if(e.button.x > 655 && e.button.x < 855 && e.button.y > 240 && e.button.y < 334)
                lan_po = 1;
            if(e.button.x > 190 && e.button.x < 630 && e.button.y > 496 && e.button.y < 596){
                end_po = 0;
                SDL_StartTextInput();
            }
            if(e.button.x > 650 && e.button.x < 990 && e.button.y > 496 && e.button.y < 596){
                end_po = 1;
                SDL_StopTextInput();
            }

            if(e.button.x > 495 && e.button.x < 790 && e.button.y > 650 && e.button.y < 750){
                if(lan_po != lan_now){
                    lan_now = lan_po;
                    set_lan(lan_po);
                }
               onMenu = true;
               onSetting = false;
               SDL_StopTextInput();
               set_time_limit();
               e.type = NULL;
            }
        }

        if(e.type == SDL_MOUSEMOTION && onMenu){
            menu_po=-1;
            if(e.motion.x > 450 && e.motion.x < 690 && e.motion.y > 360 && e.motion.y < 454)
                menu_po = 0;
            if(e.motion.x > 450 && e.motion.x < 690 && e.motion.y > 470 && e.motion.y < 564)
                menu_po = 1;
            if(e.motion.x > 450 && e.motion.x < 690 && e.motion.y > 690 && e.motion.y < 784)
                menu_po = 2;
            if(e.motion.x > 450 && e.motion.x < 690 && e.motion.y > 580 && e.motion.y < 674)
                menu_po = 3;

        }

        if(e.type == SDL_MOUSEBUTTONDOWN && onMenu){
            if(e.button.x > 450 && e.button.x < 690 && e.button.y > 470 && e.button.y < 564){
                onMenu = false;
                onNewGame = true;
                e.type =NULL;
            }
            if(e.button.x > 450 && e.button.x < 690 && e.button.y > 580 && e.button.y < 674){
                onMenu = false;
                onSetting = true;
                lan_po = lan_now;
                e.type =NULL;
            }
            if(e.button.x > 450 && e.button.x < 690 && e.button.y > 690 && e.button.y < 784){
                gameIsRunning = false;
            }
            if(e.button.x > 450 && e.button.x < 690 && e.button.y > 360 && e.button.y < 454){
                onMenu = false;
                onSavingBoard = true;
                pause_frame = 0;
                menu_po = -1;
                e.type =NULL;
            }
        }

        if(e.type == SDL_MOUSEMOTION && onPause){
            pause_po=-1;
            if(e.motion.x > 520 && e.motion.x < 760 && e.motion.y > 450 && e.motion.y < 544)
                pause_po = 0;
            if(e.motion.x > 520 && e.motion.x < 760 && e.motion.y > 560 && e.motion.y < 654)
                pause_po = 1;

        }

        if(e.type == SDL_MOUSEBUTTONDOWN && onPause){
            if(e.button.x > 520 && e.button.x < 760 && e.button.y > 560 && e.button.y < 654)
                gameIsRunning = false;
            if(e.button.x > 520 && e.button.x < 760 && e.button.y > 450 && e.button.y < 544){
                reset_data(true, false);
                menu_po = 0;
                e.type =NULL;
            }
        }
    }

    if(keystates[SDL_SCANCODE_ESCAPE] && onCourt && !ani_menu && !counting){
        onPause = (onPause) ? false : true;
        if (!onPause)  {
            counting = true;
            delay += 3000;
            timer.paused = false;
            timer.startTime = SDL_GetTicks() - timer.pauseTime;
        }else{
            timer.paused = true;
            timer.pauseTime = SDL_GetTicks() - timer.startTime;
            timer.startTime = 0;
        }
        pause_frame = 0;
        SDL_Delay(200);
    }

    if(!onPause && !counting ){
        if(!hit_p2 && !ko_p2){

        if(keystates[SDL_SCANCODE_RIGHT] && onCourt){
            check_cheat('D', true);
            run_p2 = true;
            idle_p2 = false;
            src_player2.x = 3300-(frameCount%12)*p_size;
            vx_p2 = 10;

        }
        if(keystates[SDL_SCANCODE_LEFT] && onCourt){
            check_cheat('A', true);
            run_p2 = true;
            idle_p2 = false;
            src_player2.x = 3300-(frameCount%12)*p_size;
            vx_p2 = -10;
        }

        if(!keystates[SDL_SCANCODE_LEFT] && !keystates[SDL_SCANCODE_RIGHT] && !keystates[SDL_SCANCODE_UP] && !keystates[SDL_SCANCODE_K] && onCourt){
            idle_p2=true;
            run_p2= false;
        }

        if(keystates[SDL_SCANCODE_UP] && onCourt && player2.y>=p_ground){
            jump_p2 = true;
            idle_p2 = false;
            v2_jump = Jump;
        }
        if(keystates[SDL_SCANCODE_DOWN] && onCourt){
            check_cheat('S', true);
        }

        if(keystates[SDL_SCANCODE_K] && onCourt && !shoot_p2){
            idle_p2 = false;
            run_p2=false;
            shoot_p2 = true;
            now2=0;
        }

        if(keystates[SDL_SCANCODE_L] && onCourt && !onPower_p2 && process_p2.w >= 450){
            SDL_Rect nfeet = {player2.x+70, player2.y+205, 120, 60};
            if(power_p2_po==1 && ball.y < 520){
                idle_p2 = false;
                run_p2=false;
                onPower_p2 = true;
                shoot_p2 = false;
                now2=0;
            }
            else if(power_p2_po==2 && SDL_HasIntersection(&ball, &nfeet)){
                idle_p2 = false;
                run_p2=false;
                onPower_p2 = true;
                shoot_p2 = false;
                now2=0;
            }
            else if(power_p2_po==3){
                idle_p2 = false;
                run_p1=false;
                onPower_p2 = true;
                shoot_p2 = true;
                temp2_time = timer.getTime()-delay;
                now2=0;
            }
            else if(power_p2_po==0 && p2.rect.x > 210 && p2.rect.x < 970 && abs(p1.rect.x - p2.rect.x) >= 240){
                idle_p2 = false;
                run_p2=false;
                onPower_p2 = true;
                if(ball.x <=p2.rect.x+p2.rect.w+80 && ball.x > p2.rect.x && ball.y+60 > p2.rect.y)
                    player2.x -= p2.rect.x+230-ball.x;
                if(ball.x >=p2.rect.x-p2.rect.w-80 && ball.x < p2.rect.x && ball.y+60 > p2.rect.y)
                    player2.x -= p2.rect.x-220-ball.x;
                temp2_time = timer.getTime()-delay;
            }
            else if(power_p2_po==4 && p2.rect.x <= p1.rect.x+p1.rect.w+80){
                idle_p2 = false;
                run_p2=false;
                onPower_p2 = true;
                now2=0;
                temp1_time = timer.getTime()-delay;
            }
        }
    }
    if(!hit_p1 && !ko_p1){

        if(keystates[SDL_SCANCODE_S] && onCourt){
            check_cheat('S', false);
        }
        if(keystates[SDL_SCANCODE_D] && onCourt){

            check_cheat('D', false);
            run_p1 = true;
            idle_p1 = false;
            src_player1.x = (frameCount%12)*p_size;
            vx_p1 = 10;

        }
        if(keystates[SDL_SCANCODE_A] && onCourt){
            check_cheat('A', false);
            run_p1 = true;
            idle_p1 = false;
            src_player1.x = (frameCount%12)*p_size;
            vx_p1 = -10;

        }
        if(!keystates[SDL_SCANCODE_A] && !keystates[SDL_SCANCODE_D] && !keystates[SDL_SCANCODE_W] && !keystates[SDL_SCANCODE_G] && onCourt){
            idle_p1=true;
            run_p1= false;
        }

        if(keystates[SDL_SCANCODE_W] && onCourt && player1.y>=p_ground){
            jump_p1 = true;
            idle_p1 = false;
            v1_jump = Jump;
        }

        if(keystates[SDL_SCANCODE_G] && onCourt && !shoot_p1){
            idle_p1 = false;
            run_p1=false;
            shoot_p1 = true;
            now1=0;
        }
        if(keystates[SDL_SCANCODE_Y] && onCourt && !onPower_p1 && process_p1.w >= 450){
            SDL_Rect Nfeet = {player1.x+115, player1.y+205, 120, 60};
            if(power_p1_po==1 && ball.y < 520){
                idle_p1 = false;
                run_p1=false;
                onPower_p1 = true;
                shoot_p1 = false;
                now1=0;
            }
            else if(power_p1_po==2 && SDL_HasIntersection(&ball, &Nfeet) && abs(p1.rect.x - p2.rect.x) >= 300){
                idle_p1 = false;
                run_p1=false;
                onPower_p1 = true;
                shoot_p1 = false;
                now1=0;
            }
            else if(power_p1_po==3){
                idle_p1 = false;
                run_p1=false;
                onPower_p1 = true;
                shoot_p1 = true;
                temp1_time = timer.getTime()-delay;
                now1=0;
            }
            else if(power_p1_po==0 && p1.rect.x > 210 && p1.rect.x < 970 && abs(p1.rect.x - p2.rect.x) >= 240){
                idle_p1 = false;
                run_p1=false;
                onPower_p1 = true;
                if(ball.x <=p1.rect.x+p1.rect.w+80 && ball.x > p1.rect.x && ball.y+60 > p1.rect.y)
                    player1.x -= p1.rect.x+230-ball.x;
                if(ball.x >=p1.rect.x-p1.rect.w-80 && ball.x < p1.rect.x && ball.y+60 > p1.rect.y)
                    player1.x -= p1.rect.x-220-ball.x;
                temp1_time = timer.getTime()-delay;
            }
            else if(power_p1_po==4 && p2.rect.x <= p1.rect.x+p1.rect.w+80){
                idle_p1 = false;
                run_p1=false;
                onPower_p1 = true;
                now1=0;
                temp2_time = timer.getTime()-delay;
            }
        }
    }

    }
}

void render()
{
    SDL_RenderClear(renderer);
    if(onLogo){
        SDL_RenderCopy(renderer, logo_img, NULL, NULL);
    }
    else if(onMenu){
        SDL_RenderCopy(renderer, menu_back_img, NULL, NULL);
        SDL_RenderCopy(renderer, title_img, NULL, &title);
        switch(menu_po){
                    case 0: SDL_RenderCopy(renderer, load_tick_img, NULL, &load);
                            SDL_RenderCopy(renderer, new_save_untick_img, NULL, &new_save);
                            SDL_RenderCopy(renderer, quit_untick_img, NULL, &quit);
                            SDL_RenderCopy(renderer, setting_untick_img, NULL, &setting);
                            break;
                    case 1: SDL_RenderCopy(renderer, load_untick_img, NULL, &load);
                            SDL_RenderCopy(renderer, new_save_tick_img, NULL, &new_save);
                            SDL_RenderCopy(renderer, quit_untick_img, NULL, &quit);
                            SDL_RenderCopy(renderer, setting_untick_img, NULL, &setting);
                            break;
                    case 2: SDL_RenderCopy(renderer, load_untick_img, NULL, &load);
                            SDL_RenderCopy(renderer, new_save_untick_img, NULL, &new_save);
                            SDL_RenderCopy(renderer, quit_tick_img, NULL, &quit);
                            SDL_RenderCopy(renderer, setting_untick_img, NULL, &setting);
                            break;
                    case 3: SDL_RenderCopy(renderer, load_untick_img, NULL, &load);
                            SDL_RenderCopy(renderer, new_save_untick_img, NULL, &new_save);
                            SDL_RenderCopy(renderer, quit_untick_img, NULL, &quit);
                            SDL_RenderCopy(renderer, setting_tick_img, NULL, &setting);
                            break;
                    default:SDL_RenderCopy(renderer, load_untick_img, NULL, &load);
                            SDL_RenderCopy(renderer, new_save_untick_img, NULL, &new_save);
                            SDL_RenderCopy(renderer, quit_untick_img, NULL, &quit);
                            SDL_RenderCopy(renderer, setting_untick_img, NULL, &setting);
                            break;
        }
    }
    else if(onSavingBoard){
        load.x = 831;
        load.y = 650;
        SDL_RenderCopy(renderer, menu_back_img, NULL, NULL);
        SDL_RenderCopy(renderer, saving_board_img, NULL, &saving_board);
        switch(board_po){
                    case 0: SDL_RenderCopy(renderer, load_tick_img, NULL, &load);
                            SDL_RenderCopy(renderer, main_menu_untick_img, NULL, &main_menu);
                            break;
                    case 1: SDL_RenderCopy(renderer, load_untick_img, NULL, &load);
                            SDL_RenderCopy(renderer, main_menu_tick_img, NULL, &main_menu);
                            break;
                    default:SDL_RenderCopy(renderer, load_untick_img, NULL, &load);
                            SDL_RenderCopy(renderer, main_menu_untick_img, NULL, &main_menu);
                            break;
            }
        for(int k=0; k<5; k++){
            text(260, 300 + 60*k, 0, saving[k][0].c_str(), 30, {255,255,B[k],255});
            text(430, 300+ 60*k, 0, saving[k][1].c_str(), 30, {255,255,B[k],255});
            text(575, 300+ 60*k, 0, saving[k][2].c_str(), 30, {255,255,B[k],255});
            text(680, 300+ 60*k, 0, saving[k][3].c_str(), 30, {255,255,B[k],255});
            text(860, 300+ 60*k, 0, saving[k][4].c_str(), 30, {255,255,B[k],255});
            text(1000, 300+ 60*k, 0, saving[k][5].c_str(), 30, {255,255,B[k],255});
        }
    }else if(onNewGame){
        SDL_RenderCopy(renderer, menu_back_img, NULL, NULL);
        if(chose_char){
                switch(new_po){
                    case 0: SDL_RenderCopy(renderer, next_tick_img, NULL, &next_p1);
                            SDL_RenderCopy(renderer, next_untick_img, NULL, &next_p2);
                            SDL_RenderCopy(renderer, next_power_untick_img, NULL, &next_power_p2);
                            SDL_RenderCopy(renderer, next_power_untick_img, NULL, &next_power_p1);
                            SDL_RenderCopy(renderer, next_court_untick_img, NULL, &next_court);
                            break;
                    case 1: SDL_RenderCopy(renderer, next_untick_img, NULL, &next_p1);
                            SDL_RenderCopy(renderer, next_tick_img, NULL, &next_p2);
                            SDL_RenderCopy(renderer, next_power_untick_img, NULL, &next_power_p2);
                            SDL_RenderCopy(renderer, next_power_untick_img, NULL, &next_power_p1);
                            SDL_RenderCopy(renderer, next_court_untick_img, NULL, &next_court);
                            break;
                    case 2: SDL_RenderCopy(renderer, next_untick_img, NULL, &next_p1);
                            SDL_RenderCopy(renderer, next_untick_img, NULL, &next_p2);
                            SDL_RenderCopy(renderer, next_power_untick_img, NULL, &next_power_p2);
                            SDL_RenderCopy(renderer, next_power_tick_img, NULL, &next_power_p1);
                            SDL_RenderCopy(renderer, next_court_untick_img, NULL, &next_court);
                            break;
                    case 3: SDL_RenderCopy(renderer, next_untick_img, NULL, &next_p1);
                            SDL_RenderCopy(renderer, next_untick_img, NULL, &next_p2);
                            SDL_RenderCopy(renderer, next_power_tick_img, NULL, &next_power_p2);
                            SDL_RenderCopy(renderer, next_power_untick_img, NULL, &next_power_p1);
                            SDL_RenderCopy(renderer, next_court_untick_img, NULL, &next_court);
                            break;
                    case 4: SDL_RenderCopy(renderer, next_untick_img, NULL, &next_p1);
                            SDL_RenderCopy(renderer, next_untick_img, NULL, &next_p2);
                            SDL_RenderCopy(renderer, next_power_untick_img, NULL, &next_power_p2);
                            SDL_RenderCopy(renderer, next_power_untick_img, NULL, &next_power_p1);
                            SDL_RenderCopy(renderer, next_court_tick_img, NULL, &next_court);
                            break;
                    default:SDL_RenderCopy(renderer, next_untick_img, NULL, &next_p1);
                            SDL_RenderCopy(renderer, next_untick_img, NULL, &next_p2);
                            SDL_RenderCopy(renderer, next_power_untick_img, NULL, &next_power_p2);
                            SDL_RenderCopy(renderer, next_power_untick_img, NULL, &next_power_p1);
                            SDL_RenderCopy(renderer, next_court_untick_img, NULL, &next_court);
                            break;

                }
            SDL_RenderCopy(renderer, chose_p1_img, NULL, &chose_p1);
            SDL_RenderCopy(renderer, chose_p2_img, NULL, &chose_p2);

            SDL_RenderCopy(renderer, power_p1_img, NULL, &power_p1);
            SDL_RenderCopy(renderer, power_p2_img, NULL, &power_p2);

            SDL_RenderCopy(renderer, chose_court_img, NULL, &chose_court);
        }else if(chose_name){
            text(400, 500, 0, txt.c_str(), 100, {255,255,255,255});
            SDL_RenderCopy(renderer, insert_p1_img, NULL, &insert_player);
        }else{
            text(400, 500, 0, txt.c_str(), 100, {255,255,255,255});
            SDL_RenderCopy(renderer, insert_p2_img, NULL, &insert_player);
        }
        SDL_RenderCopy(renderer, ok_img, NULL, &ok);

    }else if(onSetting){
        SDL_RenderCopy(renderer, menu_back_img, NULL, NULL);
        SDL_RenderCopy(renderer, lan_title_img, NULL, &lan_title);
        SDL_RenderCopy(renderer, ok_img, NULL, &ok);
        SDL_RenderCopy(renderer, condition_title_img, NULL, &condition_title);

        switch(lan_po){
            case 0: SDL_RenderCopy(renderer, lan_en_tick_img, NULL, &lan_en);
                    SDL_RenderCopy(renderer, lan_fars_untick_img, NULL, &lan_fars);
                    break;
            case 1: SDL_RenderCopy(renderer, lan_en_untick_img, NULL, &lan_en);
                    SDL_RenderCopy(renderer, lan_fars_tick_img, NULL, &lan_fars);
                    break;
        }
        switch(end_po){
            case 0: SDL_RenderCopy(renderer, time_condition_tick_img, NULL, &time_condition);
                    SDL_RenderCopy(renderer, goal_condition_untick_img, NULL, &goal_condition);
                    break;
            case 1: SDL_RenderCopy(renderer, time_condition_untick_img, NULL, &time_condition);
                    SDL_RenderCopy(renderer, goal_condition_tick_img, NULL, &goal_condition);
                    break;
        }
        text(475, 515, 0, time_limit.c_str(), 50, {255,255,204,255});
    }else if(onCourt){

        if(onGoal){
                if(goal_p1)
                    SDL_RenderCopy(renderer, court_p1_img, NULL, NULL);
                else if(goal_p2)
                    SDL_RenderCopy(renderer, court_p2_img, NULL, NULL);
        }else{
            if(!ani_menu)
                SDL_RenderCopy(renderer, court_img, NULL, NULL);
            else
                SDL_RenderCopy(renderer, welcome, NULL, NULL);
        }
        if(!ani_menu){
            SDL_RenderCopy(renderer, gate1_img, NULL, &gate1);
            SDL_RenderCopy(renderer, gate2_img, NULL, &gate2);
            SDL_RenderCopy(renderer, ball_img, &src_ball, &ball);
            ostringstream tem;
            if(timer.getTime() > delay && !isEnd){
                tem << (int)(timer.getTime()-delay)/1000;
                text(600, 0, 1, tem.str().c_str(), 72, {255,255,255,255});
            }
            int b = 255;
            text(10, 10, 0, saving[0][0].c_str(), 72, {255,255,255,255});
            b = (thief_p1) ? 20 : 255;
            text(370, 40, 0, show_power[power_p1_po].c_str(), 35, {255,255,b,255});
            text(450, 10, 0, to_string(score_p1).c_str(), 72, {255,255,255,255});
            text(800, 10, 0, saving[0][3].c_str(), 72, {255,255,255,255});
            b = (thief_p2) ? 20 : 255;
            text(1070, 40, 0, show_power[power_p2_po].c_str(), 35, {255,255,b,255});
            text(1150, 10, 0, to_string(score_p2).c_str(), 72, {255,255,255,255});
        }
        SDL_RenderCopy(renderer, process_img, NULL, &process_p1);
        SDL_RenderCopy(renderer, process_img, NULL, &process_p2);
        if(process_p1.w >= 450)
            text(30, 100, 1, "Power Time", 40, {255,255,255,255});
        if(process_p2.w >= 450)
            text(820, 100, 1, "Power Time", 40, {255,255,255,255});

        if(onPower_p2 && power_p2_po !=3 && power_p2_po !=0){
            if(power_p2_po==1)
                SDL_RenderCopy(renderer, p2_tel_img, NULL, &player2);
            else if(power_p2_po==2)
                SDL_RenderCopy(renderer, p2_fire_kick_img, &src_player2, &player2);
            else if(power_p2_po==4)
                SDL_RenderCopy(renderer, p2_hit_img, &src_player2, &player2);
        }
        else if(shoot_p2){
            SDL_RenderCopy(renderer, p2_kick_img, &src_player2, &player2);
            if(onPower_p2 && power_p2_po == 0){
                temp = player2;
                temp.x += 120;
                SDL_RenderCopy(renderer, p2_kick_img, &src_player2, &temp);
                temp.x -= 240;
                SDL_RenderCopy(renderer, p2_kick_img, &src_player2, &temp);
            }
        }
        else if(ko_p2){
            SDL_RenderCopy(renderer, p2_ko_img, &src_player2, &player2);
            if(onPower_p2 && power_p2_po == 0){
                temp = player2;
                temp.x += 120;
                SDL_RenderCopy(renderer, p2_ko_img, &src_player2, &temp);
                temp.x -= 240;
                SDL_RenderCopy(renderer, p2_ko_img, &src_player2, &temp);
            }
        }
        else if(idle_p2 && player2.y >= p_ground){
            SDL_RenderCopy(renderer, p2_idle_img, &src_player2, &player2);
            if(onPower_p2 && power_p2_po == 0){
                temp = player2;
                temp.x += 120;
                SDL_RenderCopy(renderer, p2_idle_img, &src_player2, &temp);
                temp.x -= 240;
                SDL_RenderCopy(renderer, p2_idle_img, &src_player2, &temp);
            }
        }
        else if(jump_p2){
            SDL_RenderCopy(renderer, p2_jump_img, NULL, &player2);
             if(onPower_p2 && power_p2_po == 0){
                temp = player2;
                temp.x += 120;
                SDL_RenderCopy(renderer, p2_jump_img, NULL, &temp);
                temp.x -= 240;
                SDL_RenderCopy(renderer, p2_jump_img, NULL, &temp);
            }
        }
        else if(player2.y < p_ground){
            SDL_RenderCopy(renderer, p2_jump_img, NULL, &player2);
            if(onPower_p2 && power_p2_po == 0){
                temp = player2;
                temp.x += 120;
                SDL_RenderCopy(renderer, p2_jump_img, NULL, &temp);
                temp.x -= 240;
                SDL_RenderCopy(renderer, p2_jump_img, NULL, &temp);
            }
        }
        else if(run_p2){
            SDL_RenderCopy(renderer, p2_run_img, &src_player2, &player2);
            if(onPower_p2 && power_p2_po == 0){
                temp = player2;
                temp.x += 120;
                SDL_RenderCopy(renderer, p2_run_img, &src_player2, &temp);
                temp.x -= 240;
                SDL_RenderCopy(renderer, p2_run_img, &src_player2, &temp);
             }
        }
        if(onPower_p1 && power_p1_po !=3 && power_p1_po !=0){
            if(power_p1_po==1)
                SDL_RenderCopy(renderer, p1_tel_img, NULL, &player1);
            else if(power_p1_po==2)
                SDL_RenderCopy(renderer, p1_fire_kick_img, &src_player1, &player1);
            else if(power_p1_po==4)
                SDL_RenderCopy(renderer, p1_hit_img, &src_player1, &player1);
        }
        else if(shoot_p1){
            SDL_RenderCopy(renderer, p1_kick_img, &src_player1, &player1);
            if(onPower_p1 && power_p1_po == 0){
                temp = player1;
                temp.x += 120;
                SDL_RenderCopy(renderer, p1_kick_img, &src_player1, &temp);
                temp.x -= 240;
                SDL_RenderCopy(renderer, p1_kick_img, &src_player1, &temp);
            }
        }
        else if(ko_p1){
            SDL_RenderCopy(renderer, p1_ko_img, &src_player1, &player1);
            if(onPower_p1 && power_p1_po == 0){
                temp = player1;
                temp.x += 120;
                SDL_RenderCopy(renderer, p1_ko_img, &src_player1, &temp);
                temp.x -= 240;
                SDL_RenderCopy(renderer, p1_ko_img, &src_player1, &temp);
            }
        }
        else if(idle_p1 && player1.y >= p_ground){
            SDL_RenderCopy(renderer, p1_idle_img, &src_player1, &player1);
            if(onPower_p1 && power_p1_po == 0){
                temp = player1;
                temp.x += 120;
                SDL_RenderCopy(renderer, p1_idle_img, &src_player1, &temp);
                temp.x -= 240;
                SDL_RenderCopy(renderer, p1_idle_img, &src_player1, &temp);
            }
        }
        else if(jump_p1){
            SDL_RenderCopy(renderer, p1_jump_img, NULL, &player1);
            if(onPower_p1 && power_p1_po == 0){
                temp = player1;
                temp.x += 120;
                SDL_RenderCopy(renderer, p1_jump_img, NULL, &temp);
                temp.x -= 240;
                SDL_RenderCopy(renderer, p1_jump_img, NULL, &temp);
            }
        }
        else if(player1.y < p_ground){
            SDL_RenderCopy(renderer, p1_jump_img, NULL, &player1);
             if(onPower_p1 && power_p1_po == 0){
                temp = player1;
                temp.x += 120;
                SDL_RenderCopy(renderer, p1_jump_img, NULL, &temp);
                temp.x -= 240;
                SDL_RenderCopy(renderer, p1_jump_img, NULL, &temp);
             }
        }
        else if(run_p1){
            SDL_RenderCopy(renderer, p1_run_img, &src_player1, &player1);
             if(onPower_p1 && power_p1_po == 0){
                temp = player1;
                temp.x += 120;
                SDL_RenderCopy(renderer, p1_run_img, &src_player1, &temp);
                temp.x -= 240;
                SDL_RenderCopy(renderer, p1_run_img, &src_player1, &temp);
             }
        }
        if(isEnd){
                SDL_RenderCopy(renderer, end_img, NULL, &End);
            if(winner == 1){
                text(450, 350, 0, saving[0][0].c_str(), 100, {255,255,255,255});
                text(750, 350, 0, "Wins", 100, {255,255,255,255});
            }else if(winner == 2){
                text(450, 350, 0, saving[0][3].c_str(), 100, {255,255,255,255});
                text(750, 350, 0, "Wins", 100, {255,255,255,255});
            }else{
                text(600, 350, 0, "Draw", 100, {255,255,255,255});
            }
        }else if(onGoal)
            SDL_RenderCopy(renderer, goal_img, NULL, &goal);
        if(onPause){
            SDL_RenderCopy(renderer, pause_img, NULL, &pause);
            if(pause_frame > 60){
                switch(pause_po){
                    case 0: SDL_RenderCopy(renderer, quit_untick_img, NULL, &quit);
                            SDL_RenderCopy(renderer, main_menu_tick_img, NULL, &main_menu);
                            break;
                    case 1: SDL_RenderCopy(renderer, quit_tick_img, NULL, &quit);
                            SDL_RenderCopy(renderer, main_menu_untick_img, NULL, &main_menu);
                            break;
                    default:SDL_RenderCopy(renderer, quit_untick_img, NULL, &quit);
                            SDL_RenderCopy(renderer, main_menu_untick_img, NULL, &main_menu);
                            break;
                    }
            }
        }
        if(onCheat1){
            SDL_RenderCopy(renderer, wall_1_img,NULL, &obstacle1);
        }
        if(onCheat2){
            SDL_RenderCopy(renderer, wall_2_img, NULL, &obstacle2);
        }
        if(counting && !ani_menu)
            SDL_RenderCopy(renderer, counter_img, NULL, &counter);
        if(ani_menu){
            if(pause_frame <=60)
                SDL_RenderCopy(renderer, menu_back_img, NULL, &menu_back);
            else {
                SDL_RenderCopy(renderer, welcome, NULL, NULL);
                SDL_RenderCopy(renderer, p1_run_img , &src_player1, &player1);
                SDL_RenderCopy(renderer, p2_run_img , &src_player2, &player2);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

int pause_Out(int start, int finish, double current_frame, int nFrames)
{
    int change=finish-start;
    current_frame/=nFrames;
    current_frame--;
    return change*(current_frame*current_frame*current_frame+1)+start;
}

Uint32 callback(Uint32 interval, void* param)
{
     onPause = (onPause) ? false : true;
        if (!onPause)   counting = true;
        pause_frame = 0;
        SDL_Delay(200);
        return 0;
}

void text(int x, int y, int font, const char* message, int f_size, SDL_Color color)
{
        const char* f_path0 = "fonts/oregano.ttf";
        const char* f_path1 = "fonts/segoeprb.ttf";
        const char* font_path = (font == 0) ? f_path0 : f_path1;
        TTF_Font* Font = TTF_OpenFont(font_path, f_size);

        SDL_Surface* surface = TTF_RenderText_Solid(Font, message, color);

        SDL_Rect text = {x, y, surface->w, surface->h};

        SDL_Texture* txt = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        SDL_RenderCopy(renderer, txt, NULL, &text);
        SDL_DestroyTexture(txt);
}

void set_data()
{
    ifstream fin("./savings.txt", ios::in);
    for(int k=0; k<5; k++)
        for(int i=0; i<9; i++)
            getline(fin, saving[k][i]);
    for(int k=0; k<5; k++){
        for(int i=0; i<9; i++)
            cout << saving[k][i] << " ";
        cout << endl;
    }
    ifstream fin_app("app_data.txt", ios::in);
    fin_app >> lan_now;
    //cout << "lan = "<< lan_now <<endl;
    fin_app >> end_po;
    string temp;
    fin_app >> temp;
    time_limit=" ";
    time_limit += temp;
    stringstream stream(temp);
    stream >> limit;
    //cout << "time limit = "<<limit <<endl;
}

void update_data(string char1, string char2)
{
    int skin1, skin2;
    if(char1 == "Orc")
        skin1 = 0;
    else if(char1 == "Ogre")
        skin1 = 1;
    else if(char1 == "Gablin")
        skin1 = 2;
    if(char2 == "Orc")
        skin2 = 0;
    else if(char2 == "Ogre")
        skin2 = 1;
    else if(char2 == "Gablin")
        skin2 = 2;
    stringstream tempC(saving[saving_po][8]);
    int tem;
    tempC >> tem;
    set_skin(skin1, skin2, tem);

    stringstream temp1(saving[saving_po][6]);
    temp1 >> power_p1_po;
    if(power_p1_po == 5){
            thief_p1=true;
            srand(time(NULL));
            power_p1_po = rand()%5;
    }

    stringstream temp2(saving[saving_po][7]);
    temp2 >> power_p2_po;
    if(power_p2_po == 5){
            thief_p2=true;
            srand(time(NULL));
            power_p2_po = rand()%5;
    }

    if(saving_po !=0){
        string tem[9];
            for(int i=0; i<9; i++)
                tem[i] = saving[saving_po][i];
        for(int i=saving_po; i > 0; i--){
            for(int k=0; k<9; k++)
                saving[i][k] = saving[i-1][k];
        }
        for(int i=0; i<9; i++)
            saving[0][i] = tem[i];
        ofstream fout("./savings.txt", ios::out);
            for(int k=0; k<5; k++)
                for(int i=0; i<9; i++)
                    fout << saving[k][i] << endl;
    }
}

void reset_data(bool menu, bool board)
{
    onCourt = false;
    onPause = false;
    counting = false;
    onMenu = menu;
    onGoal = false;
    onSavingBoard = board;
    onNewGame = false;
    onSetting = false;
    ani_menu = false;
    chose_char=true;
    chose_name=false;
    idle_p1 = true;
    shoot_p1 = false;
    idle_p2 = true;
    shoot_p2 = false;
    onPower_p1=false;
    onPower_p2=false;
    thief_p1=false;
    thief_p2=false;
    hit_p1 = false;
    hit_p2 = false;
    ko_p1 = false;
    ko_p2 = false;
    goal_p1 = false;
    goal_p2 = false;
    fire_kick_p1 = false;
    fire_kick_p2 = false;
    fire_head_p1 = false;
    fire_head_p2 = false;
    thief_p1 = false;
    thief_p2 = false;
    change_chose_p1 = true;
    change_chose_p2 = true;
    change_power_p1 = true;
    change_power_p2 = true;
    change_court = true;
    onCheat1 = false;
    onCheat2 = false;
    onKey1 = false;
    onKey2 = false;
    isEnd=false;
    onCheat1= false;
    onCheat2= false;
    Uint32 tempTime=0;
    vx_ball = 0;
    vy_ball = 0;
    v_power_p1=0.5;
    v_power_p2=0.5;
    add1 =0;
    add2 =0;
    score_p1=0;
    score_p2=0;
    menu_po=-1;
    pause_po=-1;
    saving_po=0;
    lan_po=0;
    chose_court_po=0;
    chose_p1_po=1;
    chose_p2_po=0;
    power_p1_po=1;
    power_p2_po=4;
    new_po=-1;
    board_po=-1;
    pause_frame=0;
    set_B(0);
    txt = " ";
    ball = {615, 400, 50, 50};
    src_ball = {0, 0, 97, 100};
    player1 = {50,p_ground, 300, 300};
    src_player1 = {-300,0, p_size, p_size};
    player2 = {1250,p_ground, 300, 300};
    src_player2 = {0,0, p_size, p_size};
    load = {450, 360, 240, 94};
    quit = {450, 690, 240, 94};
    main_menu = {551, 650, 240, 94};
    pause = {640, 400, 0, 0};
    counter = {490, 250, 300, 300};
    process_p1 = {10, 100, 0, 72};
    process_p2 = {800, 100, 0, 72};

    counter_img = IMG_LoadTexture(renderer, "images/number/ready.png");

}

void set_skin(int skin1, int skin2, int court_po)
{
    switch(skin1){
        case 0: p1_idle_img = IMG_LoadTexture(renderer, "images/player1/orc/idle.png");
                p1_jump_img = IMG_LoadTexture(renderer, "images/player1/orc/jump.png");
                p1_run_img = IMG_LoadTexture(renderer, "images/player1/orc/run.png");
                p1_kick_img = IMG_LoadTexture(renderer, "images/player1/orc/kick.png");
                p1_fire_kick_img = IMG_LoadTexture(renderer, "images/player1/orc/fire_kick.png");
                p1_tel_img = IMG_LoadTexture(renderer, "images/player1/orc/teleport.png");
                p1_hit_img = IMG_LoadTexture(renderer, "images/player1/orc/punch.png");
                p1_ko_img = IMG_LoadTexture(renderer, "images/player1/orc/ko1.png");
                break;
        case 1: p1_idle_img = IMG_LoadTexture(renderer, "images/player1/ogre/idle.png");
                p1_jump_img = IMG_LoadTexture(renderer, "images/player1/ogre/jump.png");
                p1_run_img = IMG_LoadTexture(renderer, "images/player1/ogre/run.png");
                p1_kick_img = IMG_LoadTexture(renderer, "images/player1/ogre/kick.png");
                p1_fire_kick_img = IMG_LoadTexture(renderer, "images/player1/ogre/fire_kick.png");
                p1_tel_img = IMG_LoadTexture(renderer, "images/player1/ogre/teleport.png");
                p1_hit_img = IMG_LoadTexture(renderer, "images/player1/ogre/punch.png");
                p1_ko_img = IMG_LoadTexture(renderer, "images/player1/ogre/ko1.png");
                break;
        case 2: p1_idle_img = IMG_LoadTexture(renderer, "images/player1/gablin/idle.png");
                p1_jump_img = IMG_LoadTexture(renderer, "images/player1/gablin/jump.png");
                p1_run_img = IMG_LoadTexture(renderer, "images/player1/gablin/run.png");
                p1_kick_img = IMG_LoadTexture(renderer, "images/player1/gablin/kick.png");
                p1_fire_kick_img = IMG_LoadTexture(renderer, "images/player1/gablin/fire_kick.png");
                p1_tel_img = IMG_LoadTexture(renderer, "images/player1/gablin/teleport.png");
                p1_hit_img = IMG_LoadTexture(renderer, "images/player1/gablin/punch.png");
                p1_ko_img = IMG_LoadTexture(renderer, "images/player1/gablin/ko1.png");
                break;
    }
    switch(skin2){
        case 0: p2_idle_img = IMG_LoadTexture(renderer, "images/player2/orc/idle.png");
                p2_jump_img = IMG_LoadTexture(renderer, "images/player2/orc/jump.png");
                p2_run_img = IMG_LoadTexture(renderer, "images/player2/orc/run.png");
                p2_kick_img = IMG_LoadTexture(renderer, "images/player2/orc/kick.png");
                p2_fire_kick_img = IMG_LoadTexture(renderer, "images/player2/orc/fire_kick.png");
                p2_tel_img = IMG_LoadTexture(renderer, "images/player2/orc/teleport.png");
                p2_hit_img = IMG_LoadTexture(renderer, "images/player2/orc/punch.png");
                p2_ko_img = IMG_LoadTexture(renderer, "images/player2/orc/ko1.png");
                break;
        case 1: p2_idle_img = IMG_LoadTexture(renderer, "images/player2/ogre/idle.png");
                p2_jump_img = IMG_LoadTexture(renderer, "images/player2/ogre/jump.png");
                p2_run_img = IMG_LoadTexture(renderer, "images/player2/ogre/run.png");
                p2_kick_img = IMG_LoadTexture(renderer, "images/player2/ogre/kick.png");
                p2_fire_kick_img = IMG_LoadTexture(renderer, "images/player2/ogre/fire_kick.png");
                p2_tel_img = IMG_LoadTexture(renderer, "images/player2/ogre/teleport.png");
                p2_hit_img = IMG_LoadTexture(renderer, "images/player2/ogre/punch.png");
                p2_ko_img = IMG_LoadTexture(renderer, "images/player2/ogre/ko1.png");
                break;
        case 2: p2_idle_img = IMG_LoadTexture(renderer, "images/player2/gablin/idle.png");
                p2_jump_img = IMG_LoadTexture(renderer, "images/player2/gablin/jump.png");
                p2_run_img = IMG_LoadTexture(renderer, "images/player2/gablin/run.png");
                p2_kick_img = IMG_LoadTexture(renderer, "images/player2/gablin/kick.png");
                p2_fire_kick_img = IMG_LoadTexture(renderer, "images/player2/gablin/fire_kick.png");
                p2_tel_img = IMG_LoadTexture(renderer, "images/player2/gablin/teleport.png");
                p2_hit_img = IMG_LoadTexture(renderer, "images/player2/gablin/punch.png");
                p2_ko_img = IMG_LoadTexture(renderer, "images/player2/gablin/ko1.png");
                break;
    }
    switch(court_po){
        case 0: court_img = IMG_LoadTexture(renderer, "images/court_0.jpg");
                court_p1_img = IMG_LoadTexture(renderer, "images/court_0_p1_goal.jpg");
                court_p2_img = IMG_LoadTexture(renderer, "images/court_0_p2_goal.jpg");
                welcome = IMG_LoadTexture(renderer, "images/features/court_0.png");
                break;
        case 1: court_img = IMG_LoadTexture(renderer, "images/court_1.jpg");
                court_p1_img = IMG_LoadTexture(renderer, "images/court_1_p1_goal.jpg");
                court_p2_img = IMG_LoadTexture(renderer, "images/court_1_p2_goal.jpg");
                welcome = IMG_LoadTexture(renderer, "images/features/court_1.png");
                break;
        case 2: court_img = IMG_LoadTexture(renderer, "images/court_2.jpg");
                court_p1_img = IMG_LoadTexture(renderer, "images/court_2_p1_goal.jpg");
                court_p2_img = IMG_LoadTexture(renderer, "images/court_2_p2_goal.jpg");
                welcome = IMG_LoadTexture(renderer, "images/features/court_2.png");
                break;

    }


}

void set_B(int i)
{
    saving_po = i;
    for(int k=0; k<5; k++)
        if(k != i)
            B[k] = 255;
        else
            B[k] = 20;
}


void Timer::start()
{
    started = true;
    paused = false;

    startTime = SDL_GetTicks();
    pauseTime = 0;
}

void Player::setParameters(int p, int xh, int yh, int xb, int yb, int wb, int hb, int xf, int yf, int wf, int hf)
{
    if(!p){
        x_head = player1.x+xh;
        y_head = player1.y+yh;
        head = {x_head-head_r, y_head-head_r, 2*head_r, 2*head_r};
        body = {player1.x+xb, player1.y+yb, wb, hb};
        feet = {player1.x+xf, player1.y+yf, wf, hf};
    }else{
        x_head = player2.x+xh;
        y_head = player2.y+yh;
        head = {x_head-head_r, y_head-head_r, 2*head_r, 2*head_r};
        body = {player2.x+xb, player2.y+yb, wb, hb};
        feet = {player2.x+xf, player2.y+yf, wf, hf};
    }
}

void Player::setRellativeDirection()
{
    bool onAir = false;
    bool onClone = false;
    if(!player){
        if(onPower_p1 && power_p1_po == 0)
            onClone = true;
        if(shoot_p1){
            if(onClone)
                setParameters(0,135, 130, 100, 195, 90, 10, 235, 205, 100, 45);
            else
                setParameters(0,135, 130, 100, 195, 90, 10, 115, 205, 100, 45);
        }
        else if(idle_p1 && player1.y >= p_ground){
            setParameters(0,145, 140, 110, 200, 75, 40, 120, 240, 72, 15);
        }
        else if(jump_p1){
                onAir=true;
            setParameters(0,130, 125, 115, 185, 60, 25, 115, 210, 95, 25);
        }
        else if(player1.y < p_ground){
                onAir=true;
            setParameters(0,130, 125, 115, 185, 60, 25, 115, 210, 95, 25);
        }
        else if(run_p1){
            setParameters(0,145, 140, 110, 200, 75, 40, 120, 240, 72, 15);
        }
    }else{
        if(onPower_p2 && power_p2_po == 0)
            onClone = true;
        if(shoot_p2){
            if(onClone)
                setParameters(1,165, 135, 120, 195, 90, 10, -30, 205, 100, 45);
            else
                setParameters(1,165, 135, 120, 195, 90, 10, 90, 205, 100, 45);

        }
        else if(idle_p2 && player2.y >= p_ground){
            setParameters(1,155, 140, 115, 200, 75, 40, 105, 240, 72, 15);
        }
        else if(jump_p2){
                onAir=true;
            setParameters(1,170, 125, 125, 185, 60, 25, 90, 210, 95, 25);
        }
        else if(player2.y < p_ground){
                onAir=true;
            setParameters(1,170, 125, 125, 185, 60, 25, 90, 210, 95, 25);
        }
        else if(run_p2){
            setParameters(1,155, 140, 115, 200, 75, 40, 105, 240, 72, 15);
        }
    }
    if(onClone){
        if(onAir)
            rect = {x_head-190,y_head-50,360,165};
        else
            rect = {x_head-170,y_head-50,340,165};
    }else{
        if(onAir)
            rect = {x_head-70,y_head-50,120,165};
        else
            rect = {x_head-50,y_head-50,100,165};
    }
}

Uint32 Timer::getTime()
{
    Uint32 time = 0;
    if(started){
        if(paused){
            time = pauseTime;
        }
        else{
            time = SDL_GetTicks() - startTime;
        }
    }
    return time;
}

bool hasIntersection(Player player)
{
    int r2 = (r_ball.x-player.x_head)*(r_ball.x-player.x_head) + (r_ball.y-player.y_head)*(r_ball.y-player.y_head);
    if(r2 <= 7225) {
            return true;
    }
    return false;
}

void shoot1()
{
    if(SDL_HasIntersection(&ball, &p1.feet) && ball.x >= p1.feet.x+40){
        if(power_p1_po==3 && onPower_p1)
            SDL_SetTextureAlphaMod(ball_img, 0);
        if(r_ball.y > p1.feet.y+15 && r_ball.y <= p1.feet.y+30){
            vx_ball=20;
            vy_ball=-6;
        }
        if(r_ball.y <= p1.feet.y+15){
            vx_ball=20;
            vy_ball=-20;
        }
        if(player1.y < p_ground && r_ball.y > p1.feet.y+30){
            vx_ball=20;
            vy_ball=20;
        }
    }
}

void shoot2()
{
    if(SDL_HasIntersection(&ball, &p2.feet) && ball.x <= p2.feet.x+40){
        if(power_p2_po==3 && onPower_p2)
            SDL_SetTextureAlphaMod(ball_img, 0);
        if(r_ball.y > p2.feet.y+15 && r_ball.y <= p2.feet.y+30){
            vx_ball=-20;
            vy_ball=-6;
        }
        if(r_ball.y <= p2.feet.y+15){
            vx_ball=-20;
            vy_ball=-20;
        }
        if(player2.y < p_ground && r_ball.y > p2.feet.y+30){
            vx_ball=-20;
            vy_ball=20;
        }
    }
}

void setWinner()
{
    if(score_p1 > score_p2){
        int win;
        winner = 1;
        stringstream tem(saving[0][2]);
        tem >> win;
        win++;
        saving[0][2] = to_string(win);
    }
    else if(score_p1 < score_p2){
        int win;
        winner = 2;
        stringstream tem(saving[0][5]);
        tem >> win;
        win++;
        saving[0][5] = to_string(win);
    }else
        winner = 0;

}

void check_ball()
{

    if(power_p1_po == 1 && hit_p2 && player2.x >= temp_x_p2+200){
                vx_ball = -10;
                fire_head_p1 = false;
                hit_p2 = false;
                ko_p2 = true;
                temp2_time = timer.getTime()-delay;
    }
    if(power_p2_po == 1 && hit_p1 && player1.x <= temp_x_p1-200){
                vx_ball = 10;
                fire_head_p2 = false;
                hit_p1 = false;
                ko_p1 = true;
                temp1_time = timer.getTime()-delay;
    }


    if(SDL_HasIntersection(&ball, &p1.rect) && SDL_HasIntersection(&ball, &p2.rect) && abs(player1.x-player2.x)<=p1.rect.w+50){
        if(player1.x < player2.x){
        player1.x-=25;
        player2.x+=25;
        }
        if(player1.x > player2.x){
        player1.x+=25;
        player2.x-=25;
        }
    }
    if(SDL_HasIntersection(&ball, &p1.rect)){
        if(fire_kick_p2){
            if(!hit_p1)
                temp_x_p1 = player1.x;
            hit_p1 = true;
            vx_p1 = vx_ball;
            if(player1.x <= temp_x_p1-200){
                vx_ball = 10;
                fire_kick_p2 = false;
                hit_p1 = false;
                ko_p1 = true;
                temp1_time = timer.getTime()-delay;
            }
        }else if(fire_head_p2){
            if(!hit_p1){
                vx_p1 = vx_ball;
                temp_x_p1 = player1.x;
            }
            hit_p1 = true;
            if(SDL_HasIntersection(&ball, &p1.head)){
                ball.y -= vy_ball;
                vy_ball *= -0.8;
            }
            else{
                vy_ball = 0;
            }
        }
        else if(ball.y <= p1.rect.y || ball.y+50 >= p1.rect.y+p1.rect.h){
            player1.y -= v1_jump;
            vx_ball += vx_p1;
            if(vy_ball*v1_jump <= 0 && vy_ball !=0){
                ball.y -= vy_ball;
                SDL_Delay(5);
                vy_ball *= -0.8;
            }
            if(vy_ball*v1_jump >= 0 && v1_jump !=0){
                ball.y += vy_ball;
                vy_ball = v1_jump;
            }

        }
        else{

            player1.x -= vx_p1;
            /*if(p1.rect.y-ball.y < p1.rect.h-5 && ball.x + 45> p1.rect.x  && p1.rect.x+p1.rect.w>ball.x){
                ball.x = p1.rect.x+p1.rect.w+15;
                vy_ball = -4;
            }*/
            if(idle_p1 && ball.x + 45> p1.rect.x && p1.rect.x+p1.rect.w-5>ball.x){
                ball.x = p1.rect.x+p1.rect.w+15;
                vy_ball=-4;
            }
            if(vx_ball*vx_p1 <= 0 && vx_ball !=0){
                ball.x -= vx_ball;
                vx_ball *= -0.8;
            }
            if(vy_ball*vx_p1 >= 0 && vx_p1 !=0){
                ball.x += vx_ball;
                vx_ball = vx_p1;
            }
        }
    }

    if(SDL_HasIntersection(&ball, &p2.rect) ){
        if(fire_kick_p1){
            if(!hit_p2)
                temp_x_p2 = player2.x;
            hit_p2 = true;
            vx_p2 = vx_ball;
            if(player2.x >= temp_x_p2+200){
                vx_ball = -10;
                fire_kick_p1 = false;
                hit_p2 = false;
                ko_p2 = true;
                temp2_time = timer.getTime()-delay;
            }
        }else if(fire_head_p1){
            if(!hit_p2){
                vx_p2 = vx_ball;
                temp_x_p2 = player2.x;
            }
            hit_p2 = true;
            if(SDL_HasIntersection(&ball, &p2.head)){
                ball.y -= vy_ball;
                vy_ball *= -0.8;
            }
            else{
                vy_ball = 0;
            }

        }
        else if(ball.y <= p2.rect.y || ball.y+50 >= p2.rect.y+p2.rect.h){
            player2.y -= v2_jump;
            vx_ball += vx_p2;
            if(vy_ball*v2_jump <= 0 && vy_ball !=0){
                ball.y -= vy_ball;
                vy_ball *= -0.8;
            }
            if(vy_ball*v2_jump >= 0 && v2_jump !=0){
                ball.y += vy_ball;
                vy_ball = v2_jump;
            }

        }
        else{
            player2.x -= vx_p2;
        if(idle_p2 && ball.x + 45> p2.rect.x && p2.rect.x+p2.rect.w-5>ball.x){
                ball.x = p2.rect.x-65;
                vy_ball=-4;
        }
         if(vx_ball*vx_p2 <=0 && vx_ball !=0){
                ball.x -= vx_ball;
                vx_ball *= -0.8;
         }
            if(vy_ball*vx_p2 >= 0 && vx_p2 !=0){
                ball.x += vx_ball;
                vx_ball = vx_p2;
            }

        }
    }
}

void write_data()
{
    ofstream fout("savings.txt", ios::out);
    for(int i=0; i<5; i++)
        for(int j=0; j<9; j++)
            fout << saving[i][j] << endl;
    ofstream fout_app("app_data.txt", ios::out);
    fout_app << lan_now<<endl;
    fout_app << end_po<<endl;
    fout_app <<time_limit<<endl;
}

void check_cheat(char input, bool player)
{
    if(!onKey1){
            if(!player){
            int index = input_cheat1.length();
                    if(cheat[index] == input)
                        input_cheat1 += input;
                    else if(input_cheat1.length() != 0)
                        input_cheat1 = "";

            if(input_cheat1 == cheat){
                input_cheat1 = "";
                onCheat1= true;
                temp_time1=timer.getTime()-delay;
            }
            onKey1 = true;
            tempTime1 = timer.getTime()-delay;
        }
    }
    if(!onKey2){
            if(player){
            int index = input_cheat2.length();
                    if(cheat[index] == input)
                        input_cheat2 += input;
                    else if(input_cheat2.length() != 0)
                        input_cheat2 = "";

            if(input_cheat2 == cheat){
                input_cheat2 = "";
                onCheat2= true;
                temp_time2=timer.getTime()-delay;
            }
            onKey2 = true;
            tempTime2 = timer.getTime()-delay;
        }
    }
}

void set_lan(int lan)
{
    if(lan == 0){
        condition_title_img = IMG_LoadTexture(renderer, "images/condition_title.png");
        time_condition_untick_img = IMG_LoadTexture(renderer, "images/buttons/time_condition_untick.png");
        time_condition_tick_img = IMG_LoadTexture(renderer, "images/buttons/time_condition_tick.png");
        goal_condition_untick_img = IMG_LoadTexture(renderer, "images/buttons/goal_condition_untick.png");
        goal_condition_tick_img= IMG_LoadTexture(renderer, "images/buttons/goal_condition_tick.png");
        load_tick_img = IMG_LoadTexture(renderer, "images/buttons/load_tick.png");
        load_untick_img = IMG_LoadTexture(renderer, "images/buttons/load_untick.png");
        new_save_tick_img = IMG_LoadTexture(renderer, "images/buttons/new_tick.png");
        new_save_untick_img = IMG_LoadTexture(renderer, "images/buttons/new_untick.png");
        setting_untick_img = IMG_LoadTexture(renderer, "images/buttons/set_untick.png");
        setting_tick_img = IMG_LoadTexture(renderer, "images/buttons/set_tick.png");
        quit_tick_img = IMG_LoadTexture(renderer, "images/buttons/quit_tick.png");
        quit_untick_img = IMG_LoadTexture(renderer, "images/buttons/quit_untick.png");
        main_menu_tick_img = IMG_LoadTexture(renderer, "images/buttons/main_menu_tick.png");
        main_menu_untick_img = IMG_LoadTexture(renderer, "images/buttons/main_menu_untick.png");
        insert_p1_img = IMG_LoadTexture(renderer, "images/insert_p1.png");
        insert_p2_img = IMG_LoadTexture(renderer, "images/insert_p2.png");
        next_tick_img = IMG_LoadTexture(renderer, "images/buttons/next_tick.png");
        next_untick_img = IMG_LoadTexture(renderer, "images/buttons/next_untick.png");
        ok_img = IMG_LoadTexture(renderer, "images/buttons/ok.png");
        next_power_tick_img = IMG_LoadTexture(renderer, "images/buttons/next_power_tick.png");
        next_power_untick_img = IMG_LoadTexture(renderer, "images/buttons/next_power_untick.png");
        next_court_tick_img = IMG_LoadTexture(renderer, "images/buttons/next_court_tick.png");
        next_court_untick_img = IMG_LoadTexture(renderer, "images/buttons/next_court_untick.png");
    }else{
        condition_title_img = IMG_LoadTexture(renderer, "images/fars_condition_title.png");
        time_condition_untick_img = IMG_LoadTexture(renderer, "images/buttons/fars_time_condition_untick.png");
        time_condition_tick_img = IMG_LoadTexture(renderer, "images/buttons/fars_time_condition_tick.png");
        goal_condition_untick_img = IMG_LoadTexture(renderer, "images/buttons/fars_goal_condition_untick.png");
        goal_condition_tick_img = IMG_LoadTexture(renderer, "images/buttons/fars_goal_condition_tick.png");
        load_tick_img = IMG_LoadTexture(renderer, "images/buttons/fars_load_tick.png");
        load_untick_img = IMG_LoadTexture(renderer, "images/buttons/fars_load_untick.png");
        new_save_tick_img = IMG_LoadTexture(renderer, "images/buttons/fars_new_tick.png");
        new_save_untick_img = IMG_LoadTexture(renderer, "images/buttons/fars_new_untick.png");
        setting_untick_img = IMG_LoadTexture(renderer, "images/buttons/fars_set_untick.png");
        setting_tick_img = IMG_LoadTexture(renderer, "images/buttons/fars_set_tick.png");
        quit_tick_img = IMG_LoadTexture(renderer, "images/buttons/fars_quit_tick.png");
        quit_untick_img = IMG_LoadTexture(renderer, "images/buttons/fars_quit_untick.png");
        main_menu_tick_img = IMG_LoadTexture(renderer, "images/buttons/fars_main_menu_tick.png");
        main_menu_untick_img = IMG_LoadTexture(renderer, "images/buttons/fars_main_menu_untick.png");
        insert_p1_img = IMG_LoadTexture(renderer, "images/fars_insert_p1.png");
        insert_p2_img = IMG_LoadTexture(renderer, "images/fars_insert_p2.png");
        next_tick_img = IMG_LoadTexture(renderer, "images/buttons/fars_next_tick.png");
        next_untick_img = IMG_LoadTexture(renderer, "images/buttons/fars_next_untick.png");
        ok_img = IMG_LoadTexture(renderer, "images/buttons/fars_ok.png");
        next_power_tick_img = IMG_LoadTexture(renderer, "images/buttons/fars_next_power_tick.png");
        next_power_untick_img = IMG_LoadTexture(renderer, "images/buttons/fars_next_power_untick.png");
        next_court_tick_img = IMG_LoadTexture(renderer, "images/buttons/fars_next_court_tick.png");
        next_court_untick_img = IMG_LoadTexture(renderer, "images/buttons/fars_next_court_untick.png");
    }
}

void set_time_limit()
{
    for(int i=1; i<time_limit.length(); i++)
        if(time_limit[i]<48 && time_limit[i]>57){
            limit = 90;
            time_limit=" 90";
            return;
        }
    if(time_limit == " "){
        limit = 90;
        time_limit = " 90";
    }
    else{
        stringstream stream(time_limit);
        stream >> limit;
        if(limit < 60){
            limit = 60;
            time_limit = " 60";
        }
    }
}
