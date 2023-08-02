#pragma once
#include <cstdint>
#include <memory>
#include "ClientService.h"


using BYTE = unsigned char;
using int32 = uint8_t;
using PacketSessionRef = std::shared_ptr<class ClientService>();