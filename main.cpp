#include <iostream>

using namespace std;

//Global variables
int p = 7;
const auto N = 16;
int Mp = (1 << p) - 1;
int invN = (1 << p)/N; // invN = 2^p/N

int mod(int input, int Mp);
void calculateNMNTMatrix(int p1, int N1);

int main(){

    calculateNMNTMatrix(p, N);
    return 0;
}

int mod(int input, int Mp) {
    int result = input % Mp;
    if (result < 0) {
        result += Mp;
    }
    return result;
}
//Definition of calculateNMNTMatrix
void calculateNMNTMatrix(int p1, int N1){
    int alpha1, alpha2;
    int alpha1_temp, alpha2_temp, alpha1_0, alpha2_0;
    int *beta1 = NULL, *beta2 = NULL, *beta = NULL;
    const auto row = N;
    const auto col = N;
    //n = 16;

    int m = log2(N);// m = log2(2^p+1) => m = p + 1
    alpha1 = 2; // Root value of alpha1(0)
    alpha2 = 3; // Root value of alpha2(0)
    int Nmax = 1 << (p - 1); //Nmax = 2^(p-1)



    auto NMNT = new unsigned long long[row][col];

    cout <<"m = " <<m <<endl;
    cout <<"Nmax = " <<Nmax <<endl;
    cout <<"Mp = " <<Mp <<endl;

    for (int i = 0; i < p-2; i++){
        alpha1 = mod((alpha1 * alpha1), Mp); //alpha1 = 2^q, q = 2^(p-2), alpha1 = 2^2^(p-2)
        alpha2 = mod((alpha2 * alpha2), Mp); //alpha2 = 3^q, q = 2^(p-2), alpha2 = 3^2^(p-2)
    }

    cout <<"alpha1_0: " <<alpha1 <<endl;
    cout <<"alpha2_0: " <<alpha2 <<endl;


    for (int j = 0; j < p - m ; j++){
        alpha1_temp = mod((alpha1 * alpha1 - alpha2 * alpha2),Mp);
        alpha2_temp = mod((2 * alpha1 * alpha2), Mp);
        alpha1 = alpha1_temp;
        alpha2 = alpha2_temp;
    }

    cout <<"alpha1: " <<alpha1 <<endl;
    cout <<"alpha2: " <<alpha2 <<endl;

    beta1 = new int [(N-1)*(2*N-1)];
    beta2 = new int [(N-1)*(2*N-1)];
    beta = new int[(N-1)*2*(2*N-1)];

    beta1[0] = 1;
    beta2[0] = 0;
    beta[0] = beta1[0] + beta2[0];

    //Using precalculated alpha1 and alpha2 for p = 7 and N = 16
// alpha1 = 106;
// alpha2 = 103;

    //Calculation of beta[n]
    for(int i = 0; i < (N-1)*(2*N-1); i++) {

        beta1[i + 1] = mod((alpha1 * beta1[i] - alpha2 * beta2[i]), Mp);

        if (beta1[i + 1] < 0) {
            beta1[i + 1] = beta1[i + 1] + Mp;
        } else if (beta1[i + 1] > Mp/2) {
            beta1[i + 1] = beta1[i + 1] - Mp;
        }

        beta2[i + 1] = mod((alpha1 * beta2[i] + alpha2 * beta1[i]), Mp);

        if (beta2[i + 1] < 0) {
            beta2[i + 1] = beta2[i + 1] + Mp;
        } else if (beta2[i + 1] > Mp/2) {
            beta2[i + 1] = beta2[i + 1] - Mp;
        }

//        beta1[i + 1] = mod((alpha1 * beta1[i] - alpha2 * beta2[i]), Mp);
//        beta2[i + 1] = mod((alpha1 * beta2[i] + alpha2 * beta1[i]), Mp);

        // cout <<"beta1[i]: " << beta1[i] << endl;
        // cout <<"beta2[i]: " << beta2[i] << endl;
        beta[i + 1] = mod((beta1[i + 1] + beta2[i + 1]), Mp);
        //cout << "beta[" << i + 1 << "]: " << beta[i + 1] << endl;


    }

    //Populate NMNT matrix with beta(nk)
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            if (r == 0){
                NMNT[r][c] = beta[0];
            } else {
                NMNT[r][c] = beta[r * (2*c + 1)];
            }

            cout << NMNT[r][c] << " \n"[c == col - 1];
        }

    }

    //Free memory pointed to by beta1, beta2 and beta;
    delete [] beta1;
    delete [] beta2;
    delete [] beta;
    delete [] NMNT;

    //Clear beta1, beta2, beta to prevent using invalid memory reference
    beta1 = NULL;
    beta2 = NULL;
    beta = NULL;
    NMNT = NULL;

}

