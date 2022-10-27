#include "../baselib/Common.h"
#include "../baselib/ConcurrentAlloc.h"
// #include "Common.h"
// #include "ConcurrentAlloc.h"
#define SIZE 16

void BenchmarkMalloc(size_t ntimes, size_t nworks, size_t rounds)
{
	std::vector<std::thread> vthread(nworks);
	size_t malloc_costtime = 0;
	size_t free_costtime = 0;
	for (size_t k = 0; k < nworks; ++k)
	{
		vthread[k] = std::thread([&, k]() {
			std::vector<void*> v;
			v.reserve(ntimes);
			for (size_t j = 0; j < rounds; ++j)
			{
				size_t begin1 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					v.push_back(malloc(SIZE));
				}
				size_t end1 = clock();
				size_t begin2 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					free(v[i]);
				}
				size_t end2 = clock();
				v.clear();
				malloc_costtime += end1 - begin1;
				free_costtime += end2 - begin2;
			}
		});
	}
	for (auto& t : vthread)
	{
		t.join();
	}
	printf("%u锟斤拷锟竭程诧拷锟斤拷执锟斤拷%u锟街次ｏ拷每锟街达拷malloc %u锟斤拷: 锟斤拷锟窖ｏ拷%u ms\n", nworks, rounds, ntimes, malloc_costtime);
	printf("%u锟斤拷锟竭程诧拷锟斤拷执锟斤拷%u锟街次ｏ拷每锟街达拷free %u锟斤拷: 锟斤拷锟窖ｏ拷%u ms\n", nworks, rounds, ntimes, free_costtime);
	printf("%u锟斤拷锟竭程诧拷锟斤拷malloc&free %u锟轿ｏ拷锟杰计伙拷锟窖ｏ拷%u ms\n", nworks, nworks*rounds*ntimes, malloc_costtime + free_costtime);
}

// 锟斤拷锟街达拷锟斤拷锟斤拷锟酵放达拷锟斤拷 锟竭筹拷锟斤拷 锟街达拷
void BenchmarkConcurrentMalloc(size_t ntimes, size_t nworks, size_t rounds)
{
	std::vector<std::thread> vthread(nworks);
	size_t malloc_costtime = 0;
	size_t free_costtime = 0;
	for (size_t k = 0; k < nworks; ++k)
	{
		vthread[k] = std::thread([&]() {
			std::vector<void*> v;
			v.reserve(ntimes);
			for (size_t j = 0; j < rounds; ++j)
			{
				size_t begin1 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					v.push_back(ConcurrentAlloc(SIZE));
				}
				size_t end1 = clock();
				size_t begin2 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					ConcurrentFree(v[i]);
				}
				size_t end2 = clock();
				v.clear();
				malloc_costtime += end1 - begin1;
				free_costtime += end2 - begin2;
			}
		});
	}
	for (auto& t : vthread)
	{
		t.join();
	}
	printf("%u锟斤拷锟竭程诧拷锟斤拷执锟斤拷%u锟街次ｏ拷每锟街达拷concurrent alloc %u锟斤拷: 锟斤拷锟窖ｏ拷%u ms\n", nworks, rounds, ntimes, malloc_costtime);
		printf("%u锟斤拷锟竭程诧拷锟斤拷执锟斤拷%u锟街次ｏ拷每锟街达拷concurrent dealloc %u锟斤拷: 锟斤拷锟窖ｏ拷%u ms\n",
		nworks, rounds, ntimes, free_costtime);
	printf("%u锟斤拷锟竭程诧拷锟斤拷concurrent alloc&dealloc %u锟轿ｏ拷锟杰计伙拷锟窖ｏ拷%u ms\n",
		nworks, nworks*rounds*ntimes, malloc_costtime + free_costtime);
}


int main()
{
	cout << "==========================================================" << endl;

	// BenchmarkMalloc(100, 10000, 10);
	cout << endl;
	BenchmarkConcurrentMalloc(100, 10000, 10);
	cout << endl << endl;

	cout << "==========================================================" << endl;

	// system("pause");
	return 0;
}