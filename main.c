#include <stdio.h>
#include <math.h>

// Прототипы функций
void   ClearInputBuffer(void);
double ArshinWithGivenPrecision(double x, double eps, int *k_used);

// main
int main(void) {
    double x = 0.0;
    double eps = 0.0;
    int k_used = 0;

    while (1) { // 1 это типа true
        printf("Enter x (|x| < 1) and eps (eps > 0): ");

        if (scanf("%lf %lf", &x, &eps) != 2) { // scanf возвращает количество успешно считанных элементов
            printf("Invalid input!\n");
            ClearInputBuffer();
            continue;
        }

        if (fabs(x) >= 1.0) {
            printf("Series does not converge. |x| must be < 1.\n");
            continue;
        }

        if (eps <= 0.0) {
            printf("Accuracy eps must be positive (eps > 0).\n");
            continue;
        }

        break;
    }

    // Запишем в exact значение соотв. функции
    double exact = log(x + sqrt(1.0 + x * x));

    // Запишем в approx значение соотв. функции
    double approx = ArshinWithGivenPrecision(x, eps, &k_used);

    printf("asinh      : %.12f\n", exact);
    printf("ArshinWithGivenPrecision : %.12f  (N=%d, eps=%.g)\n", approx, k_used, eps);

    return 0;
}

// Очистка входного буфера
void ClearInputBuffer(void) {
    int temp;
    while ((temp = getchar()) != '\n' && temp != EOF) {
        // просто читаем и игнорируем символы до '\n'
    }
}

// Вычисление arsinh(x) через ряд с заданной точностью eps
double ArshinWithGivenPrecision(double x, double eps, int *k_used) {
    double s  = 0.0;   // сумма
    double an = x;     // первый член ряда
    int n = 0;         // номер члена

    // идёт счёт, пока вклад очередного члена ≥ eps
    while (fabs(an) >= eps) {
        s += an;   // добавляем текущий член к сумме

        // вычисляем следующий член ряда по рекуррентной формуле
        an *= -(x * x) * (2.0 * n + 1.0) * (2.0 * n + 1.0) /
              (2.0 * (n + 1.0) * (2.0 * n + 3.0));

        n++;

        // на всякий случай защита от бесконечного цикла
        if (n > 1000000) {
            break;
        }
    }

    if (k_used != NULL) {
        *k_used = n;   // возвращаем количество членов ряда через указатель
    }

    return s;
}
