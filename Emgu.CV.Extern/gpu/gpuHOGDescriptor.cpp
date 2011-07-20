//----------------------------------------------------------------------------
//
//  Copyright (C) 2004-2011 by EMGU. All rights reserved.
//
//----------------------------------------------------------------------------

#include "gpu_c.h"

void gpuHOGDescriptorPeopleDetectorCreate(CvSeq* seq) 
{   
   std::vector<float> v = cv::gpu::HOGDescriptor::getDefaultPeopleDetector();  
   cvSeqPushMulti(seq, &v.front(), v.size()); 
}

cv::gpu::HOGDescriptor* gpuHOGDescriptorCreateDefault() { return new cv::gpu::HOGDescriptor; }

cv::gpu::HOGDescriptor* gpuHOGDescriptorCreate(
   cv::Size* _winSize, 
   cv::Size* _blockSize, 
   cv::Size* _blockStride,
   cv::Size* _cellSize, 
   int _nbins, 
   double _winSigma,
   double _L2HysThreshold, 
   bool _gammaCorrection, 
   int _nlevels)
{
   return new cv::gpu::HOGDescriptor(*_winSize, *_blockSize, *_blockStride, *_cellSize, _nbins, _winSigma, _L2HysThreshold, _gammaCorrection, _nlevels);
}

void gpuHOGSetSVMDetector(cv::gpu::HOGDescriptor* descriptor, std::vector<float>* vector) 
{ 
   descriptor->setSVMDetector(*vector); 
}

void gpuHOGDescriptorRelease(cv::gpu::HOGDescriptor* descriptor) { delete descriptor; }

void gpuHOGDescriptorDetectMultiScale(
   cv::gpu::HOGDescriptor* descriptor, 
   cv::gpu::GpuMat* img, 
   CvSeq* foundLocations,
   double hitThreshold, 
   CvSize winStride,
   CvSize padding, 
   double scale,
   int groupThreshold)
{
   cvClearSeq(foundLocations);

   std::vector<cv::Rect> rects;

   descriptor->detectMultiScale(*img, rects, hitThreshold, winStride, padding, scale, groupThreshold);
   if (rects.size() > 0)
      cvSeqPushMulti(foundLocations, &rects[0], rects.size());
}