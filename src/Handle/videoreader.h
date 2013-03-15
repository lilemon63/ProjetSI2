#ifndef VIDEOREADER_H
#define VIDEOREADER_H

#include <opencv2/opencv.hpp>

/** @brief Read a video stream and give an image for each frame. */
class VideoReader
{
public:
    VideoReader();
    virtual ~VideoReader() = default;
    VideoReader( const VideoReader & ) = delete;
    VideoReader & operator=( const VideoReader & ) = delete;


    /** @brief Return true if the stream can be seeked ie reading cursor can be moved.
    **  @brief bool : true if the reading cursor can be moved else false.
    */
    virtual bool acceptSeek(void);


    /** @brief Get the last image grabbed.
    **  @return IplImage * : last image grabbed.
    */
    virtual IplImage * getImage(void);

    /** @brief Grab the current image from the video stream.
    **
    **  There is no copy so it's faster so we can get several image from several video stream at the same time
        with more accuracy.
    */
    virtual void grab(void);


    /** @brief Get the maximum frame we can get from this stream, 0 for infinity.
    **  @return int : maximum frame we can get from this stream, 0 for infinity.
    */
    virtual int nbFrame(void);


    /** @brief Grab the previous image from the video stream.
    **
    **  There is no copy so it's faster so we can get several image from several video stream at the same time
        with more accuracy.
    **
    **  If the stream doesn't accepted seek, do nothing.
    */
    virtual void r_grab(void);


    /** @brief Grab the ième image from the video stream.
    **
    **  There is no copy so it's faster so we can get several image from several video stream at the same time
        with more accuracy.
    **
    **  If the stream doesn't accepted seek, do nothing.
    **  @param int : image number to gran
    */
    virtual void slid(int);


    /** @brief Specified the camera to use as source (if there is several cameras).
    **
    **  VideoReader's child, this method can be unused, but you can use it to create some "virtual cameras".
    **  @param int idCamera = 0 : camera to use as source.
    */
    virtual void useCamera(int idCamera = 0);
private :
    /** @brief video stream */
    CvCapture * m_video;
};

#endif // VIDEOREADER_H
