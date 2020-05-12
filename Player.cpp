#include "Player.h"

Player_Cfg Player::player_cfg;

Player::Player()
{
    lives = player_cfg.lives;

    box.x = player_cfg.start_x;
    box.y = player_cfg.start_y;
    box.w = player_cfg.width;
    box.h = player_cfg.height;

    direction = UP;

    tag = "player";
}

void Player::handle_event(SDL_Event event)
{

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_UP: y_vel = -player_cfg.velocity; direction=UP; break;
            case SDLK_DOWN: y_vel = player_cfg.velocity; direction=DOWN; break;
            case SDLK_LEFT: x_vel = -player_cfg.velocity; direction=LEFT; break;
            case SDLK_RIGHT: x_vel = player_cfg.velocity; direction=RIGHT; break;
            default: break;
        }
        if (event.key.keysym.sym == SDLK_SPACE)
            if_shoot = true;
    }
    if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_UP: y_vel = 0; break;
            case SDLK_DOWN: y_vel = 0; break;
            case SDLK_LEFT: x_vel = 0; break;
            case SDLK_RIGHT: x_vel = 0; break;
            default: break;
        }
    }
}

Bullet Player::shoot()
{
    //Bullet bullet(box.x+box.w/2, box.y+box.h/2, direction);
    Bullet_Cfg bullet_cfg;
    /*if (direction == UP)
    {
        Bullet bullet(box.x+box.w/2-bullet_cfg.width/2, box.y-bullet_cfg.height, direction, tag);
        return bullet;
    }
    if (direction == DOWN)
    {
        Bullet bullet(box.x+box.w/2-bullet_cfg.width/2, box.y+box.h+bullet_cfg.height, direction, tag);
        return bullet;
    }
    if (direction == RIGHT)
    {
        Bullet bullet(box.x+box.w+bullet_cfg.width, box.y+box.h/2-bullet_cfg.height/2, direction, tag);
        return bullet;
    }
    if (direction == LEFT)
    {
        Bullet bullet(box.x-bullet_cfg.width, box.y+box.h/2-bullet_cfg.height/2, direction, tag);
        return bullet;
    }*/

    if (direction == UP)
    {
        Bullet bullet(box.x+box.w/2-bullet_cfg.width/2, box.y+box.h/2-bullet_cfg.height/2, direction, tag);
        return bullet;
    }
    if (direction == DOWN)
    {
        Bullet bullet(box.x+box.w/2-bullet_cfg.width/2, box.y+box.h/2-bullet_cfg.height/2, direction, tag);
        return bullet;
    }
    if (direction == RIGHT)
    {
        Bullet bullet(box.x+box.w/2-bullet_cfg.width/2, box.y+box.h/2-bullet_cfg.height/2, direction, tag);
        return bullet;
    }
    if (direction == LEFT)
    {
        Bullet bullet(box.x+box.w/2-bullet_cfg.width/2, box.y+box.h/2-bullet_cfg.height/2, direction, tag);
        return bullet;
    }
}

void Player::add_score(int enemy_score)
{
    score += enemy_score;
}
