#include <stdio.h>

int main(void)
{ 
	int nTotalmoney = 0; //받은 금액
	int nDiscount = 0; //할인율
	int nDiscount_Amount = 0; //할인금액
	int nProduct_Price = 0; //단가
	int nQuantity = 0; //수량
	int nPayment_amount = 0; //결제금액
	int nChange = 0; //거스름돈
	int nManwon = 0; //만원권
	int nChonwon = 0; //천원권
	int nBaekwon = 0; //백원권
	double dSibwong = 0.0; //십원권

	printf("Write down the money you received. :\n"); //얼마를 받았나
	scanf_s("%d", &nTotalmoney);
	printf("money received : %d WON \n", nTotalmoney); 
	printf("What is the unit price of the product? : \n"); //상품 단가가 얼마인가?
	scanf_s("%d", &nProduct_Price);
	printf("How many are there? : \n"); //수량은 몇게 인가?
	scanf_s("%d", &nQuantity);
	printf("What is the discount rate?(%%) : \n"); //할인율이 얼마인가?
	scanf_s("%d", &nDiscount);

	nPayment_amount = (nProduct_Price * nQuantity) - ((nProduct_Price * nQuantity) * nDiscount / 100); // 결제금액
	nChange = (nTotalmoney - nPayment_amount); //거스름돈
	nDiscount_Amount = ((nProduct_Price * nQuantity) * nDiscount / 100); //할인금액
	nManwon = nChange / 10000; //만원권
	nChonwon = (nChange % 10000) / 1000; //천원권
	nBaekwon = (nChange % 1000) / 100; //백원권
	dSibwong = (nChange % 100) / 10.0; //십원권

	//출력
	printf("Product price ; %d \n", nProduct_Price);
	printf("Number of items ; %d \n\n", nQuantity);

	printf("Payment amount ; %d \n", nPayment_amount);
	printf("Discount rate ; %d %% \n", nDiscount);
	printf("Discount amount ; %d \n\n", nDiscount_Amount);
	
	printf("Change ; %d \n", nChange);
	printf("10,000 won bills ; %d \n", nManwon);
	printf("1,000 won bills ; %d \n", nChonwon);
	printf("100 won bills ; %d \n", nBaekwon);
	printf("10 won coins ; %.1f \n", dSibwong);

}