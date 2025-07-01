#include "Awm.h"

size_t AwmGetImageCenteredX(size_t ImageWidth, size_t ScreenWidth, size_t Scale){
    //DB0 Sanity
    if((ImageWidth <= 1) || (ScreenWidth <= 1) || (Scale < 1)){
        return 0x00;
    }
    size_t ScreenFocal = ScreenWidth / 2;  
    size_t ImageFocal = (ImageWidth / 2);
    return ScreenFocal - (ImageFocal * Scale);
}

size_t AwmGetImageCenteredY(size_t ImageHeight, size_t ScreenHeight, size_t Scale){
    //DB0 Sanity
    if((ImageHeight <= 1) || (ScreenHeight <= 1) || (Scale < 1)){
        return 0x00;
    }
    size_t ScreenFocal = ScreenHeight / 2;  
    size_t ImageFocal = ImageHeight / 2;
    return ScreenFocal - (ImageFocal * Scale);
}


void AwmGetImageScaleingCentered(
    size_t ImageWidth, size_t ImageHeight, 
    size_t ScreenHeight, size_t ScreenWidth,
    size_t* XScaling, size_t* YScaling
){
    if(ImageHeight >= ScreenHeight){
        *YScaling = 1;
    }else{
        *YScaling = ((ScreenHeight / ImageHeight) / 2) + 1;
    }
    if(ImageWidth >= ScreenWidth){
        *XScaling = 1;
    }else{
        *XScaling = ((ScreenWidth / ImageWidth) / 2) + 1;
    }
    if(*XScaling > *YScaling){
        *XScaling = *YScaling;
    }else if(*YScaling > *XScaling){
        *YScaling = *XScaling;
    }
}