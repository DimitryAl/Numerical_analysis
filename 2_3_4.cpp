#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


///////////Численное дифференцирование//////////////////////
void Task2();

///////Численное интегрирование//////////
int Task3();
void Trap(double x[5], double y[5], double step, int N);
void Rect(double x[5], double y[5], double step, int N);
void Simpson(double x[5], double y[5], double step, int N);
///////Численное решение уравнений///////
int Task4();
double F(double x);			//Заданное уравнение
double Der(double x);		//Производная заданного уравнения
double newF(double x);		//Новое уравнение для метода итераций
double newDer(double x);
void Iter(double a, double b);
void Bi(double a, double b);	//Метод Дихотомии
void Newton(double a, double b);//Метод Ньютона
void Secant(double a, double b);//Метод секущих

int main()
{
	setlocale(LC_ALL, "RUS");
	
	cout << "Численное дифференцирование\n";
	Task2();


	cout << "\nЧисленное интегрирование.\n";
	Task3();


	cout << "\nЧисленное решение уравнений.\n";
	Task4();
	return 0;
}
void Task2()
{
	const int N = 5;
	const int n = 4;
	double x[N] = {1.25, 1.27, 1.29, 1.31, 1.33};
	double y[N] = {4.82835, 4.84418, 4.85989, 4.87523, 4.86331};
	double der1[n], der2[n];
	int i;
	double h;

	cout << "Функция заданная в виде таблицы:\n";
	cout << "xi\t";
	for (i = 0; i < N; i++)
	{
		cout << x[i] << "\t";
	}
	cout << "\nyi\t";
	for (i = 0; i < N; i++)
	{
		cout << y[i] << "\t";
	}

	for (i = 0; i < n; i++)
	{
		h = abs(x[i] - x[i + 1]);
		der1[i] = (y[i + 1] - y[i]) / h;
	}
	der2[0] = (-2 * y[0] + 5 * y[0 + 1] - 4 * y[0 + 2] + y[0 + 3]) / (h * h);
	for (i = 1; i < n; i++)
	{
		h = abs(x[i] - x[i + 1]);
		
		der2[i] = (y[i + 1] - 2 * y[i] + y[i - 1]) / (h * h);
	}

	cout << endl;
	for (i = 0; i < n; i++)
	{
		cout << "x = " << x[i] << "\tf'(x) = " << der1[i] /*<< "\tf''(x) = " << der2*/ << endl;
	}
	for (i = 0; i < n; i++)
	{
		cout << "x = " << x[i] << "\tf''(x) = " << der2[i] << endl;
	}
	cout << endl;
}

int Task3()
{
	double x[5] = { 1.25, 1.27, 1.29, 1.31, 1.33 };
	double y[5] = { 4.82835, 4.84418, 4.85989, 4.97523, 4.86331 };
	int i, N = 5;
	double step = (x[4] - x[0]) / N;
	
	cout << "Функция заданная в виде таблицы:\n";
	cout << "xi\t";
	for (i = 0; i < N; i++)
	{
		cout << x[i] << "\t";
	}
	cout << "\nyi\t";
	for (i = 0; i < N; i++)
	{
		cout << y[i] << "\t";
	}
	cout << endl;

	Trap(x, y, step, N);
	Rect(x, y, step, N);
	Simpson(x, y, step, N);

	return 0;
}

void Trap(double x[5], double y[5], double step, int N)
{
	double res = 0;
	int i;

	cout << "\nВычисление интеграла методом трапеции.\n";
	for (i = 1; i < N - 1; i++)
	{
		res += y[i];
	}
	res *= 2;
	res += y[0];
	res += y[N - 1];
	res = res * step / 2;

	cout << "Интеграл равен " << res << endl;
}

void Rect(double x[5], double y[5], double step, int N)
{
	double res = 0;
	int i;

	cout << "\nВычисление интеграла методом левых прямоугольников.\n";
	for (i = 0; i < N - 1; i++)
	{
		res += y[i];
	}
	res *= step;
	cout << "Интеграл равен " << res << endl;
}

void Simpson(double x[5], double y[5], double step, int N)
{
	double res = 0;
	double temp = 0;
	int i;

	cout << "\nВычисление интеграла методом Симпсона.\n";
	res = 0;
	res += y[0];
	for (int i = 1; i < N - 1; i = i + 2)
	{
		temp += y[i];
	}
	temp *= 4;
	res += temp;
	temp = 0;
	for (i = 2; i < N - 2; i = i + 2)
	{
		temp += y[i];
	}
	temp *= 2;
	res += temp;
	res += y[N - 1];
	res =  res * (step / 3);
	cout << "Интеграл равен " << res << endl;
}

int Task4()
{
	double a, b, temp;

	cout << "Заданное уравнение ln(x) + x - 2 = 0\n";
	cout << "Ввод границ отрезка:\n";
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	if (a > b)
	{
		temp = a;
		a = b;
		b = temp;
	}
	if (a <= 0)
	{
		cout << "Точка " << a << " не входит в область определения функции.";
		return 1;
	}
	if (b > 20)
	{
		cout << "Точка " << b << " too big";
		return 3;
	}
	if (F(a) * F(b) > 0)
	{
		cout << "На границах отрезка функция одного знака.";
		return 2;
	}

	Bi(a, b);
	Iter(a, b);
	Newton(a, b);
	Secant(a, b);
}

double F(double x)
{
	return log(x) + x - 2;
}

double Der(double x)
{
	return 1 / x + 1;
}

double newF(double x)
{
	return 2 - log(x);
}

double newDer(double x)
{
	return -1 / x;
}

void Bi(double a, double b)
{
	double eps = 0.01;
	double c;
	int i = 1;
	cout << "\nРешение уравнения методом дихотомии:\n";
	while (fabs(a - b) >= eps)
	{
		c = (a + b) / 2;
		if (F(c) * F(a) <= 0) b = c;
		else  a = c;
		cout << "Шаг " << i << ": X = " << setprecision(10) << c << endl;
		i++;
	}
	cout << "Корень уравнения с точностью " << eps << " равен " << c << endl;
}

void Newton(double a, double b)
{
	double Xn;
	double X0;
	int i = 1;
	double Eps = 0.001;
	cout << "\nРешение уравнения методом Ньютона:\n";
	// Выбираем начальную точку
	X0 = b;
	cout << "Начальная точка = " << X0 << endl;
	Xn = X0 - F(X0) / Der(X0); // Считаем первое приближение
	cout << "Шаг " << i << ": X = " << setprecision(10) << Xn << endl;
	// Продолжаем вычислять  пока не достигнем необходимой точности
	while (abs(X0 - Xn) >= Eps)
	{
		i++;
		X0 = Xn;
		Xn = X0 - F(X0) / Der(X0);
		cout << "Шаг " << i << ": X = " << setprecision(10) << Xn << endl;
	}
	cout << "Корень с точностью " << Eps << " равен " << setprecision(10) << Xn << endl;

}

void Secant(double a, double b)
{
	double c = a, d;
	double Eps = 0.001;
	int i = 1;
	cout << "\nРешение уравнения методом секущих:\n";
	do
	{
		d = c;											//Старое значение точки c
		c = b - ((b - a) / (F(b) - F(a))) * F(b);		//Новое значение точки c
		
		if (F(a) * F(c) <= 0)
		{
			b = c;
		}
		else a = c;
		cout << "Шаг " << i << ": X = " << setprecision(10) << c << endl;
		i++;
	} while (fabs(d - c) >= Eps);
	cout << "Корень с точностью " << Eps << " равен " << setprecision(10) << c << endl;
}

void Iter(double a, double b)
{
	double Eps = 0.001;
	double x, newx;
	int i = 1;
	cout << "\nРешение уравнения методом итераций:\n";
	if (F(a) * F(b) >= 0) return;
	newx = newF(b);
	while(1)
	{
		x = newF(newx);
		if (abs(newDer(x)) >= 1) break;
		cout << "Шаг " << i << ": X = " << setprecision(10) << x << endl;
		i++;
		if (fabs(x - newx) <= Eps) break;
		newx = newF(x);
	}
	
	cout << "Корень с точностью " << Eps << " равен " << setprecision(10) << x << endl;
