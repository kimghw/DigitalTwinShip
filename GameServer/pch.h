#pragma once

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#ifdef _DEBUG
#pragma comment(lib, "Debug\\ServerCore.lib")
#else
#pragma comment(lib, "Release\\ServerCore.lib")
#endif

#include "CorePch.h"
#include <iostream>
#include <fstream>
#include "JsonToConf.h"
#include "Protocol.pb.h"
#include "EDT0001.pb.h"

#define START_TIMER { auto start = std::chrono::high_resolution_clock::now();
#define END_TIMER(msg) auto end = std::chrono::high_resolution_clock::now(); \
                       std::chrono::duration<double, std::milli> elapsed = end - start; \
                       std::cout << msg << " took " << elapsed.count() << " ms\n"; }