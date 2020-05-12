#ifndef CFG_H_INCLUDED
#define CFG_H_INCLUDED
#include <vector>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#define FRAME_PER_SECOND 60

enum Direction{RIGHT, LEFT, UP, DOWN};

struct Background_Cfg
{
    Background_Cfg()
    {
        outer[0].x = 0;
        outer[0].y = 0;
        outer[0].w = 716;
        outer[0].h = 50;

        outer[1].x = 0;
        outer[1].y = 50;
        outer[1].w = 50;
        outer[1].h = 616;

        outer[2].x = 666;
        outer[2].y = 50;
        outer[2].w = 50;
        outer[2].h = 616;

        outer[3].x = 0;
        outer[3].y = 666;
        outer[3].w = 716;
        outer[3].h = 50;

        middle[0].x = 50;
        middle[0].y = 50;
        middle[0].w = 616;
        middle[0].h = 100;

        middle[1].x = 50;
        middle[1].y = 150;
        middle[1].w = 100;
        middle[1].h = 416;

        middle[2].x = 566;
        middle[2].y = 150;
        middle[2].w = 100;
        middle[2].h = 416;

        middle[3].x = 50;
        middle[3].y = 566;
        middle[3].w = 616;
        middle[3].h = 100;

        inner.x = 150;
        inner.y = 150;
        inner.w = 416;
        inner.h = 416;

        for (int i=0; i != 3; ++i)
        {
            player_live_position[i].x = 576+i*20;
            player_live_position[i].y = 290+i*0;
            player_live_position[i].w = live_width;
            player_live_position[i].h = live_height;
        }

        home_path = std::string("images\\home.png");
        home.x = 150+32*6;
        home.y = 150+416-32;
        home.w = 32;
        home.h = 32;
    }

    const int width = 716;
    const int height = 716;

    std::vector<SDL_Rect> outer{4}; //最外部的一层
    std::vector<SDL_Rect> middle{4}; //中间的灰色层
    SDL_Rect inner; //最内层

    const int enemy_num_msg_x = 60;
    const int enemy_num_msg_y = 150;
    const int enemy_num_x = 80;
    const int enemy_num_y = 180;
    const int score_msg_x = 576;
    const int score_msg_y = 150;
    const int score_num_x = 596;
    const int score_num_y = 180;
    const int tip_x = 265;
    const int tip_y = 490;
    const int time_x = 335;
    const int time_y = 100;

    const int live_width = 16;
    const int live_height = 16;
    const int live_msg_x = 576;
    const int live_msg_y = 250;
    std::vector<SDL_Rect> player_live_position{3};

    std::string home_path;
    SDL_Rect home;

    const int game_time = 60*1000;
};

struct Start_Cfg
{
    Start_Cfg()
    {
        start_path = std::string("images\\battle_city.png");
    }

    const int width = 376;
    const int height = 136;

    const int start_x = 170;
    const int start_y = 260;

    std::string start_path;
};

struct Barrier_Cfg
{
    Barrier_Cfg()
    {
        brick_path = std::string("images\\wall_brick_min.png");

        barrier_boundary[0].x = 182;
        barrier_boundary[0].y = 182;
        barrier_boundary[0].w = 32;
        barrier_boundary[0].h = 144;

        barrier_boundary[1].x = 182+64;
        barrier_boundary[1].y = 182;
        barrier_boundary[1].w = 32;
        barrier_boundary[1].h = 144;

        barrier_boundary[2].x = 182+64*2;
        barrier_boundary[2].y = 182;
        barrier_boundary[2].w = 32;
        barrier_boundary[2].h = 144;

        barrier_boundary[3].x = 182+64*3;
        barrier_boundary[3].y = 182;
        barrier_boundary[3].w = 32;
        barrier_boundary[3].h = 144;

        barrier_boundary[4].x = 182+64*4;
        barrier_boundary[4].y = 182;
        barrier_boundary[4].w = 32;
        barrier_boundary[4].h = 144;

        barrier_boundary[5].x = 182+64*5;
        barrier_boundary[5].y = 182;
        barrier_boundary[5].w = 32;
        barrier_boundary[5].h = 144;

        barrier_boundary[6].x = 182+64*2+32;
        barrier_boundary[6].y = 182+144-64;
        barrier_boundary[6].w = 32;
        barrier_boundary[6].h = 32;

        barrier_boundary[7].x = 182;
        barrier_boundary[7].y = 390;
        barrier_boundary[7].w = 32;
        barrier_boundary[7].h = 144;

        barrier_boundary[8].x = 182+64;
        barrier_boundary[8].y = 390;
        barrier_boundary[8].w = 32;
        barrier_boundary[8].h = 144;

        barrier_boundary[9].x = 182+64*4;
        barrier_boundary[9].y = 390;
        barrier_boundary[9].w = 32;
        barrier_boundary[9].h = 144;

        barrier_boundary[10].x = 182+64*5;
        barrier_boundary[10].y = 390;
        barrier_boundary[10].w = 32;
        barrier_boundary[10].h = 144;

        barrier_boundary[11].x = 310;
        barrier_boundary[11].y = 358;
        barrier_boundary[11].w = 96;
        barrier_boundary[11].h = 32;

        barrier_boundary[12].x = 310;
        barrier_boundary[12].y = 502;
        barrier_boundary[12].w = 96;
        barrier_boundary[12].h = 32;

        barrier_boundary[13].x = 310;
        barrier_boundary[13].y = 534;
        barrier_boundary[13].w = 32;
        barrier_boundary[13].h = 32;

        barrier_boundary[14].x = 374;
        barrier_boundary[14].y = 534;
        barrier_boundary[14].w = 32;
        barrier_boundary[14].h = 32;

        for (SDL_Rect &barrier : barrier_boundary)
        {
            for (int i = 0; i != barrier.w/brick_width; ++i)
            {
                for (int j = 0; j != barrier.h/brick_height; ++j)
                {
                    SDL_Rect brick;
                    brick.x = barrier.x + i*brick_width;
                    brick.y = barrier.y + j*brick_height;
                    brick.w = brick_width;
                    brick.h = brick_height;
                    bricks.push_back(brick);
                }
            }
        }

        for (int i = 0; i != bricks.size(); ++i)
        {
            Sint16 x = bricks[i].x;
            int k = i;
            for (int j = i; j != bricks.size(); ++j)
            {
                if (bricks[j].x < x)
                {
                    k = j;
                    x = bricks[j].x;
                }
            }

            if (k != i)
            {
                SDL_Rect temp = bricks[i];
                bricks[i] = bricks[k];
                bricks[k] = temp;
            }
        }

        dark_boundary[0].x = 150;
        dark_boundary[0].y = 150;
        dark_boundary[0].w = 416;
        dark_boundary[0].h = 32;

        dark_boundary[1].x = 150;
        dark_boundary[1].y = 150+32;
        dark_boundary[1].w = 32;
        dark_boundary[1].h = 416-64;

        dark_boundary[2].x = 150+64;
        dark_boundary[2].y = 150+32;
        dark_boundary[2].w = 32;
        dark_boundary[2].h = 416-64;

        dark_boundary[3].x = 150+32*4;
        dark_boundary[3].y = 150+32;
        dark_boundary[3].w = 32;
        dark_boundary[3].h = 416-64;

        dark_boundary[4].x = 150+32*5+30;
        dark_boundary[4].y = 182;
        dark_boundary[4].w = 34;
        dark_boundary[4].h = 144-32*2;

        dark_boundary[5].x = 150+32*8;
        dark_boundary[5].y = 182;
        dark_boundary[5].w = 32;
        dark_boundary[5].h = 416-64;

        dark_boundary[6].x = 150+32*10;
        dark_boundary[6].y = 182;
        dark_boundary[6].w = 32;
        dark_boundary[6].h = 416-64;

        dark_boundary[7].x = 150+32*12;
        dark_boundary[7].y = 182;
        dark_boundary[7].w = 32;
        dark_boundary[7].h = 416-64;

        dark_boundary[8].x = 150+32*6;
        dark_boundary[8].y = 182+144-32;
        dark_boundary[8].w = 32;
        dark_boundary[8].h = 32;

        dark_boundary[9].x = 150;
        dark_boundary[9].y = 182+144;
        dark_boundary[9].w = 416;
        dark_boundary[9].h = 32;

        dark_boundary[10].x = 150;
        dark_boundary[10].y = 182+144+32;
        dark_boundary[10].w = 32*5;
        dark_boundary[10].h = 32;

        dark_boundary[11].x = 150+32*8;
        dark_boundary[11].y = 182+144+32;
        dark_boundary[11].w = 32*5;
        dark_boundary[11].h = 32;

        dark_boundary[12].x = 150+32*4;
        dark_boundary[12].y = 182+144+64;
        dark_boundary[12].w = 32*5;
        dark_boundary[12].h = 144-32;

        dark_boundary[13].x = 150;
        dark_boundary[13].y = 150+416-32;
        dark_boundary[13].w = 32*5;
        dark_boundary[13].h = 32;

        //home
        dark_boundary[14].x = 150+32*6;
        dark_boundary[14].y = 150+416-32;
        dark_boundary[14].w = 32;
        dark_boundary[14].h = 32;

        dark_boundary[15].x = 150+32*8;
        dark_boundary[15].y = 150+416-32;
        dark_boundary[15].w = 32*5;
        dark_boundary[15].h = 32;
    }


    const int brick_width = 8;
    const int brick_height = 8;

    std::string brick_path;

    std::vector<SDL_Rect> barrier_boundary{15};
    std::vector<SDL_Rect> bricks;
    std::vector<SDL_Rect> dark_boundary{16};
};


struct Player_Cfg
{
    Player_Cfg()
    {
        player_path[UP] = std::string("images\\tank_player_up.png");
        player_path[DOWN] = std::string("images\\tank_player_down.png");
        player_path[RIGHT] = std::string("images\\tank_player_right.png");
        player_path[LEFT] = std::string("images\\tank_player_left.png");

        live_path = std::string("images\\lives.png");
    }

    const int width = 26; //玩家坦克的大小
    const int height = 26;

    const int start_x = 279;
    const int start_y = 535;

    const float velocity = 2; //玩家坦克的行动速度

    const int lives = 3;

    std::vector<std::string> player_path{4}; //玩家坦克的各种形态的文件位置
    std::string live_path;
};

struct Enemy_Cfg
{
    Enemy_Cfg()
    {
        enemy_path[RIGHT] = std::string("images\\tank_armor1_right.png");
        enemy_path[LEFT] = std::string("images\\tank_armor1_left.png");
        enemy_path[UP] = std::string("images\\tank_armor1_up.png");
        enemy_path[DOWN] = std::string("images\\tank_armor1_down.png");

        enemy_path[RIGHT+4] = std::string("images\\tank_armor2_right.png");
        enemy_path[LEFT+4] = std::string("images\\tank_armor2_left.png");
        enemy_path[UP+4] = std::string("images\\tank_armor2_up.png");
        enemy_path[DOWN+4] = std::string("images\\tank_armor2_down.png");

        enemy_path[RIGHT+8] = std::string("images\\tank_armor3_right.png");
        enemy_path[LEFT+8] = std::string("images\\tank_armor3_left.png");
        enemy_path[UP+8] = std::string("images\\tank_armor3_up.png");
        enemy_path[DOWN+8] = std::string("images\\tank_armor3_down.png");

        explosion_path[0] = std::string("images\\big_explosion_1.png");
        explosion_path[1] = std::string("images\\big_explosion_2.png");
        explosion_path[2] = std::string("images\\big_explosion_3.png");
        explosion_path[3] = std::string("images\\big_explosion_4.png");
        explosion_path[4] = std::string("images\\big_explosion_5.png");


        start_x[LEFT] = 150+64;
        start_y[LEFT] = 246;

        start_x[UP] = 358;
        start_y[UP] = 150;

        start_x[RIGHT] = 534-64;
        start_y[RIGHT] = 246;
    }

    const int width = 26;
    const int height = 26;

    const int exporsion_width = 48;
    const int exporsion_height = 48;

    std::vector<int> start_x{3};
    std::vector<int> start_y{3};

    const float velocity = 2;

    const int lives = 1;
    const int score = 3;

    const int change_direction_interval = 1000;
    const int shoot_interval = 750;
    const int produce_enemy_interval = 4500;

    std::vector<std::string> enemy_path{12};
    std::vector<std::string> explosion_path{5};
};

struct Bullet_Cfg
{
    Bullet_Cfg()
    {
        bullet_path[UP] = std::string("images\\bullet_up.png");
        bullet_path[DOWN] = std::string("images\\bullet_down.png");
        bullet_path[RIGHT] = std::string("images\\bullet_right.png");
        bullet_path[LEFT] = std::string("images\\bullet_left.png");

    }

    const int width = 8;
    const int height = 8;

    const int velocity = 3;

    const int dark_sphere = 10;

    const int lives = 1;

    const int boom_strength = 2;

    std::vector<std::string> bullet_path{4};
};

struct Explosion_Cfg
{
    Explosion_Cfg()
    {
        explosion_path[0] = std::string("images\\big_explosion_1.png");
        explosion_path[1] = std::string("images\\big_explosion_2.png");
        explosion_path[2] = std::string("images\\big_explosion_3.png");
        explosion_path[3] = std::string("images\\big_explosion_4.png");
        explosion_path[4] = std::string("images\\big_explosion_5.png");
    }

    std::vector<std::string> explosion_path{5};
};

struct Over_Cfg
{
    Over_Cfg()
    {
        over_path = std::string("images\\game_over.png");
    }

    std::string over_path;
    const int width = 376;
    const int height = 136;
};

#endif // CFG_H_INCLUDED
