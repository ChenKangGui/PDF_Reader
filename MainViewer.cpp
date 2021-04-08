#include "MainViewer.h"
#include <QStatusBar>

MainViewer::MainViewer(QWidget *parent) :  QMainWindow(parent)
{

	resize(QSize(800,600)); //设置初始窗口大小

    statusBar(); //显示状态栏
#if 0
    QAction *openAction = new QAction(QIcon(":/image/open"), "打开", this);
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setStatusTip("打开文件");
    connect(openAction, &QAction::triggered, this, &MainViewer::OpenFile);

    QAction *saveAction = new QAction(QIcon(":/image/save"), "保存", this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip("保存文件");
    connect(saveAction, &QAction::triggered, this, &MainViewer::SaveFile);

    QAction *quitAction = new QAction(QIcon(":/image/close"), "退出", this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    quitAction->setStatusTip(tr("退出程序"));
    connect(quitAction, &QAction::triggered, this, &MainViewer::CloseFile);

    QAction *zoomInAction = new QAction(QIcon(":/image/zoom_in"), "放大", this);
    zoomInAction->setStatusTip("放大");
    connect(zoomInAction, &QAction::triggered, this, &MainViewer::ZoomIn);

    QAction *zoomOutAction = new QAction(QIcon(":/image/zoom_out"), "缩小", this);
    zoomOutAction->setStatusTip("缩小");
    connect(zoomOutAction, &QAction::triggered, this, &MainViewer::ZoomOut);

    QAction *resetAction = new QAction(QIcon(":/image/zoom_reset"), "重置", this);
    resetAction->setStatusTip("重置大小");
    connect(resetAction, &QAction::triggered, this, &MainViewer::ZoomReset);

    QAction *previousAction = new QAction(QIcon(":/image/previouspage"), "上一页", this);
    previousAction->setStatusTip("上一页");
    connect(previousAction, &QAction::triggered, this, &MainViewer::PreviousPage);

    QAction *NextAction = new QAction(QIcon(":/image/nextpage"), "下一页", this);
    NextAction->setStatusTip("下一页");
    connect(NextAction, &QAction::triggered, this, &MainViewer::NextPage);

    //第一种添加menu方法
    QMenu *menu = menuBar()->addMenu(tr("文件(F)"));
    menu->addAction(openAction);
    menu->addAction(saveAction);
    menu->addSeparator();
    menu->addAction(quitAction);

    //第二种添加menu方法
    QMenu *editMenu = new QMenu("编辑(E)");
    menuBar()->addMenu(editMenu);

    QToolBar *openTool = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, openTool);
    openTool->addAction(openAction);
    openTool->addAction(saveAction);
    openTool->addSeparator();
    openTool->addAction(quitAction);
    openTool->addSeparator();
    openTool->addAction(zoomInAction);
    openTool->addAction(resetAction);
    openTool->addAction(zoomOutAction);
    openTool->addSeparator();
    openTool->addAction(previousAction);
    openTool->addAction(NextAction);

    m_MainMdiArea = new MultiViwer();
    setCentralWidget(m_MainMdiArea);
    connect(m_MainMdiArea, &MultiViwer::subWindowActivated, this, &MainViewer::UpdataPageNum);
    m_MainMdiArea->setViewMode(QMdiArea::TabbedView);

#endif
#if 1

	CreatActions();
	CreatMenus();
	CreatToolBar();

	m_MainMdiArea = new MultiViwer();
	setCentralWidget(m_MainMdiArea);
	connect(m_MainMdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(UpdataPageNum()));
	m_MainMdiArea->setViewMode(QMdiArea::TabbedView);
#endif
}

MainViewer::~MainViewer()
{

}

void MainViewer::CreatActions()
{
	//打开动作
	m_OpenAction = new QAction(QIcon(":/image/open"), "打开", this);
	m_OpenAction->setShortcut(tr("Ctrl+O"));
	m_OpenAction->setStatusTip(tr("打开文件"));
	connect(m_OpenAction,SIGNAL(triggered()), this, SLOT(OpenFile()));

	//保存动作
	m_SaveAction = new QAction(QIcon(":/image/save"), "保存", this);
	m_SaveAction->setShortcut(tr("Ctrl+S"));
	m_SaveAction->setStatusTip(tr("保存文件"));
	connect(m_SaveAction,SIGNAL(triggered()), this, SLOT(SaveFile()));

	//退出动作
	m_QuitAction = new QAction(QIcon(":/image/close"), "退出", this);
	m_QuitAction->setShortcut(tr("Ctrl+Q"));
	m_QuitAction->setStatusTip(tr("退出程序"));
	connect(m_QuitAction,SIGNAL(triggered()),this,SLOT(CloseFile()));

	//放大
	m_ZoomIn = new QAction(QIcon(":/image/zoom_in"), "放大", this);
	m_ZoomIn->setStatusTip(tr("放大"));
	connect(m_ZoomIn, SIGNAL(triggered()), this, SLOT(ZoomIn()));

	//缩小
	m_ZoomOut = new QAction(QIcon(":/image/zoom_out"), "缩小", this);
	m_ZoomOut->setStatusTip(tr("缩小"));
	connect(m_ZoomOut, SIGNAL(triggered()), this, SLOT(ZoomOut()));

	//重置大小
	m_ZoomReset = new QAction(QIcon(":/image/zoom_reset"), "重置", this);
	m_ZoomReset->setStatusTip(tr("重置"));
	connect(m_ZoomReset, SIGNAL(triggered()), this, SLOT(ZoomReset()));

	//跳转上一页
	m_PreviousPage = new QAction(QIcon(":/image/previouspage"), "上一页", this);
	m_PreviousPage->setStatusTip(tr("上一页"));
	connect(m_PreviousPage, SIGNAL(triggered()), this, SLOT(PreviousPage()));

	//跳转下一页
	m_NextPage = new QAction(QIcon(":/image/nextpage"), "下一页", this);
	m_NextPage->setStatusTip(tr("下一页"));
	connect(m_NextPage, SIGNAL(triggered()), this, SLOT(NextPage()));

}

void MainViewer::CreatMenus()
{
	m_FileMenu = menuBar()->addMenu(tr("文件(F)"));
	m_FileMenu->addAction(m_OpenAction);//往菜单栏内添加动作
	m_FileMenu->addAction(m_SaveAction);
	m_FileMenu->addSeparator();
	m_FileMenu->addAction(m_QuitAction);

	//两种添加menu的方法
	m_EditMenu = new QMenu("编辑(E)");
	menuBar()->addMenu(m_EditMenu);

	m_WindowMenu = menuBar()->addMenu(tr("视图(V)"));
	m_HelpMenu = menuBar()->addMenu(tr("帮助(H)"));
}

void MainViewer::CreatToolBar()
{
	// 打开工具条
	m_FileTool = new QToolBar(this);
	addToolBar(Qt::TopToolBarArea, m_FileTool);//把这两个工具栏添加到窗口
	m_FileTool->addAction(m_OpenAction);//向工具栏内添加动作
	m_FileTool->addAction(m_SaveAction);
	m_FileTool->addSeparator();
	m_FileTool->addAction(m_QuitAction);

	// zoom工具条
	m_ZoomTool = new QToolBar(this);
	addToolBar(Qt::TopToolBarArea, m_ZoomTool);
	m_ZoomTool->addAction(m_ZoomIn);
	m_ZoomTool->addAction(m_ZoomReset);
	m_ZoomTool->addAction(m_ZoomOut);

	// 页码工具条
	m_PageTool = new QToolBar(this);
	addToolBar(Qt::TopToolBarArea, m_PageTool);
	m_PageTool->addAction(m_PreviousPage);
	m_PageTool->addAction(m_NextPage);

	m_PageNumLineEdit = new QLineEdit();
	m_PageTool->addWidget(m_PageNumLineEdit);
	m_PageNumLineEdit->setFixedWidth(30);
	m_PageNumLineEdit->setText("0");

	m_PageCountLabel = new QLabel();
	m_PageTool->addWidget(m_PageCountLabel);
	m_PageCountLabel->setFixedWidth(30);
	m_PageCountLabel->setText(" / 0");

	connect(m_PageNumLineEdit, SIGNAL(textChanged()), this, SLOT(UpdataPageNum()));
	connect(m_PageNumLineEdit, SIGNAL(returnPressed()), this, SLOT(GotoPage()));
}

void MainViewer::OpenFile()
{
	QString strFilter = "*.pdf";
	QString strDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
	m_strFileName = QFileDialog::getOpenFileName(this,"Reader", strDir, strFilter);

	if(m_strFileName.isEmpty())
		return;

	NewFile();
	RefreshWindow();
}

void MainViewer::NewFile()
{
	ChildViewer *childViewer = CreateChildViewer();

	int index = m_strFileName.lastIndexOf("/");
	QString strFileName = m_strFileName.mid((index + 1), (m_strFileName.size() - index));
	childViewer->setWindowTitle(strFileName);
	childViewer->show();
}

ChildViewer* MainViewer::CreateChildViewer()
{
	ChildViewer *child = new ChildViewer(this);
	m_MainMdiArea->addSubWindow(child);
	return child;
}

void MainViewer::SaveFile()
{

}

void MainViewer::CloseFile()
{
	this->close();
}


ChildViewer* MainViewer::getCurChildViewer()
{
	QMdiSubWindow* mdiSubWindow = m_MainMdiArea->currentSubWindow();
	if (mdiSubWindow == NULL)
		return NULL;

	ChildViewer* child = static_cast<ChildViewer*>(mdiSubWindow->widget());
	Q_ASSERT(child != NULL);

	return child;
}

void MainViewer::ZoomIn()
{
	ChildViewer* child = getCurChildViewer();
	if (child == NULL)
		return;

	child->ZoomIn();
	RefreshWindow();
}

void MainViewer::ZoomOut()
{
	ChildViewer* child = getCurChildViewer();
	if (child == NULL)
		return;

	child->ZoomOut();
	RefreshWindow();
}

void MainViewer::ZoomReset()
{
	ChildViewer* child = getCurChildViewer();
	if (child == NULL)
		return;

	child->ZoomReset();
	RefreshWindow();
}

void MainViewer::PreviousPage()
{
	ChildViewer* child = getCurChildViewer();
	if (child == NULL)
		return;
	child->PreviousPage();
}

void MainViewer::NextPage()
{
	ChildViewer* child = getCurChildViewer();
	if (child == NULL)
		return;

	child->NextPage();

}

void MainViewer::UpdataPageNum()
{
	ChildViewer* child = getCurChildViewer();
	if (child == NULL)
		return;
	int nCurPageNum = child->getCurPageNum() + 1;
	QString str = QString::number(nCurPageNum);
	m_PageNumLineEdit->setText(str);

	int nCurPageCount = child->getPageCount();
	str = QString::number(nCurPageCount);
	str = " / " + str;
	m_PageCountLabel->setText(str);
}

void MainViewer::GotoPage()
{
	ChildViewer* child = getCurChildViewer();
	if (child == NULL)
		return;

	QString str = m_PageNumLineEdit->text();
	int nPage = str.toInt() - 1;
	child->GotoPage(nPage);

}

void MainViewer::RefreshWindow()
{
	ChildViewer* child = getCurChildViewer();
	if (child == NULL)
		return;

	child->RefreshWindow();
	UpdataPageNum();
}




