#include "slice.h"

#include "config.h"
Slice::Slice()
{
}

void Slice::setSliceKind(int i)
{
    sliceKind = i;
}

void Slice::setPixmapRoadInPractice()
{
    switch(sliceKind){
    case 0:
        SlicePixmapRoad = ERROR_PATH;
        break;
    case 1:
        SlicePixmapRoad = TRIANGLE_PATH;
        break;
    case 2:
        SlicePixmapRoad = CIRCLE_PATH;
        break;
    case 3:
        SlicePixmapRoad = TRIANGLE_PATH;
        break;
    case 4:
        SlicePixmapRoad = SQUARE_PATH;
        break;
    default:
        SlicePixmapRoad = LOADFAILURE_PATH;
    }
}
void Slice::setPixmapRoadInCompetition()
{
    switch(sliceKind){
    case 0:
        SlicePixmapRoad = CIRCLE_PATH;
        break;
    case 1:
        SlicePixmapRoad = TRIANGLE_PATH;
        break;
    case 2:
        SlicePixmapRoad = CIRCLE_PATH;
        break;
    case 3:
        SlicePixmapRoad = TRIANGLE_PATH;
        break;
    case 4:
        SlicePixmapRoad = SQUARE_PATH;
        break;
    default:
        SlicePixmapRoad = LOADFAILURE_PATH;
    }
}


void sliceToPut::setPixmapRoad()
{
    switch(sliceToPutKind){
    case 1:
        SliceToPutPixmapRoad = SLICETOPUT1;
        break;
    case 2:
        SliceToPutPixmapRoad = SLICETOPUT2;
        break;
    case 3:
        SliceToPutPixmapRoad = SLICETOPUT3;
        break;
    case 4:
        SliceToPutPixmapRoad = SLICETOPUT4;
    }
}

void sliceToPut::setSliceToPutKind(int a)
{
    if(a>=1 && a<=4) sliceToPutKind = a;
}
