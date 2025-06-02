#include <iostream>
#include <thread>
#include "xtools.h"
#include "xdemux_task.h"
#include "xdecode_task.h"
#include "xvideo_view.h"
#include "xmux_task.h"
using namespace std;

//读取文件路径
#define URL "v1080.mp4"

//保存文件路径
#define SAVE_URL1 "rtsp_out1.mp4"

//截取时长
#define DRUNTION 10000

int main(int argc, char* argv[])
{
    XDemuxTask demux_task;
    for (;;)
    {
        if (demux_task.Open(URL))
        {
            break;
        }
        MSleep(100);
        continue;
    }

    auto vpara = demux_task.CopyVideoPara();
    auto apara = demux_task.CopyAudioPara();
    
    XMuxTask mux_task;
    if (!mux_task.Open(SAVE_URL1, vpara->para, vpara->time_base,
        apara->para, apara->time_base
    ))
    {
        LOGERROR("mux_task.Open failed!");
        return -1;
    }
    demux_task.set_next(&mux_task);
    demux_task.Start();
    mux_task.Start();
    MSleep(DRUNTION);   //截取时间
    
    mux_task.Stop();
    demux_task.Stop();

    system("pause");
    return 0;
}
