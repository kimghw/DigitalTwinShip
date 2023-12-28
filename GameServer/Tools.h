#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

float dmsStrToDd(const std::string& dmsStr) {
    std::istringstream iss(dmsStr);
    float degrees, minutes, seconds;
    char direction;

    // 문자열을 공백을 기준으로 파싱
    if (!(iss >> degrees >> minutes >> seconds >> direction)) {
        throw std::invalid_argument("잘못된 형식의 문자열입니다.");
    }

    // 도분초를 십진수로 변환
    double dd = degrees + minutes / 60.0 + seconds / 3600.0;

    // 남쪽과 서쪽 방향의 경우 음수로 처리
    if (direction == 'S' || direction == 'W') {
        dd *= -1.0;
    }

    return dd;
}