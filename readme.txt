LargeVis用于大规模和高维数据的可视化。它现在支持可视化高维特征向量和网络。该软件包还包含一个用于构造K-最近邻图（K-NNG）的非常有效的算法。
原论文[(Tang, Liu, Zhang and Mei)](https://arxiv.org/abs/1602.00370)

改动主要是为了windows下我自己使用方便，linux环境没有试过，应该没什么大问题，有问题自己调试下吧，原理没改过。

改动的地方：
１、使用c++11随机数库替换[原创官方实现LargeVis模型](https://github.com/lferry007/LargeVis)需要外部软件包，包括Linux和OS X上的GSL（GNU Scientific Library）或Windows上的BOOST，用于生成随机数折方式。
２、使用c++11多线程，替换了原有方式。



说明：
	ANNOY中
		mman.cpp
		mman.h
	是在windows环境下的文件。使用的是 from https://code.google.com/p/mman-win32/
	在linux中并不使用，而是使用sys/mman.h。

环境,编译
	C++11
	python
	
	windows环境,编译
		
		安装mingw-w64-install.exe，支持c++11，因为代码中的线程改为c++11自有thread库，方便多平台使用。默认安装路径（C:\Program Files\mingw-w64\x86_64-7.3.0-posix-seh-rt_v5-rev0\mingw64\bin），如果不是修改PATH.bat文件
		
		build.bat

	linux 环境,编译
	
		build.sh
		
运行
	windows环境
		cd Examples\CondMat
		执行　run_CondMat.bat　
		
		生成　CondMat_vec2D.txt　二维数据　和　CondMat_plot.png　图
		
	linux环境
		cd Examples\CondMat
		执行　run_CondMat.sh
		
		
	
输入文件的格式说明：
	对于高维特征向量，输入文件的格式应该如下：第一行指定特征向量的数量和维数（在下面的例子中，500个向量具有10个维度），并且接下来的500行中的每一行都描述了一个带有10个浮点数的特征向量。

	500 10
	1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
	1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
	...
	...
	1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
	
	对于网络，输入文件的每一行都是有向边。对于每个无向边，用户必须使用两个边来表示它。例如，
	0 1 2.5
	1 0 2.5
	2 5 4.5
	5 2 4.5
	3 10 3.0
	...
	...
	495 498 1.5

参数说明：

LargeVis命令参数：

	-input：输入特征矢量或网络文件（请参阅输入格式的示例文件夹）。
	-output：低维表示的输出文件。

	其他可选参数还包括：

	-fea：指定输入文件是高维特征向量（1）还是网络（0）。缺省值是1。
	-threads：线程数。默认值是8。
	-outdim：较低的维度LargesVis学习可视化（通常2或3）。缺省值是2。
	-samples：图形布局的边缘样本数（以百万为单位）。默认值设置为'''data size / 100'''（百万）。
	-prop：在K-NNG构造状态下邻居传播的次数，通常小于3。默认值为3。
	-alpha：初始学习率。默认值是1.0。	-trees：用于构建K-NNG的随机投影树的数量。50对大多数情况是足够的，除非你正在处理非常大的数据集（例如数据大小超过500万），并且较少的树适用于较小的数据集。默认值根据数据大小设置。
	-neg：用于负样本的负样本数量。缺省值是5。
	-neigh：K-NNG中的邻居数量（K），通常设置为三次困惑度。默认值是150。
	-gamma：分配给负边的权重。缺省值是7。
	-perp：用于确定K-NNG中的边权重的困惑性。默认值是50。

	
如果您使用LargeVis来显示数据，请引用以下文章。##引文

@inproceedings{tang2016visualizing,
  title={Visualizing Large-scale and High-dimensional Data},
  author={Tang, Jian and Liu, Jingzhou and Zhang, Ming and Mei, Qiaozhu},
  booktitle={Proceedings of the 25th International Conference on World Wide Web},
  pages={287--297},
  year={2016},
  organization={International World Wide Web Conferences Steering Committee}
}
##确认此软件包的一些方法来自LargeVis作者LINE（大规模信息网络嵌入）的先前工作。