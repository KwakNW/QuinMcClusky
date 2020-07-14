#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int selectsort4(int arr[][4], int num, int size) // 2차배열에서 num 첫번째 방 위치 size = variable
{
	int i, j, k;

	for (i = 0; i < size - 1; i++) {
		for (j = i + 1; j < size; j++) {
			if (arr[num][i] > arr[num][j]) {
				k = arr[num][i];
				arr[num][i] = arr[num][j];
				arr[num][j] = k;
			}
		}
	}
}

int main(void)
{
	int variable;

	printf("교수님 제 과제는 Don't care항도 안되고 변수도 4개짜리만 되지만 최대한 돌아가도록 만들었습니다. \n");
	printf("일단 확실한 것은 0,1,2,5,6,7,8,9,10,14 인 경우는 확실히 돌아갑니다.. 최대한 노력했습니다. \n\n");

	printf("변수의 갯수를 입력하시오(2~4) : ");
	scanf("%d", &variable);
	while (variable < 2 || variable > 4)
	{
		printf("변수의 갯수가 2보다 작거나 4보다 큽니다. 다시 입력해주세요. \n");
		printf("변수의 갯수를 입력하시오(2~4) : ");
		scanf("%d", &variable);
	}

	// Minterm 항의 갯수 받기
	int n, Minterm;
	int pow = 1;

	int dontcare;

	for (n = 1; n <= variable; n++)
	{
		pow *= 2;
	}

	printf("몇개의 Minterm항을 가지는가?(Don't care항 포함) (0~%d): ", pow);
	scanf("%d", &Minterm);

	while ((Minterm > pow) || (Minterm <= 0))
	{
		printf("몇개의 Minterm항을 가지는가?(Don't care항 포함) (0~%d) : ", pow);
		scanf("%d", &Minterm);
	}

	char dont;
	printf("Don't care항을 가집니까? [y/n] : ");
	scanf(" %c", &dont);

	while (!(dont == 'y') && !(dont == 'n'))
	{
		printf("[y/n] 중에 선택해주세요. \n");
		printf("Don't care항을 가집니까? [y/n] : ");
		scanf(" %c", &dont);
	}

	if (dont == 'y') {
		printf("몇개의 Don't care항을 가지는가?: ");
		scanf("%d", &dontcare);
	}

	printf("부울 함수식을 입력하시오.(10진수로) \n ");

	// Minterm이나 Don't care항을 담을 변수
	char M_term[33] = { 0 }, D_term[33] = { 0 };

	switch (variable)
	{
	case(2):
		printf("F(A,B) = ∑m(");
		scanf("%s", M_term);
		break;
	case(3):
		printf("F(A,B,C) = ∑m(");
		scanf("%s", M_term);
		break;
	case(4):
		printf("F(A,B,C,D) = ∑m(");
		scanf("%s", M_term);
		break;
	}

	if (dont == 'y')
	{
		printf(" + ∑d(");
		scanf("%s", D_term);
	}

	char *Msplit = strtok(M_term, ",");
	int term[16];
	int i;
	int m = 0;

	while (Msplit != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
	{
		//printf("%s\n", Msplit);
		term[m] = atoi(Msplit);

		m++;
		Msplit = strtok(NULL, ",");      // 다음 문자열을 잘라서 포인터를 반환
	}

	/*for (i = 0; i < m; i++)
	{
		printf("%d\n", term[i]);
	}*/

	char *Dsplit = strtok(D_term, ",");
	int dterm[16];
	int d;

	d = 0;
	while (Dsplit != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
	{
		//printf("%s\n", Msplit);
		dterm[d] = atoi(Dsplit);

		d++;
		Dsplit = strtok(NULL, ",");      // 다음 문자열을 잘라서 포인터를 반환
	}
	/*for (i = 0; i < d; i++)
	{
		printf("%d\n", dterm[i]);
	}*/


	//10진수를 2진수로 변환
	int bin[16][4] = { 0 };
	int b, mok, nmg, j, k;
	int Num = 0;

	for (i = 0; i < m; i++)
	{
		b = term[i];
		j = 0;
		do
		{
			mok = b / 2;

			nmg = b - mok * 2;
			bin[i][(variable - 1) - j] = nmg;

			j++;
			b = mok;
		} while (mok != 0);
	}

	for (k = 0; k < Minterm; k++)
	{
		printf("%#2d  ", term[k]);
		for (j = 0; j < variable; j++)
		{
			printf("%d ", bin[k][j]);
		}
		printf("\n");
	}

	printf("\n----------------1차 구분-------------------\n\n");

	// 배열 안의 0과 1을 각각 비교
	int sum = 0, a = 0, ar = 0;
	int s;
	int arr[32][4] = { 0 };
	int arr_name[100][2] = { 0 };
	int p = 0;

	for (k = 0; k < Minterm; k++)
	{
		for (s = 1; s < Minterm - k; s++)
		{
			for (j = 0; j < 4; j++)
			{
				if (bin[k][j] == bin[k + s][j])
					sum += 0;
				else
					sum += 1;
			}

			if (sum == 1)
			{

				ar = 0;
				for (j = 0; j < 4; j++)
				{
					if (bin[k][j] == bin[k + s][j])
					{
						arr[a][ar] = bin[k][j];
					}
					else
					{
						arr[a][ar] = 9;
					}
					ar++;
				}
				a++;
				//}
				arr_name[p][0] = term[k];
				arr_name[p][1] = term[k + s];

				p++;

				//printf("(%d, %d)\t", arr_name[p][0], arr_name[p][1]);
				//p++;

			/*	for (i = 0; i < a; i++)
				{
					for (j = 0; j < ar; j++)
					{
						printf("%d ", arr[i][j]);
					}
					printf("\n");
				}*/
			}
			sum = 0;
		}

	}
	int z = 0;

	for (i = 0; i < a; i++)
	{
		if (z < p)
		{
			printf("(%#2d, %#2d) ", arr_name[z][0], arr_name[z][1]);
			Num++;
		}
		z++;


		for (j = 0; j < ar; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	printf("\n----------------2차 구분-------------------\n\n");

	int arr2[100][4] = { 0 };
	int arr_name2[100][4] = { 0 };
	int q = 0;

	int pp = 0;
	a = 0;
	for (k = 0; k < z; k++)
	{
		for (s = 1; s < z - k; s++)
		{
			for (j = 0; j < 4; j++)
			{
				if (arr[k][j] == arr[k + s][j])
					sum += 0;
				else
					sum += 1;
			}

			if (sum == 1)
			{
				ar = 0;
				for (j = 0; j < 4; j++)
				{
					if (arr[k][j] == arr[k + s][j])
					{
						arr2[a][ar] = arr[k][j];
					}
					else
					{
						arr2[a][ar] = 9;
					}
					ar++;
				}
				a++;
				arr_name2[pp][0] = arr_name[k][0];
				arr_name2[pp][1] = arr_name[k][1];
				arr_name2[pp][2] = arr_name[k + s][0];
				arr_name2[pp][3] = arr_name[k + s][1];

				selectsort4(arr_name2, pp, 4);

				pp++;
			}
			sum = 0;
		}

	}

	z = 0;
	for (i = 0; i < a; i++)
	{
		if (z < pp)
		{
			printf("(%#2d, %#2d, %#2d, %#2d) ", arr_name2[z][0], arr_name2[z][1], arr_name2[z][2], arr_name2[z][3]);
		}
		z++;

		for (j = 0; j < ar; j++)
		{
			printf("%d ", arr2[i][j]);
		}
		printf("\n");
	}

	printf("\n---------------중복 제거------------------\n\n");

	// 중복 제거를 위한 작업
	int arr3[100][4] = { 0 };
	int arr_name3[100][4] = { 0 };
	int count = 0;
	int Ncount = 0;
	int kk = 0;

	for (int i = 0; i < a; i++) {
		int sum = 0;

		for (int s = 1; s < a - i; s++) {
			if (arr_name2[i][0] == arr_name2[i + s][0] && arr_name2[i][1] == arr_name2[i + s][1] && arr_name2[i][2] == arr_name2[i + s][2] && arr_name2[i][3] == arr_name2[i + s][3]) {
				sum++;
			}
		}

		if (sum < 1)
		{
			Ncount++;
		}


		if (sum < 1) {
			while (kk < Ncount) {
				arr_name3[kk][0] = arr_name2[i][0];
				arr_name3[kk][1] = arr_name2[i][1];
				arr_name3[kk][2] = arr_name2[i][2];
				arr_name3[kk][3] = arr_name2[i][3];
				arr3[kk][0] = arr2[i][0];
				arr3[kk][1] = arr2[i][1];
				arr3[kk][2] = arr2[i][2];
				arr3[kk][3] = arr2[i][3];

				kk++;
			}
		}
	}
	for (int h = 0; h < Ncount; h++) {
		printf("(%#2d, %#2d, %#2d, %#2d) ", arr_name3[h][0], arr_name3[h][1], arr_name3[h][2], arr_name3[h][3]);
		printf("%d %d %d %d \n", arr3[h][0], arr3[h][1], arr3[h][2], arr3[h][3]);
	}

	int newarr[32][4] = { 0 };
	int newarr_name[100][2] = { 0 };
	int Acount = 0;
	int hh = 0;

	// 안 쓴 arr 항들 뽑아오기
	for (int j = 0; j < Num; j++) {
		sum = 0;
		for (int k = 0; k < Ncount; k++) {
			for (int i = 0; i < 4; i++) {
				if (arr_name[j][0] == arr_name3[k][i]) {
					for (int h = 0; h < 4; h++) {
						if (arr_name[j][1] == arr_name3[k][h])
							sum++;
					}
				}
			}
		}

		if (sum < 1) {
			Acount++;
		}

		if (sum < 1) {
			while (hh < Acount) {
				newarr_name[hh][0] = arr_name[j][0];
				newarr_name[hh][1] = arr_name[j][1];
				newarr[hh][0] = arr[j][0];
				newarr[hh][1] = arr[j][1];
				newarr[hh][2] = arr[j][2];
				newarr[hh][3] = arr[j][3];

				hh++;

			}
		}
	}
	for (int h = 0; h < Acount; h++) {
		printf("(%#2d, %#2d) \t ", newarr_name[h][0], newarr_name[h][1]);
		printf("%d %d %d %d \n", newarr[h][0], newarr[h][1], newarr[h][2], newarr[h][3]);
	}

	// 9를 -로 바꾸는 작업
	printf("\n---------------9를 -로 변환---------------\n\n");
	printf("\t \t  a b c d\n");
	for (int h = 0; h < Ncount; h++) {
		printf("(%#2d, %#2d, %#2d, %#2d) ", arr_name3[h][0], arr_name3[h][1], arr_name3[h][2], arr_name3[h][3]);
		for (int i = 0; i < 4; i++) {
			if (arr3[h][i] == 9) {
				printf(" - ");
			}
			else {
				printf("%d ", arr3[h][i]);
			}
		}
		printf("\n");
	}

	for (int h = 0; h < Acount; h++) {
		printf("(%#2d, %#2d) \t  ", newarr_name[h][0], newarr_name[h][1]);
		for (int i = 0; i < 4; i++) {
			if (newarr[h][i] == 9) {
				printf(" - ");
			}
			else {
				printf("%d ", newarr[h][i]);
			}
		}
		printf("\n");
	}

	// 테이블 만들기
	int Xterm[16] = { 0 };
	int Tterm[100][16] = { 0 };
	char X = 'X';
	char space = ' ';
	int Tcount = 0, TTcount = 0;


	printf("\n---------------------------------Table----------------------------------\n");
	printf("\t \t |");

	for (int k = 0; k < Minterm; k++)
	{
		printf("%#5d", term[k]);
	}

	printf("\n------------------------------------------------------------------------\n");

	for (int h = 0; h < Acount; h++) {
		printf("(%#2d, %#2d) \t |", newarr_name[h][0], newarr_name[h][1]);

		for (int k = 0; k < Minterm; k++)
		{
			if (newarr_name[h][0] == term[k] || newarr_name[h][1] == term[k]) {
				Tterm[Tcount][k] = 1;
				printf(" %4c", X);
				Xterm[k]++;
			}
			else {
				Tterm[Tcount][k] = 0;
				printf(" %4c", space);
			}
		}
			printf("\n");
			Tcount++;
			TTcount++;
	}

	for (int h = 0; h < Ncount; h++) {
		printf("(%#2d, %#2d, %#2d, %#2d) |", arr_name3[h][0], arr_name3[h][1], arr_name3[h][2], arr_name3[h][3]);

		for (int k = 0; k < Minterm; k++)
		{
			if (arr_name3[h][0] == term[k] || arr_name3[h][1] == term[k] || arr_name3[h][2] == term[k] || arr_name3[h][3] == term[k]) {
				Tterm[Tcount][k] = 1;
				printf(" %4c", X);
				Xterm[k]++;
			}
			else {
				Tterm[Tcount][k] = 0;
				printf(" %4c", space);
			}
		}
		printf("\n");
		Tcount++;
	}

	printf("\n\n---------------------------------Table----------------------------------\n");
	printf("\t \t |");

	for (int k = 0; k < Minterm; k++)
	{
		printf("%#5d", term[k]);
	}

	printf("\n------------------------------------------------------------------------\n");

	int H = 0;
	for (int h = 0; h < Acount; h++) {
		printf("(%#2d, %#2d) \t |", newarr_name[h][0], newarr_name[h][1]);

		for (int t = H; t < H+1; t++)
		{
			for (int k = 0; k < Minterm; k++) {
				printf(" %4d", Tterm[t][k]);
			}
			printf("\n");
		}
		H++;
	}


	for (int h = 0; h < Ncount; h++) {
		printf("(%#2d, %#2d, %#2d, %#2d) |", arr_name3[h][0], arr_name3[h][1], arr_name3[h][2], arr_name3[h][3]);

		for (int t = H; t < H+1; t++) {
			for (int k = 0; k < Minterm; k++) {
				printf(" %4d", Tterm[t][k]);
			}
			printf("\n");
		}
		H++;
	}

	int check[56] = { 0 };
	int checkr[16] = { 0 };

	for (int h = 0; h < Acount; h++) {
		for (int k = 0; k < Minterm; k++){
			if (Xterm[k] == 1) {
				if (newarr_name[h][0] == term[k] || newarr_name[h][1] == term[k]) {
					for (int kk = 0; kk < Minterm; kk++) {
						if (Tterm[h][kk] == 1) {
							for (int c = 0; c < TTcount; c++) {
								Tterm[c][kk] = 0; // 열 삭제
								checkr[kk] = 1; //삭제 열 체크
							}
							Tterm[h][kk] = 0; // 행 삭제
							check[h] = 1; //삭제 행 체크
						}
					}
				}
			}
		}
	}
	
	for (int h = 0; h < Ncount; h++) {
		for (int k = 0; k < Minterm; k++) {
			if (Xterm[k] == 1) {
				if (arr_name3[h][0] == term[k] || arr_name3[h][1] == term[k] || arr_name3[h][2] == term[k] || arr_name3[h][3] == term[k]) {
					for (int kk = 0; kk < Minterm; kk++) {
						if (Tterm[h + TTcount][kk] == 1) {
							for (int c = 0; c < Tcount; c++) {
								Tterm[c][kk] = 0;
								checkr[kk] = 1; //삭제 열 체크
							}
							Tterm[h + TTcount][kk] = 0;
							check[h + TTcount] = 1;
						}
					}
				}
			}
		}
	}

	printf("\n\n---------------------------------Table----------------------------------\n");
	printf("\t \t |");

	for (int k = 0; k < Minterm; k++)
	{
		printf("%#5d", term[k]);
	}

	printf("\n------------------------------------------------------------------------\n");

	int HH = 0;
	for (int h = 0; h < Acount; h++) {
		printf("(%#2d, %#2d) \t |", newarr_name[h][0], newarr_name[h][1]);

		for (int t = HH; t < HH + 1; t++)
		{
			for (int k = 0; k < Minterm; k++) {
				printf(" %4d", Tterm[t][k]);
			}
			printf("\n");
		}
		HH++;
	}


	for (int h = 0; h < Ncount; h++) {
		printf("(%#2d, %#2d, %#2d, %#2d) |", arr_name3[h][0], arr_name3[h][1], arr_name3[h][2], arr_name3[h][3]);

		for (int t = HH; t < HH + 1; t++) {
			for (int k = 0; k < Minterm; k++) {
				printf(" %4d", Tterm[t][k]);
			}
			printf("\n");
		}
		HH++;
	}



	printf("\n\n----------------------선택된 항들----------------------------\n");
	//char finalarr[6][4] = { 0 };

	int finalcheck[20] = { 0 };
	int fc = 0;

	printf("\t \t   a  b  c  d\n");
	for (int h = 0; h < Tcount; h++) {
		int fsum = 0;
		if (check[h] == 1) {
			if (h < TTcount) {
				printf("(%#2d, %#2d) \t |", newarr_name[h][0], newarr_name[h][1]);
				fc++;
				for (int i = 0; i < 4; i++) {
					if (newarr[h][i] == 9) {
						printf(" - ");
					}
					else {
						printf("%2d ", newarr[h][i]);
					}
				}
				printf("\n");
			}
			else {
				printf("(%#2d, %#2d, %#2d, %#2d) |", arr_name3[h - TTcount][0], arr_name3[h - TTcount][1], arr_name3[h - TTcount][2], arr_name3[h - TTcount][3]);
				fc++;
				for (int i = 0; i < 4; i++) {
					if (arr3[h - TTcount][i] == 9) {
						printf(" - ");
					}
					else {
						printf("%2d ", arr3[h - TTcount][i]);
					}
				}
				printf("\n");
			}
		}

		for (int j = 0; j < Minterm; j++) {
			fsum += Tterm[h][j];
		}

		if (fsum == 2) {
			if (h < TTcount) {
				printf("(%#2d, %#2d) \t |", newarr_name[h][0], newarr_name[h][1]);
				fc++;
				for (int i = 0; i < 4; i++) {
					if (newarr[h][i] == 9) {
						printf(" - ");
					}
					else {
						printf("%2d ", newarr[h][i]);
					}
				}
				printf("\n");
			}
			else {
				printf("(%#2d, %#2d, %#2d, %#2d) |", arr_name3[h - TTcount][0], arr_name3[h - TTcount][1], arr_name3[h - TTcount][2], arr_name3[h - TTcount][3]);
				fc++;
				for (int i = 0; i < 4; i++) {
					if (arr3[h - TTcount][i] == 9) {
						printf(" - ");
					}
					else {
						printf("%2d ", arr3[h - TTcount][i]);
					}
				}
				printf("\n");
			}
		}
	}

	printf("\n----------------------결과----------------------------\n");
	printf("F = ");
	//char finalarr[6][4] = { 0 };

	int plus = 0;

	for (int h = 0; h < Tcount; h++) {
		int fsum = 0;
		if (check[h] == 1) {
			if (h < TTcount) {
				for (int i = 0; i < variable; i++) {
					switch (i) {
					case 0:
						if (newarr[h][i] == 9)
							;
						else if (newarr[h][i] == 1)
							printf("a");
						else
							printf("a\'");
						break;
					case 1:
						if (newarr[h][i] == 9)
							;
						else if (newarr[h][i] == 1)
							printf("b");
						else
							printf("b\'");
						break;
					case 2:
						if (newarr[h][i] == 9)
							;
						else if (newarr[h][i] == 1)
							printf("c");
						else
							printf("c\'");
						break;
					case 3:
						if (newarr[h][i] == 9)
							;
						else if (newarr[h][i] == 1)
							printf("d");
						else
							printf("d\'");
						break;
					}
				}
				if (plus < fc-1) {
					printf(" + ");
					plus++;
				}
			}
			else {
					for (int i = 0; i < variable; i++) {
					switch (i) {
					case 0:
						if (arr3[h - TTcount][i] == 9)
							;
						else if (arr3[h - TTcount][i] == 1)
							printf("a");
						else
							printf("a\'");
						break;
					case 1:
						if (arr3[h - TTcount][i] == 9)
							;
						else if (arr3[h - TTcount][i] == 1)
							printf("b");
						else
							printf("b\'");
						break;
					case 2:
						if (arr3[h - TTcount][i] == 9)
							;
						else if (arr3[h - TTcount][i] == 1)
							printf("c");
						else
							printf("c\'");
						break;
					case 3:
						if (arr3[h - TTcount][i] == 9)
							;
						else if (arr3[h - TTcount][i] == 1)
							printf("d");
						else
							printf("d\'");
						break;
					}
				}
				if (plus < fc - 1) {
					printf(" + ");
					plus++;
				}
			}
		}

		for (int j = 0; j < Minterm; j++) {
			fsum += Tterm[h][j];
		}

		if (fsum == 2) {
			if (h < TTcount) {
				for (int i = 0; i < variable; i++) {
					switch (i) {
					case 0:
						if (newarr[h][i] == 9)
							;
						else if (newarr[h][i] == 1)
							printf("a");
						else
							printf("a\'");
						break;
					case 1:
						if (newarr[h][i] == 9)
							;
						else if (newarr[h][i] == 1)
							printf("b");
						else
							printf("b\'");
						break;
					case 2:
						if (newarr[h][i] == 9)
							;
						else if (newarr[h][i] == 1)
							printf("c");
						else
							printf("c\'");
						break;
					case 3:
						if (newarr[h][i] == 9)
							;
						else if (newarr[h][i] == 1)
							printf("d");
						else
							printf("d\'");
						break;
					}
				}
				if (plus < fc - 1) {
					printf(" + ");
					plus++;
				}
			}
			else {
				for (int i = 0; i < variable; i++) {
					switch (i) {
					case 0:
						if (arr3[h - TTcount][i] == 9)
							;
						else if (arr3[h - TTcount][i] == 1)
							printf("a");
						else
							printf("a\'");
						break;
					case 1:
						if (arr3[h - TTcount][i] == 9)
							;
						else if (arr3[h - TTcount][i] == 1)
							printf("b");
						else
							printf("b\'");
						break;
					case 2:
						if (arr3[h - TTcount][i] == 9)
							;
						else if (arr3[h - TTcount][i] == 1)
							printf("c");
						else
							printf("c\'");
						break;
					case 3:
						if (arr3[h - TTcount][i] == 9)
							;
						else if (arr3[h - TTcount][i] == 1)
							printf("d");
						else
							printf("d\'");
						break;
					}
				}
				if (plus < fc - 1) {
					printf(" + ");
					plus++;
				}
			}
		}
	}

	printf("\n\n");
}





