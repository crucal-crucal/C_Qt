#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSlider>
#include <QAudioOutput>
#include <QTime>
#include <QPushButton>

class playbackwidget : public QWidget{
  public:
    explicit playbackwidget();
    ~playbackwidget();
    
  private:
    void createCtrl();
    void layout();
    void initConnection();
    
  private:  
};
