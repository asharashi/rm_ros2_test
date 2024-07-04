#include "toGetImage.hpp"

bool toGetImage(cv::Mat* outer_img)
{
    if(outer_img == nullptr)
    {
        return false;
    }

    std::string img_path = "";
    
    if(img_path.empty())
    {
        return false;
    }
    
    cv::Mat temp_img;
    temp_img = cv::imread(img_path);

    if(temp_img.empty())
    {
        return false;
    }

    *outer_img = temp_img;

}