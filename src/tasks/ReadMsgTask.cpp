#include "ReadMsgTask.h"
#include "Context.h"

ReadMsgTask::ReadMsgTask(){
}
  
void ReadMsgTask::init(int period){
  Task::init(period);  
}
  
void ReadMsgTask::tick(){
    Context& context = Context::getInstance();
    this->msg = MsgService.receiveMsg();
    if (msg->getContent() == "stp") {
        context.setIdle();
    } else if (msg->getContent() == "rst") {
        context.setWorking();
    } else if (msg->getContent() == "rs") {
        context.setRight();
    } else if (msg->getContent() == "ls") {
        context.setLeft();
    } else if (msg->getContent() == "tc") {
        context.setWaiting();
    } else if (msg->getContent() == "rc") {
        context.setRSU();
    }
}