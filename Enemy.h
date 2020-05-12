#ifndef ENEMY_H
#define ENEMY_H
#include "Base.h"
#include "Bullet.h"

class Enemy : public Base
{
    public:
        Enemy();

        void handle_event();

        Bullet shoot();

        void explode_show(SDL_Surface *image, SDL_Surface *screen);

        int serial_number;
        bool if_shoot = false;
        int score;
        int boom_process=0;
    private:
        static Enemy_Cfg enemy_cfg;

        int change_direction_interval = enemy_cfg.change_direction_interval;
        int shoot_interval = enemy_cfg.shoot_interval;

        static int number;

        Uint32 start_ticks; //对象被创建时计时器的时间
        Uint32 present_ticks; //每次计时时计时器的时间
};

#endif // ENEMY_H
