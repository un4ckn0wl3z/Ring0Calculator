#include "AboutWidget.h"
#include <QMediaPlayer>
#include <QAudioOutput>

AboutWidget::AboutWidget(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::AboutWidgetClass())
{
	ui->setupUi(this);
	QMediaPlayer *player = new QMediaPlayer(this);
	QAudioOutput *audioOutput = new QAudioOutput(this);
	player->setAudioOutput(audioOutput);
	player->setSource(QUrl::fromLocalFile("qrc:/Ring0Calculator/sound/kenet-rez-unreal-super-hero.mp3"));
	audioOutput->setVolume(50);
	player->play();
}

AboutWidget::~AboutWidget()
{
	delete ui;
}
