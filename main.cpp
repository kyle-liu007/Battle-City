#include <cmath>
#include "cfg.h"
#include "Base.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace std;

Background_Cfg background_cfg;
Start_Cfg start_cfg;
Barrier_Cfg barrier_cfg;
Player_Cfg player_cfg;
Enemy_Cfg enemy_cfg;
Bullet_Cfg bullet_cfg;
Over_Cfg over_cfg;


bool init();
void clear_up();
SDL_Surface *load_image(string file_path);
SDL_Surface *load_str_message(string msg);
SDL_Surface *load_num_message(const int num);
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip=nullptr);
void apply_number(int x, int y, int num, SDL_Surface *destination, SDL_Rect *clip=nullptr);
void set_barrier();
bool start_game();
void handle_event();
void move();
void check_collision();
void clear_loser();
void display();

SDL_Surface *start_image = nullptr;

SDL_Surface *screen = nullptr;
SDL_Surface *enemy_num_msg = nullptr;
SDL_Surface *score_msg = nullptr;
SDL_Surface *tip_msg = nullptr;
SDL_Surface *live_msg = nullptr;
SDL_Surface *home = nullptr;

SDL_Surface *brick = nullptr;
vector<SDL_Surface *> player_image;
SDL_Surface * live_image;
vector<SDL_Surface *> enemy_image;
vector<SDL_Surface *> explosion_image;
vector<SDL_Surface *> bullet_image;
SDL_Surface *over_image;

SDL_Event event;

TTF_Font *font = nullptr;

SDL_Color text_color = {255, 255, 255};

Uint32 start_ticks=0;
Uint32 present_ticks=0;
/*Uint32 frame_control_ticks_1=0;
Uint32 frame_control_ticks_2=0;*/


Base base;
Player player;
vector<Enemy> enemies;
vector<Enemy> boom_enemies;
vector<Bullet> bullets;

int produce_enemy_interval = enemy_cfg.produce_enemy_interval;

int main(int argc, char* argv[])
{
    bool quit = false;
    bool start = false;
    bool over = false;

    if (init() == false)
        return 1;

    for (auto rect : background_cfg.outer)
        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
    for (auto rect : background_cfg.middle)
        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0xAA, 0xAA, 0xAA));
    SDL_FillRect(screen, &background_cfg.inner, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

    apply_surface(background_cfg.tip_x, background_cfg.tip_y, tip_msg, screen);
    apply_surface(start_cfg.start_x, start_cfg.start_y, start_image, screen);

    //frame_control_ticks_1 = SDL_GetTicks();
    while (quit == false)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                quit = true;
            if (event.key.keysym.sym == SDLK_SPACE)
            {
                if (start == false)
                    start = start_game();
            }

            if (start && !over)
            {
                player.handle_event(event);
                if (player.if_shoot)
                {
                    bullets.push_back(player.shoot());
                    player.if_shoot = false;
                }

            }
        }

        if (start && !over)
        {
            handle_event();
            if (present_ticks - start_ticks > background_cfg.game_time)
                over = true;
            move();

            check_collision();
            clear_loser();
            if (!player.check_if_live())
                over = true;

            display();
        }
        if (over)
        {
            SDL_FillRect(screen, &background_cfg.inner, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
            apply_surface(background_cfg.width/2-over_cfg.width/3, background_cfg.height/2-over_cfg.height/2, over_image, screen);
        }

        if (SDL_Flip(screen)==-1)
            return 1;

        /*frame_control_ticks_2 = SDL_GetTicks();
        if (1000/(frame_control_ticks_2-frame_control_ticks_1)>FRAME_PER_SECOND)
        {
            SDL_Delay((Uint32)1000/(Uint32)FRAME_PER_SECOND-(frame_control_ticks_2-frame_control_ticks_1));
        }
        frame_control_ticks_1 = frame_control_ticks_2;*/

        SDL_Delay(12.5);
    }

    clear_up();
    SDL_Quit();

    return 0;
}

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING)==-1 || TTF_Init()==-1)
        return false;

    screen = SDL_SetVideoMode(background_cfg.width, background_cfg.height, 32, SDL_SWSURFACE);

    if (screen == nullptr)
        return false;

    SDL_WM_SetCaption("Battle City", nullptr);

    font = TTF_OpenFont("timesbd.ttf", 28);

    start_image = load_image(start_cfg.start_path);
    enemy_num_msg = load_str_message(string("enemy"));
    score_msg = load_str_message(string("score"));
    tip_msg = load_str_message(string("Press space to start"));
    live_msg = load_str_message(string("live"));

    home = load_image(background_cfg.home_path);
    brick = load_image(barrier_cfg.brick_path);

    for (auto file_path : player_cfg.player_path)
    {
        player_image.push_back(load_image(file_path));
    }

    live_image = load_image(player_cfg.live_path);

    for (auto file_path : enemy_cfg.enemy_path)
    {
        enemy_image.push_back(load_image(file_path));
    }

    for (auto file_path : enemy_cfg.explosion_path)
    {
        explosion_image.push_back(load_image(file_path));
    }

    for (string file_path : bullet_cfg.bullet_path)
    {
        bullet_image.push_back(load_image(file_path));
    }

    over_image = load_image(over_cfg.over_path);


    return true;
}

SDL_Surface *load_image(string file_path)
{
    SDL_Surface *loaded_image = nullptr;
    SDL_Surface *optimized_image = nullptr;

    loaded_image = IMG_Load(file_path.c_str());

    if (loaded_image != nullptr)
    {
        optimized_image = SDL_DisplayFormat(loaded_image);

        SDL_FreeSurface(loaded_image);
    }

    if (optimized_image != nullptr)
    {
        Uint32 colorkey = SDL_MapRGB(optimized_image->format, 0xFF, 0xFF, 0xFF);

        SDL_SetColorKey(optimized_image, SDL_SRCCOLORKEY, colorkey);
    }

    return optimized_image;
}

SDL_Surface *load_str_message(const string msg)
{
    SDL_Surface *message = TTF_RenderText_Solid(font, msg.c_str(), text_color);

    return message;
}

SDL_Surface *load_num_message(const int num)
{
    if (num < 0)
        return nullptr;

    string msg;
    int n = num;
    int i=1;
    do {
        switch (n % 10)
        {
            case 0: msg = "0"+msg; break;
            case 1: msg = "1"+msg; break;
            case 2: msg = "2"+msg; break;
            case 3: msg = "3"+msg; break;
            case 4: msg = "4"+msg; break;
            case 5: msg = "5"+msg; break;
            case 6: msg = "6"+msg; break;
            case 7: msg = "7"+msg; break;
            case 8: msg = "8"+msg; break;
            case 9: msg = "9"+msg; break;
        }
        n = n/pow(10, i);

    }while (num/pow(10, i++)>=1);

    SDL_Surface *num_message = TTF_RenderText_Solid(font, msg.c_str(), text_color);

    return num_message;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, clip, destination, &offset);
}

void apply_number(int x, int y, int num, SDL_Surface *destination, SDL_Rect *clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    offset.w = 28*2;
    offset.h = 28*2;

    SDL_FillRect(screen, &offset, SDL_MapRGB(screen->format, 0xAA, 0xAA, 0xAA));
    SDL_BlitSurface(load_num_message(num), clip, destination, &offset);
}

void set_barrier()
{

    SDL_FillRect(screen, &background_cfg.inner, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

    for (auto box : base.bricks)
        apply_surface(box.x, box.y, brick, screen);
}

bool start_game()
{
    start_ticks = SDL_GetTicks();
    set_barrier();
    apply_surface(background_cfg.live_msg_x, background_cfg.live_msg_y, live_msg, screen);
    for (int i=0; i != player_cfg.lives; ++i)
        apply_surface(background_cfg.player_live_position[i].x,
                        background_cfg.player_live_position[i].y, live_image, screen);

    apply_surface(background_cfg.enemy_num_msg_x,
                background_cfg.enemy_num_msg_y, enemy_num_msg, screen);
    apply_surface(background_cfg.score_msg_x,
                    background_cfg.score_msg_y, score_msg, screen);
    apply_number(background_cfg.time_x, background_cfg.time_y, background_cfg.game_time/1000, screen);

    Enemy enemy_1;
    Enemy enemy_2;
    Enemy enemy_3;

    enemies.push_back(enemy_1);
    enemies.push_back(enemy_2);
    enemies.push_back(enemy_3);

    return true;
}

void handle_event()
{
    present_ticks = SDL_GetTicks();

    if (present_ticks - start_ticks > produce_enemy_interval)
    {
        Enemy enemy;
        enemies.push_back(enemy);
        produce_enemy_interval += enemy_cfg.produce_enemy_interval;
    }
    for (auto &enemy : enemies)
    {
        enemy.handle_event();
        if (enemy.if_shoot)
        {
            bullets.push_back(enemy.shoot());
            enemy.if_shoot = false;
        }
    }
}

void move()
{
    player.move();
    for (auto &enemy : enemies)
        enemy.move();
    for (Bullet &bullet : bullets)
        bullet.move();
}

void check_collision()
{
    for (Bullet &bullet: bullets)
    {
        if (bullet.shooter == "player")
        {
            for (Enemy &enemy : enemies)
            {
                if (bullet.box.x+bullet.box.w >= enemy.box.x && bullet.box.x <= enemy.box.x + enemy.box.w &&
                    bullet.box.y+bullet.box.h >= enemy.box.y && bullet.box.y <= enemy.box.y + enemy.box.h)
                {
                    bullet.update_lives();
                    enemy.update_lives();
                    player.add_score(enemy.score);
                }
            }
        }
        if (bullet.shooter == "enemy")
        {
            if (bullet.box.x+bullet.box.w >= player.box.x && bullet.box.x <= player.box.x + player.box.w &&
            bullet.box.y+bullet.box.h >= player.box.y && bullet.box.y <= player.box.y + player.box.h)
            {
                bullet.update_lives();
                player.update_lives();
            }

            if (bullet.box.x+bullet.box.w >= background_cfg.home.x &&
                bullet.box.x <= background_cfg.home.x + background_cfg.home.w &&
                bullet.box.y+bullet.box.h >= background_cfg.home.y &&
                bullet.box.y <= background_cfg.home.y + background_cfg.home.h)
            {
                player.lives = 0;
            }
        }
    }
}

void clear_loser()
{
    for (auto iter = enemies.begin(); iter != enemies.end(); ++iter)
    {
        if (!(iter->check_if_live()))
        {
            boom_enemies.push_back(*iter);
            iter = enemies.erase(iter);
            --iter;
        }
    }

    for (auto iter = bullets.begin(); iter != bullets.end(); ++iter)
    {
        if (!(iter->check_if_live()))
        {
            iter = bullets.erase(iter);
            --iter;
        }
    }
}

void explosion()
{
    for (auto iter = boom_enemies.begin(); iter != boom_enemies.end(); ++iter)
    {
        if (iter->boom_process<5)
        {
            iter->explode_show(explosion_image[iter->boom_process], screen);
            iter->boom_process += 1;
        }
        else
        {
            for (auto brick_iter = base.bricks.begin(); brick_iter != base.bricks.end(); ++brick_iter)
            {
                if (iter->box.x+enemy_cfg.width/2+enemy_cfg.exporsion_width/2 > brick_iter->x
                     && iter->box.x+enemy_cfg.width/2-enemy_cfg.exporsion_width/2 < brick_iter->x+brick_iter->w &&
                    iter->box.y+enemy_cfg.height/2+enemy_cfg.exporsion_height/2 > brick_iter->y
                     && iter->box.y+enemy_cfg.height/2-enemy_cfg.exporsion_height/2 < brick_iter->y+brick_iter->h)
                {
                    SDL_Rect dark;
                    dark.x = brick_iter->x;
                    dark.y = brick_iter->y;
                    dark.w = brick_iter->w;
                    dark.h = brick_iter->h;
                    base.dark_boundary.push_back(dark);

                    brick_iter = base.bricks.erase(brick_iter)-1;
                    continue;
                }
                if (iter->box.x+enemy_cfg.width/2+enemy_cfg.exporsion_width/2 < brick_iter->x)
                    break;
            }

            iter = boom_enemies.erase(iter)-1;
        }
    }
}

void display()
{
    /*for (auto dark : base.dark_boundary)
    {
        SDL_FillRect(screen, &dark, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
    }*/
    for (auto rect : background_cfg.middle)
        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0xAA, 0xAA, 0xAA));

    apply_surface(background_cfg.live_msg_x, background_cfg.live_msg_y, live_msg, screen);
    for (int i=0; i != player_cfg.lives; ++i)
        apply_surface(background_cfg.player_live_position[i].x,
                        background_cfg.player_live_position[i].y, live_image, screen);

    apply_surface(background_cfg.enemy_num_msg_x,
                background_cfg.enemy_num_msg_y, enemy_num_msg, screen);
    apply_surface(background_cfg.score_msg_x,
                    background_cfg.score_msg_y, score_msg, screen);
    apply_number(background_cfg.time_x, background_cfg.time_y,
                 (background_cfg.game_time-present_ticks+start_ticks)/1000, screen);
    set_barrier();

    apply_surface(background_cfg.home.x, background_cfg.home.y, home, screen);

    for (Bullet &bullet : bullets)
        bullet.show(bullet_image[bullet.direction], screen);

    player.show(player_image[player.direction], screen);

    explosion();

    for (auto &enemy : enemies)
        enemy.show(enemy_image[enemy.direction+4*enemy.serial_number-4], screen);

    if (player.lives < player_cfg.lives)
    {
        for (int i=player_cfg.lives-1; i != player.lives-1; --i)
            SDL_FillRect(screen, &background_cfg.player_live_position[i], SDL_MapRGB(screen->format, 0xAA, 0xAA, 0xAA));
    }

    apply_number(background_cfg.enemy_num_x, background_cfg.enemy_num_y,
                    enemies.size(), screen);
    apply_number(background_cfg.score_num_x, background_cfg.enemy_num_y,
                    player.score, screen);
}

void clear_up()
{
    SDL_FreeSurface(start_image);
    SDL_FreeSurface(enemy_num_msg);
    SDL_FreeSurface(score_msg);
    SDL_FreeSurface(live_image);
    SDL_FreeSurface(tip_msg);
    SDL_FreeSurface(live_msg);
    SDL_FreeSurface(brick);
    SDL_FreeSurface(home);

    for (auto &surface : player_image)
        SDL_FreeSurface(surface);
    for (auto &surface : enemy_image)
        SDL_FreeSurface(surface);
    for (auto &surface : explosion_image)
        SDL_FreeSurface(surface);
    for (auto &surface : bullet_image)
        SDL_FreeSurface(surface);
}
