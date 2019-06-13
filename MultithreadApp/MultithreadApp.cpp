// MultithreadApp.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;



mutex mtx;
 
class MyClass
{
public:
	void DoWork()
	{
		for (size_t i = 0; i < 10; i++)
		{
			mtx.lock();
			cout << "ID Потока =" << this_thread::get_id() << "\tDoWork\t" << i << endl;
			mtx.unlock();
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
	};


	int DoWork2(int a)
	{
		for (size_t i = 0; i < a; i++)
		{
			mtx.lock();
			cout << "ID Потока =" << this_thread::get_id() << "\tDoWork2\t" << i << endl;
			mtx.unlock();
			this_thread::sleep_for(chrono::milliseconds(800));
		}
		return a;
	};

private:

};




int main()
{
	setlocale(LC_ALL, "ru");
	

	MyClass m;


	thread th1([&]()
		{
			m.DoWork();
		});

	int result;;
	
	thread th2([&]()
		{
			result = m.DoWork2(20);
		});

	
	
	th1.join();
	th2.join();

	return 0;

}

