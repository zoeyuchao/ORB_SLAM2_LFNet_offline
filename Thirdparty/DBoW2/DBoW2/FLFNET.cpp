/**
 * File: FLFNET.cpp
 * Date: oct 2018
 * Author: Zoe
 * Description: functions for LFNet descriptors
 * License: see the LICENSE.txt file
 *
 * Distance function has been modified 
 *
 */

 
#include <vector>
#include <string>
#include <sstream>
//#include <stdint-gcc.h>

#include "FLFNET.h"

using namespace std;

namespace DBoW2 {

// --------------------------------------------------------------------------

const int FLFNET::L=256;

void FLFNET::meanValue(const std::vector<FLFNET::pDescriptor> &descriptors, 
  FLFNET::TDescriptor &mean)
{
  mean.resize(0);
  mean.resize(FLFNET::L, 0);
  
  float s = descriptors.size();
  
  vector<FLFNET::pDescriptor>::const_iterator it;
  for(it = descriptors.begin(); it != descriptors.end(); ++it)
  {
    const FLFNET::TDescriptor &desc = **it;
    for(int i = 0; i < FLFNET::L; i += 4)
    {
      mean[i  ] += desc[i  ] / s;
      mean[i+1] += desc[i+1] / s;
      mean[i+2] += desc[i+2] / s;
      mean[i+3] += desc[i+3] / s;
    }
  }
}

// --------------------------------------------------------------------------
  
float FLFNET::distance(const FLFNET::TDescriptor &a,
  const FLFNET::TDescriptor &b)
{
  float sqd = 0.;
  for(int i = 0; i < FLFNET::L; i += 4)
  {
    sqd += (a[i  ] - b[i  ])*(a[i  ] - b[i  ]);
    sqd += (a[i+1] - b[i+1])*(a[i+1] - b[i+1]);
    sqd += (a[i+2] - b[i+2])*(a[i+2] - b[i+2]);
    sqd += (a[i+3] - b[i+3])*(a[i+3] - b[i+3]);
  }
  //sqd = sqrt(sqd);
  return sqd;
}

// --------------------------------------------------------------------------
  
std::string FLFNET::toString(const FLFNET::TDescriptor &a)
{
  stringstream ss;
    for(int i = 0; i < FLFNET::L; ++i)
    {
      ss << a[i] << " ";
    }
    return ss.str();
}

// --------------------------------------------------------------------------
  
void FLFNET::fromString(FLFNET::TDescriptor &a, const std::string &s)
{
  a.resize(FLFNET::L);
  
  stringstream ss(s);
  for(int i = 0; i < FLFNET::L; ++i)
  {
    ss >> a[i];
  }  
}

// --------------------------------------------------------------------------

void FLFNET::toMat32F(const std::vector<TDescriptor> &descriptors, 
  cv::Mat &mat)
{
  if(descriptors.empty())
  {
    mat.release();
    return;
  }
  
  const int N = descriptors.size();
  const int L = FLFNET::L;
  
  mat.create(N, L, CV_32F);
  
  for(int i = 0; i < N; ++i)
  {
    const TDescriptor& desc = descriptors[i];
    float *p = mat.ptr<float>(i);
    for(int j = 0; j < L; ++j, ++p)
    {
      *p = desc[j];
    }
  } 
}

// --------------------------------------------------------------------------
/*
void FLFNET::toMat8U(const std::vector<TDescriptor> &descriptors, 
  cv::Mat &mat)
{
  mat.create(descriptors.size(), 32, CV_8U);
  
  unsigned char *p = mat.ptr<unsigned char>();
  
  for(size_t i = 0; i < descriptors.size(); ++i, p += 32)
  {
    const unsigned char *d = descriptors[i].ptr<unsigned char>();
    std::copy(d, d+32, p);
  }
  
}
*/
// --------------------------------------------------------------------------

} // namespace DBoW2


