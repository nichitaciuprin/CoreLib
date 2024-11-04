#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <array>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <winuser.h>

#include <d3d11_1.h>
#include <d3dcompiler.h>

using namespace std;

#include "Debug.h"
#include "Math.h"
#include "FileHelper.h"
#include "Time.h"
#include "Subgen.h"
#include "Physics.h"

#include "Boids/World.h"