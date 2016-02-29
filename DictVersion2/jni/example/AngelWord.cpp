#include"AngelDict.h"
#include"AngelLog.h"

int main(){
    AngelDictWord d("hello");
    d.AddMeaning("你好","Hello,How are you!");
    angel_printfe("trace\n");
    d.AddPhonetic("[hello]","file:///hello.mp3",0);

    angel_printfe("trace\n");
    d.AddPhonetic("[hexx]","file:///hexx.mp3",0);

    angel_printfe("trace\n");
    d.AddPhonetic("[hex]","file:///hexx.mp4",0);

    angel_printfe("trace\n");

    d.AddPict("file://hello.jpg",234,768,"comment");
    d.AddPict("file://hello.jpg",235,768,"comment");
    d.AddPict("file://hello.jpg",236,768,"comment");

    angel_printfe("trace\n");
    d.AddPict("file://hello.jpg",237,768,"comment");

    angel_printfe("trace\n");
    char buff[10240]={0};
    angel_printfe("trace\n");
    int ret = d.GetJsonString(buff,sizeof(buff));
    angel_printfe("trace\n");
    angel_printfe("trace\n");
    if(ret == 0){
        angel_printfe("get empty json\n");
    }else{
        angel_printfd("json is %s \n",buff);
    }
    return 0;
}
