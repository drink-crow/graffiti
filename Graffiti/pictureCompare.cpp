#include "pictureCompare.h"

double getSSIM_CPU(vector<vector<int>> s1, vector<vector<int>> s2, int h, int w, int bit, double pixelRadius)
{
	//s1Ҫ��s2��ͬ��С
	if (s1.size() != s2.size())
		return 0.0;
	else
	{
		int w = s1[0].size();
		for (int i = 0; i < s1.size(); i++)
		{
			if (s1[i].size() != s2[i].size() || s1[i].size() != w)
			{
				return 0.0;
			}
		}
	}
	
	vector<vector<double>> weightMatrix;
	getGaussianWeightMatrix(pixelRadius, &weightMatrix);

	//������ڴ�С�ɸ����ĸ�˹ģ�������ذ뾶��ָ��
	int convolutionWindowSize = weightMatrix.size();

	//���ִ���
	int height = s1.size();
	int width = s1[0].size();
	//���ִ��ڵ�����
	int M = ceil((double)height/convolutionWindowSize);
	int N = ceil((double)width / convolutionWindowSize);
	vector<vector<double>> smallWindow1, smallWindow2;
	smallWindow1.resize(convolutionWindowSize);
	for (int i = 0; i < convolutionWindowSize; i++)
	{
		smallWindow1[i].resize(convolutionWindowSize);
	}
	smallWindow2.resize(convolutionWindowSize);
	for (int i = 0; i < convolutionWindowSize; i++)
	{
		smallWindow2[i].resize(convolutionWindowSize);
	}
	//��չs1,s2
	for (int y = 0; y < height; y++)
	{
		for (int x = width; x < N*convolutionWindowSize; x++)
		{
			s1[y].push_back(s1[y][width - 1]);
			s2[y].push_back(s2[y][width - 1]);
		}
	}
	for (int y = height; y < M*convolutionWindowSize; y++)
	{
		s1.push_back(s1[height - 1]);
		s2.push_back(s1[height - 1]);
	}

	//�ִ�����õĸ���SSIM
	vector<double> ssim;
	double MSSIM = 0;
	const int windowPixelCount = convolutionWindowSize * convolutionWindowSize;
	const int L = pow(2, bit) - 1;
	const double C1 = pow(0.01 * L, 2);
	const double C2 = pow(0.03 * L, 2);
	double E1, E2, S1, S2, S12;

	for (int m = 0; m < M; m++)
	{
		for (int n = 0; n < N; n++)
		{
			E1 = 0; E2 = 0; S1 = 0; S2 = 0; S12 = 0;
			//���С��
			for (int y = 0; y < convolutionWindowSize; y++)
			{
				for (int x = 0; x < convolutionWindowSize; x++)
				{
					smallWindow1[y][x] = s1[m*convolutionWindowSize + y][n*convolutionWindowSize + x];
					smallWindow2[y][x] = s2[m*convolutionWindowSize + y][n*convolutionWindowSize + x];

					E1 += weightMatrix[y][x] * s1[m*convolutionWindowSize + y][n*convolutionWindowSize + x];
					E2 += weightMatrix[y][x] * s2[m*convolutionWindowSize + y][n*convolutionWindowSize + x];
				}
			}
			
			for (int y = 0; y < convolutionWindowSize; y++)
			{
				for (int x = 0; x < convolutionWindowSize; x++)
				{
					S1 += weightMatrix[y][x] * pow(s1[m*convolutionWindowSize + y][n*convolutionWindowSize + x] - E1, 2);
					S2 += weightMatrix[y][x] * pow(s2[m*convolutionWindowSize + y][n*convolutionWindowSize + x] - E2, 2);
					S12 += weightMatrix[y][x] * (s1[m*convolutionWindowSize + y][n*convolutionWindowSize + x] - E1) * (s2[m*convolutionWindowSize + y][n*convolutionWindowSize + x] - E2);
				}
			}
			S1 = sqrt(S1);
			S2 = sqrt(S2);

			MSSIM += ((2 * E1*E2 + C1)*(2 * S12 + C2)) / ((E1*E1 + E2 * E2 + C1)*(S1*S1 + S2 * S2 + C2));
		}
	}

	return MSSIM / (M*N);
}

//pixelRadiusΪ��˹ģ�������ذ뾶��outputMatrix�������õ�
void getGaussianWeightMatrix(double pixelRadius, vector<vector<double>> *outputMatrix)
{
	//���ذ뾶����С�ڵ�0
	if (pixelRadius <= 0)
	{
		return;
	}
	
	//sigma�Ǹ�˹ģ�������еı�׼���������̬���ߵķֲ���3����׼��ĵط�������97%���ϵ����ֵ�����Ա�׼��ȡr/3
	double sigma = pixelRadius / 3;

	//���ݵľ���뾶����Ϊ����
	int r = ceil(pixelRadius);

	//for (int i = 0; i < outputMatrix->size(); i++)
	//{
	//	outputMatrix[i].clear();
	//}
	//outputMatrix->clear();



	vector<vector<double>> temp;
	temp.resize(r);
	for (int i = 0; i < r; i++)
	{
		temp[i].resize(r);
	}

	//Բ����
	constexpr double pi = 3.1415926535;
	//��˹�����������
	const double a = 1 / (2 * pi * sigma *sigma);
	const double b = 2 * sigma * sigma;
	//���ݶ�ά��˹�����ĶԳ��ԣ�ֻҪ����1/8�ĵط��Ϳ�����
	for (int y = 0; y < r; y++)
	{
		for (int x = 0 + y; x < r; x++)
		{
			temp[y][x] = a * exp(-(x * x + y * y) / b);
		}
	}

	//������,б�ԽǶԳ����
	for (int y = 0; y < r; y++)
	{
		for (int x = 0; x < y; x++)
		{
			temp[y][x] = temp[x][y];
		}
	}
	//���
	const int size = 2 * r - 1;
	outputMatrix->resize(size);
	for (int i = 0; i < outputMatrix->size(); i++)
	{
		(*outputMatrix)[i].resize(size);
	}
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			(*outputMatrix)[y][x] = temp[abs(y - r + 1)][abs(x - r + 1)];
		}
	}

	//Ȩ�ؾ����һ��
	double normalize = 0.0;
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			normalize += (*outputMatrix)[y][x];
		}
	}
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			(*outputMatrix)[y][x] = (*outputMatrix)[y][x] / normalize;
		}
	}

	//���ڴ�ӡ��˹�������

	//wchar_t str[100];
	//wstring ss;
	//for (int y = size -1; y >= 0; y--)
	//{
	//	ss.clear();
	//	for (int x = 0; x < size; x++)
	//	{
	//		swprintf_s(str, L"%.6f  ", (*outputMatrix)[y][x]);
	//		ss.append(str);
	//	}
	//	ss.append(L"\n");
	//	OutputDebugString(ss.c_str());
	//}
}

//Ĭ��ÿͨ��8λ,������0xAARRGGBB,С��ģʽ
double getPSNR_Color_CPU(const unsigned char * s1, const unsigned char * s2, int h, int w)
{
	constexpr long long MAX = 2113;

	long long MSE = 0;

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			MSE += pow(getLABColorDistance(s1 + 4 * (y * w + x), s2 + 4 * (y * w + x)), 2);
		}
	}
	MSE = MSE / (h*w);

	return 20 * log10(MAX / sqrt(MSE));
}


//Ĭ����С��ģʽ��0xAARRGGBB�����������һ������BB
//double getLABColorDistance(const unsigned char * c1,const unsigned char * c2)
//{
//	long rmean = ((c1[2] + c2[2]) / 2);
//	long r = (c1[2] - c2[2]);
//	long g = (c1[1] - c2[1]);
//	long b = (c1[0] - c2[0]);
//
//	return sqrt((((512 + rmean)*r*r) >> 8) + 4 * g*g + (((767 - rmean)*b*b) >> 8));
//	//return sqrt((((512 + ((c1[2] + c2[2]) / 2))*(c1[2] - c2[2])*(c1[2] - c2[2])) >> 8) + 4 * (c1[1] - c2[1])*(c1[1] - c2[1]) + (((767 - ((c1[2] + c2[2]) / 2))*(c1[0] - c2[0])*(c1[0] - c2[0])) >> 8));
//
//}
