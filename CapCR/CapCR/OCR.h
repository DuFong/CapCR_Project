#pragma once

#define MAX_COUNT_STANDARD				80			// �⺻ �̹��� �������� �ִ� ����
#define MAX_COUNT_DATA							2000		// ���� �̹������� �ִ� ���� ��
#define RANGE_OF_COLOR_TO_CHECK		130		// ���� ���� �ν��ϱ� ���� ��

#define RATE_START_FOR_PARSING			0.1		// �̹��� �Ľ��� ���� ���� ����
#define RATE_END_FOR_PARSING				0.3		// �̹��� �Ľ��� ���� ������ �κ��� ����

struct Point {
	int x;
	int y;
};

struct Rect {
	Point start;
	Point end;
};

struct Letter {
	char value;
	unsigned int image[48];
};

struct Standard {
	int count;
	Letter letter[62];
};

struct Data {
	Letter letter;
	Rect rect;
	bool isFixed;
	bool isSpaced;
	bool isDeleted;
};

struct AllData {
	int count;
	Data data[MAX_COUNT_DATA];
};

struct AllDataPointer {
	int count;
	Data *data[MAX_COUNT_DATA + MAX_COUNT_DATA];
};

class COCR
{
private:
	CImage *image;
	Standard standard;
	AllData allData;
	AllDataPointer allDataPointer;
	Data *data;

	Data letterSpace;

	int colorToCheck;

public:
	COCR();
	~COCR();

	void CreateStandard(CImage* newImage);
	void ParsingStepFirst();
	void ParsingStepSecond(int yTop, int yBottom);
	void ParsingStepThird(Rect* rect);
	void PrintImageToFile(int fileNo, Rect* rect);
	void ParsingStepThird2(Rect* rect);
	void MakeImageData();
	void PrintImageDataToFile(int fileNo, Letter* letter);
	//	void PrintEveryImageDataInTextFile(char* fileName);
	//	void GetStandardImageDataFromTextFile(char* fileName);
	void PrintAllStandardImageToTextFile(char* fileName);
	void PrintEveryImageDataInBinaryFile(char* fileName);
	void GetStandardImageDataFromBinaryFile(char* fileName);
	void RunOCR(CImage* newImage, CString outFileName, int colorLetter);
	void FindLetterValue();
	void StoreLetterToTextFile(CString outFileName);
	void AddSpaceValue();
	int CalculateMidlineValue(int index);
	void MakePeriodApostrophe();
	void MakeQuotationMark();
	//void ChangeBigSmallLetter();
	bool IsAlphabet(char value);
	bool IsBigLetter(char value);
	bool IsSmallLetter(char value);
	void ChangeBigToSmallLetter(char* value);
	void ChangeSmallToBigLetter(char* value);
	void CheckBigSmallLetter();
};

