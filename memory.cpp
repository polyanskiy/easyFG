#include "easyfg.h"


void MainWindow::AllocateMemory()
{
    DataArray = (int**)malloc(MAX_WIDTH*sizeof(int*));
    RefArray = (int**)malloc(MAX_WIDTH*sizeof(int*));
    CorrectedArray = (int**)malloc(MAX_WIDTH*sizeof(int*));
    for(int i=0; i<MAX_WIDTH; i++)
    {
        DataArray[i] = (int*)malloc(MAX_HEIGHT*sizeof(int));
        RefArray[i] = (int*)malloc(MAX_HEIGHT*sizeof(int));
        CorrectedArray[i] = (int*)malloc(MAX_HEIGHT*sizeof(int));
    }
    X = (float*)malloc(MAX_WIDTH*sizeof(float));
    Y = (float*)malloc(MAX_HEIGHT*sizeof(float));
    R = (float*)malloc((int)ceil(sqrt(pow(MAX_WIDTH,2)+pow(MAX_HEIGHT,2)))*sizeof(float));
    //R = (float*)malloc(MAX_R*sizeof(float));
}


void MainWindow::ClearMemory()
{
    for(int i=0; i<MAX_WIDTH; i++)
    {
        free(DataArray[i]);
        free(RefArray[i]);
        free(CorrectedArray[i]);
    }
    free(DataArray);
    free(RefArray);
    free(CorrectedArray);
    free(X);
    free(Y);
    free(R);
}
