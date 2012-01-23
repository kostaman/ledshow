/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include "textedit.h"

#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFontComboBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextCodec>
#include <QTextEdit>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QtDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QTextEdit>
#include <QTextTable>
#include <QImage>
#include <QSettings>
#include <QTextBrowser>
#include <QAbstractTextDocumentLayout>
#include <QTextDocumentFragment>
#include <QRgb>
#include <QDialog>
#include <QTextLayout>
#include "showArea.h"
#include "mainwindow.h"
/*
#ifdef Q_WS_MAC
const QString rsrcPath = ":/images/mac";
#else
const QString rsrcPath = ":/images/win";
#endif
*/
extern MainWindow *w;
extern QSettings settings;

#define LINE_POSI_ADJ 2
#define TEXT_LEFT_BORDER_WIDTH 4
#define TEXT_RIGHT_BORDER_WIDTH 4

int linePosi[MAX_LINE_NUM];
int pagePosi[MAX_LINE_NUM];

CtextEdit::CtextEdit(QWidget *parent): QTextEdit(parent)
{

}

TextEdit::TextEdit(QWidget *parent, int mode)
    : QMainWindow(parent)
{
    editMode = mode;
    //setWindowFlags(windowFlags() | Qt::WType_TopLevel);
    setWindowModality(Qt::WindowModal);//Qt::WindowModal
    setToolButtonStyle(Qt::ToolButtonFollowStyle);
    setupFileActions();
    setupEditActions();
    setupTextActions();
    setupTableActions();
/*
    {
        QMenu *helpMenu = new QMenu(tr("Help"), this);
        menuBar()->addMenu(helpMenu);
        helpMenu->addAction(tr("About"), this, SLOT(about()));
        helpMenu->addAction(tr("About &Qt"), qApp, SLOT(aboutQt()));
    }
*/
    textEdit = new CtextEdit(this);
    connect(textEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat)),
            this, SLOT(currentCharFormatChanged(QTextCharFormat)));
    connect(textEdit, SIGNAL(cursorPositionChanged()),
            this, SLOT(cursorPositionChanged()));

    setCentralWidget(textEdit);
    textEdit->setFocus();
    setCurrentFileName(QString());

    fontChanged(textEdit->font());

    //textEdit->setTextColor(colorCombo->getColor());
    //colorChanged(colorCombo->getColor());

    alignmentChanged(textEdit->alignment());

    //connect(textEdit->document(), SIGNAL(modificationChanged(bool)),
            //actionSave, SLOT(setEnabled(bool)));
    /*
    connect(textEdit->document(), SIGNAL(modificationChanged(bool)),
            this, SLOT(setWindowModified(bool)));
    */
    connect(textEdit->document(), SIGNAL(undoAvailable(bool)),
            actionUndo, SLOT(setEnabled(bool)));
    connect(textEdit->document(), SIGNAL(redoAvailable(bool)),
            actionRedo, SLOT(setEnabled(bool)));

    setWindowModified(textEdit->document()->isModified());
    actionSave->setEnabled(true);//textEdit->document()->isModified());
    actionUndo->setEnabled(textEdit->document()->isUndoAvailable());
    actionRedo->setEnabled(textEdit->document()->isRedoAvailable());

    connect(actionUndo, SIGNAL(triggered()), textEdit, SLOT(undo()));
    connect(actionRedo, SIGNAL(triggered()), textEdit, SLOT(redo()));

    actionCut->setEnabled(false);
    actionCopy->setEnabled(false);

    connect(actionCut, SIGNAL(triggered()), textEdit, SLOT(cut()));
    connect(actionCopy, SIGNAL(triggered()), textEdit, SLOT(copy()));
    connect(actionPaste, SIGNAL(triggered()), textEdit, SLOT(paste()));

    connect(textEdit, SIGNAL(copyAvailable(bool)), actionCut, SLOT(setEnabled(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)), actionCopy, SLOT(setEnabled(bool)));


#ifndef QT_NO_CLIPBOARD
    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));
#endif
/*
    QString initialFile = ":/example.html";
    const QStringList args = QCoreApplication::arguments();
    if (args.count() == 2)
        initialFile = args.at(1);

    if (!load(initialFile))
        fileNew();
*/
    //connect(textEdit, SIGNAL(textChanged()), this, SLOT(edit())); //�ı������仯�򴥷��¼�
    //textEdit->clear();
    //QColor color = new QColor();
    palette = new QPalette(QPalette::Base,QColor(Qt::black));
    textEdit->setPalette(*palette);//->setPalette(palette);

    setWindowTitle(tr("�༭��"));
}

void TextEdit::closeEvent(QCloseEvent *e)
{
    //if (maybeSave())
        e->accept();
    //else
        //e->ignore();
}

void TextEdit::showEvent(QShowEvent *event)
{
  move((w->width() - width())/2, (w->height() - height())/2);
}

void TextEdit::setupFileActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("File Actions"));
    addToolBar(tb);

    QMenu *menu = new QMenu(tr("�ļ�"), this);
    menuBar()->addMenu(menu);

    QAction *a;

    QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction( newIcon, tr("�½�"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(QIcon::fromTheme("document-open", QIcon(rsrcPath + "/fileopen.png")),
                    tr("����..."), this);
    a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    tb->addAction(a);
    menu->addAction(a);

    menu->addSeparator();

    actionSave = a = new QAction(QIcon::fromTheme("document-save", QIcon(rsrcPath + "/filesave.png")),
                                 tr("����"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
    //a->setEnabled(false);
    tb->addAction(a);
    menu->addAction(a);
/*
    a = new QAction(tr("���Ϊ"), this);
    a->setPriority(QAction::LowPriority);
    connect(a, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
    menu->addAction(a);*/
    menu->addSeparator();
/*
#ifndef QT_NO_PRINTER
    a = new QAction(QIcon::fromTheme("document-print", QIcon(rsrcPath + "/fileprint.png")),
                    tr("&Print..."), this);
    a->setPriority(QAction::LowPriority);    
    a->setShortcut(QKeySequence::Print);
    connect(a, SIGNAL(triggered()), this, SLOT(filePrint()));
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(QIcon::fromTheme("fileprint", QIcon(rsrcPath + "/fileprint.png")),
                    tr("Print Preview..."), this);
    connect(a, SIGNAL(triggered()), this, SLOT(filePrintPreview()));
    menu->addAction(a);

    a = new QAction(QIcon::fromTheme("exportpdf", QIcon(rsrcPath + "/exportpdf.png")),
    tr("&Export PDF..."), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(Qt::CTRL + Qt::Key_D);
    connect(a, SIGNAL(triggered()), this, SLOT(filePrintPdf()));
    tb->addAction(a);
    menu->addAction(a);

    menu->addSeparator();
#endif
*/
    a = new QAction(tr("�˳�"), this);
    a->setShortcut(Qt::CTRL + Qt::Key_Q);
    connect(a, SIGNAL(triggered()), this, SLOT(close()));
    menu->addAction(a);
}

void TextEdit::setupEditActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("Edit Actions"));
    addToolBar(tb);
    QMenu *menu = new QMenu(tr("�༭"), this);
    menuBar()->addMenu(menu);

    QAction *a;
    a = actionUndo = new QAction(QIcon::fromTheme("edit-undo", QIcon(rsrcPath + "/editundo.png")),
                                              tr("ȡ��"), this);
    a->setShortcut(QKeySequence::Undo);
    tb->addAction(a);
    menu->addAction(a);
    a = actionRedo = new QAction(QIcon::fromTheme("edit-redo", QIcon(rsrcPath + "/editredo.png")),
                                              tr("����"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Redo);
    tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();
    a = actionCut = new QAction(QIcon::fromTheme("edit-cut", QIcon(rsrcPath + "/editcut.png")),
                                             tr("����"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Cut);
    tb->addAction(a);
    menu->addAction(a);
    a = actionCopy = new QAction(QIcon::fromTheme("edit-copy", QIcon(rsrcPath + "/editcopy.png")),
                                 tr("����"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Copy);
    tb->addAction(a);
    menu->addAction(a);
    a = actionPaste = new QAction(QIcon::fromTheme("edit-paste", QIcon(rsrcPath + "/editpaste.png")),
                                  tr("ճ��"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Paste);
    tb->addAction(a);
    menu->addAction(a);
#ifndef QT_NO_CLIPBOARD
    actionPaste->setEnabled(!QApplication::clipboard()->text().isEmpty());
#endif
}
/*
*actionInsertTable, //������
*actionInsertRowAbove;
*actionInsertRowBelow;
*actionInsertColumnLeft;
*actionInsertColumnRight;
*actionSelectTable;
*actionSelectRow;
*actionSelectColumn;
*actionDeleteTable;
*actionDeleteRow;
*actionDeleteColumn;
*actionTableProperty;
*/
void TextEdit::setupTableActions()
{

    if(editMode EQ 0) //�ı���ʽ��û�б��
        return;

    tablePropertyEdit = new CtablePropertyEdit(this);

    menuTable = new QMenu(tr("���"), this);
    menuBar()->addMenu(menuTable);

    menuInsert = new QMenu(tr("����"), menuTable);
    actionInsertTable = new QAction(tr("�±��"), this);
    actionInsertTable->setPriority(QAction::LowPriority);
    connect(actionInsertTable, SIGNAL(triggered()), tablePropertyEdit, SLOT(show()));//SLOT(textBold()));
    menuInsert->addAction(actionInsertTable);


    actionInsertRowAbove = new QAction(tr("�ϲ���һ��"),this);
    //connect(actionInsertTable, SIGNAL(triggered()), this, SLOT(textBold()));
    menuInsert->addAction(actionInsertRowAbove);

    actionInsertRowBelow = new QAction(tr("�²���һ��"),this);
    //connect(actionInsertTable, SIGNAL(triggered()), this, SLOT(textBold()));
    menuInsert->addAction(actionInsertRowBelow);

    actionInsertColumnLeft = new QAction(tr("�����һ��"),this);
    //connect(actionInsertTable, SIGNAL(triggered()), this, SLOT(textBold()));
    menuInsert->addAction(actionInsertColumnLeft);

    actionInsertColumnRight = new QAction(tr("�Ҳ���һ��"),this);
    //connect(actionInsertTable, SIGNAL(triggered()), this, SLOT(textBold()));
    menuInsert->addAction(actionInsertColumnRight);

    menuDelete = new QMenu(tr("ɾ��"), menuTable);
    actionDeleteTable = new QAction(tr("ɾ�����"), this);
    actionDeleteTable->setPriority(QAction::LowPriority);
    //connect(actionInsertTable, SIGNAL(triggered()), this, SLOT(textBold()));
    menuDelete->addAction(actionDeleteTable);

    actionDeleteRow = new QAction(tr("ɾ����"), this);
    actionDeleteRow->setPriority(QAction::LowPriority);
    //connect(actionInsertTable, SIGNAL(triggered()), this, SLOT(textBold()));
    menuDelete->addAction(actionDeleteRow);

    actionDeleteColumn = new QAction(tr("ɾ����"), this);
    actionDeleteColumn->setPriority(QAction::LowPriority);
    //connect(actionInsertTable, SIGNAL(triggered()), this, SLOT(textBold()));
    menuDelete->addAction(actionDeleteColumn);

    actionTableProperty = new QAction(tr("����"), this);
    actionTableProperty->setPriority(QAction::LowPriority);
    //connect(actionInsertTable, SIGNAL(triggered()), this, SLOT(textBold()));

    menuTable->addAction(menuInsert->menuAction());
    menuTable->addAction(menuDelete->menuAction());
    menuTable->addAction(actionTableProperty);

    connect(menuTable, SIGNAL(aboutToShow()), this, SLOT(setupTableMenu()));
    connect(actionInsertTable, SIGNAL(triggered()), this, SLOT(tableNew()));
    connect(actionTableProperty, SIGNAL(triggered()),this,SLOT(tableProperties()));
    /*
    connect(mw->ui.actionTableProperty, SIGNAL(triggered()), this, SLOT(tableProperties()));
    connect(mw->ui.actionDeleteTable, SIGNAL(triggered()), this, SLOT(tableDelete()));
    connect(mw->ui.actionInsertRowAbove, SIGNAL(triggered()), this, SLOT(rowInsertAbove()));
    connect(mw->ui.actionInsertRowBelow, SIGNAL(triggered()), this, SLOT(rowInsertBelow()));
    connect(mw->ui.actionDeleteRow, SIGNAL(triggered()), this, SLOT(rowDelete()));
    connect(mw->ui.actionInsertColumnLeft, SIGNAL(triggered()), this, SLOT(columnInsertLeft()));
    connect(mw->ui.actionInsertColumnRight, SIGNAL(triggered()), this, SLOT(columnInsertRight()));
    connect(mw->ui.actionDeleteColumn, SIGNAL(triggered()), this, SLOT(columnDelete()));
    */
    menuTable0 = new QMenu(tr("���"));
            //menuTable->addAction( tr("Select"), this, SLOT(tableSelect()) );
            menuTable0->addAction( tr("ɾ��"), this, SLOT(tableDelete()) );

    menuRow = new QMenu(tr("��"));
            menuRow->addAction( tr("�ϲ���"), this, SLOT(rowInsertAbove()) );
            menuRow->addAction( tr("�²���"), this, SLOT(rowInsertBelow()) );
            menuRow->addAction( tr("ɾ��"), this, SLOT(rowDelete()) );

    menuColumn = new QMenu(tr("��"));
            menuColumn->addAction( tr("�����"), this, SLOT(columnInsertLeft()) );
            menuColumn->addAction( tr("�Ҳ���"), this, SLOT(columnInsertRight()) );
            menuColumn->addAction( tr("ɾ��"), this, SLOT(columnDelete()) );

    menuCell = new QMenu(tr("��Ԫ��"));
            menuCell->addAction( tr("�ϲ�"), this, SLOT(cellMerge()) );
            //menuCell->addAction( tr("���(Does not work yet!)"), this, SLOT(cellSplit()) );

    connect(tablePropertyEdit, SIGNAL(createTable(int, int, QTextTableFormat)), this, SLOT(tableInsert(int, int, QTextTableFormat)));
    connect(tablePropertyEdit, SIGNAL(updateTable(int, int, QTextTableFormat)), this, SLOT(tableUpdate(int, int, QTextTableFormat)));
}

void TextEdit::setupTextActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("Format Actions"));
    addToolBar(tb);

    QMenu *menu = new QMenu(tr("��ʽ"), this);
    menuBar()->addMenu(menu);

    actionTextBold = new QAction(QIcon::fromTheme("format-text-bold", QIcon(rsrcPath + "/textbold.png")),
                                 tr("����"), this);
    actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
    actionTextBold->setPriority(QAction::LowPriority);
	QFont bold;
    bold.setBold(true);
    actionTextBold->setFont(bold);
    connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
    tb->addAction(actionTextBold);
    menu->addAction(actionTextBold);
    actionTextBold->setCheckable(true);

    actionTextItalic = new QAction(QIcon::fromTheme("format-text-italic", QIcon(rsrcPath + "/textitalic.png")),
                                   tr("б��"), this);
    actionTextItalic->setPriority(QAction::LowPriority);
    actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
    QFont italic;
    italic.setItalic(true);
    actionTextItalic->setFont(italic);
    connect(actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));
    tb->addAction(actionTextItalic);
    menu->addAction(actionTextItalic);
    actionTextItalic->setCheckable(true);

    actionTextUnderline = new QAction(QIcon::fromTheme("format-text-underline", QIcon(rsrcPath + "/textunder.png")),
                                      tr("�»�"), this);
    actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
    actionTextUnderline->setPriority(QAction::LowPriority);
    QFont underline;
    underline.setUnderline(true);
    actionTextUnderline->setFont(underline);
    connect(actionTextUnderline, SIGNAL(triggered()), this, SLOT(textUnderline()));
    tb->addAction(actionTextUnderline);
    menu->addAction(actionTextUnderline);
    actionTextUnderline->setCheckable(true);

    menu->addSeparator();

    QActionGroup *grp = new QActionGroup(this);
    connect(grp, SIGNAL(triggered(QAction*)), this, SLOT(textAlign(QAction*)));

    // Make sure the alignLeft  is always left of the alignRight
    if (QApplication::isLeftToRight()) {
        actionAlignLeft = new QAction(QIcon::fromTheme("format-justify-left", QIcon(rsrcPath + "/textleft.png")),
                                      tr("����"), grp);
        actionAlignCenter = new QAction(QIcon::fromTheme("format-justify-center", QIcon(rsrcPath + "/textcenter.png")), tr("����"), grp);
        actionAlignRight = new QAction(QIcon::fromTheme("format-justify-right", QIcon(rsrcPath + "/textright.png")), tr("����"), grp);
    } else {
        actionAlignRight = new QAction(QIcon::fromTheme("format-justify-right", QIcon(rsrcPath + "/textright.png")), tr("����"), grp);
        actionAlignCenter = new QAction(QIcon::fromTheme("format-justify-center", QIcon(rsrcPath + "/textcenter.png")), tr("����"), grp);
        actionAlignLeft = new QAction(QIcon::fromTheme("format-justify-left", QIcon(rsrcPath + "/textleft.png")), tr("����"), grp);
    }
    actionAlignJustify = new QAction(QIcon::fromTheme("format-justify-fill", QIcon(rsrcPath + "/textjustify.png")), tr("&Justify"), grp);

    actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
    actionAlignLeft->setCheckable(true);
    actionAlignLeft->setPriority(QAction::LowPriority);
    actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
    actionAlignCenter->setCheckable(true);
    actionAlignCenter->setPriority(QAction::LowPriority);
    actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
    actionAlignRight->setCheckable(true);
    actionAlignRight->setPriority(QAction::LowPriority);
    actionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
    actionAlignJustify->setCheckable(true);
    actionAlignJustify->setPriority(QAction::LowPriority);

    tb->addActions(grp->actions());
    menu->addActions(grp->actions());

    menu->addSeparator();
/*
    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    actionTextColor = new QAction(pix, tr("��ɫ..."), this);
    connect(actionTextColor, SIGNAL(triggered()), this, SLOT(textColor()));
    tb->addAction(actionTextColor);
    menu->addAction(actionTextColor);
*/

    tb = new QToolBar(this);
    tb->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    tb->setWindowTitle(tr("Format Actions"));
    addToolBarBreak(Qt::TopToolBarArea);
    addToolBar(tb);
/*
    comboStyle = new QComboBox(tb);
    tb->addWidget(comboStyle);
    comboStyle->addItem("Standard");
    comboStyle->addItem("Bullet List (Disc)");
    comboStyle->addItem("Bullet List (Circle)");
    comboStyle->addItem("Bullet List (Square)");
    comboStyle->addItem("Ordered List (Decimal)");
    comboStyle->addItem("Ordered List (Alpha lower)");
    comboStyle->addItem("Ordered List (Alpha upper)");
    comboStyle->addItem("Ordered List (Roman lower)");
    comboStyle->addItem("Ordered List (Roman upper)");
    connect(comboStyle, SIGNAL(activated(int)),
            this, SLOT(textStyle(int)));
*/
    comboFont = new QFontComboBox(tb);
    tb->addWidget(comboFont);
    connect(comboFont, SIGNAL(activated(QString)),
            this, SLOT(textFamily(QString)));

    comboSize = new QComboBox(tb);
    comboSize->setObjectName("comboSize");
    tb->addWidget(comboSize);
    comboSize->setEditable(true);

    colorCombo = new CcolorCombo(tb);
    tb->addWidget(colorCombo);
    connect(colorCombo, SIGNAL(activated(int)), this, SLOT(textColor()));

    QFontDatabase db;
    foreach(int size, db.standardSizes())
        comboSize->addItem(QString::number(size));

    connect(comboSize, SIGNAL(activated(QString)),
            this, SLOT(textSize(QString)));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(QApplication::font()
                                                                   .pointSize())));

    smLineCombo = new CsmLineCombo(tb);
    tb->addWidget(smLineCombo);
    connect(smLineCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(edit()));//SLOT(textColor()));

    QLabel *pageLabel;
    pageLabel = new QLabel(tr("��"),tb);
    tb->addWidget(pageLabel);

    spinPage = new QSpinBox(tb);
    tb->addWidget(spinPage);
    spinPage->setValue(1);
    connect(spinPage, SIGNAL(valueChanged(int)), this, SLOT(edit()));//SLOT(textColor()));

    QLabel *muLabel;
    muLabel = new QLabel(tr("Ļ"),tb);
    tb->addWidget(muLabel);

    QLabel *distanceLabel;
    distanceLabel = new QLabel(tr("�о�"),tb);
    tb->addWidget(distanceLabel);

    spinLineDis = new QSpinBox(tb);
    tb->addWidget(spinLineDis);
    spinPage->setValue(1);
    connect(spinLineDis, SIGNAL(valueChanged(int)), this, SLOT(lineDisEdit(int)));//SLOT(textColor()));

    distanceLabel->setFixedWidth(0); //��ʱ����ʾ��������Ŀǰû��ʵ�ֺ�
    spinLineDis->setFixedWidth(0);

}

bool TextEdit::load(const QString &f)
{
    if (!QFile::exists(f))
        return false;
    QFile file(f);
    if (!file.open(QFile::ReadOnly))
        return false;

    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);
    if (1/*Qt::mightBeRichText(str)*/) {
        textEdit->setHtml(str);
    } else {
        str = QString::fromLocal8Bit(data);
        textEdit->setPlainText(str);
    }

    file.close();
    setCurrentFileName(f);
    return true;
}

bool TextEdit::maybeSave()
{
    if (!textEdit->document()->isModified())
        return true;
    if (fileName.startsWith(QLatin1String(":/")))
        return true;
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Application"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard
                               | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
        return fileSave();
    else if (ret == QMessageBox::Cancel)
        return false;
    return true;
}

void TextEdit::setCurrentFileName(const QString &fileName)
{
    this->fileName = fileName;
    textEdit->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = "untitled.txt";
    else
        shownName = QFileInfo(fileName).fileName();
  /*
    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Rich Text")));
    setWindowModified(false);
    */
    setWindowTitle("");
}

void TextEdit::fileNew()
{
    //if (maybeSave()) {
        textEdit->clear();
       // setCurrentFileName(QString());
    //}
}

void TextEdit::fileOpen()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("���ļ�..."),
                                              QString(), tr("HTML-Files (*.htm *.html);;All Files (*)"));
    if (!fn.isEmpty())
        load(fn);
}

bool TextEdit::fileSave()
{
    if (fileName.isEmpty())
        return fileSaveAs();

    QTextDocumentWriter writer(fileName);
    bool success = writer.write(textEdit->document());
    if (success)
        textEdit->document()->setModified(false);
    return success;
}

bool TextEdit::fileSaveAs()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("���Ϊ..."),
                                              QString(), tr("HTML-Files (*.htm *.html);;All Files (*)"));
    if (fn.isEmpty())
        return false;
    if (! (fn.endsWith(".odt", Qt::CaseInsensitive) || fn.endsWith(".htm", Qt::CaseInsensitive) || fn.endsWith(".html", Qt::CaseInsensitive)) )
        fn += ".html"; // default
    //setCurrentFileName(fn);
    //return fileSave();
    QTextDocumentWriter writer(fn);
    bool success = writer.write(textEdit->document());
    //if (success)
        //textEdit->document()->setModified(false);
    return success;
}

void TextEdit::filePrint()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (textEdit->textCursor().hasSelection())
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    dlg->setWindowTitle(tr("Print Document"));
    if (dlg->exec() == QDialog::Accepted) {
        textEdit->print(&printer);
    }
    delete dlg;
#endif
}

void TextEdit::filePrintPreview()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreview(QPrinter*)));
    preview.exec();
#endif
}

void TextEdit::printPreview(QPrinter *printer)
{
#ifdef QT_NO_PRINTER
    Q_UNUSED(printer);
#else
    textEdit->print(printer);
#endif
}


void TextEdit::filePrintPdf()
{
#ifndef QT_NO_PRINTER
//! [0]
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",
                                                    QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        textEdit->document()->print(&printer);
    }
//! [0]
#endif
}

void TextEdit::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);

    //QTextCursor cursor = textEdit->textCursor();
}

void TextEdit::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(actionTextUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(actionTextItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}

void TextEdit::textStyle(int styleIndex)
{
    QTextCursor cursor = textEdit->textCursor();

    if (styleIndex != 0) {
        QTextListFormat::Style style = QTextListFormat::ListDisc;

        switch (styleIndex) {
            default:
            case 1:
                style = QTextListFormat::ListDisc;
                break;
            case 2:
                style = QTextListFormat::ListCircle;
                break;
            case 3:
                style = QTextListFormat::ListSquare;
                break;
            case 4:
                style = QTextListFormat::ListDecimal;
                break;
            case 5:
                style = QTextListFormat::ListLowerAlpha;
                break;
            case 6:
                style = QTextListFormat::ListUpperAlpha;
                break;
            case 7:
                style = QTextListFormat::ListLowerRoman;
                break;
            case 8:
                style = QTextListFormat::ListUpperRoman;
                break;
        }

        cursor.beginEditBlock();

        QTextBlockFormat blockFmt = cursor.blockFormat();

        QTextListFormat listFmt;

        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }

        listFmt.setStyle(style);

        cursor.createList(listFmt);

        cursor.endEditBlock();
    } else {
        // ####
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}

void TextEdit::textColor()
{/*
    QColor col = QColorDialog::getColor(textEdit->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
    */
    QColor col;

    col = colorCombo->getColor();

    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
}

void TextEdit::textAlign(QAction *a)
{
    if (a == actionAlignLeft)
        textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == actionAlignCenter)
        textEdit->setAlignment(Qt::AlignHCenter);
    else if (a == actionAlignRight)
        textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == actionAlignJustify)
        textEdit->setAlignment(Qt::AlignJustify);
}

void TextEdit::currentCharFormatChanged(const QTextCharFormat &format)
{
    if(format.foreground().color() != QColor(Qt::red) &&
       format.foreground().color() != QColor(Qt::green) &&
       format.foreground().color() != QColor(Qt::yellow))
    {
       fontChanged(format.font());
       textEdit->setTextColor(colorCombo->getColor());
       colorChanged(colorCombo->getColor());
/*
       QTextCursor tc = textEdit->textCursor();
       //tc.setPosition(it.position(),QTextCursor::MoveAnchor);
       QTextBlockFormat bfmt = tc.blockFormat();
       //bfmt.setBottomMargin(mlinespacing);
       lineDistanceChanged(bfmt.topMargin());
  */ }
   else
   {
     fontChanged(format.font());
     colorChanged(format.foreground().color());
/*
     QTextCursor tc = textEdit->textCursor();
     //tc.setPosition(it.position(),QTextCursor::MoveAnchor);
     QTextBlockFormat bfmt = tc.blockFormat();
     //bfmt.setBottomMargin(mlinespacing);
     lineDistanceChanged(bfmt.topMargin());
  */ }
}

void TextEdit::lineDisEdit(int dis)
{
    QTextCursor tc = textEdit->textCursor();

    //tc.setPosition(it.position(),QTextCursor::MoveAnchor);
    QTextBlockFormat bfmt = tc.blockFormat();
    bfmt.setBottomMargin(dis);
    tc.setBlockFormat(bfmt);
    textEdit->setTextCursor(tc);
}

void TextEdit::cursorPositionChanged()
{
    alignmentChanged(textEdit->alignment());
}

void TextEdit::clipboardDataChanged()
{
#ifndef QT_NO_CLIPBOARD
    actionPaste->setEnabled(!QApplication::clipboard()->text().isEmpty());
#endif
}

void TextEdit::about()
{
    QMessageBox::about(this, tr("About"), tr("This example demonstrates Qt's "
        "rich text editing facilities in action, providing an example "
        "document for you to experiment with."));
}

void TextEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textEdit->textCursor();
    /*
    if (!cursor.hasSelection())
    {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    */
    cursor.mergeCharFormat(format);

    textEdit->mergeCurrentCharFormat(format);
}

void TextEdit::fontChanged(const QFont &f)
{
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    actionTextBold->setChecked(f.bold());
    actionTextItalic->setChecked(f.italic());
    actionTextUnderline->setChecked(f.underline());
}

void TextEdit::colorChanged(const QColor &c)
{/*
    QPixmap pix(16, 16);
    pix.fill(c);
    actionTextColor->setIcon(pix);
*/
    colorCombo->setColor(c);//
    //setColor(QColor &col)
}

void TextEdit::lineDistanceChanged(const int dis)
{
   spinLineDis->setValue(dis);
}

void TextEdit::alignmentChanged(Qt::Alignment a)
{
    if (a & Qt::AlignLeft) {
        actionAlignLeft->setChecked(true);
    } else if (a & Qt::AlignHCenter) {
        actionAlignCenter->setChecked(true);
    } else if (a & Qt::AlignRight) {
        actionAlignRight->setChecked(true);
    } else if (a & Qt::AlignJustify) {
        actionAlignJustify->setChecked(true);
    }
}

QTextEdit *TextEdit::getEdit()
{
    return textEdit;
}

void TextEdit::showInit()
{
    CshowArea *area;

    //qDebug("propertyEdited");
    area = w->screenArea->getFocusArea(); //��ǰ�������
    if(area != (CshowArea *)0)
    {
        //connect(textEdit, SIGNAL(textChanged()), this, SLOT(edit())); //�ı������仯�򴥷��¼�
        textEdit->setLineWrapMode(QTextEdit::FixedPixelWidth);

        int borderHeight;
        if(area->filePara.Pic_Para.Border_Check)
          borderHeight = area->filePara.Pic_Para.Border_Height;
        else
          borderHeight = 0;

        textEdit->setLineWrapColumnOrWidth(area->width() - borderHeight*2 + TEXT_LEFT_BORDER_WIDTH + TEXT_RIGHT_BORDER_WIDTH);

        int mode;
        if(smLineCombo->currentIndex() == 0)
            mode = SLINE_MODE;
        else
            mode = MLINE_MODE;

        int pageNum;
        if(editMode EQ 0)
        {
            int lineNum;
            QImage image = getTextImage(area->width(), textEdit->toHtml(), &lineNum, linePosi);
            pageNum = getTextPageNum(mode, MOVE_NORMAL, image.height(), area->width(), area->height(), lineNum, linePosi, pagePosi);
        }
        else
        {
            getTableImage(area->width(), area->height(), textEdit->toHtml(), &pageNum);

        }
        //int pageNum = getTextImagePageNum(mode,area->width(),area->height(),textEdit->toHtml(), linePosi);
        spinPage->setMinimum(0);

        spinPage->setMaximum((pageNum > 0)?(pageNum-1) : 0);

        colorCombo->setCurrentIndex(0);
        this->textColor();

        show();
        setWindowTitle(tr("�༭��"));
    }
}

void TextEdit::edit()
{
    CshowArea *area;

  QString str = w->screenArea->getCurrentFileStr();//getCurrentStr
  //setSettingsToWidget(str);
  getSettingsFromWidget(str);
  area = w->screenArea->getFocusArea();

  if(smLineCombo->currentIndex() == 0) {
      area->smLineFlag = SLINE_MODE;
  }//smLineCombo->currentIndex();
  else
      area->smLineFlag = MLINE_MODE;

  area->picStr = textEdit->toHtml();
  area->moveFlag = checkSLineMoveLeftContinuous(str);

  int lineNum,pageNum;
  if(editMode EQ 0) //�ı��༭��ʽ
  {
      if(area->moveFlag != MOVE_LEFT_CONTINUOUS) //������������
      {
          QImage image = getTextImage(area->width(), area->picStr, &lineNum, linePosi);
          pageNum = getTextPageNum(area->smLineFlag, area->moveFlag, image.height(), area->width(), area->height(), lineNum, linePosi, pagePosi);
          //int pageNum = getTextImagePageNum(area->smLineFlag, area->width(),area->height(),area->picStr, linePosi);


      }
      else //��������
      {
          pageNum = getSLineTextPageNum(area->picStr, area->width());
        //getSLineTextImage(area->picStr, area->width(),area->height());

      }
  }
  else //���༭��ʽ
  {
    getTableImage(area->width(), area->height(), area->picStr, &pageNum);

  }

  pageNum = (pageNum > 0)?(pageNum-1) : 0;
  spinPage->setMaximum(pageNum);
  w->property->picProperty->pageBox->setMaximum(pageNum);

  if(spinPage->value() > pageNum)
  {
    spinPage->setValue(pageNum);
    w->property->picProperty->pageBox->setValue(pageNum);
  }

  area->page = spinPage->value(); //ҳ��
  area->updateFlag = true;
  area->update(); //���µ�ǰ��ʾ����

}

void TextEdit::screenCardParaChangeProc()
{
  colorCombo->setItems();
}

void TextEdit::getSettingsFromWidget(QString str)
{

    settings.beginGroup(str);
    settings.beginGroup("textEdit");
    settings.setValue("text", getEdit()->toHtml());
    settings.setValue("page", spinPage->value());
    //settings.setValue("color", colorCombo->currentIndex());
    settings.endGroup();
    settings.endGroup();

    smLineCombo->getSettingsFromWidget(str);
}

void TextEdit::setSettingsToWidget(QString str)
{
    //QStringList keys;
    QString text;


    settings.beginGroup(str);
    settings.beginGroup("textEdit");
    int setFlag = settings.value("setFlag").toBool();
    if(setFlag == 0)
    {
       settings.setValue("page", 0);
       settings.setValue("text", QString(""));
       //settings.setValue("color", 0);
       settings.setValue("setFlag", 1);
    }
    text = settings.value("text").toString();
    if(text == "")
        text == QString(tr("ͼ����ʾ"));

    int page = settings.value("page").toInt();
    //int color = settings.value("color").toInt();
    settings.endGroup();
    settings.endGroup();

    //disconnect()
    disconnect(textEdit, SIGNAL(textChanged()), this, SLOT(edit())); //�ı������仯�򴥷��¼�
    textEdit->clear();
    textEdit->setHtml(text);
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(edit())); //�ı������仯�򴥷��¼�

    disconnect(spinPage, SIGNAL(valueChanged(int)), this, SLOT(edit()));
    spinPage->setMaximum(999);
    spinPage->setValue(page);
    connect(spinPage, SIGNAL(valueChanged(int)), this, SLOT(edit()));

    disconnect(smLineCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(edit()));
    int type = checkStrType(str) ;
    if(type EQ PIC_STEXT_PROPERTY)
    {
      smLineCombo->setCurrentIndex(0);
      smLineCombo->setEnabled(false);
      menuTable->setEnabled(false);
      editMode = 0;
    }
    else if(type EQ PIC_MTEXT_PROPERTY)
    {
      smLineCombo->setCurrentIndex(1);
      smLineCombo->setEnabled(true);

      menuTable->setEnabled(false);
      editMode = 0;
    }
    else if(type EQ PIC_TABLE_PROPERTY)
    {
      smLineCombo->setCurrentIndex(1);
      smLineCombo->setEnabled(false);
      menuTable->setEnabled(true);
      editMode = 1;
    }

    connect(smLineCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(edit()));

    //colorCombo->setCurrentIndex(color);
}
/*
������QGraphicsTextItem  �ּ�ࣺvoid QFont::setLetterSpacing ( SpacingType type, qreal spacing )

�м�࣬��ο���ϴ��룺

���ƴ���
        for (QTextBlock it = doc->begin(); it != doc->end(); it = it.next())
        {
            tc.setPosition(it.position(),QTextCursor::MoveAnchor);
            QTextBlockFormat bfmt = it.blockFormat();
            bfmt.setBottomMargin(mlinespacing);
            tc.setBlockFormat(bfmt);
            this->setTextCursor(tc);
        }




 */

/*
//��ȡ�ı�����
int getTextImageLineNum(int w, QString str)
{
    QTextEdit edit;

    edit.setLineWrapMode(QTextEdit::FixedPixelWidth);
    edit.setLineWrapColumnOrWidth(w);
    edit.setHtml(str);

    QSize size = edit.document()->documentLayout()->documentSize().toSize();

    int line = 1,posi;
    QTextCursor cursor = edit.textCursor();
    while(1)
    {
        posi = cursor.position();
        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, 1);

        if(posi == cursor.position())
         break;

        line ++;
    }

    return line;
}*/

//��ȡ�ı�ĳ�еĸ߶�
//wΪͼ��Ŀ��,strΪ��ʵ��HTML����
//*pLineNum��¼�ı�������
//linePosi��¼ÿ�е�λ��--linePosi[0]��ʾ��0�е���ʼλ��
QImage getTextImage(int w, QString str, int *pLineNum, int linePosi[])
{
    QTextEdit edit;
    QTextLayout *layout = 0;

    edit.setLineWrapMode(QTextEdit::FixedPixelWidth);
    edit.setLineWrapColumnOrWidth(w + TEXT_LEFT_BORDER_WIDTH + TEXT_RIGHT_BORDER_WIDTH);
    edit.setHtml(str);

    QSize size = edit.document()->documentLayout()->documentSize().toSize();
    edit.resize(size.width(), size.height());

    QPalette *palette = new QPalette(QPalette::Base,QColor(Qt::black));
    edit.setPalette(*palette);

    edit.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    edit.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QImage image(edit.width(), edit.height(),QImage::Format_RGB32);
    edit.render(&image);

    image = image.copy(TEXT_LEFT_BORDER_WIDTH, 0, image.width() - TEXT_LEFT_BORDER_WIDTH - TEXT_RIGHT_BORDER_WIDTH, image.height());

    //ÿ��Block
    qreal blockPosi = 0;
    int lineNum = 0;

    //����ÿ�����䣬�õ�ÿ�е���ʼλ�ú�����
    for(int i = 0; i < edit.document()->blockCount(); i ++)
    {
       layout = edit.document()->findBlockByNumber(i).layout();
       blockPosi = (layout->position().y());
       for(int j = 0; j < layout->lineCount(); j ++)
       {
           linePosi[lineNum++] = blockPosi + (layout->lineAt(j).position().y()) + LINE_POSI_ADJ;
           //linePosi[lineNum]+=20; //--!!!�˴������+1���ܵ���ͼ�����е����ݽ��뱾�У����е����һ�����ݽ�������
       }
    }

    if(layout != 0)
    {
        linePosi[lineNum] = (int)(layout->position().y() + layout->boundingRect().height());
        linePosi[lineNum]+=LINE_POSI_ADJ;//--!!!�˴������+1���ܵ���ͼ�����е����ݽ��뱾�У����е����һ�����ݽ�������
        *pLineNum = lineNum;
    }
    else
        *pLineNum = 0;
    //image.save("d:\\Image.png");
    return image;
}

QImage getTableImage(int w, int h, QString str, int *pPageNum)
{
    QTextEdit edit;
    //QTextLayout *layout = 0;

    edit.setLineWrapMode(QTextEdit::FixedPixelWidth);
    edit.setLineWrapColumnOrWidth(w + TEXT_LEFT_BORDER_WIDTH + TEXT_RIGHT_BORDER_WIDTH);
    edit.setHtml(str);

    QSize size = edit.document()->documentLayout()->documentSize().toSize();
    edit.resize(size.width(), size.height());

    QPalette *palette = new QPalette(QPalette::Base,QColor(Qt::black));
    edit.setPalette(*palette);

    edit.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    edit.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QImage image(edit.width(), edit.height(),QImage::Format_RGB32);
    edit.render(&image);

    if(h > 0)
    {
      if((image.height() % h) EQ 0)
        *pPageNum = image.height() / h;
      else
        *pPageNum = image.height() / h + 1;
    }
    else
      *pPageNum = 0;

    image = image.copy(0, 0, w, image.height());

    return image;
    /*
    //ÿ��Block
    qreal blockPosi = 0;
    int lineNum = 0;

    //����ÿ�����䣬�õ�ÿ�е���ʼλ�ú�����
    for(int i = 0; i < edit.document()->blockCount(); i ++)
    {
       layout = edit.document()->findBlockByNumber(i).layout();
       blockPosi = (layout->position().y());
       for(int j = 0; j < layout->lineCount(); j ++)
       {
           linePosi[lineNum++] = blockPosi + (layout->lineAt(j).position().y()) + LINE_POSI_ADJ;
           //linePosi[lineNum]+=20; //--!!!�˴������+1���ܵ���ͼ�����е����ݽ��뱾�У����е����һ�����ݽ�������
       }
    }

    if(layout != 0)
    {
        linePosi[lineNum] = (int)(layout->position().y() + layout->boundingRect().height());
        linePosi[lineNum]+=LINE_POSI_ADJ;//--!!!�˴������+1���ܵ���ͼ�����е����ݽ��뱾�У����е����һ�����ݽ�������
        *pLineNum = lineNum;
    }
    else
        *pLineNum = 0;
    //image.save("d:\\Image.png");
    return image;
    */
}

QImage getTablePageImage(QImage &image, int w, int h, int page)
{
  QImage reImage;

  reImage = image.copy(0, page*h, w, h);
  return reImage;
}

//��ȡҳ��
//mode��ʾ���л��Ƕ���ģʽ
//w,h��ʾͼ��Ŀ�Ⱥ͸߶�
//lineNum��ʾ�ı�����
//linePosi��¼ÿ�е���ʼλ��,�������
//pagePosi��ʾʱÿҳ����ʼλ�ã��������,pagePosi[0]��¼��0ҳ����ʼλ��
//���������ı���ҳ��
int getTextPageNum(int mode ,int moveFlag, int imageHeight, int w, int h, int lineNum, int linePosi[], int pagePosi[])
{
    //int height = 0,height1 = 0;
    //int tmp = 0;
    int pageNum = 0;
    int startLine = 0;

    if(mode == SLINE_MODE)
    {
        for(int i = 0; i < lineNum + 1; i ++)
            pagePosi[i] = linePosi[i];

        return lineNum;
    }
    else
    {
        if(moveFlag EQ MOVE_NORMAL)
        {
            pagePosi[pageNum++] = linePosi[0];
            startLine = 0;
            for(int i =1; i < lineNum; i ++)
            {
                if(linePosi[i + 1] - linePosi[startLine] > h)
                {
                  pagePosi[pageNum++] = linePosi[i];
                  startLine = i;
                }
            }

            pagePosi[pageNum] = linePosi[lineNum]; // ��ǰҳ�Ľ���λ��

       }
       else
       {
           if(h EQ 0)
               return 0;

           imageHeight = imageHeight - linePosi[0];
           pageNum = (imageHeight % h) >0? (imageHeight / h + 1):(imageHeight / h);

           pagePosi[0] = linePosi[0];
           for(int i= 1; i < pageNum + 1; i ++)
               pagePosi[i] = pagePosi[i - 1] + h;

           //pagePosi[i] = pagePosi[i -1] + h;

       }


        return pageNum;
    }
}

//��ȡ�ı���ĳҳ����ʾͼ��
//mode��ʾ���л��Ƕ���
//image��ʾ�����ı���ͼ��
//w,hÿҳ�Ŀ�Ⱥ͸߶�
//pageΪҳ��
//pagePosiΪÿҳ��λ��
//����Ϊ��ҳ��ͼ��
QImage getTextPageImage(int mode, QImage &image, int w, int h, int page, int pagePosi[])
{
    QRgb rgb;
    int height; //image.height();
    QImage reImage(w,h,QImage::Format_RGB32); //

    reImage.fill(Qt::black);
    height = pagePosi[page + 1] - pagePosi[page]; //�߶�

    if(height > h) //�и߶ȱȴ��ڸ߶ȸ�?
    {
        for(int i = 0; i < w; i ++)
          for(int j = pagePosi[page] + (height - h) / 2; j < pagePosi[page] + (height - h) / 2 + h; j ++)
          {
            if(i < image.width() && j<image.height())
              rgb = image.pixel(i,j);
            else
                rgb = Qt::black;
            reImage.setPixel(i, j - pagePosi[page] - (height - h) / 2, rgb);

          }
    }
    else
    {
        for(int i = 0; i < w; i ++)
          for(int j = pagePosi[page]; j < pagePosi[page] + height; j ++)
          {
            if(i < image.width() && j<image.height())
              rgb = image.pixel(i,j);
            else
                rgb = Qt::black;
            reImage.setPixel(i, j - pagePosi[page] + (h - height) / 2, rgb);

          }

    }

    //reImage.save("d:\\reImage.png");
    return reImage;
}
/*
//--------------------------------------------------------------------------------------------
//modeģʽ
//w���
int getTextImagePageNum(int mode, int w, int h, QString str, int posi[])
{
  int height = 0,height1 = 0;
  int tmp = 0;
  int pageNum = 0;

  if(mode == SLINE_MODE)
      return getTextImageLineNum(w, str);
  else
  {
      int lineNum = getTextImageLineNum(w, str);

      for(int i = 0; i < lineNum; i ++)
      {
         tmp = 0;//getTextImageLineHeight(w, str, i);

         if(height + tmp> h)
         {
             if(pageNum >= MAX_LINE_NUM)
             {
                 ASSERT_FAILED();
                 return 0;
             }

             posi[pageNum] = height1; // ��ǰҳ�Ľ���λ��
             pageNum++;

             height1 += tmp;
             height = tmp; //��һҳ�ĵ�һ��line�߶�
         }
         else
         {
           height1 += tmp;
           height += tmp;
         }
      }
      posi[pageNum] = height1; // ��ǰҳ�Ľ���λ��
      pageNum++;
      return pageNum;
  }
}
*/

int getSLineTextPageNum(QString str, int w)
{
    QTextEdit edit;
    //QTextLayout *layout;

    edit.setLineWrapMode(QTextEdit::NoWrap);
    //edit.setLineWrapColumnOrWidth(w + TEXT_LEFT_BORDER_WIDTH + TEXT_RIGHT_BORDER_WIDTH);
    edit.setHtml(str);

    QSize size = edit.document()->documentLayout()->documentSize().toSize();
    edit.resize(size.width(), size.height());

    QPalette *palette = new QPalette(QPalette::Base,QColor(Qt::black));
    edit.setPalette(*palette);

    edit.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    edit.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //QImage image(edit.width(), edit.height(),QImage::Format_RGB32);
    //edit.render(&image);
    //image.save("d:\\slinetext.png");

    int num = 0, blockPageNum = 0;
    for(int i = 0; i < edit.document()->blockCount(); i ++)
    {
      int width =edit.document()->findBlockByNumber(i).layout()->boundingRect().width();// - TEXT_LEFT_BORDER_WIDTH  - TEXT_RIGHT_BORDER_WIDTH;

      if((width % w) == 0)
          blockPageNum = width / w;
      else
          blockPageNum = width / w + 1;

          num += blockPageNum;
    }

    return num;
}

QImage getSLineTextImage(QString str, int w, int h, int page)
{
    QTextEdit edit;
    QTextLayout *layout;
    QImage reImage(w,h,QImage::Format_RGB32);
    QRgb rgb;

    edit.setLineWrapMode(QTextEdit::NoWrap);
    //edit.setLineWrapColumnOrWidth(w + TEXT_LEFT_BORDER_WIDTH + TEXT_RIGHT_BORDER_WIDTH);
    edit.setHtml(str);

    QSize size = edit.document()->documentLayout()->documentSize().toSize();
    edit.resize(size.width(), size.height());

    QPalette *palette = new QPalette(QPalette::Base,QColor(Qt::black));
    edit.setPalette(*palette);

    edit.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    edit.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QImage image(edit.width(), edit.height(),QImage::Format_RGB32);
    edit.render(&image);
    image.save("d:\\slinetext.png");

    //edit.document()->findBlockByNumber(0).clearLayout();

    int num = 0, blockPageNum = 0;
    for(int i = 0; i < edit.document()->blockCount(); i ++)
    {
      int x,y;

      layout = edit.document()->findBlockByNumber(i).layout();

      int width = layout->boundingRect().width();// - TEXT_LEFT_BORDER_WIDTH - TEXT_RIGHT_BORDER_WIDTH;
      int height = layout->boundingRect().height();// - LINE_POSI_ADJ;

      //int diff = edit.document()->findBlockByNumber(i + 1).layout()->position().y() - layout->position().y();
      //qDebug("height = %d, diff = %d", height, diff);

      if((width % w) == 0)
          blockPageNum = width / w;
      else
          blockPageNum = width / w + 1;

      if(num + blockPageNum > page)
      {
          x = TEXT_LEFT_BORDER_WIDTH + layout->boundingRect().x();
          x += (page - num) * w;
          y = LINE_POSI_ADJ + layout->lineAt(0).position().y() + layout->position().y();
          //yֵ��Ҫ+4������ƥ�䣬����ֵ

          reImage.fill(Qt::black);
          if(height > h) //�и߶ȱȴ��ڸ߶ȸ�?
          {
              for(int i = 0; i < w; i ++)
                for(int j = 0; j < h; j ++)
                {
                  if(x + i < image.width() && y + j < image.height())
                    rgb = image.pixel(x + i,y + (height - h) / 2 + j);
                  else
                    rgb = Qt::black;
                  reImage.setPixel(i, j, rgb);
                }
          }
          else
          {
              for(int i = 0; i < w; i ++)
                for(int j = 0; j < height; j ++)
                {
                  if(x + i < image.width() && y + j < image.height())
                    rgb = image.pixel(x + i,y + j);
                  else
                    rgb = Qt::black;
                  reImage.setPixel(i, (h - height) / 2 + j, rgb);
                  /*
                  if(reImage.pixel(i, (h - height) / 2 + j) != rgb)
                  {
                      ASSERT_FAILED();
                  }*/
                }

          }

          //image = image.copy(, 0, w, height);
          //reImage.save("d:\\slinepage.png");
          return reImage;
      }
       else
          num += blockPageNum;

    }

    //qDebug("text width = %f, height = %f", layout->boundingRect().width(),layout->boundingRect().height());


    return image;
}

//-------------------------------------------------

void TextEdit::tableNew()
{
    tablePropertyEdit->setProperties(2, 2, QTextTableFormat(), true);
    tablePropertyEdit->setModal(true);
    tablePropertyEdit->show();
}


//-------------------------------------------------
void TextEdit::tableInsert(int rows, int columns, QTextTableFormat format)
{
    QTextCursor cursor = textEdit->textCursor();
    QTextTable *table = cursor.insertTable(rows, columns);
    table->setFormat(format);
}

//-------------------------------------------------
/*
void TextEdit::tableProperties()
{
    QTextCursor cursor = textEdit->textCursor();
        QTextTable *table = cursor.currentTable();
        tableprop->setProperties(table->rows(), table->columns(), table->format(), false);
    tableprop->show();
}
*/

//-------------------------------------------------
void TextEdit::tableUpdate(int rows, int colums, QTextTableFormat tableFormat)
{
    QTextCursor cursor = textEdit->textCursor();
        QTextTable *table = cursor.currentTable();
        table->resize(rows, colums);
    table->setFormat(tableFormat);
}
//-------------------------------------------------
void TextEdit::tableDelete()
{
        QTextCursor cursor = textEdit->textCursor();
        QTextTable *table = cursor.currentTable();
        table->removeRows(0, table->rows());
}

//-------------------------------------------------
void TextEdit::rowInsertAbove()
{
    QTextCursor cursor = textEdit->textCursor();
        QTextTable *table = cursor.currentTable();
        QTextTableCell cell = table->cellAt(cursor);
        table->insertRows(cell.row(), 1);
}

//-------------------------------------------------
void TextEdit::rowInsertBelow()
{
    QTextCursor cursor = textEdit->textCursor();
        QTextTable *table = cursor.currentTable();
        QTextTableCell cell = table->cellAt(cursor);
        table->insertRows(cell.row()+1, 1);
}

//-------------------------------------------------
void TextEdit::rowDelete()
{
        QTextCursor cursor = textEdit->textCursor();
        QTextTable *table = cursor.currentTable();
        QTextTableCell cell = table->cellAt(cursor);
        table->removeRows(cell.row(), 1);
}

//-------------------------------------------------
void TextEdit::columnInsertLeft()
{
    QTextCursor cursor = textEdit->textCursor();
        QTextTable *table = cursor.currentTable();
        QTextTableCell cell = table->cellAt(cursor);
        table->insertColumns(cell.column(), 1);
}

//-------------------------------------------------
void TextEdit::columnInsertRight()
{
    QTextCursor cursor = textEdit->textCursor();
        QTextTable *table = cursor.currentTable();
        QTextTableCell cell = table->cellAt(cursor);
        table->insertColumns(cell.column()+1, 1);
}

//-------------------------------------------------
void TextEdit::columnDelete()
{
        QTextCursor cursor = textEdit->textCursor();
        QTextTable *table = cursor.currentTable();
        QTextTableCell cell = table->cellAt(cursor);
        table->removeColumns(cell.column(), 1);
}

//-------------------------------------------------
void TextEdit::cellMerge()
{
        QTextCursor cursor = textEdit->textCursor();
        QTextTable *table = cursor.currentTable();
        table->mergeCells(cursor);
}
//-------------------------------------------------
/*
void TextEdit::cellSplit()
{
        cellsplit->show();
}

//-------------------------------------------------
void TextEdit::cellSplit(int rows, int columns)
{
        QTextCursor cursor = textEdit->textCursor();
        QTextTable *table = cursor.currentTable();
        QTextTableCell cell = table->cellAt(cursor);
        Config::configuration()->toPrjLog(3,"Cell Split: cell.row()="+QString::number(cell.row())+", cell.column()="+QString::number(cell.column())+", rows="+QString::number(rows)+", columns="+QString::number(columns));
        table->splitCell(cell.row(), cell.column(), rows, columns);
}
*/
void TextEdit::setupTableMenu()
{
        bool state = false;
    QTextCursor cursor = textEdit->textCursor();
        QTextTable *table = cursor.currentTable();
        if ( table != 0) state = true;

        actionTableProperty->setEnabled(state);
        actionInsertRowAbove->setEnabled(state);
        actionInsertRowBelow->setEnabled(state);
        actionInsertColumnLeft->setEnabled(state);
        actionInsertColumnRight->setEnabled(state);
        menuDelete->setEnabled(state);
}

void TextEdit::tableProperties()
{
    QTextCursor cursor = textEdit->textCursor();
        QTextTable *table = cursor.currentTable();
        tablePropertyEdit->setProperties(table->rows(), table->columns(), table->format(), false);
    tablePropertyEdit->setModal(true);
    tablePropertyEdit->show();
}
/*
void TextEdit::setupPopupMenu(QMenu *m)
{
    m->addMenu(menuSign);
        m->addSeparator();
    m->addAction(ui.actionNewWindow);
    m->addAction(ui.actionOpenPage);
    m->addAction(ui.actionClosePage);
    m->addSeparator();
//    m->addAction(ui.actionZoomIn);
//    m->addAction(ui.actionZoomOut);
        m->addAction(ui.actionViewSource);
    m->addSeparator();
    m->addAction(ui.actionCopy);
    m->addAction(ui.actionPaste);
    m->addAction(ui.actionCut);
    m->addSeparator();
    m->addAction(ui.actionEditFind);
}
*/
void CtextEdit::contextMenuEvent(QContextMenuEvent *e)
{
    QMenu *m = new QMenu(0);
    /*
    if (hasAnchorAt(e->pos())) {
        m->addAction( tr("Open Link in New Window\tShift+LMB"), this, SLOT(openLinkInNewWindow()) );
        m->addAction( tr("Open Link in New Tab\tMMB"), this, SLOT(openLinkInNewPage()) );
        m->addAction( tr("Link properties..."), this, SLOT(showLinkProperties()) );
    }else{
        if ( textCursor().hasSelection() )
                m->addAction( tr("Create link..."), this, SLOT(showLinkProperties()) );
    }

    m->addSeparator();*/
    if (((TextEdit *)parent())->editMode > 0 && textCursor().currentTable() ){
        m->addAction( tr("�������"), (TextEdit *)parent(), SLOT(tableProperties()) );
        m->addMenu(((TextEdit *)parent())->menuTable0);
        m->addMenu(((TextEdit *)parent())->menuRow);
        m->addMenu(((TextEdit *)parent())->menuColumn);
        m->addMenu(((TextEdit *)parent())->menuCell);
        m->addSeparator();
        }
    m->addSeparator();
    m->addAction(((TextEdit *)parent())->actionUndo);
    m->addAction(((TextEdit *)parent())->actionRedo);
    m->addAction(((TextEdit *)parent())->actionCopy);
    m->addAction(((TextEdit *)parent())->actionPaste);
    m->addAction(((TextEdit *)parent())->actionCut);
    m->addSeparator();
    m->exec(e->globalPos());
    delete m;
}

/*
INT16U getSLineTextPageNum(QString str, INT16U width)
{
  QImage image = getSLineTextImage(str);

  if((image.width() % width) EQ 0)
      return image.width() / width;
  else
      return image.width() / width + 1;
}
*/
