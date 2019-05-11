#! /bin/bash
#  使用说明 ：
#  1. 更改Dataset的值为需要测评的数据集的根路径，例如 Dataset="/media/a901/高宇的硬盘/slam资料/数据集/tum/rgbd_dataset_freiburg3_walking_rpy" 
#  2. 更改ImgPrefix的值为保存的png图片的前缀，Num是想要测评该数据的次数。
#  3. 一定要记得！！！更换数据集后，把png txt文件夹下的文件全部拷出来单独存，尤其是txt文件，否则分不清是哪个数据集测评的结果了。由于记录下的txt文件里的数据之间都有空格作为分隔符，所以可以直接粘贴到libreOffice软件 的excel表格里面，选择分隔选项为 空格 就可以完美整理到表格中啦。 不过png 和txt文件夹不要删除哦，否则无法自动创建的。
#  4. 在终端运行 ./orbEvaluate.sh 即可

Dataset="/home/zoe/data/rgbd_dataset_freiburg1_room"
ImgPrefix="1_room"
Num=1

slamArg="/home/zoe/catkin_ws/src/ORB_SLAM2_LFNet/Vocabulary/LFNET500voc.txt /home/zoe/catkin_ws/src/ORB_SLAM2_LFNet/Examples/RGB-D/TUM1.yaml "$Dataset" "$Dataset"/associate.txt"

for i in $(seq $Num)
do
echo "start test"
/home/zoe/catkin_ws/src/ORB_SLAM2_LFNet/Examples/RGB-D/rgbd_tum $slamArg
python evaluate_rpe.py $Dataset/groundtruth.txt /home/zoe/catkin_ws/src/ORB_SLAM2_LFNet/CameraTrajectory.txt --fixed_delta --plot png/${ImgPrefix}_RPE_LFNET_${i}.png --verbose
python evaluate_ate.py $Dataset/groundtruth.txt /home/zoe/catkin_ws/src/ORB_SLAM2_LFNet/CameraTrajectory.txt --plot png/${ImgPrefix}_ATE_LFNET_${i}.png --verbose
done

