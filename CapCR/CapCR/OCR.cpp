#include "stdafx.h"
#include "OCR.h"
#include "CapCRView.h"
#include "MainFrm.h"
#include "ProgressDlg.h"
#include <fstream>
#include "TextboxDlg.h"
#include "resource.h"
using namespace std;


COCR::COCR()
	: textbox(NULL)
	, m_bTextboxEmpty(true)
{
	GetStandardImageDataFromBinaryFile("standard.bin");

	letterSpace.letter.value = ' ';
	//letterSpace.isFixed = true;
}


COCR::~COCR()
{
}


/*void COCR::CreateStandard(CImage* newImage)		// 기본 이미지 데이터를 만들기 위해 실행되는 함수
{
image = newImage;
colorToCheck = 50;

ParsingStepFirst();

for (int i = 0; i < allData.count; i++)
PrintImageToFile(i, &allData.data[i].rect);
}
void COCR::CreateStandard(CImage* newImage)		// 기본 이미지 데이터를 만들기 위해 실행되는 함수
{
image = newImage;
colorToCheck = 50;

ParsingStepFirst();
MakeImageData();

for (int i = 0; i < allData.count; i++)
PrintImageDataToFile(i, &allData.data[i].letter);
}
void COCR::CreateStandard(CImage* newImage)		// 기본 이미지 데이터를 만들어 텍스트 파일에 저장하고 불러옴
{
image = newImage;
colorToCheck = 50;

ParsingStepFirst();
MakeImageData();

int i = 0;
for (i = 0; i < 26; i++)
allData.data[i].letter.value = 'a' + i;
for (i = 0; i < 26; i++)
allData.data[i + 26].letter.value = 'A' + i;
for (i = 0; i < 10; i++)
allData.data[i + 52].letter.value = '0' + i;

PrintEveryImageDataInTextFile("standard.txt");		// 테스트를 위해 'standard.txt'파일에 기본 이미지 데이터의 value 값과 이미지 데이터를 출력하여 시각적으로 확인
GetStandardImageDataFromTextFile("standard.txt");		// 'standard.txt'에 저장된 기본 이미지 데이터를 불러와서 기본 이미지 데이터의 구조체인 Standard에 넣음

PrintAllStandardImageToTextFile("standardout.txt");		// 테스트를 위해 Standard 구조체에 있는 기본 이미지 데이터를 다시 'standardout.txt' 파일에 저장. 'standard.txt' == 'standardout.txt'이면 모든 함수가 정상적으로 동작
}*/
void COCR::CreateStandard(CImage* newImage)		// 기본 이미지 데이터를 만들어 텍스트 파일에 저장하고 불러옴
{
	image = newImage;
	colorToCheck = 50;

	//ParsingStepFirst();
//	MakeImageData();

	int i = 0;
	for (i = 0; i < 26; i++)
		allData.data[i].letter.value = 'a' + i;
	for (i = 0; i < 26; i++)
		allData.data[i + 26].letter.value = 'A' + i;
	for (i = 0; i < 10; i++)
		allData.data[i + 52].letter.value = '0' + i;

	PrintEveryImageDataInBinaryFile("standard.bin");		// 테스트를 위해 'standard.txt'파일에 기본 이미지 데이터의 value 값과 이미지 데이터를 출력하여 시각적으로 확인
	GetStandardImageDataFromBinaryFile("standard.bin");		// 'standard.txt'에 저장된 기본 이미지 데이터를 불러와서 기본 이미지 데이터의 구조체인 Standard에 넣음

	PrintAllStandardImageToTextFile("standardout.txt");		// 테스트를 위해 Standard 구조체에 있는 기본 이미지 데이터를 다시 'standardout.txt' 파일에 저장. 'standard.txt' == 'standardout.txt'이면 모든 함수가 정상적으로 동작
}


void COCR::ParsingStepFirst(CProgressDlg* pDlg)		// 전체 이미지에 대하여 라인을 구분
{
	allData.count = 0;
	data = &allData.data[0];

	int xMax = image->GetWidth();
	int yMax = image->GetHeight();

	int x, y;
	COLORREF rgb;
	int yTop, yBottom;
	bool isLetterLine;
	bool flagPrevLine;

	int xStart = (int)(xMax * 0.01);
	int xEnd = (int)(xMax * 0.99);

	flagPrevLine = false;

	pDlg->m_progressBar.SetRange(0, yMax);
	pDlg->m_progressBar.SetPos(0);

	for (y = 0; y < yMax; y++)
	{
		isLetterLine = false;

		for (x = xStart; x < xEnd; x++)
		{
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK)
			{
				isLetterLine = true;
				break;
			}
		}
		
		if (isLetterLine)
		{
			if (!flagPrevLine)
				yTop = y;
		}
		else
		{
			if (flagPrevLine)
			{
				yBottom = y - 1;
				ParsingStepSecond(yTop, yBottom, pDlg);
			}
		}

		flagPrevLine = isLetterLine;
		if (y % 2 == 0)
			pDlg->m_progressBar.SetPos(pDlg->m_progressBar.GetPos() + 1);
	}
}


void COCR::ParsingStepSecond(int yTop, int yBottom, CProgressDlg* pDlg)		// 하나의 라인에 대해 개별 문자를 나누는 작업
{
	int xMax = image->GetWidth();

	int x, y;
	COLORREF rgb;
	bool isLetterLine;
	bool flagPrevLine;

	flagPrevLine = false;

	for (x = 0; x < xMax; x++)
	{
		isLetterLine = false;

		for (y = yTop; y <= yBottom; y++)
		{
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK)
			{
				isLetterLine = true;
				break;
			}
		}

		if (isLetterLine)
		{
			if (!flagPrevLine)
			{
				data->rect.start.x = x;
				data->rect.start.y = yTop;
			}
		}
		else
		{
			if (flagPrevLine)
			{
				data->rect.end.x = x - 1;
				data->rect.end.y = yBottom;

				ParsingStepThird(&data->rect, pDlg);
				ParsingStepThird2(&data->rect, pDlg);
				ParsingStepThird(&data->rect, pDlg);

				allData.count += 1;
				data = &allData.data[allData.count];
			}
		}
		flagPrevLine = isLetterLine;
	}

	data->isFixed = true;
}


void COCR::ParsingStepThird(Rect* rect, CProgressDlg* pDlg)		// 한 문자의 사각형(세로 보정 작업)
{
	int x, y;
	COLORREF rgb;
	bool isLetterLine;

	// Letter Top
	for (y = rect->start.y; ; y--)
	{
		isLetterLine = false;

		for (x = rect->start.x; x <= rect->end.x; x++)
		{
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK)
			{
				rect->start.y = y;
				isLetterLine = true;
				break;
			}
		}
		if (!isLetterLine)
			break;
	}
	for (y = rect->start.y; ; y++)
	{
		isLetterLine = false;

		for (x = rect->start.x; x <= rect->end.x; x++)
		{
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK)
			{
				rect->start.y = y;
				isLetterLine = true;
				break;
			}
		}
		if (isLetterLine)
			break;
	}
	// Letter Bottom
	for (y = rect->end.y; ; y++)
	{
		isLetterLine = false;

		for (x = rect->start.x; x <= rect->end.x; x++)
		{
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK)
			{
				rect->end.y = y;
				isLetterLine = true;
				break;
			}
		}
		if (!isLetterLine)
			break;
	}
	for (y = rect->end.y; ; y--)
	{
		isLetterLine = false;

		for (x = rect->start.x; x <= rect->end.x; x++)
		{
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK)
			{
				rect->end.y = y;
				isLetterLine = true;
				break;
			}
		}
		if (isLetterLine)
			break;
	}
}


void COCR::PrintImageToFile(int fileNo, Rect* rect)
{
	CString strName;
	strName.Format(TEXT("./image%d.jpg"), fileNo);

	CImage newImage;
	int width, height;

	width = rect->end.x - rect->start.x + 1;
	height = rect->end.y - rect->start.y + 1;

	if (width <= 0 || height <= 0)
	{
		AfxMessageBox(_T("Error: 사진의 크기가 0보다 작습니다."));
		return;
	}

	newImage.Create(width, height, 32);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
			newImage.SetPixel(i, j, image->GetPixel(rect->start.x + i, rect->start.y + j));
	}
	newImage.Save(strName, Gdiplus::ImageFormatJPEG);
}


void COCR::ParsingStepThird2(Rect* rect, CProgressDlg* pDlg)
{
	int x, y;
	COLORREF rgb;
	bool isLetterLine;

	// Letter Left
	for (x = rect->start.x; ; x--)
	{
		isLetterLine = false;

		for (y = rect->start.y; y <= rect->end.y; y++)
		{
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK)
			{
				rect->start.x = x;
				isLetterLine = true;
				break;
			}
		}
		if (!isLetterLine)
			break;
	}
	for (x = rect->start.x; ; x++)
	{
		isLetterLine = false;

		for (y = rect->start.y; y <= rect->end.y; y++)
		{
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK)
			{
				rect->start.x = x;
				isLetterLine = true;
				break;
			}
		}
		if (isLetterLine)
			break;
	}
	// Letter Right
	for (x = rect->end.x; ; x++)
	{
		isLetterLine = false;

		for (y = rect->start.y; y <= rect->end.y; y++)
		{
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK)
			{
				rect->end.x = x;
				isLetterLine = true;
				break;
			}
		}
		if (isLetterLine)
			break;
	}
	for (x = rect->end.x; ; x--)
	{
		isLetterLine = false;

		for (y = rect->start.y; y <= rect->end.y; y++)
		{
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK)
			{
				rect->end.x = x;
				isLetterLine = true;
				break;
			}
		}
		if (isLetterLine)
			break;
	}
}


void COCR::MakeImageData(CProgressDlg* pDlg)		// 이미지 데이터 만들기
{
	int i, j;
	pDlg->m_progressBar.SetRange(0, allData.count);
	pDlg->m_progressBar.SetPos(allData.count / 2 + 1);

	for (i = 0; i < allData.count; i++)
	{
		Data *data = &allData.data[i];
		Letter *letter = &data->letter;
		Rect *rect = &data->rect;

		float xRate, yRate;
		int x, y;
		unsigned int buffer;
		COLORREF rgb;

		for (j = 0; j < 48; j++)
			letter->image[j] = 0x00000000;

		xRate = (float)(rect->end.x - rect->start.x) / (32 - 1);
		yRate = (float(rect->end.y - rect->start.y) / (48 - 1));

		for (y = 0; y < 48; y++)
		{
			for (x = 0; x < 32; x++)
			{
				rgb = image->GetPixel((int)(rect->start.x + (x * xRate)), (int)(rect->start.y + (y * yRate)));
				if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK)
				{
					buffer = 0x80000000;
					buffer >>= x;
					letter->image[y] |= buffer;
				}
			}
		}
		if (i % 2 == 1)
			pDlg->m_progressBar.SetPos(pDlg->m_progressBar.GetPos() + 1);
	}
}


void COCR::PrintImageDataToFile(int fileNo, Letter* letter)
{
	CString strName;
	strName.Format(TEXT("./ImageData%d.txt"), fileNo);
	std::ofstream o(strName);

	//FILE *fp;
	//fp = fopen(LPSTR(LPCTSTR(strName)), "wt");

	int x, y;
	unsigned int buffer;

	for (y = 0; y < 48; y++)
	{
		buffer = letter->image[y];

		for (x = 0; x < 32; x++)
		{
			if (buffer & 0x80000000)
				//fputc('1', fp);
				o << '1' << std::ends;

			else
				//fputc('0', fp);
				o << '0' << std::ends;
			buffer <<= 1;
		}
		//fputc('\n', fp);
		o << '\n' << std::ends;
	}
	//fclose(fp);
}


/*void COCR::PrintEveryImageDataInTextFile(char* fileName)
{
FILE *fp;
fp = fopen(fileName, "wt");

unsigned int buffer;
Letter *letter;

fprintf(fp, "%d\n", allData.count);

for (int i = 0; i < allData.count; i++)
{
letter = &allData.data[i].letter;

fprintf(fp, "\n%c\n", letter->value);

for (int y = 0; y < 48; y++)
{
buffer = letter->image[y];

for (int x = 0; x < 32; x++)
{
if (buffer & 0x80000000)
fputc('1', fp);
else
fputc('0', fp);
buffer <<= 1;
}
fputc('\n', fp);
}
}
fclose(fp);
}


void COCR::GetStandardImageDataFromTextFile(char* fileName)
{
FILE *fp;
fp = fopen(fileName, "rt");

int temp;
char ch;
unsigned int buffer;
Letter *letter;

fscanf(fp, "%d\n", &standard.count);

for (int i = 0; i < standard.count; i++)
{
letter = &standard.letter[i];
fscanf(fp, "\n%c\n", &letter->value);

for (int y = 0; y < 48; y++)
{
letter->image[y] = 0x00000000;

for (int x = 0; x < 32; x++)
{
if ((ch = fgetc(fp)) == '1')
{
buffer = 0x80000000;
buffer >>= x;
letter->image[y] |= buffer;
}
}
ch = fgetc(fp);
}
}
fclose(fp);
}*/


void COCR::PrintAllStandardImageToTextFile(char* fileName)
{
	FILE *fp;
	fp = fopen(fileName, "wt");

	unsigned int buffer;
	Letter *letter;

	fprintf(fp, "%d\n", standard.count);

	for (int i = 0; i < standard.count; i++)
	{
		letter = &standard.letter[i];

		fprintf(fp, "\n%c\n", letter->value);

		for (int y = 0; y < 48; y++)
		{
			buffer = letter->image[y];

			for (int x = 0; x < 32; x++)
			{
				if (buffer & 0x80000000)
					fputc('1', fp);
				else
					fputc('0', fp);
				buffer <<= 1;
			}
			fputc('\n', fp);
		}
	}
}


void COCR::PrintEveryImageDataInBinaryFile(char* fileName)
{
	FILE *fp;
	fp = fopen(fileName, "wb");

	Letter *letter;

	fprintf(fp, "%d\n", allData.count);

	for (int i = 0; i < allData.count; i++)
	{
		letter = &allData.data[i].letter;
		fprintf(fp, "%c\n", letter->value);

		for (int y = 0; y < 48; y++)
			fprintf(fp, "%d\n", letter->image[y]);
	}
	fclose(fp);
}


void COCR::GetStandardImageDataFromBinaryFile(char* fileName)
{
	FILE *fp;
	fp = fopen(fileName, "rb");

	Letter *letter;

	fscanf(fp, "%d\n", &standard.count);

	for (int i = 0; i < standard.count; i++)
	{
		letter = &standard.letter[i];
		fscanf(fp, "%c\n", &letter->value);

		for (int y = 0; y < 48; y++)
			fscanf(fp, "%d\n", &letter->image[y]);
	}
	fclose(fp);
}


void COCR::RunOCR(CImage* newImage, CString outFileName, CProgressDlg* pDlg)
{
	image = newImage;
	colorToCheck = 50;

	for (int i = 0; i < MAX_COUNT_DATA; i++)
	{
		allData.data[i].isFixed = false;
		allData.data[i].isSpaced = false;
		allData.data[i].isDeleted = false;
	}

	ParsingStepFirst(pDlg);		// 문자를 자르기
	MakeImageData(pDlg);		// 자른 문자들을 텍스트화

	FindLetterValue();
	AddSpaceValue();
	MakePeriodApostrophe();
	MakeQuotationMark();

	//ChangeBigSmallLetter();
	CheckBigSmallLetter();		// 대소문자 확인

	StoreLetterToTextFile(outFileName);
}


void COCR::FindLetterValue()
{
	int count, maxCount;
	unsigned int buffer, bit;

	for (int i = 0; i < allData.count; i++)
	{
		Data *data = &allData.data[i];
		Letter *letter = &data->letter;
		Rect *rect = &data->rect;

		maxCount = 0;

		for (int j = 0; j < standard.count; j++)
		{
			count = 0;

			for (int y = 0; y < 48; y++)
			{
				buffer = letter->image[y] ^ standard.letter[j].image[y];
				for (int x = 0; x < 32; x++)
				{
					bit = 0x80000000;
					bit >>= x;
					bit = bit & buffer;

					if (!bit)
						count += 1;
				}
			}

			if (count > maxCount)
			{
				letter->value = standard.letter[j].value;
				maxCount = count;
			}
		}
	}
}


void COCR::StoreLetterToTextFile(CString outFileName)
{
	FILE *fp;
	fp = fopen((char*)((LPCSTR)(outFileName)), "wt");

	CString strResult;
	strResult.Format(_T(""));

	/*	CString a, b, c;
	a.Format(_T("%d"), allData.data[5].rect.start.y);
	b.Format(_T("%d"), allData.data[5].rect.end.y);
	if (allData.data[1].isDeleted)
	c = "Delete";
	else
	c = "Alive";
	AfxMessageBox(a);
	AfxMessageBox(b);*/
	//AfxMessageBox(c);

	for (int i = 0; i < allData.count; i++)
	{
		CString chr2str;
		chr2str.Format(_T("%c"), allData.data[i].letter.value);

		if (!allData.data[i].isDeleted)		// 큰따옴표("")처리
		{
			fputc(allData.data[i].letter.value, fp);
			strResult += chr2str;
		}

		if (allData.data[i + 1].isFixed)		// 개행 삽입
		{
			fputc('\n', fp);
			strResult += "\n";
		}

		if (allData.data[i + 1].isSpaced)		// 공백 삽입
		{
			fputc(' ', fp);
			strResult += " ";
		}

		//	PrintImageDataToFile(i, &allData.data[i].letter);
		//	PrintImageToFile(i, &allData.data[i].rect);
	}
	fclose(fp);
	
	textbox = new CTextboxDlg();
	textbox->m_strTextbox.SetString(strResult);
	if (textbox->m_strTextbox.IsEmpty() == FALSE) {
		textbox->Create(IDD_TEXTBOX);
		m_bTextboxEmpty = FALSE;
		textbox->ShowWindow(SW_SHOW);
	}
	else
		AfxMessageBox(_T("텍스트 변환에 실패하였습니다."));
}


void COCR::AddSpaceValue()
{
	int gap, maxGap;
	maxGap = 0;

	for (int i = 1; i < allData.count; i++)
	{
		gap = allData.data[i].rect.start.x - allData.data[i - 1].rect.end.x;

		if (!allData.data[i].isFixed && maxGap < gap)
			maxGap = gap;
	}

	for (int i = 1; i < allData.count; i++)
	{
		gap = allData.data[i].rect.start.x - allData.data[i - 1].rect.end.x;

		if (!allData.data[i].isFixed)
		{
			if (maxGap - 5 < gap && gap < maxGap + 5)
				allData.data[i].isSpaced = true;
		}
	}
}


int COCR::CalculateMidlineValue(int index)
{
	int count = 0;
	float sumHeight = 0;

	for (int i = index; i < allData.count; i++)
	{
		if (allData.data[i + 1].isFixed)
			break;

		sumHeight += ((allData.data[i].rect.end.y + allData.data[i].rect.start.y) / 2);
		count++;
	}

	return (int)(sumHeight / count);
}


void COCR::MakePeriodApostrophe()
{
	int avgMidline;

	for (int i = 0; i < allData.count;)
	{
		avgMidline = CalculateMidlineValue(i);

		while (!allData.data[i].isFixed)
		{
			if (allData.data[i].rect.start.y > avgMidline)			//. , 인식하는 부분
			{
				if ((allData.data[i].letter.value == 'I') || (allData.data[i].letter.value == 'l'))
					allData.data[i].letter.value = '.';
				else if ((allData.data[i].letter.value == 'i'))
					allData.data[i].letter.value = ',';
			}
			else if (allData.data[i].rect.end.y < avgMidline)
			{
				if ((allData.data[i].letter.value == 'I') || (allData.data[i].letter.value == 'l') || (allData.data[i].letter.value == ','))
					allData.data[i].letter.value = 0x27;		// '
			}
			i++;
		}
		i++;
	}
}

void COCR::MakeQuotationMark()
{
	for (int i = 0; i < allData.count; i++)
	{
		if (!(allData.data[i].isDeleted) && allData.data[i].letter.value == 0x27)
		{
			if (allData.data[i + 1].letter.value == 0x27)
			{
				allData.data[i].letter.value = 0x22;		// "
				allData.data[i + 1].isDeleted = true;
			}
		}
	}
}


/*void COCR::ChangeBigSmallLetter()
{
bool isFirstChar = true;
char *ch, *chNext, *chDbNext;

for (int i = 0; i < allData.count - 1; i++)
{
ch = &(allData.data[i].letter.value);
chNext = &(allData.data[i + 1].letter.value);
chDbNext = &(allData.data[i + 2].letter.value);

if (isFirstChar)
{
if (IsSmallLetter(*ch))
{
ChangeSmallToBigLetter(ch);
isFirstChar = false;
}
else if (IsBigLetter(*ch))
isFirstChar = false;
else if (*ch == '0')
{
if (*chNext == '0')
{
if (IsAlphabet(*chDbNext))
*ch = 'O';
}
else if (IsAlphabet(*chNext))
*ch = 'O';

isFirstChar = false;
}
}
else
{
if (IsBigLetter(*ch))
ChangeBigToSmallLetter(ch);
else if (*ch == '0')
{
if (*chNext == '0')
{
if (IsAlphabet(*chDbNext))
*ch = 'o';
}
else if (IsAlphabet(*chNext))
*ch = 'o';
}

if ((*ch == '.') || (*ch == 0x22))
isFirstChar = true;
}
}
}*/


bool COCR::IsAlphabet(char value)
{
	if (value >= 'A' && value <= 'Z')
		return true;
	else if (value >= 'a' && value <= 'z')
		return true;

	return false;
}


bool COCR::IsBigLetter(char value)
{
	if (value >= 'A' && value <= 'Z')
		return true;

	return false;
}


bool COCR::IsSmallLetter(char value)
{
	if (value >= 'a' && value <= 'z')
		return true;

	return false;
}


void COCR::ChangeBigToSmallLetter(char* value)
{
	if (*value == 'I')
		*value = 'l';
	else if (*value == 'C')
		*value = 'c';
	else if (*value == 'O')
		*value = 'o';
	else if (*value == 'S')
		*value = 's';
	else if (*value == 'U')
		*value = 'u';
	else if (*value == 'V')
		*value = 'v';
	else if (*value == 'W')
		*value = 'w';
	else if (*value == 'X')
		*value = 'x';
	else if (*value == 'Z')
		*value = 'z';
}


void COCR::ChangeSmallToBigLetter(char* value)
{
	if (*value == 'l')
		*value = 'I';
	else if (*value == 'c')
		*value = 'C';
	else if (*value == 'o')
		*value = 'O';
	else if (*value == 's')
		*value = 'S';
	else if (*value == 'u')
		*value = 'U';
	else if (*value == 'v')
		*value = 'V';
	else if (*value == 'w')
		*value = 'W';
	else if (*value == 'x')
		*value = 'X';
	else if (*value == 'z')
		*value = 'Z';
}


void COCR::CheckBigSmallLetter()		// 대소문자 확인
{
	int nMaxHeight;		// 가장 작은 rect.start.y 값
	int idxStart;

	for (int i = 0; i < allData.count; i++)
	{
		if (i == 0 || allData.data[i].isFixed)		// 한 줄의 시작
			idxStart = i;

		if (allData.data[i + 1].isFixed || i == allData.count - 1)		// 한 줄의 끝
		{
			nMaxHeight = 999999999;

			for (int j = idxStart; j < i; j++)		// 한 줄씩 nMaxHeight를 찾음
			{
				if (nMaxHeight > allData.data[j].rect.start.y)
					nMaxHeight = allData.data[j].rect.start.y;
			}

			for (int j = idxStart; j < i; j++)			// 한줄씩 대소문자 판별
			{
				// nMaxHeight와 높이가 비슷하면 대문자
				if (nMaxHeight - 3 < allData.data[j].rect.start.y && allData.data[j].rect.start.y < nMaxHeight + 3)
					ChangeSmallToBigLetter(&allData.data[j].letter.value);

				// 그 외이면 소문자
				else
					ChangeBigToSmallLetter(&allData.data[j].letter.value);
			}
		}
	}
}


void COCR::DestroyTextDialog()
{
		textbox->ShowWindow(SW_HIDE);
		textbox->DestroyWindow();
}
