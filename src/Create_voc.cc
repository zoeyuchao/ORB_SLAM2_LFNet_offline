#include <cstdlib>
#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Thirdparty/DBoW2/DBoW2/TemplatedVocabulary.h"
#include "Thirdparty/DBoW2/DBoW2/BowVector.h"
#include "Thirdparty/DBoW2/DBoW2/FeatureVector.h"
#include "Thirdparty/DBoW2/DBoW2/FLFNET.h"

using namespace DBoW2;
using namespace cv;
using namespace std;


int main()
 {
    //0. 参数
    string strAssociationFilename = "/home/zoe/data/rgbd_dataset_freiburg1_room/associate.txt";
	vector<double> vTimestamps;
    string strLFNetPath = "/home/zoe/data/rgbd_dataset_freiburg1_room/LFNet_DBOW/";
    int kpts_num = 500;//超参数,可以根据情况修改 每张照片提取特征点的个数 1000个,目前是跟ORB本身的个数是一样的.
    float ffeats[kpts_num][256] = { 0 };//定义一个1000*256的矩阵，用于存放feats数据
    vector<KeyPoint> mvKpts;
	vector<vector<float>> dspts;
	typedef TemplatedVocabulary<FLFNET::TDescriptor, FLFNET> LFNETVocabulary;
	//!!Note: 9 and 3 is the parameters you may want to change
	LFNETVocabulary lfnet(10, 6, TF_IDF, L1_NORM);
	vector<vector<vector<float>>> features;

    //1. load features
    ifstream fAssociation;
    fAssociation.open(strAssociationFilename.c_str());
    while(!fAssociation.eof())
    {
        string s;
        getline(fAssociation,s);
        if(!s.empty())
        {
            stringstream ss;
            ss << s;
            double t;
            string sRGB, sD;
            ss >> t;
            vTimestamps.push_back(t);
        }
    }
    int nImages = vTimestamps.size();// 一共多少照片
    //features.clear();
	//features.reserve(nImages);
    //dspts.reserve(kpts_num);
    cout << "all images number = " << nImages <<endl;
 
	for(int ni=0; ni<nImages; ni=ni+4)
    {
        double tframe = vTimestamps[ni];
        string strTimeStamp = to_string(tframe);
        ifstream featsfile;//定义读取文件流，相对于程序来说是in
        featsfile.open(strLFNetPath + strTimeStamp + "_feats.txt");//打开文件

        for (int i = 0; i < kpts_num; i++)//定义行循环
        {
            vector<float> dspt;
            dspt.resize(256);
            for (int j = 0; j < 256; j++)//定义列循环
            {
                featsfile >> ffeats[i][j];//读取一个值（空格、制表符、换行隔开）就写入到矩阵中，行列不断循环进行
                if(ffeats[i][j] < -0.3)
                    dspt[j] = -0.3;//0
                else if(ffeats[i][j] > 0.3)
                    dspt[j] = 0.3;//255
                else
                    dspt[j]= ffeats[i][j];
                //cout << "LFNet feats : " << ffeats[i][j] << endl;
            }
            dspts.push_back(dspt); 
            //cout << "dspts size now is: " << dspts.size() << endl;
			//must pre-initialize, to allocate memery			          
        }
        features.push_back(dspts);
        cout << "features size now is: " << features.size() << endl;
        featsfile.close();//读取完成之后关闭文件
    }
	cout << "creating the vocabulary..." << endl;
	lfnet.create(features);
	cout << "saving the vocabulary to text file..." << endl;
	lfnet.saveToTextFile("/home/zoe/catkin_ws/src/ORB_SLAM2_LFNet/Vocabulary/LFNET500voc.txt");
	return 0;
}
