#include<SDL.h>
#include<iostream>
#include<random>
#include<algorithm>
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
        renderer = NULL;
        if(renderer != NULL)
        {
            cout<<"Error in closing rendering\n"<<SDL_GetError();
            success = false;
        }
    }
    if(window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
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
        SDL_SetRenderDrawColor(renderer , 0 , 0 , 255 ,255); //blue color
        SDL_RenderDrawLine(renderer , index , SCREEN_HEIGHT , index , SCREEN_HEIGHT - i*4);
        index += 5;
    }
    SDL_RenderPresent(renderer);
}

///Partition
//
int partition (vector<int> &v, int start, int end)
{

    int pivot = v[end]; // pivot element
    int i = (start - 1);

    for (int j = start; j <= end - 1; j++)
    {
        // If current element is smaller than the pivot
        if (v[j] < pivot)
        {
            i++; // increment index of smaller element
            int t = v[i];
            v[i] = v[j];
            v[j] = t;
        }
    }
    int t = v[i+1];
    v[i+1] = v[end];
    v[end] = t;
    return (i + 1);
}

///Quick Sort Implementation
//
void quickSort(vector<int> &v, int start, int end, SDL_Renderer* renderer) /* a[] = array to be sorted, start = Starting index, end = Ending index */
{
    if (start < end)
    {

        int p = partition(v, start, end); //p is the partitioning index
        drawState(v, renderer); // Visualize the sorting process
        SDL_RenderPresent(renderer); // Update the screen
        SDL_Delay(10); // Delay in sec
        quickSort(v, start, p - 1, renderer);
        quickSort(v, p + 1, end, renderer);
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
int main(int argc, char* args[])
{
    vector<int> v;
    random_device rd;
    uniform_int_distribution dist(1, 99);

    for (int i = 1; i < 100; i++)
    {
        v.push_back(dist(rd));
    }

    int start = 0;
    int end = v.size() - 1;

    if (init())
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
            quickSort(v, start, end, renderer);
            printSort(v);
            SDL_Delay(4000);
            break;
        }
    }
    close();

    return 0;
}
