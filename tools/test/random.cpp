#include <random>
#include <iostream>
#include <ctime>
#include <chrono>



//就是不能放在类里，编译不过
//std::mt19937 gen;
std::default_random_engine gen;
//gen.seed(time(0));
std::uniform_real_distribution<> dis(0.0,1.0);	

class tRandom{
public:
	tRandom(){
		//不重新设置时，都是一样的数
		gen.seed(time(0));

	};
	void show(){
		

		for (int n = 0; n < 10; ++n) {
			//Use dis to transform the random unsigned int generated by gen into a double in [1, 2)
			std::cout << dis(gen) << ' '; //Each call to dis(gen) generates a new random double
		}
		//std::random_device rd;  //Will be used to obtain a seed for the random number engine将用于获取随机数引擎的种子
		//std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::cout << '\n';
		
	};
	
};


int main()
{
	tRandom tr;
	tr.show();
	
	

	
	return 0;
}