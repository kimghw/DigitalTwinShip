#pragma once
#include "pch.h"

class IMessageObserver
{
public:
	virtual ~IMessageObserver() = default;
	virtual void MessageUpdate(const SendBufferRef messageFromSubject)=0;
};



