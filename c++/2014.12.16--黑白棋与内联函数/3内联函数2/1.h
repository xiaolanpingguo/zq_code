int add1(int a,int b);
//内联函数的写法和普通函数不一样，是不能
//在h文件写声明，cpp写定义的，
//我们应该直接把内联函数的"定义"写在cpp文件中
//内联函数有点像宏（仅是有点像）。
//inline int add2(int a,int b);