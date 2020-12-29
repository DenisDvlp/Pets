//DDrawBuffer.h
#pragma once
#include "DDraw.h"
#include "DSafeObject.h"
#include "DBuffer.h"

using DDrawBuffer = DSafeObject<DDoubleBuffer<DDraw>>;