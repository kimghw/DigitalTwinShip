#pragma once
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <sstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class TestJson
{
public:
// 랜덤한 위도경도 생성 

    static pair<string, string> generateRandomCoordinates() {
        // 이전 함수 호출 시간을 저장하는 static 변수
        static time_t lastCallTime = time(0);

        // 현재 시간을 가져옴
        time_t currentTime = time(0);

        // 시간 간격을 계산
        double timeInterval = difftime(currentTime, lastCallTime);
        cout << "TimeInterval :" << timeInterval << endl;
        // 1초당 10미터 이동
        double maxDistance = 10 * timeInterval;

        // 시드(seed) 설정
        srand(static_cast<unsigned int>(currentTime));

        // 거리를 0에서 maxDistance 사이의 무작위 값으로 생성
        double distance = (rand() / static_cast<double>(RAND_MAX)) * maxDistance;

        // 방향을 0에서 360도 사이의 무작위 값으로 생성
        double direction = (rand() / static_cast<double>(RAND_MAX)) * 360.0;

        // 라디안으로 변환
        double radianDirection = direction * M_PI / 180.0;

        // 대한민국 부산시 영도의 위도와 경도
        double baseLatitude = 35.0982;
        double baseLongitude = 129.0432;

        // 위도와 경도를 계산
        double latitude = baseLatitude + (distance / 6371.0) * (180.0 / M_PI);
        double longitude = baseLongitude + (distance / 6371.0) * (180.0 / M_PI) / cos(baseLatitude * M_PI / 180.0);

        // 현재 함수 호출 시간을 업데이트
        lastCallTime = currentTime;
        std::string latitudeHMS = convertToDMS(latitude);
        std::string logitudeHMS = convertToDMS(longitude);

        return make_pair(latitudeHMS, logitudeHMS);
    }
// 위도와 경도를 도분초 형식의 문자열로 변환
    static std::string convertToDMS(double degrees) {
        char direction = degrees < 0 ? 'S' : 'N';
        degrees = std::abs(degrees);

        int d = static_cast<int>(degrees);
        int m = static_cast<int>((degrees - d) * 60);
        double s = (degrees - d - m / 60.0) * 3600;

        std::ostringstream oss;
        oss << d << " " << m << " " << std::fixed << std::setprecision(2) << s << " " << direction;

        return oss.str();
    }



};

