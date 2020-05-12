#include "Base.h"

Barrier_Cfg Base::barrier_cfg;
Background_Cfg Base::background_cfg;
std::vector<SDL_Rect> Base::bricks=barrier_cfg.bricks;
std::vector<SDL_Rect> Base::dark_boundary=barrier_cfg.dark_boundary;

Base::Base()
{
    x_vel = 0;
    y_vel = 0;
}

void Base::update_lives()
{
    lives -= 1;
}

bool Base::check_barrier_collison()
{
    bool flag = false;
    /*for (auto barrier : barrier_cfg.barrier_boundary)
    {
        if (box.x+box.w > barrier.x && box.x < barrier.x+barrier.w &&
            box.y+box.h > barrier.y && box.y < barrier.y+barrier.h)
        {
            if_crash_barrier = true;
            break;
        }
    }*/

    for (auto iter = bricks.begin(); iter != bricks.end(); ++iter)
    {
        if (box.x+box.w > iter->x && box.x < iter->x+iter->w &&
            box.y+box.h > iter->y && box.y < iter->y+iter->h)
        {
            flag = true;

            if (tag == "bullet")
            {
                SDL_Rect dark;
                dark.x = iter->x;
                dark.y = iter->y;
                dark.w = iter->w;
                dark.h = iter->h;
                dark_boundary.push_back(dark);

                iter = bricks.erase(iter)-1;
                continue;
            }
            break;
        }
        if (box.x+box.w < iter->x)
            break;
    }

    return flag;
}

void Base::move()
{
    box.x += x_vel;
    box.y += y_vel;

    if (box.x<background_cfg.inner.x || box.x + box.w > background_cfg.inner.x + background_cfg.inner.w
        || check_barrier_collison())
    {
        box.x -= x_vel;
        if (tag == "bullet")
        {
            update_lives();
        }
    }
    if (box.y<background_cfg.inner.y || box.y + box.h > background_cfg.inner.y + background_cfg.inner.h
        || check_barrier_collison())
    {
        box.y -= y_vel;
        if (tag == "bullet")
        {
            update_lives();
        }
    }
}

void Base::show(SDL_Surface *image, SDL_Surface *screen)
{
    SDL_Rect offset;
    offset.x = box.x;
    offset.y = box.y;

    SDL_BlitSurface(image, nullptr, screen, &offset);
}

bool Base::check_if_live()
{
    if (lives <= 0)
        return false;
    return true;
}
