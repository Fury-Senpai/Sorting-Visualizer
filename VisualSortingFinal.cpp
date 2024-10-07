//
///Including header files
//
#include<SDL.h>
#include<iostream>
#include<algorithm>
#include<ranges>
#include<random>
using namespace std;

///Globally defining function
//
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;
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
        window = SDL_CreateWindow(" Visualization Window" , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_SHOWN );
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

void drawState(vector<int> &v, SDL_Renderer* renderer, unsigned int red, unsigned blue, int screenHeight) {
    // Clear the renderer with a black color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Calculate the width of each line
    int lineWidth = SCREEN_WIDTH / v.size();

    // Draw the lines
    int index = 0;
    for (int i : v) {
        if (index == red) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red color
        } else if (index == blue) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // blue color
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 105, 108, 255); // pink color
        }

        // Draw a line
        SDL_RenderDrawLine(renderer, index * lineWidth, screenHeight, index * lineWidth, screenHeight - (i / 2) * 4);

        index+=1;
    }

    // Update the screen
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
            drawState(v, renderer , i ,j, SCREEN_HEIGHT);

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
            drawState(v, renderer , i ,j, SCREEN_HEIGHT);

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
            drawState(v, renderer , i ,j, SCREEN_HEIGHT);

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


///Merge Logic
void merge(vector<int> &v,int low , int mid , int high)
{
    int p1 = low;
    int p2 = mid+1;

    vector<int> temp; // Creating a temp arr

    while(p1 <= mid && p2 <= high )
    {
        if(v[p1] <= v[p2] )
        {
            temp.push_back(v[p1]);
            p1++;
        }
        else
        {
            temp.push_back(v[p2]);
            p2++;
        }
    }

    while(p1 <= mid)
    {
        temp.push_back(v[p1]);
        p1++;
    }
    while(p2 <= high)
    {
        temp.push_back(v[p2]);
        p2++;
    }

    for(int i = low; i<=high; i++)
    {
        v[i] = temp[i-low];
    }
}

///Merge Sort
//
void mergeSort(vector<int> &v , int low , int high)
{
    Uint32 startTime = SDL_GetTicks();
    if(low>=high)
    {
        return;
    }
    int mid = (low + high)/2;
    mergeSort(v,low,mid);
    mergeSort(v,mid+1,high);
    merge(v,low,mid ,high);
        // Draw the state of the sort
            drawState(v, renderer , low , high , SCREEN_HEIGHT);

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


///Partition h
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
        drawState(v, renderer , start , end , SCREEN_HEIGHT); // Visualize the sorting process
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
    cout<<"Press '1' for Bubble Sort\nPress '2' for Selection Sort\nPress '3' for Insertion Sort\nPress '4' for Merge Sort\nPress '5' for Quick Sort\nPress 'Escape' for returning\n\n";
    if (!init())
    {
        cout << "Failed to initialize!" << endl;
        return -1;
    }

    random_device rd;
    uniform_int_distribution<int> dist(1, 99);
    vector<int> v;
    for (int i = 1; i < 100; i++)
    {
        v.push_back(dist(rd));
    }
    int low = 0;
    int high = v.size() - 1;
    vector<int> vCopy = v;  // Copy of the original array for resetting.

    bool quit = false;
    SDL_Event e;
    bool bubbleSortDone = false;
    bool selectionSortDone = false;
    bool insertionSortDone = false;
    bool mergeSortDone = false;
    bool quickSortDone = false;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_1:  // Press '1' for Bubble Sort
                        v = vCopy;
                        if (!bubbleSortDone) {
                            bubbleSort(v);
                            cout<<"Bubble Sort : "<<endl;
                            printSort(v);
                            cout<<endl;
                            bubbleSortDone = true;
                        }
                        else {
                            cout << "Bubble Sort already done!" << endl;
                        }
                        break;
                    case SDLK_2:  // Press '2' for Selection Sort
                        v = vCopy;
                        if (!selectionSortDone) {
                            selectionSort(v);
                            cout<<"Selection Sort : "<<endl;
                            printSort(v);
                            cout<<endl;
                            selectionSortDone = true;
                        }
                        else {
                            cout << "Selection Sort already done!" << endl;
                        }
                        break;
                    case SDLK_3: //Press '3' for Insertion Sort
                        v = vCopy;
                        if(!insertionSortDone) {
                            insertionSort(v);
                            cout<<"Insertion Sort : "<<endl;
                            printSort(v);
                            cout<<endl;
                            insertionSortDone = true;
                        }
                        else {
                            cout<< "Insertion Sort already done!" << endl;
                        }
                        break;
                    case SDLK_4: // Press '4' for Merge Sort
                        v = vCopy;
                        if (!mergeSortDone) {
                            mergeSort(v, low, high);
                            cout<<"Merge Sort : "<<endl;
                            printSort(v);
                            cout<<endl;
                            mergeSortDone = true;
                        }
                        else {
                            cout<< "Merge Sort already done!" << endl;
                        }
                        break;
                    case SDLK_5: //Press '5' for Quick Sort
                        v = vCopy;
                        if(!quickSortDone) {
                            quickSort(v,low , high , renderer);
                            cout<<"Quick Sort : "<<endl;
                            printSort(v);
                            quickSortDone = true;
                        }
                        else {
                            cout<< "Quick Sort already done!" <<endl; 
                        }
                        break;
                    case SDLK_ESCAPE:  // Press 'Escape' to quit
                        quit = true;
                        break;
                }
            }
        }
    }

    close();
    return 0;
}

