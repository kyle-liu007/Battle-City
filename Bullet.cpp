#include "Bullet.h"

Bullet_Cfg Bullet::bullet_cfg;

Bullet::Bullet(int x, int y, int dct, std::string s)
{

    box.x = x;
    box.y = y;
    box.w = bullet_cfg.width;
    box.h = bullet_cfg.height;

    lives = bullet_cfg.lives;
    tag = "bullet";
    shooter = s;

    direction = dct;

    if (direction == UP)
    {
        x_vel = 0;
        y_vel = -bullet_cfg.velocity;
    }
    else if (direction == DOWN)
    {
        x_vel = 0;
        y_vel = bullet_cfg.velocity;
    }
    else if (direction == RIGHT)
    {
        x_vel = bullet_cfg.velocity;
        y_vel = 0;
    }
    else
    {
        x_vel = -bullet_cfg.velocity;
        y_vel = 0;
    }
}
