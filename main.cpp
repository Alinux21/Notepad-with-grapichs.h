#include <iostream>
#include <graphics.h>
#include <conio.h>
#include<stdlib.h>
#include <fstream>
#include <time.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DELETE 83
#ifndef CTRL
#define CTRL(c) ((c) & 037)
#endif


char inputbuf[500][500],inputTitle[100];
FILE *f;
int i,j,z,ok,Notepad,input_pos,x,y=20,stil,marime,status_bar,word_wrap=1,culoare,anticuloare;
bool newButton=false,saveAsButton=false,light=true,disco=false,image=false;

void thick(int x, int y)
{
    setcolor(anticuloare);
    setlinestyle(0,SOLID_LINE,3);

    line(x,y,x+3,y+5);
    line(x+3,y+5,x+16,y-5);
    setlinestyle(0,0,0);
}

void toolbar()
{
    settextstyle(0,0,0);
    setfillstyle(SOLID_LINE,BLACK);
    outtextxy(5,0,"File");
    line(6,14,11,14);

    outtextxy(55,0,"Edit");
    line(55,14,60,14);

    outtextxy(110,0,"Format");
    line(110,14,115,14);

    outtextxy(180,0,"View");
    line(180,14,185,14);

    outtextxy(235,0,"Help");
    line(235,14,245,14);

    line(0,18,800,18);
}



void actualizare()
{
    setbkcolor(culoare);
    setcolor(anticuloare);
    int x=0,y;
    cleardevice();

         if(image==true)
            {readimagefile("nature.jpg",0,0,800,600);}
    toolbar();
    settextstyle(stil,0,marime);
    for(int i1=0; i1<=50; i1++)
    {
        y=i1*20+20;
        outtextxy(x,y,inputbuf[i1]);
    }

    if(status_bar)
    {
        int x1=getmaxx();
        int y1=getmaxy();

        char buff[80];

        memset(buff,0,80);
        sprintf(buff, "Ln %d Col %d",i+1,j+1);
        outtextxy(x1-130,y1-20,buff);

        line(0,y1-20,x1,y1-20);

    }

}

void refresh()
{


    inputbuf[i][j]='|';
    swapbuffers();
    actualizare();

}
int getEOL(char s[256])
{
    int j=0;
    while(s[j]!=0)
        j++;

    return j;

}
bool lastLine(int i)
{
    for(int i1=i; i1<50; i1++)
        if(inputbuf[i1][1]!=0)
            return 0;

    return 1;

}
void golire()
{
    for(int i=0; i<100; i++)
    {
        for(int j=0; j<100; j++)
            inputbuf[i][j]='\0';
    }
}


void nou()
{
    outtextxy(325,495,"All files");
    rectangle(320,490,700,520);
    int a4,b4;
    while(!ok)
    {
        getmouseclick(WM_LBUTTONDOWN,a4,b4);
        if((a4>=320&&a4<=700)&&(b4>490&&b4<520))
        {
            setcolor(0);
            rectangle(320,490,700,520);
            outtextxy(325,495,"All files");
            setcolor(15);
            outtextxy(330,470,"All files");
            rectangle(320,465,700,490);
            ok=1;
            setcolor(0);
            rectangle(320,490,700,520);
            rectangle(325,470,695,485);
            setcolor(15);
        }
        rectangle(320,465,700,490);
        if(ok==1)
            break;
    }
    //save button
    rectangle(750,550,790,580);
    outtextxy(755,555,"Save");
    int a5,b5;
    while(1)
    {
        getmouseclick(WM_LBUTTONDOWN,a5,b5);
        if((a5>=750&&a5<=790)&&(b5>=550&&b5<=590))
            //save
        {
            setcurrentwindow(Notepad);
            f=fopen("Notepad.txt","w+");
            //whichFile();
            inputbuf[i][j]=0;
            for(int a=0; a<=i; a++)
                fprintf(f,"%s\n",inputbuf[a]);
            fclose(f);
            closegraph();

        }
    }

}

void saveTitle(int x, int y)
{
    do
    {
        inputTitle[input_pos]='|';
        outtextxy(x, y, inputTitle);
        char c = getch();
        switch (c)
        {
        case 8:
            /* backspace */
            if (input_pos)
            {
                if (inputTitle[input_pos + 1] == 0)
                {
                    inputTitle[input_pos + 2] = ' ';
                    inputTitle[input_pos + 1] = ' ';
                }

                inputTitle[input_pos] = ' ';
                input_pos--;
                inputTitle[input_pos] = ' ';
            }
            break;
        case 9:
            /*tab*/
            inputTitle[input_pos++]='.';
            inputTitle[input_pos++]='t';
            inputTitle[input_pos++]='x';
            inputTitle[input_pos++]='t';
            inputTitle[input_pos]='\0';
            outtextxy(x,y,inputTitle);
            rectangle(325,470,695,485);
            nou();
            break;
        default:
            if (input_pos < 100 - 1 && c >= ' ' && c <= '~')
            {
                inputTitle[input_pos] = c;
                input_pos++;
            }
        }
    }
    while (1);
}

int main();
void save()
{
    if(saveAsButton==false)
    {
        initwindow(400, 50, "Alert", 400, 300);
        outtextxy(130, 0, "Do you want to save?");
        rectangle(50, 20, 100, 40);
        //background();
        outtextxy(60, 23, "YES");
        //background();
        rectangle(350, 20, 300, 40);
        outtextxy(315, 23, "NO");

        int s1, s2;
        while (1)
        {
            getmouseclick(WM_LBUTTONDOWN, s1, s2);
            if ((s1 >= 50 && s1 <= 100) && (s2 >= 20 && s2 <= 40))
            {
                initwindow(800, 600, "Save as");
                line(200, 0, 200, 600);
                line(201, 0, 201, 600);
                line(201, 400, 800, 400);
                line(201, 401, 800, 401);
                //arbore fisiere
                rectangle(30,50,180,75);
                outtextxy(35,55,"Codeblocks");
                rectangle(30,130,180,155);
                outtextxy(35,135,"IntroP");
                rectangle(30,225,180,250);
                outtextxy(35,230,"notepad");
                //sageti
                line(40,80,40,120);
                line(35,110,40,120);
                line(45,110,40,120);

                line(60,160,60,220);
                line(55,210,60,220);
                line(65,210,60,220);
                //butoane
                outtextxy(205, 420, "  FILE  NAME");
                rectangle(320, 415, 700, 440);
                outtextxy(205,460,"  SAVE AS TYPE");
                rectangle(320,465,700,490);
                int a1,a2;
                bool ok=0;
                while(1)
                {
                    getmouseclick(WM_LBUTTONDOWN, a1, a2);
                    if((a1>=320&&a1<=700)&&(a2>=415&&a2<=440))
                        saveTitle(325,420);
                    if((a1>=320&&a1<=700)&&(a2>=465&&a2<=480))
                    {
                        rectangle(320,490,700,520);
                        outtextxy(325,495,"All files");
                        int a4,b4;
                        while(!ok)
                        {
                            getmouseclick(WM_LBUTTONDOWN,a4,b4);
                            if((a4>=320&&a4<=700)&&(b4>490&&b4<520))
                            {
                                setcolor(0);
                                rectangle(320,490,700,520);
                                outtextxy(325,495,"All files");
                                setcolor(15);
                                outtextxy(325,470,"All files");
                                rectangle(320,465,700,490);
                                ok=1;
                            }
                        }
                    }
                    if(ok==1)
                        break;
                }
                //save button
                rectangle(750,550,790,580);
                outtextxy(755,555,"Save");
                int a5,b5;
                while(1)
                {
                    getmouseclick(WM_LBUTTONDOWN,a5,b5);
                    if((a5>=750&&a5<=790)&&(b5>=550&&b5<=590))
                        //save
                    {
                        setcurrentwindow(Notepad);
                        f=fopen("notepad.txt","w+");
                        //whichFile();
                        inputbuf[i][j]=0;
                        for(int a=0; a<=i; a++)
                            fprintf(f,"%s\n",inputbuf[a]);
                        fclose(f);
                        closegraph();

                    }
                }
            }
            else if ((s1 >= 300 && s1 <= 350) && (s2 >= 20 && s2 <= 40))
                if(newButton==false)
                    closegraph();
                else
                    main();
        }

    }
    else
    {
        initwindow(800, 600, "Save as");
        line(200, 0, 200, 600);
        line(201, 0, 201, 600);
        line(201, 400, 800, 400);
        line(201, 401, 800, 401);
        //arbore fisiere
        rectangle(30,50,180,75);
        outtextxy(35,55,"Codeblocks");
        rectangle(30,130,180,155);
        outtextxy(35,135,"IntroP");
        rectangle(30,225,180,250);
        outtextxy(35,230,"notepad");
        //sageti
        line(40,80,40,120);
        line(35,110,40,120);
        line(45,110,40,120);

        line(60,160,60,220);
        line(55,210,60,220);
        line(65,210,60,220);
        //butoane
        outtextxy(205, 420, "  FILE  NAME");
        rectangle(320, 415, 700, 440);
        outtextxy(205,460,"  SAVE AS TYPE");
        rectangle(320,465,700,490);
        int a1,a2;
        bool ok=0;
        while(1)
        {
            getmouseclick(WM_LBUTTONDOWN, a1, a2);
            if((a1>=320&&a1<=700)&&(a2>=415&&a2<=440))
                saveTitle(325,420);
            if((a1>=320&&a1<=700)&&(a2>=465&&a2<=480))
            {
                rectangle(320,490,700,520);
                outtextxy(325,495,"All files");
                int a4,b4;
                while(!ok)
                {
                    getmouseclick(WM_LBUTTONDOWN,a4,b4);

                    if((a4>=320&&a4<=700)&&(b4>490&&b4<520))
                    {
                        setcolor(0);
                        rectangle(320,490,700,520);
                        outtextxy(325,495,"All files");
                        setcolor(15);
                        outtextxy(325,470,"All files");
                        rectangle(320,465,700,490);
                        ok=1;
                    }
                }
            }
            if(ok==1)
                break;
        }
        //save button
        rectangle(750,550,790,580);
        outtextxy(755,555,"Save");
        int a5,b5;
        while(1)
        {
            getmouseclick(WM_LBUTTONDOWN,a5,b5);
            if((a5>=750&&a5<=790)&&(b5>=550&&b5<=590))
                //save
            {
                setcurrentwindow(Notepad);
                f=fopen("notepad.txt","w+");
                //whichFile();
                inputbuf[i][j]=0;
                for(int a=0; a<=i; a++)
                    fprintf(f,"%s\n",inputbuf[a]);
                fclose(f);
                closegraph();

            }
        }

    }
}

void notepad();

void info()
{
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    rectangle(372,32,640,300);
    floodfill(373,36,BLACK);
    setbkcolor(LIGHTGRAY);
    int y1=47;
    outtextxy(378,y1,"Acest proiect a fost");
    outtextxy(377,y1+20,"realizat de catre Alin");
    outtextxy(377,y1+40,"sub indrumarea");
    outtextxy(377,y1+60,"domnului Bogdan Patrut.");

    setcolor(YELLOW);

    // creating yellow circle
    circle(500, 200, 40);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(500, 200, YELLOW);

    // black
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);

    // eyes
    fillellipse(510, 185, 2, 6);
    fillellipse(490, 185, 2, 6);

    // mouth
    ellipse(500, 200, 205, 335, 20, 9);
    ellipse(500, 200, 205, 335, 20, 10);
    ellipse(500, 200, 205, 335, 20, 11);
    /*//////////////////////////////*/swapbuffers();
}

void help()
{
    cleardevice();
    toolbar();

    settextstyle(0,0,0);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    rectangle(235,20,395,45);
    if(anticuloare==0)
        floodfill(236,21,BLACK);
    if(anticuloare==15)
        floodfill(236,21,WHITE);
    setcolor(WHITE);
    line(255,20,255,45);
    setcolor(BLACK);
    setbkcolor(LIGHTGRAY);
    outtextxy(260,25,"About notepad");

    int a,y;
    /*//////////////////////////////*/swapbuffers();
    while(1)
    {
        getmouseclick(WM_LBUTTONDOWN,a,y);

        if(y>45||(y>18&&a<235||a>395))
            notepad();

        if(a>=215&&a<=370)
            if(y>=20&&y<=40)
                //About
            {

                info();

            }

    }
}

void view()
{
    cleardevice();
    toolbar();
    settextstyle(0,0,0);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    rectangle(180,20,315,45);
    if(anticuloare==0)
        floodfill(181,21,BLACK);
    if(anticuloare==15)
        floodfill(181,21,WHITE);
    setcolor(WHITE);
    line(205,20,205,45);
    setcolor(BLACK);
    setbkcolor(LIGHTGRAY);
    if(status_bar)
        thick(184,30);
    outtextxy(210,25,"Status bar");
    setcolor(WHITE);
    setcolor(BLACK);

    int a,b;
    /*//////////////////////////////*/swapbuffers();
    while(1)
    {
        getmouseclick(WM_LBUTTONDOWN,a,b);
        if(b>45||(b>18&&a<180||a>315))
            notepad();
        if(a>=160&&a<=280)
        {
            if(b>=20&&b<=40)
                //Status bar
            {
                status_bar=!status_bar;
                notepad();
            }

        }
    }
}

void alegereMarime()
{
    switch(stil)
    {
    case 0:
        marime=2;
        break;
    case 1:
        marime=2;
        break;
    case 2:
        marime=15;
        break;
    case 3:
        marime=15;
        break;
    }
    notepad();
}

void selectFont()
{
    int a=-1,b=-1,latime=30;
    while(a==-1)
    {
        getmouseclick(WM_LBUTTONDOWN,a,b);
        if(b>350||a>700||b>130&&a<500||b>65&&a<180||a<110&&b>20)
            notepad();

        else if(a>=472&&a<=700)
            if(b<=20+latime)
                stil=0;
            else if(b<=20+2*latime)
                stil=1;
            else if(b<=20+3*latime)
                stil=2;
            else if(b<=20+4*latime)
                stil=3;
            else if(b<=20+5*latime)
                stil=4;
            else if(b<=20+6*latime)
                stil=5;
            else if(b<=20+7*latime)
                stil=6;
            else if(b<=20+8*latime)
                stil=7;
            else if(b<=20+9*latime)
                stil=8;
            else if(b<=20+10*latime)
                stil=9;
            else if(b<=20+11*latime)
                stil=10;

    }
    alegereMarime();
}

void fonts()
{
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    rectangle(502,20,700,350);
    floodfill(503,21,BLACK);
    setcolor(WHITE);

    for(int i=1; i<=11; i++)
    {
        setcolor(WHITE);
        if(i!=11)
            line(502,20+30*i,700,20+30*i);
        char nume_font[100];
        switch(i)
        {
        case 1:
            strcpy(nume_font,"DEFAULT");
            break;
        case 2:
            strcpy(nume_font,"TRIPLEX");
            break;
        case 3:
            strcpy(nume_font,"SMALL");
            break;
        case 4:

            strcpy(nume_font,"SANS SERIF");
            break;
        case 5:
            strcpy(nume_font,"GOTHIC");
            break;
        case 6:
            strcpy(nume_font,"SCRIPT");
            break;
        case 7:
            strcpy(nume_font,"SIMPLEX");
            break;
        case 8:
            strcpy(nume_font,"TRIPLEX SCR");

            break;
        case 9:
            strcpy(nume_font,"COMPLEX");
            break;
        case 10:
            strcpy(nume_font,"EUROPEAN");
            break;
        case 11:
            strcpy(nume_font,"BOLD");
            break;
        }
        setcolor(BLACK);
        outtextxy(512,30*i,nume_font);

    }
    /*//////////////////////////////*/swapbuffers();
    selectFont();

}
void format()
{
    cleardevice();
    toolbar();
    //menu bar
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    rectangle(110,20,280,65);
    if(anticuloare==0)
        floodfill(111,21,BLACK);
    if(anticuloare==15)
        floodfill(111,21,WHITE);
    setcolor(WHITE);
    line(135,20,135,65);
    //word wrap

    setbkcolor(LIGHTGRAY);
    if(word_wrap)
    {
        thick(114,30);
    }
    setcolor(BLACK);
    outtextxy(145,25,"Word Wrap");
    //format
    outtextxy(145,45,"Format...");
    setcolor(WHITE);

    //Cancel
    setcolor(BLACK);


    int a,b;
    /*//////////////////////////////*/swapbuffers();
    while(1)
    {
        getmouseclick(WM_LBUTTONDOWN,a,b);
        if((b>18)&&(a<110||a>280||b>65))
            notepad();
        if(b>=20&&b<=40)
            //word wrap
        {
            word_wrap=!word_wrap;
            notepad();
        }
        if(b>40&&b<=60)
            //format
        {
            /*//////////////////////////////*/swapbuffers();
            setfillstyle(SOLID_FILL,LIGHTGRAY);
            rectangle(282,52,500,130);
            floodfill(283,53,BLACK);
            setcolor(WHITE);
            line(307,52,307,130);
            setcolor(BLACK);
            outtextxy(313,57,"Fonts...");
            outtextxy(313,77,"Size");
            settextstyle(0,0,4);
            outtextxy(313,100,"Aa");
            rectangle(309,100,380,125);
            settextstyle(0,0,3);
            outtextxy(390,105,"Aa");
            rectangle(386,105,440,125);
            settextstyle(0,0,2);
            outtextxy(450,110,"Aa");
            rectangle(446,110,480,125);
            int c,d;
            /*//////////////////////////////*/swapbuffers();
            while(1)
            {
                getmouseclick(WM_LBUTTONDOWN,c,d);

                if((c<282&&d>65)||(d>130)||(c>500)||(c<500&&c>282&&d<52))
                {
                    notepad();
                }
                if(c>=309&&c<=380&&d>=100&&d<=125)
                    //size big
                {
                    marime=6;
                    notepad();
                }
                if(c>=386&&c<=440&&d>=105&&d<=125)
                {
                    marime=4;
                    notepad();
                }
                if(c>=446&&c<=480&&d>=110&&d<=125)
                {
                    marime=1;
                    notepad();
                }

                if(c>=252&&c<=470)
                    if(d>=55&&d<=75)
                    {

                        /*//////////////////////////////*/swapbuffers();
                        fonts();

                    }

            }
        }
        if(b>60&&b<=90)
//cancel
        {
            notepad();
        }

    }
}

void time_date()
{
    time_t rawtime;
    char s[256];
    time (&rawtime);
    struct tm  *timeinfo = localtime (&rawtime);
    strftime(s, sizeof(s)-1, "%H:%M %d.%m.%Y", timeinfo);

    char s1[100];
    int si1,aux1=j;
    for(si1=0; si1<=getEOL(inputbuf[i])-j+1; si1++)
    {
        s1[si1]=inputbuf[i][aux1+1];
        aux1++;
    }
    s1[si1++]=0;
    for(int aux=0; aux<strlen(s); aux++)
    {
        int z=getEOL(inputbuf[i]);
        z++;
        inputbuf[i][z]=' ';
        for(int i1=z; i1>j; i1--)
            swap(inputbuf[i][i1],inputbuf[i][i1-1]);

        inputbuf[i][j]=s[aux];
        j++;
    }
}

void selectColor(int latime)
{

    int a=-1,b=-1;

    while(a==-1)
    {
        getmouseclick(WM_LBUTTONDOWN,a,b);
        //292,52,470,375
        if(b>375||a>470)
            notepad();
        else if(a>=292&&a<=470)
            if(b<=22+2*latime)
            {

                culoare=1;
                anticuloare=15;
            }
            else if(b<=20+3*latime)
            {
                culoare=2;
                anticuloare=0;
            }
            else if(b<=20+4*latime)
            {
                culoare=3;
                anticuloare=0;
            }
            else if(b<=20+5*latime)
            {
                culoare=5;
                anticuloare=15;
            }
            else if(b<=20+6*latime)
            {
                culoare=6;
                anticuloare=15;
            }
            else if(b<=20+7*latime)
            {
                culoare=9;
                anticuloare=0;
            }
            else if(b<=20+8*latime)
            {
                culoare=10;
                anticuloare=0;
            }
            else if(b<=20+9*latime)
            {
                culoare=13;
                anticuloare=0;
            }
            else if(b<=20+10*latime)
            {
                culoare=14;
                anticuloare=0;
            }
            else if(b<=20+11*latime)
            {
                culoare=4;
                anticuloare=0;
            }
            else if(b<=20+12*latime)
            {
                culoare=12;
                anticuloare=0;
            }

    }
    swapbuffers();
    notepad();
}

void Background()
{

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    if(light==false)
    setcolor(WHITE);

    rectangle(177,52,290,115);

   floodfill(178,53,BLACK);
   if(light==false)
    floodfill(178,53,WHITE);


    setcolor(WHITE);
    line(202,53,202,114);
    setcolor(BLACK);
    setbkcolor(LIGHTGRAY);
    outtextxy(207,57,"Theme");
    outtextxy(207,77,"Colors");
    outtextxy(207,97,"Image");




    swapbuffers();
    int a,b;

    while(1)
    {
        getmouseclick(WM_LBUTTONDOWN,a,b);
        if(a>290||b>115)
            notepad();

        if(a>=177&&a<=290)
        {
            swapbuffers();
            if(b>=52&&b<=70)
            {

                //theme
                setfillstyle(SOLID_FILL,LIGHTGRAY);
                if(light==false)
                setcolor(WHITE);

                rectangle(292,52,590,75);
                floodfill(293,53,BLACK);
                setcolor(BLACK);

                outtextxy(297,57,"Light");
                outtextxy(390,57,"Dark");
                outtextxy(490,57,"Disco");

                if(light==true)
                    thick(355,65);
                else if(disco!=true)
                    thick(450,65);
                else
                    thick(550,65);
                int a,b;
                swapbuffers();

                while(1)
                {
                    getmouseclick(WM_LBUTTONDOWN,a,b);
                    if(a>590||(b>75&&a>290)||b>115)
                        notepad();
                    if(b>=52&&b<=75)
                    {

                        if(a>=292&&a<=335)
                            //light
                        {
                            light=true;
                            thick(355,65);

                            setcolor(LIGHTGRAY);
                            thick(450,65);
                            culoare=15;
                            anticuloare=0;

                            notepad();
                            swapbuffers();
                        }
                        if(a>335&&a<=470)
                            //dark
                        {
                            light=false;
                            thick(450,65);
                            culoare=0;
                            anticuloare=15;
                            setcolor(LIGHTGRAY);
                            thick(355,65);
                            swapbuffers();
                            notepad();
                        }
                        if(a>470&&a<590)
                        {
                            thick(570,65);
                            setcolor(LIGHTGRAY);
                            thick(355,65);
                            thick(450,65);
                            light=false;
                            disco=!disco;
                            swapbuffers();
                            notepad();
                        }
                    }
                }
                swapbuffers();
            }
            if(b>70&&b<=90)
                //colors
            {

                setfillstyle(SOLID_FILL,LIGHTGRAY);

                if(light==false)
                setcolor(WHITE);

                rectangle(302,52,470,375);
                floodfill(303,53,BLACK);
                setcolor(WHITE);

                for(int l=1; l<=11; l++)
                {
                    if(l!=11)
                        setcolor(WHITE);
                    else
                        setcolor(culoare);
                    line(292,52+30*l,470,52+30*l);
                    char nume_font[100];
                    switch(l)
                    {
                    case 1:
                        strcpy(nume_font,"Blue");
                        break;
                    case 2:
                        strcpy(nume_font,"Green");

                        break;
                    case 3:
                        strcpy(nume_font,"Cyan");

                        break;
                    case 4:

                        strcpy(nume_font,"Magenta");

                        break;
                    case 5:
                        strcpy(nume_font,"Brown");

                        break;
                    case 6:
                        strcpy(nume_font,"Light Blue");

                        break;
                    case 7:
                        strcpy(nume_font,"Light Green");

                        break;
                    case 8:
                        strcpy(nume_font,"Light Magenta");


                        break;
                    case 9:
                        strcpy(nume_font,"Yellow");

                        break;
                    case 10:
                        strcpy(nume_font,"Red");

                        break;
                    case 11:
                        strcpy(nume_font,"Light Red");

                        break;
                    }
                    setcolor(BLACK);
                    outtextxy(297,25+30*l,nume_font);
                }
                swapbuffers();
                selectColor(30);
            }
            if(b>90&&b<=115)
                //image
            {
                image=!image;
                readimagefile("nature.jpg",0,0,800,600);
                swapbuffers();
                notepad();
            }

            }
    }
}

void edit()
{
    cleardevice();
    toolbar();
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    rectangle(55,20,175,70);

    if(anticuloare==0)
        floodfill(56,21,BLACK);
    if(anticuloare==15)
        floodfill(56,21,WHITE);
    setcolor(WHITE);
    line(75,20,75,70);

    setcolor(BLACK);
    setbkcolor(LIGHTGRAY);
    outtextxy(80,25,"Time/Date");

    outtextxy(77,45,"Background");
    int a,b;
    /*//////////////////////////////*/swapbuffers();
    while(1)
    {
        getmouseclick(WM_LBUTTONDOWN,a,b);

        if(b>70||a>175||b<70&&b>14&&a<55)
            //cancel
        {
            notepad();
        }

        if(a>=55&&a<=170)
        {
            if(b>=20&&b<=40)
                //time/date
            {
                time_date();
                notepad();
            }
            if(b>40&&b<=70)
            {
                swapbuffers();
                Background();

            }
        }
    }
}

void new_file()
{
    newButton=true;
    golire();
    i=0;
    j=0;
    y=20;
    cleardevice();
    notepad();
}
void save_AS()
{
    saveAsButton=true;
    save();
}

void file()
{

    cleardevice();

    toolbar();

    //menu bar
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    rectangle(5,20,210,125);
    if(anticuloare==0)
        floodfill(6,21,BLACK);
    if(anticuloare==15)
        floodfill(6,21,WHITE);
    setcolor(WHITE);
    line(30,20,30,125);
    //new
    setcolor(BLACK);
    setbkcolor(LIGHTGRAY);
    outtextxy(40,25,"New       CTRL+N");
    //save
    outtextxy(40,45,"Save");
    //save as
    outtextxy(40,65,"Save As...CTRL+S");
    //separator
    setcolor(WHITE);
    line(30,90,210,90);
    //Exit
    setcolor(BLACK);
    outtextxy(40,100,"Exit         ESC");
    /*//back
    setcolor(WHITE);
    line(30,125,190,125);
    setcolor(BLACK);
    // outtextxy(40,130,"Cancel");*/
    int a,b;
    /*//////////////////////////////*/swapbuffers();
    while(1)
    {
        getmouseclick(WM_LBUTTONDOWN,a,b);

        if(b>125||a>190)
            //cancel
        {
            notepad();
        }
        if(b>=20&&b<=40)
            //new
        {
            new_file();
        }
        if(b>40&&b<=60)
            //save
        {
            notepad();
        }
        if(b>60&&b<=80)
            //save as
        {
            save_AS();

        }
        if(b>80&&b<=125)
            //exit
        {
            saveAsButton=false;
            newButton=false;
            save();
        }



    }
}


void toolbarInterpret()
{


    int a,b;
    while(GetAsyncKeyState(VK_LBUTTON))
    {
        getmouseclick(WM_LBUTTONDOWN,a,b);
        if(a>=0 && a<=40)
        {

            file();


        }
        if(a>=45&& a<=100)
        {

            edit();
        }
        if(a>=105&&a<=160)
        {

            format();
        }
        if(a>170&&a<=225)
        {

            view();
        }
        if(a>230&&a<=260)
        {

            help();
        }


    }
    notepad();
}


int tab(char s[256],int pos)
{
    int cnt=0;
    for( int j=pos; j>=pos-18; j--)
        if(s[j]==' ')
            cnt++;

    if (cnt==18)
        return 1;

    return 0;
}

void notepad()
{
    int anterior;

    setbkcolor(culoare);
    setcolor(anticuloare);

    do
    {

        actualizare();



        char c;
        inputbuf[i][j]='|';
        outtextxy(x,y,inputbuf[i]);

        refresh();


        while(!kbhit())
        {
            POINT pozitieMouse;
            GetCursorPos(&pozitieMouse);
            if(pozitieMouse.y<=50)
            {

                toolbarInterpret();

            }
        }


        c=getch();


        if(disco==true)
        {
            srand(time(0));

            culoare=rand()%16;
            while(anterior==culoare)
                culoare=rand()%16;
            if(culoare==1||culoare==5||culoare==6)
                anticuloare=15;
            else if(culoare==0)
            {
                culoare=12;
                anticuloare=0;
            }
            else if(culoare==15)
            {
                culoare=3;
                anticuloare=0;
            }
            else
                anticuloare=0;

        }
        anterior=culoare;

        swapbuffers();


        switch (c)
        {
        case 0:
            switch(getch())
            {
            case KEY_LEFT:
                if(i==0&&j==0)
                { }
                else if(j==0)
                {
                    strcpy(inputbuf[i]+j,inputbuf[i]+j+1);
                    for(int x=0; x<800; x++)
                    {
                        if(inputbuf[i-1][x]==0)
                        {
                            j=x;
                            break;
                        }
                    }

                    z=j;
                    y=y-20;
                    i--;
                    for(int i1=j; i1<100; i1++)
                        inputbuf[i][i1]=0;
                    actualizare();
                }
                else
                {
                    swap(inputbuf[i][j-1],inputbuf[i][j]);
                    outtextxy(x,y,inputbuf[i]);
                    j--;
                }
                break;

            case KEY_RIGHT:
                if(inputbuf[0][0]==0||lastLine(i))
                {}
                else if(inputbuf[i][j+1]==0)
                {
                    inputbuf[i][j]=0;
                    j=0;
                    i++;
                    int len;
                    len=getEOL(inputbuf[i]);
                    len++;
                    inputbuf[i][len]=' ';
                    for(int i1=len; i1>j; i1--)
                        swap(inputbuf[i][i1],inputbuf[i][i1-1]);

                    y=y+20;
                    ok=0;
                    actualizare();

                }
                else
                {
                    swap(inputbuf[i][j],inputbuf[i][j+1]);
                    outtextxy(x,y,inputbuf[i]);
                    j++;
                }
                break;

            case KEY_UP:
                if(i==0)
                {}
                else  if(inputbuf[i-1][j]==0&&inputbuf[i-1][0]!=0)
                {
                    int lung=getEOL(inputbuf[i-1]);
                    strcpy(inputbuf[i]+j,inputbuf[i]+j+1);
                    j=lung;
                    inputbuf[i-1][lung--]=' ';
                    i--;
                    y=y-20;
                    actualizare();
                }

                else
                {
                    int len;
                    len=getEOL(inputbuf[i-1]);
                    len++;
                    inputbuf[i-1][len]=' ';
                    for(int i1=len; i1>j; i1--)
                        swap(inputbuf[i-1][i1],inputbuf[i-1][i1-1]);
                    strcpy(inputbuf[i]+j,inputbuf[i]+j+1);
                    i--;
                    y=y-20;
                    actualizare();
                }
                break;

            case KEY_DOWN:
                if(lastLine(i))
                {}
                else if(inputbuf[i+1][j]==0)
                {
                    int lung=getEOL(inputbuf[i+1]);
                    strcpy(inputbuf[i]+j,inputbuf[i]+j+1);
                    j=lung;
                    i++;
                    y=y+20;
                    actualizare();
                }
                else
                {
                    int len;
                    len=getEOL(inputbuf[i+1]);
                    len++;
                    inputbuf[i+1][len]=' ';
                    for(int i1=len; i1>j; i1--)
                        swap(inputbuf[i+1][i1],inputbuf[i+1][i1-1]);
                    strcpy(inputbuf[i]+j,inputbuf[i]+j+1);
                    i++;
                    y=y+20;

                    actualizare();
                }

                break;

            case KEY_DELETE: //DEL
                strcpy(inputbuf[i]+j+1,inputbuf[i]+j+2);
                actualizare();
                break;
            }

            break;

        case 8: // backspace
            //culoare=13;
            //anticuloare=0;
            if(i==0&&j==0) //inceput fisier
            {}
            else if(tab(inputbuf[i],j))
            {

                strcpy(inputbuf[i]+j-18,inputbuf[i]+j);

                j=j-18;

                actualizare();
            }
            else  if(j)             //interiorul unei linii
            {
                int z=getEOL(inputbuf[i]);
                strcpy(inputbuf[i]+j-1,inputbuf[i]+j);
                inputbuf[i][z]=0;
                j--;
                actualizare();
            }


            else                      //prima pozitie de pe o linie
            {
                int len;
                len=getEOL(inputbuf[i-1]);
                len++;
                inputbuf[i-1][len]=' ';
                j=len-1;
                strcat(inputbuf[i-1],inputbuf[i]);
                len=getEOL(inputbuf[i]);
                for(int i1=1; i1<=len; i1++)
                    strcpy(inputbuf[i],inputbuf[i]+1);
                i--;
                y=y-20;

                for(int i1=i+1; !lastLine(i1); i1++)
                    swap(inputbuf[i1+1],inputbuf[i1]);

                actualizare();

            }

            break;

        case 9: //TAB
        {
            char s1[100];
            int si1,aux1=j;
            for(si1=0; si1<=getEOL(inputbuf[i])-j+1; si1++)
            {
                s1[si1]=inputbuf[i][aux1+1];
                aux1++;
            }
            s1[si1++]=0;

            for(int i1=j; i1<=j+18; i1++)
                inputbuf[i][i1]=' ';

            j=j+18;

            strcpy(inputbuf[i]+j+1,s1);
            cout<<inputbuf[i]<<endl;

            inputbuf[i][j]=' ';
            actualizare();
        }
        break;

        case 13: // return
            if(stil>=2||marime>=4)
                for(int f=1; f<=2; f++)
                {

                    if(inputbuf[i][j+1]==0)
                    {
                        strcpy(inputbuf[i]+j,inputbuf[i]+j+1);
                        y=y+20;
                        i++;
                        j=0;
                        z=j;
                        inputbuf[i][j]=' ';
                        actualizare();
                    }
                    else
                    {
                        int i1;
                        for( i1=i; !lastLine(i1); i1++)
                        {}
                        i1++;

                        inputbuf[i1][0]=' ';
                        for(int x=i1; x>i+1; x--)
                            swap(inputbuf[x],inputbuf[x-1]);


                        char s[100];
                        int si,aux=j;
                        for(si=0; si<=getEOL(inputbuf[i])-j+1; si++)
                        {
                            s[si]=inputbuf[i][aux+1];
                            aux++;
                        }
                        s[si++]=0;

                        strcat(inputbuf[i+1],s);

                        strcpy(inputbuf[i]+j,inputbuf[i]+getEOL(inputbuf[i]));
                        i++;
                        j=0;
                        z=j;
                        y=y+20;
                        actualizare();
                    }
                }
            else
            {
                if(inputbuf[i][j+1]==0)
                {
                    strcpy(inputbuf[i]+j,inputbuf[i]+j+1);
                    y=y+20;
                    i++;
                    j=0;
                    z=j;
                    inputbuf[i][j]=' ';
                    actualizare();
                }
                else
                {
                    int i1;
                    for( i1=i; !lastLine(i1); i1++)
                    {}
                    i1++;

                    inputbuf[i1][0]=' ';
                    for(int x=i1; x>i+1; x--)
                        swap(inputbuf[x],inputbuf[x-1]);


                    char s[100];
                    int si,aux=j;
                    for(si=0; si<=getEOL(inputbuf[i])-j+1; si++)
                    {
                        s[si]=inputbuf[i][aux+1];
                        aux++;
                    }
                    s[si++]=0;

                    strcat(inputbuf[i+1],s);

                    strcpy(inputbuf[i]+j,inputbuf[i]+getEOL(inputbuf[i]));
                    i++;
                    j=0;
                    z=j;
                    y=y+20;
                    actualizare();
                }
            }

            break;

        case 27: // Escape = Abort
            save();
            getch();
            closegraph();
            break;

        case CTRL('n'):

            new_file();

            break;

        case CTRL('s'):

            save_AS();

            break;


        default:

            if (c >= ' ' && c <= '~')
            {
                if(textwidth(inputbuf[i])>795&&word_wrap==1)
                {

                    strcpy(inputbuf[i]+j,inputbuf[i]+j+1);
                    y+=20;
                    i++;
                    j=0;
                    inputbuf[i][j]=c;
                    j++;
                }

                else if(inputbuf[i][j+1]==0)
                {
                    inputbuf[i][j] = c;
                    j++;
                    z=j;
                    inputbuf[i][j+1] = 0;
                }
                else
                {
                    int z=getEOL(inputbuf[i]);
                    z++;
                    inputbuf[i][z]=' ';
                    for(int i1=z; i1>j; i1--)
                        swap(inputbuf[i][i1],inputbuf[i][i1-1]);

                    inputbuf[i][j]=c;
                    j++;

                    actualizare();
                }
            }
        }

    }

    while(1);
}

int main()
{
    Notepad=initwindow(800,600,"Notepad");
    int x=0,y=20;
    inputbuf[i][j]= {0};
    POINT cursorpos;
    settextstyle(0,0,0);
    culoare=15;
    anticuloare=0;
    notepad();

    getch();
    closegraph();
    return 0;
}
