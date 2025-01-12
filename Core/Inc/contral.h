#ifndef __CONTRAL_H__
#define __CONTRAL_H__

#include "main.h"

void returnToStartingPoint(void);//返回起点
void HandsomeReturnToPlace(void);
void FollowTrailToDesignatedArea(uint8_t zone);
void ThrowingPackages(void);

void task1(uint8_t mode2_flag,uint8_t mode2_count);//将物块放置在一号区域并返回起点
void task2(uint8_t mode2_flag,uint8_t mode2_count);
void task3(uint8_t mode2_flag,uint8_t mode2_count);

 
#endif 
