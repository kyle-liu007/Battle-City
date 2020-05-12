#ifndef BULLET_H
#define BULLET_H
#include "Base.h"


class Bullet : public Base
{
    public:
        Bullet(int x, int y, int dct, std::string s);

        void handle_event();

        std::string shooter;
    private:
        static Bullet_Cfg bullet_cfg;

};

#endif // BULLET_H
