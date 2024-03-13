#pragma once
#include "Subsystemheaders/drive.h"

class Drive;

extern Drive chassis;

void default_constants();

void adj();
void stopall();
void bothwings(const float &value);
void usertime();
void prints();
void Drawing();