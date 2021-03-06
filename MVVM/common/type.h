/*
 * File: type.h
 * Version: 1.0
 * Author: kk
 * Created Date: Wed Jul 18 13:32:01 DST 2018
 * -------------------------------------------
 * 所有的命令/属性都用一个相应的枚举变量区分。
 * 属性也使用枚举变量
 * 每增加一个command, 就在相应的枚举变量后面增加一个值
 */

#pragma once


enum commandsType{
    OPEN_FILE,
    SAVE_FILE,
    OPEN_SUB_FILE,
    FILTER,
    EDGE_DETECTION,
    HOUGH_CIRCLE_DETECTION,
    CHANNEL,
    RED_CHANNEL,
    GREEN_CHANNEL,
    BLUE_CHANNEL,
    HOUGH_LINE_DETECTION,
    GRAY_SCALE_TRANSFER,
    OTSU,
    OPEN_SUB_DIALOG,
    DUAL_THRESHOLD,
    HUE_SATURA_LIGHT,
    CURVE,
    LEVEL,
    CLIP,
    SCALE,
    HISTOGRAM,
    ALGEBRAIC,
    ALGEBRAIC_ADD,
    ALGEBRAIC_SUBTRACT,
    ALGEBRAIC_MULTIPLY,
    BINARY_MORPHOLOGY,
    GRAY_MORPHOLOGY,
    ART_EFFECTS,
    CLASSIC_EFFECTS,
};

enum propertyType{
    MAIN_IMAGE,
    SUB_IMAGE,
    TMP_IMAGE,
    LOG,
};

enum ChannelType{
    RED,
    GREEN,
    BLUE,
};

enum OperationType{
    DILATION,
    EROSION, 
    OPENING, 
    CLOSING,                      
    THINNING, 
    THICKING, 
    DISTANCE_TRANSFORM,
    SKELETONIZATION, 
    SKELETON_RECONSTRUCTION,
    RECONSTRUCTION,
    OBR,
    CBR,
    WATERSHED,
};

enum EffectsType{
    NOEFFECTS,
// art effects
    EMBOSS,
    SCULPTURE,
    DILATE,
    ERODE,
    FROSTGLASS,
    SKETCH,
    OILPAINT,
    WOODCUT,
    INVERTED,
    MEMORY,
    FREEZING,
    CASTING,
    COMICSTRIP,
// classic effects
    SHARPEN,
    COLORTOBLACK,
    DEFOG,
    SOFT,
    BALANCE,
    NOSTALGIA,
    BLACKCOMIC,
    TIMETUUNEL,
    CLASSICLOMO,
    WHITEFACE,
    BEAUTIFYFACE,
    PINKLADY,
};
