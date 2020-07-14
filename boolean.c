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
		for (s = 1; s < Minterm-k; s++)
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

	printf("\n----------------중복 제거-------------------\n\n");

	// 중복 제거를 위한 작업
	int arr3[100][4] = { 0 };
	int arr_name3[100][4] = { 0 };
	int count = 0;
	int Ncount = 0;

	for (int i = 0; i < a; i++) {
		int sum = 0;
		count = 0;

		for (int s = 1; s < a - i; s++) {
			if (arr_name2[i][0] == arr_name2[i + s][0] && arr_name2[i][1] == arr_name2[i + s][1] && arr_name2[i][2] == arr_name2[i + s][2] && arr_name2[i][3] == arr_name2[i + s][3]) {
				sum++;
			}
		}
		if (sum < 1)
		{
			count++;
			Ncount++;
		}
		

		if (sum < 1) {
			for (int k = 0; k < count; k++) {
				arr_name3[k][0] = arr_name2[i][0];
				arr_name3[k][1] = arr_name2[i][1];
				arr_name3[k][2] = arr_name2[i][2];
				arr_name3[k][3] = arr_name2[i][3];
				arr3[k][0] = arr2[i][0];
				arr3[k][1] = arr2[i][1];
				arr3[k][2] = arr2[i][2];
				arr3[k][3] = arr2[i][3];
			}
		}

		for (int k = 0; k < count; k++) {
			printf("(%#2d, %#2d, %#2d, %#2d) ", arr_name3[k][0], arr_name3[k][1], arr_name3[k][2], arr_name3[k][3]);
			printf("%d %d %d %d \n", arr3[k][0], arr3[k][1], arr3[k][2], arr3[k][3]);
		}
	}

	// 안 쓴 arr 항들 뽑아오기
	for (int j = 0; j < Num; j++) {
		sum = 0;
		for (int i = 0; i < Ncount; i++) {
			if (((arr_name[j][0] == arr_name3[i][0]) || (arr_name[j][0] == arr_name3[i][1]) || (arr_name[j][0] == arr_name3[i][2]) || (arr_name[j][0] == arr_name3[i][3]))
				&& ((arr_name[j][1] == arr_name3[i][0]) || (arr_name[j][1] == arr_name3[i][1]) || (arr_name[j][1] == arr_name3[i][2]) || (arr_name[j][1] == arr_name3[i][3])))
				sum++;
		}

		if (sum < 1) {
			printf("(%#2d, %#2d) ", arr_name[j][0], arr_name[j][1]);
			printf("%d %d %d %d \n", arr[j][0], arr[j][1], arr[j][2], arr[j][3]);
		}
	}

}
	



