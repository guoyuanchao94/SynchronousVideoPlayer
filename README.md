# 同步视频播放器
 功能：
- 支持多人同步看电影
- 支持播放、暂停、停止
- 支持文字聊天
- 支持多人语音

# MP4 格式
西瓜视频 Demo：https://sf1-cdn-tos.huoshanstatic.com/obj/media-fe/xgplayer_doc_video/mp4/xgplayer-demo-360p.mp4

新闻视频1：https://stream7.iqilu.com/10339/upload_transcode/202002/09/20200209105011F0zPoYzHry.mp4

新闻视频2：https://stream7.iqilu.com/10339/upload_transcode/202002/09/20200209104902N3v5Vpxuvb.mp4

# 编译报错排查
Failed to create QVideoSink "Not available"

和QT版本有关系，目前QT6.7有bug。

可以使用QT6.5.3和6.6.3 mingw64编译器正常编译。

# 潜在问题
本项目完全采用Qt6多媒体模块,频繁切换媒体源会导致D3D11:Removing Devices错误，出现该错误再拖动进度条会导致程序崩溃

Unbutu 22.04.4版本GCC构建存在qt.multimedia.ffmpeg.libsymbolsresolver: Couldn't load VAAPI library问题

QVideoWidget组件在没有播放视频时,出现其他画面

# HTTP服务
服务端需开启HTTP服务，才能将本地文件路径转换成HTTP服务路径，其他主机才能播放

Python提供的HTTP服务对于较大文件无法完全传输，请使用其他服务器进行测试

