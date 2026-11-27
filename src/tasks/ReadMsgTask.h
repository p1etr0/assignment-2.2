#ifndef __READMSGTASK__
#define __READMSGTASK__

#include "Task.h"
#include "components/MsgService.h"


class ReadMsgTask: public Task { 

public:
    ReadMsgTask();
    void init(int period);
    void tick();

private:
    Msg* msg;
};

#endif