# video_sdk
这是一个音视频播放器SDK，支持从RTSP拉流，或者本地MP4文件播放以及转录

### 技术栈
C++、SDL、FFMPEG、责任链模式、工厂模式

### API接口说明

##### 一、线程基类(XThread)
```C++
void XThread::set_next(XThread* xt)
```
1. 设置当前线程的下一个责任链线程，比如封装线程后要解码，此时传入解码线程对象

```C++
void XThread::Start()
```
2. 启动线程
```C++
void XThread::Stop()
```
3. 停止线程

##### 二、解封装线程(class XDemuxTask :public XThread)
```C++
bool XDemuxTask::Open(std::string url, int timeout_ms)
```
1. url 为要播放或者转录的RTSP或者本地MP4文件地址，timeout_ms 为超时断开连接时间，有默认值为1000ms（可不传）。
设置成功返回true，失败返回false

```C++
std::shared_ptr<XPara> CopyVideoPara()
```
2. 返回视频参数的智能指针

```C++
std::shared_ptr<XPara> CopyAudioPara()
```
3. 返回音频参数的智能指针

##### 三、封装线程(class XMuxTask :public XThread)
```C++
bool XMuxTask::Open(const char* url,
    AVCodecParameters* video_para,
    AVRational* video_time_base,
    AVCodecParameters* audio_para,
    AVRational* audio_time_base 
)
```
1. url 为要保存的文件地址，video_para 为视频参数，video_time_base 为视频时间基，audio_para 为音频参数，audio_time_base 为音频的时间基。
设置成功返回true，失败返回false

