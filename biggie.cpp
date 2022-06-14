#include<iostream>
using namespace std;

class biggie{

private:
	string num;

public:

// ---------------------- CONSTRUCTORS -------------------------	
	// default constructor
	biggie();

	// // parameterized constructor
	biggie(const char*);
	biggie(string&);
	biggie(int);
	biggie(long long int);
	
	// // copy constructor
	biggie(const biggie&);
// ---------------------------------------------------------------



/********************* OPERATOR OVERLOADING **********************/


//----------------------- INPUT / OUTPUT -------------------------
	friend istream& operator >>(istream &in, biggie &n);
	friend ostream& operator <<(ostream &out, const biggie &n);
//----------------------------------------------------------------


//------------------------RELATIONAL operators -------------------
	bool operator ==(biggie &n);
	bool operator !=(biggie &n);
	bool operator >(biggie &n);
	bool operator >=(biggie &n);
	bool operator <(biggie &n);
	bool operator <=(biggie &n);
//----------------------------------------------------------------


//----------------------- ARITHMETIC operators --------------------
	// addition
	biggie operator +(biggie &n);
	void operator +=(biggie &n);

	// subtraction
	biggie operator -(biggie &n);
	void operator -=(biggie &n);

	// multiplication
	biggie operator *(biggie &n);
	void operator *=(biggie &n);
//-----------------------------------------------------------------


//--------------------- INCREMENT / DECREMENT ---------------------
	// prefix increment
	biggie& operator ++();
	// postfix increment
	biggie operator ++(int);

	// prefix decrement
	biggie& operator --();
	// postfix decrement
	biggie operator --(int);
//----------------------------------------------------------------

//---------------------------- MISC ------------------------------
	int size();
	// subscript operator
	int operator [](int);

	friend biggie nth_fibonacci(int);
	friend biggie factorial(int);
//----------------------------------------------------------------

};

biggie :: biggie()
{
	this -> num = "0";
}

biggie :: biggie(string &s)
{
	int len = s.size();
	for(int i = len -1; i >= 0; i--)
		this -> num += s[i];
}

biggie :: biggie(const char *s)
{
	int len = 0;
	while(s[len] != '\0') len++;

	for(int i = len - 1; i >= 0; i--)
		this -> num += s[i]; 
}

biggie :: biggie(int n)
{
	if(n == 0) num = "0";
	while(n)
	{
		this -> num += n % 10 + '0';
		n /= 10;
	}
}

biggie :: biggie(long long int n)
{
	if(n == 0) num = "0";
	while(n)
	{
		this -> num += n % 10 + '0';
		n /= 10;
	}
}

biggie :: biggie(const biggie &bignum)
{
	this -> num = bignum.num;
}

istream& operator >>(istream &in, biggie &n)
{
	in >> n.num;
	int len = n.num.size();
	for(int i = 0; i < len / 2; i++)
	{
		char tmp = n.num[i];
		n.num[i] = n.num[len - 1 - i];
		n.num[len - 1 - i] = tmp;
	}
	return in;
}

ostream& operator <<(ostream &out, const biggie &n)
{
	int len = n.num.size();
	for(int i = len - 1; i >= 0; i--)
		out << n.num[i];

	return out;
}

bool biggie :: operator ==(biggie &n)
{
	if(this -> num == n.num) return true;
	return false;
}

bool biggie :: operator !=(biggie &n)
{
	if(this -> num != n.num) return true;
	return false;
}
bool biggie :: operator >(biggie &n)
{
	int len1 = this -> size();
	int len2 = n.size();
	if(len1 != len2) return len1 > len2;

	int idx = len1 - 1;
	while(idx)
	{
		if(num[idx] != n.num[idx]) 
			return num[idx] > n.num[idx];
	} 

	return false;
}

bool biggie :: operator >=(biggie &n)
{
	if(num == n.num) return true;
	
	int len1 = this -> size();
	int len2 = n.size();
	if(len1 != len2) return len1 > len2;
	if(num == n.num) return true;

	int idx = len1 - 1;
	while(idx)
	{
		if(num[idx] != n.num[idx]) 
			return num[idx] > n.num[idx];
	} 

	return false;
}

bool biggie :: operator <(biggie &n)
{	
	return n > *this;
}

bool biggie :: operator <=(biggie &n)
{
	return n >= *this;
}

void biggie :: operator +=(biggie &n)
{
	*this = *this + n;
}

biggie biggie :: operator +(biggie &n)
{
	string &num1 = this -> num;
	string &num2 = n.num;

	biggie result;
	string &ans = result.num;
	ans = "";

	int len = min(num1.size(), num2.size());

	int carry = 0;
	int i;
	for(i = 0; i < len; i++)
	{
		int digit1 = num1[i] - '0';
		int digit2 = num2[i] - '0';

		int sum = digit1 + digit2 + carry;
		carry = sum / 10;
		sum = sum % 10;
		ans += sum + '0';
	}

	for(; i < num1.size(); i++)
	{
		int sum = (num1[i] - '0') + carry;
		carry = sum / 10;
		sum = sum % 10;
		ans += sum + '0';
	}

	for(; i < num2.size(); i++)
	{
		int sum = (num2[i] - '0') + carry;
		carry = sum / 10;
		sum = sum % 10;
		ans += sum + '0';
	}

	if(carry) ans += carry + '0';

	return result;
}

biggie biggie :: operator -(biggie &n)
{
	biggie result = *this;
	string &num1 = result.num;
	string &num2 = n.num;
	
	if(num1 == num2) return "0";

	int len1 = num1.size();
	int len2 = num2.size();

	for(int i = 0; i < len2; i++)
	{
		int j = i;
		if(num1[i] < num2[i])
		{
			j += 1;
			while(j < len1 and num1[j] < '1') j++;
		}

		if(j == len1)
		{
			return "num1 smaller than num2";
		}

		if(j != i)
		{
			num1[j--]--;
			while(j > i) num1[j--] = '9';
			num1[i] += 10;
		}
		num1[i] = num1[i] - num2[i] + '0';
	}

	int idx = len1 - 1;
	while(num1[idx] == '0') idx--;

	num1.resize(idx + 1);
	return result;
}

void biggie :: operator -=(biggie &n)
{
	*this = *this - n;
}

biggie biggie :: operator *(biggie &n)
{
	string &num1 = this -> num;
	string &num2 = n.num;

	if(num1 == "0" or num2 == "0") return "0";
	if(num1 == "1") return num2;
	if(num2 == "1") return num1;

	int len1 = num1.size();
	int len2 = num2.size();

	biggie result;
	string &ans = result.num;
	ans = string(len1 + len2, '0');

	int idx;
	for(int i = 0; i < num1.size(); i++)
	{
		idx = i;
		int carry = 0;
		for(int j = 0; j < num2.size(); j++)
		{
			int digit1 = num1[i] - '0';
			int digit2 = num2[j] - '0';

			int prod = digit1 * digit2;
			prod += (ans[idx] - '0') + (carry);
			ans[idx] = (prod % 10) + '0';
			carry = prod / 10;
			idx++;
		}

		if(carry) ans[idx++] = carry + '0';
	}

	ans.resize(idx);

	return result;
}

void biggie :: operator *=(biggie &n)
{
	*this = *this * n;
}

biggie& biggie :: operator ++()
{
	biggie tmp = 1;
	*this = *this + tmp;
	return *this;
}

biggie biggie :: operator ++(int dummy)
{
	biggie tmp = *this;
	++(*this);
	return tmp;
}

biggie& biggie :: operator --()
{
	biggie tmp = 1;
	*this = *this - tmp;
	return *this;
}

biggie biggie :: operator --(int dummy)
{
	biggie tmp = *this;
	--(*this);
	return tmp;
}

int biggie :: size()
{
	return (this -> num).size();
}

int biggie :: operator [](int idx)
{
	int len = this -> size();
	return num[len - 1 - idx] - '0';
}

biggie nth_fibonacci(int n)
{
	biggie num1 = "0";
	biggie num2 = "1";

	if(n == 0) return num1;
	if(n == 1) return num2;

	biggie ans;
	for(int i = 1; i < n; i++)
	{
		ans = num1 + num2;
		num1 = num2;
		num2 = ans;
	}

	return ans;
}

biggie factorial(int n)
{
	biggie ans = 1;
	biggie num = 0;
	if(n < 2) return ans;

	for(int i = 0; i < n; i++)
	{
		num++;
		ans *= num;
	}

	return ans;
}

int main()
{
	//sample code to illustrate the biggie class

	// different ways to define and initialize biggie variables
	biggie n1("12345");
	biggie n2 = 12345;
	biggie n3 = "99999";
	biggie n4 = n1;
	biggie n5;

	// can use cout to print to the console
	cout << "n5 " << n5 << endl;

	// can use cin to take INPUT
	cin >> n5;
	cout << "n5 after taking input " << n5 << endl;

	cout << "n1: " << n1 << endl;
	cout << "n2: " << n2 << endl;
	cout << "n3: " << n3 << endl;
	cout << "n4: " << n4 << endl;
	cout << "n5: " << n5 << endl;

	// can compare two biggies
	if (n1 == n2) {
		cout << "n1 and n2 are equal\n";
	}else if(n1 != n2){
		cout << "n1 and n2 are not equal!\n";
	}

	if (n3 < n4) {
		cout << "n3 is smaller than n4\n";
	}else if(n3 >= n4){
		cout << "n4 is greater than equal to n3\n";
	}


	// can add two biggies
	biggie sum = n1 + n3;
	cout << "n1: " << n1 << " n3: " << n3 << " sum = n1 + n3 " << sum << endl;

	// can subtract two biggies
	biggie diff = n3 - n1;
	cout << "n3: " << n3 << " n1: " << n1 << " diff = n3 - n1 " << diff << endl;

	// can also add / subtract assign
	n1 += n4;
	cout << "n1: " << n1 << " n4: " << n4 << "  n1 += n4 " << n1 << endl;


	// can increment or decrement biggie
	cout << "n1 " << n1 << endl;
	cout << "++n1 " << ++n1 << endl; // pre increment
	cout << "n1 " << n1 << endl;
	cout << "n1-- " << n1-- << endl; // post decrement
	cout << "n1 " << n1 << endl;


	// can get the number of digits in a biggie
	cout << "size of n1 is " << n1.size() << endl;

	// can get digit at a specific index
	cout << "n1 " << n1 << "  n1[1] " << n1[1] << endl;


	// biggie can be helpful for computing big factorials and fibonacci
	cout << "factorial of 50 is  " << factorial(50) << endl;

	cout << "100th fibonacci number is  " << nth_fibonacci(100) << endl;
}