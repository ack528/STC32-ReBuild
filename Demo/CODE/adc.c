#include "headfile.h"
#include "adc.h"

void adc_get(int *temp)
{
    int a1[4], a2[4], a3[4], a4[4], a5[4], a6[4], a7[4], a8[4];

    a1[0] = (adc_once(ADC_P17, ADC_12BIT));
    a2[0] = (adc_once(ADC_P16, ADC_12BIT));
    a3[0] = (adc_once(ADC_P15, ADC_12BIT));
    a4[0] = (adc_once(ADC_P14, ADC_12BIT));
		a5[0] = (adc_once(ADC_P13, ADC_12BIT));
		a6[0] = (adc_once(ADC_P11, ADC_12BIT));
		a7[0] = (adc_once(ADC_P06, ADC_12BIT));	
		a8[0] = (adc_once(ADC_P10, ADC_12BIT));	
	
    a1[1] = (adc_once(ADC_P17, ADC_12BIT));
    a2[1] = (adc_once(ADC_P16, ADC_12BIT));
    a3[1] = (adc_once(ADC_P15, ADC_12BIT));
    a4[1] = (adc_once(ADC_P14, ADC_12BIT));
		a5[1] = (adc_once(ADC_P13, ADC_12BIT));
		a6[1] = (adc_once(ADC_P11, ADC_12BIT));
		a7[1] = (adc_once(ADC_P06, ADC_12BIT));	
		a8[1] = (adc_once(ADC_P10, ADC_12BIT));	

    a1[2] = (adc_once(ADC_P17, ADC_12BIT));
    a2[2] = (adc_once(ADC_P16, ADC_12BIT));
    a3[2] = (adc_once(ADC_P15, ADC_12BIT));
    a4[2] = (adc_once(ADC_P14, ADC_12BIT));
		a5[2] = (adc_once(ADC_P13, ADC_12BIT));
		a6[2] = (adc_once(ADC_P11, ADC_12BIT));
		a7[2] = (adc_once(ADC_P06, ADC_12BIT));	
		a8[2] = (adc_once(ADC_P10, ADC_12BIT));	
	
    a1[3] = (adc_once(ADC_P17, ADC_12BIT));
    a2[3] = (adc_once(ADC_P16, ADC_12BIT));
    a3[3] = (adc_once(ADC_P15, ADC_12BIT));
    a4[3] = (adc_once(ADC_P14, ADC_12BIT));
		a5[3] = (adc_once(ADC_P13, ADC_12BIT));
		a6[3] = (adc_once(ADC_P11, ADC_12BIT));
		a7[3] = (adc_once(ADC_P06, ADC_12BIT));	
		a8[3] = (adc_once(ADC_P10, ADC_12BIT));	

    temp[0] = MeanFilter(a1, 4);
    temp[1] = MeanFilter(a2, 4);
    temp[2] = MeanFilter(a3, 4);
    temp[3] = MeanFilter(a4, 4);
		temp[4] = MeanFilter(a5, 4);
    temp[5] = MeanFilter(a6, 4);
    temp[6] = MeanFilter(a7, 4);
    temp[7] = MeanFilter(a8, 4);

//    temp[0] = temp[0] < 1 ? 1 : temp[0];
//    temp[1] = temp[1] < 1 ? 1 : temp[1];
//    temp[2] = temp[2] < 1 ? 1 : temp[2];
//    temp[3] = temp[3] < 1 ? 1 : temp[3];
//		temp[4] = temp[4] < 1 ? 1 : temp[4];
//    temp[5] = temp[5] < 1 ? 1 : temp[5];
//    temp[6] = temp[6] < 1 ? 1 : temp[6];
//    temp[7] = temp[7] < 1 ? 1 : temp[7];
//		
//		temp[0]=temp[0]>1500?1500:temp[0];
//		temp[1]=temp[1]>1500?1500:temp[1];
//		temp[2]=temp[2]>1500?1500:temp[2];
//		temp[3]=temp[3]>1500?1500:temp[3];
//		temp[4]=temp[4]>1500?1500:temp[4];
//		temp[5]=temp[5]>1500?1500:temp[5];
//		temp[6]=temp[6]>1500?1500:temp[6];
//		temp[7]=temp[7]>1500?1500:temp[7];


}
int MeanFilter(int *arr, int n)
{
    int i = 0;
    float Sum = 0;
    float result;

    for (i = 0; i < n; i++)
    {
        Sum += arr[i];
    }
    result = Sum / n;
    return (int)result;
}

float ADC_error = 0;
float error_get(int *temp, int flag)
{
    float L, R, awm;

    if (flag == cross)
    {
        awm = (float)(temp[0] - temp[4]) / (float)(temp[0] + temp[4]);
    }
    else if (flag == right_angle)
    {
        L = sqrt((double)temp[0] * (double)temp[0] + (double)temp[1] * (double)temp[1]);
        R = sqrt((double)temp[3] * (double)temp[3] + (double)temp[4] * (double)temp[4]);
        awm = (L - R) / (L + R);
    }
    else
    {
        L = sqrt((double)temp[0] * (double)temp[0] + (double)temp[1] * (double)temp[1]);
        R = sqrt((double)temp[3] * (double)temp[3] + (double)temp[4] * (double)temp[4]);
        awm = (L - R) / (L + R);
    }
		ADC_error = awm;
    return awm;

}
