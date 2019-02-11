#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>


#define WINDOW_WIDTH (1000)
#define WINDOW_HEIGHT (1000)
#define SPEED (300)

int close_requested = 0;
void blur(int,int);
int main()
{   srand(time(0));
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("Space Rocket",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1000, WINDOW_HEIGHT,0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    SDL_Surface * surface = IMG_Load("resources/hello.png");
    SDL_SetWindowIcon(win, surface);
    SDL_Texture* tex1 = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    int H_S;
    FILE *fp;
    fp = fopen("resources/score.txt","r");                                                                                    // score database handling
    fscanf(fp,"%d",&H_S);
    fclose(fp);
    SDL_Rect dest,obj,obj1,life_1,back,pro[7],sco[5],hco[5],plus;
    SDL_Rect bullet[5];
    SDL_Texture* tex2[5];
    SDL_Texture* sc[5], * hc[5];
    surface = IMG_Load("resources/hello1.png");
    for(int i=0;i<5;i++)
    tex2[i] =SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("resources/hello12.png");
    SDL_Texture* tex12[7];
    for(int i=0;i<7;i++)
    tex12[i] =SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("resources/hello3.1.png");
    SDL_Texture* tex3_1 =SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("resources/hello3.2.png");
    SDL_Texture* tex3_2 =SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("resources/hello2.jpg");
    SDL_Texture* tex4 =SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("resources/hello4.png");
    SDL_Texture* tex5 =SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("resources/hello8.gif");
    SDL_Texture* tex6 =SDL_CreateTextureFromSurface(rend,surface);
    SDL_Texture* tex8 =SDL_CreateTextureFromSurface(rend,surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("resources/hello9.png");
    SDL_Texture* tex7 = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("resources/heart.png");
    
    SDL_Texture* tex9_1= SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("resources/hello10.png");
    SDL_Texture* tex10= SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("resources/hello11.png");
    SDL_Texture* tex11= SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(tex9_1, NULL, NULL, &life_1.w, &life_1.h);
    SDL_QueryTexture(tex10, NULL, NULL, &back.w, &back.h);
    SDL_QueryTexture(tex1, NULL, NULL, &dest.w, &dest.h);
    SDL_QueryTexture(tex6, NULL, NULL, &obj.w, &obj.h);
    SDL_QueryTexture(tex8, NULL, NULL, &obj1.w, &obj1.h);
    for(int i=0;i<5;i++)
    SDL_QueryTexture(tex2[i], NULL, NULL, &bullet[i].w, &bullet[i].h);
    for(int i=0;i<7;i++)
    SDL_QueryTexture(tex12[i], NULL, NULL, &pro[i].w, &pro[i].h);
    for(int i=0;i<7;i++){pro[i].h /=2;pro[i].w /=2;}
    int a[7]={0,0,0,0,0,0,0};
    back.h /=4;
    back.w /=4;
    life_1.w /= 16;
    life_1.h /=16;
    dest.w /= 8;
    dest.h /= 8;
    obj.w /= 8;
    obj.h /= 8;
    obj1.w /= 8;
    obj1.h /= 8;
    for(int i=0;i<5;i++)
    {bullet[i].w /= 9;bullet[i].h /= 16;}
    int d;
    float x_pos = (WINDOW_WIDTH - dest.w) / 2;
    float y_pos = (WINDOW_HEIGHT - dest.h) / 2;
    float x_vel = 0;
    float y_vel = 0;
    float x_b[5];
    float y_b[5];
    int up = 0;int L=1;
    int down = 0;
    int left = 0;
    int right = 0;
    int d1=0;d=0;
    int life =3;
    int t=0,p= 1,score=0,c=0;int clock = -10;
    int d5,d6,i,j,w=0;
    life_1.x=WINDOW_WIDTH-life_1.w;life_1.y=0;

    // animation loop
    while(!close_requested)                                                                         // game start menu
    {  SDL_Event event;
       while (SDL_PollEvent(&event))
            {
            switch (event.type)
            {
            case SDL_QUIT:
                close_requested = 1;p=0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_UP :p=1;break;
                case SDL_SCANCODE_DOWN :p=0;break;
                case SDL_SCANCODE_RETURN :close_requested = 1;break;
                }
             break;
             }
        }
        d5=H_S;
        for(i=4;i>=0;i--)                                                                                            // score display handling mechanism
        {
        d6=d5%10;d5=d5/10;
        switch(d6)
        {
        case 0 : surface = IMG_Load("resources/0.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 1 : surface = IMG_Load("resources/1.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 2 : surface = IMG_Load("resources/2.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 3 : surface = IMG_Load("resources/3.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 4 : surface = IMG_Load("resources/4.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 5 : surface = IMG_Load("resources/5.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 6 : surface = IMG_Load("resources/6.png");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 7 : surface = IMG_Load("resources/7.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 8 : surface = IMG_Load("resources/8.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 9 : surface = IMG_Load("resources/9.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
        }
        }
    for(i=0;i<5;i++)
    {hco[i].w /=3;hco[i].h /=3;hco[i].y=(WINDOW_HEIGHT)-hco[i].h;hco[i].x=(WINDOW_WIDTH/2)-3*hco[i].w+20+(hco[i].w)*i;}
     SDL_RenderClear(rend);
     if(p==1)
     { SDL_RenderCopy(rend, tex3_1, NULL, NULL);}
     if(p==0)
     { SDL_RenderCopy(rend, tex3_2, NULL, NULL);}
    for(i=0;i<5;i++) 
    SDL_RenderCopy(rend, hc[i], NULL, &hco[i]);
    SDL_RenderPresent(rend);
    SDL_Delay(1000/60);
    for(i=0;i<5;i++)
    SDL_DestroyTexture(hc[i]);
     }
    SDL_DestroyTexture(tex3_1);
    SDL_DestroyTexture(tex3_2);
    surface = IMG_Load("resources/hello5.png");
    tex3_1 = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("resources/hello6.jpg");
    tex3_2 = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface); 
    t=0;
    if(p==1)
    {close_requested = 0;
    SDL_RenderCopy(rend, tex4, NULL, NULL);
    SDL_RenderPresent(rend);
    SDL_Delay(2000);
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, tex5, NULL, NULL);
    SDL_RenderPresent(rend);
    SDL_Delay(1000);
    SDL_RenderClear(rend);
    }
    p=0;
    SDL_DestroyTexture(tex4);
    SDL_DestroyTexture(tex5);
    surface = IMG_Load("resources/plus.png");
    tex5 = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(tex5, NULL, NULL, &plus.w, &plus.h);
    plus.w /=2;
    plus.h /=2;
    back.x=0,back.y=0;
    p=-1;
    while (!close_requested)                                                                 // game loop
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))                                                        // Events mangement
        {
            switch (event.type)
            {
            case SDL_QUIT:                                                                     // handling of close button
                close_requested = 1;
                break;
            
            case SDL_KEYDOWN:                                                                 // keyboard API for key pressed
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 1;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 1;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 1;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 1;
                    break;
                case SDL_SCANCODE_X :
                case SDL_SCANCODE_SPACE :
                      t=1;p=p+1;if(p>4){p=0;}
                      break;
                case SDL_SCANCODE_ESCAPE :
                      surface = IMG_Load("resources/blur.png");
                      tex4 =SDL_CreateTextureFromSurface(rend,surface);
                      SDL_FreeSurface(surface);
                      SDL_RenderCopy(rend, tex4, NULL, NULL);
                      SDL_RenderPresent(rend);
                      blur(0,31);up=0;down=0;right=0;left=0;
                      SDL_DestroyTexture(tex4);
                      break;
                }
                break;
            case SDL_KEYUP:                                                                          // keyboard API for key up
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 0;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 0;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 0;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 0;
                    break;
                }
                break;
            }
        }
        d5=score;
        for(i=4;i>=0;i--)                                                                                            // score display handling mechanism
        {
        d6=d5%10;d5=d5/10;
        switch(d6)
        {
        case 0 : surface = IMG_Load("resources/0.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 1 : surface = IMG_Load("resources/1.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 2 : surface = IMG_Load("resources/2.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 3 : surface = IMG_Load("resources/3.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 4 : surface = IMG_Load("resources/4.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 5 : surface = IMG_Load("resources/5.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 6 : surface = IMG_Load("resources/6.png");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 7 : surface = IMG_Load("resources/7.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 8 : surface = IMG_Load("resources/8.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 9 : surface = IMG_Load("resources/9.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
        }
        }

        for(i=0;i<5;i++)
        {sco[i].w /=6;sco[i].h /=6;sco[i].y=0;sco[i].x=(sco[i].w)*i;}

        x_vel = y_vel = 0;                                                       // sets initial vel of space rocket to zero until key is pressed
        if (up && !down) y_vel = -SPEED;                                         // keyboard commands handling for space rocket
        if (down && !up) y_vel = SPEED;
        if (left && !right) x_vel = -SPEED;
        if (right && !left) x_vel = SPEED;

        x_pos += x_vel / 30;                                                     // calculates real time position of space rocket                             
        y_pos += y_vel / 30;
        if(back.x>=WINDOW_WIDTH){back.x=0,back.y=rand()%WINDOW_HEIGHT;}          // calculates initial position of background animation
        back.x=back.x+SPEED/60;                                                 // calculates position of background animation suttle
        back.y=back.y+SPEED/60;

        if (x_pos <= 0) x_pos = 0;                                              // makes boundary for space rocket 
        if (y_pos <= 0) y_pos = 0;
        if (x_pos >= WINDOW_WIDTH - dest.w) x_pos = WINDOW_WIDTH - dest.w;
        if (y_pos >= WINDOW_HEIGHT - dest.h) y_pos = WINDOW_HEIGHT - dest.h;
        
        for(i=0;i<7;i++)                                           // calculates position of things to be protected
        {pro[i].x= 50 + pro[0].w * i;
        pro[i].y= WINDOW_HEIGHT-pro[0].h;}
        dest.y = (int) y_pos;
        dest.x = (int) x_pos;
        
        if(score==clock+1)
        {plus.x=dest.x;
        plus.y=dest.y-25;}
        if(d==0)                                                       // calculates initial random position of objects
        {obj.y=0;
         obj.x=rand()%(WINDOW_WIDTH-obj.w);d=1;}
        if(d1==0)                                                     
        {obj1.y=0;
         obj1.x=rand()%(WINDOW_WIDTH-obj.w);d1=1;}
        obj.y=obj.y+(SPEED/50)*L;                                         // manages position of objects
        obj1.y=obj1.y+(SPEED/50)*L;
        if(t!=0)                                                     // t=1 if bullet is fired and sets bullet initial position to space rocket position
        {
        x_b[p]= dest.x + 28;
        y_b[p]= dest.y;t=0;
        t=0;
        }
        for(i=0;i<5;i++)                                         // calculates bullets real time position
        {bullet[i].y= y_b[i];
        bullet[i].x= x_b[i];
        y_b[i]=y_b[i]-SPEED/50;} 
        SDL_RenderClear(rend);
        if(score<clock+20)
        SDL_RenderCopy(rend, tex5, NULL, &plus);
        SDL_RenderCopy(rend, tex11, NULL, NULL);                     // loads background stars
        SDL_RenderCopy(rend, tex10, NULL, &back);                    // loads background animation suttle
        SDL_RenderCopy(rend, tex9_1, NULL, &life_1);                 // loads life show utility
        for(i=0;i<5;i++) 
        SDL_RenderCopy(rend, sc[i], NULL, &sco[i]);
        SDL_RenderPresent(rend);                 
        SDL_RenderCopy(rend, tex1, NULL, &dest);                     // loads space rocket
        SDL_RenderCopy(rend, tex6, NULL, &obj);                      // loads objects
        SDL_RenderCopy(rend, tex8, NULL, &obj1);
        SDL_RenderPresent(rend);
        for(i=0;i<7;i++)
        {
        if(a[i]==0)                                                                                                                      // shows things to be protected on ther screen
        {SDL_RenderCopy(rend, tex12[i], NULL, &pro[i]);}
        }
        SDL_RenderPresent(rend);
        for(i=0;i<=p;i++)                                                                                                                     // shows bullets on the screen
        {
        SDL_RenderCopy(rend, tex2[i], NULL, &bullet[i]);
        }
        SDL_RenderPresent(rend);

        for(i=0;i<5;i++)                                                                                                                      // bullets hitting objects
        {if((bullet[i].y >= obj.y) && (bullet[i].y <= (obj.y + obj.h)) && (bullet[i].x >= obj.x) && (bullet[i].x <= (obj.x + obj.w)))
        {obj.x=-1000;score=score+100;clock=score;}}
        for(i=0;i<5;i++)
        {if((bullet[i].y >= obj1.y) && (bullet[i].y <= (obj1.y + obj1.h)) && (bullet[i].x >= obj1.x) && (bullet[i].x <= (obj1.x + obj1.w)))
        {obj1.x=-1000;score=score+100;clock=score;}}

        for(j=0;j<7;j++)                                                                                                                      // objects hitting things to be protected
        {if(((obj.y+obj.h) >= pro[j].y) && ((obj.y+obj.h) <= (pro[j].y + pro[j].h)) && (obj.x+obj.w >= pro[j].x) && (obj.x <= (pro[j].x + pro[j].w)) && a[j]==0)
        {obj.x=-1000;a[j]=1;SDL_DestroyTexture(tex12[j]);}
        }
        for(j=0;j<7;j++)
        {if(((obj1.y +obj1.h)>= pro[j].y) && ((obj1.y+obj1.h) <= (pro[j].y + pro[j].h)) && (obj1.x +obj1.w >= pro[j].x) && (obj1.x <= (pro[j].x + pro[j].w)) && a[j]==0)
        {obj1.x=-1000;a[j]=1;SDL_DestroyTexture(tex12[j]);}}

        if((dest.y <= (obj.y +obj.h)) && ((dest.y +dest.h - 10) >= obj.y) && ( dest.x <= (obj.x + obj.w)) && ((dest.x+dest.w) >= obj.x))           // objects hitting space rocket
        {obj.x=-1000;life--;if(life == 0){close_requested = 1;d=-1;}life_1.x +=life_1.w/3;SDL_Delay(500);}
        if((dest.y <= (obj1.y +obj1.h)) && ((dest.y + dest.h - 10) >= obj1.y) && (dest.x <= (obj1.x + obj1.w)) && ((dest.x+dest.w) >= obj1.x))
        {obj1.x=-1000;life--;if(life == 0){close_requested = 1;d=-1;}life_1.x +=life_1.w/3;SDL_Delay(500);}

        score++;                                                                                                                                 // incriment score
                                                                                                                          
        if((score>10000 && L==1)||(score>20000 && L==2) || (score >30000))
        {L++;if(L==2)SDL_RenderCopy(rend, tex3_1, NULL, NULL);if(L==3)SDL_RenderCopy(rend, tex3_2, NULL, NULL);if(L==4){w=1;close_requested =1;d=-1;}SDL_RenderPresent(rend);blur(1,0);up=0;down=0;right=0;left=0;if(L==2)SDL_DestroyTexture(tex3_1);if(L==3)SDL_DestroyTexture(tex3_2);}

        for(i=0;i<5;i++)
        SDL_DestroyTexture(sc[i]);                                                                                                                                 
        if(obj.y>=WINDOW_HEIGHT){d=0;}                                                                                                            // objects regeneration handling
        if(obj1.y>=WINDOW_HEIGHT){d1=0;}
        SDL_Delay(1000/30);c=0;                                                                                                                   // calculating to 30 fps
        for(j=0;j<7;j++)                                                                                                                      // checking for things to be protected alive or not
        if(a[j]==0)c=1;
        if(c==0){close_requested=1;d=-1;}                                                                                                         // game over if protectents are died
    }

    if(d==-1)                                                                                                                                     // game over screen
    {
    if(score>H_S)
    {H_S=score;
    fp = fopen("resources/new.txt","w");
    fprintf(fp,"%d",score);
    remove("resources/score.txt");
    rename("resources/new.txt","resources/score.txt");
    }
    d5=score;
        for(i=4;i>=0;i--)                                                                                            // score display handling mechanism
        {
        d6=d5%10;d5=d5/10;
        switch(d6)
        {
        case 0 : surface = IMG_Load("resources/0.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 1 : surface = IMG_Load("resources/1.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 2 : surface = IMG_Load("resources/2.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 3 : surface = IMG_Load("resources/3.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 4 : surface = IMG_Load("resources/4.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 5 : surface = IMG_Load("resources/5.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 6 : surface = IMG_Load("resources/6.png");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 7 : surface = IMG_Load("resources/7.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 8 : surface = IMG_Load("resources/8.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
       case 9 : surface = IMG_Load("resources/9.jpg");
                 sc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(sc[i], NULL, NULL, &sco[i].w, &sco[i].h);break;
        }
        }
    for(i=0;i<5;i++)
    {sco[i].w /=2;sco[i].h /=2;sco[i].y=(WINDOW_HEIGHT/3)-75;sco[i].x=(WINDOW_WIDTH/3)-90+(sco[i].w)*i;}
        d5=H_S;
        for(i=4;i>=0;i--)                                                                                            // score display handling mechanism
        {
        d6=d5%10;d5=d5/10;
        switch(d6)
        {
        case 0 : surface = IMG_Load("resources/0.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 1 : surface = IMG_Load("resources/1.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 2 : surface = IMG_Load("resources/2.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 3 : surface = IMG_Load("resources/3.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 4 : surface = IMG_Load("resources/4.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 5 : surface = IMG_Load("resources/5.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 6 : surface = IMG_Load("resources/6.png");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 7 : surface = IMG_Load("resources/7.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 8 : surface = IMG_Load("resources/8.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
       case 9 : surface = IMG_Load("resources/9.jpg");
                 hc[i] = SDL_CreateTextureFromSurface(rend, surface);
                 SDL_FreeSurface(surface);
                 SDL_QueryTexture(hc[i], NULL, NULL, &hco[i].w, &hco[i].h);break;
        }
        }
    for(i=0;i<5;i++)
    {hco[i].w /=2;hco[i].h /=2;hco[i].y=(WINDOW_HEIGHT/3)+300;hco[i].x=(WINDOW_WIDTH/3)-90+(hco[i].w)*i;}
    surface = IMG_Load("resources/score.png");
    tex4 = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(rend, tex4, NULL, NULL);
    for(i=0;i<5;i++) 
    SDL_RenderCopy(rend, sc[i], NULL, &sco[i]);
    for(i=0;i<5;i++) 
    SDL_RenderCopy(rend, hc[i], NULL, &hco[i]);
    SDL_RenderPresent(rend);
    SDL_Delay(3000);
    SDL_RenderClear(rend);
    if(w==0)
    {
    SDL_RenderCopy(rend, tex7, NULL, NULL);
    SDL_RenderPresent(rend);
    SDL_Delay(1000);
    }
    else
    {
    SDL_DestroyTexture(tex7);
    surface = IMG_Load("resources/win.png");
    tex7 = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(rend, tex7, NULL, NULL);
    SDL_RenderPresent(rend);
    SDL_Delay(1000);
    }
    }

    for(i=0;i<5;i++)
    SDL_DestroyTexture(sc[i]);
    for(i=0;i<5;i++)
    SDL_DestroyTexture(hc[i]);
    if(L==1)
    {SDL_DestroyTexture(tex3_1);SDL_DestroyTexture(tex3_2);}
    if(L==2)SDL_DestroyTexture(tex3_2);                                                                           
    SDL_DestroyTexture(tex1);
    SDL_DestroyTexture(tex4);
    SDL_DestroyTexture(tex5);
    SDL_DestroyTexture(tex9_1);                                                                                                                 //        destroying textures and window
    for(i=0;i<7;i++)                                                                                                                          
    SDL_DestroyTexture(tex12[i]);
    SDL_DestroyTexture(tex10); 
    SDL_DestroyTexture(tex11);
    SDL_DestroyTexture(tex7);
    SDL_DestroyTexture(tex6);
    SDL_DestroyTexture(tex8);
    for(i=0;i<5;i++)
    SDL_DestroyTexture(tex2[i]);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);                                                                                              
    SDL_Quit();

    return 0;
}
    void blur(int x,int y)                                                                                                                              // function for screen pause
    {
    while (!x ||y<=40)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:                                                                                                                      // handling of close button
                x = 1;close_requested = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                    x = 1;
                    break;
                }
             }
        }
       y++;SDL_Delay(1000/30);
      }                                                                                                                       // calculating to 30 fps
    }
