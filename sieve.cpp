/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Daniel Craig
 * Date        : 9/13/21
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
    const int max_prime_width=num_digits(max_prime_), primes_per_row=80 / (max_prime_width+1);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();

}

void PrimesSieve::display_primes() const {
    // This method is the reason I have no social life.
	cout<<"Primes up to "<<limit_<<":"<<endl;
	int chars=0;
	int chars2=0;
	int i=2;
	int j=2;

	while(j<limit_+1){
		//loop to check if there are 80 characters to begin with. If not, no right align needed.
		if(chars2<=80){
			if(is_prime_[j]==true){
				chars2+=num_digits(j);
				if(chars2>80){
					break;
				}
			}
			j++;
		}
	}
	//If there are fewer than 80 characters, print each prime with a space in between.
	//Only runs if there are fewer than or exactly 80 characters.
	if(chars2<=80){
		int k=2;
		while(k<limit_+1){
			if(is_prime_[k]==true&&k!=max_prime_){
				cout<<k<<" ";
			}
			else if(is_prime_[k]==true&&k==max_prime_){
				cout<<k;
			}
			k++;
		}
	}

	//If there ARE more than 80 characters, then do right align.
	else if(chars2>80){
		while(i<limit_+1){
			if(chars>=80){
				chars=0;
				cout<<endl;
			}
			if(is_prime_[i]==true){
				//had to use num_digits(max_prime_) for max_prime_width
				cout<<setw(num_digits(max_prime_)-1);
				if(chars+num_digits(i)==80){
					cout<<i;
				}
				if(chars+num_digits(i)<80){
					if(i!=max_prime_){
						if(chars+num_digits(i)<79)
							cout<<i<<" ";
						else
							cout<<i;
					}
					else{
						cout<<i;
					}
				}

				chars+=num_digits(max_prime_);
			}
			i++;
		}
	}
	cout<<endl;

}

int PrimesSieve::count_num_primes() const {
	int num=0;

	for(int i=0;i<=limit_;i++){
		if(is_prime_[i]==1){
			num++;
		}
	}
	cout<<endl<<"Number of primes found: "<<num<<endl;
    return num;
}

void PrimesSieve::sieve() {
	for(int i=2;i<limit_+1;i++){
		is_prime_[i]=true;
	}
	//algorithm to find primes
	for(int i=2;i<=sqrt(limit_);i++){
		if(is_prime_[i]==true){
			for(int j=i*i;j<=limit_;j+=i){
				is_prime_[j]=false;
			}
		}
	}
	//sets number of primes constant to the counting method
	num_primes_=count_num_primes();

	//finds max prime.
	for(int j=limit_+1;j>1;j--){
		if(is_prime_[j]==1){
			max_prime_=j;
			break;
		}
	}

	display_primes();
}

int PrimesSieve::num_digits(int num) {
    //Double needed to account for edge cases.
	//Divides by 10 while that number is greater than 1.
	double div=num;
	int digits=1;
	while(div>=1.0){
		div=div/10.0;
		digits++;
	}
    return digits;
}



int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    //object of primeSieve. in the constructor, this calls the sieve method, which does all the fun stuff.
    PrimesSieve mySieve = PrimesSieve(limit);
    return 0;
}
