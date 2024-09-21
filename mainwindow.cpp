#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkInterface>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->chatWidget->setWordWrap(true);

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    audioOutput->setVolume(0.1f);
    player->setVideoOutput(ui->videoDisplay);   //绑定视频输出
    player->setAudioOutput(audioOutput);        //绑定音频输出

    ui->videoDisplay->installEventFilter(this);
    ui->videoDisplay->show();
    ui->seekSlider->setRange(0,player->duration());
    ui->volumeSlider->setRange(0,100);
    ui->volumeSlider->setValue(10);
    ui->muteButton->setChecked(true);   //麦克风默认静音

    ui->labelPosition->setText("00:00  /");
    ui->labelDuration->setText("00:00");

    connect(ui->seekSlider, &QSlider::sliderMoved, this, &MainWindow::seek);        //seek事件
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);    //视频时长改变
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);    //当前播放位置改变
    //connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::handleBuffering);
    connect(ui->buttonPlay, &QPushButton::clicked, this, &MainWindow::playPressed);
    connect(ui->buttonPause, &QPushButton::clicked, this, &MainWindow::pausePressed);
    connect(ui->buttonStop, &QPushButton::clicked, this, &MainWindow::stopPressed);
    connect(ui->buttonFullScreen, &QPushButton::clicked, this, &MainWindow::fullScreen);
    connect(this, &MainWindow::signalOpenPath,this,&MainWindow::slotOpenPath);

    connect(player, &QMediaPlayer::errorOccurred, this, [=](QMediaPlayer::Error error, const QString &errorString)
    {
        switch(error)
        {
        case QMediaPlayer::FormatError:
            qDebug() << "媒体格式错误";
            qDebug() << errorString;
            break;
        case QMediaPlayer::ResourceError:
            qDebug() << "播放源错误错误";
            qDebug() << errorString;
            break;
        case QMediaPlayer::NetworkError:
            qDebug() << "网络错误";
            qDebug() << errorString;
            break;
        case QMediaPlayer::AccessDeniedError:
            qDebug() << "访问拒绝错误";
            qDebug() << errorString;
            break;
        default:
            qDebug() << "没有错误";
        }
    });

    connect(player,&QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status)
    {
        qDebug() << "播放媒体的状态: " << status;
    });

    playList = new QListWidget(this);
    playList->resize(190, this->height() - 42);
    playList->hide();

    //是否显示播放列表
    connect(ui->btnPlayList, &QPushButton::clicked, this, [=]()
    {
        if(playList->isHidden())
        {
            playList->move(ui->chatWidget->x(), (this->height() - playList->height()) / 2 + 12);
            playList->raise();
            playList->show();
        }
        else if(!playList->isHidden())
        {
            playList->hide();
        }
    });

    connect(this,&MainWindow::playListItemSetUrl, this, &MainWindow::hostLocalFile);
    connect(playList, &QListWidget::itemDoubleClicked, this, [=](QListWidgetItem *item)
    {
        qDebug() <<"双击列表项";
        if(item == nullptr)
        {
            return;
        }
        QString filePath = item->data(Qt::UserRole).toString();
        QUrl url = QUrl::fromLocalFile(filePath);
        qDebug() << url;
        emit playListItemSetUrl(filePath);  //发射信号去打开本地文件,前提是开启HTTP服务,如果有客户端连接
    });
    connect(this,&MainWindow::setlocalFile,this,&MainWindow::hostLocalFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//时间戳线程,server端定时将播放进度发送给所有client
void MainWindow::sendTimestampThreaded()
{
    if (server)
    {
        QThread *sendTimestampThread = QThread::create(&MainWindow::sendTimestamp, this);
        connect(this, &MainWindow::destroyed, sendTimestampThread, &QThread::quit);
        connect(sendTimestampThread, &QThread::finished, sendTimestampThread, &QThread::deleteLater);
        sendTimestampThread->start();
    }
}

void MainWindow::sendTimestamp()
{
    while(true)
    {
        //sncsync+position
        server->writeToClients(QString::number(player->position()), "sncsync");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void MainWindow::readFile(const QString &filePath)
{
    if(setFilePath.find(filePath) != setFilePath.end())
    {
        qDebug() << "当前文件夹已经打开";
        return;
    }
    setFilePath.insert(filePath);
    if(filePath.isEmpty())
    {
        qDebug() << "没有打开文件夹";
        return;
    }
    qDebug() <<"文件夹路径：" << filePath;
    QVector<QString> files;
    readDirectoryFilesRecursively(filePath, files);
    for(auto &file : files)
    {
        QFileInfo fileInfo(file);
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::DisplayRole,fileInfo.fileName());
        item->setData(Qt::UserRole,file);
        playList->addItem(item);
        qDebug() << file;
    }
    qDebug() <<"获取到的文件数目: " << files.size();
}

void MainWindow::readDirectoryFilesRecursively(const QString &directoryPath, QVector<QString> &files)
{
    QDir dir(directoryPath);
    if (!dir.exists())
    {
        qDebug() << "目录不存在";
        return;
    }

    // 获取所有文件和文件夹
    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDir::NoSort);

    foreach (QFileInfo file, fileList)
    {
        if (file.isFile())
        {
            QString lastSuffix = file.suffix();
            // qDebug () <<lastSuffix;
            if (lastSuffix != "mp4" && lastSuffix != "flv" && lastSuffix != "mkv")
            {
                continue;
            }
            files.push_back(file.absoluteFilePath());
            qDebug() << "文件路径：" << file.absoluteFilePath();
        }
        else if (file.isDir())
        {
            // 递归调用以处理子文件夹
            readDirectoryFilesRecursively(file.absoluteFilePath(), files);
        }
    }
}

//设置网络和单个本地的视频的视频源
//打开URL,点击确认后的发射urlSet的槽函数
void MainWindow::setVideoSource(QString url)
{
    qDebug() << "MainWindow::设置播放源: " << url;
    //客户端推送给服务端,服务端再分发给各个客户端
    if (client)
    {
        qDebug() <<"MainWindow::存在客户端";
        client->writeToServer(url, "srcnet");   //网络播放源
        //srcnet+url
    }
    else
    {
        qDebug() <<"MainWindow::不存在客户端";
        player->setSource(QUrl(url));
        this->setWindowTitle("同步视频播放器  " + url);
    }
}

//打开网络媒体或本地文件
void MainWindow::on_actionOpen_URL_triggered()
{
    openURL *urlWindow = new openURL(this);
    urlWindow->setWindowTitle("打开资源");
    urlWindow->show();
    connect(urlWindow, SIGNAL(urlSet(QString)), this, SLOT(setVideoSource(QString)));
}

void MainWindow::on_actionStart_Server_triggered()
{
    SetPort *portWindow = new SetPort(this);
    portWindow->setWindowTitle("开启服务");
    portWindow->show();
    // int result = portWindow->exec();
    if (server == nullptr)
    {
        server = new Server(this);
        qDebug() << "MainWindow::创建服务端";
    }
    else
    {
        delete server;
        server = nullptr;
        server = new Server(this);
        qDebug() << "MainWindow::创建服务端";
    }
    //开启UDPServer
    if (udpServer == nullptr)
    {
        udpServer = new UdpServer(this);
        qDebug() << "MainWindow::创建Udp服务端";
    }
    else
    {
        delete udpServer;
        udpServer = nullptr;
        udpServer = new UdpServer(this);
        qDebug() << "MainWindow::创建Udp服务端";
    }
    connect(portWindow, SIGNAL(setPort(int)), server, SLOT(initServer(int)));
    //先完成本地TCP连接
    connect(portWindow, SIGNAL(connectToLocalHost(int, QString)), this, SLOT(connectToLocalHost(int, QString)));
    connect(portWindow, SIGNAL(setPort(int)), udpServer, SLOT(initServer(int)));
    //server != nullptr
    connect(server, &Server::addUdpClient, udpServer, &UdpServer::addUdpClient);
    connect(server, &Server::removeUdpClient, udpServer, &UdpServer::removeUdpClient);

    sendTimestampThreaded();
}

void MainWindow::on_actionConnect_to_Server_triggered()
{
    ConnectToServer *connectDialog = new ConnectToServer(this);
    connectDialog->setWindowTitle("连接到服务器");
    connectDialog->show();
    if (client == nullptr)
    {
        qDebug() <<"MainWindow::创建非服务端的客户端";
        client = new Client(this);
    }
    else
    {
        delete client;
        client = nullptr;
        client = new Client(this);
        qDebug() <<"MainWindow::创建非服务端的客户端";
    }
    if (udpClient == nullptr)
    {
        udpClient = new UdpClient(this);
        qDebug() <<"MainWindow::创建非服务端的Udp客户端";
    }
    else
    {
        delete udpClient;
        udpClient = nullptr;
        udpClient = new UdpClient(this);
        qDebug() <<"MainWindow::创建非服务端的Udp客户端";
    }

    connect(udpClient, &UdpClient::connected, this, &MainWindow::initClientConnections);

    connect(connectDialog, &ConnectToServer::connectToServer, client, &Client::connectToServer);
    connect(connectDialog, &ConnectToServer::connectToUdpServer, udpClient, &UdpClient::udpConnectToServer);
    connect(connectDialog, &ConnectToServer::setUserName, this, &MainWindow::setUserName);
    connect(connectDialog, &ConnectToServer::setServerURL, this, &MainWindow::setServerURL);
}

void MainWindow::connectToLocalHost(int port, QString userName)
{
    qDebug() << "MainWindow::连接到本地服务端,接收端口号: " << port;
    serverURL = "127.0.0.1";
    if (client == nullptr)
    {
        client = new Client(this);
        qDebug() <<"MainWindow::创建服务端的客户端";
    }
    else
    {
        delete client;
        client  = nullptr;
        client = new Client(this);
        qDebug() <<"MainWindow::创建服务端的客户端";
    }
    if (udpClient == nullptr)
    {
        udpClient = new UdpClient(this);
        qDebug() << "MainWindow::创建服务端的Udp客户端";
    }
    else
    {
        qDebug() << "MainWindow::创建服务端的Udp客户端";
        delete udpClient;
        udpClient = nullptr;
        udpClient = new UdpClient(this);
    }

    //等client和udpclient都初始化完成再去初始化其他连接
    connect(udpClient, &UdpClient::connected, this, &MainWindow::initClientConnections);
    client->connectToLocalServer(port);
    udpClient->udpConnectToLocalServer(port);
    setUserName(userName);
}

void MainWindow::initClientConnections()
{
    qDebug() << "MainWindow::初始化客户端连接";
    ui->menuConnect->setEnabled(false);
    connect(udpClient, &UdpClient::setUdpPort, client, &Client::setUdpPort);
    connect(client, &Client::newChatMsg, this, &MainWindow::newChatMsg);
    connect(client, &Client::remotePlay, this, &MainWindow::remotePlay);
    connect(client, &Client::remotePause, this, &MainWindow::remotePause);
    connect(client, &Client::remoteStop, this, &MainWindow::remoteStop);
    connect(client, &Client::remoteSeek, this, &MainWindow::remoteSeek);
    connect(client, &Client::remoteSync, this, &MainWindow::remoteSync);
    connect(client, &Client::remoteSetVideoSource, this, &MainWindow::remoteSetVideoSource);
    connect(client, &Client::remoteSetLocalVideoSource, this, &MainWindow::remoteSetLocalVideoSource);
    connect(client, &Client::userConnected, this, &MainWindow::userConnected);
    connect(client, &Client::userDisconnected, this, &MainWindow::userDisconnected);

    //实例化audioinput/audiooutput
    QAudioFormat format;
    format.setSampleRate(44100);    //设置采样率
    format.setChannelCount(1);     //设置通道数
    format.setSampleFormat(QAudioFormat::UInt8);

    QAudioDevice info = QMediaDevices::defaultAudioInput();
    if (!info.isFormatSupported(format))
    {
        qWarning() << "不支持默认格式,请尝试使用最接近的格式";
    }
    QAudioDevice info2 = QMediaDevices::defaultAudioOutput();
    if (!info2.isFormatSupported(format))
    {
        qWarning() << "后端不支持原始音频格式,无法播放音频";
    }
    udpAudioSink = new QAudioSink(format, this);
    udpAudioSink->setVolume(0.2f);
    udpAudioSource = new QAudioSource(format, this);
    udpAudioSourceDevice = udpAudioSource->start();
    udpAudioSinkDevice = udpAudioSink->start();
    //从麦克风读取到数据调用readFromMicrophone进行udp发送
    connect(udpAudioSourceDevice, &QIODevice::readyRead, this, &MainWindow::readFromMicrophone);
    //从udp读取到数据调用voiceReceived进行播放
    connect(udpClient, &UdpClient::voiceReceived, this, &MainWindow::voiceReceived);
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress && object == ui->videoDisplay)
    {
        QKeyEvent *key = dynamic_cast<QKeyEvent *>(event);
        if (key->key() == Qt::Key_Escape)
        {
            ui->videoDisplay->setFullScreen(false);
            return true;
        }
        if (key->key() == Qt::Key_Space)
        {
            if (player->playbackState() == QMediaPlayer::StoppedState || player->playbackState() == QMediaPlayer::PausedState)
            {
                playPressed();  //继续播放
                return true;
            }
            if (player->playbackState() == QMediaPlayer::PlayingState)
            {
                pausePressed(); //暂停播放
                return true;
            }
        }
    }
    if (event->type() == QEvent::MouseButtonDblClick && object == ui->videoDisplay)
    {
        if (ui->videoDisplay->isFullScreen())
        {
            ui->videoDisplay->setFullScreen(false);
        }
        else
        {
            ui->videoDisplay->setFullScreen(true);
        }
        return true;
    }
    return QWidget::eventFilter(object, event);
}

void MainWindow::fullScreen()
{
    ui->videoDisplay->setFullScreen(true);
}

void MainWindow::playPressed()
{
    if (client)
    {
        client->writeToServer("play" + QString::number(player->position()), "snc");
        // sncplay+position
    }
    else
    {
        player->play();
    }
    qDebug() << "isPlaying " << player->isPlaying();
}

void MainWindow::pausePressed()
{
    if (client)
    {
        qDebug() <<"记录视频位置,暂停";
        client->writeToServer("paus" + QString::number(player->position()), "snc");
        //sncpaus+position
    }
    else
    {
        player->pause();
    }
}

void MainWindow::stopPressed()
{
    if(client)
    {
        client->writeToServer("stop", "snc");
        // sncstop
    }
    else
    {
        player->stop();
    }
}

//连接到服务器的客户端给服务器记录用户名
void MainWindow::setUserName(QString userName)
{
    if (client)
    {
        client->writeToServer(userName, "usr");
        //usr+userName
    }
}

//发送消息,回车就行
void MainWindow::on_chatInput_returnPressed()
{
    if(ui->chatInput->text().isEmpty())
    {
        qDebug() << "发送消息为空";
        return;
    }
    if (client)
    {
        client->writeToServer(ui->chatInput->text(), "msg");
        //msg+string
    }
    ui->chatInput->clear();
}

void MainWindow::on_sendButton_clicked()
{
    on_chatInput_returnPressed();//触发槽函数
}

//新消息到达添加到聊天列表
void MainWindow::newChatMsg(QString msg)
{
    QListWidgetItem *item = new QListWidgetItem(ui->chatWidget);
    item->setText(msg);
    ui->chatWidget->addItem(item);
    ui->chatWidget->scrollToBottom();   //滚动到底部
}

void MainWindow::durationChanged(qint64 duration)
{
    ui->seekSlider->setMaximum(duration);
    qDebug() << "当前播放源的时长是" << duration;
    int realSeconds = duration / 1000;
    int minutes = realSeconds / 60;
    int seconds = realSeconds % 60;
    QString textMinutes = QString::number(minutes);
    QString textSeconds = QString::number(seconds);
    if(minutes < 10)
    {
        textMinutes = "0" + textMinutes;
    }
    if(seconds < 10)
    {
        textSeconds = "0" + textSeconds;
    }
    ui->labelDuration->setText(textMinutes+":"+textSeconds);
}

void MainWindow::positionChanged(qint64 progress)
{
    ui->seekSlider->setValue(progress);
    int realSeconds = progress / 1000;
    int minutes = realSeconds / 60;
    int seconds = realSeconds % 60;
    QString textMinutes = QString::number(minutes);
    QString textSeconds = QString::number(seconds);
    if(minutes < 10)
    {
        textMinutes = "0" + textMinutes;
    }
    if(seconds<10)
    {
        textSeconds = "0" + textSeconds;
    }
    ui->labelPosition->setText(textMinutes + ":" + textSeconds + "  /");
}

//滑动条移动事件槽函数,用于视频同步
void MainWindow::seek(int mseconds)
{
    if (client)
    {
        //发送同步消息
        client->writeToServer("seek" + QString::number(mseconds), "snc");
        // sncseek+mseconds
    }
    else
    {
        player->setPosition(mseconds);
    }
}

void MainWindow::remotePlay(qint64 position)
{
    player->setPosition(position);
    player->play();
}

void MainWindow::remotePause(qint64 position)
{
    player->setPosition(position);
    player->pause();
}

void MainWindow::remoteStop()
{
    player->stop();
}

void MainWindow::remoteSeek(qint64 position)
{
    player->setPosition(position);
}

//视频同步
void MainWindow::remoteSync(qint64 position)
{
    //误差大于200ms时调整
    if (abs(player->position() - position) > 200)
    {
        player->setPosition(position);
    }
}

void MainWindow::remoteSetVideoSource(QString src)
{
    qDebug() << "MainWindow::设置播放源: " << src;
    player->setSource(QUrl(src));
    this->setWindowTitle("同步视频播放器  " + src);
}

void MainWindow::userConnected(QString usrName)
{
    QListWidgetItem *item = new QListWidgetItem(ui->participantsWidget);
    item->setText("* " + usrName);
    ui->participantsWidget->addItem(item);
}

void MainWindow::userDisconnected(QString usrName)
{
    for (int i=0; i < ui->participantsWidget->count(); i++)
    {
        if (ui->participantsWidget->item(i)->text() == "* " + usrName)
        {
            QListWidgetItem *item = ui->participantsWidget->takeItem(i);    //移除但不销毁
            delete item;
            item = nullptr;
            break;
        }
    }
}

void MainWindow::on_volumeSlider_valueChanged(int value)
{
    qDebug() << "当前音量的值是: " << value;
    audioOutput->setVolume(value / 100.0);
    ui->volumeLabel->setText(QString::number(value) + "%");
}

void MainWindow::readFromMicrophone()
{
    if (udpClient != nullptr)
    {
        udpClient->udpWriteToServer(udpAudioSourceDevice->readAll());
    }
    //udpAudioSinkDevice->write(udpAudioSourceDevice->readAll());
}


void MainWindow::voiceReceived(QByteArray data)
{
    if (!micMuted)
    {
        udpAudioSinkDevice->write(data);
    }
}

void MainWindow::on_muteButton_stateChanged(int arg1)
{
    if (udpAudioSource)
    {
        //UnChecked
        if (arg1 == 0)
        {
            micMuted=false;
            udpAudioSource->setVolume(0.2f);
        }
        //Checked
        if (arg1 == 2)
        {
            micMuted=true;
            udpAudioSource->setVolume(0.f);
        }
    }
}

//void MainWindow::handleBuffering(QMediaPlayer::MediaStatus status)
//{
//    if (buffering && player->bufferProgress() == 1.f)
//    {
//        qInfo() << "finished buffering";
//        buffering = false;
//        playPressed();
//    }
//    if (!buffering && !(player->bufferProgress() == 1.f))
//    {
//        qInfo() << "buffering";
//        buffering = true;
//        pausePressed();
//    }
//}

void MainWindow::on_actionObit_triggered()
{
    emit themeChanged("Obit");
}

void MainWindow::on_actionMyWatch_triggered()
{
    emit themeChanged("MyWatch");
}

void MainWindow::on_actionFilmovio_triggered()
{
    emit themeChanged("Filmovio");
}

void MainWindow::on_actionCombinear_triggered()
{
    emit themeChanged("Combinear");
}

void MainWindow::on_actionPerstfic_triggered()
{
    emit themeChanged("Perstfic");
}

void MainWindow::on_actionVisualScript_triggered()
{
    emit themeChanged("VisualScript");
}

void MainWindow::on_actionWstartpage_triggered()
{
    emit themeChanged("Wstartpage");
}

void MainWindow::hostLocalFile(QString file)
{
    qDebug() << "MainWindow::视频路径: " << file;
    QFileInfo info(file);
    QString directory = info.path();
    qDebug() << "MainWindow::当前文件夹是: " << directory;
    QString fileName = info.fileName();
    qDebug() << "MainWindow::视频文件名: " << fileName;
    if (client)
    {
        client->writeToServer(file, "srclcl");
        //srclcl+file
    }
    else
    {
        qDebug() << "MainWindow:本地播放";
        player->setSource(file);
        this->setWindowTitle("同步视频播放器  " + file);
    }
}

void MainWindow::slotOpenPath(const QString &filePath)
{
    readFile(filePath);
}

void MainWindow::remoteSetLocalVideoSource(QString src)
{
    qDebug() << "本地视频路径" << src;

    //D盘作为HTTP服务器的节点
    // 获取WLAN接口的IP地址以及端口

    QString serverURL = "http://" + client->getPeerIpAddress() + ":8080";
    QString replacePath = src.replace("\\", "/");
    qDebug() << "replacePath is " << replacePath;
    QUrl url = QUrl::fromLocalFile(replacePath);
    QString encodedPath = url.path(QUrl::FullyEncoded);  //进行百分号编码处理，适合HTTP路径
    qDebug() << "encodedPath is " <<encodedPath;
    if (encodedPath.startsWith("/"))
    {
        encodedPath = serverURL + encodedPath.mid(3); //去掉开头的/D:
    }
    qDebug() << "视频的HTTP路径: " << encodedPath;
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(encodedPath);
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]()
    {
        if(reply->error() == QNetworkReply::NoError)
        {
            qDebug() << "视频路径有效,开始播放";
            player->setSource(encodedPath);
            this->setWindowTitle("同步视频播放器  " + encodedPath);
        }
        else
        {
            qDebug() << "视频路径无效,无法播放";
            qDebug() << reply->errorString();
        }
        reply->deleteLater();
    });
}

void MainWindow::setServerURL(QUrl url)
{
    serverURL = url.toString();
    qDebug() << "serverURL is " << serverURL;
}

void MainWindow::on_action_Open_Directory_triggered()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setWindowTitle(tr("选择导入的文件夹"));
    fileDialog.setDirectory(QDir::currentPath());
    fileDialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if(!fileDialog.exec())
    {
        return;
    }
    fileNames=fileDialog.selectedFiles();
    if(fileNames.size() <= 0)
    {
        return;
    }
    QString importPath=fileNames.at(0);
    emit signalOpenPath(importPath);
}

void MainWindow::on_actOpenLocalFile_triggered()
{
    QString current = QDir::currentPath(); //获取当前路径
    QString filter = "视频文件(*.mp4  *.flv *.mkv)";
    QString filePath = QFileDialog::getOpenFileName(this,"打开文件",current,filter);
    if(filePath.isEmpty())
    {
        return;
    }
    emit setlocalFile(filePath);
}

