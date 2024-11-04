#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#define _USE_MATH_DEFINES
#include <math.h>

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

#include "Base/Debug.h"
#include "Base/Math.h"
#include "Base/FileHelper.h"
#include "Base/Time.h"
#include "Base/Subgen.h"
#include "Base/Physics.h"

#include "Boids/Boid.h"
#include "Boids/BoidWorld.h"
#include "Boids/World.h"

#include "Renderer/DeviceRecources.h"
#include "Renderer/Window.h"
#include "Renderer/Model.h"
#include "Renderer/ShaderBasic.h"
#include "Renderer/Renderer.h"
