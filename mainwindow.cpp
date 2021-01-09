#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    qDebug()<<QStyleFactory::keys();
//    QApplication::setStyle(QStyleFactory::create("plastique"));
//    QApplication::setPalette(QApplication::style()->standardPalette());

    myPreview = new QPrintPreviewWidget(this);
    myPreview->fitToWidth();
    //生成预览界面
    connect(myPreview,QPrintPreviewWidget::paintRequested,this,[=](QPrinter * printer){
        QPainter painter(printer);//直接在打印机上画，文字不会失真
//        printer->setPageSize(QPrinter::A4);
        qDebug()<<"打印机分辨率："<<printer->resolution()<<"打印机纸张大小："<<printer->paperSize()<<"rect："<<printer->paperRect()<<"pagerect："<<printer->pageRect()<<"layout："<<printer->pageLayout();
        //默认dpi为96；A4 is defined by the standard as 210mm x 297mm, 8.27in x 11.69in, or 595pt x 842pt,793 x 1123px,755 x 1084
        //首先单位是像素，且计边界，定位位置是左下点

        //定义四种字体
        QFont font0;
        font0.setFamily("Song");
        font0.setPixelSize(24);//18号字，24像素，小二
        font0.setBold(true);

        QFont font1;
        font1.setFamily("Song");
        font1.setPixelSize(14);//五号

        QFont font2;
        font2.setFamily("Song");
        font2.setPixelSize(10);//六号

        //设置一支彩色的笔用于消记
        QPen colorPen;
        colorPen.setColor(Qt::green);
        //设置几种行距
        int height_0 = 24*1.3*2;//单倍行距为字号的1.3倍，96dPi时，像素数/96*72=磅数
        int height_1 = 14*1.3*1.5;//1.5倍行距

        //设置几种缩进
        int indent_0 = 14*6;//标准字间距是0磅，所以缩进了4个字符
        int indent_1 = 14*29;

        //设置表格属性
        //表头
        QString c0 = "编号";
        QString c1 = "类型";
        QString c2 = "主副";
        QString c3 = "截面";
        QString c4 = "左实测";
        QString c5 = "左间隙";
        QString c6 = "左超差";
        QString c7 = "右实测";
        QString c8 = "右间隙";
        QString c9 = "右超差";
        QString c10 = "中实测";
        QString c11 = "测量时间";
        QString c12 = "尺号";
        //设置表格宽度
        int w0 = 20;
        int w1 = 60;
        int w2 = 20;
        //设置y起始位置
        int y0 = 100;
        //设置表格高度
        int height_table = 10*1.3*1.5;

        //标题及说明文字
        QString title = "单组缓行器制动位数据报表";
        QString item_L_0 = QString("站场：");
        QString item_L_1 = QString("编号：");
        QString item_L_2 = "缓行器型号：";
        QString item_L_3 = "容许偏差：";
        QString item_L_3_0 = "第一钳口中心处：128+132-125";
        QString item_L_3_1 = "其他钳口中心处：";
        QString item_L_3_2 = "轨顶间最小距离：";
        QString item_L_4 = "统计：";
        QString item_L_4_0 = "超限总数：";
        QString item_L_4_1 = "第一钳口中心处：";
        QString item_L_4_1_0 = "已消记：";
        QString item_L_4_2 = "其他钳口中心处：";
        QString item_L_4_2_0 = "已消记：";
        QString item_L_4_3 = "轨顶间最小距离：";
        QString item_L_4_3_0 = "已消记：";
        QString item_R_0 = "检测日期：";
        QString item_R_1 = "打印日期：";
        QString item_R_2 = "页数：";

        int global_y = 0;
        {
        //画表头
        painter.setFont(font0);
        QRect rect = QRect(0,global_y,755,height_0);
        painter.drawText(rect,Qt::AlignCenter,title);
        global_y += height_0;
        //第二步
        painter.setFont(font1);
        rect = QRect(indent_0,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_L_0);

        rect = QRect(indent_1,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_R_0);
        global_y += height_1;
        //
        rect = QRect(indent_0,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_L_1);

        rect = QRect(indent_1,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_R_1);
        global_y += height_1;
        //
        rect = QRect(indent_0,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_L_2);

        rect = QRect(indent_1,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_R_2);
        global_y += height_1;
        //容许偏差
        rect = QRect(indent_0,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_L_3+item_L_3_0);

        rect = QRect(indent_1,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_L_3_1);
        global_y += height_1;
        //
        rect = QRect(indent_0+item_L_3.length()*14,global_y,755,height_1);//用中文字符
        global_y += height_1;
        painter.drawText(rect,Qt::AlignLeft,item_L_3_2);

        //统计
        rect = QRect(indent_0,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_L_4+item_L_4_0);
        global_y += height_1;

        rect = QRect(indent_0+item_L_4.length()*14,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_L_4_1);
        rect = QRect(indent_1,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_L_4_1_0);
        global_y += height_1;

        rect = QRect(indent_0+item_L_4.length()*14,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_L_4_2);
        rect = QRect(indent_1,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_L_4_2_0);
        global_y += height_1;

        rect = QRect(indent_0+item_L_4.length()*14,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_L_4_2);
        rect = QRect(indent_1,global_y,755,height_1);
        painter.drawText(rect,Qt::AlignLeft,item_L_4_2_0);
        global_y += height_1;

        //

        }
        //画表格
        painter.setFont(font2);
        painter.setRenderHint(QPainter::Antialiasing, true);//开启抗锯齿的渲染;使用该方法后，可解决所画的横线竖线粗细不一的问题
        int rowNum = 10; //定义行数，并对其判断，以实施翻页;755 x 1084
        //先画竖线
        int widthLis[14] = {40,70,40,40,45,45,45,45,45,45,45,45,65,40};//定义列宽
        const char * columnNames[14] = {"编号","类型","主副","截面","左实测","左间隙","左超差","右实测","右间隙","右超差","中实测","中超差","测量时间","尺号"};//表头
        const char * testData[14] = {"998", "其他钳口中心",	"主", "2", "250.00", "50", "+100.00", "140.00", "141", "81.00", "130", "-2696.00", "2020-12-30", "1311"};
        QVector<QLine> hLines;//横线
        QVector<QLine> vLines;//竖线

        for(int i = 0; i < rowNum; i++)
        {
            int x = 50;//记录x坐标起始值
            for(int j = 0; j < 14; j++)
            {
                vLines.append(QLine(QPoint(x,global_y),QPoint(x,global_y + height_table)));
                if(i == 0)
                {
                    QRect rect = QRect(x,global_y,widthLis[j],height_table);
                    painter.drawText(rect,Qt::AlignCenter,columnNames[j]);
                }
                else
                {
                    QRect rect = QRect(x,global_y,widthLis[j],height_table);
                    painter.drawText(rect,Qt::AlignCenter,testData[j]);
                }

                x += widthLis[j];

            }
            vLines.append(QLine(QPoint(x,global_y),QPoint(x,global_y + height_table)));//封口
            hLines.append(QLine(QPoint(50,global_y),QPoint(705,global_y)));
            global_y += height_table;
        }
        hLines.append(QLine(QPoint(50,global_y),QPoint(705,global_y)));//封口
        painter.drawLines(vLines);
        painter.drawLines(hLines);


//        rect = QRect(indent_0,global_y,755,height_1);
//        painter.drawText(19,16,"打印机测试字符串");
//        painter.drawText(0,8,"这是第三页");
//        painter.drawText(730,16,"打印机测试字符串2");//首先单位是像素，且计边界，定位位置是左下点
//        painter.drawText(300,200,"打印机测试字符串3");
//        QFontInfo info = painter.fontInfo();
//        qDebug()<<info.family();
//        qDebug()<<info.italic();
//        qDebug()<<info.pixelSize();
//        printer->newPage();
//        painter.drawText(30,20,"这是第二页");
//        printer->newPage();
//        painter.drawText(790,1100,"这是第三页");
//        painter.drawText(30,20,"打印机测试字符串3");
//        ui->textEdit->print(printer);//所以对比之前的方法，差别在哪里？

    });

    ui->verticalLayout_2->addWidget(myPreview);
    connect(ui->pushButton,&QPushButton::clicked,[=](){

        qDebug()<<ui->textEdit->textCursor().hasSelection();


    });
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        QPrinter printer;
        QPrintDialog *pDialog = new QPrintDialog(&printer,this);
//        pDialog->setStyle(QStyle a);
        if (ui->textEdit->textCursor().hasSelection())//光标选择的范围内
            pDialog->setOption(QAbstractPrintDialog::PrintSelection);//选择使能打印的方式，按页，按区域等
//         如果在对话框中按下了打印按钮，则执行打印操作

        if (pDialog->exec() == QDialog::Accepted)
        {
            ui->textEdit->print(&printer);
            //       // print the existing document by absoult path
            //        printFile("D:/myRSM.doc");
        }
    });
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        createPdf();
    });
    connect(ui->pushButton_5,&QPushButton::clicked,[=](){
        QPrinter printer;
            QPageSetupDialog pageSetUpdlg(&printer, this);
            if (pageSetUpdlg.exec() == QDialog::Accepted)
            {
                printer.setOrientation(QPrinter::Landscape);//横向
        }
        else
        {
            printer.setOrientation(QPrinter::Portrait);
        }
    });
}

void MainWindow::drawPic(QPrinter *printerPixmap)
{
    QPixmap pix = QPixmap(2400,1800);//定义一个像素图
    pix.setDevicePixelRatio(3.0);//实际像素与逻辑限速的比值，用来产生高DPI图片
    //这个函数算是画模板的函数吧，毕竟打印时有模板的
    createPix(&pix);//PixelRatio影响这里的坐标系统
    QRect sRect = pix.rect();
//    qDebug()<<"pix.rect:"<<sRect;
//    QString sFilePix = "./test3.jpg";
//    pix.save(sFilePix);

    //纵向：Portrait 横向：Landscape
//    printerPixmap->setOrientation(QPrinter::Landscape);


    //获取界面的图片
    QPainter painterPixmap(printerPixmap);//挂在对象树上

//    painterPixmap.begin(printerPixmap);//设置PaintDevice为打印机

//    painterPixmap.setViewport(0,0,800,600);改变此值会改使得只适用printer的一部分画面
//    painterPixmap.setWindow(0,0,800,600);


//    QRect rect = painterPixmap.viewport();//
    QRect tRect = painterPixmap.window();//注意这里是定位到了printer的pagerect，且单位是px
    qDebug()<<"tRect:"<<tRect<<"sRect:"<<sRect;

//    int x = rect.width() / pix.width();
//    int y = rect.height() / pix.height();


    //设置图像长宽是原图的多少倍

//    painterPixmap.scale(x, y);//应该是缩小
//    painterPixmap.drawPixmap(0, 0, pix);
    painterPixmap.drawPixmap(tRect,pix,sRect);//会自适应缩放
//    delete painterPixmap;
}

void MainWindow::createPix(QPixmap *pix)
{
    qDebug()<<"定位一";
    QPainter *painter = new QPainter(pix);//不必挂在对象树上
    qDebug()<<"定位二";
//    painter->begin(pix);//用构造和析构代替begin和end
    painter->setRenderHint(QPainter::TextAntialiasing, true);//开启抗锯齿的渲染

//    qDebug()<<"画笔的信息";
//    qDebug()<<painter->viewport();
//    qDebug()<<painter->window();//所以应该与指定的paintDevice的大小一致，是被动的
    // 设置画笔颜色、宽度
//    painter->setPen(QPen(QColor(255, 255, 255),2));

    // 设置画刷颜色
//    painter->setBrush(QColor(255, 255, 255));
    QRect rect(0,0,2400,1800);
    //整张图设置画刷白底
    painter->fillRect(rect,QColor(255, 255, 255));
//    painter->drawRect(rect);
    //画数据部分的线条
    painter->setPen(QPen(QColor(0, 0, 0), 3));//涉及到了类型转换
    QVector<QLine> lines;
    lines.append(QLine(QPoint(50,50),QPoint(750,50)));//上边
    lines.append(QLine(QPoint(750,50),QPoint(750,550)));//右边
    lines.append(QLine(QPoint(50,550),QPoint(750,550)));//下边
    lines.append(QLine(QPoint(50,50),QPoint(50,550)));//左边
    lines.append(QLine(QPoint(50,120),QPoint(750,120)));//名称下边
    lines.append(QLine(QPoint(50,180),QPoint(750,180)));//信息下边
    lines.append(QLine(QPoint(50,200),QPoint(750,200)));//条目下边
    lines.append(QLine(QPoint(50,490),QPoint(750,490)));//数据下边
    lines.append(QLine(QPoint(120,180),QPoint(120,200)));//类型分割边
    lines.append(QLine(QPoint(190,180),QPoint(190,200)));//类型分割边
    lines.append(QLine(QPoint(260,180),QPoint(260,200)));//类型分割边
    lines.append(QLine(QPoint(330,180),QPoint(330,200)));//类型分割边

    painter->drawLines(lines);
    QFont font;
    font.setPointSize(13);//单位是pt，磅
//    font.setPixelSize(13);//单位是px，像素
    font.setFamily("黑体");
//    font.setWeight(75);

    font.setItalic(true);
    painter->setFont(font);
    //第一部分
    painter->drawText(50,50,700,40,Qt::AlignCenter,"哈尔滨工程大学");//单位名称
    painter->drawText(QPoint(650,110),"No:");
    font.setPointSize(20);
    painter->setFont(font);
    painter->drawText(50,80,700,40,Qt::AlignCenter,"年度总结报告");//报告名称
    font.setPointSize(10);
    painter->setFont(font);
    //第二部分
    painter->drawText(50,120,700,60,Qt::AlignVCenter,QString("样本ID： ")+QString("11111111"));
    painter->drawText(210,120,700,60,Qt::AlignVCenter,QString("标本类型： ")+QString("ABC"));
    painter->drawText(370,120,700,60,Qt::AlignVCenter,QString("检测方法： "));
    painter->drawText(600,120,700,60,Qt::AlignVCenter,QString("仪器： "));
    //第三部分
    painter->drawText(50,180,70,20,Qt::AlignCenter,"序号");
    painter->drawText(120,180,70,20,Qt::AlignCenter,"检测项目");
    painter->drawText(190,180,70,20,Qt::AlignCenter,"Ct");
    painter->drawText(260,180,70,20,Qt::AlignCenter,"检测下限");
    painter->drawText(330,180,70,20,Qt::AlignCenter,"结果");
    //第四部分
    painter->drawText(50,210,70,20,Qt::AlignCenter,"1");
    painter->drawText(120,210,70,20,Qt::AlignCenter,"我");
    painter->drawText(190,210,70,20,Qt::AlignCenter,"真的");
    painter->drawText(260,210,70,20,Qt::AlignCenter,"不知道");
    painter->drawText(330,210,70,20,Qt::AlignCenter,"写啥");
    //第五部分
    painter->drawText(50,490,700,30,Qt::AlignVCenter,QString("送检者： "));
    painter->drawText(230,490,700,30,Qt::AlignVCenter,QString("代码： "));
    painter->drawText(410,490,700,30,Qt::AlignVCenter,QString("检验者： "));
    painter->drawText(590,490,700,30,Qt::AlignVCenter,QString("审核者： "));
    painter->drawText(50,520,700,30,Qt::AlignVCenter,QString("送检日期： "));
    painter->drawText(410,520,700,30,Qt::AlignVCenter,QString("报告日期： "));
    delete painter;
    //    总结：画图方法（用pixmap间接传递），文字有锯齿，且生成PDF不可复制
}



void MainWindow::createPdf()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出PDF文件"), QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        // 如果文件后缀为空，则默认使用.pdf
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QPrinter printer;
        // 指定输出格式为pdf
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        ui->textEdit->print(&printer);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_6_clicked()
{
//    QPrinter printer(QPrinter::ScreenResolution);//设置分辨率dpi，默认96
//    QPrinter printer(QPrinter::HighResolution);
    QPrinter printer;
//    printer.setResolution(100);//设置100dpi影响paint的viewport(实际像素数)
//    printer.setWinPageSize(2);
    printer.setPaperSize(QSizeF(1000,600),QPrinter::Point);//单位是像素点
//    printer.setOrientation(QPrinter::Landscape);
//    printer.setPaperSize(QPrinter::A4);//A4 is defined by the standard as 210mm x 297mm, 8.27in x 11.69in, or 595pt x 842pt,这里应该是逻辑分辨率
    qDebug()<<"打印机分辨率："<<printer.resolution()<<"打印机纸张大小："<<printer.paperSize()<<"rect："<<printer.paperRect()<<"pagerect："<<printer.pageRect()<<"layout："<<printer.pageLayout();
    //paperRect比pageRect大，因为有页边距的缘故，单位是px
    QPrintPreviewDialog preview(&printer,this);//创建打印预览对话框
//    preview.setMinimumSize(1920,1080);
//    preview.setFixedSize(1000,800);
    connect(&preview,QPrintPreviewDialog::paintRequested,this,MainWindow::drawPic);//不知道为什么this不能省略
    preview.setGeometry(650,100,600,400);
    preview.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
//    qDebug()<<"进来了";
//    QPrinter printer;
//    QPrintPreviewDialog * preview = new QPrintPreviewDialog(&printer,this);
//    connect(preview,QPrintPreviewDialog::paintRequested,[=](QPrinter * prt){
//        qDebug()<<"signal:paintRequested"<<prt;
//       ui->textEdit->print(prt);//打印预览会生成一个打印机，把这个打印机device使用即打印预览
//    });
//    preview->exec();

    QPrintPreviewWidget * preview = new QPrintPreviewWidget(this);
    preview->resize(600,800);
//    preview->fitToWidth();
    connect(preview,QPrintPreviewWidget::paintRequested,this,[=](QPrinter * printer){
//        QPainter painter(printer);//直接在打印机上画，文字不会失真
//        painter.drawText(20,20,"打印机测试字符串");
//        printer->newPage();
//        painter.drawText(30,20,"这是第二页");
        ui->textEdit->print(printer);
    });
    preview->show();//会出现，没问题，默认位置
//    qDebug()<<"CurrentPage:"<<preview->currentPage();
//    qDebug()<<"Qrientation:"<<preview->orientation();
//    qDebug()<<"pageCount:"<<preview->pageCount();
    qDebug()<<"zoomFactor:"<<preview->zoomFactor();
    qDebug()<<"zoomMode:"<<preview->zoomMode();


}

void MainWindow::on_pushButton_7_clicked()
{
    QProgressDialog dlg(this);
    dlg.setWindowTitle("进度条");
    dlg.setLabelText("正在上传数据");
    dlg.setMinimum(0);
    dlg.setMaximum(100);
    dlg.setValue(35);
    dlg.exec();
}
