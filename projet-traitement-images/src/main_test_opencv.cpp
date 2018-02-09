//#include<stdio.h>
//
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/highgui.hpp"
//#include <math.h>
//
//#include <iostream>
//#include <fstream>
//
//using namespace cv;
//using namespace std;
//
//#define EVAL_MODE true
//
//#define NB_WRITER_W 35
//#define NB_PAGE_W 22
//
//#define NB_WRITER_S 6
//#define NB_PAGE_S 2
//
//#define NB_ROWS 7
//#define NB_COLS 5
//
//struct TPage {
//	string pageNumber;
//	string scripterNumber;
//	string formNumber;
//	string path;
//};
//
//struct TImagette {
//	TPage page;
//	Mat subimage;
//	string label;
//	string size;
//	string row;
//	string column;
//	string name;
//};
//
//const string outputPath = "..\\output";
//
//void save(string name, Mat img) {
//	imwrite(outputPath + "\\" + name + ".png", img);
//}
//
//Mat load(string path) {
//	return imread(path, IMREAD_COLOR);
//}
//
//vector<TPage> fetchPages_W(string basePath) {
//	vector<TPage> result;
//
//	for (int writer_n = 0; writer_n < NB_WRITER_W; ++writer_n) {
//		for (int page_n = 0; page_n < NB_PAGE_W; ++page_n) {
//
//			string scripter_str = std::to_string(writer_n);
//
//			while (scripter_str.length() < 3) {
//				scripter_str = "0" + scripter_str;
//			}
//
//			string page_str = std::to_string(page_n);
//
//			while (page_str.length() < 2) {
//				page_str = "0" + page_str;
//			}
//
//			string form_str = scripter_str + page_str;
//
//			string filename = basePath + "w" + scripter_str + "-scans\\" + form_str + ".png";
//
//			TPage page;
//
//			page.pageNumber = page_str;
//			page.scripterNumber = scripter_str;
//			page.formNumber = form_str;
//			page.path = filename;
//
//			result.push_back(page);
//		}
//	}
//
//	return result;
//}
//
//vector<TPage> fetchPages_S(string basePath) {
//	vector<TPage> result;
//
//	for (int writer_n = 1; writer_n <= NB_WRITER_S; ++writer_n) {
//		for (int page_n = 1; page_n <= NB_PAGE_S; ++page_n) {
//
//			string scripter_str = std::to_string(writer_n);
//
//			while (scripter_str.length() < 2) {
//				scripter_str = "0" + scripter_str;
//			}
//
//			string page_str = std::to_string(page_n);
//
//			while (page_str.length() < 4) {
//				page_str = "0" + page_str;
//			}
//
//			string form_str = scripter_str + page_str;
//
//			string filename = basePath + "s" + scripter_str + "_" + page_str + ".png";
//
//			TPage page;
//
//			page.pageNumber = page_str;
//			page.scripterNumber = scripter_str;
//			page.formNumber = form_str;
//			page.path = filename;
//
//			result.push_back(page);
//		}
//	}
//
//	return result;
//}
//
//
//const int rect_size = 242;
//const int stepX = 349;
//const int stepY = 349;
//
//Rect getImagetteBounds(int row, int col, int startX, int startY, float ratioX, float ratioY) {
//	return Rect(startX + stepX * col * ratioX, startY + stepY * row * ratioY, rect_size * ratioX, rect_size * ratioY);
//}
//
//TImagette createImagette(Mat &pageImage, TPage page, int row, int col, string label, string size, int startX, int startY, float ratioX, float ratioY) {
//	TImagette imgt;
//
//	imgt.page = page;
//	imgt.row = std::to_string(row);
//	imgt.column = std::to_string(col);
//	imgt.label = label;
//	imgt.size = size;
//	imgt.subimage = Mat(pageImage, getImagetteBounds(row, col, startX, startY, ratioX, ratioY));
//	imgt.name = label + "_" + imgt.page.scripterNumber + "_" + imgt.page.pageNumber + "_" + imgt.row + "_" + imgt.column;
//
//	return imgt;
//}
//
//void saveImagette(TImagette imgt) {
//	
//	save(imgt.name, imgt.subimage);
//
//	string filepath = outputPath + "\\ " + imgt.name + ".txt";
//
//	ofstream out(filepath);
//	if (!out)
//	{
//		cout << "Couldn't create/open file at path : " << filepath << endl;
//		return;
//	}
//
//	out << "label " << imgt.label << endl;
//	out << "form " << imgt.page.formNumber << endl;
//	out << "scripter " << imgt.page.scripterNumber << endl;
//	out << "page " << imgt.page.pageNumber << endl;
//	out << "row " << imgt.row << endl;
//	out << "column " << imgt.column << endl;
//	out << "size " << imgt.size << endl;
//
//	out.close();
//}
//
//Mat reticleTemplate = load("../templates/reticle.png");
//
//vector<Point> findReticles(Mat img)
//{
//	vector<Point> reticles;
//
//	Mat ref = img;
//	Mat gref, gtpl;
//	cvtColor(ref, gref, CV_BGR2GRAY);
//	Mat tpl = reticleTemplate;
//	cvtColor(tpl, gtpl, CV_BGR2GRAY);
//	Mat res(ref.rows - tpl.rows + 1, ref.cols - tpl.cols + 1, CV_32FC1);
//	matchTemplate(gref, gtpl, res, CV_TM_CCOEFF_NORMED);
//	threshold(res, res, 0.8, 0.8, CV_THRESH_TOZERO);
//	while (true)
//	{
//		double minval, maxval, threshold = 0.8;
//		Point minloc, maxloc;
//		minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);
//		if (maxval >= threshold)
//		{
//			reticles.push_back(Point(maxloc.x + tpl.cols / 2, maxloc.y + tpl.rows / 2));
//			floodFill(res, maxloc, Scalar(0), 0, Scalar(.1), Scalar(1.));
//		}
//		else {
//			break;
//		}
//	}
//
//	return reticles;
//}
//
//
//vector<string> Icon_Names({
//	"bomb", "fire", "warning", "car", "cross", "forbidden", "laidman", "crossegg", "f", "horizontalwaves", "p", "thunder", "stickman", "verticalwaves"
//});
//
//vector<Mat> Icon_Templates;
//
//
//vector<string> Text_Names({
//	"small", "medium", "large"
//});
//
//vector<Mat> Text_Templates;
//
//vector<string> findNamedTemplates(Mat img, vector<Mat> templates, vector<string> names, vector<Rect> regionsOfInterest) {
//	bool stop = false;
//
//	Mat ref = img;
//
//	vector<string> found;
//
//	for (int j = 0; j < regionsOfInterest.size(); j++)
//	{
//		Mat roiimg = ref(regionsOfInterest[j]);
//		Mat gref, gtpl;
//		cvtColor(roiimg, gref, CV_BGR2GRAY);
//		bool foundTemplate = false;
//
//		for (int i = 0; i < templates.size(); i++)
//		{
//			Mat tpl = templates[i];
//			cvtColor(tpl, gtpl, CV_BGR2GRAY);
//			Mat res(roiimg.rows - tpl.rows + 1, roiimg.cols - tpl.cols + 1, CV_32FC1);
//			matchTemplate(gref, gtpl, res, CV_TM_CCOEFF_NORMED);
//			threshold(res, res, 0.3, 0.3, CV_THRESH_TOZERO);
//
//			double minval, maxval, threshold = 0.45;
//
//			// Ease distinction between f and p
//			if (names[i] == "f")
//				threshold = 0.6;
//
//			Point minloc, maxloc;
//			minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);
//
//			if (maxval >= threshold)
//			{
//				floodFill(res, maxloc, Scalar(0), 0, Scalar(.1), Scalar(1.));
//				found.push_back(names[i]);
//				foundTemplate = true;
//				break;
//			}
//		}
//
//		if (!foundTemplate) {
//			found.push_back("");
//		}
//	}
//
//	return found;
//}
//
//int main(int argc, char** argv)
//{
//	for (auto iconName : Icon_Names) {
//		Icon_Templates.push_back(imread("../templates/" + iconName + ".png", IMREAD_COLOR));
//	}
//
//	for (auto textName : Text_Names) {
//		Text_Templates.push_back(imread("../templates/" + textName + ".png", IMREAD_COLOR));
//	}
//
//	vector<TPage> pages;
//
//	if(EVAL_MODE)
//		pages = fetchPages_S("..\\..\\EvalScans\\");
//	else
//		pages = fetchPages_W("..\\..\\Scans\\");
//
//	for (auto &page : pages)
//	{
//		cout << "Processing form #" << page.formNumber << endl;
//
//		Mat loaded = load(page.path);
//		
//		vector<Point> reticles = findReticles(loaded);
//
//		if (reticles.size() < 2) {
//			cout << "Found " << reticles.size() << " reticles but at least 2 were expected (in form " << page.formNumber << ")" << endl;
//			continue;
//		}
//
//		Point topReticle = reticles[0], bottomReticle = reticles[0];
//
//		for (auto reticle : reticles) {
//			if (reticle.x > topReticle.x)
//				topReticle = reticle;
//			else if (reticle.x < bottomReticle.x)
//				bottomReticle = reticle;
//		}
//
//		float lenX = topReticle.x - bottomReticle.x;
//		float lenY = bottomReticle.y - topReticle.y;
//
//		float ratioX = lenX / 1951.0f;
//		float ratioY = lenY / 2762.0f;
//
//		float distanceBelow = 251 * ratioY;
//		float distanceRight = 357 * ratioX;
//
//		int startX = bottomReticle.x + distanceRight;
//		int startY = topReticle.y + distanceBelow;
//
//		vector<Rect> regionsOfInterest({
//			Rect(bottomReticle.x - 80 * ratioX, topReticle.y + 260 * ratioY, 370 * ratioX, 300 * ratioY),
//			Rect(bottomReticle.x - 80 * ratioX, topReticle.y + 610 * ratioY, 370 * ratioX, 300 * ratioY),
//			Rect(bottomReticle.x - 80 * ratioX, topReticle.y + 960 * ratioY, 370 * ratioX, 300 * ratioY),
//			Rect(bottomReticle.x - 80 * ratioX, topReticle.y + 1310 * ratioY, 370 * ratioX, 300 * ratioY),
//			Rect(bottomReticle.x - 80 * ratioX, topReticle.y + 1660 * ratioY, 370 * ratioX, 300 * ratioY),
//			Rect(bottomReticle.x - 80 * ratioX, topReticle.y + 2010 * ratioY, 370 * ratioX, 300 * ratioY),
//			Rect(bottomReticle.x - 80 * ratioX, topReticle.y + 2360 * ratioY, 370 * ratioX, 300 * ratioY)
//		});
//
//		vector<string> iconNames = findNamedTemplates(loaded, Icon_Templates, Icon_Names, regionsOfInterest);
//		vector<string> textNames = findNamedTemplates(loaded, Text_Templates, Text_Names, regionsOfInterest);
//
//		for (int col = 0; col < NB_COLS; ++col) {
//			for (int row = 0; row < NB_ROWS; ++row) {
//				TImagette imgt = createImagette(loaded, page, row, col, iconNames[row], textNames[row], startX, startY, ratioX, ratioY);
//				saveImagette(imgt);
//			}
//		}
//	}
//
//	system("PAUSE");
//	return 0;
//}