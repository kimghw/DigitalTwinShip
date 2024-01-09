#pragma once

#define WIN32_LEAN_AND_MEAN // °ÅÀÇ »ç¿ëµÇÁö ¾Ê´Â ³»¿ëÀ» Windows Çì´õ¿¡¼­ Á¦¿ÜÇÕ´Ï´Ù.

#ifdef _DEBUG
#pragma comment(lib, "Debug\\ServerCore.lib")
#else
#pragma comment(lib, "Release\\ServerCore.lib")
#endif

#include "CorePch.h"
#include <iostream>
#include <fstream>
#include "JsonToConf.h"
#include <thread>


#include "ClientPacketHandler.h"
#include "DataSessionManager.h"

#include <google/protobuf/message.h>
#include "MRSchema.pb.h"
#include "EDT0001.pb.h"
#include "enum.pb.h"


// 매크로 시작: 고유한 start 시간 기록
#define START_TIMER { const auto startTime = std::chrono::high_resolution_clock::now();

// 매크로 종료: 시간 차이 계산과 출력
#define END_TIMER(msg) const auto endTime = std::chrono::high_resolution_clock::now(); \
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count(); \
    std::cout << msg << " took " << elapsed << " ms\n"; \
}


#define RUN_IN_THREAD(func, ...) std::thread(func, ##__VA_ARGS__).detach();