#include<SDL.h>
#include<iostream>
#include<algorithm>
#include<ranges>
#include<random>
using namespace std;

///globally defining
//
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 320;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool init();
bool close();


/// Initializing Function
//
bool init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout<<"Error in initializing window : \n"<<SDL_GetError();
        success = false;
    }
    else
    {
        window = SDL_CreateWindow(" Virtualization Window" , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_SHOWN );
        if(window == NULL)
        {
            cout<<"Error in Window :\n"<<SDL_GetError();
        }
        else
        {
            renderer = SDL_CreateRenderer(window , -1 ,SDL_RENDERER_ACCELERATED);
            if(renderer == NULL)
            {
                cout<<"Error in rendering :\n"<<SDL_GetError();
                success = false;
            }
        }
    }
    return success;
}
///closing function
//
bool close()
{
    bool success = true;
    if(renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
        if(renderer != NULL)
        {
            cout<<"Error in closing rendering :\n"<<SDL_GetError();
            success = false;
        }

    }
    if(window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
        if(window != NULL)
        {
            cout<<"Error in closing window :\n"<<SDL_GetError();
            success = false;
        }
    }
    SDL_Quit();

    return success;
}

///Draw State
//
void drawState(vector<int> &v , SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer , 255 , 255 , 255 , 255);
    SDL_RenderClear( renderer );
    int index = 0;
    for(int i:v)
    {
        SDL_SetRenderDrawColor(renderer , 0 , 0 , 255 , 255);
        SDL_RenderDrawLine(renderer , index , SCREEN_HEIGHT , index , SCREEN_HEIGHT - i*4);
        index += 5;
    }
    SDL_RenderPresent(renderer);
}

///Bubble Sort
//
void bubbleSort(vector<int> &v)
{
    Uint32 startTime = SDL_GetTicks();
    for(int i = 0; i<v.size()-1; i++)
    {
        for(int j=i+1; j<v.size(); j++) //2 5 3 4 1 9
        {
            if(v[i] > v[j])
            {
                swap(v[i] , v[j]);
            }
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
}
/// Selection Sort
//
void selectionSort(vector<int> &v)
{
    Uint32 startTime = SDL_GetTicks();
    for(int i = 0; i<v.size()-1; i++)
    {
        int sortedElem = i;
        for(int j=i+1; j<v.size(); j++) //2 5 3 4 1 9
        {
            if(v[sortedElem] > v[j])
            {
                sortedElem = j;
            }
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
        if(sortedElem != i)
        {
            swap(v[i], v[sortedElem]);
        }
    }
}

///Printing Array
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
int main(int argc , char* args[])
{
    random_device rd;
    uniform_int_distribution dist(1,50);
    vector<int> v;

    //creating arr with random value
    for(int i = 1; i<51; i++)
    {
        v.push_back(dist(rd));
    }
    vector<int> vCopy = v; // create a copy of the original vector
    if(init())
    {
        SDL_Event e;
        bool quit = false;
        bool bubbleSortDone = false;
        bool selectionSortDone = false;
        while (!quit)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
            if (!bubbleSortDone)
            {
                bubbleSort(v);
                printSort(v);
                SDL_Delay(2000); // wait for 2 seconds before sorting again
                v = vCopy; // reset the vector to its original state
                bubbleSortDone = true;
            }
            if (!selectionSortDone)
            {
                selectionSort(v);
                printSort(v);
                SDL_Delay(2000); // wait for 2 seconds before quitting
                selectionSortDone = true;
            }
            if (bubbleSortDone && selectionSortDone)
            {
                quit = true;
            }
        }
        close();
    }



    return 0;


}
