#ifndef BASE_H
#define BASE_H
#include "cfg.h"

/**< ����Ϊ����࣬�ӵ��࣬��������ഴ���Ļ��� */

class Base
{
    public:
        Base();

        void update_lives();

        bool check_barrier_collison(); //����Ƿ�ײ��ǽ

        void move();

        void show(SDL_Surface *, SDL_Surface *);

        bool check_if_live();

        int direction;
        SDL_Rect box; //λ������,�Լ���ײ������
        static std::vector<SDL_Rect> bricks;
        static std::vector<SDL_Rect> dark_boundary;
        int lives; //����

    protected:
        int x_vel;
        int y_vel;

        std::string tag; //����ı�ǩ�����ڱ�ʶ����һ�����

    private:
        static Background_Cfg background_cfg;
        static Barrier_Cfg barrier_cfg;

};

#endif // BASE_H
