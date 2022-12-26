#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "stack.h"
#include "node.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

void replace(float**& newarr, float ValToBeChgd, float NewValue, int rows, int cols);

class qNode
{
public:
	int data;
	qNode* next;

	qNode()
	{
		next = NULL;
	}


};

class queue
{
public:
	queue* head;
	qNode* front;
	qNode* rear;
	queue();

	void enqueue(int x)
	{
		if (!isEmpty())
		{
			rear->next = new qNode();
			rear->next->data = x;
			rear = rear->next;
		}
		else 
		{
			front = new qNode();
			front->data = x;
			rear = front;
		}
	}
	void dequeue()
	{
		bool end = false;
		if (!isEmpty())
		{
			if (front == rear)
			{
				end = true;
			}
			qNode* temp = front;
			front = front->next;
			delete temp;
			if (end)
			{
				front = NULL;
				rear = NULL;
			}
		}

	}
	bool isEmpty() {
		if (front == NULL && rear == NULL)
		{
			return true;
		}
		return false;
	}

};





int GalaxyImageProcessing(string ImageFileDir)
{

	//cout << ImageFileDir << endl;
	//"C:\Users\muham\source\repos\DataAssignment2\DataAssignment2\Images\Img2.png"

	Mat img = imread("C:/Users/muham/source/repos/DataAssignment2/DataAssignment2/" + ImageFileDir, IMREAD_GRAYSCALE);
	img.convertTo(img, CV_32F);
	imshow("First OpenCV Application", img);

	waitKey(0);
	destroyAllWindows();
	

	float** newarr = new float* [img.rows];
	for (int i = 0; i < img.rows; i++)
	{
		newarr[i] = new float[img.cols];
	}

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			newarr[i][j] = -1.0;
		}

	}



	float** arr = new float* [img.rows];
	for (int i = 0; i < img.rows; i++)
	{
		arr[i] = new float[img.cols];
	}


	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{

			arr[i][j] = img.at<float>(i, j);

		}
	}

	int label = 1;
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols;j++)
		{
			if (arr[i][j] == 255.0)
			{
				//right
				if (j == 0 && i > 0)
				{
					if (arr[i - 1][j] == 0.0 && arr[i - 1][j + 1] == 0.0)
					{
						newarr[i][j] = label;
						label++;
					}
					else if (newarr[i - 1][j] != 0.0 && newarr[i - 1][j + 1] != 0.0)
					{
						if (newarr[i - 1][j] < newarr[i - 1][j + 1])
						{
							newarr[i][j] = newarr[i - 1][j];
							newarr[i - 1][j + 1] = newarr[i][j];
						}
						else
						{
							newarr[i][j] = newarr[i - 1][j + 1];
							newarr[i - 1][j] = newarr[i][j];
						}


					}


					else if (newarr[i - 1][j] != 0.0)
					{
						newarr[i][j] = newarr[i - 1][j];
					}
					else if (newarr[i - 1][j + 1] != 0.0)
					{
						newarr[i][j] = newarr[i - 1][j + 1];
					}

				}
				//left
				else if (j == img.cols && i > 0)    //MIGHT HAVE TO ADD A -1
				{
					if (newarr[i - 1][j] == 0.0 && newarr[i - 1][j - 1] == 0.0 && newarr[i][j - 1] == 0.0)
					{
						newarr[i][j] = label;
					}
					else if (newarr[i - 1][j] != 0.0 && newarr[i - 1][j - 1] != 0.0 && newarr[i][j - 1] != 0.0)////
					{
						if (newarr[i - 1][j] < newarr[i - 1][j - 1] && newarr[i - 1][j] < newarr[i][j - 1])
						{
							newarr[i][j] = newarr[i - 1][j];
							newarr[i - 1][j - 1] = newarr[i][j];
							newarr[i][j - 1] = newarr[i][j];
						}
						else if (newarr[i - 1][j - 1] < newarr[i - 1][j] && newarr[i - 1][j - 1] < newarr[i][j - 1])
						{
							newarr[i][j] = newarr[i - 1][j - 1];
							newarr[i - 1][j] = newarr[i][j];
							newarr[i][j - 1] = newarr[i][j];

						}
						else if (newarr[i][j - 1] < newarr[i - 1][j] && newarr[i][j - 1] < newarr[i - 1][j - 1])
						{
							newarr[i][j] = newarr[i][j - 1];
							newarr[i - 1][j] = newarr[i][j];
							newarr[i - 1][j - 1] = newarr[i][j];
						}
					}
					else if (newarr[i - 1][j] != 0.0)
					{
						newarr[i][j] = newarr[i - 1][j];
					}
					else if (newarr[i - 1][j - 1] != 0.0)
					{
						newarr[i][j] = newarr[i - 1][j - 1];
					}
					else if (newarr[i][j - 1] != 0.0)
					{
						newarr[i][j] = newarr[i][j - 1];
					}

				}
				//top
				else if (i == 0)
				{
					if (newarr[i][j - 1] == 0.0)
					{
						newarr[i][j] = label;
						label++;
					}
				}
				//center
				else
				{
					if (newarr[i][j - 1] == 0.0 && newarr[i - 1][j - 1] == 0.0 && newarr[i - 1][j] == 0.0 && newarr[i - 1][j + 1] == 0.0)
					{
						newarr[i][j] = label;
						label++;
					}
					else if (newarr[i][j - 1] != 0.0)
					{
						newarr[i][j] = newarr[i][j - 1];
					}
					else if (newarr[i - 1][j - 1] != 0.0)
					{
						newarr[i][j] = newarr[i - 1][j - 1];
					}
					else if (newarr[i - 1][j] != 0.0)
					{
						newarr[i][j] = newarr[i - 1][j];
					}
					else if (newarr[i - 1][j + 1] != 0.0)
					{
						newarr[i][j] = newarr[i - 1][j + 1];
					}



				}

			}
			else
			{
				newarr[i][j] = 0.0;
			}



		}
	}
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols;j++)
		{
			if (newarr[i][j] != 0.0)
			{

				if (newarr[i][j] != newarr[i][j - 1])
				{

					replace(newarr, newarr[i][j - 1], newarr[i][j], img.rows, img.cols);
				}
				if (newarr[i][j] != newarr[i - 1][j - 1])
				{
					replace(newarr, newarr[i - 1][j - 1], newarr[i][j], img.rows, img.cols);

				}
				if (newarr[i][j] != newarr[i - 1][j])
				{
					replace(newarr, newarr[i - 1][j], newarr[i][j], img.rows, img.cols);

				}
				if (newarr[i][j] != newarr[i - 1][j + 1])
				{
					replace(newarr, newarr[i - 1][j + 1], newarr[i][j], img.rows, img.cols);

				}



			}

		}
	}

	int* Labels = new int[img.rows * img.cols];
	int* CountLabels = new int[img.rows * img.cols];

	for (int i = 0; i < img.rows * img.cols;i++)
	{
		Labels[i] = 0;
		CountLabels[i] = 0;
	}

	int num = 0;
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols;j++)
		{
			if (newarr[i][j] != 0)
			{
				int x = 0;
				bool check = false;
				while (Labels[x] != 0)
				{
					if (Labels[x] == newarr[i][j])
					{
						check = true;
					}
					x++;
				}

				if (check == false)
				{
					Labels[num] = newarr[i][j];
					num++;
				}



			}
		}
	}

	int i = 0;
	while(Labels[i] != 0)
	{
		//Labels[i] = i+1;
		//cout << Labels[i] << endl;
		i++;
	}

	//cout << i << endl;
	//while(labels)
	
	

	float** temparr = new float* [img.rows];
	for (int i = 0; i < img.rows; i++)
	{
		temparr[i] = new float[img.cols];
		for (int j = 0; j < img.cols; j++)
		{
			temparr[i][j] = newarr[i][j];
		}
	}

	for (int x = 0; x < i;x++)
	{
		for (int i = 0; i < img.rows; i++)
		{
			for (int j = 0; j < img.cols; j++)
			{
				if (temparr[i][j] == Labels[x])
				{
					temparr[i][j] = x+1;
				}
			}
		}
	}



	Mat tmp = imread("C:/Users/muham/source/repos/DataAssignment2/DataAssignment2/" + ImageFileDir/*,IMREAD_GRAYSCALE*/);
	img.convertTo(tmp, CV_32F);

	int x = 0;
	for (int x = 0; x < i; x++)
	{

		for (int i = 0; i < img.rows; i++)
		{
			for (int j = 0; j < img.cols; j++)
			{
				//cout << temparr[i][j];
				if (temparr[i][j] == 0)
				{
					tmp.at<float>(i, j) = 0.0;
				}
				else if (temparr[i][j] == x+1)
				{
					tmp.at<float>(i, j) = 255.0;
				}
				else
				{
					tmp.at<float>(i, j) = 0.0;
				}

			}
		}


		imshow("Brand New Image", tmp);
		imwrite("C:/Users/muham/source/repos/DataAssignment2/DataAssignment2/Images/NewImageGalaxy" + to_string(x) + ".jpg", tmp);

		waitKey(0);
		destroyAllWindows();
	}
	

	


	return i;


	/*int* Labels = new int[img.rows * img.cols];
	int* CountLabels = new int[img.rows * img.cols];

	for (int i = 0; i < img.rows * img.cols;i++)
	{
		Labels[i] = 0;
		CountLabels[i] = 0;
	}

	int num = 0;
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols;j++)
		{
			if (newarr[i][j] != 0)
			{
				int x = 0;
				bool check = false;
				while (Labels[x] != 0)
				{
					if (Labels[x] == newarr[i][j])
					{
						check = true;
					}
					x++;
				}

				if (check == false)
				{
					Labels[num] = newarr[i][j];
					num++;
				}



			}
		}
	}

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols;j++)
		{
			if (newarr[i][j] != 0)
			{
				int x = 0;
				while (Labels[x] != 0)
				{
					if (Labels[x] == newarr[i][j])
					{
						CountLabels[x]++;
					}
					x++;
				}
			}
		}
	}



	int max = CountLabels[0];
	int maxIndex = 0;
	for (int i = 0; i < img.rows * img.cols; i++)
	{
		if (CountLabels[i] > max)
		{
			max = CountLabels[i];
			maxIndex = i;
		}
	}



	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols;j++)
		{
			if (newarr[i][j] != Labels[maxIndex])
			{
				newarr[i][j] = 0;
			}
			else
			{
				newarr[i][j] = 255;
			}
		}
	}


	for (int j = 0; j < img.cols; j++)
	{
		int first = FindFirst(newarr, j, img.rows);
		int last = FindLast(newarr, j, img.rows);
		for (int i = 0; i < img.rows;i++)
		{
			if (i > first && i < last)
			{
				newarr[i][j] = 255;

			}
		}
	}



	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols;j++)
		{
			img.at<float>(i, j) = newarr[i][j];

		}
	}*/



}


void replace(float**& newarr, float ValToBeChgd, float NewValue, int rows, int cols)
{
	if (ValToBeChgd != 0)
	{

		for (int i = 0; i < rows; i++)
		{
			int j = 0;
			for (; j < cols; j++)
			{
				if (newarr[i][j] == ValToBeChgd)
				{
					newarr[i][j] = NewValue;
				}
			}
			if (newarr[i][j] == -1)
			{
				break;
			}
		}

	}



}