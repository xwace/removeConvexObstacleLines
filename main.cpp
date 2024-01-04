std::fstream infile("/home/oswin/Desktop/map4.txt");
    string str;
    Mat src;

    while (getline(infile, str)) {
        src.push_back(Mat(1, (int) str.size(), 0, &str[0]));
    }

    vector<vector<Point>> contours;
    using VVP = vector<vector<Point>>;
    using VP = vector<Point>;
    Mat input = src == 48;
    erode(input, input, Matx<uchar, 3, 3>::ones());
    namedWindow("input", 2);
    imshow("input", input);
    waitKey();

    VVP contours;
    findContours(input,contours,RETR_CCOMP,CHAIN_APPROX_NONE);
    sort(contours.begin(),contours.end(),[](VP a,VP b){return contourArea(a)> contourArea(b);});
    drawContours(input,contours,0,90,2);
    auto src = input.clone();
    std::vector<int> ms;

    namedWindow("ORI", 2);
    imshow("ORI", input);
    waitKey();

    for (int i = 1; i < src.rows - 1; ++i)
    {
        for (int j = 0; j < src.cols; ++j)
        {
            if ((src.at<uchar>(i, j) > 100 || src.at<uchar>(i, j) < 80) && (src.at<uchar>(i + 1, j) >= 80 && src.at<uchar>(i + 1, j) <= 100))
            {
                ms.push_back(j);
                cv::Mat color=input.clone();
                cvtColor(color,color,COLOR_GRAY2BGR);
                color.at<Vec3b>(i,j)=Vec3b{0,0,255};
                namedWindow("color", 2);
                imshow("color",color);
                waitKey();
            }
        }

        for(auto m:ms)
            cout<<"ms: "<<m<<endl;

        if (ms.size() != 0)
        {
            for (int k = 0; k < ms.size() - 1; k++)
            {
                int cc = 0;
                int dd = 0;
                for (int t = ms[k] + 1; t < ms[k + 1]; t++)
                {
                    if ((src.at<uchar>(i, t) >= 80 && src.at<uchar>(i, t) <= 100) && (src.at<uchar>(i + 1, t) >= 80 && src.at<uchar>(i + 1, t) <= 100))
                        cc++;
                    if (src.at<uchar>(i - 1, t) >= 80 && src.at<uchar>(i - 1, t) <= 100)
                    {
                        dd++;
                    }
                }
                if (cc == ms[k + 1] - ms[k] - 1 && dd == 0)
                {
                    for (int t = ms[k] + 1; t < ms[k + 1]; t++)
                    {
                        src.at<uchar>(i, t) = src.at<uchar>(i - 1, t);
                        namedWindow("blank1", 2);
                        imshow("blank1",src);
                        waitKey();
                    }
                }
            }
            ms.clear();
        }
    }
    std::vector<int> ms2;
    for (int j = 1; j < src.cols - 1; ++j)
    {
        for (int i = 0; i < src.rows; ++i)
        {
            if ((src.at<uchar>(i, j) < 80 || src.at<uchar>(i, j) > 100) && (src.at<uchar>(i, j + 1) >= 80 && src.at<uchar>(i, j + 1) <= 100))
            {
                ms2.push_back(i);
            }
        }
        if (ms2.size() != 0)
        {
            for (int k = 0; k < ms2.size() - 1; k++)
            {
                int cc = 0;
                int dd = 0;
                for (int t = ms2[k] + 1; t < ms2[k + 1]; t++)
                {
                    if ((src.at<uchar>(t, j) >= 80 && src.at<uchar>(t, j) <= 100) && (src.at<uchar>(t, j + 1) >= 80 && src.at<uchar>(t, j + 1) <= 100))
                        cc++;
                    if (src.at<uchar>(t, j - 1) >= 80 && src.at<uchar>(t, j - 1) <= 100)
                    {
                        dd++;
                    }
                }
                if (cc == ms2[k + 1] - ms2[k] - 1 && dd == 0)
                {
                    for (int t = ms2[k] + 1; t < ms2[k + 1]; t++)
                    {
                        src.at<uchar>(t, j) = src.at<uchar>(t, j - 1);
                    }
                }
            }
            ms2.clear();
        }
    }

    std::vector<int> ms3;
    for (int i = src.rows - 2; i > 0; --i)
    {
        for (int j = 0; j < src.cols; ++j)
        {
            if ((src.at<uchar>(i, j) < 80 || src.at<uchar>(i, j) > 100) && (src.at<uchar>(i - 1, j) >= 80 && src.at<uchar>(i - 1, j) <= 100))
            {
                ms3.push_back(j);
            }
        }
        if (ms3.size() != 0)
        {
            for (int k = 0; k < ms3.size() - 1; k++)
            {
                int cc = 0;
                int dd = 0;
                for (int t = ms3[k] + 1; t < ms3[k + 1]; t++)
                {
                    if ((src.at<uchar>(i, t) >= 80 && src.at<uchar>(i, t) <= 100) && (src.at<uchar>(i - 1, t) >= 80 && src.at<uchar>(i - 1, t) <= 100))
                        cc++;
                    if (src.at<uchar>(i + 1, t) >= 80 && src.at<uchar>(i + 1, t) <= 100)
                    {
                        dd++;
                    }
                }
                if (cc == ms3[k + 1] - ms3[k] - 1 && dd == 0)
                {
                    for (int t = ms3[k] + 1; t < ms3[k + 1]; t++)
                    {
                        src.at<uchar>(i, t) = src.at<uchar>(i + 1, t);
                    }
                }
            }
            ms3.clear();
        }
    }

    std::vector<int> ms4;
    for (int j = src.cols - 2; j > 0; --j)
    {
        for (int i = 0; i < src.rows; ++i)
        {
            if ((src.at<uchar>(i, j) < 80 || src.at<uchar>(i, j) > 100) && (src.at<uchar>(i, j - 1) >= 80 && src.at<uchar>(i, j - 1) <= 100))
            {
                ms4.push_back(i);
            }
        }
        if (ms4.size() != 0)
        {
            for (int k = 0; k < ms4.size() - 1; k++)
            {
                int cc = 0;
                int dd = 0;
                for (int t = ms4[k] + 1; t < ms4[k + 1]; t++)
                {
                    if ((src.at<uchar>(t, j) >= 80 && src.at<uchar>(t, j) <= 100) && (src.at<uchar>(t, j - 1) >= 80 && src.at<uchar>(t, j - 1) <= 100))
                        cc++;
                    if (src.at<uchar>(t, j + 1) >= 80 && src.at<uchar>(t, j + 1) <= 100)
                    {
                        dd++;
                    }
                }
                if (cc == ms4[k + 1] - ms4[k] - 1 && dd == 0)
                {
                    for (int t = ms4[k] + 1; t < ms4[k + 1]; t++)
                    {
                        src.at<uchar>(t, j) = src.at<uchar>(t, j + 1);
                    }
                }
            }
            ms4.clear();
        }
    }

    namedWindow("blank", 2);
    imshow("blank",src);
    waitKey();
