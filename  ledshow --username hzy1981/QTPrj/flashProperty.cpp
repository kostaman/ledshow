#include <QFileDialog>
#include <QSettings>
#include <QMovie>
#include "mainwindow.h"
#include "flashProperty.h"

extern MainWindow *w;
extern QSettings settings;

#define FLASH_MIN_VALUE 150
#define FLASH_MAX_VALUE 250
/*
//flash���Դ�
class CflashProperty:public QWidget
{
    Q_OBJECT
private:
    QLabel *flashSourceLabel; //flashԴ��־
    QLineEdit *flashSourceEdit; //flashԴ�༭��
    QPushButton *openButton; //�򿪰�ť

    QLabel *frameNumLabel; //֡����־
    QLineEdit *frameNumEdit; //֡���༭
    QLabel *runSpeedLabel; //�����ٶȱ�־
    QLineEdit *runSpeedCheck; //�����ٶȱ༭
    QLabel *speedUnitLabel; //�ٶȵ�λ

    QLabel *totalFrameNumLabel; //��֡��


public:
    CflashProperty(QWidget *parent=0);
    ~CflashProperty();
};
*/
//flash���Ա༭
CflashProperty::CflashProperty(QWidget *parent):QWidget(parent)
{
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;
    QGridLayout *gridLayout;
    hLayout = new QHBoxLayout(this);
    vLayout = new QVBoxLayout(this);


    area = new Carea(this);
    nameEdit = new CnameEdit(this);

    vLayout->addWidget(nameEdit);
    vLayout->addWidget(area);
    hLayout->addLayout(vLayout);
    //setLayout(vLayout);

    groupBox = new QGroupBox(tr("������Ϣ"),this);

   flashSourceLabel = new QLabel(tr("�����ļ�"), this);
   flashSourceEdit = new QLineEdit(this);
   openButton = new QPushButton(tr("��"), this);

   totalFrameNumLabel = new QLabel(tr("��֡��"), this);
   totalFrameNumEdit = new QLineEdit(this);

   frameNumLabel = new QLabel(tr("��ȡ֡��"), this);
   frameNumEdit = new QSpinBox(this);

   runSpeedLabel = new QLabel(tr("�����ٶ�"), this);
   runSpeedCheck = new QComboBox(this);
   speedUnitLabel = new QLabel(tr("΢��"), this);

   runSpeedCheck->addItem(tr("0���"));
   runSpeedCheck->addItem(tr("1"));
   runSpeedCheck->addItem(tr("2"));
   runSpeedCheck->addItem(tr("3"));
   runSpeedCheck->addItem(tr("4"));
   runSpeedCheck->addItem(tr("5"));
   runSpeedCheck->addItem(tr("6"));
   runSpeedCheck->addItem(tr("7"));
   runSpeedCheck->addItem(tr("8"));
   runSpeedCheck->addItem(tr("9����"));


   flashSourceEdit->setEnabled(false);
   totalFrameNumEdit->setEnabled(false);

   totalFrameNumEdit->setFixedWidth(40);
   frameNumEdit->setFixedWidth(40);

   gridLayout = new QGridLayout(this);
   gridLayout->addWidget(flashSourceLabel, 0, 0);
   gridLayout->addWidget(flashSourceEdit, 0, 1,1,5);
   gridLayout->addWidget(openButton, 0, 6);

   gridLayout->addWidget(totalFrameNumLabel, 1, 0);
   gridLayout->addWidget(totalFrameNumEdit, 1, 1);
   gridLayout->addWidget(frameNumLabel, 1, 2);
   gridLayout->addWidget(frameNumEdit, 1, 3);
   gridLayout->addWidget(runSpeedLabel, 1, 4);
   gridLayout->addWidget(runSpeedCheck, 1, 5);
   gridLayout->addWidget(speedUnitLabel, 1, 6);
   groupBox->setLayout(gridLayout);

   vLayout = new QVBoxLayout(this);
   vLayout->addWidget(groupBox);
   hLayout->addLayout(vLayout);

   hLayout->addStretch(10);
   setLayout(hLayout);

   connect(openButton, SIGNAL(clicked()), this, SLOT(openFlashFile()));
}

void CflashProperty::openFlashFile()
{
    CshowArea *area;
    QTreeWidgetItem *item;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.png *.xpm *.jpg *.gif)"));
    if(fileName.isEmpty() == false)
    {
        flashSourceEdit->setText(fileName);
        QMovie *movie = new QMovie(fileName);
        totalFrameNumEdit->setText(QString::number(movie->frameCount()));


        area = w->screenArea->getFocusArea(); //��ǰ�������

        if(area != (CshowArea *)0) //
        {
            //��ǰѡ�е�item
            item = area->fileItem;//w->progManage->treeWidget->currentItem();////// //w->progManage->treeWidget->currentItem();
            if(item != (QTreeWidgetItem *)0)
            {
                QString str = item->data(0,Qt::UserRole).toString();
                getSettingsFromWidget(str);
                //getFlashParaFromSettings(str, area->filePara);
                updateFlashShowArea(area);
            }
        }

  }
}

void getFlashParaFromSettings(QString str, U_File_Para &para)
{
   para.Temp_Para.Flag = SHOW_FLASH;
}

CflashProperty::~CflashProperty()
{

}

//ˢ����ʾ����
void updateFlashShowArea(CshowArea *area)
{
    //CshowArea *area;
    QString str;
    QTreeWidgetItem *item;

    if(area != (CshowArea *)0) //
    {
        item = area->fileItem;
        str = item->data(0,Qt::UserRole).toString();

        getFlashParaFromSettings(str,area->filePara);

        settings.beginGroup(str);
        QMovie *movie = new QMovie(settings.value("fileName").toString());
        settings.endGroup();
        //totalFrameNumEdit->setText(QString::number(movie->frameCount()));
        movie->jumpToFrame(0);

        area->imageBk = movie->currentImage();
        area->imageBk.save("d:\\flash.png");
        area->updateFlag = true;
        //area->imageBk = getTextEditImage(MLINE_MODE, area->width(), area->height(), str, 0);

        //qDebug("file_para flag = %d", area->File_Para.Temp_Para.Flag);
        area->update(); //ˢ����ʾ

    }
    else
    {
        ASSERT_FAILED();
    }

}
void CflashProperty::getSettingsFromWidget(QString str)
{
  settings.beginGroup(str);
  settings.setValue("fileName", flashSourceEdit->text());
  settings.setValue("speed", runSpeedCheck->currentIndex());
  settings.endGroup();

  nameEdit->getSettingsFromWidget(str);
}

void CflashProperty::setSettingsToWidget(QString str)
{
    settings.beginGroup(str);
    flashSourceEdit->setText(settings.value("fileName").toString());
    runSpeedCheck->setCurrentIndex(settings.value("speed").toInt());
    settings.endGroup();

    if(flashSourceEdit->text().isEmpty() == false)
    {
        QMovie *movie = new QMovie(flashSourceEdit->text());
        totalFrameNumEdit->setText(QString::number(movie->frameCount()));
    }

    nameEdit->setSettingsToWidget(str);
}

QSize getFlashShowData(QImage image, S_Show_Data *pDst, INT16U x, INT16U y)
{
    /*
  QSize size;
  QRgb rgb,r,g,b,ye;
  int i,j;

  for(i = 0; i < image.width(); i ++)
      for(j = 0; j < image.height(); j ++)
      {
        rgb = image.pixel(i,j);
        r = qRed(rgb);
        g = qGreen(rgb);
        b = qBlue(rgb);
        //ye = QColor(rgb).yellow();
        if(r > FLASH_VALUE && g>FLASH_VALUE && b <FLASH_VALUE)
        {
            Set_Area_Point_Data(pDst, 0, x + i, y + j, 0x04);
            //qDebug("yellow");
        }
        else if(r > FLASH_VALUE)// && g<FLASH_VALUE && b <FLASH_VALUE)
        {
            Set_Area_Point_Data(pDst, 0, x + i, y + j, 0x01);
            //qDebug("red");
        }
        else if(g > FLASH_VALUE)// && r < FLASH_VALUE && b <FLASH_VALUE)
        {
            Set_Area_Point_Data(pDst, 0, x + i, y + j, 0x02);
            //qDebug("green");
        }

        else //if((r == 0 && g == 0 && b == 0) || rgb == 0xFF7F9DB9)
        {
            Set_Area_Point_Data(pDst, 0, x + i, y + j, 0x00);
            //qDebug("black");
        }

      }
  size.setWidth(image.width());
  size.setHeight(image.height());
  return size;
*/
    QSize size;
    QRgb rgb,r,g,b,ye;
    int i,j;

    for(i = 0; i < image.width(); i ++)
        for(j = 0; j < image.height(); j ++)
        {
          rgb = image.pixel(i,j);
          r = qRed(rgb);
          g = qGreen(rgb);
          b = qBlue(rgb);
          //ye = QColor(rgb).yellow();
          if(r > FLASH_MIN_VALUE && r < FLASH_MAX_VALUE &&
             g > FLASH_MIN_VALUE && g < FLASH_MAX_VALUE &&
             b > 35 && b < 165)
          {
              Set_Area_Point_Data(pDst, 0, x + i, y + j, 0x04);
              //qDebug("yellow");
          }
          else if(r > FLASH_MIN_VALUE && r < FLASH_MAX_VALUE)// && g<FLASH_VALUE && b <FLASH_VALUE)
          {
              Set_Area_Point_Data(pDst, 0, x + i, y + j, 0x01);
              //qDebug("red");
          }
          else if(g > FLASH_MIN_VALUE && g < FLASH_MAX_VALUE)// && r < FLASH_VALUE && b <FLASH_VALUE)
          {
              Set_Area_Point_Data(pDst, 0, x + i, y + j, 0x02);
              //qDebug("green");
          }

          else //if((r == 0 && g == 0 && b == 0) || rgb == 0xFF7F9DB9)
          {
              Set_Area_Point_Data(pDst, 0, x + i, y + j, 0x00);
              //qDebug("black");
          }

        }
    size.setWidth(image.width());
    size.setHeight(image.height());
    return size;
}
