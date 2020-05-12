#ifndef BASE_H
#define BASE_H
#include "cfg.h"

/**< 这是为玩家类，子弹类，敌人类等类创建的基类 */

class Base
{
    public:
        Base();

        void update_lives();

        bool check_barrier_collison(); //检查是否撞到墙

        void move();

        void show(SDL_Surface *, SDL_Surface *);

        bool check_if_live();

        int direction;
        SDL_Rect box; //位置坐标,以及碰撞检测盒子
        static std::vector<SDL_Rect> bricks;
        static std::vector<SDL_Rect> dark_boundary;
        int lives; //生命

    protected:
        int x_vel;
        int y_vel;

        std::string tag; //对象的标签，用于标识是哪一类对象

    private:
        static Background_Cfg background_cfg;
        static Barrier_Cfg barrier_cfg;

};

#endif // BASE_H
