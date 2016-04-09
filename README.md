
# Qt实现中国象棋 

这是用人工智能算法实现人机对战的莪一个小例子，其中用到了最大最小值算法，和优化-剪枝算法。算法的实现在`singlegame`类中 从 函数`computer`开始。

Qt中国象棋 目前实现了人机对战，后续会添加网络对战，和人人对战，并会移植到`Android`平台上。程序包含以下几个部分：

1. `Board`类，这个类主要用来实现棋盘和棋子的绘制以及走棋的规则。
2. `Stone`类，这个类是棋子类，定义了棋子的属性。
3. `Step`类，这个类是步数类，用来保存记录棋子的移动，以便悔棋用。
3. `SingleGame`类，这个类是人机对战类，继承自`Board`类，实现了简单的神经网络算法。
4. `Ctrlpanel`类，这个类是控制面板类，监听`back`（返回）操作。
5. `MainWnd`类，主窗口类，这个类实现总的窗口。
6. `ChooseDlg`类，这个类是选择对话框类，实现用户的选择对战的类型。

程序运行图：

![选择对战类型](http://7xsc1o.com1.z0.glb.clouddn.com/qt%E4%B8%AD%E5%9B%BD%E8%B1%A1%E6%A3%8B%E9%80%89%E6%8B%A9%E5%AF%B9%E6%88%98%E7%B1%BB%E5%9E%8B.png)

![界面](http://7xsc1o.com1.z0.glb.clouddn.com/qt%E4%B8%AD%E5%9B%BD%E8%B1%A1%E6%A3%8B%E7%95%8C%E9%9D%A2.png)

![人机对战](http://7xsc1o.com1.z0.glb.clouddn.com/qt%E4%B8%AD%E5%9B%BD%E8%B1%A1%E6%A3%8B%E4%BA%BA%E6%9C%BA%E5%AF%B9%E6%88%98.png)
