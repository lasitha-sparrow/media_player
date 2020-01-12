#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //this->setStyleSheet("background-color: rgb(85, 85, 127);");

    player = new QMediaPlayer(this);


    vw = new QVideoWidget(this);


    player->setVideoOutput(vw);

    this->setCentralWidget(vw);

    slider = new QSlider(this);

    bar = new QProgressBar(this);


    slider->setOrientation(Qt::Horizontal);

    ui->statusBar->addPermanentWidget(slider);
    ui->statusBar->addPermanentWidget(bar);

    connect(player, &QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);


    connect(player, &QMediaPlayer::positionChanged,slider,&QSlider::setValue);

    //set the playback position of the current media
    connect(slider, &QSlider::sliderMoved,player,&QMediaPlayer::setPosition);

    //set the maxium value of progress bar
    connect(player, &QMediaPlayer::durationChanged,bar,&QProgressBar::setMaximum);

    //hold the progress bar current value
    connect(player, &QMediaPlayer::positionChanged,bar,&QProgressBar::setValue);

    //create the volume slider
    slider = new QSlider(this);

    //
    slider->setOrientation(Qt::Vertical);

    //slider add to the video widget
    ui->statusBar->addPermanentWidget(slider);

    //set the slider's volume, min to max and max to min
    slider->setRange(0, 100);

    //set the current play back volume
    connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setVolume);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    //set the file selection directions
    QString filename = QFileDialog::getOpenFileName(this, "Open a file", "", "Video File (*.*)");
    //call the stop method
    on_actionStop_triggered(); //(*.avi, *.mpg, *.mp4)

    //get the url from local file and set to the media
    player->setMedia(QUrl::fromLocalFile(filename));

    //call the play method
    on_actionPlay_triggered();
}

void MainWindow::on_actionPlay_triggered()
{
    //call the play method
    player->play();
    //set the message
    ui->statusBar->showMessage("Playing");
}

void MainWindow::on_actionPause_triggered()
{
    //calling pause method
    player->pause();
    //set the message
    ui->statusBar->showMessage("Paused...");
}

void MainWindow::on_actionStop_triggered()
{
    //calling stop method
    player->stop();
    //set the message
    ui->statusBar->showMessage("Stopped");
}

void MainWindow::on_horizontalSlider_actionTriggered(int position)
{
    //call the play back postion of the current media
    player->setPosition(position);
}

void MainWindow::on_possitionChanged(qint64 position)
{
    //call the slider's current value
    ui->horizontalSlider->setValue(position);
}

void MainWindow::on_durationChanged(qint64 position)

{
   //call the sliders maxium value
    ui->horizontalSlider->setMaximum(position);
}

void MainWindow::on_sliderVolume_sliderMoved(int position)
{
    //set current media volume postion
    player->setPosition(position);
}

void MainWindow::on_actionOpenUrl_triggered()
{
    on_actionStop_triggered();
    QString url =
            QInputDialog::getText(this, tr("Open Url"), tr("Enter the video Url bellow "));
    if (url.isEmpty())
        return;
    player= new QMediaPlayer(this);
}


