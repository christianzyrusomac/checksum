
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
 
 //block size is defined as 8
#define BlockSize 8

//functions to be use.
string onesComplement(string data);
string checkSum(string data);
bool check(string data);

int main()
{
	//The program will ask you to input some data to be check in binary form
    string sent_data;
    cout<<"Input data(1's and 0's only): ";
	cin>>sent_data;
    
    check(sent_data);
 
    return 0;
}

//this function is used to invert the result
string onesComplement(string data)
{
    for (int i = 0; i < data.length(); i++) {
        if (data[i] == '0')
            data[i] = '1';
        else
            data[i] = '0';
    }
 
    return data;
}
 
 //this function is used to add up the data whiech is grouped by 8 
string checkSum(string data)
{

    int n = data.length();
    if (n % BlockSize != 0) {
        int pad_size = BlockSize - (n % BlockSize);
        for (int i = 0; i < pad_size; i++) {
            data = '0' + data;
        }
    }
 

    string result = "";
 

    for (int i = 0; i < BlockSize; i++) {
        result += data[i];
    }

    for (int i = BlockSize; i < n; i += BlockSize) {

        string next_block = "";
 
        for (int j = i; j < i + BlockSize; j++) {
            next_block += data[j];
        }
 
  
        string additions = "";
        int sum = 0, carry = 0;
 
  
        for (int k = BlockSize - 1; k >= 0; k--) {
            sum += (next_block[k] - '0')
                   + (result[k] - '0');
            carry = sum / 2;
            if (sum == 0) {
                additions = '0' + additions;
                sum = carry;
            }
            else if (sum == 1) {
                additions = '1' + additions;
                sum = carry;
            }
            else if (sum == 2) {
                additions = '0' + additions;
                sum = carry;
            }
            else {
                additions = '1' + additions;
                sum = carry;
            }
        }
 
        string final = "";
 
        if (carry == 1) {
            for (int l = additions.length() - 1; l >= 0;
                 l--) {
                if (carry == 0) {
                    final = additions[l] + final;
                }
                else if (((additions[l] - '0') + carry) % 2
                         == 0) {
                    final = "0" + final;
                    carry = 1;
                }
                else {
                    final = "1" + final;
                    carry = 0;
                }
            }
 
            result = final;
        }
        else {
            result = additions;
        }
    }
    return onesComplement(result);
}
 
//to check if the data is rejected or accepted.
bool check(string sent_data)
{
 		cout<<"sum = "<<onesComplement(checkSum(sent_data)) <<endl;
 		
 
    string sender_checksum
        = checkSum(sent_data);
 		cout<<"checksum: "<<sender_checksum<<endl;

    string receiver_checksum = checkSum(
        sender_checksum + sent_data);
 		cout<<"checksum + received data = "<<receiver_checksum<<endl;
   
   	
    if (count(receiver_checksum.begin(),
              receiver_checksum.end(), '0')
        == BlockSize) {
        cout<<endl;
        cout << "No Error";
        return true;
    }
    else {
    	cout<<endl;
        cout << "Error";
        return false;
    }
}


