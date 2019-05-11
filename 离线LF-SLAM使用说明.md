# 离线LF-SLAM使用说明

## 1. 安装

跟ORB-SLAM2完全一样，从下面的[链接](https://pan.baidu.com/s/1C1dFLPhTMbhjGQWt-K_39w  )(提取码：ew2r )里把字典下载下来，并且在根目录下进行解压。

## 2.使用

- 下载一个我自己做好的测试集，[链接](https://pan.baidu.com/s/19HQOypHpyBd4GzrkVWPtsQ
  )（提取码：chtj）[链接](https://pan.baidu.com/s/1ctpvOlROBFRefGohW801-A)（提取码：z6l8）
- 在***~/catkin_ws/src/ORB_SLAM2_LFNet***路径下运行下列语句:

[^]: 注意:运行前要先运行LFNet,将特征提前提取完毕(这一步已经做完,暂时不需要再运行),存储在/home/zoe/data/rgbd_dataset_freiburg1_room/LFNet文件里,如果改动了LF-SLAM的代码,先在build下进行编译.

```bash
./Examples/RGB-D/rgbd_tum Vocabulary/LFNET500voc.txt Examples/RGB-D/TUM1.yaml /home/zoe/data/rgbd_dataset_freiburg1_room /home/zoe/data/rgbd_dataset_freiburg1_room/associate.txt
```

## 3.说明

1. 本程序基于ORB-SLAM2框架,将ORB特征全面替换为LFNET特征,文中所有改动均已加了注释//zoe time,可以全文搜索zoe,寻找改动的地方.
2. 由于LFNet和ORB特征不尽相同,所以level这个信息目前是全面屏蔽的.之后再进行改进.
3. 程序还有很多超参数,不知道应该怎么进行修改,目前就是暂时可以按照正常的程序运行,但是精度不如ORB本身,差了一个量级.
4.  字典生成代码在Vocabulary文件夹下的create_voc.bin,原始代码在src下的create_voc.cc文件,如果需要修改,请先修改源码,然后在build文件里进行编译,同时注意,有可能还要进一步修改DBOW2三方库下的文件,里面有FLFNET.cc和FLFNET.h文件,这两个文件是我新加的,适用于新的LFNET特征.
5. 根据不同的特征距离计算方式,可以有平方差及sqrt(平方差)两种方式,也可以有一张照片提取500个特征点或者1000个特征点,根据此,我生成了几个词袋模型.
      1. LFNET500voc.txt表示500个特征点,平方差.
      2. LFNET500sqrtvoc.txt表示500个特征点,sqrt(平方差).
      3. LFNET1000voc.txt表示1000个特征点,平方差.
6. **精度评价**
   在eval_script文件夹下,有2个sh脚本,直接运行即可,他们的作用分别是;
7.   1. LFNET_Evaluate.sh:进行LF-SLAM的性能分析
       2. ORB_Evaluate.sh:进行ORB-SLAM2的性能分析
[^]: 运行脚本前请看脚本里的备注,注意路径/数据集名称是否需要修改,如果在此电脑运行,则不需要更改.
​	现在存了LFNET500和LFNET1000以及ORB三个文件夹,里面有对应的性能分析文件,供参考.

## 4. LFNet

如果需要自己制作数据集，或者其他操作，请移步这个[仓库](https://github.com/zoeyuchao/LFNet_modify.git)。里面的jupyter文件run里面有记录

