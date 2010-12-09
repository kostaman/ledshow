#include "progManage.h"
#include <QDockWidget>
#include <QPainter>
#include <QSettings>
#include "showArea.h"
#include "mainwindow.h"
#include <QLabel>

extern MainWindow *w;
extern QSettings settings;
/*
 QSettings��
 program
   |-00
   |-01
     |-area
        |-00
        |-01
           |-
 */
int checkItemType(QTreeWidgetItem *item)
{
    //QVariant QVar;

    QString QStr = item ->data(0,Qt::UserRole).toString();
/*
    if(QStr.contains("file"))
        return FILE_TYPE;
    else if(QStr.contains("area"))
        return AREA_TYPE;
    else if(QStr.contains("program"))
        return PROG_TYPE;
        */
    settings.beginGroup(QStr);
    int type = settings.value("type").toInt();
    settings.endGroup();
/*
    if(type == PROG_PROPERTY)
        return PROG_TYPE;
    else if(type == AREA_PROPERTY)
        return AREA_TYPE;
    else
        return FILE_TYPE;
        */
    return type;
}

void updateItemSubIndex(QTreeWidgetItem *item)
{
    QString QStr;
    QTreeWidgetItem *parent;
    int index,parentIndex;

    //parent = item ->parent();
    //parentIndex = parent->parent()->indexOfChild(parent);
    index = item->parent()->indexOfChild(item);//�ڸ���������
    //QStr = QString::number(parentIndex + 1) + QObject::tr("����");
    //QStr = QStr + "(" + QString::number(index + 1) + ")";
    //item->parent()->setText(0,QStr);//setText(QStr);

    QStr = (item->parent()->data(0,Qt::UserRole)).toString();
    settings.beginGroup(QStr);
    settings.setValue("subIndex", index + 1);
    settings.endGroup();

}

/*
#define HTXT_AREA  0x00 //���ı�
#define PIC_AREA   0x01 //ͼƬ
#define FLASH_AREA 0x02 //����
#define CLOCK_AREA 0x03 //����
#define TIME_AREA  0x04 //����ʱ��
#define TIMER_AREA 0x05 //��ʱ
#define TEMP_AREA  0x06 //�¶�
 */

void newAreaSettings(QString &groupName, int type)
{
    settings.beginGroup(groupName);
    if(type == PROG_PROPERTY)
    {
        settings.setValue("name", "new prog");//����
        settings.setValue("timerPlay", 0); //��ʱ����
        settings.setValue("weekPlay", 0); //���ڲ���
        settings.setValue("fixTimePlay", 0);  //��������-�̶�ʱ��
        //settings.setValue("", );
    }
    settings.endGroup();

}

//program����
CprogManage:: CprogManage(QWidget *parent):QDockWidget(tr("��Ŀ����"), parent)
{
  setAllowedAreas(Qt::LeftDockWidgetArea);
  treeWidget = new QTreeWidget(this);
  treeWidget->setHeaderHidden(true);//header()->setVisible(false);

  QObject::connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)),\
          this, SLOT(clickItem(QTreeWidgetItem *, int)));
  setWidget(treeWidget);

  settingsInit();
}

CprogManage::~CprogManage()
{


}
/*
#define PROG_PROPERTY 0x00
#define AREA_PROPERTY 0x01
#define PIC_PROPERTY    0x02 //ͼƬ
#define FLASH_PROPERTY  0x03 //����
#define CLOCK_PROPERTY  0x04 //����
#define TIME_PROPERTY   0x05 //����ʱ��
#define TIMER_PROPERTY  0x06 //��ʱ
#define TEMP_PROPERTY   0x07 //�¶�
*/

//�������ͻ�ö�Ӧ���ַ��������ַ���������ʾ,������Qsettngs��
QString getTypeString(int type)
{
    QString Qstr;

    if(type == PROG_PROPERTY)
        Qstr = QObject::tr("��Ŀ");
    else if(type == AREA_PROPERTY)
        Qstr = QObject::tr("����");
    else if(type == PIC_PROPERTY)
        Qstr = QObject::tr("ͼ��");
    else if(type == FLASH_PROPERTY)
        Qstr = QObject::tr("����");
    else if(type == CLOCK_PROPERTY)
        Qstr = QObject::tr("����");
    else if(type == TIME_PROPERTY)
        Qstr = QObject::tr("ʱ��");
    else if(type == TIMER_PROPERTY)
        Qstr = QObject::tr("��ʱ");
    else if(type == TEMP_PROPERTY)
        Qstr = QObject::tr("�¶�");
    else if(type == LUN_PROPERTY)
        Qstr = QObject::tr("ũ��");
    else
    {
        //ASSERT_FAILED();
        Qstr = "";
        //return "";
    }

    return Qstr;
}

//����parent����������ı���
//parentΪ0ʱ��ʾ���¶�����
//parent!=0��ʾ����parent����������
void CprogManage::updateTextHead(QTreeWidgetItem *parent)
{
    int count,type,subIndex,parentIndex;
    QString Qstr,str;
    QTreeWidgetItem *temp;

    if(parent == 0) //������
       count = treeWidget->topLevelItemCount();
    else
       count = parent->childCount();

    if(parent != 0)
    {
        type = checkItemType(parent);
        if(type == AREA_PROPERTY || type == PROG_PROPERTY)
        {
            str = parent->data(0, Qt::UserRole).toString();
            settings.beginGroup(str);
            subIndex = settings.value("subIndex").toInt();
            settings.endGroup();
            Qstr = Qstr + "(" + QString::number(subIndex) + ")";

            if(type == AREA_PROPERTY)
            {
              parentIndex = parent->parent()->indexOfChild(parent);
              parent->setText(0, QString::number(parentIndex + 1) + tr("����") + Qstr); //����text
            }
            else
            {
              parentIndex = treeWidget->indexOfTopLevelItem(parent);
              parent->setText(0, QString::number(parentIndex + 1) + tr("��Ŀ") + Qstr); //����text

            }
        }
    }/*
    else //��ǰΪ����
    {
        settings.beginGroup();
        subIndex = settings.value("subIndex").toInt();
        settings.endGroup();
        Qstr = Qstr + "(" + QString::number(subIndex) + ")";

        int parentIndex = parent->parent()->indexOfChild(parent);
        if(type == AREA_PROPERTY)
          parent->setText(0, QString::number(parentIndex + 1) + tr("����") + Qstr); //����text
        else
          parent->setText(0, QString::number(parentIndex + 1) + tr("��Ŀ") + Qstr); //����text

    }*/
    for(int i=0; i < count; i ++)
    {
        if(parent == (QTreeWidgetItem *)0)
           temp = treeWidget->topLevelItem(i); //������
        else
           temp = parent->child(i);

        int type = checkItemType(temp); //����

        Qstr = getTypeString(type); //�������ͻ�ö�Ӧ���ַ���
        if(type == AREA_PROPERTY || type == PROG_PROPERTY) //����
        {
            str = temp->data(0, Qt::UserRole).toString();
            settings.beginGroup(str);
            subIndex = settings.value("subIndex").toInt();
            settings.endGroup();
            Qstr = Qstr + "(" + QString::number(subIndex) + ")";
        }

        temp->setText(0, QString::number(i + 1) + Qstr); //����text
    }
}

// program/01
void CprogManage::newProg()
{
    int i,size;
    int max = 0,tmp;

    settings.beginGroup("program"); //����settings��program����
    QStringList groups = settings.childGroups(); //���н�Ŀ���б�

    size = groups.size();
    //qDebug("groups size = %d", size);
    for(i = 0; i < size; i ++)
    {
      tmp = groups.at(i).toInt();
      if(tmp > max)
          max=tmp;
    }
    max++;

    //qDebug("new prog %d",max);

    settings.beginGroup(QString::number(max));
    settings.setValue("subIndex", 0); //��ǰ�ӷ���
    settings.setValue("name", QString("new prog"));
    settings.setValue("type", PROG_PROPERTY);
    settings.setValue("setFlag", 0); //û���������
      //�����ڶ�ʱ
    settings.setValue("dateTimerCheck", 0);
    settings.setValue("startYear", 2010);
    settings.setValue("startMonth", 1);
    settings.setValue("startDay", 1);
    settings.setValue("endYear", 2010);
    settings.setValue("endMonth", 1);
    settings.setValue("endDay", 1);

    //�����ڶ�ʱ
    settings.setValue("weekTimerCheck", 0);
    settings.setValue("w0", 0);
    settings.setValue("w1", 0);
    settings.setValue("w2", 0);
    settings.setValue("w3", 0);
    settings.setValue("w4", 0);
    settings.setValue("w5", 0);
    settings.setValue("w6", 0);

    //��ʱ�䶨ʱ
    settings.setValue("timeCheck", 0);
    settings.setValue("startHour", 0);
    settings.setValue("startMin", 0);
    settings.setValue("endHour", 0);
    settings.setValue("endMin", 0);

    //��������
    settings.setValue("playTimeCheck", 0);
    settings.setValue("playTime", 0);

    //�߿�ѡ��
    settings.setValue("borderCheck", 0);
    settings.setValue("width", 1);
    settings.setValue("speed", 1);
    settings.setValue("style", 1);
    settings.setValue("color", 1);

    //qDebug("progs size = %d", settings.childGroups().size());
    settings.endGroup();
    settings.endGroup();

    QTreeWidgetItem* item = new QTreeWidgetItem(treeWidget);//QStringList(QString::number(size + 1)+tr("��Ŀ")));
    item->setData(0, Qt::UserRole, QVariant(QString("program") + "/" + QString::number(max)));

    treeWidget->addTopLevelItem(item);
    treeWidget->setCurrentItem(item);
    saveCurItem(item); //��ǰ���ӵ�

    updateTextHead(0);
    w->property->updateProperty(item);
    w->screenArea->updateShowArea(item);//  progSettingsInit(QStr);

}



//һ���µ�area����
// program/01/
void CprogManage::newArea()
{
    QTreeWidgetItem *curItem;
    QTreeWidgetItem *parentItem;
    QString QStr;
    int i,size,type,index;
    int max = 0,tmp;

    curItem = treeWidget->currentItem(); //��ǰ��ѡ�е���
    if(curItem == (QTreeWidgetItem *)0)
        return;

    settings.beginGroup("screen");
    int xLen = settings.value("xLen").toInt();
    int yLen = settings.value("yLen").toInt();
    settings.endGroup();

    type = checkItemType(curItem); //����Ŀ������?

    //�ҵ��÷�����Ӧ�Ľ�Ŀ��treeWidgetItem
    if(type == PROG_PROPERTY)
        parentItem = curItem;
    else if(type == AREA_PROPERTY)
        parentItem = curItem->parent();
    else
    {
      parentItem = (curItem ->parent())->parent();
    }

    QStr = (parentItem ->data(0,Qt::UserRole)).toString();
    QStr = QStr + "/" + QString(tr("area"));

    settings.beginGroup(QStr);
    QStringList groups = settings.childGroups(); //area�б�

    size = groups.size();
    for(i = 0; i < size; i ++)
    {
      tmp = groups.at(i).toInt();
      if(tmp > max)
          max=tmp;
    }
    max++;

    //����Ƿ����㹻��Area
    index = w->screenArea->checkEnoughArea();
    if(index <= 0)
        return;
    else
        index --;

    //��ʼ����������
    settings.beginGroup(QString::number(max));
    settings.setValue("subIndex", 0); //��������
    settings.setValue("name", QString("new area"));
    settings.setValue("type", AREA_PROPERTY);
    settings.setValue("setFlag", 0); //û���������
    settings.setValue("index", index);
    settings.setValue("x", size*(xLen / 20));  //�÷��������x
    settings.setValue("y", size*(yLen / 20));  //�÷��������y
    settings.setValue("xLen", xLen / 2);  //�÷����Ŀ��
    settings.setValue("yLen", yLen / 2);  //�÷����ĳ���
    settings.endGroup();
    settings.endGroup();

    QTreeWidgetItem* item = new QTreeWidgetItem(parentItem,QStringList(QString::number(size + 1)+tr("����")));
    item->setData(0, Qt::UserRole, QVariant(QStr + "/" + QString::number(max)));

    //w->setCurSettingsStr(QStr + "/" + QString::number(max));


    parentItem->addChild(item);
    treeWidget->setCurrentItem(item);
    saveCurItem(item);

    updateItemSubIndex(item);
    updateTextHead(item->parent());


    //w->property->stackedWidget->setCurrentIndex(AREA_PROPERTY);
    //w->property->setSettingsToWidget(QStr + "/" + QString::number(max), AREA_PROPERTY);
    w->property->updateProperty(item);
    w->screenArea->updateShowArea(item);//w->getCurSettingsStr());//��ʾһ������,�÷���֮ǰ��������״̬
}


void CprogManage::newPic() //��ͼ��
{
  newFile(PIC_PROPERTY);
}

void CprogManage::newFlash() //�¶���
{
  newFile(FLASH_PROPERTY);
}

void CprogManage::newTime() //������
{
  newFile(TIME_PROPERTY);
}

void CprogManage::newTimer() //�¼�ʱ
{
  newFile(TIMER_PROPERTY);
}

void CprogManage::newClock() //�±���
{
  newFile(CLOCK_PROPERTY);
}

void CprogManage::newTemp() //���¶�
{
  newFile(TEMP_PROPERTY);

}

void CprogManage::newLun() //��ũ��
{
  newFile(LUN_PROPERTY);
}

//һ���µ���ʾfile
void CprogManage::newFile(int fileType)
{
    QTreeWidgetItem *curItem;
    QTreeWidgetItem *parentItem;
    QString QStr;
    int i,size,type;
    int max = 0,tmp;

    curItem = treeWidget->currentItem(); //��ǰ��ѡ�е���
    if(curItem == (QTreeWidgetItem *)0)
        return;

    type = checkItemType(curItem); //����Ŀ������?

    if(type == PROG_PROPERTY)
    {
        return;
    }
    else if(type == AREA_PROPERTY) //area��
        parentItem = curItem;
    else
    {
      parentItem = curItem ->parent();
    }

    QStr = (parentItem ->data(0,Qt::UserRole)).toString();
    QStr = QStr + "/" + QString(tr("file"));

    settings.beginGroup(QStr);
    QStringList groups = settings.childGroups(); //area�б�

    size = groups.size();
    for(i = 0; i < size; i ++)
    {
      tmp = groups.at(i).toInt();
      if(tmp > max)
          max=tmp;
    }
    max++;
    settings.beginGroup(QString::number(max));
    settings.setValue("type", fileType);
    settings.setValue("setFlag", 0); //û���������
    settings.endGroup();
    settings.endGroup();

    //w->setCurSettingsStr(QStr + "/" + QString::number(max));

    QTreeWidgetItem* item = new QTreeWidgetItem(parentItem,QStringList(QString::number(max)));
    item->setData(0, Qt::UserRole, QVariant(QStr + "/" + QString::number(max)));
    parentItem->addChild(item);
    treeWidget->setCurrentItem(item);
    saveCurItem(item);

    updateItemSubIndex(item);
    updateTextHead(item->parent());
    //w->property->stackedWidget->setCurrentIndex(fileType);
    //w->property->setSettingsToWidget(QStr + "/" + QString::number(max), fileType);


    /*
    QStr = (parentItem ->data(0,Qt::UserRole)).toString();
    settings.beginGroup(QStr);
    settings.setValue("subIndex", size);
    settings.endGroup();

    int index = parentItem->parent()->indexOfChild(parentItem);//�ڸ���������
    QStr = QString::number(index + 1) + QString(tr("����"));
    QStr = QStr + "(" + QString::number(size + 1) + ")";
    parentItem->setText(0,QStr);//setText(QStr);
*/
    w->property->updateProperty(item);
    w->screenArea->updateShowArea(item);//  progSettingsInit(QStr);
}

//ɾ����Ŀ
void CprogManage::deleteItem()
{
    QTreeWidgetItem *curItem;
    QVariant Qvar;
    int index;

    curItem = treeWidget->currentItem(); //��ǰ��ѡ�е���
    if(curItem == 0)
        return;

    Qvar = curItem->data(0, Qt::UserRole);
    if(checkItemType(curItem) != PROG_PROPERTY)
    {
        if(checkItemType(curItem) == AREA_PROPERTY)
        {
            settings.beginGroup(Qvar.toString());

            int index = settings.value("index").toInt();
            if(index < MAX_AREA_NUM)
                w->screenArea->setAreaVisible(index, 0);
            else
                ASSERT_FAILED();

            settings.endGroup();
        }

        QTreeWidgetItem *parent = curItem->parent();
        curItem->parent()->removeChild(curItem);
        //updateItemSubIndex(cur)
        updateTextHead(parent);

    }
    else
    {
        index = treeWidget->indexOfTopLevelItem(curItem);
        treeWidget->takeTopLevelItem(index);
        updateTextHead(0);
    }

    settings.beginGroup(Qvar.toString());
    settings.remove("");
    settings.endGroup();
    //settings.remove(Qvar.toString());//ɾ�������

    //qDebug("remove : %s", (const char *)(Qvar.toString().toLocal8Bit()));
    curItem = treeWidget->currentItem(); //��ǰ��ѡ�е���
    if(curItem == 0)
    {
        for(int i = 0; i < MAX_AREA_NUM; i ++)
            w->screenArea->setAreaVisible(i, 0);
        return;
    }

    saveCurItem(0); //ɾ����ǰû�е�����
    w->progManage->clickItem(curItem, 0);
}

//���
void CprogManage::clickItem(QTreeWidgetItem *item, int column)
{
    int type;
    QString QStr;
    QTreeWidgetItem *lastItem;

    lastItem = getCurItem();

    if(lastItem == item) //ͬһ����Ŀ���
        return;

    if(lastItem != (QTreeWidgetItem *)0)
    {
       w->property->getSettingsFromWidget(lastItem);
    }

    saveCurItem(item);

    type = checkItemType(item);
    if(type != PROG_PROPERTY) //&& type != AREA_PROPERTY) //�Ȳ��ǽ�ĿҲ���Ƿ���
    {
        //int index =
        //QString str = item->parent()->data(0, Qt::UserRole).toString();
        updateItemSubIndex(item);
        updateTextHead(item->parent());
        if(type != AREA_PROPERTY)
        {
          updateItemSubIndex(item->parent());        //updateItemSubIndex(item);
          updateTextHead(item->parent()->parent());
        }
    }

    treeWidget->setCurrentItem(item);//setCurrentItem()
    w->property->updateProperty(item);
    w->screenArea->updateShowArea(item);
}

//progManage�е�treeWidget�ĳ�ʼ��,����settings���г�ʼ��
void CprogManage::settingsInit()
{
    int progSize, fileSize;
    QStringList progGroups, areaGroups, fileGroups;

    treeWidget->clear();
    settings.beginGroup("program");
    progGroups = settings.childGroups(); //��Ŀ�б�
    progSize = progGroups.size(); //��Ŀ����

    for(int i = 0; i < progSize; i ++)
    {
        QTreeWidgetItem *progItem = new QTreeWidgetItem(treeWidget);
        QString progStr = QString("program") + "/" + progGroups.at(i);
        progItem->setData(0, Qt::UserRole, progStr);
        progItem->setText(0, QString::number(i + 1) + tr("��Ŀ"));
        treeWidget->addTopLevelItem(progItem);

        settings.beginGroup(progGroups.at(i) + "/area");
        areaGroups = settings.childGroups(); //�б�
        //areaSize = areaGroups.size();
        //qDebug("set %d prog %s, area size = %d", i, progGroups.at(i), areaSize);

        for(int j = 0; j < areaGroups.size(); j ++)
        {
            QTreeWidgetItem *areaItem = new QTreeWidgetItem(progItem);
            QString areaStr = progStr + "/area/" + areaGroups.at(j);
            areaItem->setData(0, Qt::UserRole, areaStr);
            areaItem->setText(0, QString::number(j + 1) + tr("����"));
            progItem->addChild(areaItem);

            settings.beginGroup(areaGroups.at(j) + "/file");
            fileGroups = settings.childGroups(); //�б�
            fileSize = fileGroups.size();
            //qDebug("set %d area %s, file size = %d", j, areaGroups.at(i), fileSize);

            for(int k = 0; k < fileSize; k ++)
            {
                QTreeWidgetItem *fileItem = new QTreeWidgetItem(areaItem);
                QString fileStr = areaStr + "/file/" + fileGroups.at(k);
                fileItem->setData(0, Qt::UserRole, fileStr);

                settings.beginGroup(fileGroups.at(k));
                int type = settings.value("type").toInt();
                QString name = getTypeString(type);
                fileItem->setText(0, QString::number(k + 1) + name);
                areaItem->addChild(fileItem);

                settings.endGroup();
                //qDebug("set %d file %s", k, fileGroups.at(i));
            }
            settings.endGroup();
         }
        settings.endGroup();
    }
    settings.endGroup();

    if(treeWidget->topLevelItemCount()>0)
    {
        treeWidget->setCurrentItem(treeWidget->topLevelItem(0)); //���õ�һ��itemΪ��ǰ����

        for(int i = 0; i <treeWidget->topLevelItemCount(); i ++)
        {
            QTreeWidgetItem *progItem;

            progItem = treeWidget->topLevelItem(i);
            updateTextHead(progItem);
            for(int j = 0; j<progItem->childCount(); j ++)
            {
                QTreeWidgetItem *areaItem;

                areaItem =progItem->child(j);
                updateTextHead(areaItem);
            }
        }

        saveCurItem(0);
        //clickItem(treeWidget->topLevelItem(0), 0);
   }
}

//��ȡ��ǰsettings��str
QTreeWidgetItem * CprogManage::getCurItem()
{
    return curItem;
}

//���õ�ǰ������settings��str
void CprogManage::saveCurItem(QTreeWidgetItem *item)
{
    curItem = item;
}
