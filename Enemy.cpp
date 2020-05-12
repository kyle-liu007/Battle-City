#include "Enemy.h"

Enemy_Cfg Enemy::enemy_cfg;
int Enemy::number = 0;

Enemy::Enemy()
{
    start_ticks = SDL_GetTicks();

    number += 1;

    lives = enemy_cfg.lives;
    score = enemy_cfg.score;

    box.w = enemy_cfg.width;
    box.h = enemy_cfg.height;

    serial_number = number;
    if (number == 1)
    {
        box.x = enemy_cfg.start_x[LEFT];
        box.y = enemy_cfg.start_y[LEFT];
        x_vel = 0;
        y_vel = enemy_cfg.velocity;
        direction = DOWN;
    }
    else if (number == 2)
    {
        box.x = enemy_cfg.start_x[UP];
        box.y = enemy_cfg.start_y[UP];
        x_vel = enemy_cfg.velocity;
        y_vel = 0;
        direction = RIGHT;
    }
    else
    {
        box.x = enemy_cfg.start_x[RIGHT];
        box.y = enemy_cfg.start_y[RIGHT];
        x_vel = 0;
        y_vel = enemy_cfg.velocity;
        direction = DOWN;
        number = 0;
    }


    tag = "enemy";
}

void Enemy::handle_event()
{
    present_ticks = SDL_GetTicks();

    srand(present_ticks);

    if (present_ticks - start_ticks > shoot_interval)
    {
        if_shoot = true;
        shoot_interval += enemy_cfg.shoot_interval;
    }
    if (present_ticks - start_ticks > change_direction_interval)
    {
        direction = rand()%4;
        if (direction == UP)
        {
            x_vel = 0;
            y_vel = -enemy_cfg.velocity;
        }
        else if (direction == DOWN)
        {
            x_vel = 0;
            y_vel = enemy_cfg.velocity;
        }
        else if (direction == RIGHT)
        {
            x_vel = enemy_cfg.velocity;
            y_vel = 0;
        }
        else
        {
            x_vel = -enemy_cfg.velocity;
            y_vel = 0;
        }
        change_direction_interval += enemy_cfg.change_direction_interval;
    }
}

Bullet Enemy::shoot()
{
    Bullet_Cfg bullet_cfg;

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

void Enemy::explode_show(SDL_Surface *image, SDL_Surface *screen)
{
    SDL_Rect offset;
    offset.x = box.x+enemy_cfg.width/2-enemy_cfg.exporsion_width/2;
    offset.y = box.y+enemy_cfg.height/2-enemy_cfg.exporsion_height/2;

    SDL_BlitSurface(image, nullptr, screen, &offset);
}
