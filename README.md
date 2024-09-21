# 异地情侣影院
原始链接：https://github.com/vlasopoulos/SynchronizedPlayer，原始项目没有注释，也没有编译说明。

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



# 后续更新

提供详细项目文档。
