/*
 * YangMatImage.h
 *
 *  Created on: 2020年10月29日
 *      Author: yang
 */

#ifndef YANGRECLIVING_INCLUDE_YANGMATIMAGECV_H_
#define YANGRECLIVING_INCLUDE_YANGMATIMAGECV_H_

//cv.h cxcore.h highgui.h

//#include  "opencv2/opencv.hpp"
#include "opencv/cv.h"
//using namespace cv;


#include "yangavutil/video/YangMatImage.h"
#include <yangavutil/video/YangYuvConvert.h>
#include "yangutil/sys/YangLoadLib.h"

#include <yangavutil/vr/YangJpegUtil.h>

using namespace std;
class YangMatImageCv:public YangMatImage {
public:
	YangMatImageCv();
	virtual ~YangMatImageCv();
	void initImg(char *bgfile,int width,int height,int typeLen=3);
	void matImage(unsigned char* psrc,unsigned char *pdst);
	YangJpegData m_jpgData;
	unsigned char* m_bkData;

private:
	//Mat  background_02;

	//IplImage *background_02;
	IplImage *m_frame;
	//Mat m_frameYuv;
	IplImage *  m_hsv;
	IplImage * m_mask;

	//Mat m_frameYv12;
	int m_imgLen;
	int m_width,m_height;
	//void matImageHandle();
	void replace_and_blend(unsigned char *pdst);


private:
	unsigned char* m_data;
	YangLoadLib m_lib,m_lib1;
	void loadLib();
	void unloadLib();

	void loadJpeg(char* filename,YangJpegData *jpg);
	YangJpegUtil jpg;
	YangYuvConvert yuv;
	IplImage*  (*yang_cvCreateImage)( CvSize size, int depth, int channels );
	IplImage*  (*yang_cvCreateImageHeader)( CvSize size, int depth, int channels );
	void  (*yang_cvCvtColor)( const CvArr* src, CvArr* dst, int code );
	void (*yang_cvInRangeS)( const CvArr* src, CvScalar lower,
	                       CvScalar upper, CvArr* dst );
	 IplConvKernel*  (*yang_cvCreateStructuringElementEx)(
	            int cols, int  rows, int  anchor_x, int  anchor_y,
	            int shape, int* values);
	 void  (*yang_cvMorphologyEx)( const CvArr* src, CvArr* dst,
	                              CvArr* temp, IplConvKernel* element,
	                              int operation, int iterations  );
	 void  (*yang_cvErode)( const CvArr* src, CvArr* dst,
	                       IplConvKernel* element ,
	                       int iterations);
	 void (*yang_cvSmooth)( const CvArr* src, CvArr* dst,
	                       int smoothtype ,
	                       int size1 ,
	                       int size2 ,
	                       double sigma1 ,
	                       double sigma2);
	 void  (*yang_cvReleaseImageHeader)( IplImage** image );
	 void  (*yang_cvReleaseImage)( IplImage** image );

	/**
	Mat (*yang_imread)( const String& filename, int flags );//codec
	//imgproc...........
	void (*yang_cvtColor)( InputArray src, OutputArray dst, int code, int dstCn);
	Mat (*yang_getStructuringElement)(int shape, Size ksize, Point anchor );//imgproc
	void (*yang_morphologyEx)( InputArray src, OutputArray dst,
	                                int op, InputArray kernel,
	                                Point anchor , int iterations,
	                                int borderType ,
	                                const Scalar& borderValue  );

	void (*yang_erode)( InputArray src, OutputArray dst, InputArray kernel,
	                         Point anchor , int iterations,
	                         int borderType,
	                         const Scalar& borderValue);
	void (*yang_GaussianBlur)( InputArray src, OutputArray dst, Size ksize,
	                                double sigmaX, double sigmaY,
	                                int borderType );
	//core....
	void (*yang_inRange)(InputArray src, InputArray lowerb,
	                          InputArray upperb, OutputArray dst);//core**/

};

#endif /* YANGRECLIVING_INCLUDE_YANGMATIMAGECV_H_ */
