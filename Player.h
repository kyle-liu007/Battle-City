#ifndef PLAYER_H
#define PLAYER_H
#include "Base.h"
#include "Bullet.h"

class Player : public Base
{
    public:
        Player();

        Bullet shoot();

        void handle_event(SDL_Event event);

        void add_score(int enemy_score);

        bool if_shoot = false;
        int score = 0;
    private:
        static Player_Cfg player_cfg;



};

#endif // PLAYER_H
