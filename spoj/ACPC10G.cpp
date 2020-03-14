#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

typedef int64_t i64;
typedef int8_t i8;
typedef uint8_t u8;
typedef int32_t i32;
typedef uint32_t u32;

struct P { i64 x, y; };

static constexpr i64 LU_SIZE = 10;
static const i64 LU[LU_SIZE][LU_SIZE] = {
	{0, 3, 2, 3, 2, 3, 4, 5, 4, 5},
	{3, 2, 1, 2, 3, 4, 3, 4, 5, 6},
	{2, 1, 4, 3, 2, 3, 4, 5, 4, 5},
	{3, 2, 3, 2, 3, 4, 3, 4, 5, 6},
	{2, 3, 2, 3, 4, 3, 4, 5, 4, 5},
	{3, 4, 3, 4, 3, 4, 5, 4, 5, 6},
	{4, 3, 4, 3, 4, 5, 4, 5, 6, 5},
	{5, 4, 5, 4, 5, 4, 5, 6, 5, 6},
	{4, 5, 4, 5, 4, 5, 6, 5, 6, 7},
	{5, 6, 5, 6, 5, 6, 5, 6, 7, 6},
};

static constexpr i64 TABLE_SIZE = 100;
static i64 table[TABLE_SIZE+4][TABLE_SIZE+4];
i64 testTableHelper()
{
	for(int y = 0; y < TABLE_SIZE+4; y++)
	for(int x = 0; x < TABLE_SIZE+4; x++)
		table[y][x] = 0x7FFF'FFFF'FFFF'FFFF;
	table[0+2][0+2] = 0;

	vector<P> q = {{0,0}};
	while(not q.empty())
	{
		static const P dp[] = {
			{-2, -1},
			{-2, +1},
			{-1, -2},
			{-1, +2},
			{+1, -2},
			{+1, +2},
			{+2, -1},
			{+2, +1},
		};
		const P p = q.back();
		q.pop_back();
		const i64 c0 = table[p.y+2][p.x+2];
		for(int i = 0; i < 8; i++) {
			const P np{ p.x+dp[i].x, p.y+dp[i].y };
			if(np.x >= TABLE_SIZE+2 || np.y >= TABLE_SIZE+2 || np.x < -2 || np.y < -2)
				continue;
			i64& c1 = table[np.y+2][np.x+2];
			if(c0+1 < c1) {
				c1 = c0+1;
				q.push_back(np);
			}
		}
	}
};

i64 cost(P a, P b)
{
	P c { abs(a.x-b.x), abs(a.y-b.y) };
	i64 res = 0;
	if(c.x > c.y) {
		const i64 i = min(
			min(c.y, c.x-c.y),
			max(0L, max((c.x-LU_SIZE+2)/2, (c.y-LU_SIZE+1)/1))
		);
		c.x -= 2*i;
		c.y -= i;
		res += i;
		/*while(c.y > 0 && c.x > c.y && (c.x >= LU_SIZE || c.y >= LU_SIZE)) {
			c.x -= 2;
			c.y -= 1;
			res += 1;
		}*/
	}
	else {
		const i64 i = min(
			min(c.x, c.y-c.x),
			max(0L, max((c.x-LU_SIZE+1)/1, (c.y-LU_SIZE+2)/2))
		);
		c.x -= i;
		c.y -= 2*i;
		res += i;
		/*while(c.x > 0 && c.y > c.x && (c.x >= LU_SIZE || c.y >= LU_SIZE)) {
			c.x -= 1;
			c.y -= 2;
			res += 1;
		}*/
	}

	if(c.x >= LU_SIZE && c.y >= LU_SIZE) {
		const i64 i = min(
			max(0L, max((c.x-LU_SIZE+3)/3, (c.y-LU_SIZE+3)/3)),
			min(c.x/3,  c.y/3)
		);
		c.x -= 3*i;
		c.y -= 3*i;
		res += 2*i;
		/*while(c.x > 0 && c.y > 0 && (c.x >= LU_SIZE || c.y >= LU_SIZE)) {
			c.x -= 3;
			c.y -= 3;
			res += 2;
		}*/
	}

	if(c.x >= LU_SIZE) {
		const i64 i = (c.x - LU_SIZE) / 4 + 1;
		c.x -= 4*i;
		res += 2*i;
	}
	else if(c.y >= LU_SIZE) {
		const i64 i = (c.y - LU_SIZE) / 4 + 1;
		c.y -= 4*i;
		res += 2*i;
	}
	res += LU[c.y][c.x];
	return res;
}

i64 testTable()
{
	//testTableHelper();

	for(int y = 0; y < TABLE_SIZE; y++)
	{
		for(int x = 0; x < TABLE_SIZE; x++)
		{
			const i64 myCost = cost({0, 0}, {x, y});
			const i64 rightCost = table[y+2][x+2];
			if(myCost != rightCost)
			{
				printf("Error in {%d, %d}\n", x, y);
				printf("Has %ld, should have %ld\n", myCost, rightCost);
			}
			//printf("%3ld", rightCost);
		}
		//printf("\n");
	}
}

i64 hungarianAlgorithm(const i64* costs, i32 n)
{
	static i64 t[16*16];
	for(i32 i = 0; i < n*n; i++)
		t[i] = costs[i];
	// rows pass
	for(i32 y = 0; y < n; y++) {
		i64 minVal = t[y*n];
		for(i32 x = 1; x < n; x++)
			minVal = min(minVal, t[x + y*n]);
		for(i32 x = 0; x < n; x++)
			t[x + y*n] -= minVal;
	}
	// cols pass
	for(i32 x = 0; x < n; x++) {
		i64 minVal = t[x];
		for(i32 y = 1; y < n; y++)
			minVal = min(minVal, t[x + y*n]);
		for(i32 y = 0; y < n; y++)
			t[x + y*n] -= minVal;
	}
	// count zeros in each row/col
	static i32 zeros[32];
	for(i32 y = 0; y < n; y++) {
		zeros[y] = 0;
		for(i32 x = 0; x < n; x++)
			if(t[x + y*n] == 0)
				zeros[y]++;
	}
	for(i32 x = 0; x < n; x++) {
		zeros[n+x] = 0;
		for(i32 y = 0; y < n; y++)
			if(t[x + y*n] == 0)
				zeros[n+x]++;
	}

	while(true)
	{
		i32 zeros2[32];
		for(i32 i = 0; i < 2*n; i++)
			zeros2[i] = zeros[i];
		bitset<32> crossed = 0;
		// find min number of zero crossings
		while(crossed.count() < n)
		{
			bitset<32> crossed2 = 0;
			for(i32 y = 0; y < n; y++) {
				for(i32 x = 0; x < n; x++) {
					if(t[x + n*y] == 0 && !crossed2[n+x]) {
						crossed2[n+x] = true;
						crossed2[y] = true;
						break;
					}
				}
			}
			// Mark all rows having no assignments
			bitset<32> marked = 0;
			bitset<16> justMarkedRows;
			for(i32 y = 0; y < n; y++) {
				if(!crossed2[y]) {
					marked[y] = true;
				}
			}
			do {
				// Mark all columns having zeros in newly marked rows
				bitset<16> justMarkedCols = 0;
				for(i32 x = 0; x < n; x++) {
					for(i32 y = 0; y < n; y++) {
						if(marked[y] && t[x + n*y] == 0) {
							justMarkedCols[x] = true;
							break;
						}
					}
				}
				// Mark all rows having assignments in newly marked columns
				justMarkedRows = 0;
				for(i32 y = 0; y < n; y++) {
					for(i32 x = 0; x < n; x++) {
						if(justMarkedCols[x] && crossed2[y] && crossed2[x+n]) {
							justMarkedRows[y] = true;
							break;
						}
					}
				}

			} while(justMarkedRows || justMarkedCols);

			/*i32 maxZeros = zeros2[0];
			i32 maxZerosInd = 0;
			for(i32 i = 1; i < 2*n; i++) {
				if(maxZeros < zeros2[i]) {
					maxZeros = zeros2[i];
					maxZerosInd = i;
				}
			}
			if(maxZeros == 0)
				break;
			zeros2[maxZerosInd] -= maxZeros;
			crossed[maxZerosInd] = true;
			if(maxZerosInd < n) { // row
				for(i32 x = 0; x < n; x++) {
					if(t[x + maxZerosInd*n] == 0 && !crossed[n+x]) {
						zeros2[n+x]--;
					}
				}
			}
			else { // col
				for(i32 y = 0; y < n; y++) {
					if(t[maxZerosInd-n + y*n] == 0 && !crossed[y]) {
						zeros2[y]--;
					}
				}
			}*/
		}

		if(crossed.count() == n) {
			i64 res = 0;
			for(i32 i = 0; i < n; i++)
			{
				i64 minZeros = 0x7FFF'FFFF'FFFF'FFFF;
				i64 minZerosInd = -1;
				for(i32 j = 0; j < 2*n; j++)
				if(zeros[j] > 0 && zeros[j] < minZeros) {
					minZeros = zeros[j];
					minZerosInd = j;
				}
				{
					i32 j = minZerosInd;
					zeros[j] = 0;
					if(j < n) { // row
						i32 x;
						for(x = 0; x < n; x++) {
							if(zeros[x+n] && t[x + n*j] == 0) {
								zeros[x+n] = 0;
								res += costs[x + n*j];
								break;
							}
						}
						for(i32 y = 0; y < n; y++)
							if(y != j && t[x + n*y] == 0)
								zeros[y]--;
						for(x++; x < n; x++)
							if(zeros[x+n] && t[x + n*j] == 0)
								zeros[x+n]--;

					}
					else { // col
						j -= n;
						i32 y;
						for(y = 0; y < n; y++) {
							if(zeros[y] && t[j + n*y] == 0) {
								zeros[y] = 0;
								res += costs[j + n*y];
								break;
							}
						}
						for(i32 x = 0; x < n; x++)
							if(x != j && t[x + n*y] == 0)
								zeros[x+n]--;
						for(y++; y < n; y++)
							if(zeros[y] && t[j + n*y] == 0)
								zeros[y]--;
					}
				}
			}
			return res;
		}
		else { // crossed.count() < n
			i64 valMin = 0x7FFF'FFFF'FFFF'FFFF;
			for(i32 y = 0; y < n; y++)
			for(i32 x = 0; x < n; x++)
			{
				if(!crossed[y] && !crossed[x+n] && t[x+y*n] < valMin) {
					valMin = t[x+y*n];
				}
			}
			for(i32 y = 0; y < n; y++)
			for(i32 x = 0; x < n; x++)
			{
				if(!crossed[y] && !crossed[x+n]) {
					t[x+y*n] -= valMin;
					if(t[x+y*n] == 0) {
						zeros[y]++;
						zeros[x+n]++;
					}
				}
				else if(crossed[y] && crossed[x+n]) {
					if(t[x+y*n] == 0) {
						zeros[y]--;
						zeros[x+n]--;
					}
					t[x+y*n] += valMin;
				}
			}
		}
	}
}

int main()
{
	static P hh[16];
	static P tt[16];
	static i64 mm[16*16];
	//testTable();
	i64 n;
	cin >> n;
	i64 iCase = 1;
	while(n)
	{
		for(i64 i = 0; i < n; i++)
			cin >> hh[i].x >> hh[i].y;
		for(i64 i = 0; i < n; i++)
			cin >> tt[i].x >> tt[i].y;

		i64 end = 0;
		for(i64 i = 0; i < n; i++)
		for(i64 j = 0; j < n; j++)
		{
			mm[end] = cost(hh[i], tt[j]);
			//printf("%ld %ld: %ld\n", i, j, mm[end]);
			end++;
		}
		const i64 res = hungarianAlgorithm(mm, n);

		cout << iCase << ". " << res << endl;
		iCase++;
		cin >> n;
	}
}