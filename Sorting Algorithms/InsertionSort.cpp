#include<SDL.h>
#include<iostream>
#include<algorithm>
#include<random>
#include<vector>
using namespace std;

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 320;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool init();
bool close();

/// Initializing Window
bool init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout<<"Error in creating Window\n"<<SDL_GetError();
        success = false;
    }
    else
    {
        window = SDL_CreateWindow(" Visualization Window " , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            cout<<"Error in initializing window\n"<<SDL_GetError();
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer( window ,-1 , SDL_RENDERER_ACCELERATED);
            if(renderer == NULL)
            {
                cout<<"Error in rendering\n"<<SDL_GetError();
                success = false;
            }
        }
    }
    return success;
}

///Closing Function
bool close()
{
    bool success = true;
    if(renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
        if(renderer != NULL)
        {
            cout<<"Error in closing rendering\n"<<SDL_GetError();
            success = false;
        }
    }
    if(window != NULL)
    {
        SDL_DestroyWindow(window);
        if(window != NULL)
        {
            cout<<"Error in closing window\n"<<SDL_GetError();
            success = false;
        }
    }
    SDL_Quit();
    return success;
}

///Draw State
void drawState(vector<int> &v,SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer , 255 , 255 , 255 ,255);
    SDL_RenderClear( renderer );
    int index = 0;
    for(int i:v)
    {
        SDL_SetRenderDrawColor(renderer , 0 , 0 , 255 ,255);
        SDL_RenderDrawLine(renderer , index , SCREEN_HEIGHT , index , SCREEN_HEIGHT - i*4);
        index += 5;
    }
    SDL_RenderPresent(renderer);
}

///Insertion Sort
//
void insertionSort(vector<int> &v)
{
    Uint32 startTime = SDL_GetTicks();
    for (int i = 1; i < v.size(); ++i) {
        int key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = key;
        // Draw the state of the sort
            drawState(v, renderer);

            // Update the screen
            SDL_RenderPresent(renderer);

            // Delay in sec
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - startTime < 10)
            {
                SDL_Delay(10 - (currentTime - startTime));
            }
            startTime = currentTime;
    }
}

///Print Sorted arr
//
void printSort(vector<int> &v)
{
    for(int i:v)
    {
        cout<<i<<" ";
    }
}

///Main Function
//
int main(int argc , char *args[])
{
    vector<int> v;
    random_device rd;
    uniform_int_distribution dist(1,99);

    for(int i = 1; i<100; i++)
    {
        v.push_back(dist(rd));
    }

    if(init())
    {
        SDL_Event e;
        bool quit = false;
        while (!quit)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
            insertionSort(v);
            printSort(v);
            SDL_Delay(4000);
            break;


        }

    }
    close();


    return 0;

}
