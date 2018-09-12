#include"getAllFiles.h"

int main(int argc, char* argv[])
{
    std::string imgPath = argv[1];
    std::vector<std::string> files=getFiles(imgPath);
    std::vector<std::string>::iterator iter;
    for(iter = files.begin(); iter != files.end(); iter++)
    {
        std::string fullName=imgPath + *iter;
        cv::Mat src=cv::imread(fullName, cv::IMREAD_GRAYSCALE);
        if(src.data == NULL)
		{
            printf("can't read image");
            return -1;
        }
        cv::resize(src, src, cv::Size(), 1, 1, cv::INTER_CUBIC);
        cv::imshow("test", src);
        cv::waitKey(1000);
    }
    return 0;
}
