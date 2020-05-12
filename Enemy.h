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

        Uint32 start_ticks; //���󱻴���ʱ��ʱ����ʱ��
        Uint32 present_ticks; //ÿ�μ�ʱʱ��ʱ����ʱ��
};

#endif // ENEMY_H
