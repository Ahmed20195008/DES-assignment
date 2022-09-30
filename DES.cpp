#include <iostream>
#include <cstring>
#include <cmath>
#include <bitset>
#include <bits/stdc++.h>

using namespace std;
string plain_text;
string keys[16];
string new_key="";
/*string strToBinary(string s)
{
    int n = s.length();


    for (int i = 0; i <= n; i++)
    {
        // convert each char to
        // ASCII value
        int val = int(s[i]);

        // Convert ASCII value to binary
        string bin = "";
        while (val > 0)
        {
            (val % 2)? bin.push_back('1') :
                       bin.push_back('0');
            val /= 2;
        }
        reverse(bin.begin(), bin.end());

        cout << bin << " ";
        new_key +=bin;
    }
    return new_key;
}*/
//  XOR Function
string XOR(string First, string Second){
	string Result = "";
	int Size = Second.length();
	for(int i = 0; i < Size; i++)
        {
            if(First[i] != Second[i])
            {
                Result += "1";
            }
		else{
			Result += "0";
            }
	}
	return Result;
}
// decimal to binary
string DecimalToBinary(int decimal)
{
	string binary;
    while(decimal != 0) {
		binary = (decimal % 2 == 0 ? "0" : "1") + binary;
		decimal = decimal/2;
	}
	while(binary.length() < 4){
		binary = "0" + binary;
	}
    return binary;
}
// binary to decimal
int BinaryToDecimal(string binary)
{
    int decimal = 0;
	int counter = 0;
	int size = binary.length();
	for(int i = size-1; i >= 0; i--)
	{
    	if(binary[i] == '1'){
        	decimal += pow(2, counter);
    	}
    counter++;
	}
	return decimal;
}
//Left Shift by 1
string shift_by_1(string shifted_key){
    string shifted1="";
        for(int i = 1; i < 28; i++)
            {
                shifted1 = shifted1 + shifted_key[i];
            }
        shifted1 = shifted1 +  shifted_key[0];
    return shifted1;
}
//Left Shift by 2
string shift_by_2(string shifted_key){
    string shifted2="";
    for(int i = 0; i < 2; i++){
        for(int j = 1; j < 28; j++){
            shifted2 = shifted2+shifted_key[j];
        }
        shifted2 = shifted2+shifted_key[0];
        shifted_key= shifted2;
        shifted2 ="";
    }
    return shifted_key;
}
void GenerateKeys(string bs4){

// Permuted choice 1 (PC-1) table
	int PC1[56] = {
	57,49,41,33,25,17,9,
	1,58,50,42,34,26,18,
	10,2,59,51,43,35,27,
	19,11,3,60,52,44,36,
	63,55,47,39,31,23,15,
	7,62,54,46,38,30,22,
	14,6,61,53,45,37,29,
	21,13,5,28,20,12,4
	};
// Permuted choice 2 (PC-2) table
	int PC2[48] = {
	14,17,11,24,1,5,
	3,28,15,6,21,10,
	23,19,12,4,26,8,
	16,7,27,20,13,2,
	41,52,31,37,47,55,
	30,40,51,45,33,48,
	44,49,39,56,34,53,
	46,42,50,36,29,32
	};
//Compressing the key to 56 bits
	string Compressed_key="";
	for(int i = 0; i < 56; i++){
		Compressed_key+= bs4[PC1[i]-1];
	}
//Dividing the result to left and right
	string left= Compressed_key.substr(0, 28);
	string right= Compressed_key.substr(28, 56);
// Generating 16 keys
	for(int i=0; i<16; i++){
//For rounds 1, 2, 9, 16 the key_chunks
// are shifted by 1.
		if(i == 0 || i == 1 || i==8 || i==15 )
            {
			left= shift_by_1(left);
			right= shift_by_1(right);
		    }
// For other rounds
// are shifted by 2
		else{
			left= shift_by_2(left);
			right= shift_by_2(right);
		    }
//  The left and right key are combined
	string combined_key = left + right;
	string final_key = "";
	//PC2 table is used to transpose the key bits
	for(int i = 0; i < 48; i++){
		final_key = final_key + combined_key[PC2[i]-1];
	}
	keys[i] = final_key;
		//cout<<"Key "<<i+1<<": "<<keys[i]<<endl;
	}

}
string DES_AlGORITHM(){
//initial permutation table
	int I_P[64] = {
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7
	};
//E-Bit Selection Table
	int E_T[48] = {
	32,1,2,3,4,5,4,5,
	6,7,8,9,8,9,10,11,
	12,13,12,13,14,15,16,17,
	16,17,18,19,20,21,20,21,
	22,23,24,25,24,25,26,27,
	28,29,28,29,30,31,32,1
	};
	// The S boxes
	int S_BOXES[8][4][16]=
	{{
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
    },
    {
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
    },
    {
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
    },
    {
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
    },
    {
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
    },
    {
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
    },
    {
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
    },
    {
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
    }};
// The permutation table
	int P_table[32] = {
	16,7,20,21,29,12,28,17,
	1,15,23,26,5,18,31,10,
	2,8,24,14,32,27,3,9,
	19,13,30,6,22,11,4,25
	};
// The inverse permutation table
	int inverse_P[64]= {
	40,8,48,16,56,24,64,32,
	39,7,47,15,55,23,63,31,
	38,6,46,14,54,22,62,30,
	37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,
	35,3,43,11,51,19,59,27,
	34,2,42,10,50,18,58,26,
	33,1,41,9,49,17,57,25
	};
// Applying the initial permutation
  	string IP = "";
	for(int i = 0; i < 64; i++){
		IP += plain_text[I_P[i]-1];
	}
// Dividing the result to left and right
	string left = IP.substr(0, 32);
	string right = IP.substr(32, 64);
// The plain text is encrypted 16 times
	for(int i=0; i<16; i++) {
    	string right_expanded = "";
// 3.1. The right half of the plain text is expanded to 48 bit
    	for(int i = 0; i < 48; i++) {
      		right_expanded += right[E_T[i]-1];
    };
// 3.3. The result is XOR with a key
		string XORED = XOR(keys[i], right_expanded);
		string res = "";
		// 3.4. The result is divided into 8 equal parts and passed
		// through 8 substitution boxes. After passing through a
		// substituion box, each box is reduces from 6 to 4 bits.
		for(int i=0;i<8; i++){
			// Finding row and column indices to lookup the
			// substituition box
      		string row1= XORED.substr(i*6,1) + XORED.substr(i*6 + 5,1);
      		int row = BinaryToDecimal(row1);
      		string col1 = XORED.substr(i*6 + 1,1) + XORED.substr(i*6 + 2,1) + XORED.substr(i*6 + 3,1) + XORED.substr(i*6 + 4,1);;
			int col = BinaryToDecimal(col1);
			int val = S_BOXES[i][row][col];
			res += DecimalToBinary(val);
		}
		// 3.5. Another permutation is applied
		string perm2 ="";
		for(int i = 0; i < 32; i++){
			perm2 += res[P_table[i]-1];
		}
		// 3.6. The result is xored with the left half
		XORED = XOR(perm2, left);
		// 3.7. The left and the right parts of the plain text are swapped
		left = XORED;
		if(i < 15){
			string temp = right;
			right = XORED;
			left = temp;
		}
	}
	// 4. The halves of the plain text are applied
	string combined_text = left + right;
	string Cipher_Text ="";
	// The inverse of the initial permuttaion is applied
	for(int i = 0; i < 64; i++){
		Cipher_Text+= combined_text[inverse_P[i]-1];
	}
	//And we finally get the cipher text
	return Cipher_Text;
}
int main(){


    int choice;
    cout<<"Pleas Enter Your Choice"<<endl;
    cout<<"1-Encryption"<<endl;
    cout<<"2-Decryption"<<endl;

    cin>>choice;
    if (choice==1)
    {
        cout<<"Pleas Enter Plain Text"<<endl;
        cin>>plain_text;
        cout<<"Pleas Enter Your Key"<<endl;
        string key;
        cin>>key;
        GenerateKeys(key);
        string c_t= DES_AlGORITHM();
        cout<<"Ciphertext: "<<c_t<<endl;
    }
    else if (choice==2)
    {
        cout<<"Pleas Enter Cipher Text"<<endl;
        string c_t= DES_AlGORITHM();
        cin>>c_t;
        cout<<"Pleas Enter Your Key"<<endl;
        string key;
        cin>>key;
        GenerateKeys(key);
        int i = 15;
        int j = 0;
        while(i > j)
        {
            string temp = keys[i];
            keys[i] = keys[j];
            keys[j] = temp;
            i--;
            j++;
        }
        plain_text = c_t;
        string apt = plain_text;

        string decrypted = DES_AlGORITHM();
        cout<<"Decrypted text:"<<decrypted<<endl;
// Comapring the initial plain text with the decrypted text
        if (decrypted == apt){
            cout<<"Plain text encrypted and decrypted successfully."<<endl;
        }
    }
    else
        cout<<"You Entered Wrong choice"<<endl;
}