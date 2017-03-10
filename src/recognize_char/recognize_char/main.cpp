#include <opencv2/opencv.hpp> 


int main(int argc, char* argv[])
{
    IplImage* imgSrc = cvLoadImage("C:\\pj\\bin\\w32d\\11.jpeg", CV_LOAD_IMAGE_COLOR);

    IplImage* img_gray = cvCreateImage(cvGetSize(imgSrc), IPL_DEPTH_8U, 1);
    cvCvtColor(imgSrc, img_gray, CV_BGR2GRAY);
    cvThreshold(img_gray, img_gray, 100, 255, CV_THRESH_BINARY_INV);// CV_THRESH_BINARY_INVʹ�ñ���Ϊ��ɫ���ַ�Ϊ��ɫ�������ҵ������������ַ��������  
    cvShowImage("ThresholdImg", img_gray);
    CvSeq* contours = NULL;
    CvMemStorage* storage = cvCreateMemStorage(0);
    // ����ԴͼƬ��覴ÿ����ø�ʴ�����������  
    int count = cvFindContours(img_gray, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL);
    printf("����������%d", count);
    int idx = 0;
    char szName[56] = { 0 };
    int tempCount = 0;
    for (CvSeq* c = contours; c != NULL; c = c->h_next) {
        CvRect rc = cvBoundingRect(c, 0);
        //      if ()      
        //       {    
        //           continue;     ������Ը��������Ĵ�С����ɸѡ  
        //       }  
        cvDrawRect(imgSrc, cvPoint(rc.x, rc.y), cvPoint(rc.x + rc.width, rc.y + rc.height), CV_RGB(255, 0, 0));
        IplImage* imgNo = cvCreateImage(cvSize(rc.width, rc.height), IPL_DEPTH_8U, 3);
        cvSetImageROI(imgSrc, rc);
        cvCopy(imgSrc, imgNo);
        cvResetImageROI(imgSrc);
        sprintf(szName, "wnd_%d", idx++);
        cvNamedWindow(szName);
        cvShowImage(szName, imgNo); //������и������ͼ����������򣬻���ϵ��£����ԱȽ�rc.x,rc.y;  
        cvReleaseImage(&imgNo);
    }
    cvNamedWindow("src");
    cvShowImage("src", imgSrc);
    cvWaitKey(0);
    cvReleaseMemStorage(&storage);
    cvReleaseImage(&imgSrc);
    cvReleaseImage(&img_gray);
    cvDestroyAllWindows();
    return 0;
}
