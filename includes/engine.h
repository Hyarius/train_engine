#ifndef ENGINE_H
#define ENGINE_H

#include "jgl.h"

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <random>

#include "event.h"
#include "c_city.h"
#include "c_milestone.h"
#include "c_rail.h"
#include "c_journey.h"
#include "c_train.h"
#include "c_map.h"
#include "c_train_engine.h"
#include "c_main_window.h"

#define MIN_SPEED 5.0f

void saving_map();
void saving_journey();

#endif
