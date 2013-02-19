#include "rotation.h"
#include "../../exception.h"
#include "../imagedata.h"
#include "../Parameters/dial.h"

Rotation::Rotation(int angle, const std::string & name)
    : VirtualHandle(name)
{
    m_listParameters.resize(Max);
    m_listParameters[AngleRotation] = std::shared_ptr<HandleParameters>(new HandleParameters() );
    m_listParameters[AngleRotation]->changeSources( new Dial("Rotation", angle) );
}


ImageDataPtr Rotation::startHandle(const ImageDataPtr src1, const ImageDataPtr)
{
    if( ! src1 )
        throw Exception::buildException("La source est vide", "Rotation", "startHandle", EPC);

   int angleDegrees = m_listParameters[AngleRotation]->toInt() % 360;

   ImageDataPtr newImage( new ImageData(*src1->getImage() ) );
   IplImage * imageRotated = newImage->getImage();

   if( angleDegrees )
   {
       CvMat* rot_mat = cvCreateMat(2,3,CV_32FC1);
       CvPoint2D32f center = cvPoint2D32f( cvGetSize(imageRotated).width/2, cvGetSize(imageRotated).height/2 );
       cv2DRotationMatrix( center, angleDegrees, 1, rot_mat );
       cvWarpAffine( src1->getImage() , imageRotated, rot_mat );
       cvReleaseMat(&rot_mat);
   }

   updateImageForView(newImage);
   return newImage;
}
